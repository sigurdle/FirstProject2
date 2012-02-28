#include "stdafx.h"
#include "LXUI2.h"

namespace System
{
namespace UI
{

PreProcessInputEventArgs::PreProcessInputEventArgs()
{
	m_canceled = false;
}

void PreProcessInputEventArgs::Cancel()
{
	m_canceled = true;
}

bool PreProcessInputEventArgs::get_Canceled()
{
	return m_canceled;
}

//

InputManager* InputManager::s_Current = new InputManager;

InputManager::InputManager()
{
}

}	// UI
}
