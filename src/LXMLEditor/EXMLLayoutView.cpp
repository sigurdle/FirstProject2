#include "stdafx.h"
#include "LXMLEditor2.h"

#include "EXMLLayoutView.h"

#include "EElement.h"
#include "EXMLDocument.h"
#include "EXMLViewGroup.h"
#include "LXMLEditorApp.h"	// TODO remove
#include "EXMLViewGroup.h"
#include "SourceView.h"
#include "InsertTableDlg.h"
#include "WENavigatorDlg.h"

#include "SVGBehavior.h"

#include "WEUndoDeleteObjects.h"

//#include "..\LHTML\LHTML2.h"
#include "../LXML/cssunits.h"
//#include "..\LHTML\PElement.h"
//#include "..\LXUI\LXMLDocumentView.h"
//#include "..\LHTML\HTMContext.h"
//#include "..\LHTML\LBoxWindow.h"
//#include "..\LXUI\PBlockBox.h"

#include "../LSVG/SVGSVGElement.h"

//#include "../OleDataObject.h"

#include "ESelectedSVGPathElement.h"	// TODO remove

#include "LayoutViewOptionsDlg.h"

#include "SVGObjectsDlg.h"

//#pragma comment(lib, "../LHTML/Debug/LHTML.lib")

namespace System
{
namespace MSWindows
{

extern "C"
{
DECLSPEC_DLLIMPORT UINT WINAPI RegisterClipboardFormatA(
  LPCSTR lpszFormat   // address of name string
  );

}
}
}

namespace System
{
namespace LXmlEdit
{

class ClipboardFormats
{
public:
	ClipboardFormats();

	UINT cfPng;
	UINT cfJpeg;
	UINT cfGif;

	UINT cfRichTextFormat;
};

ClipboardFormats::ClipboardFormats()
{
	cfPng = MSWindows::RegisterClipboardFormatA("PNG");
	cfJpeg = MSWindows::RegisterClipboardFormatA("JFIF");
	cfGif = MSWindows::RegisterClipboardFormatA("GIF");

	cfRichTextFormat = MSWindows::RegisterClipboardFormatA("Rich Text Format");
}

ClipboardFormats _clipboardFormats;

void GetNewElementInsertionAt(CEXMLViewGroup* viewGroup, Web::Element** pparentNode, Web::Node** pbeforeNode);
//int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);

void DrawStippledLineV(MSWindows::HDC hDC, int x, int starty, int endy)
{
	/*
	for (int y = starty; y < endy; y += 2)
	{
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x, y+1);
	}
	*/
}

void DrawStippledLineH(MSWindows::HDC hDC, int y, int startx, int endx)
{
	for (int x = startx; x < endx; x += 2)
	{
		/*
		MoveToEx(hDC, x, y, NULL);
		LineTo(hDC, x+1, y);
		*/
	}
}

LDraw::RectD GetViewBoxRect(LDraw::RectD viewBox, LDraw::RectD viewPort, Web::SVGPreserveAspectRatioAlignType align, Web::SVGMeetOrSliceType meetOrSlice)
{
	LDraw::RectD rect;

	if (align == Web::SVG_PRESERVEASPECTRATIO_NONE)
	{
		rect.X = viewBox.X;
		rect.Y = viewBox.Y;
		rect.Width = viewBox.Width;
		rect.Height = viewBox.Height;
	}
	else
	{
		// Preserve aspect ratio

		if (meetOrSlice == Web::SVG_MEETORSLICE_SLICE)
		{
			rect.Width = viewBox.Width;
			rect.Height = (rect.Width*viewPort.Height)/viewPort.Width;

			if (rect.Height < viewBox.Height)
			{
				rect.Height = viewBox.Height;
				rect.Width = (rect.Height*viewPort.Width)/viewPort.Height;
			}
		}
		else if (meetOrSlice == Web::SVG_MEETORSLICE_MEET)
		{
			rect.Width = viewBox.Width;
			rect.Height = (rect.Width*viewPort.Height)/viewPort.Width;

			if (rect.Height > viewBox.Height)
			{
				rect.Height = viewBox.Height;
				rect.Width = (rect.Height*viewPort.Width)/viewPort.Height;
			}
		}
		else
			ASSERT(0);

		switch (align)
		{
		case Web::SVG_PRESERVEASPECTRATIO_XMINYMIN:
		case Web::SVG_PRESERVEASPECTRATIO_XMINYMID:
		case Web::SVG_PRESERVEASPECTRATIO_XMINYMAX:
			{
				rect.X = viewBox.X;
			}
			break;

		case Web::SVG_PRESERVEASPECTRATIO_XMIDYMIN:
		case Web::SVG_PRESERVEASPECTRATIO_XMIDYMID:
		case Web::SVG_PRESERVEASPECTRATIO_XMIDYMAX:
			{
				rect.X = viewBox.X + (viewBox.Width-rect.Width)/2;
			}
			break;

		case Web::SVG_PRESERVEASPECTRATIO_XMAXYMIN:
		case Web::SVG_PRESERVEASPECTRATIO_XMAXYMID:
		case Web::SVG_PRESERVEASPECTRATIO_XMAXYMAX:
			{
				rect.X = viewBox.X + (viewBox.Width-rect.Width);
			}
			break;
		}

		switch (align)
		{
	///////////////////////////////////////////////////
		case Web::SVG_PRESERVEASPECTRATIO_XMINYMIN:
		case Web::SVG_PRESERVEASPECTRATIO_XMIDYMIN:
		case Web::SVG_PRESERVEASPECTRATIO_XMAXYMIN:
			{
				rect.Y = viewBox.Y;
			}
			break;

		case Web::SVG_PRESERVEASPECTRATIO_XMINYMID:
		case Web::SVG_PRESERVEASPECTRATIO_XMIDYMID:
		case Web::SVG_PRESERVEASPECTRATIO_XMAXYMID:
			{
				rect.Y = viewBox.Y + (viewBox.Height-rect.Height)/2;
			}
			break;

	////////////////////////////////////////////////
		case Web::SVG_PRESERVEASPECTRATIO_XMINYMAX:
		case Web::SVG_PRESERVEASPECTRATIO_XMIDYMAX:
		case Web::SVG_PRESERVEASPECTRATIO_XMAXYMAX:
			{
				rect.Y = viewBox.Y + (viewBox.Height-rect.Height);
			}
			break;
		}
	}

	return rect;
}

/////////////////////////////////////////////////////////////////////////////
// CEXMLLayoutView

CEXMLLayoutView::CEXMLLayoutView()
{
	m_dragging = 0;

	m_view = NULL;
	m_viewGroup = NULL;

//	m_pBehavior = NULL;

//	m_pbctx = NULL;

	m_marginLeft = -999999;
	m_marginRight = -999999;
	m_textIndent = -999999;

	m_rulerOffset = LDraw::PointD(0,0);
	m_bShowRulers = true;
	m_bShowTransparencyGrid = false;

	m_pSkinBitmap = NULL;

	m_horRulerUnits = Web::CSS_PX;
	m_verRulerUnits = Web::CSS_PX;
}

CEXMLLayoutView::~CEXMLLayoutView()
{
	TRACE("~CEXMLLayoutView\n");
}

void CEXMLLayoutView::handleEvent(System::Event* evt)
{
	System::StringW* type = evt->get_type();

	System::EventPhaseType phase = evt->get_eventPhase();
	if (phase == System::CAPTURING_PHASE)
	{
		//if (evt->get_target() == dynamic_cast<CLXUIEventTargetImpl*>(m_domNode))
		{
			/*
			if (type == OLESTR("TextChanged"))
			{
				evt->stopPropagation;

				LXmlEdit::MutationEvent* mutEvt = dynamic_cast<LXmlEdit::MutationEvent*>(evt);

				TextDataEvent* evt2 = new TextDataEvent;
				evt2->m_offset = mutEvt->m_offset;
				evt2->m_len = mutEvt->m_len;
				evt2->initEvent(OLESTR("TextChanged"), false, false);
				dispatchEvent(evt2);
				
				return;
			}
			else*/ if (*type == L"TextInserted")
			{
				evt->stopPropagation();
				LXmlEdit::MutationEvent* mutEvt = dynamic_cast<LXmlEdit::MutationEvent*>(evt);

				CharacterData* node = dynamic_cast<CharacterData*>(evt->get_target());
				Web::CharacterData* charData = dynamic_cast<Web::CharacterData*>(node->getUserData(WSTR("Layout")));

				charData->insertData(mutEvt->m_offset, node->substringData(mutEvt->m_offset, mutEvt->m_len));
				/*
				TextDataEvent* evt2 = new TextDataEvent;
				evt2->m_offset = mutEvt->m_offset;
				evt2->m_len = mutEvt->m_len;
				evt2->initEvent(OLESTR("TextInserted"), false, false);
				dispatchEvent(evt2);
				*/
				
				return;
			}
			/*
			else if (type == OLESTR("TextDeleted"))
			{
				evt->stopPropagation;

				LXmlEdit::MutationEvent* mutEvt = dynamic_cast<LXmlEdit::MutationEvent*>(evt);

				TextDataEvent* evt2 = new TextDataEvent;
				evt2->m_offset = mutEvt->m_offset;
				evt2->m_len = mutEvt->m_len;
				evt2->initEvent(OLESTR("TextDeleted"), false, false);
				dispatchEvent(evt2);
				
				return;
			}
			*/
		}
	}

	Control::handleEvent(evt);
}

ErrorCode CEXMLLayoutView::ShowViews(IEFrame* pFrame)
{
//	ASSERT(0);
	MessageBeep(-1);
#if 0
	CDocumentWorkspace* pWorkspace = &static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_layoutViewWorkspace;

	{
		CComObject<CWENavigatorDlg>* p;
		CComObject<CWENavigatorDlg>::CreateInstance(&p);
		if (p)
		{
			p->m_layoutView = this;
			p->m_view = NULL;	// TODO
			p->AddRef();
		}

		m_views.Add(p);
	}

	pWorkspace->Create(pFrame, static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p), this);
#endif

	return Success;
}

// CViewGroup
int CEXMLLayoutView::OnGroupActivate(bool bActivate)
{
	CViewGroup::Activate(bActivate);
	return Success;
}

int CEXMLLayoutView::OnGroupClose()
{
	return Success;
}

#if 0
extern const GUID CLSID_HTMLDOCUMENT    = {0x25336920,0x03F9,0x11CF,{0x8F,0xD0,0x00,0xAA,0x00,0x68,0x6F,0x13}};
#endif

long CEXMLLayoutView::OnCreate()
{
	ASSERT(0);
#if 0
	/*
	{
		CComPtr<Web::Element> element;
		m_behaviorSite->GetElement(&element);

		CComPtr<IUnknown> unk;
		element->getUserData(L"n", &unk);
		CComQIPtr<IEXMLViewGroup> viewGroup(unk);

		m_viewGroup = static_cast<CEXMLViewGroup*>(viewGroup.p);
	}
	*/
	ASSERT(m_viewGroup);

	CComQIPtr<Web::DocumentView> documentView = m_viewGroup->m_pDocument->m_document;

	ASSERT(0);
#if 0
	documentView->createPresentation(&m_presentation);
#endif

//	m_pSkinBitmap = new LDraw::Bitmap(L"C:\\nokia.png");

#if 0	// I had this
	m_sizeGrip.Create(m_hWnd, CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE | SBS_SIZEGRIP);
	m_markupBar.Create(m_hWnd, CRect(0, 0, 0, 0), NULL, WS_CHILD | WS_VISIBLE);

	CComQIPtr<IOleObject> spOleObject = static_cast<CEXMLDocument*>(m_viewGroup->m_pDocument)->m_document;

	/*
	CRect rc;
	GetClientRect(&rc);
	spOleObject->DoVerb(OLEIVERB_SHOW, NULL, static_cast<CEXMLDocument*>(m_document.p), 0, m_hWnd, &rc);
	*/
	CComQIPtr<IOleDocument> spOleDocument = static_cast<CEXMLDocument*>(m_viewGroup->m_pDocument)->m_document;

	spOleDocument->CreateView(this, NULL, 0, &m_pIOleDocView);

	if (m_pIOleDocView == NULL)
	{
		return -1;
	}

	//This sets up toolbars and menus first
	m_pIOleDocView->UIActivate(TRUE);

	//Set the window size sensitive to new toolbars
	CRect rc;
	GetClientRect(&rc);

	m_pIOleDocView->SetRect(&rc);

	//Makes it all active
	m_pIOleDocView->Show(TRUE);

	{
		CComPtr<Web::Document> document;
		m_viewGroup->m_pDocument->get_DOMDocument(&document);

		CComQIPtr<Web::EventTarget> eventTarget = document;

		eventTarget->addEventListener(L"select", static_cast<Web::EventListener*>(this), VARIANT_TRUE);
	}
#endif

#if 0
/*	{
		CRect rc(0,0,0,0);
		IUnknown* p;

		m_axhorz.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
		m_axhorz.AttachControl(m_horz, &p);
		IDispEventImpl<1, EXMLLayoutView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_horz);

		m_axvert.Create(m_hWnd, rc, NULL, WS_VISIBLE | WS_CHILD);
		m_axvert.AttachControl(m_vert, &p);
		IDispEventImpl<2, EXMLLayoutView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventAdvise(m_vert);
	}
*/
	if (TRUE)
	{
#if 0
		WCHAR* filePath = L"";//L"C:\\MMStudio\\help\\Testing.doc";

		IMoniker* _pmkfile;
		ErrorCode hr = CreateFileMoniker(filePath, &_pmkfile);

		hr = CreateBindCtx(0, &m_pbctx);

		if (StgIsStorageFile(filePath) == Success)
		{
			/*
			FORMATETC fetc;
			fetc.cfFormat = 0;
			fetc.ptd = NULL;
			fetc.dwAspect = DVASPECT_CONTENT;
			fetc.lindex = -1;
			fetc.tymed = TYMED_ISTORAGE;
			*/

			ErrorCode hr;

    /*
     * 7.  Create a temp file for all embedded files.  Note that in this
     *     sample we don't save any changes to DocObjects because we 
	 *     don't manage any storage directly.
	 */	  
			 if (FAILED(StgCreateDocfile(NULL, STGM_TRANSACTED | STGM_READWRITE
				  | STGM_SHARE_EXCLUSIVE | STGM_CREATE| STGM_DELETEONRELEASE
				  , 0, &m_pIStorage)))
				  return FALSE;

			 /*
			CComPtr<IStorage> stg;
			hr = StgOpenStorage(
				L"C:\\test.doc",
				NULL,
				STGM_DIRECT | STGM_READ | STGM_SHARE_EXCLUSIVE,
				NULL,
				0,
				&stg);
				*/

			{
			 DWORD       dwMode=STGM_TRANSACTED | STGM_READWRITE
								  | STGM_SHARE_EXCLUSIVE;
			 TCHAR       szName[32];

//			 IStorage* pIStorage = m_pIStorage;
//			 if (NULL==pIStorage)
//				  return FALSE;

			 /*
			  * Attempt to open the storage under this ID.  If there is
			  * none, then create it.  In either case we end up with an
			  * IStorage that we either save in pPage or release.
			  */
			 wsprintf(szName, TEXT("Site %lu"), 1);

			#ifdef UNICODE
			 hr=m_pIStorage->CreateStorage(szName, dwMode, 0, 0, &m_pIStorage2);
			#else
			 OLECHAR  szwName[32];
			MultiByteToWideChar(CP_ACP, 0, szName, -1, szwName, 32);    
			 hr=m_pIStorage->CreateStorage(szwName, dwMode, 0, 0, &m_pIStorage2);
			#endif

			 if (FAILED(hr))
				  return FALSE;

			//Create stream for the object; name is irrelevant
			dwMode=STGM_DIRECT | STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
			#ifdef UNICODE
			 hr=m_pIStorage2->CreateStream(TEXT("\003DocObjInfo"), dwMode, 0, 0
				  , &m_pIStream);
			#else    
			MultiByteToWideChar(CP_ACP, 0, "\003DocObjInfo", -1, szwName, 32);    
			 hr=m_pIStorage2->CreateStream(szwName, dwMode, 0, 0, &m_pIStream);
			#endif
   
			 //If we failed to create a stream in the file, do it in memory
			if (FAILED(hr))
				{
				if (FAILED(CreateStreamOnHGlobal(NULL, TRUE, &m_pIStream)))
					 return FALSE;
				}
			}

			char* pszFile = "C:\\test.doc";

			 //Now create an object from the file
			#ifdef UNICODE    
			 hr=OleCreateFromFile(CLSID_NULL, pszFile, IID_IUnknown
				  , OLERENDER_NONE, NULL, NULL, m_pIStorage2, (void **)&pObj);
			#else
			 OLECHAR     szFile[512];    //Assumption on string length

			 MultiByteToWideChar(CP_ACP, 0, pszFile, -1, szFile, 512);    
			hr=OleCreateFromFile(CLSID_NULL, szFile, IID_IUnknown
				  , OLERENDER_NONE, NULL, NULL, m_pIStorage2, (void **)&m_spUnknown);
			#endif

		//	hr = OleCreateFromFile(CLSID_NULL, L"C:\\test.doc", IID_IOleObject,
		//		OLERENDER_NONE, &fetc, NULL, stg, (void**)&spOleObject);

			m_dwAdvise = 0;

			if (SUCCEEDED(hr))
			{
				m_spOleObject = m_spUnknown;
				m_spOleDocument = m_spUnknown;

				m_spOleObject->SetClientSite(this);
				m_spOleObject->Advise(this, &m_dwAdvise);

				OleRun(m_spUnknown);

				CRect rc;
				GetClientRect(&rc);
				m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_hWnd, &rc);
			}
			else
			{
				ATLTRACE("OleCreateFromFile()=%ld\n", hr);
				::MessageBox(NULL, "Failed to create document", "", MB_OK);
			}
		}
		else
#endif
		{
			ErrorCode hr;

			_bstr_t url = static_cast<CEXMLDocument*>(m_document.p)->m_pathName;

			CComPtr<IMoniker> moniker;
		//if (SUCCEEDED(hr))

			CComPtr<IBindCtx> bindctx;
		//	hr = CreateAsyncBindCtx(NULL, this, NULL, &bindctx);
			hr = CreateBindCtx(0, &bindctx);
			ASSERT(SUCCEEDED(hr));

		//	ULONG chEaten;
		//	hr = MkParseDisplayNameEx(bindctx, url, &chEaten, &moniker);
		//	ASSERT(SUCCEEDED(hr));
			hr = CreateURLMoniker(NULL, url, &moniker);

			PWSTR mime;
			::FindMimeFromData(bindctx, url, NULL, 0, NULL, 0, &mime, 0);

			PSTR rgszTypes[3] =
			{
				"text/html",	// CFSTR_MIME_HTML
				"text/xml+svg",
				"text/plain",
			};

			CLSID rgclsID[3];
			rgclsID[0] = CLSID_LHTMLActiveDocument;
			rgclsID[1] = CLSID_LHTMLActiveDocument;
			rgclsID[2] = CLSID_LHTMLActiveDocument;

			hr = RegisterMediaTypeClass(bindctx, 3, rgszTypes, rgclsID, 0);
			ASSERT(SUCCEEDED(hr));

		//	CComPtr<IBindStatusCallback> oldcallback;
		//	hr = RegisterBindStatusCallback(bindctx, this, &oldcallback, 0);
			//if (SUCCEEDED(hr))
	
#if 0
			BIND_OPTS opts;
			opts.grfFlags = 0;
			opts.cbStruct = sizeof(opts);
			opts.grfMode = /*STGM_TRANSACTED |*/ STGM_READ/*WRITE*/ /*| STGM_SHARE_EXCLUSIVE*/;
			opts.dwTickCountDeadline = 0;

			hr = bindctx->SetBindOptions(&opts);
#endif
			//	CComPtr<IUnknown> spUnknown;
			moniker->BindToObject(bindctx, NULL, IID_IUnknown, (void**)&m_spUnknown);

			CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;

#if 0
//			CLSID rclsid = CLSID_HTMLDOCUMENT;
			CLSID rclsid = CLSID_LHTMLActiveDocument;
			 IPersistStorage*    pipstg  = NULL;

		 // Don't load if an object has already been loaded...
			 //if ((!_pstgfile) || (_poleobj)) return FALSE;

		 // Create an inproc handler and load the data from IStorage...
			ErrorCode hr = CoCreateInstance(rclsid, NULL, CLSCTX_ALL, IID_IUnknown, (void**)&m_spUnknown);
			 //if (FAILED(hr) || (NULL == punk)) return FALSE;

			CComQIPtr<IPersistMoniker> persistMoniker = m_spUnknown;
			persistMoniker->Load(FALSE, moniker, NULL, 0);

		 // Load the data using IPersistStorage...
			/*
			 hr = m_spUnknown->QueryInterface(IID_IPersistStorage, (void**)&pipstg);
			if (SUCCEEDED(hr))
			 {
			  // If we opened a file and have moniker, load from existing data...
				  if (_pmkfile)
					  hr = pipstg->Load(_pstgfile);
				  else
					  hr = pipstg->InitNew(_pstgfile);

				pipstg->Release();
			 }
			 else
			 */
			/*
			 {
				  IPersistFile* pipf = NULL;
				  LPOLESTR  pwszDisplayName = NULL;

				  hr = _pmkfile->GetDisplayName(m_pbctx, NULL, &pwszDisplayName);
				  if (SUCCEEDED(hr))
				  {
						hr = m_spUnknown->QueryInterface(IID_IPersistFile, (void**)&pipf);
						if (SUCCEEDED(hr))
						{
							 pipf->Load(pwszDisplayName, STGM_READ);
							 pipf->Release();
						}
						CoTaskMemFree(pwszDisplayName);
				  }
			 }
			 */

			// Had loading here
			CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
			if (htmlActiveDoc)
			{
				CComPtr<Web::Document> xmldocument;
				m_document->get_DOMDocument(&xmldocument);

				htmlActiveDoc->SetDocument(xmldocument);
				htmlActiveDoc->SetElement(m_viewGroup->m_outerElement);

				ErrorCode hr = IDispEventImpl<4, EXMLLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(htmlActiveDoc);
				ASSERT(SUCCEEDED(hr));
			}
#endif


		 // Check if the object could not be initialized...
			 //if (FAILED(hr)) {punk->Release(); return FALSE;}

		 // We need IOleObject so ask. If object doesn't support it we should fail...
				m_spOleObject = m_spUnknown;
				if (m_spOleObject == NULL)
				{
					ASSERT(0);
				}

		//	 hr = punk->QueryInterface(IID_IOleObject, (void **)&_poleobj);
		//	 punk->Release(); // Release punk here just in case...
		//	 if (FAILED(hr)) return FALSE;

		 // Fudge factor -- if you make the following calls too quickly, PPT will hang...
			// Sleep(250);

		 // Run the object (object must support IRunnableObject)...
			OleRun(m_spOleObject);

		 // SetClientSite is critical for DocObjects. If this fails the
		 // object doesn't support inplace activation!!
			hr = m_spOleObject->SetClientSite(static_cast<IOleClientSite*>(this));
			/*
			 if (FAILED(hr))
			 {
				  _poleobj->Release();
				  _poleobj = NULL;
				  return FALSE;
			 }
			 */

		 // Lock the object in memory and make a few housekeeping calls...
			 OleLockRunning(m_spOleObject, TRUE, FALSE);

			// m_spOleObject->SetHostNames(L"Framer Ex", _bstrDocName);
			 m_spOleObject->Advise(static_cast<IAdviseSink*>(this), &m_dwAdvise);
			 
			 CRect rc;
			 GetClientRect(&rc);
			 m_spOleObject->DoVerb(OLEIVERB_SHOW, NULL, this, 0, m_hWnd, &rc);

			// Didn't have loading here
		}
	}
#endif

#if 0
	{
		CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		IDispEventImpl<2, CEXMLLayoutView, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>::DispEventAdvise(window);
	}
#endif
#endif
	return 0;
}

long CEXMLLayoutView::OnDestroy()
{
	ErrorCode hr;

#if 0	// I had this
	{
		CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		IDispEventImpl<2, CEXMLLayoutView, &DIID__ILHTMLWindowEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(window);
	}
#endif

	// TODO here
#if 0
	CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;
	if (htmlActiveDoc)
	{
		hr = IDispEventImpl<4, EXMLLayoutView, &DIID__ILHTMLActiveDocumentEvents, &LIBID_LHTMLLib, 1, 0>::DispEventUnadvise(htmlActiveDoc);
		ASSERT(SUCCEEDED(hr));
	}

	m_pIOleDocView->SetInPlaceSite(NULL);
	//m_spOleObject->Unadvise(m_dwAdvise);
	hr = m_spOleObject->SetClientSite(NULL);

	//m_pIOleDocView.Release();
//	hr = IDispEventImpl<3, EXMLLayoutView, &DIID__IESvgDocumentEvents, &LIBID_WEBEDITORLib, 1, 0>::DispEventUnadvise(m_document);
//	ASSERT(SUCCEEDED(hr));

	/*
	IDispEventImpl<1, EXMLLayoutView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_horz);
	IDispEventImpl<2, EXMLLayoutView, &DIID__IUIScrollBarEvents, &LIBID_UILib, 1, 0>::DispEventUnadvise(m_vert);
	*/

	/*
	if (m_hWndSizeGrip)
	{
		::DestroyWindow(m_hWndSizeGrip);
		m_hWndSizeGrip = NULL;
	}
	*/
#endif

	return 0;
}

/*
long CEXMLLayoutView::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	OnSize();
	return 0;
}
*/

void CEXMLLayoutView::OnSize()
{
	ASSERT(0);
#if 0
	CRect client;
	GetClientRect(&client);
	
	CRect rc = client;

	if (m_bShowRulers)
	{
		rc.top += 16;
		rc.left += 16;
	}

	rc.bottom -= 16+1;	// Markup (and dividing line)
	/*
	//Tell the in-place object about the new frame size
	
	  if (pFrame->m_pIOleIPActiveObject != NULL)
	  pFrame->m_pIOleIPActiveObject->ResizeBorder(&rc, this, FALSE);
	*/
	
	/*
	* Resize the client, which is done in all cases since this window
	* is the parent of the DocObject, plus we need to tell the 
	* DocObject of the new size through IOleDocumentView::SetRect.
	*/

	if (m_pSkinBitmap)
	{
		rc.left = (client.right-100)/2;
		rc.top = 100;
		rc.right = rc.left + 100;
		rc.bottom = rc.top + 100;
	}

	if (m_pIOleDocView != NULL)
	{
		m_pIOleDocView->SetRect(&rc);
	}
	
#if 0
	rc.left  +=pFR->m_bwIP.left;
	rc.right -=pFR->m_bwIP.right;
	rc.top   +=pFR->m_bwIP.top;
	rc.bottom-=pFR->m_bwIP.bottom;
	
	pFR->ResizeClientWindow(rc.left, rc.top, rc.right-rc.left
		, rc.bottom-rc.top);
#endif

//	OnSize();

	m_sizeGrip.MoveWindow(client.right-16, client.bottom-16, 16, 16);
	m_markupBar.MoveWindow(0, client.bottom-17, client.right-16, 17);

	InvalidateRect(NULL);
#endif
}

#if 0
ErrorCode CEXMLLayoutView::get_ESvgDocument(IEXMLDocument **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_viewGroup->m_pDocument;
	(*pVal)->AddRef();
	return Success;
}
#endif

ErrorCode CEXMLLayoutView::OnActivate(bool bActivate, UI::Control* pActivateView, UI::Control* pDeactivateView)
{
//	CComQIPtr<IUIActiveManager> uiActiveManager = m_viewGroup->m_pDocument->m_app;
	ASSERT(0);
#if 0

	if (bActivate)
	{
	//	CComQIPtr<IUIFrame> frame = static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_frame;
	//	frame->FloatControlBar(static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_navigatorBar, CPoint(0,0), CBRS_SIZE_DYNAMIC);

	//	static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_navigatorBar->Show(TRUE);
#if 0
		static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_svgToolsBar->Show(TRUE);
#endif

	//	uiActiveManager->ActivateObject(m_viewGroup->GetUnknown(), GetUnknown());

		CViewGroup::Activate(bActivate);
	}
	else
	{
		CViewGroup::Activate(bActivate);

	//	static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_navigatorBar->Show(FALSE);
#if 0
		static_cast<CLXMLEditorApp*>(m_viewGroup->m_pDocument->m_app.p)->m_svgToolsBar->Show(FALSE);
#endif

	//	uiActiveManager->DeactivateObject(GetUnknown());
	}
#endif
	return Success;
}

/*
static TCHAR* UnitTypeString[] =
{
	CSS_NUMBER	= 1,
	CSS_PERCENTAGE	= 2,
	CSS_EMS	= 3,
	CSS_EXS	= 4,
	CSS_PX	= 5,
	CSS_CM	= 6,
	CSS_MM	= 7,
	CSS_IN	= 8,
	CSS_PT	= 9,
	CSS_PC	= 10,
};
*/

void GetRulerValues(Web::CSSUnitType unit, double& pixelInterval, double& numberInterval, double magnify, double percentageOf = 0)
{
	double minPixelInterval = 40;

	if (unit == Web::CSS_PERCENTAGE)
	{
		double pixelsPerPoint = percentageOf/100 * magnify;

		// First, get 100,50,25,12.5 etc.
		numberInterval = 100;
		pixelInterval = numberInterval * pixelsPerPoint;

		while (1/*pixelInterval > minPixelInterval*/)
		{
			double _numberInterval = numberInterval/2;
			double _pixelInterval = _numberInterval * pixelsPerPoint;

			if (_pixelInterval <= minPixelInterval)
				break;

			numberInterval = _numberInterval;
			pixelInterval = _pixelInterval;
		}

		// If every 100 is still too large...
		while (pixelInterval < minPixelInterval)
		{
			numberInterval += 100;
			pixelInterval = numberInterval * pixelsPerPoint;
		}
	}
	else
	{
		double pixelsPerPoint = Web::ConvertSpecifiedValueToUserUnit(unit, 1) * magnify;

		numberInterval = 6;
		pixelInterval = numberInterval * pixelsPerPoint;

		while (pixelInterval < minPixelInterval)
		{
			if (numberInterval < 24) numberInterval += 6;
			else if (numberInterval == 24) numberInterval = 36;
			else if (numberInterval < 288) numberInterval *= 2;
			else if (numberInterval == 288) numberInterval = 1152;
			else numberInterval *= 4;

			pixelInterval = numberInterval * pixelsPerPoint;
		}
	}

#if 0
	double pixelsPerPoint = ConvertSpecifiedValueToUserUnit(unit, 1) * m_magnify;

	double minEveryPx = 40;
	double valueAdd2 = minEveryPx / pixelsPerPoint;//*pixelsPerPoint;

	numberEveryPx = 6 * pixelsPerPoint;

	valueAdd = 0;//valueAdd2;
	numberEveryPx = valueAdd2 * pixelsPerPoint;

	while (numberEveryPx < minEveryPx)
	{
	}

	int n = 1;
	while (valueAdd == 0/*numberEveryPx < minEveryPx*/)
	{
		if (valueAdd2 <= 6) valueAdd = 6*(n);
		else if (valueAdd2 <= 24) valueAdd = 24*(n);
		else if (valueAdd2 <= 36) valueAdd = 36*(n);
		else if (valueAdd2 <= 72) valueAdd = 72*(n);

		numberEveryPx = valueAdd * pixelsPerPoint;

		valueAdd2 /= 100;
		n *= 100;
	}
#endif
}

void DrawSubDivisionLines(UI::Graphics* pGraphics, bool bHorizontal, int start, int width, int height, uint subdivisionsMask)
{
	int nsubdivisions = subdivisionsMask & 0xf;

	for (int i = 0; i < nsubdivisions; i++)
	{
		int offset = start + i*width/nsubdivisions;

		if (bHorizontal)
		{
			pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0,0,0)), offset, 16-height, offset, 16);
		}
		else
		{
			pGraphics->DrawLine(new LDraw::Pen(LDraw::Color(0,0,0)), 16-height, offset, 16, offset);
		}

		if (subdivisionsMask>>4)
		{
			DrawSubDivisionLines(pGraphics, bHorizontal, offset, width/nsubdivisions, height-2, subdivisionsMask>>4);
		}
	}
}

/*
void CEXMLLayoutView::CalculateBoundsAndChildren(LDraw::SizeD availSize)
{
	m_desiredSize.Width = 50;
	m_desiredSize.Height = 50;
}
*/

void CEXMLLayoutView::OnRender(UI::Graphics* pGraphics)
{
	Control::OnRender(pGraphics);
//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color::Red), 0, 0, m_computedSize.Width, m_computedSize.Height);
}

#if 0
ErrorCode CEXMLLayoutView::Draw(ILCanvas* canvas)
{
	ASSERT(0);
#if 0
	CRect client;
	GetClientRect(&client);

	LDraw::Graphics* pGraphics;
	canvas->GetGdip((long*)&pGraphics);

#if 0
	CRect clip;
	dc.GetClipBox(&clip);

	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;
	if (view)
#endif

	{
#if 0
		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		if (m_pSkinBitmap)
		{
			LDraw::Graphics graphics(dc);

			graphics.DrawImage(m_pSkinBitmap,

				LDraw::Rect(
					(client.Width()-m_pSkinBitmap->GetWidth())/2,
					0,
					m_pSkinBitmap->GetWidth(), m_pSkinBitmap->GetHeight()),

				0, 0, m_pSkinBitmap->GetWidth(), m_pSkinBitmap->GetHeight(),
				LDraw::UnitPixel);
		}

		if (window)
#endif
		{
			double m_magnify = 1;
			double scrollposX = 0;
			double scrollposY = 0;

#if 0
			window->get_magnify(&m_magnify);
			window->get_currentTranslateX(&scrollposX);
			window->get_currentTranslateY(&scrollposY);
#endif
			scrollposX = -scrollposX;
			scrollposY = -scrollposY;

			long innerWidth = 400;
			long innerHeight = 400;
#if 0
			window->get_innerWidth(&innerWidth);
			window->get_innerHeight(&innerHeight);
#endif

			// Draw horizontal ruler
			if (TRUE)
			{
#if 0
				dc.SetBkMode(TRANSPARENT);
#endif

				if (m_bShowRulers)
				{
					CRect client;
					GetClientRect(&client);

					CRect m_areaRect(16, 16, client.right, client.bottom);

					CRect horRulerRect(16, 0, m_areaRect.right, 16);
					CRect verRulerRect(0, 16, 16, m_areaRect.bottom);

					CRect irect;
					bool bIHorRuler = TRUE;//irect.IntersectRect(&horRulerRect, &clip);
					bool bIVerRuler = TRUE;//irect.IntersectRect(&verRulerRect, &clip);

					pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(255, 255, 255)), 0, 0, 16, 16);

					if (bIHorRuler)
					{
						//LDraw::Graphics graphics(dc);

						LDraw::Rect rect(horRulerRect.left, horRulerRect.top, horRulerRect.Width(), horRulerRect.Height());
						LDraw::LinearGradientBrush brush(rect, LDraw::Color(255, 255, 255, 255), LDraw::Color(255, 210, 210, 210), LDraw::LinearGradientModeVertical);
						pGraphics->FillRectangle(&brush, rect);

					//	dc.FillSolidRect(&horRulerRect, RGB(255, 255, 255));
					}

					if (bIVerRuler)
					{
						//LDraw::Graphics graphics(dc);

						LDraw::Rect rect(verRulerRect.left, verRulerRect.top, verRulerRect.Width(), verRulerRect.Height());
						LDraw::LinearGradientBrush brush(rect, LDraw::Color(255, 255, 255, 255), LDraw::Color(255, 210, 210, 210), LDraw::LinearGradientModeHorizontal);
						pGraphics->FillRectangle(&brush, rect);

						//	dc.FillSolidRect(&verRulerRect, RGB(255, 255, 255));
					}

					pGraphics->DrawRectangle(&LDraw::Pen(LDraw::Color(0,0,0)), 0, 0, client.right, 16);
					pGraphics->DrawRectangle(&LDraw::Pen(LDraw::Color(0,0,0)), 0, 0, 16, client.bottom);

#if 0
					DrawStippledLineH(pGraphics, 5, 0, 16);
					DrawStippledLineV(pGraphics, 5, 0, 16);
#endif

					// TODO remove
					CComPtr<Web::Document> document;
					m_viewGroup->m_pDocument->get_DOMDocument(&document);

					CComPtr<Web::Element> documentElement;
					document->get_documentElement(&documentElement);

					//
					CComQIPtr<ILSVGFitToViewBox> fitToViewBox = m_rulerElement;//svgsvgElement;

					double tx = 0;
					double ty = 0;
					double sx = 1;
					double sy = 1;
					if (fitToViewBox)
					{
						CComPtr<ILSVGAnimatedPreserveAspectRatio> apreserveAspectRatio;
						fitToViewBox->get_preserveAspectRatio(&apreserveAspectRatio);

						CComPtr<ILSVGPreserveAspectRatio> preserveAspectRatio;
						apreserveAspectRatio->get_baseVal(&preserveAspectRatio);

						LSVGPreserveAspectRatioAlignType align;
						preserveAspectRatio->get_align(&align);

						LSVGMeetOrSliceType meetOrSlice;
						preserveAspectRatio->get_meetOrSlice(&meetOrSlice);

						CComPtr<ILSVGAnimatedRect> arect;
						fitToViewBox->get_viewBox(&arect);

						CComPtr<ILSVGRect> _viewBox;
						arect->get_baseVal(&_viewBox);
						SVGRect viewBox = _viewBox;

						CComPtr<ILSVGRect> _viewPort;
						ASSERT(0);
#if 0
						window->svgGetRBBox(CComQIPtr<ILSVGElement>(m_rulerElement), &_viewPort);
#endif
						SVGRect viewPort =_viewPort;

						LDraw::RectD rect = GetViewBoxRect(viewPort, viewBox, align, meetOrSlice);

						CComPtr<ILSVGMatrix> viewBoxMatrix;
#if 0
						window->svgGetElementViewBoxMatrix(CComQIPtr<ILSVGElement>(documentElement), &viewBoxMatrix);
#endif

						/*
						viewBoxMatrix->get_e(&tx);
						viewBoxMatrix->get_f(&ty);
						viewBoxMatrix->get_a(&sx);
						viewBoxMatrix->get_d(&sy);
						*/

						sx = rect.Width / viewBox.Width;
						sy = rect.Height / viewBox.Height;

						tx = rect.X/sx;
						ty = rect.Y/sy;
					}

					if (bIHorRuler || bIVerRuler)
					{
					//	HFONT hFont = CreateFont(11, 0, 0, 0, 0, FALSE, FALSE, FALSE, 0, 0, 0, PROOF_QUALITY, FF_DONTCARE, "Small Fonts");
					//	HFONT hOldFont = dc.SelectFont(hFont);
						LDraw::Font font(L"Arial", 11, LDraw::FontStyleRegular, LDraw::UnitPixel);

						//if (m_activeSpread)
						{
							LDraw::GraphicsState state = pGraphics->Save();

						//	state = dc.SaveDC();

							// Horizontal ruler
							if (TRUE)//dc.IntersectClipRect(horRulerRect.left, horRulerRect.top, horRulerRect.right, horRulerRect.bottom) > NULLREGION)
							{
								double valueAdd;
								double numberEveryPx;

								GetRulerValues(m_horRulerUnits, numberEveryPx, valueAdd, m_magnify*sx, innerWidth);

								DWORD subdivisionsMask = (2<<0) | (2<<4) | (3<<8);

								int start = (scrollposX - (tx+m_rulerOffset.X)*m_magnify*sx - (numberEveryPx-1))/ numberEveryPx;
								int end = start + (m_areaRect.Width()+numberEveryPx+numberEveryPx-1) / numberEveryPx;

								//POINT oldOrg;
								//LDraw::Matrix oldTransform;
								//pGraphics->GetTransform(&oldTransform);

								pGraphics->TranslateTransform(16 + -scrollposX + (tx+m_rulerOffset.X)*m_magnify*sx, 0);
								//dc.SetViewportOrg(16 + -scrollposX + (tx+m_rulerOffset.X)*m_magnify*sx, 0, &oldOrg);

								int y = 0;

								for (int i = start; i < end; i++)
								{
									int x = i * numberEveryPx;

#if 0
									dc.MoveTo(x, 0);
									dc.LineTo(x, 16);
#endif

									WCHAR str[32];
									int len = swprintf(str, L"%g", fabs(i * valueAdd));

									//dc.TextOut(x+1, y+1, str, str.GetLength());
									pGraphics->DrawString(
										str, len,
										&font,
										LDraw::PointF(x+1, y+1),
										&LDraw::SolidBrush(LDraw::Color(0,0,0)));

									DrawSubDivisionLines(pGraphics, TRUE, x, numberEveryPx, 8, subdivisionsMask);
								}

						//		dc.SetViewportOrg(oldOrg.x, oldOrg.y, NULL);
							}

							/*
							{
								CRect rc(horRulerRect.right-16, horRulerRect.top, horRulerRect.right, horRulerRect.bottom);
								dc.Draw3dRect(&rc, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DDKSHADOW));
								rc.InflateRect(-1,-1);
								dc.FillSolidRect(&rc, GetSysColor(COLOR_BTNFACE));


							}
							*/

							pGraphics->Restore(state);

							state = pGraphics->Save();

							// Vertical ruler
							if (TRUE)//dc.IntersectClipRect(verRulerRect.left, verRulerRect.top, verRulerRect.right, verRulerRect.bottom) > NULLREGION)
							{
								double valueAdd;
								double numberEveryPx;

								GetRulerValues(m_verRulerUnits, numberEveryPx, valueAdd, m_magnify*sy, innerHeight);

								DWORD subdivisionsMask = (2<<0) | (2<<4) | (3<<8);

								int start = (scrollposY - (ty+m_rulerOffset.Y)*m_magnify*sy) / numberEveryPx;
								int end = start + (m_areaRect.Height()+numberEveryPx-1) / numberEveryPx;

							//	POINT oldOrg;
							//	dc.SetViewportOrg(0, 16 + -scrollposY + (ty+m_rulerOffset.Y)*m_magnify*sy, &oldOrg);
								pGraphics->TranslateTransform(0, 16 + -scrollposY + (ty+m_rulerOffset.Y)*m_magnify*sy);

								int x = 0;

								for (int i = start; i < end; i++)
								{
									int y = i * numberEveryPx;

								//	dc.MoveTo(0, y);
								//	dc.LineTo(16, y);

									WCHAR str[64];
									int len = swprintf(str, L"%g", fabs(i * valueAdd));

									for (int j = 0; j < len; j++)
									{
										//dc.TextOut(x+1, y+1+j*11, &str[j], 1);
										pGraphics->DrawString(
											&str[j], 1,
											&font,
											LDraw::PointF(x+1, y+1+j*11),
											&LDraw::SolidBrush(LDraw::Color(0,0,0)));
									}

									DrawSubDivisionLines(pGraphics, FALSE, y, numberEveryPx, 8, subdivisionsMask);
								}

							//	dc.SetViewportOrg(oldOrg.x, oldOrg.y, NULL);
							}

							pGraphics->Restore(state);
						}

					//	dc.SelectFont(hOldFont);
					//	DeleteObject(hFont);

#if 0
						if (m_bCurPosOnRulerVisible)
						{
							int oldR2 = SetROP2(hDC, R2_NOTXORPEN);
							DrawCurPosOnRuler(hDC, m_point);
							SetROP2(hDC, oldR2);
						}
#endif
					}
				}
			}
#if 0
			else
			{
				CComPtr<ILDOMRange> range;
				window->get_selection(&range);

				if (range)
				{
					dc.FillSolidRect(0, 0, client.right, 22, GetSysColor(COLOR_BTNFACE));

					CRect rc(0, 2, client.right, 16);
				//	dc.Draw3dRect(&rc, GetSysColor(COLOR_3DDKSHADOW), GetSysColor(COLOR_3DSHADOW));

				//	rc.InflateRect(-1, -1);
					dc.FillSolidRect(&rc, RGB(255, 255, 255));

					HPEN hOldPen = dc.GetCurrentPen();
					HBRUSH hOldBrush = dc.GetCurrentBrush();

					CPen lightPen;
					lightPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));

					CPen darkPen;
					darkPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

					CPen blackPen;
					blackPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DDKSHADOW));

					CBrush grayBrush;
					grayBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

					// Draw text-indent
					{
						double x;

						if (m_dragging == -1)
						{
							x = m_oldpoint.x;
						}
						else if (m_dragging == -3)
						{
							x = m_oldpoint.x + m_textIndent;
						}
						else
						{
							x = m_marginLeft + m_textIndent;
						}

						int xmid = x;

						CPoint pts[5] =
						{
							CPoint(xmid+4, 0),
							CPoint(xmid-4, 0),
							CPoint(xmid-4, 3),
							CPoint(xmid, 7),
							CPoint(xmid+4, 3)
						};

						dc.SelectPen(blackPen);
						dc.SelectBrush(grayBrush);
						dc.Polygon(pts, 5);

					//	CPen lightPen;
					//	lightPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));

					//	CPen darkPen;
					//	darkPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

						dc.SelectPen(lightPen);
						dc.MoveTo(pts[0].x-1, pts[0].y+1);
						dc.LineTo(pts[1].x+1, pts[1].y+1);
						dc.LineTo(pts[2].x+1, pts[2].y);
						dc.LineTo(pts[3].x, pts[3].y-1);

						dc.SelectPen(darkPen);
						dc.LineTo(pts[4].x-1, pts[4].y);
						dc.LineTo(pts[0].x-1, pts[0].y+1);
					}

					// Draw margin-left
					{
						double x;

						if (m_dragging == -2 || m_dragging == -3)
						{
							x = m_oldpoint.x;
						}
						else
						{
							x = m_marginLeft;
						}

						int xmid = x;

						CPoint pts[5] =
						{
							CPoint(xmid-4, 7+7),
							CPoint(xmid+4, 7+7),
							CPoint(xmid+4, 4+7),
							CPoint(xmid, 0+7),
							CPoint(xmid-4, 4+7)
						};

						dc.SelectPen(blackPen);
						dc.SelectBrush(grayBrush);
						dc.Polygon(pts, 5);

						dc.SelectPen(darkPen);
						dc.MoveTo(pts[0].x+1, pts[0].y-1);
						dc.LineTo(pts[1].x-1, pts[1].y-1);
						dc.LineTo(pts[2].x-1, pts[2].y);
						dc.LineTo(pts[3].x, pts[3].y+1);

						dc.SelectPen(lightPen);
						dc.LineTo(pts[4].x+1, pts[4].y);
						dc.LineTo(pts[0].x+1, pts[0].y-1);
					}

					// Draw margin-left/text-indent
					{
						double x;

						if (m_dragging == -2 || m_dragging == -3)
						{
							x = m_oldpoint.x;
						}
						else
						{
							x = m_marginLeft;
						}

						int xmid = x;

					//	CBrush grayBrush;
					//	grayBrush.CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

						dc.SelectPen(blackPen);
						dc.SelectBrush(grayBrush);
						dc.Rectangle(x-4, 15, x+5, 15+7);

						dc.Draw3dRect(x-3, 16, 7, 5, GetSysColor(COLOR_3DHILIGHT), GetSysColor(COLOR_3DSHADOW));
					}

					// Draw margin-right
					{
						double x;

						if (m_dragging == -4)
						{
							x = m_oldpoint.x;
						}
						else
						{
							x = client.right - m_marginRight;
						}

						int xmid = x;

						CPoint pts[5] =
						{
							CPoint(xmid-4, 7+7),
							CPoint(xmid+4, 7+7),
							CPoint(xmid+4, 4+7),
							CPoint(xmid, 0+7),
							CPoint(xmid-4, 4+7)
						};

						dc.SelectPen(blackPen);
						dc.SelectBrush(grayBrush);
						dc.Polygon(pts, 5);

					//	CPen lightPen;
					//	lightPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DHILIGHT));

					//	CPen darkPen;
					//	darkPen.CreatePen(PS_SOLID, 1, GetSysColor(COLOR_3DSHADOW));

						dc.SelectPen(darkPen);
						dc.MoveTo(pts[0].x+1, pts[0].y-1);
						dc.LineTo(pts[1].x-1, pts[1].y-1);
						dc.LineTo(pts[2].x-1, pts[2].y);
						dc.LineTo(pts[3].x, pts[3].y+1);

						dc.SelectPen(lightPen);
						dc.LineTo(pts[4].x+1, pts[4].y);
						dc.LineTo(pts[0].x+1, pts[0].y-1);
					}

					dc.SelectPen(hOldPen);
					dc.SelectBrush(hOldBrush);
				}
			}
#endif
		}
	}

#if 0	// Had this
	{
		CXMLDocumentView* pDocumentView = static_cast<CXMLDocumentView*>(m_presentation.p);

		CPSVGElementImpl* pPElement = (CPSVGElementImpl*)(pDocumentView->m_pRootElement);
		CLSVGSVGElement* psvgsvgElement = static_cast<CLSVGSVGElement*>(pDocumentView->m_pRootElement->m_pNode);

		if (psvgsvgElement)
		{
			CHTMRenderContext pC;
		//	pC.m_pUI = NULL;//m_pWindow->m_pUI;
			pC.m_pWindow = NULL;//m_pOwnedWindow;//m_pWindow;
			pC.m_pGraphics = pGraphics;

			double magnify = 1;//GetFinalMagnify();

			LDraw::GraphicsState state = pC.m_pGraphics->Save();	// TODO, just save matrix, it's probably faster

			/*
			double currentTranslateX = m_currentTranslateX + psvgsvgElement->m_currentTranslate->m_x;
			double currentTranslateY = m_currentTranslateY + psvgsvgElement->m_currentTranslate->m_y;
			*/
#if 0 // Done in CPSVGSVGElement
			CComPtr<ILSVGPoint> currentTranslate;
			psvgsvgElement->get_currentTranslate(&currentTranslate);

			double currentScale;
			psvgsvgElement->get_currentScale(&currentScale);

			double x, y;
			currentTranslate->get_x(&x);
			currentTranslate->get_y(&y);
			pC.m_pGraphics->TranslateTransform(x, y);
#endif

			CComQIPtr<ILSVGGlyphElement> glyphElement = pPElement->m_pNode;

			if (glyphElement)	// y is up
			{
				pC.m_pGraphics->ScaleTransform(magnify, -magnify);
			}
			else
			{
				pC.m_pGraphics->ScaleTransform(magnify/**currentScale*/, magnify/**currentScale*/);
			}

#if 0	// Have something like this
			{
				gmMatrix3& matrix = m_pMatrix->m_matrix;

				LDraw::Matrix gdipmatrix(
					(float)matrix[0][0], (float)matrix[0][1],
					(float)matrix[1][0], (float)matrix[1][1],
					(float)matrix[2][0], (float)matrix[2][1]);
				pC.m_pGraphics->MultiplyTransform(&gdipmatrix);
			}
#endif

			pPElement->Render4(&pC, NULL, pC.m_pGraphics, pPElement->m_scaleX*magnify, pPElement->m_scaleY*magnify, FALSE, TRUE);

#if 0
			pC.m_pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighQuality/*pGraphics->GetSmoothingMode()*/);
			pPElement->RenderSelection(&pC);
#endif

			pC.m_pGraphics->Restore(state);
		}
	}
#endif
#endif
	return Success;
}
#endif

long CEXMLLayoutView::OnLButtonDown()
{
	ASSERT(0);
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	if (m_bShowRulers)
	{
		if (point.y < 16 || point.x < 16)
		{
			if (TRUE)
			{
				if (point.y < 16 && point.x < 16)	// corner
				{
				}
				else
				{
					if (point.y < 16)
					{
						m_dragging = -10;	// Horizontal guide
					}
					else
					{
						m_dragging = -11;	// Vertical guide
					}
				}
			}
			else
			{
				if (point.y < 8)
				{
					if (abs(point.x-(m_marginLeft+m_textIndent)) < 4)
					{
						m_dragging = -1;
					}
				}
				else if (point.y < 15)
				{
					if (abs(point.x-m_marginLeft) < 4)
					{
						m_dragging = -2;
					}
					else if (abs(point.x-(client.right-m_marginRight)) < 4)
					{
						m_dragging = -4;
					}
				}
				else
				{
					if (abs(point.x-m_marginLeft) < 4)
					{
						m_dragging = -3;
					}
				}
			}

			if (m_dragging)
			{
				m_oldpoint = point;

#if 0	// Had this
				SetCapture();
#endif
			}
		}
	}
#endif
	return 0;
}

long CEXMLLayoutView::OnLButtonUp()
{
	ASSERT(0);
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_dragging)
	{
		ReleaseCapture();

		if (m_dragging < 0)
		{
			if (m_dragging <= -10)	// Creating guides
			{
				if (point.y < 16)
				{
					CLayoutViewOptionsDlg dlg;
					dlg.m_horRulerUnits = m_horRulerUnits;
					dlg.m_verRulerUnits = m_verRulerUnits;

					if (dlg.DoModal() == IDOK)
					{
						m_horRulerUnits = dlg.m_horRulerUnits;
						m_verRulerUnits = dlg.m_verRulerUnits;

						Invalidate();
					}
				}
				else
				{
					CComPtr<Web::Document> document;
					m_viewGroup->m_pDocument->get_DOMDocument(&document);

					CComPtr<Web::Element> activeParentNode;
					CComPtr<Web::Node> beforeNode;
					GetNewElementInsertionAt(m_viewGroup, &activeParentNode, &beforeNode);

					CComPtr<Web::Element> pathElement;
					document->createElementNS(L"http://www.w3.org/2000/svg", L"path", &pathElement);
					if (pathElement)
					{
						pathElement->setAttributeNS(NULL, L"guide", L"yes");	// TODO, private namespace

						CComQIPtr<ILSVGAnimatedPathData> pathData = pathElement;

						CComPtr<ILSVGPathSegList> seglist;
						pathData->get_pathSegList(&seglist);

						if (m_dragging == -10)
						{
							double y = point.y-16;
							seglist->AddLine(-5000, y, 5000, y);
						}
						else
						{
							double x = point.x-16;
							seglist->AddLine(x, -5000, x, 5000);
						}

						activeParentNode->insertBefore(pathElement, CComVariant(beforeNode), NULL);
					}
				}
			}
			else
			{
				CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

				CComPtr<ILHTMLWindow> window;
				view->GetHTMLWindow(&window);

				CComQIPtr<ILDOMViewCSS> viewCSS = window;

				CComPtr<ILDOMRange> range;
				window->get_selection(&range);

				if (range)
				{
					CComPtr<Web::Node> startContainer;
					range->get_startContainer(&startContainer);

					//double textIndent = -999999;

					CComQIPtr<Web::Element> element;

				// Find nearest ancestor element that is a block element
					CComPtr<Web::Node> parent = startContainer;
					while (parent)
					{
						element = parent;
						if (element)
						{
							CComPtr<ILCSSStyleDeclaration> computedStyle;
							viewCSS->getComputedStyle(element, L"", &computedStyle);

							CComBSTR display;
							computedStyle->getPropertyValue(L"display", &display);

							if (!wcscmp(display, L"block"))	// TODO Add more
							{
								break;
							}
						}

						CComPtr<Web::Node> parentNode;
						parent->get_parentNode(&parentNode);
						parent = parentNode;
					}

					if (element)
					{
						CComQIPtr<ILElementCSSInlineStyle> stylable = element;
						if (stylable)
						{
							CComPtr<ILCSSStyleDeclaration> style;
							stylable->get_style(&style);

							WCHAR buf[64];

							if (m_dragging == -1)	// text-indent
							{
								m_textIndent = (double)m_oldpoint.x-m_marginLeft;
								swprintf(buf, L"%gpx", (double)m_textIndent);
								style->setProperty(L"text-indent", buf, NULL);
							}
							else if (m_dragging == -2)	// margin-left/text-indent
							{
								m_textIndent = m_textIndent + (m_marginLeft-m_oldpoint.x);
								swprintf(buf, L"%gpx", (double)m_textIndent);
								style->setProperty(L"text-indent", buf, NULL);

								m_marginLeft = (double)m_oldpoint.x;
								swprintf(buf, L"%gpx", (double)m_marginLeft);
								style->setProperty(L"margin-left", buf, NULL);
							}
							else if (m_dragging == -3)	// margin-left
							{
								m_marginLeft = (double)m_oldpoint.x;
								swprintf(buf, L"%gpx", (double)m_marginLeft);
								style->setProperty(L"margin-left", buf, NULL);
							}
							else if (m_dragging == -4)	// margin-right
							{
								m_marginRight = (double)client.right-m_oldpoint.x;
								swprintf(buf, L"%gpx", (double)m_marginRight);
								style->setProperty(L"margin-right", buf, NULL);
							}
						}
					}
				}
			}
		}

		m_dragging = 0;
	}
#endif

	return 0;
}

long CEXMLLayoutView::OnMouseMove()
{
	ASSERT(0);
#if 0
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging < 0)
	{
		if (m_dragging <= -10)
		{
			//CComPtr<ILHTMLActiveView> oleActiveView;
			//window->GetOleView(&oleActiveView);

			CComQIPtr<IOleWindow> window = m_pIOleDocView;
			UI::Control* hwnd;
			window->GetWindow(&hwnd);

			CRect client;
			GetClientRect(&client);

			CClientDC dc(hwnd);

			dc.SetROP2(R2_NOTXORPEN);

			if (m_dragging == -10)
			{
				{
					int y = m_oldpoint.Y-16;
					dc.MoveTo(0, y);
					dc.LineTo(client.right, y);
				}

				{
					int y = point.Y-16;
					dc.MoveTo(0, y);
					dc.LineTo(client.right, y);
				}
			}
			else
			{
				{
					int x = m_oldpoint.X-16;
					dc.MoveTo(x, 0);
					dc.LineTo(x, client.bottom);
				}

				{
					int x = point.X-16;
					dc.MoveTo(x, 0);
					dc.LineTo(x, client.bottom);
				}
			}
		}
		else
		{
			CRect client;
			GetClientRect(&client);

			InvalidateRect(&CRect(0, 0, client.right, 22));
		}
	}

	m_oldpoint = point;
#endif
	return 0;
}

void LHTMLEXT GetTransformRectBoundingBox(const LDraw::matrix3f& mat, const LDraw::RectD& bounds, LDraw::RectD* pVal);

#if 0
{
	ASSERT(pVal != NULL);

	LDraw::PointD pts[4] =
	{
		LDraw::PointD(bounds.X, bounds.Y),
		LDraw::PointD(bounds.X+bounds.Width, bounds.Y),
		LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height),
		LDraw::PointD(bounds.X, bounds.Y+bounds.Height),
	};

	double minx = 999999999;
	double miny = 999999999;
	double maxx = -999999999;
	double maxy = -999999999;

	for (int i = 0; i < 4; i++)
	{
		LDraw::PointD xpt = mat.transform(pts[i]);

		if (xpt.X < minx) minx = xpt.X;
		if (xpt.Y < miny) miny = xpt.Y;
		if (xpt.X > maxx) maxx = xpt.X;
		if (xpt.Y > maxy) maxy = xpt.Y;
	}

	pVal->X = minx;
	pVal->Y = miny;
	pVal->Width = maxx-minx;
	pVal->Height = maxy-miny;
}
#endif

void CEXMLLayoutView::CopyTargetObjectsToClipboard(IDataObject* dataObject)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	double minx = 999999999;
	double miny = 999999999;
	double maxx = -999999999;
	double maxy = -999999999;

	for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
	{
		CComPtr<IEElement> eElement;
		m_viewGroup->m_targetElements[i]->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComPtr<ILSVGMatrix> _ctm;
		window->svgGetScreenCTM(CComQIPtr<ILSVGElement>(element), &_ctm);
		SVGMatrix screenctm = _ctm;

		CComPtr<ILSVGRect> _bbox;
		window->svgGetRBBox(CComQIPtr<ILSVGElement>(element), &_bbox);
		SVGRect bbox = _bbox;

		//CComPtr<IPDMatrix> ctm;
		//object->getScreenCTM(&ctm);

		LDraw::RectD xbbox;
		GetTransformRectBoundingBox(screenctm, bbox, &xbbox);

		minx = min(minx, xbbox.X);
		miny = min(miny, xbbox.Y);
		maxx = max(maxx, xbbox.X+xbbox.Width);
		maxy = max(maxy, xbbox.Y+xbbox.Height);
	}

	LDraw::RectD objectsBoundingBox(minx,miny,maxx-minx,maxy-miny);

	if (/*m_pActiveObject &&*/ objectsBoundingBox.Width > 0 && objectsBoundingBox.Height > 0)
	{
		HDC hDC = ::GetDC(NULL);
		long inchesPerPixelX = GetDeviceCaps(hDC, LOGPIXELSX);
		long inchesPerPixelY = GetDeviceCaps(hDC, LOGPIXELSY);
		::ReleaseDC(NULL, hDC);

		long ppi = inchesPerPixelX;
		LDraw::Color bgColor = LDraw::Color(0, 0, 0, 0);

		int pixelWidth = (int)ceil(objectsBoundingBox.Width*ppi/inchesPerPixelX);
		int pixelHeight = (int)ceil(objectsBoundingBox.Height*ppi/inchesPerPixelY);

		//CComPtr<IPDContentGraphic> contentGraphic;
		//m_document->createContentGraphic(&contentGraphic);

		double scaleX = (double)inchesPerPixelX/ppi;
		double scaleY = (double)inchesPerPixelY/ppi;

		LDraw::Bitmap* pBitmap32 = NULL;
		pBitmap32 = new LDraw::Bitmap(pixelWidth, pixelHeight, PixelFormat32bppARGB);
		if (pBitmap32)
		{
			{
				LDraw::Graphics graphics(pBitmap32);
				graphics.Clear(bgColor);
			}

			LDraw::BitmapData bitmapdata;
			if (pBitmap32->LockBits(
				&LDraw::Rect(0, 0, pBitmap32->GetWidth(), pBitmap32->GetHeight()),
				LDraw::ImageLockModeRead | LDraw::ImageLockModeWrite,
				PixelFormat32bppARGB, &bitmapdata) == 0)
			{
				//renderer->put_targetHDC((HDC)&graphics);
				//renderer->put_magnify(1/scaleX);

			//	graphics.ScaleTransform(1/scaleX, 1/scaleY);
			//	graphics.TranslateTransform(-objectsBoundingBox.X, -objectsBoundingBox.Y);

				for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
				{
					CComPtr<IEElement> eElement;
					m_viewGroup->m_targetElements[i]->get_eElement(&eElement);

					CComPtr<Web::Element> element;
					eElement->get_domElement(&element);

					CComPtr<ILSVGMatrix> ctm;
					window->svgGetScreenCTM(CComQIPtr<ILSVGElement>(element), &ctm);

					window->svgDrawElementToBuffer(CComQIPtr<ILSVGElement>(element), ctm, bitmapdata.Width, bitmapdata.Height, bitmapdata.Stride, bitmapdata.PixelFormat, (void*)bitmapdata.Scan0);
				}

				pBitmap32->UnlockBits(&bitmapdata);
			}
			else
			{
				delete pBitmap32;
				pBitmap32 = NULL;
			}
		}

		if (pBitmap32)
		{
			LDraw::Bitmap* pBitmap24 = new LDraw::Bitmap(pBitmap32->GetWidth(), pBitmap32->GetHeight(), PixelFormat24bppRGB);
			if (pBitmap24)
			{
				{
					LDraw::Graphics graphics(pBitmap24);
					graphics.Clear(LDraw::Color(255,255,255));
					graphics.DrawImage(pBitmap32, 0, 0);
				}

				//CComQIPtr<IPDApplicationSettings> appSettings = gIApp;

				VARIANT_bool bBitmap = VARIANT_TRUE;

				VARIANT_bool bPng = VARIANT_TRUE;
				//appSettings->get_clipboardSavePNG(&bPng);

				VARIANT_bool bJpeg = VARIANT_TRUE;
				//appSettings->get_clipboardSaveJPEG(&bJpeg);

				VARIANT_bool bGif = VARIANT_TRUE;
				//appSettings->get_clipboardSaveGIF(&bGif);

				if (bBitmap)
				{
					STGMEDIUM stgm;
					stgm.tymed = TYMED_GDI;
					stgm.pUnkForRelease = NULL;

					LDraw::Color colorBackground = LDraw::Color(255, 255, 255);
					pBitmap24->GetHBITMAP(colorBackground, &stgm.hBitmap);
					if (stgm.hBitmap)
					{
						FORMATETC etc = { CF_BITMAP, NULL, DVASPECT_CONTENT, -1, TYMED_GDI};

						dataObject->SetData(&etc, &stgm, TRUE);
					}
				}

				if (bPng)
				{
					STGMEDIUM stgm;
					stgm.tymed = TYMED_ISTREAM;
					stgm.pUnkForRelease = NULL;
					if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &stgm.pstm)))
					{
						CLSID pngClsid;
						GetEncoderClsid(L"image/png", &pngClsid);

						LDraw::Status stat = pBitmap32->Save(stgm.pstm, &pngClsid);
						if(stat == LDraw::Ok)
						{
							FORMATETC etc = { _clipboardFormats.cfPng, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

							dataObject->SetData(&etc, &stgm, TRUE);
						}
					}
				}

				if (bJpeg)
				{
					STGMEDIUM stgm;
					stgm.tymed = TYMED_ISTREAM;
					stgm.pUnkForRelease = NULL;
					if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &stgm.pstm)))
					{
						CLSID pngClsid;
						GetEncoderClsid(L"image/jpeg", &pngClsid);

						LDraw::Status stat = pBitmap24->Save(stgm.pstm, &pngClsid);
						if (stat == LDraw::Ok)
						{
							FORMATETC etc = { _clipboardFormats.cfJpeg, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

							dataObject->SetData(&etc, &stgm, TRUE);
						}
					}
				}

				if (bGif)
				{
					STGMEDIUM stgm;
					stgm.tymed = TYMED_ISTREAM;
					stgm.pUnkForRelease = NULL;
					if (SUCCEEDED(CreateStreamOnHGlobal(NULL, TRUE, &stgm.pstm)))
					{
						CLSID pngClsid;
						GetEncoderClsid(L"image/gif", &pngClsid);

						LDraw::Status stat = pBitmap24->Save(stgm.pstm, &pngClsid);
						if (stat == LDraw::Ok)
						{
							FORMATETC etc = { _clipboardFormats.cfGif, NULL, DVASPECT_CONTENT, -1, TYMED_ISTREAM};

							dataObject->SetData(&etc, &stgm, TRUE);
						}
					}
				}

				delete pBitmap24;
			}

			delete pBitmap32;
		}
	}
#endif
}

// Web::EventListener
void CEXMLLayoutView::handleEvent(Web::Event* evt)
{
	ASSERT(0);
#if 0
	CComBSTR type;
	evt->get_type(&type);

	if (!wcscmp(type, L"select"))
	{
		CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<Web::Document> document;
		window->get_document(&document);

		CComPtr<ILDOMRange> range;
		window->get_selection(&range);

		if (range)
		{
			CEXMLViewGroup* pViewGroup = m_viewGroup;

			pViewGroup->SetCurrentSelectionCSSStyle();	// Do somewhere else ??

			for (int i = 0; i < pViewGroup->m_views.GetSize(); i++)
			{
				CComQIPtr<ISourceView> sourceView = pViewGroup->m_views[i];
				if (sourceView)
				{
					((CSourceView*)sourceView.p)->SetRange(range);
				}
			}

			{
				CEXMLDocument* eDocument;
				m_viewGroup->get_eXMLDocument(&eDocument);

				CComPtr<Web::Node> commonAncestor;
				range->get_commonAncestorContainer(&commonAncestor);

				CComQIPtr<Web::Element> element;
				while (commonAncestor != NULL)
				{
					element = commonAncestor;
					if (element)
						break;

					CComPtr<Web::Node> parentNode;
					commonAncestor->get_parentNode(&parentNode);
					commonAncestor = parentNode;
				}

				if (element)
				{
					CComPtr<IEElement> eElement;
					eDocument->GetEElementFromDOMElement(element, &eElement);

					m_viewGroup->ActivateElement(eElement, 0, NULL);
				}
			}

			m_markupBar.BuildMarkupTree(range);

			{
				CComQIPtr<ILDOMViewCSS> viewCSS = window;

				CComPtr<Web::Node> startContainer;
				range->get_startContainer(&startContainer);

				if (startContainer)
				{
					CComQIPtr<Web::Element> element = startContainer;
					if (element == NULL)
					{
						CComPtr<Web::Node> parentNode;
						startContainer->get_parentNode(&parentNode);
						element = parentNode;
					}

					if (element)
					{
						CComPtr<ILCSSStyleDeclaration> computedStyle;
						viewCSS->getComputedStyle(element, NULL, &computedStyle);

						{
							CComPtr<ILCSSPrimitiveValue> cssvalue;
							computedStyle->getPropertyCSSValue(L"margin-left", (ILCSSValue**)&cssvalue);

							cssvalue->getFloatValue(CSS_PX, &m_marginLeft);
						}

						{
							CComPtr<ILCSSPrimitiveValue> cssvalue;
							computedStyle->getPropertyCSSValue(L"text-indent", (ILCSSValue**)&cssvalue);

							cssvalue->getFloatValue(CSS_PX, &m_textIndent);
						}

						{
							CComPtr<ILCSSPrimitiveValue> cssvalue;
							computedStyle->getPropertyCSSValue(L"margin-right", (ILCSSValue**)&cssvalue);

							cssvalue->getFloatValue(CSS_PX, &m_marginRight);
						}
					}
				}
			}
		}

		CRect client;
		GetClientRect(&client);

		{
			InvalidateRect(&CRect(0, 0, client.right, 22));
		}

		{

			CRect rect = client;
			rect.top = rect.bottom-16;

			InvalidateRect(&rect);
		}
	}
#endif

}

#if 0
void __stdcall CEXMLLayoutView::OnSelect(/*Web::Event* evt*/)
{
	/*
	CComQIPtr<ILHTMLActiveDocument> htmlActiveDoc = m_spUnknown;

	CComPtr<ILDOMRange> range;
	htmlActiveDoc->get_selection(&range);
	*/
}
#endif

ErrorCode __stdcall CEXMLLayoutView::OnDOMEvent(Web::Event* evt)
{
	return Success;
}

#if 0
/*
 * CImpIOleDocumentsite::ActivateMe
 *
 * Purpose:
 *  Instructs the container to activate the object in this site as
 *  a document object.
 *
 * Parameters:
 *  pView           IOleDocumentView * of the object to activate.
 *
 * Return Value:
 *  ErrorCode         NOERROR if successful, error code otherwise.
 */
ErrorCode STDMETHODCALLTYPE EXMLLayoutView::ActivateMe(/* [in] */ IOleDocumentView __RPC_FAR *pView)
{
	RECT rc;

	/*
	* If we're passed a NULL view pointer, then try to get one from
	* the document object (the object within us).
	*/
	if (pView == NULL)
	{
		CComQIPtr<IOleDocument> oleDocument = m_spUnknown;

		ErrorCode hr = oleDocument->CreateView(this, m_pIStream, 0, &m_pIOleDocView);
		if (FAILED(hr)) return hr;
	}
	else
	{
		m_pIOleDocView = pView;	// Hold on to view

		//Make sure that the view has our client site
		m_pIOleDocView->SetInPlaceSite(this);

		////We're holding onto the pointer, so AddRef it.
		//pView->AddRef();
	}

	/*
	* Activation steps, now that we have a view:
	*
	*  1.  Call IOleDocumentView::SetInPlaceSite (assume done since
	*      either the view already knows, or IOleDocument::CreateView
	*      has done it already.
	*
	*  2.  Call IOleDocumentView::SetRect to give a bunch of space to
	*      the view.  In our case this is the whole client area of
	*      the CPages window.  (Patron doesn't use SetRectComplex)
	*
	*  3.  Call IOleDocumentView::Show to make the thing visible.
	*
	*  4.  Call IOleDocumentView::UIActivate to finish the job.
	*
	*/
	
#if 0
	m_pSite->m_fDocObj=TRUE;
	m_pSite->m_pIOleDocView=pView;
	
#endif

	//This sets up toolbars and menus first    
	m_pIOleDocView->UIActivate(TRUE);

	//Set the window size sensitive to new toolbars
	GetClientRect(&rc);
	m_pIOleDocView->SetRect(&rc);

	//Makes it all active
	m_pIOleDocView->Show(TRUE);    

	return NOERROR;
}
#endif

#if 0
/*
 * CImpIOleInPlaceSite::OnInPlaceActivate
 *
 * Purpose:
 *  Informs the container that an object is being activated in-place
 *  such that the container can prepare appropriately.  The
 *  container does not, however, make any user interface changes at
 *  this point.  See OnUIActivate.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  ErrorCode         NOERROR or an appropriate error code.
 */
ErrorCode STDMETHODCALLTYPE CEXMLLayoutView::OnInPlaceActivate( void)
{
	ASSERT(0);
#if 0
   m_pIOleIPObject = m_spUnknown;
	ASSERT(m_pIOleIPObject != NULL);
#endif

    return NOERROR;
}

/*
 * CImpIOleInPlaceSite::GetWindowContext
 *
 * Purpose:
 *  Provides an in-place object with pointers to the frame and
 *  document level in-place interfaces (IOleInPlaceFrame and
 *  IOleInPlaceUIWindow) such that the object can do border
 *  negotiation and so forth.  Also requests the position and
 *  clipping rectangles of the object in the container and a
 *  pointer to an OLEINPLACEFRAME info structure which contains
 *  accelerator information.
 *
 *  Note that the two interfaces this call returns are not
 *  available through QueryInterface on IOleInPlaceSite since they
 *  live with the frame and document, but not the site.
 *
 * Parameters:
 *  ppIIPFrame      LPOLEINPLACEFRAME * in which to return the
 *                  AddRef'd pointer to the container's
 *                  IOleInPlaceFrame.
 *  ppIIPUIWindow   LPOLEINPLACEUIWINDOW * in which to return
 *                  the AddRef'd pointer to the container document's
 *                  IOleInPlaceUIWindow.
 *  prcPos          LPRECT in which to store the object's position.
 *  prcClip         LPRECT in which to store the object's visible
 *                  region.
 *  pFI             LPOLEINPLACEFRAMEINFO to fill with accelerator
 *                  stuff.
 *
 * Return Value:
 *  ErrorCode         NOERROR
 */

ErrorCode STDMETHODCALLTYPE CEXMLLayoutView::GetWindowContext( 
																	/* [out] */ IOleInPlaceFrame __RPC_FAR *__RPC_FAR *ppFrame,
																	/* [out] */ IOleInPlaceUIWindow __RPC_FAR *__RPC_FAR *ppDoc,
																	/* [out] */ LPRECT prcPos,
																	/* [out] */ LPRECT prcClip,
																	/* [out][in] */ LPOLEINPLACEFRAMEINFO pFI)
{
	ASSERT(0);
#if 0
//	CComQIPtr<IWebEditorFrame> frame;
//	gApp->m_frame;get_frame(&frame);

	*ppFrame = gApp->m_frame;
//	frame->QueryInterface(IID_IOleInPlaceFrame, (void**)ppFrame);
//	ASSERT(*ppFrame != NULL);
	(*ppFrame)->AddRef();

	//*ppDoc = NULL;
	if (ppDoc)
	{
		*ppDoc = this;
		(*ppDoc)->AddRef();
	}
//	QueryInterface(IID_IOleInPlaceUIWindow, (void**)ppDoc);
//	ASSERT(*ppDoc != NULL);

	if (prcPos != NULL) GetClientRect(prcPos);
	if (prcClip) *prcClip=*prcPos;
	
	if (pFI)
	{
		pFI->cb=sizeof(OLEINPLACEFRAMEINFO);
		pFI->fMDIApp=TRUE;
	// ??
		pFI->hwndFrame = gApp->m_frame->m_hWnd;//frame->get_hwnd(&pFI->hwndFrame);//=m_pSite->m_pFR->Window();

		pFI->haccel=NULL;//m_pSite->m_pFR->Accelerators();
		pFI->cAccelEntries=0;//CACCELERATORS;
	}
#endif

	return NOERROR;
}
#endif

#if 0
ErrorCode CEXMLLayoutView::GetInMemoryDocument(BSTR uri, Web::Document* *pVal)
{
#if 0
	ASSERT(pVal);
	if (pVal == NULL) return E_POINTER;

	CComQIPtr<IEDocument> document;

	for (int i = 0; i < gApp->m_documents.GetSize(); i++)
	{
		BSTR pathName2;
		gApp->m_documents[i]->get_filePath(&pathName2);
		if (!wcsicmp(uri, pathName2))
		{
			document = gApp->m_documents[i];
			break;
		}
	}

	CComQIPtr<IEXMLDocument> xmldocument = document;
	if (xmldocument)
	{
		return xmldocument->get_DOMDocument(pVal);
	}
	else
		*pVal = NULL;
#endif
	return Success;
}
#endif

#if 0
CComPtr<IHlinkBrowseContext> EXMLLayoutView::GetBrowseContext()
{
	if(m_pIHlinkBrowseContext==NULL)
	{
		IHlinkFramePtr phlFrame=GetHlinkFrame();
		if (phlFrame!=NULL)
		    phlFrame->GetBrowseContext(&m_pIHlinkBrowseContext);

		if(m_pIHlinkBrowseContext==NULL)
			HlinkCreateBrowseContext(NULL,IID_IHlinkBrowseContext,(void**)&m_pIHlinkBrowseContext);

		if (m_pIHlinkBrowseContext != NULL)
		{	
			// register with the browse context
			IMonikerPtr pMoniker;
			pMoniker.Attach(GetMoniker(OLEGETMONIKER_FORCEASSIGN));
			m_pIHlinkBrowseContext->Register(0,
											GetInterface((void*)&IID_IUnknown), 
											pMoniker, 
											&m_dwBrowseContextRegister);

			// because we want the user to be able to come back to this
			// object via GoBack functionality add self to the 
			// navigation stack. This effectively tells the browse context
			// that the current hyperlink container referred to by pMoniker 
			// is a member (at the top) of the navigation stack
			AddCurrentLocationToBrowseContext(GetViewForNavigate());
		}
		else
			abort();
	}

	return m_pIHlinkBrowseContext;
}
#endif

#if 0
// IHlinkSite
ErrorCode CEXMLLayoutView::QueryService(DWORD dwSiteData, REFGUID guidService,
	REFIID riid, IUnknown __RPC_FAR *__RPC_FAR *ppiunk)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLLayoutView::GetMoniker(DWORD dwSiteData, DWORD dwAssign,
	DWORD dwWhich, IMoniker __RPC_FAR *__RPC_FAR *ppimk)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLLayoutView::ReadyToNavigate(DWORD dwSiteData, DWORD dwReserved)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLLayoutView::OnNavigationComplete(DWORD dwSiteData, DWORD dwreserved,
	ErrorCode hrError, LPCWSTR pwzError)
{
	return E_NOTIMPL;
}

// IHlinkTarget
ErrorCode CEXMLLayoutView::SetBrowseContext(IHlinkBrowseContext* pihlbc)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLLayoutView::GetBrowseContext(IHlinkBrowseContext** ppihlbc)
{
	//Here we do no call GetBrowseContext to avoid allocation
	//of the new context in case of absence of the one
	*ppihlbc = m_pIHlinkBrowseContext;
	if(*ppihlbc)
	{
		(*ppihlbc)->AddRef();
		return Success;
	}

	return E_FAIL;
}

ErrorCode CEXMLLayoutView::Navigate(DWORD grfHLNF, LPCWSTR pwzJumpLocation)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLLayoutView::GetMoniker(LPCWSTR pwzLocation, DWORD dwAssign, IMoniker** ppimkLocation)
{
	return E_NOTIMPL;
}

ErrorCode CEXMLLayoutView::GetFriendlyName(LPCWSTR pwzLocation, LPWSTR* ppwzFriendlyName)
{
	return E_NOTIMPL;
}
#endif

void CEXMLLayoutView::ClearSelection()
{
	ISVGTool* activeTool;
	m_viewGroup->m_pDocument->m_app->GetActiveTool(false, &activeTool);

	long toolID = 0;
	if (activeTool)
	{
		m_viewGroup->m_pDocument->m_app->GetToolID(activeTool, &toolID);
	}

#if 0
	LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));

	long activeTool;

	if (m_dragging)
	{
		activeTool = m_activeTool;
	}
	else
	{
		if (!bCtrl)
			activeTool = gApp->m_activeTool;
		else
			activeTool = gApp->m_activeSelectionTool;
	}

	if (m_pActiveObject)
	{
		CComQIPtr<IPDObjectText> contentText;

		if (activeTool == ID_TOOL_TEXT)
		{
			CComQIPtr<IPDObjectFrame> frame = m_pActiveObject->m_object;
			if (frame)
			{
				CComPtr<IPDObject> content;
				frame->get_content(&content);
				contentText = content;
			}
			else
				contentText = m_pActiveObject->m_object;
		}

		if (contentText)
		{
			if (m_range)
			{
				m_range->Delete(tomCharacter, 0, NULL);
#if 0
				CComPtr<IRange> domrange;
				m_range->GetDOMRange(&domrange);

// TODO here, have a method on m_range
				domrange->deleteContents();

				CComPtr<IDOMNode> startContainer;
				long startOffset;
				domrange->get_startContainer(&startContainer);
				domrange->get_startOffset(&startOffset);

				m_range->Set(startContainer, startOffset);
				/*
				m_curContainer = startContainer;
				m_curOffset = startOffset;
				m_initContainer = startContainer;
				m_initOffset = startOffset;
				*/
#endif
				Invalidate();	// TODO remove this
			}
		}
		else
#endif
			if (toolID == ID_SVGTOOL_DIRECT)
		{
			for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
			{
				m_viewGroup->m_targetElements[i]->DeleteSelection();
				/*
				CComQIPtr<IESelectedSVGPathElement> pathSelection = m_viewGroup->m_targetElements[i];

				if (pathSelection)
				{
					static_cast<CESelectedSVGPathElement*>(pathSelection.p)->DeleteSelection();
				}
				*/
			}

	//		m_pActivePath = NULL;
	//		m_curveCp = -1;
		}
		else
		{
			ClearTargetObjects();
		}
	//}
}

void CEXMLLayoutView::ClearTargetObjects()
{
	ASSERT(0);
#if 0
	CComQIPtr<IEDocument> eDocument = m_viewGroup->m_pDocument;

	CComQIPtr<IOleUndoManager> undoManager;
	eDocument->get_undoManager(&undoManager);

	CComObject<CWEUndoDeleteObjects>* pUndo;
	CComObject<CWEUndoDeleteObjects>::CreateInstance(&pUndo);
	if (pUndo)
	{
		pUndo->m_pDocument = m_viewGroup->m_pDocument;
		pUndo->m_bRedo = true;

		/*
		CElement* pParentElement = (CElement*)m_pActiveSelection->m_parent;

		CComPtr<Web::Node> domParentNode;
		pParentElement->m_eElement->get_domNode(&domParentNode);

		GUID parentGuid;
		domParentNode->get_uniqID(&parentGuid);
		*/

		for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
		{
			CComPtr<IEElement> eElement;
			m_viewGroup->m_targetElements[i]->get_eElement(&eElement);

			CComPtr<Web::Node> domNode;
			eElement->get_domNode(&domNode);
			GUID guid;
			domNode->get_uniqID(&guid);

			CComPtr<Web::Node> domParentNode;
			domNode->get_parentNode(&domParentNode);
			GUID parentGuid;
			domParentNode->get_uniqID(&parentGuid);

			pUndo->m_targetElements.Add(guid);
			pUndo->m_parentElements.Add(parentGuid);

			CComPtr<Web::Node> domBeforeNode;
			domNode->get_nextSibling(&domBeforeNode);

			if (domBeforeNode != NULL)
			{
				domBeforeNode->get_uniqID(&guid);
				pUndo->m_beforeElements.Add(guid);
			}
			else
			{
				pUndo->m_beforeElements.Add(GUID_NULL);
			}
		}

		pUndo->Do(undoManager);
	}

#if 0
	if (m_pActiveObject)
	{
		CComQIPtr<IOleUndoManager> undoManager;
		m_document->get_undoManager(&undoManager);

		CComObject<CUndoClearObjects>* pUndo;
		CComObject<CUndoClearObjects>::CreateInstance(&pUndo);
		if (pUndo)
		{
			pUndo->AddRef();
			pUndo->m_document = m_document;
			m_activeSpread->get_uniqId(&pUndo->m_spreadGUID);
			pUndo->m_pView = this;
			pUndo->m_bRedo = true;

			CComQIPtr<IPDObjectUnknown> objectChild = m_pActiveObject->m_object;

			CComPtr<IPDObjectUnknown> parentUnknown;
			objectChild->get_parent(&parentUnknown);

			CComQIPtr<IPDObjectWithChildren> parent = parentUnknown;

			GUID parentGuid;
			parentUnknown->get_uniqId(&parentGuid);

			CComPtr<IObjectMap> children;
			parent->get_children(&children);

			long length;
			children->get_length(&length);

			for (long i = 0; i < length; i++)
			{
				CComPtr<IPDObjectUnknown> objectUnknown;
				children->item(i, (IUnknown**)&objectUnknown);

				if (IsPDObjectSelected(objectUnknown))
				{
					objectUnknown.p->AddRef();
					int refcount = objectUnknown.p->Release();

					GUID guid;

					//CComQIPtr<IPDObjectChild> objectChild = objectUnknown;

					CComPtr<IPDObjectUnknown> beforeNode;
					objectChild->get_nextSibling(&beforeNode);

					//CComQIPtr<IPDObjectUnknown> beforeNode = beforeNodeChild;

					objectUnknown->get_uniqId(&guid);
					pUndo->m_targetElements.Add(guid);

					pUndo->m_parentElements.Add(parentGuid);

					if (beforeNode != NULL)
					{
						beforeNode->get_uniqId(&guid);
						pUndo->m_beforeElements.Add(guid);
					}
					else
					{
						pUndo->m_beforeElements.Add(GUID_NULL);
					}
				}
			}

			pUndo->Do(undoManager);

			Invalidate();
		}
	}
#endif
#endif
}

BEGIN_CMD_MAP(CEXMLLayoutView)
/*
	CMD_HANDLER(ID_EDIT_COPY, OnEditCopy)
	CMD_HANDLER(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecial)
	CMD_UPDATEUI(ID_EDIT_PASTE_SPECIAL, OnEditPasteSpecialUpdate)
	CMD_HANDLER(ID_EDIT_CLEAR, OnEditClear)
	CMD_UPDATEUI(ID_EDIT_CLEAR, OnEditClearUpdate)

	CMD_HANDLER(ID_VIEW_ZOOMIN, OnViewZoomIn)
	CMD_HANDLER(ID_VIEW_ZOOMOUT, OnViewZoomOut)
	CMD_HANDLER(ID_VIEW_ACTUALSIZE, OnViewActualSize)
	CMD_HANDLER(ID_VIEW_RULERS, OnViewRulers)
	CMD_UPDATEUI(ID_VIEW_RULERS, OnViewRulersUpdate)
	CMD_HANDLER(ID_VIEW_SHOWMARKUP, OnShowMarkup)
	CMD_UPDATEUI(ID_VIEW_SHOWMARKUP, OnShowMarkupUpdate)
	CMD_HANDLER(ID_VIEW_TRANSPARENCYGRID, OnViewTransparencyGrid)
	CMD_UPDATEUI(ID_VIEW_TRANSPARENCYGRID, OnViewTransparencyGridUpdate)

	CMD_HANDLER(ID_VIEW_TRANSFORMPAGE, OnViewTransformPage)

	CMD_HANDLER(ID_VIEW_GUIDES_MAKEGUIDES, OnMakeGuides)
	CMD_HANDLER(ID_VIEW_GUIDES_RELEASEGUIDES, OnReleaseGuides)

	CMD_HANDLER(ID_INSERT_IMAGE, OnInsertImage)
	CMD_HANDLER(ID_TABLE_INSERT_TABLE, OnInsertTable)

	CMD_HANDLER(ID_OBJECT_CONVERTTOPATH, OnObjectConvertToPath)
	CMD_UPDATEUI(ID_OBJECT_CONVERTTOPATH, OnObjectConvertToPathUpdate)

	CMD_HANDLER(ID_OBJECT_ALIGN_HORIZONTALLEFT, OnObjectAlignHorizontalLeft)

	CMD_HANDLER(ID_OBJECT_EDITPAINT, OnEditPaint)
	CMD_HANDLER(ID_OBJECT_EDITMASK, OnObjectEditMask)
	CMD_HANDLER(ID_OBJECT_EDITCLIPPINGPATH, OnObjectEditClippingPath)
	CMD_HANDLER(ID_OBJECT_EDITFILTER, OnObjectEditFilter)
	CMD_UPDATEUI(ID_OBJECT_EDITPAINT, OnObjectEditPaintUpdate)
	CMD_UPDATEUI(ID_OBJECT_EDITMASK, OnObjectEditMaskUpdate)
	CMD_UPDATEUI(ID_OBJECT_EDITCLIPPINGPATH, OnObjectEditClippingPathUpdate)
	CMD_UPDATEUI(ID_OBJECT_EDITFILTER, OnObjectEditFilterUpdate)
	*/
END_CMD_MAP()

long CEXMLLayoutView::OnViewTransformPage(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	if (m_viewGroup->m_pActiveSelection)
	{
		if (m_viewGroup->m_pActiveSelection->m_parent->m_parent)
		{
			CComPtr<IEElement> eElement = ((CElement*)m_viewGroup->m_pActiveSelection->m_parent)->m_eElement;

			CComPtr<Web::Element> element;
			eElement->get_domElement(&element);

			m_rulerElement = element;

			CComPtr<ILSVGMatrix> matrix;
			window->svgGetScreenNCTM2(CComQIPtr<ILSVGElement>(element), &matrix);

			CComPtr<ILSVGMatrix> imat;
			matrix->inverse(&imat);

			window->SetMatrix(imat);
		}
		else
		{
			m_rulerElement = NULL;

			CComPtr<Web::Document> document;
			m_viewGroup->m_pDocument->get_DOMDocument(&document);

			CComPtr<Web::Element> documentElement;
			document->get_documentElement(&documentElement);

			CComQIPtr<ILSVGSVGElement> svgsvgElement = documentElement;

			CComPtr<ILSVGMatrix> matrix;
			svgsvgElement->createSVGMatrix(&matrix);

			window->SetMatrix(matrix);
		}

		Invalidate();
	}
#endif

	return 0;
}

long CEXMLLayoutView::OnEditClear(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ClearSelection();
	return 0;
}

void CEXMLLayoutView::OnEditClearUpdate(long id, UI::IUICmdUpdate* pCmdUI)
{
}

long CEXMLLayoutView::OnEditCopy(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
#if 0
	COleDataObject* dataObject = new COleDataObject;
	if (dataObject)
	{
		dataObject->AddRef();

		CopyTargetObjectsToClipboard(dataObject);

		OleSetClipboard(dataObject);

		dataObject->Release();
	}
#endif
	return 0;
}

long CEXMLLayoutView::OnMakeGuides(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	return 0;
}

long CEXMLLayoutView::OnReleaseGuides(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	return 0;
}

long CEXMLLayoutView::OnObjectAlignHorizontalLeft(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	if (m_viewGroup->m_pActiveElement)
	{
		CComPtr<IEElement> eActiveElement;
		m_viewGroup->m_pActiveElement->get_eElement(&eActiveElement);

		CComPtr<Web::Element> activeElement;
		eActiveElement->get_domElement(&activeElement);

		CComPtr<ILSVGRect> _bbox;
		window->svgGetBBox(CComQIPtr<ILSVGElement>(activeElement), &_bbox);
		SVGRect activebbox = _bbox;

		for (int i = 0; i < m_viewGroup->m_targetElements.GetSize(); i++)
		{
			CComPtr<IEElement> eElement;
			m_viewGroup->m_targetElements[i]->get_eElement(&eElement);

			CComQIPtr<IESVGElement> eSVGElement = eElement;
			if (eSVGElement)
			{
				CComPtr<Web::Element> element;
				eElement->get_domElement(&element);

				CComPtr<ILSVGRect> _bbox;
				window->svgGetBBox(CComQIPtr<ILSVGElement>(element), &_bbox);
				SVGRect bbox = _bbox;

				eSVGElement->Move(m_pBehavior, activebbox.X-bbox.X, 0);
			}
		}
	}
#endif

	return 0;
}

long CEXMLLayoutView::OnViewTransparencyGrid(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	m_bShowTransparencyGrid = !m_bShowTransparencyGrid;

// TODO paintsite invalidate
	return 0;
}

void CEXMLLayoutView::OnViewTransparencyGridUpdate(long id, UI::IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowTransparencyGrid);
}

long CEXMLLayoutView::OnViewRulers(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	m_bShowRulers = !m_bShowRulers;
	OnSize();
	return 0;
}

void CEXMLLayoutView::OnViewRulersUpdate(long id, UI::IUICmdUpdate* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowRulers);
}

long CEXMLLayoutView::OnShowMarkup(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	VARIANT_bool bShowMarkup;
	window->get_showMarkup(&bShowMarkup);

	window->put_showMarkup(~bShowMarkup);
#endif

	return 0;
}

void CEXMLLayoutView::OnShowMarkupUpdate(long id, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	view->GetHTMLWindow(&window);

	VARIANT_bool bShowMarkup;
	window->get_showMarkup(&bShowMarkup);

	pCmdUI->SetCheck(bShowMarkup);
#endif
}

long CEXMLLayoutView::OnInsertTable(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	/*Remember default settings*/static CInsertTableDlg dlg;

	if (dlg.DoModal() == IDOK)
	{
		CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<Web::Document> document;
		window->get_document(&document);

		CComPtr<ILDOMRange> range;
		window->get_selection(&range);
		if (range)
		{
			CComPtr<Web::Element> tableElement;
			document->createElement(L"table", &tableElement);
			if (tableElement)
			{
				tableElement->setAttribute(L"width", L"300");	// TODO
				tableElement->setAttribute(L"border", L"1");	// TODO

				for (int nrow = 0; nrow < dlg.m_rows; nrow++)
				{
					CComPtr<Web::Element> rowElement;
					document->createElement(L"tr", &rowElement);
					if (rowElement)
					{
						for (int ncol = 0; ncol < dlg.m_columns; ncol++)
						{
							CComPtr<Web::Element> colElement;
							document->createElement(L"td", &colElement);

							colElement->put_TextContent(L"test");

							rowElement->appendChild(colElement, NULL);
						}

						tableElement->appendChild(rowElement, NULL);
					}
				}

				range->insertNode(tableElement);
			}
		}
	}
#endif

	return 0;
}

long CEXMLLayoutView::OnInsertImage(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXMLEditorApp> application;
	m_viewGroup->m_pDocument->get_Application(&application);

	CComQIPtr<ILXAddin> addin = application;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	UI::Control* hWnd;
	CComQIPtr<IUIWnd> wnd = lxframe;
	wnd->get_hwnd(&hWnd);

	static LPCTSTR FilesFilter = _T(	"All Files\0*.*\0"
												"All Images (*.png;*.jpg;*.jpeg;*.gif)\0*.png;*.jpg;*.jpeg;*.gif\0"
												);

	TCHAR sbuffer[4096];
	strcpy(sbuffer, "");	// Initial filename
	
	TCHAR curdir[MAX_PATH];
	GetCurrentDirectory(sizeof(curdir), curdir);

	OPENFILENAME	ofn = {0};
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.hInstance = _Module.m_hInst;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrFile = sbuffer;
	ofn.nMaxFile = sizeof(sbuffer);
	ofn.lpstrInitialDir = curdir;
	ofn.lpstrFilter = FilesFilter;
	ofn.nFilterIndex = 2;

	if (GetOpenFileName(&ofn))
	{
		TCHAR* filename = sbuffer;//[256];
		//_splitpath(sbuffer, NULL, NULL, filename, NULL);

		CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

		CComPtr<ILHTMLWindow> window;
		view->GetHTMLWindow(&window);

		CComPtr<Web::Document> document;
		window->get_document(&document);

		CComPtr<ILDOMRange> range;
		window->get_selection(&range);
		if (range)
		{
			CComPtr<Web::Element> imgElement;
			document->createElement(L"img", &imgElement);
			if (imgElement)
			{
				imgElement->setAttribute(L"src", _bstr_t(filename));

				range->insertNode(imgElement);
			}
		}
	}
#endif

	return 0;
}

#include "SVGReadEMF.h"

long CEXMLLayoutView::OnEditPasteSpecial(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<ILXMLEditorApp> application;
	m_viewGroup->m_pDocument->get_Application(&application);

	CComQIPtr<ILXAddin> addin = application;

	CComPtr<ILXAddinSite> addinSite;
	addin->GetSite(&addinSite);

	CComPtr<ILXFrameworkFrame> lxframe;
	addinSite->GetFrame(&lxframe);

	UI::Control* hWnd;
	CComQIPtr<IUIWnd> wnd = lxframe;
	wnd->get_hwnd(&hWnd);

	OLEUIPASTESPECIAL ps = {0};
	ps.cbStruct = sizeof(ps);
	ps.dwFlags = 0;
	ps.hWndOwner = hWnd;
	ps.hInstance = NULL;

	OLEUIPASTEENTRY pasteEntries[8] = {0};
	ps.arrPasteEntries = pasteEntries;

	ps.cPasteEntries = 0;

	/*
	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfRichTextFormat;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_HGLOBAL;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "Rich Text Format";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "Rich Text Format";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}
	*/

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = CF_METAFILEPICT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_MFPICT;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = CF_ENHMETAFILE;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ENHMF;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "Enhanced Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "Enhanced Metafile";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	/*
	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfPng;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ISTREAM;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "PNG";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "PNG";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfJpeg;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ISTREAM;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "JPEG";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "JPEG";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}

	{
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.cfFormat = _clipboardFormats.cfGif;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.dwAspect = DVASPECT_CONTENT;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.lindex = -1;
		ps.arrPasteEntries[ps.cPasteEntries].fmtetc.tymed = TYMED_ISTREAM;
		ps.arrPasteEntries[ps.cPasteEntries].lpstrFormatName = "GIF";
		ps.arrPasteEntries[ps.cPasteEntries].lpstrResultText = "GIF";
		ps.arrPasteEntries[ps.cPasteEntries].dwFlags = 0;
		ps.cPasteEntries++;
	}
	*/

	UINT n = OleUIPasteSpecial(&ps);
	
	if (n == OLEUI_OK)
	{
		/*
		CComPtr<IEnumFORMATETC> enumfmt;
		ps.lpSrcDataObj->EnumFormatEtc(1, &enumfmt);

		FORMATETC fetc;
		DWORD fetched;
		while ((enumfmt->Next(1, &fetc, &fetched) == Success) && fetched)
		{
			TCHAR name[512];
			GetClipboardFormatName(fetc.cfFormat, name, sizeof(name));

			::MessageBox(NULL, name, "clip", MB_OK);
		}
		*/

		STGMEDIUM stgm;
		if (SUCCEEDED(ps.lpSrcDataObj->GetData(&ps.arrPasteEntries[ps.nSelectedIndex].fmtetc, &stgm)))
		{
			/*
			CComQIPtr<IPDObjectLayerGroup> activeLayerGroup;
			if (m_activeSpread)
				m_activeSpread->getLayerGroupFromLayer(m_activeLayer, &activeLayerGroup);
*/
#if 0
			if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.cfFormat == _clipboardFormats.cfRichTextFormat)
			{
				char* p = (char*)GlobalLock(stgm.hGlobal);
				if (p)
				{
					::MessageBox(NULL, p, "rtf", MB_OK);

					CRTFLoader* pRtf = new CRTFLoader;
					if (pRtf)
					{
						CComPtr<IPDObjectFrame> object;
						m_document->createObjectFrame(&object);

						if (object)
						{
							// Set frame path to rectangle
							{
								CComPtr<IPDPath> path;
								object->get_path(&path);
								
								CComPtr<IPDSubPath> subpath;
								path->createSubPath(&subpath);
								subpath->setRectangle(0, 0, 200, 200);
								path->insertSubPath(-1, subpath);	
							}

						// Create new story
							CComPtr<IPDStory> story;
							m_document->createStory(&story);
							if (story)
							{
								CComPtr<Web::Document> document;
								story->get_textDocument(&document);

								CComPtr<Web::DocumentFragment> fragment;
								document->createDocumentFragment(&fragment);

								pRtf->Load(document, fragment, p);

								// Create text Content
								CComPtr<IPDContentText> content;
								m_document->createContentText(&content);
								if (content)
								{
									object->put_content(content);

									// Copy default text frame options
									CComQIPtr<IPDTextFrameOptions> defaultOptions = m_document;
									CComQIPtr<IPDTextFrameOptions> options = content;
									options->copyFrom(defaultOptions);

									story->appendTextThread(content);

								// Copy default properties
									//m_objectSelection->CopyDefaultProperties(object);
									//CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = m_document;
									//object->copyAppearanceFrom(strokeFill);
									CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill2 = m_document;
									CComQIPtr<IPDObjectWithAppearanceAndStrokeFill> strokeFill = object;
									strokeFill->copyAppearanceFrom(VARIANT_TRUE, strokeFill2);

								// Append frame
									activeLayerGroup->appendObject(object);

								// Finally append the story to the document
									m_document->appendStory(story);

									SelectPDObject(object, 0, TRUE);
								}
							}
							else
							{
								::MessageBox(GetMainHwnd(), "Couldn't create story", "PageDesigner", MB_OK);
							}
						}

						delete pRtf;
					}

					GlobalUnlock(stgm.hGlobal);
				}
			}
			else if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.tymed == TYMED_MFPICT)
			{
				LPMETAFILEPICT pmfp = (LPMETAFILEPICT)GlobalLock(stgm.hMetaFilePict); 
				if (pmfp)
				{
					SIZEL sizeInHiMetric;
					sizeInHiMetric.cx = pmfp->xExt;
					sizeInHiMetric.cy = pmfp->yExt;

					SIZEL sizeInPix;
					AtlHiMetricToPixel(&sizeInHiMetric, &sizeInPix);

					UINT nSize = ::GetMetaFileBitsEx(pmfp->hMF, 0, NULL);
//MM_ISOTROPIC
					LPBYTE buffer = (LPBYTE)malloc(nSize);
					if (buffer)
					{
						::GetMetaFileBitsEx(pmfp->hMF, nSize, buffer);

						HENHMETAFILE hemf = ::SetWinMetaFileBits(nSize, buffer, NULL, NULL);

						free(buffer);

						if (hemf)
						{
							CReadEMF* rdemf = new CReadEMF;
							if (rdemf)
							{
								CComPtr<IPDObjectGroup> group;
								rdemf->ReadEMF(hemf, &sizeInPix, m_document, &group);
								if (group)
								{
									activeLayerGroup->appendObject(group);
								}

								delete rdemf;
							}

							DeleteEnhMetaFile(hemf);
						}
					}

					GlobalUnlock(stgm.hMetaFilePict);
				}
			}
			else
#endif
				if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.tymed == TYMED_ENHMF)
			{
				CSVGReadEMF* rdemf = new CSVGReadEMF;
				if (rdemf)
				{
					CComPtr<Web::Document> document;
					m_viewGroup->m_pDocument->get_DOMDocument(&document);

					CComPtr<Web::Element> svgsvgElement;
					document->get_documentElement(&svgsvgElement);

					CComPtr<ILSVGGElement> group;
					rdemf->ReadEMF(stgm.hEnhMetaFile, NULL, document, &group);
					if (group)
					{
						svgsvgElement->appendChild(group, NULL);
					}

					delete rdemf;
				}
			}
#if 0
			else if (ps.arrPasteEntries[ps.nSelectedIndex].fmtetc.tymed == TYMED_ISTREAM)
			{
				CComPtr<IPDImage> image;
				m_document->loadImageFromStream(stgm.pstm, &image);
				if (image)
				{
					CComQIPtr<IPDContentGraphic> contentGraphic;
					m_document->createContentGraphic(&contentGraphic);
					if (contentGraphic)
					{
						contentGraphic->put_image(image);

						activeLayerGroup->appendObject(contentGraphic);
					}
				}
			}
#endif

			ReleaseStgMedium(&stgm);
		}

		ps.lpSrcDataObj->Release();
	}
	else
	{
		ATLTRACE("OleUI error %d\n", n);
	}
#endif

	return 0;
}

void CEXMLLayoutView::OnEditPasteSpecialUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
#if 0
	pCmdUI->Enable(
		/*
						IsClipboardFormatAvailable(_clipboardFormats.cfRichTextFormat) ||*/
						IsClipboardFormatAvailable(CF_ENHMETAFILE) ||
						IsClipboardFormatAvailable(CF_METAFILEPICT)/*||
						IsClipboardFormatAvailable(_clipboardFormats.cfPng) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfJpeg) ||
						IsClipboardFormatAvailable(_clipboardFormats.cfGif*/
	);
#endif
}

long CEXMLLayoutView::OnViewZoomIn(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> htmlView = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	htmlView->GetHTMLWindow(&window);

	long innerWidth;
	long innerHeight;
	window->get_innerWidth(&innerWidth);
	window->get_innerHeight(&innerHeight);

	window->ZoomToRect(
		innerWidth/2-innerWidth/4, innerHeight/2-innerHeight/4,
		innerWidth/2, innerHeight/2,
		VARIANT_TRUE);
#endif

	return 0;
}

long CEXMLLayoutView::OnViewZoomOut(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> htmlView = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	htmlView->GetHTMLWindow(&window);

	long innerWidth;
	long innerHeight;
	window->get_innerWidth(&innerWidth);
	window->get_innerHeight(&innerHeight);

	window->ZoomToRect(
		innerWidth/2-innerWidth, innerHeight/2-innerHeight,
		innerWidth*2, innerHeight*2,
		VARIANT_TRUE);

	/*
	double magnify;
	window->get_magnify(&magnify);

	window->put_magnify(magnify/2);
	*/
#endif

	return 0;
}

long CEXMLLayoutView::OnViewActualSize(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComQIPtr<ILHTMLActiveView> htmlView = m_pIOleDocView;

	CComPtr<ILHTMLWindow> window;
	htmlView->GetHTMLWindow(&window);

	double magnify;
	window->get_magnify(&magnify);

	long innerWidth;
	long innerHeight;
	window->get_innerWidth(&innerWidth);
	window->get_innerHeight(&innerHeight);

	window->ZoomToRect(
		innerWidth/2-innerWidth*magnify/2, innerHeight/2-innerHeight*magnify/2,
		innerWidth*magnify, innerHeight*magnify,
		VARIANT_TRUE);

	window->put_magnify(1);	// In case it's a little bit off
	/*
#ifdef _DEBUG
	window->get_magnify(&magnify);
	ASSERT(magnify == 1);
#endif
	*/
#endif

	return 0;
}

long CEXMLLayoutView::OnEditPaint(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			WCHAR* propertyName = static_cast<CLXMLEditorApp*>(static_cast<CEXMLDocument*>(m_viewGroup->m_pDocument)->m_app.p)->m_strokeOrFill == 0? L"stroke": L"fill";

			CComPtr<ILSVGPaint> cssvalue;
			style->getPropertyCSSValue(propertyName, (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				LSVGPaintType type;
				cssvalue->get_paintType(&type);

				if (
					type == SVG_PAINTTYPE_URI ||
					type == SVG_PAINTTYPE_URI_NONE ||
					type == SVG_PAINTTYPE_URI_CURRENTCOLOR ||
					type == SVG_PAINTTYPE_URI_RGBCOLOR ||
					type == SVG_PAINTTYPE_URI_RGBCOLOR_ICCCOLOR)
				{
					CComBSTR url;
					cssvalue->get_uri(&url);

					if (((BSTR)url)[0] == L'#')
					{
						_bstr_t uri = ((BSTR)url)+1;
					//	_bstr_t uri = url;

						CComPtr<Web::Element> element;
						document->getElementById(uri, &element);
						if (element)
						{
							//CComQIPtr<ILSVGElement> maskElement = element;
							//if (maskElement)
							{
								CComPtr<IEElement> eUriElement;
								eDocument->GetEElementFromDOMElement(element, &eUriElement);

								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement = eElement;
								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement = eUriElement;

								m_viewGroup->ActivateElement(eUriElement, 0, NULL);
							}
						}
					}
				}
			}
		}
	}
#endif
	return 0;
}

long CEXMLLayoutView::OnObjectEditMask(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"mask", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					CComBSTR url;
					cssvalue->getStringValue(&url);

					if (((BSTR)url)[0] == L'#')
					{
						_bstr_t uri = ((BSTR)url)+1;

						CComPtr<Web::Element> element;
						document->getElementById(uri, &element);
						if (element)
						{
							CComQIPtr<ILSVGMaskElement> maskElement = element;
							if (maskElement)
							{
								CComPtr<IEElement> eMaskElement;
								eDocument->GetEElementFromDOMElement(maskElement, &eMaskElement);

								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement = eElement;
								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement = eMaskElement;

								m_viewGroup->ActivateElement(eMaskElement, 0, NULL);
							}
						}
					}
				}
			}
		}
	}
#endif
	return 0;
}

long CEXMLLayoutView::OnObjectEditClippingPath(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"clip-path", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					CComBSTR url;
					cssvalue->getStringValue(&url);

					if (((BSTR)url)[0] == L'#')
					{
						_bstr_t uri = ((BSTR)url)+1;

						CComPtr<Web::Element> element;
						document->getElementById(uri, &element);
						if (element)
						{
							CComQIPtr<ILSVGClipPathElement> clipPathElement = element;
							if (clipPathElement)
							{
								CComPtr<IEElement> eClipPathElement;
								eDocument->GetEElementFromDOMElement(clipPathElement, &eClipPathElement);

								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement = eElement;
								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement = eClipPathElement;

								m_viewGroup->ActivateElement(eClipPathElement, 0, NULL);
							}
						}
					}
				}
			}
		}
	}
#endif
	return 0;
}

long CEXMLLayoutView::OnObjectEditFilter(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"filter", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				CSSUnitType type;
				cssvalue->get_primitiveType(&type);
				if (type == CSS_URI)
				{
					CComBSTR url;
					cssvalue->getStringValue(&url);

					if (((BSTR)url)[0] == L'#')
					{
						_bstr_t uri = ((BSTR)url)+1;

						CComPtr<Web::Element> element;
						document->getElementById(uri, &element);
						if (element)
						{
							CComQIPtr<ILSVGFilterElement> filterElement = element;
							if (filterElement)
							{
								CComPtr<IEElement> eFilterElement;
								eDocument->GetEElementFromDOMElement(filterElement, &eFilterElement);

								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferenceElement = eElement;
								static_cast<CEXMLViewGroup*>(m_viewGroup)->m_activeReferencedElement = eFilterElement;

								m_viewGroup->ActivateElement(eFilterElement, 0, NULL);
							}
						}
					}
				}
			}
		}
	}
#endif
	return 0;
}

void CEXMLLayoutView::OnObjectEditPaintUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
}

void CEXMLLayoutView::OnObjectEditMaskUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	BOOL bEnable = FALSE;

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"mask", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

void CEXMLLayoutView::OnObjectEditClippingPathUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	BOOL bEnable = FALSE;

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"clip-path", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

void CEXMLLayoutView::OnObjectEditFilterUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	BOOL bEnable = FALSE;

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	CEXMLDocument* eDocument;
	m_viewGroup->get_eXMLDocument(&eDocument);

	CComPtr<Web::Document> document;
	eDocument->get_DOMDocument(&document);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> element;
		eElement->get_domElement(&element);

		CComQIPtr<ILSVGStylable> stylable = element;
		if (stylable)
		{
			CComPtr<ILCSSStyleDeclaration> style;
			stylable->get_style(&style);

			CComPtr<ILCSSPrimitiveValue> cssvalue;
			style->getPropertyCSSValue(L"filter", (ILCSSValue**)&cssvalue);
			if (cssvalue)
			{
				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

long CEXMLLayoutView::OnObjectConvertToPath(int wNotifyCode, int wID, UI::Control* hWndCtl, bool& bHandled)
{
	ASSERT(0);
#if 0
	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	if (selectedElement)
	{
		CEXMLDocument* eDocument;
		m_viewGroup->get_eXMLDocument(&eDocument);

		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComPtr<Web::Document> domDocument;
		eDocument->get_DOMDocument(&domDocument);

		CComQIPtr<IESVGSimpleShapeElement> simpleShape = eElement;
		if (simpleShape)
		{
			CComBSTR style;
			domElement->getAttribute(L"style", &style);

			CComBSTR transform;
			domElement->getAttribute(L"transform", &transform);

			CComPtr<IEElement> ePath;
			eDocument->createEElementNS(L"http://www.w3.org/2000/svg", L"path", &ePath);
			if (ePath)
			{
				CComPtr<ILSVGPathElement> path;
				ePath->get_domElement((Web::Element**)&path);

				if (style.Length())
				{
					path->setAttribute(L"style", style);
				}

				if (transform.Length())
				{
					path->setAttribute(L"transform", transform);
				}

				CComQIPtr<ILSVGAnimatedPathData> pathdata = path;
				ASSERT(pathdata);

				CComPtr<ILSVGPathSegList> seglist;
				pathdata->get_normalizedPathSegList(&seglist);
				ASSERT(seglist);

				simpleShape->DrawPathSegList(path, seglist);

				CComPtr<Web::Node> parentNode;
				domElement->get_parentNode(&parentNode);

				CComPtr<Web::Node> p;
				parentNode->replaceChild(path, domElement, &p);

				m_viewGroup->ActivateElement(ePath, 0, NULL);
			}
		}
		else
		{
			CComQIPtr<ILSVGTextElement> textElement = domElement;
			if (textElement)
			{
				CComPtr<ILSVGSVGElement> svgsvgElement;
				textElement->get_ownerSVGElement(&svgsvgElement);

				CComQIPtr<ILHTMLActiveView> view = m_pIOleDocView;

				CComPtr<ILHTMLWindow> window;
				view->GetHTMLWindow(&window);

				CComPtr<Web::Element> gElement;
				domDocument->createElementNS(L"http://www.w3.org/2000/svg", L"g", &gElement);

				long nglyphs;
				window->svgGetNumberOfGlyphs(textElement, &nglyphs);

				for (int i = 0; i < nglyphs; i++)
				{
					CComPtr<ILSVGPathElement> pathElement;
					domDocument->createElementNS(L"http://www.w3.org/2000/svg", L"path", (Web::Element**)&pathElement);

					CComQIPtr<ILSVGAnimatedPathData> pathdata = pathElement;
					ASSERT(pathdata);

					CComPtr<ILSVGPathSegList> seglist;
					pathdata->get_normalizedPathSegList(&seglist);
					ASSERT(seglist);

				//
					CComPtr<ILSVGPoint> svgPoint;
					window->svgGetPositionOfGlyph(textElement, i, &svgPoint);
					SVGPoint point = svgPoint;

					CComPtr<ILSVGMatrix> mat0;
					svgsvgElement->createSVGMatrix(&mat0);

					CComPtr<ILSVGMatrix> mat;
					mat0->translate(point.X, point.Y, &mat);

				//
					window->svgAddGlyphToSegList(textElement, i, seglist);
					seglist->matrixTransform(mat);

					gElement->appendChild(pathElement, NULL);
				}

				CComPtr<Web::Node> parentNode;
				domElement->get_parentNode(&parentNode);

				CComPtr<Web::Node> p;
				parentNode->replaceChild(gElement, domElement, &p);

				CComPtr<IEElement> eGElement;
				eDocument->GetEElementFromDOMElement(gElement, &eGElement);

				m_viewGroup->ActivateElement(eGElement, 0, NULL);
			}
		}
	}
#endif

	return 0;
}

void CEXMLLayoutView::OnObjectConvertToPathUpdate(long iid, UI::IUICmdUpdate* pCmdUI)
{
	ASSERT(0);
#if 0
	BOOL bEnable = FALSE;

	CComPtr<IESelectedElement> selectedElement;
	m_viewGroup->GetActiveSelectedElement(&selectedElement);

	if (selectedElement)
	{
		CComPtr<IEElement> eElement;
		selectedElement->get_eElement(&eElement);

		CComPtr<Web::Element> domElement;
		eElement->get_domElement(&domElement);

		CComQIPtr<IESVGSimpleShapeElement> simpleShape = eElement;
		if (simpleShape)
		{
			bEnable = TRUE;
		}
		else
		{
			CComQIPtr<ILSVGTextElement> textElement = domElement;
			if (textElement)
			{
				bEnable = TRUE;
			}
		}
	}

	pCmdUI->Enable(bEnable);
#endif
}

#if 0
// ICommandTarget
ErrorCode CEXMLLayoutView::OnCmdMsg(long nID, long nCode, UI::IUICmdUpdate * pCmdUI, bool * bHandled)
{
// Try us
	ProcessTargetCommands::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return Success;

// Try viewgroup
	CComQIPtr<ICommandTarget> target = m_viewGroup;
	target->OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return Success;

	return Success;
}
#endif


}	// LXmlEdit
}
