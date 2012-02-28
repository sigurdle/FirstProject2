#pragma once

#include "../LFC/Variant.h"

namespace System
{

class CControl;
class CXMLData;
class CControlsHandler;

class IControlsWindow;

class CControlEventHandler
{
public:
	virtual void OnControlValueChanged(/*CControl* pControl*/) = 0;
};

class IControlSite : public CControlEventHandler
{
public:
	virtual IControlsWindow* GetControlWindow() = 0;
	virtual ErrorCode __stdcall Redraw() = 0;
};

class
IControlsWindow : public UI::Control
{
public:
	CControlsHandler* m_pControlsHandler;
	Array<CXMLData*> m_attributes;

	virtual int GetControlsCount() = 0;
	virtual CControl* GetControlByIndex(int index) = 0;

	virtual void AddControl(CControl* pControl) = 0;
	virtual CControl* GetControl(System::StringW* name) = 0;
	virtual void AddData(CXMLData* pData) = 0;
	virtual CXMLData* GetData(System::StringW* name) = 0;
	virtual void Redraw() = 0;

	virtual void OnDataValueChanged(CXMLData* pData) = 0;
};

class CXMLData
{
public:
	CXMLData(System::StringW* name, System::StringW* defaultv)
	{
		m_name = name;
		m_default = defaultv;

		m_controlWindow = NULL;

		m_reentrancy = 0;
	}

	System::StringW* m_name;
	System::StringW* m_default;
	int m_reentrancy;
	IControlsWindow* m_controlWindow;

	Array<CControl*> m_controls;

	//virtual void InitValue(BSTR value) = 0;
	virtual void SetValue(System::StringW* value) = 0;
	virtual System::StringW* GetValueAsString() = 0;

//	CComBSTR GetDataValue(ILDOMElement* element);
};

class CXMLStringData : public CXMLData
{
protected:
	System::StringW* m_value;

public:
	CXMLStringData(System::StringW* name, System::StringW* defaultv) : CXMLData(name, defaultv)
	{
	}

//	virtual void InitValue(BSTR value);
	virtual void SetValue(System::StringW* value);
	virtual System::StringW* GetValueAsString();
};

class CSVGNumberListData : public CXMLData
{
public:
	System::StringW* m_value;
	Array<double> m_numberList;

	CSVGNumberListData(System::StringW* name, System::StringW* defaultv) : CXMLData(name, defaultv)
	{
	}

//	virtual void InitValue(BSTR value);
	virtual void SetValue(System::StringW* value);
	virtual System::StringW* GetValueAsString();
};

class CDataConnection
{
public:
	System::StringW* m_propertyName;
	CXMLData* m_pData;
};

class CControl
{
public:
	bool m_bVisible : 1;
	bool m_bEnabled : 1;
	System::StringW* m_name;
//	StringW m_value;

	int m_height;

	IControlSite* m_pSite;

	CControl(System::StringW* name)
	{
//		m_pData = NULL;
//		m_bVisible = true;
		m_bEnabled = true;

		m_name = name;

		m_height = 18;

		m_pSite = NULL;
	}

	virtual ~CControl()
	{
	}

	IControlSite* GetSite()
	{
		return m_pSite;
	}

	Array<CDataConnection*> m_dataConnections;

	void ConnectData(CXMLData* pData, System::StringW* propertyName = NULL)
	{
		CDataConnection* pDataConnection = new CDataConnection;
		pDataConnection->m_pData = pData;
		pDataConnection->m_propertyName = propertyName;

		m_dataConnections.Add(pDataConnection);

		pData->m_controls.Add(this);
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect) = 0;
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect) = 0;
	virtual void Deactivate() = 0;
	virtual void DoDrag(LDraw::PointI point, LDraw::BBoxi box)
	{
	}

	System::StringW* GetName()
	{
		return m_name;
	}

	virtual System::Variant GetProperty(System::StringW* name)
	{
		return System::Variant();
	}

	virtual void SetProperty(System::StringW* name, System::Variant value)
	{
	}

	virtual void OnDataValueChanged(CXMLData* pData)
	{
	// default action
		for (int i = 0; i < m_dataConnections.GetSize(); i++)
		{
			if (m_dataConnections[i]->m_pData == pData)
			{
				System::StringW* value = pData->GetValueAsString();
				SetProperty(m_dataConnections[i]->m_propertyName, value);
			}
		}
	}

	void SetVisible(bool bVisible)
	{
		m_bVisible = bVisible;
		m_pSite->Redraw();
	}

	void SetEnabled(bool bEnabled)
	{
		m_bEnabled = bEnabled;
		m_pSite->Redraw();
	}
};

class CEditBox :
	public CControl
//	public CMessageMap
{
public:
	CEditBox(System::StringW* name) : CControl(name)//, m_wndEdit(NULL, this, 1)
	{
	//	m_hWndEdit = NULL;
	}

	System::StringW* m_valueAsString;

	void EndEdit();

	//UI::Control* m_hWndEdit;
	UI::Control * m_wndEdit;

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);

	/*
BEGIN_MSG_MAP(CEditBox)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
END_MSG_MAP()
*/

//	LRESULT OnEditKeydown(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
};

class CControlAnimateMotionRotate :
	public CControl,
	public CControlEventHandler
{
public:
	int m_angleType;
	double m_valueInSpecifiedUnits;

	CEditBox m_editBox;

	CControlAnimateMotionRotate(System::StringW* name) : CControl(name), m_editBox(NULL)
	{
#if 0
		m_editBox.m_pSite = this;
#endif
		m_angleType = Web::SVG_ANGLETYPE_UNKNOWN;
	}

public:
	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);

	virtual void OnControlValueChanged()
	{
		m_pSite->OnControlValueChanged();
	}
};

class CMiniControlSite :
	public IControlSite	// CControlEventHandler
{
public:
	CMiniControlSite()
	{
		m_pOwnerControl = NULL;
		m_pControl = NULL;
	}

	CControl* m_pControl;
	CControl* m_pOwnerControl;

	virtual IControlsWindow* GetControlWindow()
	{
		return m_pOwnerControl->m_pSite->GetControlWindow();
	}

	virtual ErrorCode __stdcall Redraw()
	{
		m_pOwnerControl->m_pSite->Redraw();
		return Success;
	}

	virtual void OnControlValueChanged()
	{
		/*
		for (int i = 0; i < m_pControl->m_dataConnections.GetSize(); i++)
		{
			CDataConnection* pDataConnection = m_pControl->m_dataConnections[i];

			StringW value = m_pControl->GetProperty(pDataConnection->m_propertyName);
			pDataConnection->m_pData->SetValue(value);
		}

		if (m_pContainer->m_pControlsHandler)
		{
			m_pContainer->m_pControlsHandler->OnUIValueChanged(m_pControl);
		}

	//	m_pContainer->OnControlValueChanged(pControl);
	*/
		m_pOwnerControl->m_pSite->OnControlValueChanged();
	}
};

class CControlLength :
	public CControl
//	public CControlEventHandler
{
public:
	Web::SVGLengthType m_lengthType;
	double m_valueInSpecifiedUnits;

	CMiniControlSite m_editBoxSite;
	CEditBox* m_editBox;

	CControlLength(System::StringW* name) : CControl(name)
	{
		m_editBox = new CEditBox(NULL);
		m_editBoxSite.m_pControl = m_editBox;
		m_editBoxSite.m_pControl->m_pSite = &m_editBoxSite;//m_editBox.m_pEventHandler = this;
		m_editBoxSite.m_pOwnerControl = this;

		m_lengthType = Web::SVG_LENGTHTYPE_UNKNOWN;
	}

public:
	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);

	/*
	virtual void OnControlValueChanged()
	{
		m_pSite->OnControlValueChanged();
	}
	*/
};

class CXMLControlNumber :
	public CControl
	//public CMessageMap
{
public:
	System::StringW* m_value;

	CXMLControlNumber(System::StringW* name) : CControl(name)//, m_wndEdit(NULL, this, 1)
	{
		m_hWndEdit = NULL;
	}

	UI::Control* m_hWndEdit;
	//CContainedWindow m_wndEdit;

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();

	virtual void SetStringValue(System::StringW* bstr)
	{
		m_value = bstr;
	}

	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);

	void EndEdit();

	/*
BEGIN_MSG_MAP(CXMLControlNumber)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
END_MSG_MAP()
*/

	void OnEditKeydown();
};

class CXMLControlString :
	public CControl
	//public CMessageMap
{
public:
	System::StringW* m_value;

	CXMLControlString(System::StringW* name) : CControl(name)//, m_wndEdit(NULL, this, 1)
	{
		m_hWndEdit = NULL;
	}

	UI::Control* m_hWndEdit;
	//CContainedWindow m_wndEdit;

	void EndEdit();

	/*
BEGIN_MSG_MAP(CXMLControlString)
	ALT_MSG_MAP(1)
		MESSAGE_HANDLER(WM_KEYDOWN, OnEditKeydown)
END_MSG_MAP()
*/

	void OnEditKeydown();

public:
	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);
};

class CXMLControlCheckbox : public CControl
{
public:
	int m_value;

	CXMLControlCheckbox(System::StringW* name) : CControl(name)
	{
		m_value = 0;
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void DoDrag(LDraw::PointI point, LDraw::BBoxi box);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);
};

class CXMLControlButton : public CControl
{
public:
	CXMLControlButton(System::StringW* name) : CControl(name)
	{
	}

#if 0
	virtual void Draw(HDC hDC, LDraw::BBoxi rect)
	{
		CDCHandle dc(hDC);

		dc.Draw3dRect(&rect, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
	}

	virtual BOOL Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect)
	{
		m_pSite->OnControlValueChanged();	// Do in EndDrag?
		return FALSE;
	}

	virtual void DoDrag(LDraw::PointI point, LDraw::BBoxi box)
	{
	}
	virtual void Deactivate()
	{
	}
#endif
	/*
	virtual Variant GetProperty(BSTR name);
	virtual ErrorCode SetProperty(BSTR name, Variant value);
	*/
};

class CXMLControlSlider : public CControl
{
public:
	double m_value;

	double m_minValue;
	double m_maxValue;

	CXMLControlSlider(System::StringW* name, double minValue, double maxValue) : CControl(name)
	{
		m_value = 0;
		m_minValue = minValue;
		m_maxValue = maxValue;
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void DoDrag(LDraw::PointI point, LDraw::BBoxi box);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);
};

class CXMLControlPopup : public CControl
{
public:
	System::StringW* m_value;

	CXMLControlPopup(System::StringW* name, System::StringW* enums) : CControl(name)
	{
		if (enums)
		{
			SetEnumString(enums);
		}
	}

	Array<System::StringW*> m_enumStrings;

	void SetEnumString(System::StringW* enums)
	{
		const WCHAR* p = enums->c_str();
		WCHAR v[256];
		int n = 0;

		while (*p)
		{
			if (*p == L'|')
			{
				if (n > 0)
				{
					m_enumStrings.Add(new System::StringW(string_copy(v)));
					n = 0;
				}

				p++;
			}

			while (iswspace(*p)) p++;
			if (*p == 0) break;

			v[n++] = (TCHAR)*p++;
			v[n] = 0;	// null-terminate
		}

		if (n > 0) m_enumStrings.Add(new System::StringW(string_copy(v)));
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();

	/*
	virtual void OnDataValueChanged()
	{
	}

	virtual void SetValue(BSTR value)
	{
		m_value = value;
		m_controlWindow->OnControlValueChanged(this);
	}
	*/

	virtual System::Variant GetProperty(System::StringW* name)
	{
		if (name == NULL)
			return m_value;
		else if (!wcscmp(name->c_str(), L"count"))
			return System::Variant(long(m_enumStrings.GetSize()));
		else
			return System::Variant();
	}

	virtual void SetProperty(System::StringW* name, System::Variant value)
	{
		if (name == NULL)
		{
			m_value = value;

			m_pSite->OnControlValueChanged();

			m_pSite->Redraw();	// TODO remove

			return;
		}

		ASSERT(0);
		throw -1;
	}
};

class CXMLControlColor : public CControl
{
public:
	CXMLControlColor(System::StringW* name) : CControl(name)
	{
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect)
	{
		//CDCHandle dc(hDC);

		/*
		LDraw::BBoxi rc = rect;

		dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
		rc.InflateRect(-1,-1);

		dc.Draw3dRect(&rc, GetSysColor(COLOR_3DLIGHT), GetSysColor(COLOR_3DSHADOW));
		rc.InflateRect(-1,-1);

		LDraw::BBoxi trect = rc;
		trect.right -= 20;

		dc.Draw3dRect(trect.right+1, trect.top+2, 2, trect.Height()-4, GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));

		LDraw::PointI pt[3] =
		{
			trect.right+6,		trect.top+5,
			trect.right+6+10,	trect.top+5,
			trect.right+6+5,	trect.top+5+5
		};

		HPEN hOldPen = dc.SelectPen((HPEN)GetStockObject(NULL_PEN));
		HBRUSH hOldBrush = dc.SelectBrush((HBRUSH)GetStockObject(BLACK_BRUSH));

		dc.Polygon(pt, 3);

		dc.SelectPen(hOldPen);
		dc.SelectBrush(hOldBrush);

		if (m_value.length())
		{
			dc.DrawText(m_value, m_value.length(), &trect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
		}
		*/
	}

	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect)
	{
		/*
		HMENU hMenu;
		hMenu = CreatePopupMenu();

		for (int i = 0; i < m_enumStrings.GetSize(); i++)
		{
			UINT nFlags = MF_STRING;
			if (m_value.length() && !wcscmp(m_value, m_enumStrings[i])) nFlags |= MF_CHECKED;

			AppendMenu(hMenu, nFlags, i+1, m_enumStrings[i]);
		}

		CPoint point(rect.left, rect.bottom);
		::ClientToScreen(hParent, &point);

		UINT nID = ::TrackPopupMenu(hMenu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_LEFTBUTTON, point.x, point.y, 0, hParent, NULL);
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------++++++++-+.+.++.
																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																
																																																th() == 0 || wcscmp(m_value, m_enumStrings[nID-1]))
			{
				::InvalidateRect(hParent, &rect, TRUE);	// TODO, do this in SetValue()
				SetValue(m_enumStrings[nID-1]);
			}
		}
		*/

		return false;
	}

	virtual void Deactivate()
	{
	}
};

//#include "../LXUI/Color_Conversion.h"

class CXMLControlHueRotate : public CControl
{
public:
	double m_value;

	CXMLControlHueRotate(System::StringW* name) : CControl(name)
	{
		m_height = 60;
		m_value = 0;
	}

	double GetAngle(LDraw::PointI point, LDraw::BBoxi box);

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void DoDrag(LDraw::PointI point, LDraw::BBoxi box);
	virtual void Deactivate();
	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);
};

class CXMLControlColorMatrix : public CControl
{
public:

	Web::ISVGNumberList* m_numberList;

	CXMLControlColorMatrix(System::StringW* name) : CControl(name)
	{
		m_height = 60;
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();
};

class CXMLControlDistantLight : public CControl
{
protected:

	LDraw::Color
		m_clrDiffuse,           // Ball diffusion color (self color)
		m_clrAmbient,           // Ambient (background) color
		m_clrLight,             // Color of light
		m_clrBackgroundStart,   // Background color gradient start
		m_clrBackgroundEnd;     // Background color gradient end

	double m_dSpecularExponent;    // Specularity effect intensity
	double m_dSensitivity;
	bool m_bFrontVector;

public:
	LDraw::vector3d m_dVec;
	LDraw::PointD m_iLastMouse;

	double m_azimuth;
	double m_elevation;

	CXMLControlDistantLight(System::StringW* name) : CControl(name)
	{
		m_height = 60;
	//	m_value = 0;

		m_dVec[0] = -0.52;
		m_dVec[1] = -0.66;
		m_dVec[2] = 0.5;

		m_dSensitivity = 20.0;
		m_bFrontVector = false;
	}

	LDraw::Color CalcLight(LDraw::vector3d& dVec, double dx, double dy, double dz);
	void RotateByXandY (double XRot, double YRot);

	double GetAngle(LDraw::PointI point, LDraw::BBoxi box);

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void DoDrag(LDraw::PointI point, LDraw::BBoxi box);
	virtual void Deactivate();

	virtual System::Variant GetProperty(System::StringW* name);
	virtual void SetProperty(System::StringW* name, System::Variant value);
};

class CXMLControlColorCurve : public CControl
{
public:
	CXMLControlColorCurve(System::StringW* name) : CControl(name)
	{
		m_height = 60;
	}

	virtual void Draw(MSWindows::HDC hDC, LDraw::BBoxi rect);
	virtual bool Activate(UI::Control* hParent, LDraw::PointI point, LDraw::BBoxi rect);
	virtual void Deactivate();
};

class CControlsHandler
{
public:
	IControlsWindow* m_controlWindow;

	CControlsHandler()
	{
		m_controlWindow = NULL;
	}

	virtual void Setup() = 0;
	virtual void OnDataValueChanged(CXMLData* pData) = 0;
	virtual void OnUIValueChanged(CControl* pControl) = 0;
};


/*
#define XMLTYPE_URI()	XMLType_Uri
#define XMLTYPE_COLOR()	XMLType_Color
#define XMLTYPE_LENGTH()	XMLType_Length
#define XMLTYPE_STRING()	XMLType_String
#define XMLTYPE_ENUM() XMLType_Enum//, enums, 0
#define XMLTYPE_ENUM_IMAGE(enums, nResource) XMLType_Enum, enums, nResource
#define XMLTYPE_NUMBER(minValue, maxValue, scale) XMLType_Number//, NULL, 0, minValue, maxValue, scale
#define XMLTYPE_HUEROTATE() XMLType_HueRotate
*/

}
