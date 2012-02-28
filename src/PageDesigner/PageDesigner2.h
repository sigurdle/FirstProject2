#include "..\UIT\UIT.h"

extern HWND GetMainHwnd();
extern IPageDesignerApp* gIApp;
extern IUIFrame* gIFrame;

#define IN_SOURCEGRAPHIC		-1
#define IN_SOURCEALPHA			-2
#define IN_BACKGROUNDGRAPHIC	-3
#define IN_BACKGROUNDALPHA		-4

typedef struct tagPFILTERRECORD
{
//	LPPLUGINRECORD	pluginRecord;

	DWORD	flags;
	DWORD	modified;

	WORD	quality;
	WORD	depth;

	long	sourceWidth;	// Original source width/height, unaffected by sampling
	long	sourceHeight;

	CRect	uRect;	// Invalid rect, filter this
	CRect	aRect;	// Alpha bounds
	CRect	sRect;	// Selection bounds

	WORD				bTransferTo;	// 0 = Image, 1 = Selection
	BYTE				bSet;
	BYTE				bPaintMethod;

	WORD				planes;
	WORD				imode;

	double			x_sampling;
	double			y_sampling;

	LONG				x, y, z;
	LONG				dx, dy, dz;
	LONG				angle;
	short				strength;
	BYTE				reserved4;
	BYTE				bHasSelectionYet;

	LPVOID	global_data;
	LPVOID	frame_data;
	DWORD		reserved5[2];
	DWORD		userDat;

//	MMPluginRef	thisPlugin;

	long		toolID;
	DWORD		reserved6[7];

	long	inputWidth;	// same as inImage[n]->width
	long	inputHeight;

/* Set these fields in FilterBegin to indicate
that the output image will be larger than the input image.
You should set newwidth and newheight to the size to which you
want the output buffer to be allocated. Set origin to the
place that the point (0,0) in the input should map to in the
new larger output. If you created a 5-pixel drop shadow up
and left, you might set origin to (5, 5).
*/

// Set these in FrameSetup
	LONG out_newwidth;
	LONG out_newheight;
	LONG out_x_origin;
	LONG out_y_origin;

// In values (read-only)
	long in_output_origin_x;
	long in_output_origin_y;

// origin of original source in input buffer
	long in_pre_effect_source_origin_x;
	long in_pre_effect_source_origin_y;

	long	totalFrames;
	long	currentFrame;	// Absolute composition frame
	long currentLayerFrame;
	long layerAbsStartFrame;
	long layerStartFrame;

	long	frameRate;

	LONG	startSample;
	LONG	numSamples;
	LPBYTE	waveData;
	long	samplesPerSec;
	BYTE	wBitsPerSample;
	BYTE	nChannels;
	WORD	reserved7;
	long	totalSamples;

	long layerStartSample;
	long layerDurationSamples;
/*
	ImageDef*	inDepth;
	ImageDef*	outDepth;

	ImageDef*	bgImage;
	ImageDef*	origImage;
	ImageDef*	inImageSel;
	*/
	Gdiplus::Bitmap*	inImage;
	Gdiplus::Bitmap*	outImage;
	/*
	ImageDef*	brushImage;
	*/
	short			boffset_x;
	short			boffset_y;

	//MMBasicSuite*		basic;

	Gdiplus::Bitmap* inPinImage[4];	// TODO, must be possible with unlimited inputs

//	ImageDef* inPinImage[4];	// TODO, must be possible with unlimited inputs

//	BOOL		(MMAPI *InitQTML)	();
//	long		(MMAPI* AddTool)	(MMPluginRef plugin, long id, LPCTSTR name, HINSTANCE hInst, DWORD bmID);
//	BOOL		(MMAPI* Abort)		(tagPFILTERRECORD*);

	int numSubPoints;
	int* subPoints;
	int	numPoints;
	CDblPoint* pointData;
}
PFILTERRECORD, *LPPFILTERRECORD;

template <class T> class ATL_NO_VTABLE CNotifyGetImpl :
	public INotifyGet
{
public:
	STDMETHODIMP OnBeforeChange(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		return S_OK;
	}

	/*
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, GUID targetObjectIID, DISPID dispID);
	*/

	/*
	STDMETHODIMP OnChanged(DISPID dispID)
	{
		return S_OK;
	}
	*/
};

template <class T> class ATL_NO_VTABLE CNotifySendImpl :
	public INotifySend
{
public:

	CArray<INotifyGet*,INotifyGet*> m_get;
	long m_lockCount;
	int m_pendingNotifies;

	CNotifySendImpl()
	{
		m_lockCount = 0;
		m_pendingNotifies = 0;
	}

	~CNotifySendImpl()
	{
		ATLASSERT(m_get.GetSize() == 0);
		ATLASSERT(m_lockCount == 0);
	}

	STDMETHODIMP Advise(INotifyGet* get, DWORD* cookie)
	{
		for (int i = 0; i < m_get.GetSize(); i++)
		{
			if (m_get[i] == get)
			{
				ATLASSERT(0);
			}
		}

		*cookie = m_get.Add(get)+1;

		return S_OK;
	}

	STDMETHODIMP Unadvise(INotifyGet* get)
	{
		ATLASSERT(get != NULL);

		for (int i = 0; i < m_get.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_get[i], get))
			{
				m_get.RemoveAt(i);
				return S_OK;
			}
		}

		ATLASSERT(0);
		return S_OK;
	}

	STDMETHODIMP LockSend()
	{
		m_lockCount++;
		return S_OK;
	}

	STDMETHODIMP UnlockSend()
	{
		m_lockCount--;
		ATLASSERT(m_lockCount >= 0);

		if (m_lockCount == 0)
		{
			if (m_pendingNotifies)
			{
				FireOnChanged((NotifyType)0, static_cast<T*>(this)->GetUnknown()/*NULL*/, /*static_cast<T*>(this)->GetUnknown(),*/ DISPID_UNKNOWN);
				m_pendingNotifies = 0;
			}
		}

		return S_OK;
	}

	void FireOnBeforeChange(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		if (m_lockCount == 0)
		{
			int nConnections = m_get.GetSize();

			for (int i = 0; i < nConnections; i++)
			{
				m_get[i]->OnBeforeChange(type, targetObject, immtargetObject, dispID);

				ATLASSERT(m_get.GetSize() == nConnections);
			}
		}
		else
		{
			m_pendingNotifies++;
		}
	}

	STDMETHODIMP FireOnChanged(NotifyType type, IUnknown* targetObject, /*IUnknown* immtargetObject,*/ DISPID dispID)
	{
		if (m_lockCount == 0)
		{
			int nConnections = m_get.GetSize();

			for (int i = 0; i < nConnections; i++)
			{
				m_get[i]->OnChanged(type, targetObject, static_cast<T*>(this)->GetUnknown()/*immtargetObject*/, dispID);

				ATLASSERT(m_get.GetSize() == nConnections);
			}
		}
		else
		{
			m_pendingNotifies++;
		}

		return S_OK;
	}
};

/*
template <class T> class ATL_NO_VTABLE CPropertyNotifierImpl :
	public IPropertyNotifySinkCP<T>
{
public:
	HRESULT FireOnRequestEdit(DISPID dispID)
	{
		T* pT = static_cast<T*>(this);
		return T::__ATL_PROP_NOTIFY_EVENT_CLASS::FireOnRequestEdit(pT->GetUnknown(), dispID);
	}
	HRESULT FireOnChanged(DISPID dispID)
	{
		T* pT = static_cast<T*>(this);
		return T::__ATL_PROP_NOTIFY_EVENT_CLASS::FireOnChanged(pT->GetUnknown(), dispID);
	}
};
*/
/*
template<class N> class ATL_NOVTABLE CPDListener
{
public:
	virtual void Notified() = 0;
};

class ATL_NOVTABLE CPDNotifyListeners
{
public:
	CPDNotifyListeners()
	{
		m_pListener = 0;
	}

	CArray<CPDListener*,CPDListener*> m_listeners;

	void AddListener(CPDListener* listener)
	{
		m_listeners.Add(listener);
	}

	void Notify()
	{
		for (int i = 0; i < m_listeners.GetSize(); i++)
		{
			m_listeners[i]->Notified();
		}
	}
};
*/

/*
#include "UIDialog.h"
#include "DlgSheetEx.h"
#include "DlgManagerEx.h"
#include "UIFrameImpl.h"
#include "UIMDIChild.h"
*/