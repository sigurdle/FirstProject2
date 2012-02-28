#if 0	// Removed ?? Or maybe just figure out a better place to put some of this

#ifndef __EDOC_H_
#define __EDOC_H_

/*

  // TODO rename this file to LXFramework'Something'.h

 #include "LXFramework/LXFramework.h"
*/

//struct __declspec(uuid("75D9BCBC-1431-4eeb-929A-15B149AAAFA3")) IEFrame;

struct __declspec(uuid("9c835ce0-5da5-40be-912b-df7f4c72ce0a"))
/* dual interface */ IUICommand;
struct __declspec(uuid("7db87ae9-431d-49df-bcd5-895b4c022811"))
/* interface */ IUIManager;
struct __declspec(uuid("16717969-958b-4c86-9a46-37f345d149c0"))
/* dual interface */ IUICommandGroup;

struct __declspec(uuid("9c835ce0-5da5-40be-912b-df7f4c72ce0a"))
IUICommand : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_ID (
        long * pVal ) = 0;
    virtual HRESULT __stdcall get_name (
        BSTR * pVal ) = 0;
    virtual HRESULT __stdcall get_bitmap (
        unsigned long * pVal ) = 0;
    virtual HRESULT __stdcall put_bitmap (
        unsigned long pVal ) = 0;
    virtual HRESULT __stdcall get_bitmapIndex (
        long * pVal ) = 0;
    virtual HRESULT __stdcall put_bitmapIndex (
        long pVal ) = 0;
    virtual HRESULT __stdcall get_type (
        unsigned long * pVal ) = 0;
    virtual HRESULT __stdcall put_type (
        unsigned long pVal ) = 0;
    virtual HRESULT __stdcall AddString (
        BSTR string ) = 0;
    virtual HRESULT __stdcall GetStringCount (
        long * pVal ) = 0;
    virtual HRESULT __stdcall GetString (
        long index,
        BSTR * pVal ) = 0;
    virtual HRESULT __stdcall get_itemWidth (
        long * pVal ) = 0;
    virtual HRESULT __stdcall put_itemWidth (
        long pVal ) = 0;
    virtual HRESULT __stdcall get_windowStyle (
        unsigned long * pVal ) = 0;
    virtual HRESULT __stdcall put_windowStyle (
        unsigned long pVal ) = 0;
    virtual HRESULT __stdcall get_windowClassname (
        BSTR * pVal ) = 0;
    virtual HRESULT __stdcall put_windowClassname (
        BSTR pVal ) = 0;
};

struct __declspec(uuid("D666A097-E521-4974-B8DB-ED823CFF15A0"))
IUIManagerSite : IUnknown
{
	//
	// Raw methods provided by interface
	//
	
//	virtual HRESULT __stdcall CreateDlg(UINT nID, IUIDlg* *pVal ) = 0;
};

struct __declspec(uuid("7db87ae9-431d-49df-bcd5-895b4c022811"))
IUIManager : IUnknown
{
	//
	// Raw methods provided by interface
	//
	
	virtual HRESULT __stdcall get_CommandGroupsCount (long * pVal ) = 0;
	virtual HRESULT __stdcall get_DlgCount (long * pVal ) = 0;
	virtual HRESULT __stdcall get_DesignMode (BOOL * pVal ) = 0;
	virtual HRESULT __stdcall put_DesignMode (BOOL pVal ) = 0;
	virtual HRESULT __stdcall CreateCommandGroup (BSTR name,struct IUICommandGroup * * pResult ) = 0;
	virtual HRESULT __stdcall AppendCommandGroup (struct IUICommandGroup * pCmdGroup ) = 0;
	virtual HRESULT __stdcall AddCommandID (long guid,BSTR name,struct IUICommandGroup * pGroup,struct IUICommand * * pResult ) = 0;
	virtual HRESULT __stdcall GetCommandGroup (long index,struct IUICommandGroup * * pCmdGroup ) = 0;
	virtual HRESULT __stdcall FindCommand (long ID,struct IUICommand * * pResult ) = 0;
	virtual HRESULT __stdcall AddToolbarCommands (HINSTANCE hInst, long nResourceId ) = 0;
	virtual HRESULT __stdcall Load (BSTR pathName ) = 0;
	virtual HRESULT __stdcall Save (IStream* stream) = 0;
		/*
		virtual HRESULT __stdcall RegisterDlgSheet (
		BSTR name,
		unsigned long flags,
		struct IUIDlgClass * * pVal ) = 0;
	*/
	virtual HRESULT __stdcall CreateMenuDlg (struct IUIMenuDlg * * pVal ) = 0;
};

struct __declspec(uuid("16717969-958b-4c86-9a46-37f345d149c0"))
IUICommandGroup : IDispatch
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall get_name (
        BSTR * pVal ) = 0;
    virtual HRESULT __stdcall get_length (
        long * pVal ) = 0;
    virtual HRESULT __stdcall item (
        long index,
        struct IUICommand * * pResult ) = 0;
    virtual HRESULT __stdcall append (
        struct IUICommand * pCmd ) = 0;
};

struct __declspec(uuid("DAD28B4E-8D1E-4f10-9F2A-5A0D45E298D3"))
ILXAddin : IUnknown
{
    virtual HRESULT __stdcall GetSite(ILXAddinSite* *pVal) = 0;
    virtual HRESULT __stdcall SetSite(ILXAddinSite* newVal) = 0;
    virtual HRESULT __stdcall Show(ILXUIElement* element) = 0;
//    virtual HRESULT __stdcall SetFrame(ILXFrameworkFrame* newVal) = 0;
//    virtual HRESULT __stdcall GetFrame(ILXFrameworkFrame* *pVal) = 0;
//    virtual HRESULT __stdcall SetUIManager(IUIManager* newVal) = 0;
//    virtual HRESULT __stdcall GetUIManager(IUIManager* *pVal) = 0;
//    virtual HRESULT __stdcall OnCreateFrame() = 0;
//    virtual HRESULT __stdcall OnCreateDlg(UINT nID, IUIDlg* *pVal) = 0;
//    virtual HRESULT __stdcall BindToObjectMoniker(IMoniker* mk, IBindCtx* ctx, IUnknown* *pVal) = 0;
};

#if 0
struct __declspec(uuid("723C7B54-0DA7-456d-AF52-E71BDADD659E"))
IEDocumentSite : IUnknown
{
};
#endif

struct __declspec(uuid("4CF4CD08-B8A7-4eed-BD8B-49CE52F11458"))
ILInPlaceFrame : IOleWindow
{
    virtual HRESULT __stdcall SetStatusText(LPCOLESTR pszStatusText) = 0;
};

extern "C" const GUID __declspec(selectany) IID_IUICommand =
    {0x9c835ce0,0x5da5,0x40be,{0x91,0x2b,0xdf,0x7f,0x4c,0x72,0xce,0x0a}};
extern "C" const GUID __declspec(selectany) IID_IUIManager =
    {0x7db87ae9,0x431d,0x49df,{0xbc,0xd5,0x89,0x5b,0x4c,0x02,0x28,0x11}};
extern "C" const GUID __declspec(selectany) IID_IUICommandGroup =
    {0x16717969,0x958b,0x4c86,{0x9a,0x46,0x37,0xf3,0x45,0xd1,0x49,0xc0}};

#endif // __EDOC_H_

#endif
