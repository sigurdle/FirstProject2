#include "stdafx.h"
#include "LXMLEditor.h"
#include "TransitionSettingsDlg.h"

#include "Transition.h"

#include "TransitionDirectionUI.h"
#include "TransitionProgressionUI.h"

namespace System
{
namespace UI
{

void SetDlgItemInt(TextEdit* pEdit, long number)
{
	WCHAR buf[64];
	swprintf(buf, L"%ld", number);
	pEdit->set_Text(new System::StringW(string_copy(buf)));
}

}

namespace LXmlEdit
{

CTransitionSettingsDlg::CTransitionSettingsDlg(CSMILTransition* pMapping)
{
	LDraw::Bitmap* bitmap[2];

	{
		Imaging::BitmapLoader loader;

		loader.Load(new System::StringA(string_copy("C:\\transition_bitmap_a.png")));
		bitmap[0] = loader.GetBitmap();//new LDraw::Bitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAPA));

		loader.Load(new System::StringA(string_copy("C:\\transition_bitmap_b.png")));
		bitmap[1] = loader.GetBitmap();//new LDraw::Bitmap(g_hInstance, MAKEINTRESOURCE(IDB_BITMAPB));
	}

	m_pMapping = pMapping;

	m_horzRepeat = 1;
	m_vertRepeat = 1;

	m_startProgress = 0;
	m_endProgress = 1;

	m_reverse = 0;

	UI::DockPanel* panel = new UI::DockPanel;

	m_wndHorzRepeat = new UI::TextEdit();//.SubclassWindow(GetDlgItem(IDC_SMILTRANSITION_HORZREPEAT));
	panel->AddRChild(m_wndHorzRepeat);

	m_wndVertRepeat = new UI::TextEdit();//.SubclassWindow(GetDlgItem(IDC_SMILTRANSITION_VERTREPEAT));
	panel->AddRChild(m_wndVertRepeat);

	m_startProgressUI = new CTransitionProgressionUI;
	m_startProgressUI->set_Width(new UI::Length(80));
	m_startProgressUI->set_Height(new UI::Length(80));
	m_startProgressUI->m_bitmap[0] = bitmap[0];
	m_startProgressUI->m_bitmap[1] = bitmap[1];
	panel->AddRChild(m_startProgressUI);

	m_endProgressUI = new CTransitionProgressionUI;
	m_endProgressUI->set_Width(new UI::Length(80));
	m_endProgressUI->set_Height(new UI::Length(80));
	m_endProgressUI->m_bitmap[0] = bitmap[0];
	m_endProgressUI->m_bitmap[1] = bitmap[1];
	panel->AddRChild(m_endProgressUI);

	m_transitionUI = new CTransitionDirectionUI;
	m_transitionUI->set_Width(new UI::Length(80));
	m_transitionUI->set_Height(new UI::Length(80));
	m_transitionUI->m_bitmap[0] = bitmap[0];
	m_transitionUI->m_bitmap[1] = bitmap[1];
	panel->AddRChild(m_transitionUI);

	m_frTextString = new UI::TextString();
	panel->AddRChild(m_frTextString);

	set_VisualTree(panel);
}

void CTransitionSettingsDlg::Init()
{
#if 0
	GetDlgControl(IDC_SMILTRANSITION_DIRECTIONUI, IID_ITransitionDirectionUI, (void**)&m_transitionUI);

	GetDlgControl(IDC_SMILTRANSITION_STARTPROGRESSUI, IID_ITransitionProgressionUI, (void**)&m_startProgressUI);
	GetDlgControl(IDC_SMILTRANSITION_ENDPROGRESSUI, IID_ITransitionProgressionUI, (void**)&m_endProgressUI);
#endif

	UI::SetDlgItemInt(m_wndHorzRepeat, m_horzRepeat);

	UI::SetDlgItemInt(m_wndVertRepeat, m_vertRepeat);

	m_transitionUI->set_bitCorners(m_pMapping->m_pTransition->m_bitCorners);
	m_transitionUI->set_flags(m_pMapping->m_pTransition->m_flags);
	m_transitionUI->set_arrowFlags(m_pMapping->m_arrowFlags);
	m_transitionUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
	m_transitionUI->set_reverse(m_reverse);
	
	m_startProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
	m_startProgressUI->set_reverse(m_reverse);
	m_startProgressUI->set_progress(m_startProgress);

	m_endProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
	m_endProgressUI->set_reverse(m_reverse);
	m_endProgressUI->set_progress(m_endProgress);

	m_frTextString->set_TextContent(m_reverse? WSTR("R"): WSTR("F"));

//	IDispEventImpl<1, CTransitionSettingsDlg, &DIID__ITransitionDirectionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_transitionUI);
//	IDispEventImpl<2, CTransitionSettingsDlg, &DIID__ITransitionProgressionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_startProgressUI);
//	IDispEventImpl<3, CTransitionSettingsDlg, &DIID__ITransitionProgressionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventAdvise(m_endProgressUI);
}

/*
LRESULT CTransitionSettingsDlg::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
//	IDispEventImpl<1, CTransitionSettingsDlg, &DIID__ITransitionDirectionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_transitionUI);
//	IDispEventImpl<2, CTransitionSettingsDlg, &DIID__ITransitionProgressionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_startProgressUI);
//	IDispEventImpl<3, CTransitionSettingsDlg, &DIID__ITransitionProgressionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>::DispEventUnadvise(m_endProgressUI);

	return 0;
}
*/

long CTransitionSettingsDlg::OnForwardReverse()
{
	m_reverse = !m_reverse;
//	SetDlgItemText(wID, m_reverse? "R": "F");
	m_frTextString->set_TextContent(m_reverse? WSTR("R"): WSTR("F"));

	m_transitionUI->set_reverse(m_reverse);
	m_startProgressUI->set_reverse(m_reverse);
	m_endProgressUI->set_reverse(m_reverse);

	return 0;
}

void CTransitionSettingsDlg::OnChangedStartProgress(double progress)
{
	m_startProgress = progress;
	if (m_endProgress < m_startProgress)
	{
		m_endProgress = m_startProgress;
		m_endProgressUI->set_progress(m_endProgress);
	}
}

void CTransitionSettingsDlg::OnChangedEndProgress(double progress)
{
	m_endProgress = progress;
	if (m_startProgress > m_endProgress)
	{
		m_startProgress = m_endProgress;
		m_startProgressUI->set_progress(m_startProgress);
	}
}

void CTransitionSettingsDlg::OnChangedArrowFlags(long arrowFlags)
{
// Change to the mapping that matches the arrowflags
	int i;
	for (i = 0; i < m_pMapping->m_pTransition->m_mapping.GetSize(); i++)
	{
		if (m_pMapping->m_pTransition->m_mapping[i]->m_arrowFlags == arrowFlags)
		{
			m_pMapping = m_pMapping->m_pTransition->m_mapping[i];
			break;
		}
	}
	ASSERT(i < m_pMapping->m_pTransition->m_mapping.GetSize());

	m_transitionUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
	m_startProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
	m_endProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
}

long CTransitionSettingsDlg::OnHorzRepeatKeydown()
{
	/*
	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
	*/
		m_horzRepeat = str2int(m_wndHorzRepeat->get_Text()->c_str());

		m_transitionUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
		m_startProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
		m_endProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);

		/*
		if (uMsg == WM_KEYDOWN)
			return 0;
			*/
	//}

	return 0;//m_wndHorzRepeat.DefWindowProc(uMsg, wParam, lParam);
}

long CTransitionSettingsDlg::OnVertRepeatKeydown()
{
	/*
	if ((uMsg == WM_KILLFOCUS) ||
		(uMsg == WM_KEYDOWN && wParam == VK_RETURN))
	{
	*/
		m_vertRepeat = str2int(m_wndVertRepeat->get_Text()->c_str());//GetDlgItemInt(IDC_SMILTRANSITION_VERTREPEAT);

		m_transitionUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
		m_startProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);
		m_endProgressUI->SetTransition(m_pMapping->m_type, m_pMapping->m_subtype, m_horzRepeat, m_vertRepeat, NULL, NULL);

		/*
		if (uMsg == WM_KEYDOWN)
			return 0;
			*/
	//}

	return 0;//m_wndVertRepeat.DefWindowProc(uMsg, wParam, lParam);
}

void CTransitionSettingsDlg::handleEvent(System::Event* evt)
{
	if (evt->get_eventPhase() != System::CAPTURING_PHASE)
	{
		if (evt->get_type() == WSTR("ArrowFlagsChanged"))
		{
			OnChangedArrowFlags(dynamic_cast<ArrowFlagsEvent*>(evt)->arrowFlags);
		}
	}
}

/*
LRESULT CTransitionSettingsDlg::OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}

LRESULT CTransitionSettingsDlg::OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
	EndDialog(wID);
	return 0;
}
*/

}	// LXmlEdit
}
