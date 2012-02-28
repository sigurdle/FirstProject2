struct __declspec(uuid("95C9B8EF-F06A-47c0-84BC-B4DA647BEAFD"))
/* interface */ IUIActivatable;

struct __declspec(uuid("f4a86042-ed11-11d5-95f0-0002e3045703"))
IUIEventHandler : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall handleActivateObjectEvent (
        IUnknown * object,
        long * cookie ) = 0;
    virtual HRESULT __stdcall handleDeactivateObjectEvent (
        IUnknown * object,
        long cookie,
        BOOL * bAllow ) = 0;
};

struct __declspec(uuid("1bc5e2ec-5345-11d5-95f0-ed386645315a"))
IUIActiveManager : IUnknown
{
    //
    // Raw methods provided by interface
    //

    virtual HRESULT __stdcall ActivateObject (
        IUnknown * activatedBy,
        IUnknown * object ) = 0;
    virtual HRESULT __stdcall DeactivateObject (
        IUnknown * object ) = 0;
    virtual HRESULT __stdcall IsObjectActive (
        IUnknown * object ) = 0;
    virtual HRESULT __stdcall AddEventHandler (
        struct IUIEventHandler * handler ) = 0;
    virtual HRESULT __stdcall RemoveEventHandler (
        struct IUIEventHandler * handler ) = 0;

    virtual HRESULT __stdcall GetActiveObjects (
        GUID itype,
        IUnknown * * pobjects,
        long size,
        long * count ) = 0;
};

struct __declspec(uuid("95C9B8EF-F06A-47c0-84BC-B4DA647BEAFD"))
IUIActivatable : IUnknown
{
	virtual HRESULT __stdcall OnActivate(IUIActiveManager* uiManager) = 0;
	virtual HRESULT __stdcall OnDeactivate(IUIActiveManager* uiManager) = 0;
};
