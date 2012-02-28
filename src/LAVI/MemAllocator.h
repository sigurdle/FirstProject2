#ifndef __MemAllocator_h__
#define __MemAllocator_h__

namespace System
{
namespace Media
{

	class CMemAllocator;

	class CSample : 
		public MediaSampleImpl<IMediaSample>
	{
	public:
		CSample()
		{
			//m_mediaType = NULL;
//			m_pBuffer = NULL;

			m_dwRef = 0;

			m_pMemAllocator = NULL;

			m_pointer = NULL;
			m_dwBytes = 0;
			m_dwActualBytes = 0;

		}

		~CSample()
		{
			if (m_pointer)
			{
				delete m_pointer;//GlobalFree(m_pointer);
				m_pointer = NULL;
			}
			/*
			if (m_pBuffer)
			{
				m_pBuffer->m_pMemAllocator->ReleaseBuffer(this);
			}
			*/
		}

		//CBuffer* m_pBuffer;

	//	CInputPin* m_pInput;
	//	ILMediaType* m_mediaType;

		ULONG m_dwRef;

//		BOOL m_bFree;
		CMemAllocator* m_pMemAllocator;

		uint8 * m_pointer;
		uint m_dwBytes;
		uint m_dwActualBytes;

		ULONG AddRef()
		{
			m_dwRef++;
			return m_dwRef;
		}

		ULONG Release()
		{
			ASSERT(m_dwRef > 0);
			m_dwRef--;
			return m_dwRef;
		}

	public:
		ErrorCode LockBits(LSampleData* pVal)
		{
			//if (m_pBuffer)
			{
				pVal->idata = m_pointer;
				return Success;
			}
			/*
			else
			{
				ASSERT(0);
				return E_FAIL;
			}
			*/
		}

		ErrorCode UnlockBits()
		{
			/*
			if (m_pBuffer)
			*/
			{
				return Success;
			}
			/*
			else
			{
				ASSERT(0);
				return E_FAIL;
			}
			*/
		}

		/*
		STDMETHOD(GetMediaType)(ILMediaType **pVal)
		{
			*pVal = m_mediaType;
			(*pVal)->AddRef();
			return S_OK;
		}
		*/

		virtual ULONG GetActualDataLength()
		{
			//if (m_pBuffer)
			{
				return m_dwActualBytes;
			}
			/*
			else
			{
				ASSERT(0);
				return 0;
			}
			*/
		}

		virtual ErrorCode SetActualDataLength(ULONG length)
		{
			//if (m_pBuffer)
			{
				if (length > m_dwBytes)
				{
					ASSERT(0);
					return VFW_E_BUFFER_OVERFLOW;
				}

				m_dwActualBytes = length;

				return Success;
			}
			/*
			else
			{
				ASSERT(0);
				return E_FAIL;
			}
			*/
		}
	};

	class CMemAllocator : 
		public IMemAllocator
	{
	public:
		CMemAllocator()
		{
	//		m_pInputPin = NULL;
//			m_crit.Init();
		}

	//	CInputPin* m_pInputPin;

		vector<CSample*> m_buffers;

		CriticalSection m_crit;

	public:
		ErrorCode GetBuffer(ULONG dwBytes, IMediaSample* *pVal)
		{
			//EnterCriticalSection(&m_pInputPin->m_pLock);
			m_crit.Lock();

		//	CSample* pSample = new CSample;
		//	pSample->AddRef();

			for (int i = 0; i < m_buffers.GetSize(); i++)
			{
				if (m_buffers[i]->m_dwRef == 0)
				{
					m_buffers[i]->m_dwRef++;
				//	pSample->m_pBuffer = m_buffers[i];

				//	*pVal = pSample;

				m_crit.Unlock();
//					LeaveCriticalSection(&m_pInputPin->m_pLock);

					*pVal = m_buffers[i];

					return Success;
				}
			}

			CSample* pBuffer = new CSample;
			pBuffer->m_pMemAllocator = this;
			pBuffer->m_dwRef = 1;
			m_buffers.Add(pBuffer);
			dwBytes = 1000000;
			pBuffer->m_pointer = (uint8 *)new uint8[dwBytes];
			pBuffer->m_dwBytes = dwBytes;
			pBuffer->m_dwActualBytes = dwBytes;

			//pSample->m_pBuffer = pBuffer;

			*pVal = pBuffer;

			//LeaveCriticalSection(&m_pInputPin->m_pLock);
			m_crit.Unlock();

			return Success;
		}

		ErrorCode ReleaseBuffer(IMediaSample* pBuffer)
		{
			// ??
#if 0
			CSample* pSample = static_cast<CSample*>(pBuffer);
			ASSERT(pSample->m_bFree == FALSE);

			pSample->m_pBuffer->m_bFree = TRUE;
			pSample->m_pBuffer = NULL;
#endif

			return Success;
		}
	};

}	// Media
}

#endif // __MemAllocator_h__
