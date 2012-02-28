#ifndef __LMEDIAIMPL_H_
#define __LMEDIAIMPL_H_

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/LFC.typeinfo"
#else
#include "LFC/LFC.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/XML.typeinfo"
#else
#include "XML/XML.h"
#endif

#ifndef LMEDIAEXT
#define LMEDIAEXT DECLSPEC_DLLIMPORT
#endif

#if _MSC_VER
#pragma warning(disable : 4200) // zero-sized array in struct/union

#endif

/*
namespace System
{
namespace MSWindows
{
typedef struct HWND__ * HWND;

}
}
*/

namespace System
{
namespace MediaShow
{

/* Forward Declarations */ 


enum PIN_DIRECTION
{
	PINDIR_INPUT	= 0,
	PINDIR_OUTPUT	= 1
};

enum FILTER_STATE
{
	State_Stopped	= 0,
	State_Paused	= 1,
	State_Running	= 2
};

enum StreamType
{
	StreamType_Unknown	= 0,
	StreamType_Video	= 1,
	StreamType_Audio	= 2
};

class MediaType;
    
    class IBasicVideo
    {
    public:
        virtual /* [helpstring][propput] */ int set_WindowStyle( 
            /* [in] */ long newVal) = 0;
        
        virtual /* [helpstring][propput] */ int set_Owner( 
            /* [in] */ HWND hWnd) = 0;
        
#if 0
        virtual /* [helpstring] */ int STDMETHODCALLTYPE SetRect( 
		  /* [in] */ LDraw::Rect rect) = 0;
#endif   
    };
    
   
class ISystemClock
{
public:
};


    
interface IVideoRenderer
{
};


interface IFilterMapper
{
};
    
interface IFilterGraph;
interface IBaseFilter;
interface IPin;
interface IReferenceClock;

//
// MessageId: VFW_E_ALREADY_CONNECTED
//
// MessageText:
//
//  At least one of the pins involved in the operation is already connected.%0
//
#define MEDIA_E_ALREADY_CONNECTED          ((int)0x80040204L)

//
// MessageId: VFW_E_BUFFER_OVERFLOW
//
// MessageText:
//
//  The buffer is not big enough.%0
//
#define MEDIA_E_BUFFER_OVERFLOW            ((int)0x8004020DL)

///////////////////////////////////////////////////////////

class LMEDIAEXT MediaTypeFormat : public System::Object
{
public:
	virtual MediaTypeFormat* Clone() const = 0;
};

struct LSampleData
{
	int width;
	int height;
	int rowbytes;
	uint bitcount;

	uint8* idata;	// interleaved data

	int channels;
	uint8* cdata[4];	// channel data
};

struct BitmapInfoHeader
{
	uint32      biSize;
	int32       biWidth;
	int32       biHeight;
	uint16       biPlanes;
	uint16       biBitCount;
	uint32      biCompression;
	uint32      biSizeImage;
	int32       biXPelsPerMeter;
	int32       biYPelsPerMeter;
	uint32      biClrUsed;
	uint32      biClrImportant;
};

struct RGBQuad
{
	uint8    rgbBlue;
	uint8    rgbGreen;
	uint8    rgbRed;
	uint8    rgbReserved;
};

struct BitmapInfo
{
	BitmapInfoHeader bmiHeader;
	RGBQuad bmiColors[0];
};

struct VIDEOINFOHEADER
{
    uint32               dwBitRate;
    uint32               dwBitErrorRate;
    LONGLONG      AvgTimePerFrame;
    uint32               dwInterlaceFlags;
    uint32               dwCopyProtectFlags;
    uint32               dwPictAspectRatioX;
    uint32               dwPictAspectRatioY;
    //union {
        uint32           dwControlFlags;
     //   uint32           dwReserved1;
    //};
    uint32               dwReserved2;
    BitmapInfoHeader    bmiHeader;
};

class LMEDIAEXT VideoInfoHeader : public MediaTypeFormat
{
public:
#if 0
	LDraw::Rect                rcSource;
    LDraw::Rect                rcTarget;
#endif

	CTOR VideoInfoHeader(int numColors = 0);
	~VideoInfoHeader();

	MediaTypeFormat* Clone() const;

	ULONG GetWidth() const;

	ULONG GetHeight() const;

	VIDEOINFOHEADER* vih;
};

class LMEDIAEXT WaveFormat : public MediaTypeFormat
{
public:
	CTOR WaveFormat();
	~WaveFormat();

	MediaTypeFormat* Clone() const;

	WAVEFORMATEX* wf;
};

#define TIME_SCALE	((LONGLONG)10000000)

interface IByteData
{
	virtual ULONG Read(void *pv, LONGLONG bytepos, ULONG cb) = 0;
	virtual LONGLONG GetSize() = 0;
};

class LMEDIAEXT ByteStreamWrapper : public IO::Stream
	//public System::IO::ISequentialByteStream
{
public:
	CTOR ByteStreamWrapper(IByteData* stream);

	/*
	ULONG AddRef();

	ULONG Release();
	*/

	virtual size_t Read(void* pv, size_t cb) override;
	virtual size_t Write(const void* pv, size_t cb) override;
	virtual uint64 Seek(int64 offset, IO::SeekOrigin origin) override;
	virtual uint64 GetSize() override;
	virtual ByteStreamWrapper* Clone() const;

	IByteData* GetBaseData();

protected:

	IByteData* m_stream;
	uint64 m_pos;
};

#if 0
struct __declspec(uuid("ECAC5835-2DBA-44c1-B315-824B514B190C"))
ILVideoMediaType : public ILMediaType
{
public:
	virtual int __stdcall GetWidth(long *pVal) = 0;
	virtual int __stdcall GetHeight(long *pVal) = 0;
	virtual int __stdcall GetBitCount(long *pVal) = 0;
	virtual int __stdcall GetPalette(ILPalette* *pVal) = 0;
};
#endif

#if 0
struct __declspec(uuid("9F5F0CC1-ABD6-4436-91D6-5A3E479DBB8B"))
ILBIFSMediaType : public ILMediaType
{
public:
	/*
	virtual int __stdcall GetWidth(long *pVal) = 0;
	virtual int __stdcall GetHeight(long *pVal) = 0;
	virtual int __stdcall GetBitCount(long *pVal) = 0;
	virtual int __stdcall GetPalette(ILPalette* *pVal) = 0;
	*/
};
#endif

/*
struct __declspec(uuid("124CB57A-C624-4154-B448-2A1DDF1D9CBF"))
ILAudioMediaType : public ILMediaType
{
public:
	virtual int __stdcall GetFormat(WAVEFORMATEX* pVal) = 0;
	virtual int __stdcall GetSamples(ULONG *pVal) = 0;
};
*/

interface IMediaSample
{
	virtual ULONG AddRef() = 0;
	virtual ULONG Release() = 0;
	virtual int GetMediaType(MediaType *pVal) = 0;
	virtual int GetTime(LONGLONG* pTimeStart, LONGLONG* pTimeEnd) = 0;
	virtual int SetTime(LONGLONG* pTimeStart, LONGLONG* pTimeEnd) = 0;
	virtual ULONG GetActualDataLength(void) = 0;
	virtual int SetActualDataLength(ULONG length) = 0;
	virtual int LockBits(LSampleData* pVal) = 0;
	virtual int UnlockBits() = 0;
};

/*
struct DECLSPEC_UUID("49D13E12-A538-47f7-9CFA-8E1093894DC6")
ILVideoSample : ILMediaSample
{
//	virtual int __stdcall GetWidth(long* pVal) = 0;
//	virtual int __stdcall GetHeight(long* pVal) = 0;
//	virtual int __stdcall GetPalette(ILPalette* *pVal) = 0;
};

struct DECLSPEC_UUID("E3EC2341-A0C0-48a8-B501-239DFF403BE0")
ILBIFSSample : ILMediaSample
{
	virtual int __stdcall GetScene(Object* *pVal) = 0;
};
*/

/*
struct DECLSPEC_UUID("FC9363B5-3C34-493e-9BC0-10647BAEE944")
ILAudioSample : ILMediaSample
{
//	virtual int __stdcall GetWidth(long* pVal) = 0;
//	virtual int __stdcall GetHeight(long* pVal) = 0;
//	virtual int __stdcall GetSize(ULONG *pVal) = 0;
//	virtual int __stdcall LockBits(LPBYTE *pVal) = 0;
//	virtual int __stdcall UnlockBits() = 0;
//	virtual int __stdcall GetPalette(ILPalette* *pVal) = 0;
};
*/

/*
struct __declspec(uuid("39962269-651B-49ff-B56F-6272B867EF04"))
ILVideo : ILMediaStream
{
	virtual int __stdcall GetWidth(long *pVal) = 0;
	virtual int __stdcall GetHeight(long *pVal) = 0;
	virtual int __stdcall GetSample(ILVideoSample* *pVal) = 0;
	virtual int __stdcall SetSample(ILVideoSample* newVal) = 0;
};

struct __declspec(uuid("7516BA91-2909-45e2-9F54-02DCCB521741"))
ILAudio : ILMediaStream
{
	virtual int __stdcall GetSamples(LONGLONG *pVal) = 0;
	virtual int __stdcall GetFormat(WAVEFORMATEX *pVal) = 0;
	virtual int __stdcall GetChunkSize(long nchunk, ULONG* pVal) = 0;
	virtual int __stdcall ReadChunk(long nchunk, LPSTR buffer, ULONG nsamples) = 0;
};
*/

/*
struct __declspec(uuid("82CC6C5D-88E0-4ce6-9237-93E70D36ED2E"))
ILStreamInfo : IObject
{
	virtual int __stdcall GetBitRate(long* pVal) = 0;
	virtual int __stdcall GetCodec(BSTR *pVal) = 0;
};

struct __declspec(uuid("56C76414-A798-4a5c-84E3-CB286AD713FC"))
ILVideoStreamInfo : IObject
{
	virtual int __stdcall GetFrameRate(double* pVal) = 0;
};
*/

enum TimeUnit
{
	TimeFormat_ref,
	TimeFormat_frame,
	TimeFormat_sample,
	TimeFormat_byte,
};

interface IMediaSeeking
{
	virtual int GetDuration(TimeUnit unit, LONGLONG* pVal) = 0;
	virtual int GetCurrentPosition(TimeUnit unit, LONGLONG* pVal) = 0;
	virtual int Seek(TimeUnit unit, LONGLONG t) = 0;
};

//EXTERN_C const IID IID_ILEnumMediaTypes;

interface IEnumMediaTypes
{
	virtual ULONG Next(ULONG cMediaTypes, MediaType **ppMediaTypes) = 0;
	virtual int Skip(ULONG cMediaTypes) = 0;
	virtual int Reset(void) = 0;
	virtual int Clone(IEnumMediaTypes **ppEnum) = 0;
};

//EXTERN_C const IID IID_ILEnumPins;

interface IEnumPins
{
	virtual ULONG Next(ULONG cPins, IPin **ppPins) = 0;
	virtual bool Skip(ULONG cPins) = 0;
	virtual void Reset(void) = 0;
	virtual IEnumPins* Clone() = 0;
};

interface IPin
{
	virtual int Connect(IPin *pReceivePin, MediaType* pmt) = 0;
	virtual int ReceiveConnection(IPin *pConnector, MediaType* pmt) = 0;
	virtual int Disconnect() = 0;
	virtual IPin* ConnectedTo() = 0;
	virtual int ConnectionMediaType(MediaType** pmt) = 0;
	virtual IEnumMediaTypes* EnumMediaTypes() = 0;
	virtual int QueryAccept(MediaType* pmt) = 0;
	virtual PIN_DIRECTION QueryDirection() const = 0;
	virtual IBaseFilter* QueryFilter() const = 0;
	virtual int EndOfStream() = 0;
};

interface IMemAllocator
{
	virtual int GetBuffer(ULONG dwBytes, IMediaSample* *pVal) = 0;
	virtual int ReleaseBuffer(IMediaSample* pBuffer) = 0;
};

interface IMemInputPin
{
	virtual IMemAllocator* GetAllocator() = 0;
	virtual int Receive(IMediaSample *pSample) = 0;
};

interface IMediaFilter
{
	virtual int Run(LONGLONG tStart) = 0;
	virtual int Stop() = 0;
	virtual int Pause() = 0;
	virtual FILTER_STATE GetState() = 0;
	virtual IReferenceClock* GetSyncSource() = 0;
	virtual void SetSyncSource(IReferenceClock *pClock) = 0;
};

interface IBaseFilter : public IMediaFilter
{
	virtual int SetFilterGraph(IFilterGraph* pFilterGraph, StringIn pName) = 0;
//	virtual int __stdcall GetPinCount(long *pVal) = 0;
//	virtual int __stdcall GetPin(long index, ILPin* *pVal) = 0;
	virtual IEnumPins* EnumPins() = 0;
	virtual IPin* FindPin(StringIn Id) = 0;
};

interface IReferenceClock
{
	virtual int GetTime(LONGLONG *pVal) = 0;
	virtual int AdviseTime(LONGLONG rtBaseTime, LONGLONG rtStreamTime, HANDLE hEvent, ULONG_PTR *pdwAdviseCookie) = 0;
};

interface IDirectSound
{
	virtual int SetWindow(HWND hWnd) = 0;
};

interface IBIFSOutput
{
	virtual int FindODById(int ODid, Object* *pVal) = 0;
};

interface IBIFSScene
{
	virtual int getBIFSContext(IBIFSOutput* *pVal) = 0;
	virtual int setBIFSContext(IBIFSOutput *newVal) = 0;
};

/*
class ILFilterMapper2 : public _Object
{
public:
#if _WINDOWS
	virtual int RegisterFilter(REFCLSID clsidFilter, LPCWSTR name, HINSTANCE hInst, long resID) = 0;
#endif
};
*/

interface IFilterGraph
{
	virtual void LoadURL(System::StringW* url) = 0;
	virtual void Run() = 0;
	virtual void Stop() = 0;
	
	virtual void AddFilter(IBaseFilter *pFilter) = 0;
	virtual void RemoveFilter(IBaseFilter *pFilter) = 0;
	virtual int ConnectDirect(IPin *ppinOut, IPin *ppinIn, MediaType* pmt) = 0;
//	virtual int AddSourceFilterForMoniker(IMoniker *pMoniker, IBindCtx *pCtx, LPCWSTR lpcwstrFilterName, ILBaseFilter* *ppFilter) = 0;
	//	virtual int __stdcall QueryFilterInterface(REFIID riid, IObject* *pVal) = 0;
	//	virtual int __stdcall QueryFilterInterface(const type_info& riid, IObject* *pVal) = 0;
	
	virtual void Notify(IBaseFilter* pFilter, long nEvent) = 0;
};

interface IGraphBuilder : public IFilterGraph
{
	virtual ErrorCode Connect(IPin *ppinOut, IPin *ppinIn) = 0;
	virtual ErrorCode Render(IPin *ppinOut) = 0;
};

class IStreamBuilder
{
public:
	virtual ErrorCode Render(IPin *ppinOut, IGraphBuilder *pGraph) = 0;
};

class LMEDIAEXT BytePattern
{
public:
	CTOR BytePattern();
	CTOR BytePattern(const BytePattern& other);

	~BytePattern();

	//int m_refcount;

	LONGLONG m_offset;
	ULONG m_length;
	uint8* m_mask;
	uint8* m_value;

	BytePattern& operator = (const BytePattern& other);
};

class LMEDIAEXT CMatch
{
public:
	CTOR CMatch();
	CTOR CMatch(const CMatch& other);

	CMatch& operator = (const CMatch& other);

	//CArray<BytePattern,BytePattern&> m_patterns;
	vector<BytePattern> m_patterns;
};

class LMEDIAEXT CStreamContent
{
public:
	//CArray<CMatch,CMatch&> m_matches;
	vector<CMatch> m_matches;
};

class LMEDIAEXT CLRegMediaType
{
public:
	GUID m_majortype;
	GUID m_minorType;

	CStreamContent m_streamcontent;
};

}	// MediaShow
}

//#include <initguid.h>
#undef INITGUID
#include "Luuids.h"

#include "_mmsystem.h"

namespace System
{
namespace MediaShow
{

// immutable
class LMEDIAEXT MediaType : public System::Object
{
public:
	CTOR MediaType();
	CTOR MediaType(GUID majortype, GUID subtype = GUID_NULL, GUID formattype = GUID_NULL, MediaTypeFormat *pbFormat = NULL);

	GUID GetMajorType() const
	{
		return m_majortype;
	}

	GUID GetSubType() const
	{
		return m_subtype;
	}

	MediaTypeFormat* GetFormat() const
	{
		return m_pbFormat;
	}

	MediaType* Clone() const;

// TODO protected:

	GUID m_majortype;
	GUID m_subtype;
	GUID m_formattype;
	MediaTypeFormat *m_pbFormat;

	//void SetFormat(MediaTypeFormat* pFormat);
};

class LMEDIAEXT CLEnumMediaTypes :
//	public CComObjectRootEx<CComSingleThreadModel>,
	public IEnumMediaTypes
{
public:
	CTOR CLEnumMediaTypes()//std::vector<LMediaType*>& list) : m_list(list)
	{
//		m_pos = NULL;
	}

	vector<MediaType*> m_list;
	MediaType** m_pos;

public:
	ULONG Next(ULONG celt, MediaType **rgelt);

	ErrorCode Skip(/* [in] */ ULONG celt)
	{
#if 0
		int n;
		for (n = 0; n < celt; n++)
		{
			m_list.GetNext(m_pos);
			if (m_pos == NULL) break;
		}

		if (n == celt)
			return S_OK;
		else
			return S_FALSE;
#endif
		ASSERT(0);
		return 0;
	}

	ErrorCode Reset(void)
	{
#if 0
		m_pos = m_list.GetHeadPosition();
#endif
		return 0;
	}

	ErrorCode Clone(/* [out] */ IEnumMediaTypes **ppenum)
	{
		ASSERT(0);
#if 0
		if (ppenum == NULL) return E_POINTER;
		*ppenum = NULL;

		CComObject<CLEnumMediaTypes>* pEnum;
		CComObject<CLEnumMediaTypes>::CreateInstance(&pEnum);
		if (pEnum)
		{
			pEnum->AddRef();

			pEnum->m_list = m_list;
			pEnum->m_pos = m_pos;

			*ppenum = pEnum;
		}
#endif
		return 0;
	}
};

class BaseFilterImpl;

class LMEDIAEXT BasePinImpl : public Object, public IPin
{
public:
	CTOR BasePinImpl(PIN_DIRECTION dir);
	~BasePinImpl();

	// Override this to also check for other features on the pin
	virtual ErrorCode CheckConnect(IPin* pPin);

	virtual ErrorCode Run(LONGLONG tStart);

	virtual ErrorCode Pause();

	virtual void BreakConnect();

	// You must override this
	virtual ErrorCode CheckMediaType(MediaType* mt) = 0;

	virtual ErrorCode AgreeMediaType(IPin* pReceivePin, MediaType* mt);

	// Input pins are not required to have any preferred mediatypes
	// Output pins are required to have at least one
	virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType);

	virtual ErrorCode SetMediaType(MediaType* pmt);

	virtual ErrorCode CompleteConnect(IPin *pPin);

	virtual ErrorCode AttemptConnection(IPin *pReceivePin, MediaType* mt);

	/*
pReceivePin 
Pointer to the receiving pin's IPin interface. 

mt 
a MediaType object that limits the possible media types, or NULL. 

pEnum 
Pointer to an ILEnumMediaTypes interface, used to enumerate the list of media types.

*/
	virtual ErrorCode TryMediaTypes(IPin* pReceivePin, MediaType* mt, IEnumMediaTypes* pEnum);

	ErrorCode QueryAccept(MediaType* pmt);
	ErrorCode Connect(IPin* pReceivePin, MediaType* pmt);
	ErrorCode ReceiveConnection(IPin* pConnector, MediaType* pMediaType);
	ErrorCode Disconnect();
	virtual IPin* ConnectedTo();
	ErrorCode ConnectionMediaType(MediaType** pmt);
	PIN_DIRECTION QueryDirection() const;
	ErrorCode EndOfStream();

	IEnumMediaTypes* EnumMediaTypes();

	IBaseFilter* QueryFilter() const;

	String m_id;
	BaseFilterImpl* m_pFilter;

protected:

	PIN_DIRECTION m_dir;
	IPin* m_connectedTo;
	MediaType* m_mt;
};

class LMEDIAEXT BaseOutputPinImpl :
	public BasePinImpl
{
public:
	CTOR BaseOutputPinImpl();

	IMemInputPin* m_pInputPin;
	IMemAllocator* m_pAllocator;

	virtual ErrorCode CheckConnect(IPin* pPin);

	virtual void BreakConnect();

	virtual ErrorCode CompleteConnect(IPin* pPin);
};

class LMEDIAEXT CLEnumPins : public Object, public IEnumPins
{
public:
	CTOR CLEnumPins(vector<BasePinImpl*>& arr);

	BasePinImpl** m_pos;

public:

	ULONG Next(ULONG celt, IPin** rgelt);
	bool Skip(ULONG celt);
	void Reset();
	IEnumPins* Clone();

private:

	vector<BasePinImpl*>& m_list;
};

class LMEDIAEXT BaseFilterImpl : public Object, public IBaseFilter
{
public:
	CTOR BaseFilterImpl();
	~BaseFilterImpl();

	void AddPin(BasePinImpl* pin);

	void RemovePin(BasePinImpl* pin)
	{
#if 0
		UPOSITION pos = m_pins.Find(pin);
		ASSERT(pos);
		pin->Release();
		m_pins.RemoveAt(pos);
#endif
	}

// IMediaFilter
	virtual ErrorCode Run(LONGLONG tStart);
	virtual ErrorCode Stop();
	virtual ErrorCode Pause();

	FILTER_STATE GetState();

	IReferenceClock* GetSyncSource();

	void SetSyncSource(IReferenceClock *pClock);

// IBaseFilter

	IEnumPins* EnumPins();
	IPin* FindPin(StringIn Id);

	virtual ErrorCode SetFilterGraph(IFilterGraph* pFilterGraph, StringIn pName);

public:	// TODO

	vector<BasePinImpl*> m_pins;
	IFilterGraph* m_pFilterGraph;
	CriticalSection m_criticalSection;
	IReferenceClock* m_clock;
	LONGLONG m_tStart;

protected:

	FILTER_STATE m_state;
};

template<class IBase> class MediaSampleImpl : public IBase
{
public:

	CTOR MediaSampleImpl()
	{
		m_flags = 0;	// times are invalid
	}

	uint32 m_flags;
	LONGLONG m_timeStart;
	LONGLONG m_timeEnd;

	virtual ErrorCode GetTime(LONGLONG* pTimeStart, LONGLONG* pTimeEnd)
	{
		if (m_flags & 1)
		{
			if (pTimeStart) *pTimeStart = m_timeStart;
			if (pTimeEnd) *pTimeEnd = m_timeEnd;
		}
		else
		{
			if (pTimeStart) *pTimeStart = 0;
			if (pTimeEnd) *pTimeEnd = 0;
		}

		return Success;
	}

	virtual ErrorCode SetTime(LONGLONG* pTimeStart, LONGLONG* pTimeEnd)
	{
		if (pTimeStart == NULL && pTimeEnd == NULL)
		{
			m_flags &= ~1;	// times are invalid
		}
		else
		{
			// Both must be either valid or invalid

			if (pTimeStart == NULL) return Error;
			if (pTimeEnd == NULL) return Error;

			m_timeStart = *pTimeStart;
			m_timeEnd = *pTimeEnd;

			m_flags |= 1;	// times are valid
		}

		return Success;
	}

	virtual ErrorCode GetMediaType(MediaType* ppmt)
	{
		if (ppmt == NULL) throw (int)Error_NullPointerArgument;
		ASSERT(0);
	//	ppmt = NULL->majortype = GUID_NULL;
		return Success;
	}

	ErrorCode SetActualDataLength(ULONG length)
	{
		return 0;
	}

	ULONG GetActualDataLength()
	{
		return 0;
	}
};

interface IQualProp
{
	virtual ErrorCode get_AvgFrameRate(unsigned int* piAvgFrameRate) = 0;
	virtual ErrorCode get_FramesDrawn(unsigned int* pcFramesDrawn) = 0;
	virtual ErrorCode get_FramesDroppedInRenderer(unsigned int* pcFramesDropped) = 0;
	virtual ErrorCode get_Jitter(unsigned int* piJitter) = 0;
	virtual ErrorCode get_AvgSyncOffset(int *piAvg) = 0;

};

}	// MediaShow
}

#include "LRegFilter.h"
#include "LFilterGraph.h"
#include "URLSource.h"
#include "WaveOutput.h"

#endif // __LMEDIAIMPL_H_
