#include "stdafx.h"
#include "GUI2.h"

namespace System
{

GUIEXT DdeInstance* g_ddeInst;

namespace Gui
{

ValueBinding<double> TimeManager::s_GlobalTime;

TimeManager::TimeManager()
{
}

ValueBinding<double>* TimeManager::get_GlobalTime()
{
	return &s_GlobalTime;
}

float timer_fps = 30.0f;
int timer_delay_ms = int(1000 / timer_fps);

void TimeManager::Tick()
{
	double globalTime = s_GlobalTime.m_value + (1.0/timer_fps);
	s_GlobalTime.SetValue(globalTime);

	Date* date = Date::get_CurrentDate();
	SYSTEMTIME systemtime;
	GetLocalTime(&systemtime);
	date->set_Year(systemtime.wYear);
	date->set_DayOfWeek(systemtime.wDayOfWeek);
	date->set_HourOfDay(systemtime.wHour);
	date->set_Second(systemtime.wSecond);
	date->set_Minute(systemtime.wMinute);
	date->set_Milliseconds(systemtime.wMilliseconds);

	OnTick(globalTime);
}

TimeManager TimeManager::manager;

GUIEXT IXAudio2* pXAudio2 = nullptr;
GUIEXT IXAudio2MasteringVoice* pMasteringVoice = nullptr;
GUIEXT XAUDIO2_DEVICE_DETAILS deviceDetails;

GUIEXT X3DAUDIO_HANDLE X3DInstance;

GUIEXT bool InitAudio()
{
	if (pXAudio2 == nullptr)
	{
	#ifndef _XBOX
		CoInitializeEx(NULL, COINIT_MULTITHREADED);
	#endif

		UINT32 flags = 0;
#ifdef _DEBUG
		flags |= XAUDIO2_DEBUG_ENGINE;
#endif
		HRESULT hr;
		hr = XAudio2Create(&pXAudio2, flags, XAUDIO2_DEFAULT_PROCESSOR);
		if (FAILED(hr))
		{
			return false;
		}

		pXAudio2->GetDeviceDetails(0,&deviceDetails);
		DWORD channelMask = deviceDetails.OutputFormat.dwChannelMask;

		X3DAudioInitialize(channelMask, X3DAUDIO_SPEED_OF_SOUND, X3DInstance);
	}

	//
	// Create a mastering voice
	//
	if (pMasteringVoice == nullptr)
	{
		HRESULT hr;
		hr = pXAudio2->CreateMasteringVoice(&pMasteringVoice);
		ASSERT(SUCCEEDED(hr));
	}

	return true;
}

VOID CALLBACK MyTimerproc(HWND hwnd,
    UINT uMsg,
    UINT_PTR idEvent,
    DWORD dwTime
)
{
}

void DispatchCall(WPARAM wParam, LPARAM lParam)
{
	if (wParam == 1)	// constructor
	{
		DispatchMsg* dmsg = (DispatchMsg*)lParam;
		if (dmsg)
		{
			try
			{
				VERIFY(dmsg->m_object);
				VERIFY(dmsg->m_method);

				// TODO
				void_invoke_method32(dmsg->m_method->GetAddress(), dmsg->m_object, dmsg->m_args, dmsg->m_args_nbytes);
			}
			catch (Exception* e)
			{
				dmsg->m_exception = e;
			}

			if (dmsg->caller.m_hWaitEvent)
				SetEvent(dmsg->caller.m_hWaitEvent);
			else
				ASSERT(0);
		}
	}
	else if (wParam == 3)	// Call function
	{
		DispatchMsg* dmsg = (DispatchMsg*)lParam;

		try
		{
			VerifyArgumentNotNull(dmsg->m_func);

			FunctionType* func = dmsg->m_func->m_pType->AsFunction();
			Type* pReturnType = func->get_ReturnType()->GetBaseType();

			switch (pReturnType->get_Kind())
			{
			case type_void:
				{
					dmsg->m_func->invoke_functionA<void>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_bool:
				{
					dmsg->retval.bool_val = dmsg->m_func->invoke_functionA<bool>(dmsg->m_args, dmsg->m_args_nbytes) & 1;
				}
				break;

			case type_char:
			case type_signed_char:
			case type_unsigned_char:

			case type_wchar:

			case type_short:
			case type_unsigned_short:

			case type_int:
			case type_unsigned_int:
				{
					dmsg->retval.int32_val = dmsg->m_func->invoke_functionA<int>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_long:
			case type_unsigned_long:
				{
					dmsg->retval.long_val = dmsg->m_func->invoke_functionA<long>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_long_long:
			case type_unsigned_long_long:
				{
					dmsg->retval.int64_val = dmsg->m_func->invoke_functionA<long long>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_enum:
				{
					// Shouldn't happen
					ASSERT(0);
					// basicType

					//dmsg->retval.int32val = dmsg->m_func->invoke_functionA<int>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_float:
				{
					dmsg->retval.float_val = dmsg->m_func->invoke_functionA<float>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_double:
				{
					dmsg->retval.double_val = dmsg->m_func->invoke_functionA<double>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_long_double:
				{
					dmsg->retval.double_val = dmsg->m_func->invoke_functionA<long double>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_pointer:
			case type_reference:
				{
					dmsg->retval_struct = dmsg->m_func->invoke_functionA<void*>(dmsg->m_args, dmsg->m_args_nbytes);
				}
				break;

			case type_class:
				{
					dmsg->m_func->struct_invoke_function(dmsg->m_args, dmsg->m_args_nbytes, dmsg->retval_struct);
				}
				break;

			default:
				raise(SystemException("Unknown type"));
			}
		}
		catch (Exception* e)
		{
			dmsg->m_exception = e;
		}

		if (dmsg->caller.m_hWaitEvent)
			SetEvent(dmsg->caller.m_hWaitEvent);
		else
			ASSERT(0);
	}
	else if (wParam == 2)	// Call method
	{
		DispatchMsg* dmsg = (DispatchMsg*)lParam;
		if (dmsg)
		{
			try
			{
				VERIFY(dmsg->m_dispatch);
				VERIFY(dmsg->m_object);
				VERIFY(dmsg->m_method);

				FunctionType* func = dmsg->m_func->m_pType->AsFunction();
				Type* pReturnType = func->get_ReturnType()->GetBaseType();

				switch (pReturnType->get_Kind())
				{
				case type_void:
					{
						dmsg->m_dispatch->Invoke<void>(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_bool:
					{
						dmsg->retval.bool_val = dmsg->m_dispatch->Invoke<bool>(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_char:
				case type_signed_char:
				case type_unsigned_char:

				case type_wchar_t:

				case type_short:
				case type_unsigned_short:

				case type_int:
				case type_unsigned_int:
					{
						dmsg->retval.int32_val = dmsg->m_dispatch->Invoke<int>(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_long:
				case type_unsigned_long:
					{
						dmsg->retval.long_val = dmsg->m_dispatch->Invoke<long>(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_long_long:
				case type_unsigned_long_long:
					{
						dmsg->retval.int64_val = dmsg->m_dispatch->Invoke<long long>(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

					/*
				case type_enum:
					{
						dmsg->retval.int32val = dmsg->m_dispatch->int32_Invoke(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;
					*/

				case type_float:
					{
						dmsg->retval.float_val = dmsg->m_dispatch->float_Invoke(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_double:
				case type_long_double:
					{
						dmsg->retval.double_val = dmsg->m_dispatch->double_Invoke(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_pointer:
				case type_reference:
					{
						dmsg->retval_struct = dmsg->m_dispatch->pointer_Invoke(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes);
					}
					break;

				case type_class:
					{
						dmsg->m_dispatch->struct_Invoke(dmsg->m_object, dmsg->m_method, dmsg->m_args, dmsg->m_args_nbytes, dmsg->retval_struct);
					}
					break;

				default:
					raise(SystemException("Unknown type"));
				}
			}
			catch (Exception* e)
			{
				dmsg->m_exception = e;
			}

			if (dmsg->caller.m_hWaitEvent)
				SetEvent(dmsg->caller.m_hWaitEvent);
			else
				ASSERT(0);
		}
	}
	else
	{
		raise(ArgumentException());
	}
}

BOOL WINAPI ConsoleCloseHandler(DWORD dwCtrlType)
{
	// TODO

	/*
	switch (dwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		break;

	default:
	*/

	if (true)
	{
		for (auto it = Window::s_windows.m_list.begin(); it != Window::s_windows.m_list.end(); ++it)
		{
			Window* pWindow = *it;

			if (pWindow->get_PWindow())
			{
				PostMessageW(pWindow->get_PWindow()->get_Handle(), WM_CLOSE, 0, 0);
			}
		}
	}

	if (g_ddeInst)
	{
		if (g_ddeInst->m_id)
		{
			DdeUninitialize(g_ddeInst->m_id);
			g_ddeInst->m_id = 0;
		}
	}

//	DecAppLockCount();
	//return TRUE;

//CTRL_CLOSE_EVENT
	return FALSE;	// continue to exit
}

int MessageLoop()
{
//	Window::ActiveWindowBinding.SetValue(Window::FromHwnd(::GetActiveWindow()));
//	Window::ForegroundWindowBinding.SetValue(Window::FromHwnd(::GetForegroundWindow()));
//	Window::FocusWindowBinding.SetValue(Window::FromHwnd(::GetFocus()));

	SetConsoleCtrlHandler(ConsoleCloseHandler, true);

	UINT_PTR nTimerID = SetTimer(nullptr, 0, timer_delay_ms, MyTimerproc);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (msg.message == WM_USER+1)
		{
			DispatchCall(msg.wParam, msg.lParam);
		}
		else if (msg.message == WM_TIMER)
		{
			if (msg.wParam == nTimerID && msg.hwnd == nullptr)
			{
				TimeManager::manager.Tick();
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

		//	if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);

				for (auto it = Window::s_windows.m_list.begin(); it != Window::s_windows.m_list.end(); ++it)
				{
					(*it)->PostMessage(&msg);
				}

	#if 0
				// TODO differently
				svgwindow->ArrangeOverride(LDraw::SizeD());
	#endif
			}
		}

		if (GetAppLockCount() == 0)
		{
			PostQuitMessage(0);
		}
	}

	return msg.wParam;
}

}	// Gui
}	// System
