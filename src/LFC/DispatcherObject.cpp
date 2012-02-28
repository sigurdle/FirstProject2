#include "stdafx.h"
#include "LFC.h"
#include "NameMangler.h"

namespace System
{

DispatcherObject::DispatcherObject()
{
	m_hThread = ::GetCurrentThread();
	m_threadId = GetCurrentThreadId();
}

}	// System
