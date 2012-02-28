#include "stdafx.h"
#include "LXUI2.h"
#include "LXUICommandInvokeEvent.h"

namespace System
{
namespace UI
{

#if 0
CommandInvokeEvent::CommandInvokeEvent()
{
	m_Command = 0;
}

long CommandInvokeEvent::get_Command() const
{
	return m_Command;
}

void CommandInvokeEvent::InitCommandInvokeEvent(StringW* eventType, long Command)
{
	InitEvent(eventType, true, true);
	m_Command = Command;
}
#endif

}	// UI
}
