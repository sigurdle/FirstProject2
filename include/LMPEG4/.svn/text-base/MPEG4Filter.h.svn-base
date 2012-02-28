#ifndef __MPEG4FILTER_H__
#define __MPEG4FILTER_H__

namespace System
{
namespace MediaShow
{

class MPEG4Filter : public BaseFilterImpl	// ILMediaFilter
{
public:
	class CInputPin : public BasePinImpl
	{
	public:
		CTOR CInputPin();

		virtual ErrorCode CheckConnect(IPin* pPin);
		virtual void BreakConnect();
		virtual ErrorCode CheckMediaType(MediaType* mt);
		virtual ErrorCode CompleteConnect(IPin* pPin);

		inline MPEG4Filter* GetFilter() const
		{
			return (MPEG4Filter*)m_pFilter;
		}
	};

	class COutputPin : public BasePinImpl
	{
	public:
		CTOR COutputPin() : BasePinImpl(PINDIR_OUTPUT)
		{
			m_pTrack = NULL;
		}

		Mpeg4::Track* m_pTrack;

		virtual ErrorCode GetMediaType(int iPosition, MediaType** pMediaType)
		{
			if (iPosition == 0)
			{
				MediaType* mediaType;
				//mediaType.Create();//sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

					//memcpy(mediaType->pbFormat, m_pWaveFormat, sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

				mediaType = new MediaType(LMEDIATYPE_Stream);
				//mediaType->subtype = FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

				*pMediaType = mediaType;

				return Success;
	#if 0
				if (m_streamType == 3)
				{
					CLMediaType mediaType;
					mediaType.Create();//sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

					//memcpy(mediaType->pbFormat, m_pWaveFormat, sizeof(WAVEFORMATEX)+m_pWaveFormat->cbSize);

					mediaType->majortype = LMEDIATYPE_Scene;
					//mediaType->subtype = FOURCCMap(m_pAVIStream->m_aviStreamHeader.fccHandler);

					*pMediaType = mediaType.Detach();

					return S_OK;
				}
				else if (m_streamType == 0x4)	// Visual
				{
					/*
					if (m_objectTypeIndication == 0x20)	// MPEG4 Video
					{
					}
					else
					{
						ATLASSERT(0);
					}
					*/
				}
	#endif
			}
			else
			{
				*pMediaType = NULL;
				return Success_False;
			}
		}

		virtual ErrorCode CheckMediaType(MediaType* mt)
		{
			if (mt->GetMajorType() != LMEDIATYPE_Stream)	// ??
				return Error;

			return Success;
		}

	//	STDMETHOD(Render)(ILPin *ppinOut, ILGraphBuilder *pGraph);
		inline MPEG4Filter* GetFilter() const
		{
			return (MPEG4Filter*)m_pFilter;
		}
	};

	CTOR MPEG4Filter()
	{
		m_pMovie = new Mpeg4::Movie;

		m_pInputPin = new CInputPin;
		m_pInputPin->m_pFilter = this;
		m_pInputPin->m_id = WSTR("Stream Input");
		AddPin(m_pInputPin);
	}

	Mpeg4::Movie* m_pMovie;

	Stream m_stream;
	CInputPin* m_pInputPin;

//	CMovieHeader m_movieHeader;
//	CInitialObjectDescriptor m_initialObjectDescriptor;
//	CArray<CObjectDescriptor*,CObjectDescriptor*> m_od;
//	CArray<CTrack*,CTrack*> m_tracks;
/*
	CTrack* GetTrackById(DWORD trackID);

	ErrorCode ReceiveObjectDescriptorUpdate(CTrack* pTrack, long ODid, WORD refIndex)
	{
		// Remove any previous
		for (int i = 0; i < m_od.GetSize(); i++)
		{
			if (m_od[i]->m_ObjectDescriptorID == ODid)
			{
				delete m_od[i];
				m_od.RemoveAt(i);
				break;
			}
		}

		CObjectDescriptor* pOD = new CObjectDescriptor;
		pOD->m_pTrack = pTrack;
		pOD->m_ObjectDescriptorID = ODid;
		pOD->m_refIndex = refIndex;

		m_od.Add(pOD);

	// TODO wait

		return S_OK;
	}

	ErrorCode ReadFile(ByteStreamWrapper *stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadMovie(ByteStreamWrapper *stream, LONGLONG atomStartPos, LONGLONG atomSize);
	ErrorCode ReadCompressedMovie(ByteStreamWrapper *stream, LONGLONG atomStartPos, LONGLONG atomSize);
*/
// IMP4File
public:
//	STDMETHOD(OpenStream)(/*[in]*/ IStream* stream);

//	STDMETHOD(Run)(LONGLONG tStart);
};

}	// LMedia
}

#endif // __MPEG4FILTER_H__
