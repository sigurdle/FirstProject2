#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

void ManagedRetainedRenderContext::Pop()
{
	if (m_locallevel == 0)
	{
		raise(Exception("Popping past top"));
	}

	--m_locallevel;
	m_p->Pop();
}

}	// Gui
}	// System
