#pragma once

//using namespace UI;

#include "resource.h"

#define LP2PEXT DECLSPEC_DLLIMPORT
#include "../LXChatter/GnutellaNetwork.h"
#include "../LXChatter/Gnutella2Network.h"
#include "../LXChatter/EDonkeyNetwork.h"

namespace System
{

class P2PFrame : public UI::CLXUIWindow
{
public:
	P2PFrame();

	UI::TextEdit* m_searchEdit;

	UI::ChildWindowContainer* pCanvas;

protected:
	virtual void handleEvent(System::Event* evt);
};

}
