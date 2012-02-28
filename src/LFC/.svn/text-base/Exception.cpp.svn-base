#include "stdafx.h"
#include "LFC.h"
#include <algorithm>

namespace System
{

Exception::Exception(StringIn reason/* = StringIn()*/, Exception* innerException/* = NULL*/, HRESULT hr/* = E_FAIL */) : m_reason(reason), m_innerException(innerException), m_HResult(hr)
{
	m_nframes = CaptureStackBackTrace(1, _countof(m_backtraces), m_backtraces, NULL);
}

// copy constructor
Exception::Exception(const Exception& e) :
	m_filename(e.m_filename),
	m_line(e.m_line),
	m_reason(e.m_reason),
	m_innerException(e.m_innerException)
{
	m_nframes = CaptureStackBackTrace(1, _countof(m_backtraces), m_backtraces, NULL);
}

String Exception::get_Reason()
{
	return m_reason;
}

String Exception::get_Filename()
{
	return &m_filename;
}

int Exception::get_Line()
{
	return m_line;
}

LFCEXT IO::TextWriter& WriteToStream(IO::TextWriter& writer, Exception* e)
{
	writer << e->get_Filename() << paren(e->m_line) << " : ";

	if (System::GetType((void*)e, true/*nothrow*/))
	{
		writer << e->GetType()->get_QName();
	}
	else
	{
		writer << "exception";
	}

	writer << " : " << e->get_Reason() << endl;

	if (false)
	{
		//void* backtraces[256];
	//	WORD nframes = CaptureStackBackTrace(0, _countof(backtraces), backtraces, NULL);
		for (size_t i = 0; i < e->m_nframes; ++i)
		{
			ULONG_PTR absaddress = (ULONG_PTR)e->m_backtraces[i];

			Module* pModule = Module::FromAddress((const void*)absaddress);

			if (pModule)
			{
				writer << pModule->get_Name();

				if (pModule->_p)
				{
					Declarator d;
					d.m_offset = absaddress - (ULONG_PTR)pModule->GetModuleInstance();;

					Declarator** decl = std::lower_bound(pModule->_p->m_allfunctions.begin(), pModule->_p->m_allfunctions.end(), &d, decl_offset_less_than);
					if (decl != pModule->_p->m_allfunctions.end())
					{
						writer << " - ";
						writer << (*decl)->get_QName();
					}
				}
			}
			else
			{
				writer << e->m_backtraces[i];
			}

			writer << endl;
		}
	}

	return writer;
}

Exception* Exception::FromHResult(StringIn str, HRESULT hr)
{
	if (hr == E_OUTOFMEMORY)
	{
		return new OutOfMemoryException(str);
	}
	else if (hr == E_INVALIDARG)
	{
		return new ArgumentException(str);
	}
	/*
	else if (hr == ERROR_INVALID_NAME)
	{
		return new IO::FileNotFoundException(str);
	}
	else if (hr == ERROR_CANT_RESOLVE_FILENAME)
	{
		return new IO::FileNotFoundException(str);
	}
	else if (hr == ERROR_CANT_ACCESS_FILE)
	{
		return new IO::FileNotFoundException(str);
	}
	*/
	
	/*
	else if (hr >= 3900 && hr <= 3999)
	{
		if (hr == STG_E_FILENOTFOUND)
		{
			return new IO::FileNotFoundException();
		}
		else
			return new IO::IOException();
	}
	*/
	else
		return new Exception(str);
}

Exception* Exception::FromHResult(HRESULT hr, IErrorInfo* errorinfo)
{
	String errmsg;
	String source;

	if (errorinfo)
	{
		ComBSTR descriptionBSTR;
		errorinfo->GetDescription(&descriptionBSTR);

		ComBSTR sourceBSTR;
		errorinfo->GetSource(&sourceBSTR);

		ComBSTR helpfileBSTR;
		errorinfo->GetHelpFile(&helpfileBSTR);

		DWORD helpContext;
		errorinfo->GetHelpContext(&helpContext);

		errmsg = descriptionBSTR;
		source = sourceBSTR;
	}
	else
	{
		LPTSTR errorText = NULL;
		FormatMessage(    // use system message tables to retrieve error text
			FORMAT_MESSAGE_FROM_SYSTEM |   // allocate buffer on local heap for error text
			FORMAT_MESSAGE_ALLOCATE_BUFFER |   // Important! will fail otherwise, since we're not     // (and CANNOT) pass insertion parameters
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,    // unused with FORMAT_MESSAGE_FROM_SYSTEM
			hr,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&errorText,  // output
			0, // minimum size for output buffer
			NULL);   // arguments - see note
		if (errorText != NULL)
		{
			errmsg = errorText;

			LocalFree(errorText);
			errorText = NULL; 
		}
	}

	Exception* e;

	if (hr == E_OUTOFMEMORY)
	{
		e = new OutOfMemoryException(errmsg);
	}
	else if (hr == E_INVALIDARG)
	{
		e = new ArgumentException(errmsg);
	}
	else if (hr == E_POINTER)
	{
		e = new ArgumentNullException(errmsg);
	}
	else if (hr == E_NOTIMPL)
	{
		e = new NotImplementedException(errmsg);
	}
	/*
	else if (hr >= 3900 && hr <= 3999)
	{
		if (hr == STG_E_FILENOTFOUND)
		{
			return new IO::FileNotFoundException();
		}
		else
			return new IO::IOException();
	}
	*/
	else
		e = new Exception(errmsg, NULL, hr);

	e->m_source = source;

	return e;
}

Exception* Exception::FromStdException(const std::exception& e)
{
	if (auto e2 = dynamic_cast<const std::bad_alloc*>(&e))
	{
		return new OutOfMemoryException(e2->what());
	}
	/*
	else if (auto e2 = dynamic_cast<const std::bad_array_new_length*>(&e))
	{
		return new ArrayAllocationException(e2->what());
	}
	*/

	return new Exception(e.what());
}

}	// System
