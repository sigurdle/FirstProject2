// ASFLoader.cpp : Implementation of CASFLoader
#include "stdafx.h"
#include "LASF.h"
#include "ASFLoader.h"

// Top-Level

// ASF_Header_Object	75B22630-668E-11CF-A6D9-00AA0062CE6C
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Data_Object	75B22636-668E-11CF-A6D9-00AA0062CE6C
static const GUID ASF_Data_Object = 
{ 0x75B22636, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Simple_Index_Object	33000890-E5B1-11CF-89F4-00A0C90349CB
static const GUID ASF_Simple_Index_Object = 
{ 0x33000890, 0xE5B1, 0x11CF, { 0x89, 0xF4, 0x00, 0xA0, 0xC9, 0x03, 0x49, 0xCB } };

/*
ASF_Index_Object	D6E229D3-35DA-11D1-9034-00A0C90349BE
ASF_Media_Object_Index_Object	FEB103F8-12AD-4C64-840F-2A1D2F7AD48C
ASF_Timecode_Index_Object	3CB73FD0-0C4A-4803-953D-EDF7B6228F0C
*/

// ASF Header Object GUIDs

//ASF_File_Properties_Object	8CABDCA1-A947-11CF-8EE4-00C00C205365
static const GUID ASF_File_Properties_Object = 
{ 0x8CABDCA1, 0xA947, 0x11CF, { 0x8E, 0xE4, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65 } };

// ASF_Stream_Properties_Object	B7DC0791-A9B7-11CF-8EE6-00C00C205365
static const GUID ASF_Stream_Properties_Object = 
{ 0xB7DC0791, 0xA9B7, 0x11CF, { 0x8E, 0xE6, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65 } };

// ASF_Header_Extension_Object	5FBF03B5-A92E-11CF-8EE3-00C00C205365
static const GUID ASF_Header_Extension_Object = 
{ 0x5FBF03B5, 0xA92E, 0x11CF, { 0x8E, 0xE3, 0x00, 0xC0, 0x0C, 0x20, 0x53, 0x65 } };

// ASF_Codec_List_Object	86D15240-311D-11D0-A3A4-00A0C90348F6
static const GUID ASF_Codec_List_Object = 
{ 0x86D15240, 0x311D, 0x11D0, { 0xA3, 0xA4, 0x00, 0xA0, 0xC9, 0x03, 0x48, 0xF6 } };

#if 0
// ASF_Script_Command_Object	1EFB1A30-0B62-11D0-A39B-00A0C90348F6
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Marker_Object	F487CD01-A951-11CF-8EE6-00C00C205365
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Bitrate_Mutual_Exclusion_Object	D6E229DC-35DA-11D1-9034-00A0C90349BE
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };
#endif

// ASF_Error_Correction_Object	75B22635-668E-11CF-A6D9-00AA0062CE6C
static const GUID ASF_Error_Correction_Object = 
{ 0x75B22635, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Content_Description_Object	75B22633-668E-11CF-A6D9-00AA0062CE6C
static const GUID ASF_Content_Description_Object = 
{ 0x75B22633, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

#if 0
// ASF_Extended_Content_Description_Object	D2D0A440-E307-11D2-97F0-00A0C95EA850
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Content_Branding_Object	2211B3FA-BD23-11D2-B4B7-00A0C955FC6E
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Stream_Bitrate_Properties_Object	7BF875CE-468D-11D1-8D82-006097C9A2B2
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Content_Encryption_Object	2211B3FB-BD23-11D2-B4B7-00A0C955FC6E
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Extended_Content_Encryption_Object	298AE614-2622-4C17-B935-DAE07EE9289C
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Alt_Extended_Content_Encryption_Obj	FF889EF1-ADEE-40DA-9E71-98704BB928CE
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Digital_Signature_Object	2211B3FC-BD23-11D2-B4B7-00A0C955FC6E
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Padding_Object	1806D474-CADF-4509-A4BA-9AABCB96AAE8
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };
#endif

// GUIDs for the Stream Type 

// ASF_Audio_Media	F8699E40-5B4D-11CF-A8FD-00805F5C442B
static const GUID ASF_Audio_Media = 
{ 0xF8699E40, 0x5B4D, 0x11CF, { 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B } };

// ASF_Video_Media	BC19EFC0-5B4D-11CF-A8FD-00805F5C442B
static const GUID ASF_Video_Media = 
{ 0xBC19EFC0, 0x5B4D, 0x11CF, { 0xA8, 0xFD, 0x00, 0x80, 0x5F, 0x5C, 0x44, 0x2B } };

#if 0
// ASF_Command_Media	59DACFC0-59E6-11D0-A3AC-00A0C90348F6
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_JFIF_Media	B61BE100-5B4E-11CF-A8FD-00805F5C442B
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Degradable_JPEG_Media	35907DE0-E415-11CF-A917-00805F5C442B
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_File_Transfer_Media	91BD222C-F21C-497A-8B6D-5AA86BFC0185
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };

// ASF_Binary_Media	3AFB65E2-47EF-40F2-AC2C-70A90D71D343
static const GUID ASF_Header_Object = 
{ 0x75B22630, 0x668E, 0x11CF, { 0xA6, 0xD9, 0x00, 0xAA, 0x00, 0x62, 0xCE, 0x6C } };
#endif

////////////

// ASF_Reserved_2	86D15241-311D-11D0-A3A4-00A0C90348F6
static const GUID ASF_Reserved_2 = 
{ 0x86D15241, 0x311D, 0x11D0, { 0xA3, 0xA4, 0x00, 0xA0, 0xC9, 0x03, 0x48, 0xF6 } };

class CASFObject
{
public:
	ULARGE_INTEGER m_pos;
	GUID m_guid;
	ULONGLONG m_size;

	HRESULT Descend(ILByteStream* stream)
	{
		HRESULT hr;

		LARGE_INTEGER li;
		li.QuadPart = 0;
		hr = stream->Seek(li, STREAM_SEEK_CUR, &m_pos);
		if (FAILED(hr)) return hr;

		ULONG nRead;

		hr = stream->Read(&m_guid, 16, &nRead);
		if (FAILED(hr)) return hr;
		if (nRead != 16) return S_FALSE;//E_FAIL; End of file

		hr = stream->Read(&m_size, 8, &nRead);
		if (FAILED(hr)) return hr;
		if (nRead != 8) return E_FAIL;

		return S_OK;
	}

	HRESULT Ascend(ILByteStream* stream)
	{
		HRESULT hr;

		ULARGE_INTEGER curpos;
		LARGE_INTEGER li;
		li.QuadPart = 0;
		hr = stream->Seek(li, STREAM_SEEK_CUR, &curpos);
		if (FAILED(hr)) return hr;

		li.QuadPart = m_pos.QuadPart+m_size;

		if (curpos.QuadPart > li.QuadPart)
		{
			ATLTRACE("Read past object");
			ATLASSERT(0);
			return E_FAIL;
		}

		hr = stream->Seek(li, STREAM_SEEK_SET, NULL);
		if (FAILED(hr)) return hr;

		return S_OK;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CASFLoader

STDMETHODIMP CASFLoader::CInputPin::ReceiveConnection(ILPin* pConnector, ILMediaType* pMediaType)
{
	m_connectedTo = pConnector;

	CComQIPtr<ILByteStream> stream = m_connectedTo;
	if (stream == NULL) return E_NOINTERFACE;

	m_pFilter->m_stream = stream;

	HRESULT hr;
	ULONG nRead;

//	GUID guid;
//	ULONGLONG size;
//	m_pFilter->m_stream->Read(&guid, 16, &nRead);
//	m_pFilter->m_stream->Read(&size, 8, &nRead);
	CASFObject object;
	hr = object.Descend(m_pFilter->m_stream);
	if (FAILED(hr)) return hr;

	if (object.m_guid == ASF_Header_Object)
	{
		if (object.m_size < 30)
		{
			ATLTRACE("Object size is too small");
			return E_FAIL;
		}

		DWORD numHeaderObjects;
		m_pFilter->m_stream->Read(&numHeaderObjects, 4, &nRead);

	// This field must be set to the value 0x01. ASF parsers may safely ignore this value.
		BYTE reserved1;
		m_pFilter->m_stream->Read(&reserved1, 1, &nRead);

	// This field must be set to the value 0x02. If the this value is different when read, the application should fail to source the content.
		BYTE reserved2;
		m_pFilter->m_stream->Read(&reserved2, 1, &nRead);
		if (reserved2 != 0x2)
		{
			ATLTRACE("Object header contains unsupported value");
			return E_FAIL;
		}

		for (DWORD i = 0; i < numHeaderObjects; i++)
		{
			HRESULT hr;

			CASFObject object;
			hr = object.Descend(m_pFilter->m_stream);
			if (FAILED(hr)) return hr;

			if (object.m_guid == ASF_File_Properties_Object)
			{
				if (object.m_size < 104)
				{
					ATLTRACE("File Properties Object size is too small");
					return E_FAIL;
				}

				GUID FileID;
				m_pFilter->m_stream->Read(&FileID, 16, &nRead);

				ULONGLONG FileSize;
				m_pFilter->m_stream->Read(&FileSize, 8, &nRead);

				ULONGLONG CreationDate;
				m_pFilter->m_stream->Read(&CreationDate, 8, &nRead);

				ULONGLONG DataPacketsCount;
				m_pFilter->m_stream->Read(&DataPacketsCount, 8, &nRead);

				ULONGLONG PlayDuration;
				m_pFilter->m_stream->Read(&PlayDuration, 8, &nRead);

				ULONGLONG SendDuration;
				m_pFilter->m_stream->Read(&SendDuration, 8, &nRead);

				ULONGLONG Preroll;
				m_pFilter->m_stream->Read(&Preroll, 8, &nRead);

				DWORD Flags;
				m_pFilter->m_stream->Read(&Flags, 4, &nRead);
			//	Broadcast Flag		1 (LSB)
			//	Seekable Flag		1
			//	Reserved		30

				DWORD MinimumDataPacketSize;
				m_pFilter->m_stream->Read(&MinimumDataPacketSize, 4, &nRead);

				DWORD MaximumDataPacketSize;
				m_pFilter->m_stream->Read(&MaximumDataPacketSize, 4, &nRead);

				DWORD MaximumBitrate;
				m_pFilter->m_stream->Read(&MaximumBitrate, 4, &nRead);
			}
			else if (object.m_guid == ASF_Stream_Properties_Object)
			{
				if (object.m_size < 78)
				{
					ATLTRACE("Stream Properties Object size is too small");
					return E_FAIL;
				}

				GUID StreamType;
				m_pFilter->m_stream->Read(&StreamType, 16, &nRead);

				if (StreamType == ASF_Audio_Media)
				{
					MessageBeep(-1);
				}
				else if (StreamType == ASF_Video_Media)
				{
					MessageBeep(-1);
				}
				else
				{
					MessageBeep(-1);
				}


				/*
Stream Type	GUID	128
Error Correction Type	GUID	128
Time Offset	QWORD	64
Type-Specific Data Length	DWORD	32
Error Correction Data Length	DWORD	32
Flags	WORD	16
Stream Number		7 (LSB)
Reserved		8
Encrypted Content Flag		1
Reserved	DWORD	32
Type-Specific Data	BYTE	varies
Error Correction Data	BYTE	varies
*/
			}
			else if (object.m_guid == ASF_Header_Extension_Object)
			{
				if (object.m_size < 46)
				{
					ATLTRACE("Header Extension Object size is too small");
					return E_FAIL;
				}

				GUID Reserved1;
				m_pFilter->m_stream->Read(&Reserved1, 16, &nRead);
			// TODO: This value shall be set to ASF_Reserved_1 

				WORD Reserved2;
				m_pFilter->m_stream->Read(&Reserved2, 2, &nRead);
				if (Reserved2 != 6)
				{
					ATLTRACE("Unsupported value in Extension Header Object");
					return E_FAIL;
				}

				DWORD HeaderExtensionDataSize;
				m_pFilter->m_stream->Read(&HeaderExtensionDataSize, 4, &nRead);

				//Header Extension Data	BYTE	varies
			}
			else if (object.m_guid == ASF_Error_Correction_Object)
			{
				if (object.m_size < 44)
				{
					ATLTRACE("Error Correction Object size is too small");
					return E_FAIL;
				}

				/*
				Error Correction Type	GUID	128
				Error Correction Data Length	DWORD	32
				Error Correction Data	BYTE	varies
				*/
			}
			else if (object.m_guid == ASF_Content_Description_Object)
			{
				if (object.m_size < 34)
				{
					ATLTRACE("Content Description Object size is too small");
					return E_FAIL;
				}

				WORD TitleLength;
				m_pFilter->m_stream->Read(&TitleLength, 2, &nRead);

				WORD AuthorLength;
				m_pFilter->m_stream->Read(&AuthorLength, 2, &nRead);

				WORD CopyrightLength;
				m_pFilter->m_stream->Read(&CopyrightLength, 2, &nRead);

				WORD DescriptionLength;
				m_pFilter->m_stream->Read(&DescriptionLength, 2, &nRead);

				WORD RatingLength;
				m_pFilter->m_stream->Read(&RatingLength, 2, &nRead);

				/*
				Title	WCHAR	Varies
				Author	WCHAR	Varies
				Copyright	WCHAR	Varies
				Description	WCHAR	Varies
				Rating	WCHAR	Varies
				*/
			}
			else if (object.m_guid == ASF_Codec_List_Object)
			{
				if (object.m_size < 44)
				{
					ATLTRACE("Codec List Object size is too small");
					return E_FAIL;
				}

				GUID Reserved;
				m_pFilter->m_stream->Read(&Reserved, 16, &nRead);
				if (Reserved != ASF_Reserved_2)
				{
					ATLTRACE("Unrecognized value in Codec List Object");
					return E_FAIL;
				}

				DWORD CodecEntriesCount;
				m_pFilter->m_stream->Read(&CodecEntriesCount, 4, &nRead);

				for (DWORD i = 0; i < CodecEntriesCount; i++)
				{
					WORD Type;
					m_pFilter->m_stream->Read(&Type, 2, &nRead);

					WORD CodecNameLength;
					m_pFilter->m_stream->Read(&CodecNameLength, 2, &nRead);
					WCHAR* CodecName = new WCHAR[CodecNameLength+1];
					m_pFilter->m_stream->Read(CodecName, CodecNameLength*2, &nRead);
					CodecName[CodecNameLength] = 0;

					WORD DescriptionLength;
					m_pFilter->m_stream->Read(&DescriptionLength, 2, &nRead);
					WCHAR* Description = new WCHAR[DescriptionLength+1];
					m_pFilter->m_stream->Read(Description, DescriptionLength*2, &nRead);
					Description[DescriptionLength] = 0;

					WORD InformationLength;
					m_pFilter->m_stream->Read(&InformationLength, 2, &nRead);
					LPBYTE Information = (LPBYTE)malloc(InformationLength);
					if (Information)
					{
						m_pFilter->m_stream->Read(Information, InformationLength, &nRead);
					}
					else
					{
						ATLTRACE("Not enough memory");
						ATLASSERT(0);
						return E_OUTOFMEMORY;
					}
				}
			}
			/*
			else
			{
				MessageBeep(-1);
			}
			*/

			hr = object.Ascend(m_pFilter->m_stream);
			if (FAILED(hr)) return hr;
		}
	}
	else
		return E_FAIL;

	hr = object.Ascend(m_pFilter->m_stream);
	if (FAILED(hr)) return hr;

	while (1)
	{
		CASFObject object;
		hr = object.Descend(m_pFilter->m_stream);
		if (hr != S_OK)	// Error or end of file
		{
			break;
		}

		if (object.m_guid == ASF_Data_Object)
		{
			// Data packet..

			BYTE ErrorCorrectionFlags;
			m_pFilter->m_stream->Read(&ErrorCorrectionFlags, 1, &nRead);
			if (ErrorCorrectionFlags & (1<<7))
			{
				int OpaqueDataPresent = ErrorCorrectionFlags & (1<<4);
				if (OpaqueDataPresent)
				{
					// Not supported
					ATLASSERT(0);
				}

				int ErrorCorrectionLengthType = (ErrorCorrectionFlags>>5) & 0x3;
				if (ErrorCorrectionLengthType == 0)
				{
					BYTE ErrorCorrectionDataLength = ErrorCorrectionFlags & 0xf;
				}
				else
				{
					// Reserved for future use
					ATLASSERT(0);
				}
			}

			//MessageBeep(-1);
		}
		else if (object.m_guid == ASF_Simple_Index_Object)
		{
			MessageBeep(-1);
		}
		else
		{
			MessageBeep(-1);
		}

		hr = object.Ascend(m_pFilter->m_stream);
		if (FAILED(hr)) return hr;
	}

#if 0
	ATLASSERT(m_pFilter->m_pVideo == NULL);
	CComObject<CVideoSequence>::CreateInstance(&m_pFilter->m_pVideo);
	m_pFilter->m_pVideo->m_pFilter = m_pFilter;
	m_pFilter->AddPin(m_pFilter->m_pVideo);

	m_pFilter->m_pVideo->m_file = new CBitStream(stream);
	m_pFilter->m_pVideo->m_file->next_start_code();

	return m_pFilter->m_pVideo->video_sequence();
#endif
	return -1;
}
