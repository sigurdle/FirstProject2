#include "stdafx.h"
#include "LFC.h"

namespace System
{

extern list<HANDLE, std_allocator> g_threads;

__declspec(thread) Thread* s_currentThread;

Thread::Thread(HANDLE hThread, DWORD threadId) : m_hThread(hThread), m_threadId(threadId)
{
}

/*
int Thread::Run(Object* param)
{
	return 0;
}
*/

void Thread::RunProc(ThreadStarterProc proc, Object* param)
{
	ThreadProcParameter* _param = new ThreadProcParameter;
	_param->m_thisThread = this;
	_param->m_param = param;
	_param->m_proc = proc;
	m_hThread = ::CreateThread(NULL, 0, ThreadProc, _param, 0, &m_threadId);
	g_threads.push_back(m_hThread);
}

// static
DWORD WINAPI Thread::ThreadProc(LPVOID lpParameter)
{
	ThreadProcParameter* param = (ThreadProcParameter*)lpParameter;

	ASSERT(s_currentThread == NULL);
	s_currentThread = param->m_thisThread;

	int result = param->m_proc(param->m_param);

	delete param;

	return result;
}

// static
Thread* Thread::CurrentThread()
{
	if (s_currentThread == NULL)
	{
		HANDLE hThread = ::GetCurrentThread();
		DWORD threadId = ::GetCurrentThreadId();

		s_currentThread = new Thread(hThread, threadId);
	}

	return s_currentThread;
}

// static
void Thread::Sleep(DWORD milliseconds)
{
	::Sleep(milliseconds);
}

uint Thread::GetExitCode()
{
	DWORD exitcode;
	BOOL success = GetExitCodeThread(m_hThread, &exitcode);
	if (!success)
	{
		DWORD lastError = GetLastError();
		raise(SystemException(L"GetExitCodeThread failed"));
	}
	return exitcode;
}

}	// System
