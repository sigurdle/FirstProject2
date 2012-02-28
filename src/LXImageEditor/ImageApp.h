#ifndef __IMAGEAPP_H_
#define __IMAGEAPP_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace ImageEdit
{

class CPaintMethod
{
public:
	System::StringW* m_name;
	IPaintMethod* m_method;
};

class CImageView;

class CImageTool
{
public:
	UINT m_nID;
	IImageTool* m_pTool;
};

class CBrushTip
{
public:
	int m_refcount;

	CTOR CBrushTip()
	{
		m_refcount = NULL;
	}

	virtual LDraw::Bitmap* GetBitmap() = 0;
};

class CCircularBrushTip : public CBrushTip
{
public:
	CTOR CCircularBrushTip()
	{
	}

	virtual LDraw::Bitmap* GetBitmap()
	{
		LDraw::Bitmap* pBitmap = new LDraw::Bitmap(255, 255, LDraw::PixelFormat_t::RGBAP_32);

		uint8 values[256];
		{
			for (int i = 0; i < 256; i++)
			{
				values[i] = i;
			}
		}

		LDraw::BitmapData data;
		pBitmap->LockBits(
			&LDraw::RectI(0, 0, pBitmap->GetWidth(), pBitmap->GetHeight()),
			LDraw::ImageLockModeWrite,
			/*PixelFormat32bppARGB,*/ &data);

		int radius = (data.Width-1)/2;

		for (int y2 = -radius; y2 <= radius; y2++)
		{
			int x2 = -radius;

			LDraw::PixelRGBAP_32* dest = (LDraw::PixelRGBAP_32*)((uint8*)data.Scan0 + data.Stride*(y2+radius)+(x2+radius)*4);

			for (; x2 <= radius; x2++)
			{
				int	len = (int)(sqrt((double)y2*y2+x2*x2)+0.5);

				uint8	alpha = 0;

				if (len <= radius)
				{
					alpha = 255-/*pCurve->m_data.*/values[len*2];
				}

				dest->a = alpha;
				dest->r = 0;
				dest->g = 0;
				dest->b = 0;

				dest++;
			}
		}

		pBitmap->UnlockBits(&data);

		return pBitmap;
	}
};

class CCustomBrushTip : public CBrushTip
{
protected:
	LDraw::Bitmap* m_pBitmap;

public:
	CTOR CCustomBrushTip()
	{
		m_pBitmap = NULL;
	}

	System::StringW* m_filename;

	LDraw::Bitmap* GetBitmap()
	{
		if (m_pBitmap == NULL)
		{
			ASSERT(0);
#if 0
			m_pBitmap = new LDraw::Bitmap(m_filename.c_str());
#endif
		}

		return m_pBitmap;
	}
};

class CImageBrush
{
public:
	CTOR CImageBrush()
	{
		m_pBrushTip = NULL;
		m_pMethod = NULL;
	}

	long m_brushSize;
	CBrushTip* m_pBrushTip;
	CPaintMethod* m_pMethod;
};

class CImageApp
//	public ILXImageApp,
//	public ProcessTargetCommands,
//	public CUIActiveManagerImpl
{
public:
	CTOR CImageApp();

#if 0
	CComPtr<ILXFrameworkFrame> m_frame;
#endif
//	CComPtr<IUIManager> m_uiManager;

	vector<CPaintMethod*> m_paintMethods;
	CPaintMethod* m_pActivePaintMethod;
	long m_brushSize;

	vector<CBrushTip*> m_customBrushTips;
	CBrushTip* m_pActiveBrushTip;

	vector<CImageBrush*> m_brushes;

//	int m_activeTool;
	CImageTool* m_pActiveTool;

	vector<CImageTool*> m_tools;
	CImageTool* FindToolById(UINT nID)
	{
		for (int i = 0; i < m_tools.GetSize(); i++)
		{
			if (m_tools[i]->m_nID == nID)
				return m_tools[i];
		}
		return NULL;
	}

	void OnFileOpen(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);

	void OnTool(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled);
//	void OnToolUpdate(long iid, IUICmdUpdate* pCmdUI);

// IImageApp
public:
// ICommandTarget
//	STDMETHOD(OnCmdMsg)(long nID, long nCode, IUICmdUpdate * pCmdUI, WINBOOL * bHandled);

//	STDMETHOD(OnCreateFrame)();
//	STDMETHOD(CreateDlg)(UINT nID, IUIDlg* *pVal);

	/*
	STDMETHOD(SetFrame)(IWebEditorFrame* newVal)
	{
		m_frame = newVal;
		return S_OK;
	}
   STDMETHOD(GetFrame)(IWebEditorFrame* *pVal)
	{
		*pVal = m_frame;
		(*pVal)->AddRef();
		return S_OK;
	}

   STDMETHOD(SetUIManager)(IUIManager* newVal);
   STDMETHOD(GetUIManager)(IUIManager* *pVal)
	{
		*pVal = m_uiManager;
		(*pVal)->AddRef();
		return S_OK;
	}
	*/
};

}
}

#endif //__IMAGEAPP_H_
