#ifndef __IMAGEDOCUMENT_H_
#define __IMAGEDOCUMENT_H_

//#include "resource.h"       // main symbols

//#include "../LXFramework/WebDocumentImpl.h"

namespace System
{
namespace ImageEdit
{

class CImageLayerGroup;
class CGroupImageObject;

class ILayerEffect
{
public:
	virtual ErrorCode Filter(LDraw::Bitmap* inBitmap, LDraw::Bitmap* outBitmap) = 0;
};

class CDropShadow : public ILayerEffect
{
public:
	uint32 m_blendMode;
	LDraw::PixelRGBAP_32 m_argb;
	double m_angle;
	long m_distance;
	long m_size;

	ErrorCode Filter(LDraw::Bitmap* inBitmap, LDraw::Bitmap* outBitmap);
};

class CLayerEffect
{
public:
	ILayerEffect* m_pEffect;
};

class ImageEditorExt CImageDocument : public System::Object/* : 
	public ProcessTargetCommands,*/
{
public:
	CTOR CImageDocument();
	~CImageDocument();

//	int FinalConstruct();
//	void FinalRelease();

	System::StringA* m_activeToolString;
	IImageTool* m_pActiveTool;

	CImageLayerGroup* m_imageLayerGroup;

	long m_width;
	long m_height;

	long m_color[3];

	//ILXImageApp* m_app;

	LDraw::Bitmap* m_pBitmapSelection;
	CGroupImageObject* m_groupSelection;

	ErrorCode Load(System::StringW* filename);

#if 0

DECLARE_CMD_MAP(CImageDocument)
#endif

	void OnSelectAll(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
//	void OnSelectAllUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnSelectDeselect(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
//	void OnSelectDeselectUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnSelectInverse(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnSelectFeather(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnSelectExpand(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
	void OnSelectContract(int wNotifyCode, int wID, UI::Control * hWndCtl, bool& bHandled);
//	void OnSelectHasSelectionUpdate(long iid, IUICmdUpdate* pCmdUI);

// IImageDocument
public:
	CImageLayerGroup* GetImageLayerGroup();

#if 0
// IEDocument
	STDMETHOD(Activate)();
	STDMETHOD(get_undoManager)(/*[out, retval]*/ IUndoManager* *pVal);
	STDMETHOD(NewDocument)();
	STDMETHOD(CloseDocument)();
	STDMETHOD(LoadDocumentByteArray)(/*[in]*/ SAFEARRAY* dataArray, /*[out,retval]*/ VARIANT_BOOL* success);

#if 0
	STDMETHOD(ShowViews)(ILXFrameworkFrame* pFrame);
#endif


// IPersistFile
	STDMETHOD(Load)(/*[in]*/ LPCOLESTR pszFileName, /*[in]*/ DWORD dwMode);
	STDMETHOD(Save)(/*[unique][in]*/ LPCOLESTR pszFileName, /*[in]*/ WINBOOL fRemember)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(SaveCompleted)(/*[unique][in]*/ LPCOLESTR pszFileName)
	{
		return E_NOTIMPL;
	}
	STDMETHOD(GetCurFile)(/*[out]*/ LPOLESTR *ppszFileName)
	{
		return E_NOTIMPL;
	}

// IPersistMoniker

	STDMETHOD(IsDirty)( void);

	STDMETHOD(Load)(/* [in] */ WINBOOL fFullyAvailable, /* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc, /* [in] */ DWORD grfMode);
	STDMETHOD(Save)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pbc, /* [in] */ WINBOOL fRemember);
	STDMETHOD(SaveCompleted)(/* [in] */ IMoniker *pimkName, /* [in] */ LPBC pibc);
	STDMETHOD(GetCurMoniker)(/* [out] */ IMoniker **ppimkName);
#endif
};

}	// ImageEdit
}

#endif //__IMAGEDOCUMENT_H_
