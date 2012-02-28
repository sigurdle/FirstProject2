#pragma once

#include "UIControls.h"

namespace System
{
namespace LXmlEdit
{

class CXMLControlsHandler : public CControlsHandler
{
public:
	CXMLControlsHandler()
	{
		m_bAnimation = false;
		m_reentrancy = 0;

		//m_controlWindow = controlWindow;
	}

	CEXMLViewGroup* m_viewGroup;
//	IControlsWindow* m_controlWindow;

	bool m_bAnimation;

	int m_reentrancy;

	void UpdateData(CXMLData* pData);

	virtual void Setup();
	virtual void OnUIValueChanged(CControl* pControl);
	virtual void OnDataValueChanged(CXMLData* pData);

	virtual ErrorCode SetPathNodeValue(System::StringW* path, System::StringW* value);
	virtual ErrorCode SetPathNodeValueIfNotExists(System::StringW* path, System::StringW* value);
	virtual ErrorCode GetPathNodeValue(System::StringW* path, System::StringW** pVal);
	virtual bool PathNodeExists(System::StringW* path);
};

}	// LXmlEdit
}
