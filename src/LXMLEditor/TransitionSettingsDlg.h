#ifndef __TRANSITIONSETTINGSDLG_H_
#define __TRANSITIONSETTINGSDLG_H_

#ifndef LXMLEDITEXT
#define LXMLEDITEXT DECLSPEC_DLLEXPORT
#endif

namespace System
{
namespace LXmlEdit
{
class CSMILTransition;

class CTransitionDirectionUI;
class CTransitionProgressionUI;

class LXMLEDITEXT CTransitionSettingsDlg : public UI::Control
	//public CAxDialogImpl<CTransitionSettingsDlg>
//	public IDispEventImpl<1, CTransitionSettingsDlg, &DIID__ITransitionDirectionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<2, CTransitionSettingsDlg, &DIID__ITransitionProgressionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>,
//	public IDispEventImpl<3, CTransitionSettingsDlg, &DIID__ITransitionProgressionUIEvents, &LIBID_LXMLEDITORLib, 1, 0>
{
public:
	CTransitionSettingsDlg(CSMILTransition* pMapping);

	~CTransitionSettingsDlg()
	{
	}

	void Init();

	UI::TextEdit* m_wndHorzRepeat;
	UI::TextEdit* m_wndVertRepeat;

//	_bstr_t m_type;
//	_bstr_t m_subtype;
	CSMILTransition* m_pMapping;
	long m_horzRepeat;
	long m_vertRepeat;
	double m_startProgress;
	double m_endProgress;

	CTransitionDirectionUI* m_transitionUI;
	CTransitionProgressionUI* m_startProgressUI;
	CTransitionProgressionUI* m_endProgressUI;
	UI::TextString* m_frTextString;

	bool m_reverse;

#if 0
	enum { IDD = IDD_TRANSITIONSETTINGSDLG };

BEGIN_SINK_MAP(CTransitionSettingsDlg)
//   SINK_ENTRY_EX(1, DIID__ITransitionDirectionUIEvents, /*dispid*/1, OnChangedArrowFlags)
  // SINK_ENTRY_EX(2, DIID__ITransitionProgressionUIEvents, /*dispid*/1, OnChangedStartProgress)
   //SINK_ENTRY_EX(3, DIID__ITransitionProgressionUIEvents, /*dispid*/1, OnChangedEndProgress)
END_SINK_MAP()
#endif

	void OnChangedArrowFlags(long arrowFlags);
	void OnChangedStartProgress(double progress);
	void OnChangedEndProgress(double progress);

	virtual void handleEvent(System::Event* evt);

	long OnForwardReverse();

//	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//	LRESULT OnDestroy();

	long OnHorzRepeatKeydown();
	long OnVertRepeatKeydown();

//	LRESULT OnOK(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//	LRESULT OnCancel(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
};

}	// LXmlEdit
}

#endif //__TRANSITIONSETTINGSDLG_H_
