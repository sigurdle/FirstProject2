#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

DispatcherObject::DispatcherObject()
{
#if WIN32

	m_threadId = MSWindows::GetCurrentThreadId();

#elif AMIGA

	m_pTask = FindTask(NULL);

#else
#error unknown os
#endif
}

}	// UI
}
