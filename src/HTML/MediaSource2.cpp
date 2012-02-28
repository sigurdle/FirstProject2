#include "stdafx.h"
#include "LHTML.h"
#include "MediaSource.h"

#include "MPEG.h"

#include <qedit.h>

#pragma comment(lib, "C:\\Program Files\\Microsoft SDK\\samples\\multimedia\\directshow\\BaseClasses\\debug\\strmbasd.lib")

/////////////
#include <streams.h>
//#include "vidprop.h"
#include <initguid.h>
//#include "sampvid.h"
#if (1100 > _MSC_VER)
#include <olectlid.h>
#else
#include <olectl.h>
#endif

class CVideoRenderer;

// This is the video renderer window it supports IBasicVideo and IVideoWindow
// by inheriting from the CBaseControlWindow and CbaseControlVideo classes.
// Those classes leave a few PURE virtual methods that we have to override to
// complete their implementation such as the handling of source and target
// rectangles. The class also looks after creating the window with a custom
// clip region in the shape of the word ActiveX (only applies to Windows/NT)

class CVideoText : /*public CBaseControlWindow,*/ public CBaseControlVideo
{
protected:

    CVideoRenderer *m_pRenderer;        // Owning sample renderer object
    SIZE m_Size;                        // Size of the masking bitmap

public:

    CVideoText(TCHAR *pName,                 // Object description
               LPUNKNOWN pUnk,               // Normal COM ownership
               HRESULT *phr,                 // OLE failure code
               CCritSec *pInterfaceLock,     // Main critical section
               CVideoRenderer *pRenderer);   // Delegates locking to

    virtual ~CVideoText();
    STDMETHODIMP NonDelegatingQueryInterface(REFIID riid,void **ppv);

    // Pure virtual methods for the IBasicVideo interface

    HRESULT IsDefaultTargetRect();
    HRESULT SetDefaultTargetRect();
    HRESULT SetTargetRect(RECT *pTargetRect);
    HRESULT GetTargetRect(RECT *pTargetRect);
    HRESULT IsDefaultSourceRect();
    HRESULT SetDefaultSourceRect();
    HRESULT SetSourceRect(RECT *pSourceRect);
    HRESULT GetSourceRect(RECT *pSourceRect);
    HRESULT GetStaticImage(long *pBufferSize,long *pDIBImage);

    // Prepare the window with a text region

    void InitRenderer(TCHAR *pStringName);
    HRESULT InitWindowRegion(TCHAR *pStringName);
    HFONT CreateVideoFont();
    RECT GetDefaultRect();
    VIDEOINFOHEADER *GetVideoFormat();

    // Overriden from CBaseWindow return our window and class styles

    LPTSTR GetClassWindowStyles(DWORD *pClassStyles,
                                DWORD *pWindowStyles,
                                DWORD *pWindowStylesEx);

    // Method that gets all the window messages

    LRESULT OnReceiveMessage(HWND hwnd,          // Window handle
                             UINT uMsg,          // Message ID
                             WPARAM wParam,      // First parameter
                             LPARAM lParam);     // Other parameter
}; // CVideoText

// This class supports the renderer input pin. We have to override the base
// class input pin because we provide our own special allocator which hands
// out buffers based on GDI DIBSECTIONs. We have an extra limitation which
// is that we only connect to filters that agree to use our allocator. This
// stops us from connecting to the tee for example. The extra work required
// to use someone elses allocator and select the buffer into a bitmap and
// that into the HDC is not great but would only really confuse this sample

class CVideoInputPin : public CRendererInputPin
{
    CVideoRenderer *m_pRenderer;        // The renderer that owns us
    CCritSec *m_pInterfaceLock;         // Main filter critical section

public:

    // Constructor

    CVideoInputPin(
        TCHAR *pObjectName,             // Object string description
        CVideoRenderer *pRenderer,      // Used to delegate locking
        CCritSec *pInterfaceLock,       // Main critical section
        HRESULT *phr,                   // OLE failure return code
        LPCWSTR pPinName);              // This pins identification

    // Manage our DIBSECTION video allocator
    STDMETHODIMP GetAllocator(IMemAllocator **ppAllocator);
    STDMETHODIMP NotifyAllocator(IMemAllocator *pAllocator,BOOL bReadOnly);

}; // CVideoInputPin


// This is the COM object that represents a simple rendering filter. It
// supports IBaseFilter and IMediaFilter and a single input stream (pin)
// The classes that support these interfaces have nested scope NOTE the
// nested class objects are passed a pointer to their owning renderer
// when they are created but they should not use it during construction

class CVideoRenderer : /*public ISpecifyPropertyPages,*/
//	public CBaseBasicVideo,
	public CBaseVideoRenderer
{
public:

    // Constructor and destructor

//    static CUnknown * WINAPI CreateInstance(LPUNKNOWN, HRESULT *);
    CVideoRenderer(TCHAR *pName,LPUNKNOWN pUnk,HRESULT *phr);
    ~CVideoRenderer();

	CMediaSource* m_pMediaSource;

    // Implement the ISpecifyPropertyPages interface

    DECLARE_IUNKNOWN
    STDMETHODIMP NonDelegatingQueryInterface(REFIID, void **);
    STDMETHODIMP GetPages(CAUUID *pPages);

    CBasePin *GetPin(int n);

    // Override these from the filter and renderer classes

    void PrepareRender();
    HRESULT Active();
    HRESULT BreakConnect();
    HRESULT CompleteConnect(IPin *pReceivePin);
    HRESULT SetMediaType(const CMediaType *pmt);
    HRESULT CheckMediaType(const CMediaType *pmtIn);
    HRESULT CheckVideoType(const VIDEOINFO *pDisplay,const VIDEOINFO *pInput);
    HRESULT UpdateFormat(VIDEOINFO *pVideoInfo);
    HRESULT DoRenderSample(IMediaSample *pMediaSample);
    void OnReceiveFirstSample(IMediaSample *pMediaSample);

public:

    CImageAllocator m_ImageAllocator;   // Our DIBSECTION allocator
    CVideoInputPin m_InputPin;          // IPin based interfaces
    CImageDisplay m_Display;            // Manages the video display type
    CMediaType m_mtIn;                  // Source connection media type
//    CVideoText m_VideoText;             // Does the actual video rendering
  //  CImagePalette m_ImagePalette;       // Looks after managing a palette

//    CDrawImage m_DrawImage;             // Does the actual image drawing
    CMediaType *m_pMediaType;       // Pointer to the current format

    SIZE m_VideoSize;                   // Size of the current video stream

}; // CVideoRenderer

//
// Constructor
//
CVideoRenderer::CVideoRenderer(TCHAR *pName,
                               LPUNKNOWN pUnk,
                               HRESULT *phr) :

    CBaseVideoRenderer(CLSID_NULL/*SampleRenderer*/,pName,pUnk,phr),
	//CBaseBasicVideo(
    m_InputPin(NAME("Video Pin"),this,&m_InterfaceLock,phr,L"Input"),
    m_ImageAllocator(this,NAME("Sample video allocator"),phr)
//    m_VideoText(NAME("Video properties"),GetOwner(),phr,&m_InterfaceLock,this),
//    m_ImagePalette(this,&m_VideoText,&m_DrawImage),
//    m_DrawImage(&m_VideoText)
{
    // Store the video input pin
    m_pInputPin = &m_InputPin;

    // Reset the current video size

    m_VideoSize.cx = 0;
    m_VideoSize.cy = 0;

    // Initialise the window and control interfaces

//    m_VideoText.SetControlVideoPin(&m_InputPin);
//    m_VideoText.SetControlWindowPin(&m_InputPin);

} // (Constructor)


//
// Destructor
//
CVideoRenderer::~CVideoRenderer()
{
    m_pInputPin = NULL;

} // (Destructor)


//
// CheckMediaType
//
// Check the proposed video media type
//
HRESULT CVideoRenderer::CheckMediaType(const CMediaType *pmtIn)
{
    return m_Display.CheckMediaType(pmtIn);

} // CheckMediaType


//
// GetPin
//
// We only support one input pin and it is numbered zero
//
CBasePin *CVideoRenderer::GetPin(int n)
{
    ASSERT(n == 0);
    if (n != 0) {
        return NULL;
    }

    // Assign the input pin if not already done so

    if (m_pInputPin == NULL) {
        m_pInputPin = &m_InputPin;
    }
    return m_pInputPin;

} // GetPin


//
// NonDelegatingQueryInterface
//
// Overriden to say what interfaces we support and where
//
STDMETHODIMP CVideoRenderer::NonDelegatingQueryInterface(REFIID riid,void **ppv)
{
    CheckPointer(ppv,E_POINTER);
#if 0
	 /*
    if (riid == IID_ISpecifyPropertyPages) {
        return GetInterface((ISpecifyPropertyPages *)this, ppv);
    } else if (riid == IID_IVideoWindow) {
        return m_VideoText.NonDelegatingQueryInterface(riid,ppv);
    } else*/ if (riid == IID_IBasicVideo) {
        return m_VideoText.NonDelegatingQueryInterface(riid,ppv);
    }
#endif
    return CBaseVideoRenderer::NonDelegatingQueryInterface(riid,ppv);

} // NonDelegatingQueryInterface


#if 0
//
// GetPages
//
// Return the CLSIDs for the property pages we support
//
STDMETHODIMP CVideoRenderer::GetPages(CAUUID *pPages)
{
    CheckPointer(pPages,E_POINTER);

    pPages->cElems = 1;
    pPages->pElems = (GUID *) CoTaskMemAlloc(sizeof(GUID));
    if (pPages->pElems == NULL) {
        return E_OUTOFMEMORY;
    }

    pPages->pElems[0] = CLSID_SampleQuality;
    return NOERROR;

} // GetPages
#endif


//
// DoRenderSample
//
// Have the drawing object render the current image
//
HRESULT CVideoRenderer::DoRenderSample(IMediaSample *pMediaSample)
{
    BITMAPINFOHEADER *pbmi;     // Image format data
    DIBDATA *pDibData;          // Stores DIB information
    BYTE *pImage;               // Pointer to image data
//    HBITMAP hOldBitmap;         // Store the old bitmap
    CImageSample *pSample;      // Pointer to C++ object

    ASSERT(m_pMediaType);

    // From the untyped source format block get the VIDEOINFO and subsequently
    // the BITMAPINFOHEADER structure. We can cast the IMediaSample interface
    // to a CImageSample object so we can retrieve it's DIBSECTION details

    pbmi = HEADER(m_pMediaType->Format());
    pSample = (CImageSample *) pMediaSample;
    pDibData = pSample->GetDIBData();
    //hOldBitmap = (HBITMAP) SelectObject(m_MemoryDC,pDibData->hBitmap);

    // Get a pointer to the real image data

    HRESULT hr = pMediaSample->GetPointer(&pImage);
    if (FAILED(hr)) {
        return E_FAIL;
    }

	m_pMediaSource->m_pSrcBitmap = new Gdiplus::Bitmap((BITMAPINFO*)pbmi, (void*)pImage);

    return 0;//m_DrawImage.DrawImage(pMediaSample);

} // DoRenderSample


//
// PrepareRender
//
// Overriden to realise the palette before drawing. We used to have to realise
// the palette on every frame because we could never be sure of receiving top
// level messages like WM_PALETTECHANGED. However the plug in distributor will
// now make sure we get these but we still have to do this because otherwise
// we may not find the palette being realised before the thread comes to draw

void CVideoRenderer::PrepareRender()
{
    // Realise the palette on this thread
    //m_VideoText.DoRealisePalette();
} // PrepareRender


//
// Active
//
// The auto show flag is used to have the window shown automatically when we
// change state. We do this only when moving to paused or running, when there
// is no outstanding EC_USERABORT set and when the window is not already up
// This can be changed through the IVideoWindow interface AutoShow property.
// If the window is not currently visible then we are showing it because of
// a state change to paused or running, in which case there is no point in
// the video window sending an EC_REPAINT as we're getting an image anyway
//
HRESULT CVideoRenderer::Active()
{
#if 0
    HWND hwnd = m_VideoText.GetWindowHWND();
    NOTE("AutoShowWindow");

    if (m_VideoText.IsAutoShowEnabled() == TRUE) {
        if (m_bAbort == FALSE) {
            if (IsWindowVisible(hwnd) == FALSE) {
                NOTE("Executing AutoShowWindow");
                SetRepaintStatus(FALSE);
                m_VideoText.PerformanceAlignWindow();
                m_VideoText.DoShowWindow(SW_SHOWNORMAL);
                m_VideoText.DoSetWindowForeground(TRUE);
            }
        }
    }
#endif
    return CBaseVideoRenderer::Active();

} // Active

//
// SetMediaType
//
// We store a copy of the media type used for the connection in the renderer
// because it is required by many different parts of the running renderer
// This can be called when we come to draw a media sample that has a format
// change with it. We normally delay type changes until they are really due
// for rendering otherwise we will change types too early if the source has
// allocated a queue of samples. In our case this isn't a problem because we
// only ever receive one sample at a time so it's safe to change immediately
//
HRESULT CVideoRenderer::SetMediaType(const CMediaType *pmt)
{
    CAutoLock cInterfaceLock(&m_InterfaceLock);
    CMediaType StoreFormat(m_mtIn);
    HRESULT hr = NOERROR;

    // Fill out the optional fields in the VIDEOINFOHEADER

    m_mtIn = *pmt;
    VIDEOINFO *pVideoInfo = (VIDEOINFO *) m_mtIn.Format();
    m_Display.UpdateFormat(pVideoInfo);

    // We set the new palette before completing so that the method can look
    // at the old RGB colours we used and compare them with the new set, if
    // they're all identical colours we don't need to change the palette

#if 0
    hr = m_ImagePalette.PreparePalette(&m_mtIn,&StoreFormat,NULL);
    if (FAILED(hr)) {
        return hr;
    }
#endif

    // Complete the initialisation
#if 0
    m_DrawImage.NotifyMediaType(&m_mtIn);
#endif
     m_pMediaType = &m_mtIn;//pMediaType;


    m_ImageAllocator.NotifyMediaType(&m_mtIn);
    return NOERROR;

} // SetMediaType


//
// BreakConnect
//
// This is called when a connection or an attempted connection is terminated
// and lets us to reset the connection flag held by the base class renderer
// The filter object may be hanging onto an image to use for refreshing the
// video window so that must be freed (the allocator decommit may be waiting
// for that image to return before completing) then we must also uninstall
// any palette we were using, reset anything set with the control interfaces
// then set our overall state back to disconnected ready for the next time

HRESULT CVideoRenderer::BreakConnect()
{
    CAutoLock cInterfaceLock(&m_InterfaceLock);

    // Check we are in a valid state

    HRESULT hr = CBaseVideoRenderer::BreakConnect();
    if (FAILED(hr)) {
        return hr;
    }

    // The window is not used when disconnected
    IPin *pPin = m_InputPin.GetConnected();
    if (pPin) SendNotifyWindow(pPin,NULL);

    // The base class break connect disables us from sending any EC_REPAINT
    // events which is important otherwise when we come down here to remove
    // our palette we end up painting the window again - which in turn sees
    // there is no image to draw and would otherwise send a redundant event

#if 0
    m_ImagePalette.RemovePalette();
#endif

    m_mtIn.ResetFormatBuffer();
    return NOERROR;

} // BreakConnect


//
// CompleteConnect
//
// When we complete connection we need to see if the video has changed sizes
// If it has then we activate the window and reset the source and destination
// rectangles. If the video is the same size then we bomb out early. By doing
// this we make sure that temporary disconnections such as when we go into a
// fullscreen mode do not cause unnecessary property changes. The basic ethos
// is that all properties should be persistent across connections if possible
//
HRESULT CVideoRenderer::CompleteConnect(IPin *pReceivePin)
{
    CAutoLock cInterfaceLock(&m_InterfaceLock);
    CBaseVideoRenderer::CompleteConnect(pReceivePin);
#if 0
    m_DrawImage.ResetPaletteVersion();
#endif

    // Has the video size changed between connections

    VIDEOINFOHEADER *pVideoInfo = (VIDEOINFOHEADER *) m_mtIn.Format();
    if (pVideoInfo->bmiHeader.biWidth == m_VideoSize.cx) {
        if (pVideoInfo->bmiHeader.biHeight == m_VideoSize.cy) {
            return NOERROR;
        }
    }

#if 0
    // Pass the video window handle upstream
    HWND hwnd = m_VideoText.GetWindowHWND();
    NOTE1("Sending EC_NOTIFY_WINDOW %x",hwnd);
    SendNotifyWindow(pReceivePin,hwnd);
#endif

    // Set them for the current video dimensions

#if 0
    m_DrawImage.SetDrawContext();
#endif
    m_VideoSize.cx = pVideoInfo->bmiHeader.biWidth;
    m_VideoSize.cy = pVideoInfo->bmiHeader.biHeight;
#if 0
    m_VideoText.SetDefaultSourceRect();
    m_VideoText.SetDefaultTargetRect();
    m_VideoText.OnVideoSizeChange();
    m_VideoText.ActivateWindow();
#endif

    return NOERROR;

} // CompleteConnect


//
// OnReceiveFirstSample
//
// Use the image just delivered to display a poster frame
//
void CVideoRenderer::OnReceiveFirstSample(IMediaSample *pMediaSample)
{
    DoRenderSample(pMediaSample);

} // OnReceiveFirstSample


// Constructor

CVideoInputPin::CVideoInputPin(TCHAR *pObjectName,
                               CVideoRenderer *pRenderer,
                               CCritSec *pInterfaceLock,
                               HRESULT *phr,
                               LPCWSTR pPinName) :

    CRendererInputPin(pRenderer,phr,pPinName),
    m_pRenderer(pRenderer),
    m_pInterfaceLock(pInterfaceLock)
{
    ASSERT(m_pRenderer);
    ASSERT(pInterfaceLock);

} // (Constructor)


//
// GetAllocator
//
// This overrides the CBaseInputPin virtual method to return our allocator
// we create to pass shared memory DIB buffers that GDI can directly access
// When NotifyAllocator is called it sets the current allocator in the base
// input pin class (m_pAllocator), this is what GetAllocator should return
// unless it is NULL in which case we return the allocator we would like
//
STDMETHODIMP CVideoInputPin::GetAllocator(IMemAllocator **ppAllocator)
{
    CAutoLock cInterfaceLock(m_pInterfaceLock);
    CheckPointer(ppAllocator,E_POINTER);

    // Has an allocator been set yet in the base class

    if (m_pAllocator == NULL) {
        m_pAllocator = &m_pRenderer->m_ImageAllocator;
        m_pAllocator->AddRef();
    }

    *ppAllocator = m_pAllocator;
    return NOERROR;

} // GetAllocator


//
// NotifyAllocator
//
// The COM specification says any two IUnknown pointers to the same object
// should always match which provides a way for us to see if they are using
// our DIB allocator or not. Since we are only really interested in equality
// and our object always hands out the same IMemAllocator interface we can
// just see if the pointers match. If they are we set a flag in the main
// renderer as the window needs to know whether it can do fast rendering
//
STDMETHODIMP
CVideoInputPin::NotifyAllocator(IMemAllocator *pAllocator,BOOL bReadOnly)
{
    CAutoLock cInterfaceLock(m_pInterfaceLock);

    // Make sure the base class gets a look

    HRESULT hr = CBaseInputPin::NotifyAllocator(pAllocator,bReadOnly);
    if (FAILED(hr)) {
        return hr;
    }

    // Whose allocator is the source going to use
#if 0
    m_pRenderer->m_DrawImage.NotifyAllocator(FALSE);
    if (pAllocator == &m_pRenderer->m_ImageAllocator) {
        m_pRenderer->m_DrawImage.NotifyAllocator(TRUE);
    }
#endif
    return NOERROR;

} // NotifyAllocator

#if 0
/*
//#include <Streams.h>
//#include <Mtype.h>

  If you prefer not to link to the base class library, you can use the
  following code directly:
*/

void /*My*/FreeMediaType(AM_MEDIA_TYPE& mt)
{
	if (mt.cbFormat != 0)
	{
		CoTaskMemFree((PVOID)mt.pbFormat);
		mt.cbFormat = 0;
		mt.pbFormat = NULL;
	}
	if (mt.pUnk != NULL)
	{
		// Unecessary because pUnk should not be used, but safest.
		mt.pUnk->Release();
		mt.pUnk = NULL;
	}
}
#endif

HRESULT CMediaSource::Seek(double simpleTime)
{
	if (m_pSrcBitmap)
	{
		delete m_pSrcBitmap;
		m_pSrcBitmap = NULL;
	}

	m_mpegfile->Seek(simpleTime);

	if (m_dsGraph)
	{
#if 0
	// Set one-shot mode and buffering.
		CComQIPtr<ISampleGrabber> pGrabber = m_pF;

		HRESULT hr;

		hr = pGrabber->SetOneShot(TRUE);
		hr = pGrabber->SetBufferSamples(TRUE);

	/* Query the Filter Graph Manager for these interfaces. */
		CComQIPtr<IMediaFilter> pMediaFilter = m_dsGraph;
	//	CComQIPtr<IMediaControl> pControl = m_dsGraph;
	//	CComQIPtr<IMediaEventEx> pEvent = m_dsGraph;

		pMediaFilter->SetSyncSource(NULL); // Turn off the reference clock.
#endif	// Had this

	// Seek
		if (FALSE)
		{
			CComQIPtr<IMediaSeeking> mediaSeeking = m_dsGraph;
			ASSERT(mediaSeeking);

			HRESULT hr = mediaSeeking->SetTimeFormat(&TIME_FORMAT_MEDIA_TIME);
			ASSERT(SUCCEEDED(hr));

		// 100 nanoseconds
			LONGLONG pos = (LONGLONG)(simpleTime*1000*1000*10);
			hr = mediaSeeking->SetPositions(&pos, AM_SEEKING_AbsolutePositioning, NULL, AM_SEEKING_NoPositioning);
		}
	}

	return S_OK;
}

HRESULT CMediaSource::GetBitmap(Gdiplus::Bitmap** pVal)
{
	HRESULT hr = S_OK;

	if (m_pSrcBitmap == NULL)
	{
		if (m_mpegfile)
		{
			BYTE* bits;
			m_mpegfile->GetBitmapData(&bits);

			m_pSrcBitmap = new Gdiplus::Bitmap(m_mpegfile->m_horizontal_size, m_mpegfile->m_vertical_size, ROWBYTES(m_mpegfile->m_horizontal_size, 24), PixelFormat24bppRGB, bits);

			if (m_pSrcBitmap)
			{
				/*
				Gdiplus::BitmapData outdata;
				m_pSrcBitmap->LockBits(
					&Gdiplus::Rect(0, 0, m_pSrcBitmap->GetWidth(), m_pSrcBitmap->GetHeight()),
					Gdiplus::ImageLockModeWrite,
					PixelFormat32bppARGB, &outdata);

				int width = outdata.Width;
				int height = outdata.Height;

				for (int y = 0; y < height; y++)
				{
					BYTE* p = m_mpegfile->m_ybuf + y*m_mpegfile->m_horizontal_size;
					ARGBPixel* out = (ARGBPixel*)((BYTE*)outdata.Scan0 + outdata.Stride*y);

					for (int x = 0; x < width; x++)
					{
						out->red = *p;
						out->green = *p;
						out->blue = *p;
						out->alpha = 255;

						out++;
						p++;
					}
				}

				m_pSrcBitmap->UnlockBits(&outdata);
				*/
			}
		}
	}

	*pVal = m_pSrcBitmap;

	return S_OK;

#if 0
	if (m_dsGraph == NULL)
	{
		/*
// Should maybe return failure here ?, seekElement should've been called
	// before a CHTMFrame tries to get a bitmap

		seekElement(0);
		*/
		return E_FAIL;
	}

#if 0
	if (m_pSrcBitmap == NULL)
	{
		{
			CComQIPtr<IMediaControl> pControl = m_dsGraph;
			CComQIPtr<IMediaEventEx> pEvent = m_dsGraph;

			pControl->Run(); // Run the graph.

			long evCode;
			pEvent->WaitForCompletion(INFINITE, &evCode); // Wait till it's done.

			pControl->Stop();
		}

		CComQIPtr<ISampleGrabber> pGrabber = m_pF;

		// Find the required buffer size.
		long cbBuffer = 0;
		hr = pGrabber->GetCurrentBuffer(&cbBuffer, NULL);
		if (SUCCEEDED(hr))
		{
			 char *pBuffer = new char[cbBuffer];
			 if (!pBuffer) 
			 {
				  return E_OUTOFMEMORY;
			 }
			 hr = pGrabber->GetCurrentBuffer(&cbBuffer, reinterpret_cast<long*>(pBuffer));

		//
			AM_MEDIA_TYPE mt;
			hr = pGrabber->GetConnectedMediaType(&mt);
			VIDEOINFOHEADER *pVih;
			if ((mt.formattype == FORMAT_VideoInfo) && 
				 (mt.cbFormat >= sizeof(VIDEOINFOHEADER)) ) 
			{
				 pVih = reinterpret_cast<VIDEOINFOHEADER*>(mt.pbFormat);
			}
			else 
			{
				 // Wrong format. Free the format block and return an error.
				 FreeMediaType(mt);
				 return VFW_E_INVALIDMEDIATYPE; // Something went wrong
			}

			// Now pVih->bmiHeader is the BITMAPINFOHEADER for the frame.

			m_pSrcBitmap = new Gdiplus::Bitmap((BITMAPINFO*)&pVih->bmiHeader, (void*)pBuffer);

			// Free the format block when you are done:
			FreeMediaType(mt);
		}
	}
#endif

	*pVal = m_pSrcBitmap;

	return hr;
#endif
}

HRESULT CMediaSource::CreateSampleGrabber()
{
	HRESULT hr;

	m_dsGraph.CoCreateInstance(CLSID_FilterGraph);

	// Create the Sample Grabber.
	ISampleGrabber *pGrabber = NULL;
	hr = CoCreateInstance(CLSID_SampleGrabber, NULL, CLSCTX_INPROC_SERVER,
		 IID_IBaseFilter, reinterpret_cast<void**>(&m_pF));
	if (FAILED(hr))
	{
		 // Error handling is omitted for clarity;
		ASSERT(0);
	}

	hr = m_pF->QueryInterface(IID_ISampleGrabber,
		 reinterpret_cast<void**>(&pGrabber));

	hr = m_dsGraph->AddFilter(m_pF, L"SampleGrabber");

	// Find the current bit depth.
	/*
	HDC hdc = GetDC(NULL);
	int iBitDepth = GetDeviceCaps(hdc, BITSPIXEL);
	ReleaseDC(NULL, hdc);
	*/
	// Set the media type.
	AM_MEDIA_TYPE mt;
	ZeroMemory(&mt, sizeof(AM_MEDIA_TYPE));
	mt.majortype = MEDIATYPE_Video;
/*
	switch (iBitDepth)
	{

	case 8:
		 mt.subtype = MEDIASUBTYPE_RGB8;
		 break;
	case 16:
		 mt.subtype = MEDIASUBTYPE_RGB555;
		 break;
	case 24:
		 */
		 mt.subtype = MEDIASUBTYPE_RGB24;
/*		 break;
	case 32:
		 mt.subtype = MEDIASUBTYPE_RGB32;
		 break;
	default:
		 return E_FAIL;
	}
*/
		hr = pGrabber->SetMediaType(&mt);

	return hr;
}

// Forward declares.
HRESULT GetPin(IBaseFilter *, PIN_DIRECTION, IPin **);
HRESULT ConnectFilters(IGraphBuilder *, IBaseFilter *, IBaseFilter *);

HRESULT CMediaSource::LoadFile(LPCWSTR wszFileName)
{
	USES_CONVERSION;

	m_mpegfile = new CMPEGFile;
	{
		CComPtr<IStream> stream;
		HRESULT hr = URLOpenBlockingStream(0, W2A(wszFileName), &stream, 0, 0);
		if (SUCCEEDED(hr))
		{
			m_mpegfile->Open(stream);
		}
	}

	return S_OK;

#if 0
	HRESULT hr;

	IBaseFilter *pSrc;
//	hr = m_dsGraph->AddSourceFilter(wszFileName, L"Source", &pSrc);
	hr = m_dsGraph->RenderFile(wszFileName, NULL);
	if (SUCCEEDED(hr))
	{

#if 0
		hr = ConnectFilters(m_dsGraph, pSrc, m_pF);
#endif

	//The application must also connect the Sample Grabber's output pin. If you just want to discard the samples when you are done (instead of rendering them), connect the Null Renderer Filter. The Null Renderer simply discards every sample that it receives.

		if (TRUE)
		{
			IBaseFilter *pNull = NULL;

			HRESULT hr;
			pNull = new CVideoRenderer(NAME("Sample Video Renderer"),NULL, &hr);
			((CVideoRenderer*)pNull)->m_pMediaSource = this;
			//CVideoRenderer* pRenderer = new CVideoRenderer;
			//pRenderer->AddRef();
			//pNull = pRenderer;

			/*
			hr = CoCreateInstance(CLSID_NullRenderer, NULL, CLSCTX_INPROC_SERVER,
				 IID_IBaseFilter, reinterpret_cast<void**>(&pNull));
			if (FAILED(hr))
			{
				 // Error checking omitted for clarity.
				ASSERT(0);
			}
			*/

			CComPtr<IBaseFilter> oldRenderer;
			m_dsGraph->FindFilterByName(L"Video Renderer", &oldRenderer);

			CComPtr<IPin> pIn;
			GetPin(oldRenderer, PINDIR_INPUT, &pIn);

			CComPtr<IPin> pOut;
			pIn->ConnectedTo(&pOut);

			m_dsGraph->RemoveFilter(oldRenderer);

			hr = m_dsGraph->AddFilter(pNull, L"NullRenderer");
			//hr = ConnectFilters(m_dsGraph, pSrc/*m_pF*/, pNull);

			CComPtr<IPin> pIn2;
			GetPin(pNull, PINDIR_INPUT, &pIn2);

			m_dsGraph->Connect(pOut, pIn2);
		}

#if 0
		// Had this in Seek
		{
		// Set one-shot mode and buffering.
			CComQIPtr<ISampleGrabber> pGrabber = m_pF;

			HRESULT hr;

			hr = pGrabber->SetOneShot(TRUE);
			hr = pGrabber->SetBufferSamples(TRUE);

		/* Query the Filter Graph Manager for these interfaces. */
			CComQIPtr<IMediaFilter> pMediaFilter = m_dsGraph;
		//	CComQIPtr<IMediaControl> pControl = m_dsGraph;
		//	CComQIPtr<IMediaEventEx> pEvent = m_dsGraph;

			pMediaFilter->SetSyncSource(NULL); // Turn off the reference clock.
		}
#endif

		{
			CComQIPtr<IMediaControl> pControl = m_dsGraph;
			CComQIPtr<IMediaEventEx> pEvent = m_dsGraph;

			pControl->Run(); // Run the graph.
		}
	}

	return hr;
#endif
}

// Helper functions:

// GetPin: Return the first pin with the specified direction.
HRESULT GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir, IPin **ppPin)
{
    if (!pFilter || !ppPin) return E_POINTER;
    *ppPin = NULL;

    IEnumPins  *pEnum;
    IPin       *pPin;
    HRESULT hr = pFilter->EnumPins(&pEnum);
    if (FAILED(hr)) return hr;

    while(pEnum->Next(1, &pPin, 0) == S_OK)
    {
        PIN_DIRECTION PinDirThis;
        hr = pPin->QueryDirection(&PinDirThis);
        if (FAILED(hr)) break;

        if (PinDir == PinDirThis)
        {
            // Found a matching pin.
            pEnum->Release();
            *ppPin = pPin;  // Caller must release the interface.
            return S_OK;
        }
        pPin->Release();
    }
    pEnum->Release();
    return E_FAIL;  
}

// ConnectFilters: Connect two filters. 
// Note - You could use ICaptureGraphBuilder2::RenderStream also.
HRESULT ConnectFilters(
    IGraphBuilder *pGraph, 
    IBaseFilter *pFirst, 
    IBaseFilter *pSecond)
{
    if (!pGraph || !pFirst || !pSecond) return E_POINTER;

    IPin *pOut = NULL, *pIn = NULL;
    HRESULT hr = GetPin(pFirst, PINDIR_OUTPUT, &pOut);
    if (FAILED(hr)) return hr;

    hr = GetPin(pSecond, PINDIR_INPUT, &pIn);
    if (FAILED(hr)) 
    {
        pOut->Release();
        return E_FAIL;
     }
    hr = pGraph->Connect(pOut, pIn);
	 //VFW_S_PARTIAL_RENDER

    pIn->Release();
    pOut->Release();
    return hr;
}
