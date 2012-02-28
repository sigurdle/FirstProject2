#include "stdafx.h"

#include "../include/windows_header.h"

namespace System
{
using namespace IO;

inline signed char getsbyte(ISequentialByteStream* stream)
{
	signed char v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}

inline uint8 getbyte(ISequentialByteStream* stream)
{
	uint8 v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}

inline uint8 getubyte(ISequentialByteStream* stream)
{
	uint8 v;
	ULONG nRead = stream->Read(&v, 1);
	if (nRead != 1) THROW(-1);
	return v;
}

inline short getshort(ISequentialByteStream* stream)
{
	short v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return BigEndian16(v);
}

inline uint16 getushort(ISequentialByteStream* stream)
{
	uint16 v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return BigEndian16(v);
}

inline long getlong(ISequentialByteStream* stream)
{
	long v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return BigEndian32(v);
}

inline uint32 getulong(ISequentialByteStream* stream)
{
	uint32 v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return BigEndian32(v);
}

inline LONGLONG getlonglong(ISequentialByteStream* stream)
{
	return ((LONGLONG)getlong(stream)<<32) | getlong(stream);
}

inline short le_getshort(ISequentialByteStream* stream)
{
	short v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return LittleEndian16(v);
}

inline uint16 le_getushort(ISequentialByteStream* stream)
{
	uint16 v;
	ULONG nRead = stream->Read(&v, 2);
	if (nRead != 2) THROW(-1);
	return LittleEndian16(v);
}

inline long le_getlong(ISequentialByteStream* stream)
{
	long v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return LittleEndian32(v);
}

inline uint32 le_getulong(ISequentialByteStream* stream)
{
	uint32 v;
	ULONG nRead = stream->Read(&v, 4);
	if (nRead != 4) THROW(-1);
	return LittleEndian32(v);
}

inline void skip(ISequentialByteStream* stream, ULONG nbytes)
{
	stream->Seek(nbytes, System::IO::STREAM_SEEK_CUR);
}

typedef unsigned char byte;
typedef unsigned char Uint8;
typedef signed short int Int16;
typedef unsigned short int Uint16;
typedef unsigned long int Uint32;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned long uint32_t;

#pragma pack(push,1)

struct sTag
{ /* ECMA 167 3/7.2 */
Uint16 TagIdentifier;
Uint16 DescriptorVersion;
Uint8 TagChecksum;
byte Reserved;
Uint16 TagSerialNumber;
Uint16 DescriptorCRC;
Uint16 DescriptorCRCLength;
Uint32 TagLocation;
};

struct extent_ad
{
	uint32	Length;
	uint32	Location;
};

struct EntityID
{ /* ECMA 167 1/7.4 */
Uint8 Flags;
char Identifier[23];
char IdentifierSuffix[8];
};

struct charspec { /* ECMA 167 1/7.2.1 */
Uint8 CharacterSetType;
byte CharacterSetInfo[63];
};

struct timestamp { /* ECMA 167 1/7.3 */
Uint16 TypeAndTimezone;
Int16 Year;
Uint8 Month;
Uint8 Day;
Uint8 Hour;
Uint8 Minute;
Uint8 Second;
Uint8 Centiseconds;
Uint8 HundredsofMicroseconds;
Uint8 Microseconds;
};

typedef uint8 Lb_addr[6];

struct icbtag { /* ECMA 167 4/14.6 */
Uint32 PriorRecordedNumberofDirectEntries;
Uint16 StrategyType;
byte StrategyParameter[2];
Uint16 MaximumNumberofEntries;
byte Reserved;
Uint8 FileType;
Lb_addr ParentICBLocation;
Uint16 Flags;
};

#pragma pack(pop)

class Dir;

struct UDF_FileEntry : public sTag
{
	icbtag icb;
	uint32 Uid;
	uint32 Gid;
	uint32 Permissions;
	uint16 FileLinkCount;
	uint8 RecordFormat;
	uint8 RecordDisplayAttributes;
	uint32 RecordLength;
	ULONGLONG InformationLength;
	ULONGLONG LogicalBlocksRecorded;
	timestamp AccessTime;
	timestamp ModificationTime;
	timestamp AttributeTime;
	uint32 Checkpoint;
//	p += 16;	// ExtendedAttributeICB
	EntityID ImplementationIdentifier;
	ULONGLONG UniqueID;
	uint32 LengthofExtendedAttributes;
	uint32 LengthofAllocationDescriptors;
};

class FEntry
{
public:
	StringA* m_name;
	uint32 m_length;
	ULONGLONG m_location;
};

class Dir
{
public:
	UDF_FileEntry m_fe;
	map<StringA*, FEntry*> m_entries;
};

class File
{
public:
	UDF_FileEntry m_fe;

//	uint32 ExtentLength;
//	ULONGLONG ExtentLocation;

	ULONGLONG PartitionStartingLocation;
	HANDLE m_hDevice;

	vector<extent_ad> m_extents;
};

int FileEntry(HANDLE hDevice, ULONGLONG PartitionStartingLocation, ULONGLONG Location, File* pFile)
{
#if WIN32
	uint8 buffer[2048*6];
	ULONG nRead;

// File Entry
	MSWindows::SetFilePointer(hDevice, (PartitionStartingLocation + Location)<<11, NULL, FILE_BEGIN);
	MSWindows::ReadFile(hDevice, buffer, 2048, &nRead, NULL);
	uint8* p = buffer;

	UDF_FileEntry fe;

	sTag tag = *(sTag*)p; p += sizeof(sTag);

	if (tag.TagIdentifier != 261)
		return -1;

	fe.icb = *(icbtag*)p; p += sizeof(icbtag);
	fe.Uid = *(uint32*)p; p += 4;
	fe.Gid = *(uint32*)p; p += 4;
	fe.Permissions = *(uint32*)p; p += 4;
	fe.FileLinkCount = *(uint16*)p; p += 2;
	fe.RecordFormat = *p++;
	fe.RecordDisplayAttributes = *p++;
	fe.RecordLength = *(uint32*)p; p += 4;
	fe.InformationLength = *(ULONGLONG*)p; p += 8;
	fe.LogicalBlocksRecorded = *(ULONGLONG*)p; p += 8;
	fe.AccessTime = *(timestamp*)p; p += sizeof(timestamp);
	fe.ModificationTime = *(timestamp*)p; p += sizeof(timestamp);
	fe.AttributeTime = *(timestamp*)p; p += sizeof(timestamp);
	fe.Checkpoint = *(uint32*)p; p += 4;
	p += 16;	// ExtendedAttributeICB
	fe.ImplementationIdentifier = *(EntityID*)p; p += sizeof(EntityID);
	fe.UniqueID = *(ULONGLONG*)p; p += 8;
	fe.LengthofExtendedAttributes = *(uint32*)p; p += 4;
	fe.LengthofAllocationDescriptors = *(uint32*)p; p += 4;

	p += fe.LengthofExtendedAttributes;

	ASSERT(fe.LengthofAllocationDescriptors == 8);	// ??

//	uint32 ExtentLength;
//	ULONGLONG ExtentLocation;
	for (int i = 0; i < 1/*fe.LengthofAllocationDescriptors>>3*/; i++)
	{
		extent_ad ext;
		// short allocation descriptor
		ext.Length = *(uint32*)p; p += 4;
		ext.Location = *(uint32*)p; p += 4;

		pFile->m_extents.Add(ext);
	}

	pFile->PartitionStartingLocation = PartitionStartingLocation;
	pFile->m_hDevice = hDevice;
#else
	ASSERT(0);
#endif

	return 0;
}

int Build(Dir* pDir, HANDLE hDevice, ULONGLONG PartitionStartingLocation, ULONGLONG RootDirectoryICBLocation)
{
#if WIN32
	uint8 buffer[2048*6];
	ULONG nRead;

// File Entry
	MSWindows::SetFilePointer(hDevice, (PartitionStartingLocation + RootDirectoryICBLocation)<<11, NULL, FILE_BEGIN);
	MSWindows::ReadFile(hDevice, buffer, 2048, &nRead, NULL);
	uint8* p = buffer;
	sTag tag = *(sTag*)p; p += sizeof(sTag);

	if (tag.TagIdentifier != 261)
		return -1;

	UDF_FileEntry fe;

	fe.icb = *(icbtag*)p; p += sizeof(icbtag);
	fe.Uid = *(uint32*)p; p += 4;
	fe.Gid = *(uint32*)p; p += 4;
	fe.Permissions = *(uint32*)p; p += 4;
	fe.FileLinkCount = *(uint16*)p; p += 2;
	fe.RecordFormat = *p++;
	fe.RecordDisplayAttributes = *p++;
	fe.RecordLength = *(uint32*)p; p += 4;
	fe.InformationLength = *(ULONGLONG*)p; p += 8;
	fe.LogicalBlocksRecorded = *(ULONGLONG*)p; p += 8;
	fe.AccessTime = *(timestamp*)p; p += sizeof(timestamp);
	fe.ModificationTime = *(timestamp*)p; p += sizeof(timestamp);
	fe.AttributeTime = *(timestamp*)p; p += sizeof(timestamp);
	fe.Checkpoint = *(uint32*)p; p += 4;
	p += 16;	// ExtendedAttributeICB
	fe.ImplementationIdentifier = *(EntityID*)p; p += sizeof(EntityID);
	fe.UniqueID = *(ULONGLONG*)p; p += 8;
	fe.LengthofExtendedAttributes = *(uint32*)p; p += 4;
	fe.LengthofAllocationDescriptors = *(uint32*)p; p += 4;

	p += fe.LengthofExtendedAttributes;

	ASSERT(fe.LengthofAllocationDescriptors == 8);	// ??

	uint32 ExtentLength;
	ULONGLONG ExtentLocation;
	for (int i = 0; i < fe.LengthofAllocationDescriptors>>3; i++)
	{
		// short allocation descriptor
		ExtentLength = *(uint32*)p; p += 4;
		ExtentLocation = *(uint32*)p; p += 4;
	}

	{
		MSWindows::SetFilePointer(hDevice, (PartitionStartingLocation + ExtentLocation/* + i*/)<<11, NULL, FILE_BEGIN);
		MSWindows::ReadFile(hDevice, buffer, ((ExtentLength+2047)>>11)<<11, &nRead, NULL);
		p = buffer;

		// The first entry is the parent directory

		while (p-buffer < ExtentLength)
		{
			FEntry* pEntry = new FEntry;

			// File identifier descriptor
			tag = *(sTag*)p; p += sizeof(sTag);

			ASSERT(tag.TagIdentifier == 257);

			uint16 FileVersionNumber = *(uint16*)p; p += 2;
			uint8 FileCharacteristics = *p++;
			uint8 LengthofFileIdentifier = *p++;
			// parent icb
			uint32 icb_Length = *(uint32*)p; p += 4;
			ULONGLONG icb_Location = *p++;
			icb_Location |= (*p++)<<8;
			icb_Location |= (*p++)<<16;
			icb_Location |= (*p++)<<24;
			icb_Location |= (*p++)<<32;
			icb_Location |= (*p++)<<40;

			pEntry->m_length = icb_Length;
			pEntry->m_location = icb_Location;

			p += 6;
			uint16 LengthOfImplementationUse = *(uint16*)p; p += 2;
			p += LengthOfImplementationUse;
			if (LengthofFileIdentifier)	// Parent directory woun't have a name
			{
				char name[256];
				std::memcpy(name, p, LengthofFileIdentifier); p += LengthofFileIdentifier;
				name[LengthofFileIdentifier] = 0;
				if (name[0] == 8)
				{
					ASSERT(0);
#if 0
					pEntry->m_name = name+1;
#endif
				}
				else
				{
					ASSERT(0);
					return -1;
				}
			}

			pDir->m_entries[pEntry->m_name] = pEntry;

			p += 4-((p-buffer)&3);
		}
	}
#else
	ASSERT(0);
#endif
	return 0;
}

class UDFStream : public ISequentialByteStream
{
public:
	UDFStream(File* pFile) : m_refcount(0)
	{
		m_pos = 0;

		ASSERT(pFile);
		m_pFile = pFile;

		m_size = 0;
		for (int i = 0; i < pFile->m_extents.GetSize(); i++)
		{
			m_size += pFile->m_extents[i].Length;

			ULONG n = 0;
			while (n < pFile->m_extents[i].Length)
			{
				m_blocks.Add(pFile->m_extents[i].Location+n);
				n += 2048;
			}
		}

		m_nblock = -1;
	}

	File* m_pFile;

	ULONG m_refcount;

	ULONG AddRef()
	{
		m_refcount++;
		return m_refcount;
	}

	ULONG Release()
	{
		ASSERT(m_refcount > 0);
		m_refcount--;
		if (m_refcount == 0)
		{
			delete this;
			return 0;
		}
		return m_refcount;
	}

	ULONGLONG m_pos;
	ULONGLONG m_size;

	LONGLONG m_nblock;
	uint8 m_buffer[2048];
	vector<ULONGLONG> m_blocks;

	virtual ULONG Read(void* pv, ULONG cb)
	{
		ULONG nBlock = m_pos>>11;
		ULONG blockPos = m_pos & (2048-1);

		/*
		while (pos+m_pFile->m_extents[nExtent].Length < m_pos)
		{
			pos += m_pFile->m_extents[nExtent].Length;
			nExtent++;
		}
		*/

		uint8* pb = (uint8*)pv;
		ULONG n = 0;

		while (n < cb)
		{
#if WIN32
			MSWindows::SetFilePointer(m_pFile->m_hDevice, (m_pFile->PartitionStartingLocation + m_blocks[nBlock]/*m_pFile->m_extents[nExtent].Location*/)<<11, NULL, FILE_BEGIN);
			ULONG nRead = MSWindows::ReadFile(m_pFile->m_hDevice, m_buffer, 2048, &nRead, NULL);
#else
			ULONG nRead = 0;
			ASSERT(0);
#endif

			ULONG len = cb-n;
			if (blockPos+len > 2048)
			{
				len = 2048-blockPos;
			}

			std::memcpy(pb, m_buffer + blockPos, len);

			n += len;
			pb += len;
			blockPos = 0;
			nBlock++;
		}

		m_pos += n;
		return n;
	}
	virtual LONGLONG Seek(LONGLONG offset, ULONG origin)
	{
		if (origin == System::IO::STREAM_SEEK_SET)
		{
			m_pos = offset;
		}
		else if (origin == System::IO::STREAM_SEEK_END)
		{
			m_pos = m_size - offset;
		}
		else if (origin == System::IO::STREAM_SEEK_CUR)
		{
			m_pos += offset;
		}
		return m_pos;
	}

	virtual LONGLONG GetSize()
	{
		return m_size;
	}
	virtual ISequentialByteStream* Clone() const
	{
		return NULL;
	}

	virtual ULONG Write(const void* pv, ULONG cb)
	{
		THROW(-1);
		return -1;
	}
};

// Presentation Control Information (PCI) Packet Structure
int ReadPresentationControlInformation(ISequentialByteStream* stream)
{
	// PCI general information (PCI_GI)
	uint32 Logical_Block_Address_in_sector = getlong(stream);
	uint16 Flags_including_Analog_Protection_System = getshort(stream);
	uint16 Relative_VOBU_End_Address = getshort(stream);	// (Offset within last sector of this VOBU)
	skip(stream, 4);
	uint32 Bit_mask_for_Prohibited_User_Operations = getlong(stream);
	uint32 VOBU_Start_Presentation_Time_90 = getlong(stream);
	uint16 VOBU_Start_Presentation_Time = getshort(stream);
	uint8 End_PTM_of_VOBU_if_Sequence_End_Code = getbyte(stream);
	uint32 Cell_elapsed_time = getlong(stream);
	skip(stream, 32);	// International Standard Recording Code

	// Non-seamless Angle Information (NSML_AGLI)
	uint32 Non_seamless_angle_1 = getlong(stream);
	uint32 Non_seamless_angle_2 = getlong(stream);
	uint32 Non_seamless_angle_3 = getlong(stream);
	uint32 Non_seamless_angle_4 = getlong(stream);
	uint32 Non_seamless_angle_5 = getlong(stream);
	uint32 Non_seamless_angle_6 = getlong(stream);
	uint32 Non_seamless_angle_7 = getlong(stream);
	uint32 Non_seamless_angle_8 = getlong(stream);
	uint32 Non_seamless_angle_9 = getlong(stream);

	// Sub-Picture Highlight General Information (HLI_GI)
	uint16 Highlight_status = getshort(stream);
	uint32 Highlight_start_time = getlong(stream);
	uint32 Highlight_end_time = getlong(stream);
	uint32 Button_selection_end_time = getlong(stream);
	uint16 the_grouping_of_the_buttons = getshort(stream);
	uint8 Starting_button_number = getbyte(stream);
	uint8 Number_of_buttons = getbyte(stream);
	uint8 Number_of_numerically_selected_buttons = getbyte(stream);
	skip(stream, 1);
	uint8 Force_select_button_number = getbyte(stream);
	uint8 Force_action_button_number = getbyte(stream);

	// Selection Color Information (SL_COLI)
	ULONGLONG Scheme_1 = getlonglong(stream);
	ULONGLONG Scheme_2 = getlonglong(stream);
	ULONGLONG Scheme_3 = getlonglong(stream);

	// Button Information (BTN_IT)
	for (int i = 0; i < 36; i++)
	{
		uint8 it[18];
		stream->Read(it, 18);

		int StartX = (it[0] & 63)<<4;
		StartX |= it[1]>>6;

		int EndX = (it[1] & 3)<<6;
		EndX |= it[2];

		int StartY = (it[3] & 63)<<4;
		StartX |= it[4]>>6;

		int EndY = (it[4] & 3)<<6;
		EndX |= it[5];
	}

	return 0;
}

int ReadVTS_IFO(ISequentialByteStream* stream)
{
	char identifier[12];
	stream->Read(identifier, 12);

	if (std::memcmp(identifier, "DVDVIDEO-VTS", 12) != 0)
	{
	//	stream->Release();
		return Error_Failed;
	}

	uint32 LastSector = getlong(stream);
	skip(stream, 12);
	uint32 LastSector1 = getlong(stream);
	uint16 Version = getshort(stream);
	uint32 VTS_Category = getlong(stream);
	skip(stream, 90);
	uint32 End_byte_address_of_VTSI_MAT = getlong(stream);
	skip(stream, 60);
	uint32 Start_sector_of_VTSM_VOBS = getlong(stream);
	uint32 Start_sector_of_VTST_VOBS = getlong(stream);
	uint32 Start_sector_of_VTS_PTT_SRPT = getlong(stream);
	uint32 Start_sector_of_VTS_PGCI_UT = getlong(stream);
	uint32 Start_sector_of_VTSM_PGCI_UT = getlong(stream);
	uint32 Start_sector_of_VTS_TMAPT = getlong(stream);
	uint32 Start_sector_of_VTSM_C_ADT = getlong(stream);
	uint32 Start_sector_of_VTSM_VOBU_ADMAP = getlong(stream);
	uint32 Start_sector_of_VTS_C_ADT = getlong(stream);
	uint32 Start_sector_of_VTS_VOBU_ADMAP = getlong(stream);
	skip(stream, 24);
	uint16 Video_attributes_of_VTSM_VOBS = getshort(stream);
	skip(stream, 1);
	uint8 Number_of_audio_streams_in_VTSM_VOBS = getbyte(stream);
	ULONGLONG VTSM_Audio_1_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_2_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_3_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_4_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_5_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_6_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_7_attributes = getlonglong(stream);
	ULONGLONG VTSM_Audio_8_attributes = getlonglong(stream);
	skip(stream, 17);
	uint8 Number_of_subpicture_streams_in_VTSM_VOBS = getbyte(stream);
	skip(stream, 6);//VTSM Subpicture 1 attributes
	skip(stream, 164);
	uint16 Video_attributes_of_VTST_VOBS = getshort(stream);
	skip(stream, 1);
	uint8 Number_of_audio_streams_in_VTST_VOBS = getbyte(stream);
	ULONGLONG VTST_Audio_1_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_2_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_3_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_4_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_5_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_6_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_7_attributes = getlonglong(stream);
	ULONGLONG VTST_Audio_8_attributes = getlonglong(stream);
	skip(stream, 17);
	uint8 Number_of_subpicture_streams_in_VTST_VOBS = getbyte(stream);

	// Video Title Set Part-Of-Title Search (VTS_PTT_SRPT) Start_sector_of_VTS_PTT_SRPT
	{
		stream->Seek(Start_sector_of_VTS_PTT_SRPT<<11, System::IO::STREAM_SEEK_SET);

		uint16 Number_of_title_units = getshort(stream);
	}

	// Video Title Set Program Chain Unit (VTS_PGCI_UT)
	if (Start_sector_of_VTS_PGCI_UT)
	{
		stream->Seek(Start_sector_of_VTS_PGCI_UT<<11, System::IO::STREAM_SEEK_SET);

		uint16 Number_of_program_chains_in_video_title_set = getshort(stream);
		skip(stream, 2);
		uint32 Address_of_last_byte = getlong(stream);

		for (int i = 0; i < Number_of_program_chains_in_video_title_set; i++)
		{
			uint8 Category_mask_bit_and_title_number = getbyte(stream);
			uint8 Category = getbyte(stream);
			uint16 Parental_id_mask = getshort(stream);
			uint32 Start_byte_to_VTS_program_chain_PGC = getlong(stream);
		}
	}

	// Video Title Set Cell Address (VTS_C_ADT)
	if (Start_sector_of_VTS_C_ADT)
	{
		stream->Seek(Start_sector_of_VTS_C_ADT<<11, System::IO::STREAM_SEEK_SET);

		uint16 Number_of_VOB_ids_in_VTS_VOBS = getshort(stream);
		skip(stream, 2);
		uint32 Address_of_last_byte = getlong(stream);

		for (int i = 0; i < Number_of_VOB_ids_in_VTS_VOBS; i++)
		{
			uint16 VOB_id = getshort(stream);
			uint8 Cell_id = getbyte(stream);
			skip(stream, 1);
			uint32 Start_sector_of_this_cell = getlong(stream);
			uint8 End_sector_of_this_cell = getbyte(stream);
		}

	}

	return 0;
}

void ProgramChain(ISequentialByteStream* stream)
{
	LONGLONG start = stream->Seek(0, System::IO::STREAM_SEEK_CUR);

	skip(stream, 2);	// reserved
	uint8 Number_of_programs_in_this_PGC = getbyte(stream);
	uint8 Number_of_cells_in_this_PGC = getbyte(stream);

	uint8 Playback_time_hour = getbyte(stream);
	uint8 Playback_time_minute = getbyte(stream);
	uint8 Playback_time_second = getbyte(stream);
	uint8 Playback_time_frame = getbyte(stream);
	uint32 UOP = getlong(stream);
	uint16 Audio_stream_1_status = getshort(stream);
	uint16 Audio_stream_2_status = getshort(stream);
	uint16 Audio_stream_3_status = getshort(stream);
	uint16 Audio_stream_4_status = getshort(stream);
	uint16 Audio_stream_5_status = getshort(stream);
	uint16 Audio_stream_6_status = getshort(stream);
	uint16 Audio_stream_7_status = getshort(stream);
	uint16 Audio_stream_8_status = getshort(stream);

	uint32 Subpicture_stream_status[32];

	{
		for (int i = 0; i < 32; i++)
		{
			Subpicture_stream_status[i] = getlong(stream);
		}
	}

	uint16 Next_PGC_number = getshort(stream);
	uint16 Previous_PGC_number = getshort(stream);
	uint16 GoUp_PGC_number = getshort(stream);

	uint8 Still_time_in_seconds = getbyte(stream);
	uint8 Program_playback_mode = getbyte(stream);

	uint8 colors[16][3];	// Y, Cr, Cb

	{
		for (int i = 0; i < 16; i++)
		{
			getbyte(stream);
			colors[i][0] = getbyte(stream);
			colors[i][1] = getbyte(stream);
			colors[i][2] = getbyte(stream);
		}
	}

	uint16 Start_byte_of_PGC_command_table = getshort(stream);
	uint16 Start_byte_of_PGC_program_map = getshort(stream);
	uint16 Start_byte_of_PGC_cell_playback_information = getshort(stream);
	uint16 Start_byte_of_PGC_cell_position_information = getshort(stream);

	if (Start_byte_of_PGC_command_table < 236)
	{
		THROW(-1);
	}

	stream->Seek(start + Start_byte_of_PGC_command_table, System::IO::STREAM_SEEK_SET);

	uint16 Number_of_pre_commands = getshort(stream);
	uint16 Number_of_post_commands = getshort(stream);
	uint16 Number_of_cell_commands = getshort(stream);
	uint16 End_byte_address = getshort(stream);

	{
		for (int i = 0; i < Number_of_pre_commands; i++)
		{
			ULONGLONG command = getlonglong(stream);

			if ((command>>32) & 0x30020000 == 0x30020000)
			{
				ULONG title = (command>>16) & 0xFF;
				TRACE("JumpTT %d\n", title);
			}
		}
	}

	{
		for (int i = 0; i < Number_of_post_commands; i++)
		{
			skip(stream, 8);
		}
	}

	{
		for (int i = 0; i < Number_of_cell_commands; i++)
		{
			skip(stream, 8);
		}
	}

	if (Start_byte_of_PGC_program_map)
	{
		LONGLONG cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);
		if (cur > start + Start_byte_of_PGC_program_map)
		{
			THROW(-1);
		}

		stream->Seek(start + Start_byte_of_PGC_program_map, System::IO::STREAM_SEEK_SET);
	}

	/*
	uint16 Number_of_language_units = getshort(stream);
	skip(stream, 2);
	uint32 Address_of_last_byte = getlong(stream);
	ASSERT(Number_of_language_units == 0);
	*/
}

int ReadVideo_IFO(ISequentialByteStream* stream)
{
	char identifier[12];
	stream->Read(identifier, 12);

	if (std::memcmp(identifier, "DVDVIDEO-VMG", 12) != 0)
	{
	//	stream->Release();
		return Error_Failed;
	}

	uint32 LastSector = getlong(stream);
	skip(stream, 12);
	uint32 LastSector1 = getlong(stream);
	uint16 Version = getshort(stream);
	uint32 VMG_Category_and_Mask_for_Regional_Codes = getlong(stream);
	uint16 Number_of_volumes_of_this_DVD = getshort(stream);
	uint16 Current_volume = getshort(stream);
	uint8 Disc_side = getbyte(stream);
	skip(stream, 19);
	uint16 Number_of_video_title_sets = getshort(stream);

	{
		for (int i = 0; i < Number_of_video_title_sets; i++)
		{
			char filename[256];
			std::sprintf(filename, "C:/PappaDVD/VIDEO_TS/VTS_%.2d_0.IFO", i+1);

			FileByteStream* tsstream = new FileByteStream(new StringA(string_copy(filename)));
			//tsstream->AddRef();

			ReadVTS_IFO(tsstream);

			//tsstream->Release();
		}
	}

	uint8 Provider_ID[32];
	stream->Read(Provider_ID, 32);
	LONGLONG VMG_Pos_Code = getlonglong(stream);
	skip(stream, 24);

/* This is the length of the Video Manager Information Management Table (VMGI_MAT)
in bytes - 1. VMGI_MAT includes the VMGM_MAT structure and the data structure for
the First-Play PGC.
*/
	uint32 End_byte_address_of_VMGI_MAT = getlong(stream);

	uint32 First_Play_PGC_Start_Byte = getlong(stream);
	skip(stream, 56);
	uint32 Start_sector_of_VMGM_VOBS = getlong(stream);
	uint32 Start_sector_of_VMG_PTT_SRPT = getlong(stream);
	uint32 Start_sector_of_VMGM_PGCI_UT = getlong(stream);
	uint32 Start_sector_of_VMG_PTL_MAIT = getlong(stream);
	uint32 Start_sector_of_VMG_VTS_ATRT = getlong(stream);
	uint32 Start_sector_of_VMG_TXTDT_MG = getlong(stream);
	uint32 Start_sector_of_VMGM_C_ADT = getlong(stream);
	uint32 Start_sector_of_VMGM_VOBU_ADMAP = getlong(stream);
	skip(stream, 32);
	uint16 Video_attributes_of_VMGM_VOBS = getshort(stream);
	skip(stream, 1);
	uint8 Number_of_audio_streams_in_VMGM_VOBS = getbyte(stream);
	ULONGLONG VMGM_Audio_1_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_2_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_3_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_4_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_5_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_6_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_7_attributes = getlonglong(stream);
	ULONGLONG VMGM_Audio_8_attributes = getlonglong(stream);
	skip(stream, 17);
	uint8 Number_of_subpicture_streams_in_VMGM_VOBS = getbyte(stream);
	ULONGLONG VMGM_Subpicture_attributes[256];

	(getlong(stream)<<2) | getshort(stream);
	{
		for (int i = 0; i < Number_of_subpicture_streams_in_VMGM_VOBS; i++)
		{
			VMGM_Subpicture_attributes[i] = (getlong(stream)<<2) | getshort(stream);
		}
	}

	LONGLONG cur = stream->Seek(0, System::IO::STREAM_SEEK_CUR);

	ASSERT(cur <= First_Play_PGC_Start_Byte);
	if (cur > First_Play_PGC_Start_Byte)
	{
		THROW(-1);
	}

	stream->Seek(First_Play_PGC_Start_Byte, System::IO::STREAM_SEEK_SET);

// Program Chain (PGC)
	{
		ProgramChain(stream);

	}

	stream->Seek(End_byte_address_of_VMGI_MAT+1, System::IO::STREAM_SEEK_SET);

// Video Manager Title Map Search (VMG_TT_SRPT)

	{
		uint16 Number_of_titles = getshort(stream);
		skip(stream, 2);
		uint16 Address_of_last_byte = getlong(stream);
		{
			for (int i = 0; i < Number_of_titles; i++)
			{
				skip(stream, 12);
			}
		}
	}

// Video Manager Menu Program Chain Units (VMGM_PGCI_UT)
	if (Start_sector_of_VMGM_PGCI_UT)
	{
		stream->Seek(Start_sector_of_VMGM_PGCI_UT<<11, System::IO::STREAM_SEEK_SET);

		uint16 Number_of_language_units = getshort(stream);
		skip(stream, 2);
		uint32 Address_of_last_byte = getlong(stream);
		for (int i = 0; i < Number_of_language_units; i++)
		{
			uint16 Two_character_language_code = getshort(stream);
			uint8 Language_code_extension = getbyte(stream);
			uint8 Menu_existence_flag = getbyte(stream);
			uint32 Language_unit_start_byte = getlong(stream);	// points to a LU
			uint16 Number_of_menus_in_this_language_unit = getshort(stream);
			skip(stream, 2);
			uint32 Address_of_last_byte_of_this_language_unit = getlong(stream);
		}
	}

//	ASSERT(Start_sector_of_LU == 0);
	ASSERT(Start_sector_of_VMG_PTL_MAIT == 0);

// Video Title Set Attributes (VMG_VTS_ATRT)
	
	ASSERT(Start_sector_of_VMG_VTS_ATRT);
	{
		stream->Seek(Start_sector_of_VMG_VTS_ATRT<<11, System::IO::STREAM_SEEK_SET);

		uint16 Number_of_video_title_sets = getshort(stream);
		skip(stream, 2);
		uint16 Address_of_last_byte = getlong(stream);
		{
			for (int i = 0; i < Number_of_video_title_sets; i++)
			{
				uint32 start_byte = getlong(stream);
			}
		}
	}

	if (Start_sector_of_VMG_TXTDT_MG)
	{
		ASSERT(0);
	}

// Video Manager Menu Cell Address (VMGM_C_ADT)
	if (Start_sector_of_VMGM_C_ADT)
	{
		stream->Seek(Start_sector_of_VMGM_C_ADT<<11, System::IO::STREAM_SEEK_SET);

		uint16 Number_of_VOB_ids_in_VMGM_VOBS = getshort(stream);
		skip(stream, 2);
		uint16 Address_of_last_byte = getlong(stream);
		{
			for (int i = 0; i < Number_of_VOB_ids_in_VMGM_VOBS; i++)
			{
				uint16 VOB_id = getshort(stream);
				uint8 Cell_id = getbyte(stream);
				skip(stream, 1);
			}
		}
	}

//
//	stream->Release();
	return 0;
}

#if 0//WIN32

#if defined( WIN32 )
#define INIT_SPTD( TYPE, SIZE ) \
    DWORD tmp; \
    SCSI_PASS_THROUGH_DIRECT sptd; \
    uint8_t p_buffer[ (SIZE) ]; \
    memset( &sptd, 0, sizeof( SCSI_PASS_THROUGH_DIRECT ) ); \
    sptd.Length = sizeof( SCSI_PASS_THROUGH_DIRECT ); \
    sptd.DataBuffer = p_buffer; \
    sptd.DataTransferLength = (SIZE); \
    WinInitSPTD( &sptd, (TYPE) );
#define SEND_SPTD( DEV, SPTD, TMP ) \
    (DeviceIoControl( (HANDLE)(DEV), IOCTL_SCSI_PASS_THROUGH_DIRECT, \
                      (SPTD), sizeof( SCSI_PASS_THROUGH_DIRECT ), \
                      (SPTD), sizeof( SCSI_PASS_THROUGH_DIRECT ), \
                      (TMP), NULL ) ? 0 : -1)
#define INIT_SSC( TYPE, SIZE ) \
    struct SRB_ExecSCSICmd ssc; \
    uint8_t p_buffer[ (SIZE)+1 ]; \
    memset( &ssc, 0, sizeof( struct SRB_ExecSCSICmd ) ); \
    ssc.SRB_BufPointer = (char *)p_buffer; \
    ssc.SRB_BufLen = (SIZE); \
    WinInitSSC( &ssc, (TYPE) );
#endif

//#   include <winioctl.h>

#define IOCTL_DVD_START_SESSION         CTL_CODE(FILE_DEVICE_DVD, 0x0400, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DVD_READ_KEY              CTL_CODE(FILE_DEVICE_DVD, 0x0401, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DVD_SEND_KEY              CTL_CODE(FILE_DEVICE_DVD, 0x0402, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DVD_END_SESSION           CTL_CODE(FILE_DEVICE_DVD, 0x0403, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DVD_GET_REGION            CTL_CODE(FILE_DEVICE_DVD, 0x0405, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_DVD_SEND_KEY2             CTL_CODE(FILE_DEVICE_DVD, 0x0406, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_DVD_READ_STRUCTURE        CTL_CODE(FILE_DEVICE_DVD, 0x0450, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_SCSI_PASS_THROUGH_DIRECT  CTL_CODE(FILE_DEVICE_CONTROLLER, 0x0405, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)

#define DVD_CHALLENGE_KEY_LENGTH        (12 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_BUS_KEY_LENGTH              (8 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_TITLE_KEY_LENGTH            (8 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_DISK_KEY_LENGTH             (2048 + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_RPC_KEY_LENGTH              (sizeof(DVD_RPC_KEY) + sizeof(DVD_COPY_PROTECT_KEY))
#define DVD_ASF_LENGTH                  (sizeof(DVD_ASF) + sizeof(DVD_COPY_PROTECT_KEY))

typedef ULONG DVD_SESSION_ID, *PDVD_SESSION_ID;

typedef struct _SCSI_PASS_THROUGH_DIRECT
{
    USHORT Length;
    UCHAR ScsiStatus;
    UCHAR PathId;
    UCHAR TargetId;
    UCHAR Lun;
    UCHAR CdbLength;
    UCHAR SenseInfoLength;
    UCHAR DataIn;
    ULONG DataTransferLength;
    ULONG TimeOutValue;
    PVOID DataBuffer;
    ULONG SenseInfoOffset;
    UCHAR Cdb[16];
} SCSI_PASS_THROUGH_DIRECT, *PSCSI_PASS_THROUGH_DIRECT;

typedef enum
{
    DvdChallengeKey = 0x01,
    DvdBusKey1,
    DvdBusKey2,
    DvdTitleKey,
    DvdAsf,
    DvdSetRpcKey = 0x6,
    DvdGetRpcKey = 0x8,
    DvdDiskKey = 0x80,
    DvdInvalidateAGID = 0x3f
} DVD_KEY_TYPE;

typedef struct _DVD_COPY_PROTECT_KEY
{
    ULONG KeyLength;
    DVD_SESSION_ID SessionId;
    DVD_KEY_TYPE KeyType;
    ULONG KeyFlags;
    union
    {
        struct
        {
            ULONG FileHandle;
            ULONG Reserved;   // used for NT alignment
        };
        LARGE_INTEGER TitleOffset;
    } Parameters;
    UCHAR KeyData[0];
} DVD_COPY_PROTECT_KEY, *PDVD_COPY_PROTECT_KEY;

    /* The generic packet command opcodes for CD/DVD Logical Units,
     * From Table 57 of the SFF8090 Ver. 3 (Mt. Fuji) draft standard. */
#   define GPCMD_READ_DVD_STRUCTURE 0xad
    /* DVD struct types */
#   define DVD_STRUCT_PHYSICAL      0x00
#   define DVD_STRUCT_COPYRIGHT     0x01
#   define DVD_STRUCT_DISCKEY       0x02
#   define DVD_STRUCT_BCA           0x03
#   define DVD_STRUCT_MANUFACT      0x04

#define DVD_KEY_SIZE 5
#define DVD_CHALLENGE_SIZE 10
#define DVD_DISCKEY_SIZE 2048

#if defined( WIN32 )
/*****************************************************************************
 * WinInitSPTD: initialize a sptd structure
 *****************************************************************************
 * This function initializes a SCSI pass through command structure for future
 * use, either a read command or a write command.
 *****************************************************************************/
static void WinInitSPTD( SCSI_PASS_THROUGH_DIRECT *p_sptd, int i_type )
{
    memset( p_sptd->DataBuffer, 0, p_sptd->DataTransferLength );

#if 0
    switch( i_type )
    {
        case GPCMD_SEND_KEY:
            p_sptd->DataIn = SCSI_IOCTL_DATA_OUT;
            break;

        case GPCMD_READ_DVD_STRUCTURE:
        case GPCMD_REPORT_KEY:
            p_sptd->DataIn = SCSI_IOCTL_DATA_IN;
            break;
    }
#endif

    p_sptd->Cdb[ 0 ] = i_type;
    p_sptd->Cdb[ 8 ] = (uint8_t)(p_sptd->DataTransferLength >> 8) & 0xff;
    p_sptd->Cdb[ 9 ] = (uint8_t) p_sptd->DataTransferLength       & 0xff;
    p_sptd->CdbLength = 12;

    p_sptd->TimeOutValue = 2;
}
#endif

/*****************************************************************************
 * ioctl_ReportAgid: get AGID from the drive
 *****************************************************************************/
int ioctl_ReportAgid( int i_fd, int *pi_agid )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.type = DVD_LU_SEND_AGID;
    auth_info.lsa.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVD_AUTH, &auth_info );

    *pi_agid = auth_info.lsa.agid;

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.format = DVD_REPORT_AGID;
    auth_info.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVDIOCREPORTKEY, &auth_info );

    *pi_agid = auth_info.agid;

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_REPORT_KEY, 8 );

    rdc.command[ 10 ] = DVD_REPORT_AGID | (*pi_agid << 6);

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

    *pi_agid = p_buffer[ 7 ] >> 6;

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_REPORT_KEY, 8 );

    sctl_io.cdb[ 10 ] = DVD_REPORT_AGID | (*pi_agid << 6);

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

    *pi_agid = p_buffer[ 7 ] >> 6;

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_REPORT_KEY, 8 );

    rs_cdb.cdb_opaque[ 10 ] = DVD_REPORT_AGID | (*pi_agid << 6);

    i_ret = SolarisSendUSCSI( i_fd, &sc );

    if( i_ret < 0 || sc.uscsi_status )
    {
        i_ret = -1;
    }

    *pi_agid = p_buffer[ 7 ] >> 6;

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDAuthenticationGrantIDInfo,
                   kDVDKeyFormatAGID_CSS );

    dvd.grantID = *pi_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    i_ret = ioctl( i_fd, DKIOCDVDREPORTKEY, &dvd );

    *pi_agid = dvdbs.grantID;

#elif defined( WIN32 )
//    if( WIN2K ) /* NT/2k/XP */
    {
        ULONG id;
        DWORD tmp;

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_START_SESSION,
                        &tmp, 4, &id, sizeof( id ), &tmp, NULL ) ? 0 : -1;

        *pi_agid = id;
    }
#if 0
    else
    {
        INIT_SSC( GPCMD_REPORT_KEY, 8 );

        ssc.CDBByte[ 10 ] = DVD_REPORT_AGID | (*pi_agid << 6);

        i_ret = WinSendSSC( i_fd, &ssc );

        *pi_agid = p_buffer[ 7 ] >> 6;
    }
#endif

#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_REPORT_KEY, 8 );

    p_cpt->cam_cdb[ 10 ] = DVD_REPORT_AGID | (*pi_agid << 6);

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

    *pi_agid = p_buffer[ 7 ] >> 6;

#elif defined( SYS_OS2 )
    INIT_SSC( GPCMD_REPORT_KEY, 8 );

    sdc.command[ 10 ] = DVD_REPORT_AGID | (*pi_agid << 6);

    i_ret = DosDevIOCtl(i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                        &sdc, sizeof(sdc), &ulParamLen,
                        p_buffer, sizeof(p_buffer), &ulDataLen);

    *pi_agid = p_buffer[ 7 ] >> 6;

#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

/*****************************************************************************
 * ioctl_InvalidateAgid: invalidate the current AGID
 *****************************************************************************/
int ioctl_InvalidateAgid( int i_fd, int *pi_agid )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.type = DVD_INVALIDATE_AGID;
    auth_info.lsa.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVD_AUTH, &auth_info );

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.format = DVD_INVALIDATE_AGID;
    auth_info.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVDIOCREPORTKEY, &auth_info );

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_REPORT_KEY, 0 );

    rdc.command[ 10 ] = DVD_INVALIDATE_AGID | (*pi_agid << 6);

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_REPORT_KEY, 0 );

    sctl_io.cdb[ 10 ] = DVD_INVALIDATE_AGID | (*pi_agid << 6);

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_REPORT_KEY, 0 );

    rs_cdb.cdb_opaque[ 10 ] = DVD_INVALIDATE_AGID | (*pi_agid << 6);

    i_ret = SolarisSendUSCSI( i_fd, &sc );

    if( i_ret < 0 || sc.uscsi_status )
    {
        i_ret = -1;
    }

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_send_key_t, DVDAuthenticationGrantIDInfo,
                   kDVDKeyFormatAGID_Invalidate );

    dvd.grantID = *pi_agid;

    i_ret = ioctl( i_fd, DKIOCDVDSENDKEY, &dvd );

#elif defined( WIN32 )
//    if( WIN2K ) /* NT/2k/XP */
    {
        DWORD tmp;

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_END_SESSION,
                    pi_agid, sizeof( *pi_agid ), NULL, 0, &tmp, NULL ) ? 0 : -1;
    }
#if 0
    else
    {
#if defined( __MINGW32__ )
        INIT_SSC( GPCMD_REPORT_KEY, 0 );
#else
        INIT_SSC( GPCMD_REPORT_KEY, 1 );

        ssc.SRB_BufLen    = 0;
        ssc.CDBByte[ 8 ]  = 0;
        ssc.CDBByte[ 9 ]  = 0;
#endif

        ssc.CDBByte[ 10 ] = DVD_INVALIDATE_AGID | (*pi_agid << 6);

        i_ret = WinSendSSC( i_fd, &ssc );
    }
#endif

#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_REPORT_KEY, 0 );

    p_cpt->cam_cdb[ 10 ] = DVD_INVALIDATE_AGID | (*pi_agid << 6);

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

#elif defined( SYS_OS2 )
    INIT_SSC( GPCMD_REPORT_KEY, 1 );

    sdc.data_length = 0;
    sdc.command[ 8 ] = 0;
    sdc.command[ 9 ] = 0;

    sdc.command[ 10 ] = DVD_INVALIDATE_AGID | (*pi_agid << 6);

    i_ret = DosDevIOCtl(i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                        &sdc, sizeof(sdc), &ulParamLen,
                        NULL, 0, &ulDataLen);
#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

/*****************************************************************************
 * ioctl_SendChallenge: send challenge to the drive
 *****************************************************************************/
int ioctl_SendChallenge( int i_fd, int *pi_agid, uint8_t *p_challenge )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.type = DVD_HOST_SEND_CHALLENGE;
    auth_info.hsc.agid = *pi_agid;

    memcpy( auth_info.hsc.chal, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = ioctl( i_fd, DVD_AUTH, &auth_info );

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.format = DVD_SEND_CHALLENGE;
    auth_info.agid = *pi_agid;

    memcpy( auth_info.keychal, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = ioctl( i_fd, DVDIOCSENDKEY, &auth_info );

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_SEND_KEY, 16 );

    rdc.command[ 10 ] = DVD_SEND_CHALLENGE | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xe;
    memcpy( p_buffer + 4, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_SEND_KEY, 16 );

    sctl_io.cdb[ 10 ] = DVD_SEND_CHALLENGE | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xe;
    memcpy( p_buffer + 4, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_SEND_KEY, 16 );

    rs_cdb.cdb_opaque[ 10 ] = DVD_SEND_CHALLENGE | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xe;
    memcpy( p_buffer + 4, p_challenge, DVD_CHALLENGE_SIZE );

    if( SolarisSendUSCSI( i_fd, &sc ) < 0 || sc.uscsi_status )
    {
        return -1;
    }

    i_ret = 0;

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_send_key_t, DVDChallengeKeyInfo,
                   kDVDKeyFormatChallengeKey );

    dvd.grantID = *pi_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    dvdbs.dataLength[ 1 ] = 0xe;
    memcpy( dvdbs.challengeKeyValue, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = ioctl( i_fd, DKIOCDVDSENDKEY, &dvd );

#elif defined( WIN32 )
//    if( WIN2K ) /* NT/2k/XP */
    {
        DWORD tmp;
        uint8_t buffer[DVD_CHALLENGE_KEY_LENGTH];
        PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY) &buffer;

        memset( &buffer, 0, sizeof( buffer ) );

        key->KeyLength  = DVD_CHALLENGE_KEY_LENGTH;
        key->SessionId  = *pi_agid;
        key->KeyType    = DvdChallengeKey;
        key->KeyFlags   = 0;

        memcpy( key->KeyData, p_challenge, DVD_CHALLENGE_SIZE );

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_SEND_KEY, key,
                 key->KeyLength, key, key->KeyLength, &tmp, NULL ) ? 0 : -1;
    }
#if 0
    else
    {
        INIT_SSC( GPCMD_SEND_KEY, 16 );

        ssc.CDBByte[ 10 ] = DVD_SEND_CHALLENGE | (*pi_agid << 6);

        p_buffer[ 1 ] = 0xe;
        memcpy( p_buffer + 4, p_challenge, DVD_CHALLENGE_SIZE );

        i_ret = WinSendSSC( i_fd, &ssc );
    }
#endif

#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_SEND_KEY, 16 );

    p_cpt->cam_cdb[ 10 ] = DVD_SEND_CHALLENGE | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xe;
    memcpy( p_buffer + 4, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

#elif defined( SYS_OS2 )
    INIT_SSC( GPCMD_SEND_KEY, 16 );

    sdc.command[ 10 ] = DVD_SEND_CHALLENGE | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xe;
    memcpy( p_buffer + 4, p_challenge, DVD_CHALLENGE_SIZE );

    i_ret = DosDevIOCtl( i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                         &sdc, sizeof(sdc), &ulParamLen,
                         p_buffer, sizeof(p_buffer), &ulDataLen );

#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

/*****************************************************************************
 * ioctl_ReportChallenge: get challenge from the drive
 *****************************************************************************/
int ioctl_ReportChallenge( int i_fd, int *pi_agid, uint8_t *p_challenge )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.type = DVD_LU_SEND_CHALLENGE;
    auth_info.lsc.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVD_AUTH, &auth_info );

    memcpy( p_challenge, auth_info.lsc.chal, DVD_CHALLENGE_SIZE );

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.format = DVD_REPORT_CHALLENGE;
    auth_info.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVDIOCREPORTKEY, &auth_info );

    memcpy( p_challenge, auth_info.keychal, DVD_CHALLENGE_SIZE );

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_REPORT_KEY, 16 );

    rdc.command[ 10 ] = DVD_REPORT_CHALLENGE | (*pi_agid << 6);

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

    memcpy( p_challenge, p_buffer + 4, DVD_CHALLENGE_SIZE );

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_REPORT_KEY, 16 );

    sctl_io.cdb[ 10 ] = DVD_REPORT_CHALLENGE | (*pi_agid << 6);

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

    memcpy( p_challenge, p_buffer + 4, DVD_CHALLENGE_SIZE );

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_REPORT_KEY, 16 );

    rs_cdb.cdb_opaque[ 10 ] = DVD_REPORT_CHALLENGE | (*pi_agid << 6);

    i_ret = SolarisSendUSCSI( i_fd, &sc );

    if( i_ret < 0 || sc.uscsi_status )
    {
        i_ret = -1;
    }

    memcpy( p_challenge, p_buffer + 4, DVD_CHALLENGE_SIZE );

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDChallengeKeyInfo,
                   kDVDKeyFormatChallengeKey );

    dvd.grantID = *pi_agid;

    i_ret = ioctl( i_fd, DKIOCDVDREPORTKEY, &dvd );

    memcpy( p_challenge, dvdbs.challengeKeyValue, DVD_CHALLENGE_SIZE );

#elif defined( WIN32 )
//    if( WIN2K ) /* NT/2k/XP */
    {
        DWORD tmp;
        uint8_t buffer[DVD_CHALLENGE_KEY_LENGTH];
        PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY) &buffer;

        memset( &buffer, 0, sizeof( buffer ) );

        key->KeyLength  = DVD_CHALLENGE_KEY_LENGTH;
        key->SessionId  = *pi_agid;
        key->KeyType    = DvdChallengeKey;
        key->KeyFlags   = 0;

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_READ_KEY, key,
                key->KeyLength, key, key->KeyLength, &tmp, NULL ) ? 0 : -1;

        if( i_ret < 0 )
        {
            return i_ret;
        }

        memcpy( p_challenge, key->KeyData, DVD_CHALLENGE_SIZE );
    }
#if 0
    else
    {
        INIT_SSC( GPCMD_REPORT_KEY, 16 );

        ssc.CDBByte[ 10 ] = DVD_REPORT_CHALLENGE | (*pi_agid << 6);

        i_ret = WinSendSSC( i_fd, &ssc );

        memcpy( p_challenge, p_buffer + 4, DVD_CHALLENGE_SIZE );
    }
#endif

#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_REPORT_KEY, 16 );

    p_cpt->cam_cdb[ 10 ] = DVD_REPORT_CHALLENGE | (*pi_agid << 6);

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

    memcpy( p_challenge, p_buffer + 4, DVD_CHALLENGE_SIZE );

#elif defined( SYS_OS2 )
    INIT_SSC( GPCMD_REPORT_KEY, 16 );

    sdc.command[ 10 ] = DVD_REPORT_CHALLENGE | (*pi_agid << 6);

    i_ret = DosDevIOCtl(i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                        &sdc, sizeof(sdc), &ulParamLen,
                        p_buffer, sizeof(p_buffer), &ulDataLen);

    memcpy( p_challenge, p_buffer + 4, DVD_CHALLENGE_SIZE );

#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

/*****************************************************************************
 * ioctl_ReportKey1: get the first key from the drive
 *****************************************************************************/
int ioctl_ReportKey1( int i_fd, int *pi_agid, uint8_t *p_key )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.type = DVD_LU_SEND_KEY1;
    auth_info.lsk.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVD_AUTH, &auth_info );

    memcpy( p_key, auth_info.lsk.key, DVD_KEY_SIZE );

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.format = DVD_REPORT_KEY1;
    auth_info.agid = *pi_agid;

    i_ret = ioctl( i_fd, DVDIOCREPORTKEY, &auth_info );

    memcpy( p_key, auth_info.keychal, DVD_KEY_SIZE );

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_REPORT_KEY, 12 );

    rdc.command[ 10 ] = DVD_REPORT_KEY1 | (*pi_agid << 6);

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

    memcpy( p_key, p_buffer + 4, DVD_KEY_SIZE );

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_REPORT_KEY, 12 );

    sctl_io.cdb[ 10 ] = DVD_REPORT_KEY1 | (*pi_agid << 6);

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

    memcpy( p_key, p_buffer + 4, DVD_KEY_SIZE );

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_REPORT_KEY, 12 );

    rs_cdb.cdb_opaque[ 10 ] = DVD_REPORT_KEY1 | (*pi_agid << 6);

    i_ret = SolarisSendUSCSI( i_fd, &sc );

    if( i_ret < 0 || sc.uscsi_status )
    {
        i_ret = -1;
    }

    memcpy( p_key, p_buffer + 4, DVD_KEY_SIZE );

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_report_key_t, DVDKey1Info,
                   kDVDKeyFormatKey1 );

    dvd.grantID = *pi_agid;

    i_ret = ioctl( i_fd, DKIOCDVDREPORTKEY, &dvd );

    memcpy( p_key, dvdbs.key1Value, DVD_KEY_SIZE );

#elif defined( WIN32 )
//    if( WIN2K ) /* NT/2k/XP */
    {
        DWORD tmp;
        uint8_t buffer[DVD_BUS_KEY_LENGTH];
        PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY) &buffer;

        memset( &buffer, 0, sizeof( buffer ) );

        key->KeyLength  = DVD_BUS_KEY_LENGTH;
        key->SessionId  = *pi_agid;
        key->KeyType    = DvdBusKey1;
        key->KeyFlags   = 0;

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_READ_KEY, key,
                key->KeyLength, key, key->KeyLength, &tmp, NULL ) ? 0 : -1;

        memcpy( p_key, key->KeyData, DVD_KEY_SIZE );
    }
#if 0
    else
    {
        INIT_SSC( GPCMD_REPORT_KEY, 12 );

        ssc.CDBByte[ 10 ] = DVD_REPORT_KEY1 | (*pi_agid << 6);

        i_ret = WinSendSSC( i_fd, &ssc );

        memcpy( p_key, p_buffer + 4, DVD_KEY_SIZE );
    }
#endif

#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_REPORT_KEY, 12 );

    p_cpt->cam_cdb[ 10 ] = DVD_REPORT_KEY1 | (*pi_agid << 6);

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

    memcpy( p_key, p_buffer + 4, DVD_KEY_SIZE );

#elif defined( SYS_OS2 )
    INIT_SSC( GPCMD_REPORT_KEY, 12 );

    sdc.command[ 10 ] = DVD_REPORT_KEY1 | (*pi_agid << 6);

    i_ret = DosDevIOCtl(i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                        &sdc, sizeof(sdc), &ulParamLen,
                        p_buffer, sizeof(p_buffer), &ulDataLen);

    memcpy( p_key, p_buffer + 4, DVD_KEY_SIZE );

#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

/*****************************************************************************
 * ioctl_ReadDiscKey: get the disc key
 *****************************************************************************/
int ioctl_ReadDiscKey( int i_fd, int *pi_agid, uint8_t *p_key )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_struct dvd;

    memset( &dvd, 0, sizeof( dvd ) );
    dvd.type = DVD_STRUCT_DISCKEY;
    dvd.disckey.agid = *pi_agid;
    memset( dvd.disckey.value, 0, DVD_DISCKEY_SIZE );

    i_ret = ioctl( i_fd, DVD_READ_STRUCT, &dvd );

    if( i_ret < 0 )
    {
        return i_ret;
    }

    memcpy( p_key, dvd.disckey.value, DVD_DISCKEY_SIZE );

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_struct dvd;

    memset( &dvd, 0, sizeof( dvd ) );
    dvd.format = DVD_STRUCT_DISCKEY;
    dvd.agid = *pi_agid;
    memset( dvd.data, 0, DVD_DISCKEY_SIZE );

    i_ret = ioctl( i_fd, DVDIOCREADSTRUCTURE, &dvd );

    if( i_ret < 0 )
    {
        return i_ret;
    }

    memcpy( p_key, dvd.data, DVD_DISCKEY_SIZE );

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_READ_DVD_STRUCTURE, DVD_DISCKEY_SIZE + 4 );

    rdc.command[ 7 ]  = DVD_STRUCT_DISCKEY;
    rdc.command[ 10 ] = *pi_agid << 6;

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

    if( i_ret < 0 )
    {
        return i_ret;
    }

    memcpy( p_key, p_buffer + 4, DVD_DISCKEY_SIZE );

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_READ_DVD_STRUCTURE, DVD_DISCKEY_SIZE + 4 );

    sctl_io.cdb[ 7 ]  = DVD_STRUCT_DISCKEY;
    sctl_io.cdb[ 10 ] = *pi_agid << 6;

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

    if( i_ret < 0 )
    {
        return i_ret;
    }

    memcpy( p_key, p_buffer + 4, DVD_DISCKEY_SIZE );

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_READ_DVD_STRUCTURE, DVD_DISCKEY_SIZE + 4 );

    rs_cdb.cdb_opaque[ 7 ] = DVD_STRUCT_DISCKEY;
    rs_cdb.cdb_opaque[ 10 ] = *pi_agid << 6;

    i_ret = SolarisSendUSCSI( i_fd, &sc );

    if( i_ret < 0 || sc.uscsi_status )
    {
        i_ret = -1;
        return i_ret;
    }

    memcpy( p_key, p_buffer + 4, DVD_DISCKEY_SIZE );

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_read_structure_t, DVDDiscKeyInfo,
                   kDVDStructureFormatDiscKeyInfo );

    dvd.grantID = *pi_agid;

    i_ret = ioctl( i_fd, DKIOCDVDREADSTRUCTURE, &dvd );

    memcpy( p_key, dvdbs.discKeyStructures, DVD_DISCKEY_SIZE );

#elif defined( WIN32 )
   // if( WIN2K ) /* NT/2k/XP */
    {
        DWORD tmp;
        uint8_t buffer[DVD_DISK_KEY_LENGTH];
        PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY) &buffer;

        memset( &buffer, 0, sizeof( buffer ) );

        key->KeyLength  = DVD_DISK_KEY_LENGTH;
        key->SessionId  = *pi_agid;
        key->KeyType    = DvdDiskKey;
        key->KeyFlags   = 0;

		  SetLastError(0);

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_READ_KEY, key,
                key->KeyLength, key, key->KeyLength, &tmp, NULL ) ? 0 : -1;

		  DWORD err = GetLastError();
        if( i_ret < 0 )
        {
            return i_ret;
        }

        memcpy( p_key, key->KeyData, DVD_DISCKEY_SIZE );
    }
#if 0
    else
    {
        INIT_SSC( GPCMD_READ_DVD_STRUCTURE, DVD_DISCKEY_SIZE + 4 );

        ssc.CDBByte[ 7 ]  = DVD_STRUCT_DISCKEY;
        ssc.CDBByte[ 10 ] = *pi_agid << 6;

        i_ret = WinSendSSC( i_fd, &ssc );

        if( i_ret < 0 )
        {
            return i_ret;
        }

        memcpy( p_key, p_buffer + 4, DVD_DISCKEY_SIZE );
    }
#endif

#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_READ_DVD_STRUCTURE, DVD_DISCKEY_SIZE + 4 );

    p_cpt->cam_cdb[ 7 ] = DVD_STRUCT_DISCKEY;
    p_cpt->cam_cdb[ 10 ] = *pi_agid << 6;

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

    memcpy( p_key, p_buffer + 4, DVD_DISCKEY_SIZE );

#elif defined ( SYS_OS2 )
    INIT_SSC( GPCMD_READ_DVD_STRUCTURE, DVD_DISCKEY_SIZE + 4 );

    sdc.command[ 7 ]  = DVD_STRUCT_DISCKEY;
    sdc.command[ 10 ] = *pi_agid << 6;

    i_ret = DosDevIOCtl(i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                        &sdc, sizeof(sdc), &ulParamLen,
                        p_buffer, sizeof(p_buffer), &ulDataLen);

    if( i_ret < 0 )
    {
        return i_ret;
    }

    memcpy( p_key, p_buffer + 4, DVD_DISCKEY_SIZE );

#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

/*****************************************************************************
 * ioctl_SendKey2: send the second key to the drive
 *****************************************************************************/
int ioctl_SendKey2( int i_fd, int *pi_agid, uint8_t *p_key )
{
    int i_ret;

#if defined( HAVE_LINUX_DVD_STRUCT )
    dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.type = DVD_HOST_SEND_KEY2;
    auth_info.hsk.agid = *pi_agid;

    memcpy( auth_info.hsk.key, p_key, DVD_KEY_SIZE );

    i_ret = ioctl( i_fd, DVD_AUTH, &auth_info );

#elif defined( HAVE_BSD_DVD_STRUCT )
    struct dvd_authinfo auth_info;

    memset( &auth_info, 0, sizeof( auth_info ) );
    auth_info.format = DVD_SEND_KEY2;
    auth_info.agid = *pi_agid;

    memcpy( auth_info.keychal, p_key, DVD_KEY_SIZE );

    i_ret = ioctl( i_fd, DVDIOCSENDKEY, &auth_info );

#elif defined( SYS_BEOS )
    INIT_RDC( GPCMD_SEND_KEY, 12 );

    rdc.command[ 10 ] = DVD_SEND_KEY2 | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xa;
    memcpy( p_buffer + 4, p_key, DVD_KEY_SIZE );

    i_ret = ioctl( i_fd, B_RAW_DEVICE_COMMAND, &rdc, sizeof(rdc) );

#elif defined( HPUX_SCTL_IO )
    INIT_SCTL_IO( GPCMD_SEND_KEY, 12 );

    sctl_io.cdb[ 10 ] = DVD_SEND_KEY2 | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xa;
    memcpy( p_buffer + 4, p_key, DVD_KEY_SIZE );

    i_ret = ioctl( i_fd, SIOC_IO, &sctl_io );

#elif defined( SOLARIS_USCSI )
    INIT_USCSI( GPCMD_SEND_KEY, 12 );

    rs_cdb.cdb_opaque[ 10 ] = DVD_SEND_KEY2 | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xa;
    memcpy( p_buffer + 4, p_key, DVD_KEY_SIZE );

    if( SolarisSendUSCSI( i_fd, &sc ) < 0 || sc.uscsi_status )
    {
        return -1;
    }

    i_ret = 0;

#elif defined( DARWIN_DVD_IOCTL )
    INIT_DVDIOCTL( dk_dvd_send_key_t, DVDKey2Info,
                   kDVDKeyFormatKey2 );

    dvd.grantID = *pi_agid;
    dvd.keyClass = kDVDKeyClassCSS_CPPM_CPRM;

    dvdbs.dataLength[ 1 ] = 0xa;
    memcpy( dvdbs.key2Value, p_key, DVD_KEY_SIZE );

    i_ret = ioctl( i_fd, DKIOCDVDSENDKEY, &dvd );

#elif defined( WIN32 )
//    if( WIN2K ) /* NT/2k/XP */
    {
        DWORD tmp;
        uint8_t buffer[DVD_BUS_KEY_LENGTH];
        PDVD_COPY_PROTECT_KEY key = (PDVD_COPY_PROTECT_KEY) &buffer;

        memset( &buffer, 0, sizeof( buffer ) );

        key->KeyLength  = DVD_BUS_KEY_LENGTH;
        key->SessionId  = *pi_agid;
        key->KeyType    = DvdBusKey2;
        key->KeyFlags   = 0;

        memcpy( key->KeyData, p_key, DVD_KEY_SIZE );

        i_ret = DeviceIoControl( (HANDLE) i_fd, IOCTL_DVD_SEND_KEY, key,
                 key->KeyLength, key, key->KeyLength, &tmp, NULL ) ? 0 : -1;
    }
  #if 0
	 else
    {
        INIT_SSC( GPCMD_SEND_KEY, 12 );

        ssc.CDBByte[ 10 ] = DVD_SEND_KEY2 | (*pi_agid << 6);

        p_buffer[ 1 ] = 0xa;
        memcpy( p_buffer + 4, p_key, DVD_KEY_SIZE );

        i_ret = WinSendSSC( i_fd, &ssc );
    }
#endif
#elif defined( __QNXNTO__ )

    INIT_CPT( GPCMD_SEND_KEY, 12 );

    p_cpt->cam_cdb[ 10 ] = DVD_SEND_KEY2 | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xa;
    memcpy( p_buffer + 4, p_key, DVD_KEY_SIZE );

    i_ret = devctl(i_fd, DCMD_CAM_PASS_THRU, p_cpt, structSize, NULL);

#elif defined( SYS_OS2 )
    INIT_SSC( GPCMD_SEND_KEY, 12 );

    sdc.command[ 10 ] = DVD_SEND_KEY2 | (*pi_agid << 6);

    p_buffer[ 1 ] = 0xa;
    memcpy( p_buffer + 4, p_key, DVD_KEY_SIZE );

    i_ret = DosDevIOCtl( i_fd, IOCTL_CDROMDISK, CDROMDISK_EXECMD,
                         &sdc, sizeof(sdc), &ulParamLen,
                         p_buffer, sizeof(p_buffer), &ulDataLen );

#else
#   error "DVD ioctls are unavailable on this system"

#endif
    return i_ret;
}

static uint8_t p_crypt_tab0[ 256 ] =
{
    0xB7, 0xF4, 0x82, 0x57, 0xDA, 0x4D, 0xDB, 0xE2,
    0x2F, 0x52, 0x1A, 0xA8, 0x68, 0x5A, 0x8A, 0xFF,
    0xFB, 0x0E, 0x6D, 0x35, 0xF7, 0x5C, 0x76, 0x12,
    0xCE, 0x25, 0x79, 0x29, 0x39, 0x62, 0x08, 0x24,
    0xA5, 0x85, 0x7B, 0x56, 0x01, 0x23, 0x68, 0xCF,
    0x0A, 0xE2, 0x5A, 0xED, 0x3D, 0x59, 0xB0, 0xA9,
    0xB0, 0x2C, 0xF2, 0xB8, 0xEF, 0x32, 0xA9, 0x40,
    0x80, 0x71, 0xAF, 0x1E, 0xDE, 0x8F, 0x58, 0x88,
    0xB8, 0x3A, 0xD0, 0xFC, 0xC4, 0x1E, 0xB5, 0xA0,
    0xBB, 0x3B, 0x0F, 0x01, 0x7E, 0x1F, 0x9F, 0xD9,
    0xAA, 0xB8, 0x3D, 0x9D, 0x74, 0x1E, 0x25, 0xDB,
    0x37, 0x56, 0x8F, 0x16, 0xBA, 0x49, 0x2B, 0xAC,
    0xD0, 0xBD, 0x95, 0x20, 0xBE, 0x7A, 0x28, 0xD0,
    0x51, 0x64, 0x63, 0x1C, 0x7F, 0x66, 0x10, 0xBB,
    0xC4, 0x56, 0x1A, 0x04, 0x6E, 0x0A, 0xEC, 0x9C,
    0xD6, 0xE8, 0x9A, 0x7A, 0xCF, 0x8C, 0xDB, 0xB1,
    0xEF, 0x71, 0xDE, 0x31, 0xFF, 0x54, 0x3E, 0x5E,
    0x07, 0x69, 0x96, 0xB0, 0xCF, 0xDD, 0x9E, 0x47,
    0xC7, 0x96, 0x8F, 0xE4, 0x2B, 0x59, 0xC6, 0xEE,
    0xB9, 0x86, 0x9A, 0x64, 0x84, 0x72, 0xE2, 0x5B,
    0xA2, 0x96, 0x58, 0x99, 0x50, 0x03, 0xF5, 0x38,
    0x4D, 0x02, 0x7D, 0xE7, 0x7D, 0x75, 0xA7, 0xB8,
    0x67, 0x87, 0x84, 0x3F, 0x1D, 0x11, 0xE5, 0xFC,
    0x1E, 0xD3, 0x83, 0x16, 0xA5, 0x29, 0xF6, 0xC7,
    0x15, 0x61, 0x29, 0x1A, 0x43, 0x4F, 0x9B, 0xAF,
    0xC5, 0x87, 0x34, 0x6C, 0x0F, 0x3B, 0xA8, 0x1D,
    0x45, 0x58, 0x25, 0xDC, 0xA8, 0xA3, 0x3B, 0xD1,
    0x79, 0x1B, 0x48, 0xF2, 0xE9, 0x93, 0x1F, 0xFC,
    0xDB, 0x2A, 0x90, 0xA9, 0x8A, 0x3D, 0x39, 0x18,
    0xA3, 0x8E, 0x58, 0x6C, 0xE0, 0x12, 0xBB, 0x25,
    0xCD, 0x71, 0x22, 0xA2, 0x64, 0xC6, 0xE7, 0xFB,
    0xAD, 0x94, 0x77, 0x04, 0x9A, 0x39, 0xCF, 0x7C
};

static uint8_t p_crypt_tab1[ 256 ] =
{
    0x8C, 0x47, 0xB0, 0xE1, 0xEB, 0xFC, 0xEB, 0x56,
    0x10, 0xE5, 0x2C, 0x1A, 0x5D, 0xEF, 0xBE, 0x4F,
    0x08, 0x75, 0x97, 0x4B, 0x0E, 0x25, 0x8E, 0x6E,
    0x39, 0x5A, 0x87, 0x53, 0xC4, 0x1F, 0xF4, 0x5C,
    0x4E, 0xE6, 0x99, 0x30, 0xE0, 0x42, 0x88, 0xAB,
    0xE5, 0x85, 0xBC, 0x8F, 0xD8, 0x3C, 0x54, 0xC9,
    0x53, 0x47, 0x18, 0xD6, 0x06, 0x5B, 0x41, 0x2C,
    0x67, 0x1E, 0x41, 0x74, 0x33, 0xE2, 0xB4, 0xE0,
    0x23, 0x29, 0x42, 0xEA, 0x55, 0x0F, 0x25, 0xB4,
    0x24, 0x2C, 0x99, 0x13, 0xEB, 0x0A, 0x0B, 0xC9,
    0xF9, 0x63, 0x67, 0x43, 0x2D, 0xC7, 0x7D, 0x07,
    0x60, 0x89, 0xD1, 0xCC, 0xE7, 0x94, 0x77, 0x74,
    0x9B, 0x7E, 0xD7, 0xE6, 0xFF, 0xBB, 0x68, 0x14,
    0x1E, 0xA3, 0x25, 0xDE, 0x3A, 0xA3, 0x54, 0x7B,
    0x87, 0x9D, 0x50, 0xCA, 0x27, 0xC3, 0xA4, 0x50,
    0x91, 0x27, 0xD4, 0xB0, 0x82, 0x41, 0x97, 0x79,
    0x94, 0x82, 0xAC, 0xC7, 0x8E, 0xA5, 0x4E, 0xAA,
    0x78, 0x9E, 0xE0, 0x42, 0xBA, 0x28, 0xEA, 0xB7,
    0x74, 0xAD, 0x35, 0xDA, 0x92, 0x60, 0x7E, 0xD2,
    0x0E, 0xB9, 0x24, 0x5E, 0x39, 0x4F, 0x5E, 0x63,
    0x09, 0xB5, 0xFA, 0xBF, 0xF1, 0x22, 0x55, 0x1C,
    0xE2, 0x25, 0xDB, 0xC5, 0xD8, 0x50, 0x03, 0x98,
    0xC4, 0xAC, 0x2E, 0x11, 0xB4, 0x38, 0x4D, 0xD0,
    0xB9, 0xFC, 0x2D, 0x3C, 0x08, 0x04, 0x5A, 0xEF,
    0xCE, 0x32, 0xFB, 0x4C, 0x92, 0x1E, 0x4B, 0xFB,
    0x1A, 0xD0, 0xE2, 0x3E, 0xDA, 0x6E, 0x7C, 0x4D,
    0x56, 0xC3, 0x3F, 0x42, 0xB1, 0x3A, 0x23, 0x4D,
    0x6E, 0x84, 0x56, 0x68, 0xF4, 0x0E, 0x03, 0x64,
    0xD0, 0xA9, 0x92, 0x2F, 0x8B, 0xBC, 0x39, 0x9C,
    0xAC, 0x09, 0x5E, 0xEE, 0xE5, 0x97, 0xBF, 0xA5,
    0xCE, 0xFA, 0x28, 0x2C, 0x6D, 0x4F, 0xEF, 0x77,
    0xAA, 0x1B, 0x79, 0x8E, 0x97, 0xB4, 0xC3, 0xF4
};

static uint8_t p_crypt_tab2[ 256 ] =
{
    0xB7, 0x75, 0x81, 0xD5, 0xDC, 0xCA, 0xDE, 0x66,
    0x23, 0xDF, 0x15, 0x26, 0x62, 0xD1, 0x83, 0x77,
    0xE3, 0x97, 0x76, 0xAF, 0xE9, 0xC3, 0x6B, 0x8E,
    0xDA, 0xB0, 0x6E, 0xBF, 0x2B, 0xF1, 0x19, 0xB4,
    0x95, 0x34, 0x48, 0xE4, 0x37, 0x94, 0x5D, 0x7B,
    0x36, 0x5F, 0x65, 0x53, 0x07, 0xE2, 0x89, 0x11,
    0x98, 0x85, 0xD9, 0x12, 0xC1, 0x9D, 0x84, 0xEC,
    0xA4, 0xD4, 0x88, 0xB8, 0xFC, 0x2C, 0x79, 0x28,
    0xD8, 0xDB, 0xB3, 0x1E, 0xA2, 0xF9, 0xD0, 0x44,
    0xD7, 0xD6, 0x60, 0xEF, 0x14, 0xF4, 0xF6, 0x31,
    0xD2, 0x41, 0x46, 0x67, 0x0A, 0xE1, 0x58, 0x27,
    0x43, 0xA3, 0xF8, 0xE0, 0xC8, 0xBA, 0x5A, 0x5C,
    0x80, 0x6C, 0xC6, 0xF2, 0xE8, 0xAD, 0x7D, 0x04,
    0x0D, 0xB9, 0x3C, 0xC2, 0x25, 0xBD, 0x49, 0x63,
    0x8C, 0x9F, 0x51, 0xCE, 0x20, 0xC5, 0xA1, 0x50,
    0x92, 0x2D, 0xDD, 0xBC, 0x8D, 0x4F, 0x9A, 0x71,
    0x2F, 0x30, 0x1D, 0x73, 0x39, 0x13, 0xFB, 0x1A,
    0xCB, 0x24, 0x59, 0xFE, 0x05, 0x96, 0x57, 0x0F,
    0x1F, 0xCF, 0x54, 0xBE, 0xF5, 0x06, 0x1B, 0xB2,
    0x6D, 0xD3, 0x4D, 0x32, 0x56, 0x21, 0x33, 0x0B,
    0x52, 0xE7, 0xAB, 0xEB, 0xA6, 0x74, 0x00, 0x4C,
    0xB1, 0x7F, 0x82, 0x99, 0x87, 0x0E, 0x5E, 0xC0,
    0x8F, 0xEE, 0x6F, 0x55, 0xF3, 0x7E, 0x08, 0x90,
    0xFA, 0xB6, 0x64, 0x70, 0x47, 0x4A, 0x17, 0xA7,
    0xB5, 0x40, 0x8A, 0x38, 0xE5, 0x68, 0x3E, 0x8B,
    0x69, 0xAA, 0x9B, 0x42, 0xA5, 0x10, 0x01, 0x35,
    0xFD, 0x61, 0x9E, 0xE6, 0x16, 0x9C, 0x86, 0xED,
    0xCD, 0x2E, 0xFF, 0xC4, 0x5B, 0xA0, 0xAE, 0xCC,
    0x4B, 0x3B, 0x03, 0xBB, 0x1C, 0x2A, 0xAC, 0x0C,
    0x3F, 0x93, 0xC7, 0x72, 0x7A, 0x09, 0x22, 0x3D,
    0x45, 0x78, 0xA9, 0xA8, 0xEA, 0xC9, 0x6A, 0xF7,
    0x29, 0x91, 0xF0, 0x02, 0x18, 0x3A, 0x4E, 0x7C
};

static uint8_t p_crypt_tab3[ 288 ] =
{
    0x73, 0x51, 0x95, 0xE1, 0x12, 0xE4, 0xC0, 0x58,
    0xEE, 0xF2, 0x08, 0x1B, 0xA9, 0xFA, 0x98, 0x4C,
    0xA7, 0x33, 0xE2, 0x1B, 0xA7, 0x6D, 0xF5, 0x30,
    0x97, 0x1D, 0xF3, 0x02, 0x60, 0x5A, 0x82, 0x0F,
    0x91, 0xD0, 0x9C, 0x10, 0x39, 0x7A, 0x83, 0x85,
    0x3B, 0xB2, 0xB8, 0xAE, 0x0C, 0x09, 0x52, 0xEA,
    0x1C, 0xE1, 0x8D, 0x66, 0x4F, 0xF3, 0xDA, 0x92,
    0x29, 0xB9, 0xD5, 0xC5, 0x77, 0x47, 0x22, 0x53,
    0x14, 0xF7, 0xAF, 0x22, 0x64, 0xDF, 0xC6, 0x72,
    0x12, 0xF3, 0x75, 0xDA, 0xD7, 0xD7, 0xE5, 0x02,
    0x9E, 0xED, 0xDA, 0xDB, 0x4C, 0x47, 0xCE, 0x91,
    0x06, 0x06, 0x6D, 0x55, 0x8B, 0x19, 0xC9, 0xEF,
    0x8C, 0x80, 0x1A, 0x0E, 0xEE, 0x4B, 0xAB, 0xF2,
    0x08, 0x5C, 0xE9, 0x37, 0x26, 0x5E, 0x9A, 0x90,
    0x00, 0xF3, 0x0D, 0xB2, 0xA6, 0xA3, 0xF7, 0x26,
    0x17, 0x48, 0x88, 0xC9, 0x0E, 0x2C, 0xC9, 0x02,
    0xE7, 0x18, 0x05, 0x4B, 0xF3, 0x39, 0xE1, 0x20,
    0x02, 0x0D, 0x40, 0xC7, 0xCA, 0xB9, 0x48, 0x30,
    0x57, 0x67, 0xCC, 0x06, 0xBF, 0xAC, 0x81, 0x08,
    0x24, 0x7A, 0xD4, 0x8B, 0x19, 0x8E, 0xAC, 0xB4,
    0x5A, 0x0F, 0x73, 0x13, 0xAC, 0x9E, 0xDA, 0xB6,
    0xB8, 0x96, 0x5B, 0x60, 0x88, 0xE1, 0x81, 0x3F,
    0x07, 0x86, 0x37, 0x2D, 0x79, 0x14, 0x52, 0xEA,
    0x73, 0xDF, 0x3D, 0x09, 0xC8, 0x25, 0x48, 0xD8,
    0x75, 0x60, 0x9A, 0x08, 0x27, 0x4A, 0x2C, 0xB9,
    0xA8, 0x8B, 0x8A, 0x73, 0x62, 0x37, 0x16, 0x02,
    0xBD, 0xC1, 0x0E, 0x56, 0x54, 0x3E, 0x14, 0x5F,
    0x8C, 0x8F, 0x6E, 0x75, 0x1C, 0x07, 0x39, 0x7B,
    0x4B, 0xDB, 0xD3, 0x4B, 0x1E, 0xC8, 0x7E, 0xFE,
    0x3E, 0x72, 0x16, 0x83, 0x7D, 0xEE, 0xF5, 0xCA,
    0xC5, 0x18, 0xF9, 0xD8, 0x68, 0xAB, 0x38, 0x85,
    0xA8, 0xF0, 0xA1, 0x73, 0x9F, 0x5D, 0x19, 0x0B,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x33, 0x72, 0x39, 0x25, 0x67, 0x26, 0x6D, 0x71,
    0x36, 0x77, 0x3C, 0x20, 0x62, 0x23, 0x68, 0x74,
    0xC3, 0x82, 0xC9, 0x15, 0x57, 0x16, 0x5D, 0x81
};


/*****************************************************************************
 * CryptKey : shuffles bits and unencrypt keys.
 *****************************************************************************
 * Used during authentication and disc key negociation in GetBusKey.
 * i_key_type : 0->key1, 1->key2, 2->buskey.
 * i_variant : between 0 and 31.
 *****************************************************************************/
static void CryptKey( int i_key_type, int i_variant,
                      uint8_t const *p_challenge, uint8_t *p_key )
{
    /* Permutation table for challenge */
    uint8_t pp_perm_challenge[3][10] =
            { { 1, 3, 0, 7, 5, 2, 9, 6, 4, 8 },
              { 6, 1, 9, 3, 8, 5, 7, 4, 0, 2 },
              { 4, 0, 3, 5, 7, 2, 8, 6, 1, 9 } };

    /* Permutation table for variant table for key2 and buskey */
    uint8_t pp_perm_variant[2][32] =
            { { 0x0a, 0x08, 0x0e, 0x0c, 0x0b, 0x09, 0x0f, 0x0d,
                0x1a, 0x18, 0x1e, 0x1c, 0x1b, 0x19, 0x1f, 0x1d,
                0x02, 0x00, 0x06, 0x04, 0x03, 0x01, 0x07, 0x05,
                0x12, 0x10, 0x16, 0x14, 0x13, 0x11, 0x17, 0x15 },
              { 0x12, 0x1a, 0x16, 0x1e, 0x02, 0x0a, 0x06, 0x0e,
                0x10, 0x18, 0x14, 0x1c, 0x00, 0x08, 0x04, 0x0c,
                0x13, 0x1b, 0x17, 0x1f, 0x03, 0x0b, 0x07, 0x0f,
                0x11, 0x19, 0x15, 0x1d, 0x01, 0x09, 0x05, 0x0d } };

    uint8_t p_variants[32] =
            {   0xB7, 0x74, 0x85, 0xD0, 0xCC, 0xDB, 0xCA, 0x73,
                0x03, 0xFE, 0x31, 0x03, 0x52, 0xE0, 0xB7, 0x42,
                0x63, 0x16, 0xF2, 0x2A, 0x79, 0x52, 0xFF, 0x1B,
                0x7A, 0x11, 0xCA, 0x1A, 0x9B, 0x40, 0xAD, 0x01 };

    /* The "secret" key */
    uint8_t p_secret[5] = { 0x55, 0xD6, 0xC4, 0xC5, 0x28 };

    uint8_t p_bits[30], p_scratch[10], p_tmp1[5], p_tmp2[5];
    uint8_t i_lfsr0_o;  /* 1 bit used */
    uint8_t i_lfsr1_o;  /* 1 bit used */
    uint8_t i_css_variant, i_cse, i_index, i_combined, i_carry;
    uint8_t i_val = 0;
    uint32_t i_lfsr0, i_lfsr1;
    int i_term = 0;
    int i_bit;
    int i;

    for (i = 9; i >= 0; --i)
        p_scratch[i] = p_challenge[pp_perm_challenge[i_key_type][i]];

    i_css_variant = ( i_key_type == 0 ) ? i_variant :
                    pp_perm_variant[i_key_type-1][i_variant];

    /*
     * This encryption engine implements one of 32 variations
     * one the same theme depending upon the choice in the
     * variant parameter (0 - 31).
     *
     * The algorithm itself manipulates a 40 bit input into
     * a 40 bit output.
     * The parameter 'input' is 80 bits.  It consists of
     * the 40 bit input value that is to be encrypted followed
     * by a 40 bit seed value for the pseudo random number
     * generators.
     */

    /* Feed the secret into the input values such that
     * we alter the seed to the LFSR's used above,  then
     * generate the bits to play with.
     */
    for( i = 5 ; --i >= 0 ; )
    {
        p_tmp1[i] = p_scratch[5 + i] ^ p_secret[i] ^ p_crypt_tab2[i];
    }

    /*
     * We use two LFSR's (seeded from some of the input data bytes) to
     * generate two streams of pseudo-random bits.  These two bit streams
     * are then combined by simply adding with carry to generate a final
     * sequence of pseudo-random bits which is stored in the buffer that
     * 'output' points to the end of - len is the size of this buffer.
     *
     * The first LFSR is of degree 25,  and has a polynomial of:
     * x^13 + x^5 + x^4 + x^1 + 1
     *
     * The second LSFR is of degree 17,  and has a (primitive) polynomial of:
     * x^15 + x^1 + 1
     *
     * I don't know if these polynomials are primitive modulo 2,  and thus
     * represent maximal-period LFSR's.
     *
     *
     * Note that we take the output of each LFSR from the new shifted in
     * bit,  not the old shifted out bit.  Thus for ease of use the LFSR's
     * are implemented in bit reversed order.
     *
     */

    /* In order to ensure that the LFSR works we need to ensure that the
     * initial values are non-zero.  Thus when we initialise them from
     * the seed,  we ensure that a bit is set.
     */
    i_lfsr0 = ( p_tmp1[0] << 17 ) | ( p_tmp1[1] << 9 ) |
              (( p_tmp1[2] & ~7 ) << 1 ) | 8 | ( p_tmp1[2] & 7 );
    i_lfsr1 = ( p_tmp1[3] << 9 ) | 0x100 | p_tmp1[4];

    i_index = sizeof(p_bits);
    i_carry = 0;

    do
    {
        for( i_bit = 0, i_val = 0 ; i_bit < 8 ; ++i_bit )
        {

            i_lfsr0_o = ( ( i_lfsr0 >> 24 ) ^ ( i_lfsr0 >> 21 ) ^
                        ( i_lfsr0 >> 20 ) ^ ( i_lfsr0 >> 12 ) ) & 1;
            i_lfsr0 = ( i_lfsr0 << 1 ) | i_lfsr0_o;

            i_lfsr1_o = ( ( i_lfsr1 >> 16 ) ^ ( i_lfsr1 >> 2 ) ) & 1;
            i_lfsr1 = ( i_lfsr1 << 1 ) | i_lfsr1_o;

            i_combined = !i_lfsr1_o + i_carry + !i_lfsr0_o;
            /* taking bit 1 */
            i_carry = ( i_combined >> 1 ) & 1;
            i_val |= ( i_combined & 1 ) << i_bit;
        }

        p_bits[--i_index] = i_val;
    } while( i_index > 0 );

    /* This term is used throughout the following to
     * select one of 32 different variations on the
     * algorithm.
     */
    i_cse = p_variants[i_css_variant] ^ p_crypt_tab2[i_css_variant];

    /* Now the actual blocks doing the encryption.  Each
     * of these works on 40 bits at a time and are quite
     * similar.
     */
    i_index = 0;
    for( i = 5, i_term = 0 ; --i >= 0 ; i_term = p_scratch[i] )
    {
        i_index = p_bits[25 + i] ^ p_scratch[i];
        i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

        p_tmp1[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
    }
    p_tmp1[4] ^= p_tmp1[0];

    for( i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp1[i] )
    {
        i_index = p_bits[20 + i] ^ p_tmp1[i];
        i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

        p_tmp2[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
    }
    p_tmp2[4] ^= p_tmp2[0];

    for( i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp2[i] )
    {
        i_index = p_bits[15 + i] ^ p_tmp2[i];
        i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;
        i_index = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;

        p_tmp1[i] = p_crypt_tab0[i_index] ^ p_crypt_tab2[i_index];
    }
    p_tmp1[4] ^= p_tmp1[0];

    for( i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp1[i] )
    {
        i_index = p_bits[10 + i] ^ p_tmp1[i];
        i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

        i_index = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;

        p_tmp2[i] = p_crypt_tab0[i_index] ^ p_crypt_tab2[i_index];
    }
    p_tmp2[4] ^= p_tmp2[0];

    for( i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp2[i] )
    {
        i_index = p_bits[5 + i] ^ p_tmp2[i];
        i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

        p_tmp1[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
    }
    p_tmp1[4] ^= p_tmp1[0];

    for(i = 5, i_term = 0 ; --i >= 0 ; i_term = p_tmp1[i] )
    {
        i_index = p_bits[i] ^ p_tmp1[i];
        i_index = p_crypt_tab1[i_index] ^ ~p_crypt_tab2[i_index] ^ i_cse;

        p_key[i] = p_crypt_tab2[i_index] ^ p_crypt_tab3[i_index] ^ i_term;
    }

    return;
}
#endif

int DecodeDVD()
{
#if 0
	HANDLE hDevice = CreateFile("\\\\.\\D:", GENERIC_READ/* | GENERIC_WRITE*/, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, NULL);
	if (hDevice != INVALID_HANDLE_VALUE)
	{
		{
			int agid;

			int ret = ioctl_ReportAgid((int)hDevice, &agid);
			int i = 0;
			while (ret == -1 && i < 4)
			{
			  ioctl_InvalidateAgid( (int)hDevice, &i );
				ret = ioctl_ReportAgid((int)hDevice, &agid);
				i++;
			}

			ASSERT(ret != -1);

			if (false)
			{

			uint8 p_challenge[10];
			uint8 p_buffer[10];

    /* Setup a challenge, any values should work */
    for( i = 0 ; i < 10; ++i )
    {
        p_challenge[i] = i;
    }

    /* Get challenge from host */
    for( i = 0 ; i < 10 ; ++i )
    {
        p_buffer[9-i] = p_challenge[i];
    }

			if (ioctl_SendChallenge((int)hDevice, &agid, p_challenge) < 0)
			{
				ASSERT(0);
			}

			if (ioctl_ReportKey1((int)hDevice, &agid, p_buffer) < 0)
			{
				ASSERT(0);
			}

			uint8 p_key1[5];
			uint8 p_key2[5];
			uint8 p_key_check[5];

		 /* Send key1 to host */
		 for( i = 0 ; i < 5 ; i++ )
		 {
			  p_key1[i] = p_buffer[4-i];
		 }

		 uint8_t i_variant = 0;

		 for( i = 0 ; i < 32 ; ++i )
		 {
			  CryptKey( 0, i, p_challenge, p_key_check );

			  if( memcmp( p_key_check, p_key1, 5 ) == 0 )
			  {
					//print_debug( dvdcss, "drive authenticated, using variant %d", i );
					i_variant = i;
					break;
			  }
		 }

		 if( i == 32 )
		 {
			//  print_error( dvdcss, "drive would not authenticate" );
			  ioctl_InvalidateAgid( (int)hDevice, &/*dvdcss->css.i_*/agid );
			  return -1;
		 }

		 /* Get challenge from LU */
		 if( ioctl_ReportChallenge( (int)hDevice,
											 &/*dvdcss->css.i_*/agid, p_buffer ) < 0 )
		 {
			//  print_error( dvdcss, "ioctl ReportKeyChallenge failed" );
			  ioctl_InvalidateAgid( (int)hDevice, &/*dvdcss->css.i_*/agid );
			  return -1;
		 }

		 /* Send challenge to host */
		 for( i = 0 ; i < 10 ; ++i )
		 {
			  p_challenge[i] = p_buffer[9-i];
		 }

		 CryptKey( 1, i_variant, p_challenge, p_key2 );

		 /* Get key2 from host */
		 for( i = 0 ; i < 5 ; ++i )
		 {
			  p_buffer[4-i] = p_key2[i];
		 }

		 /* Send key2 to LU */
		 if( ioctl_SendKey2( (int)hDevice, &/*dvdcss->css.i_*/agid, p_buffer ) < 0 )
		 {
			 // print_error( dvdcss, "ioctl SendKey2 failed" );
			  ioctl_InvalidateAgid( (int)hDevice, &/*dvdcss->css.i_*/agid );
			  return -1;
		 }

		 /* The drive has accepted us as authentic. */
	//	 print_debug( dvdcss, "authentication established" );

		 memcpy( p_challenge, p_key1, 5 );
		 memcpy( p_challenge + 5, p_key2, 5 );

#if 0
		 CryptKey( 2, i_variant, p_challenge, dvdcss->css.p_bus_key );
#endif
//
		 }

			uint8 key[4096];
			ioctl_ReadDiscKey((int)hDevice, &agid, key);
	}

		if (false)
		{
        INIT_SPTD( GPCMD_READ_DVD_STRUCTURE, 8 );

		  int copy;
			HANDLE i_fd = hDevice;
			int i_layer = 0;
			int *pi_copyright = &copy;

        /*  When using IOCTL_DVD_READ_STRUCTURE and
            DVD_COPYRIGHT_DESCRIPTOR, CopyrightProtectionType
            seems to be always 6 ???
            To work around this MS bug we try to send a raw scsi command
            instead (if we've got enough privileges to do so). */

        sptd.Cdb[ 6 ] = i_layer;
        sptd.Cdb[ 7 ] = DVD_STRUCT_COPYRIGHT;

     int   i_ret = SEND_SPTD( i_fd, &sptd, &tmp );

        if( i_ret == 0 )
        {
            *pi_copyright = p_buffer[ 4 ];
        }
		}

		uint8 buffer[2048*6];

		ULONG low = SetFilePointer(hDevice, 0, NULL, FILE_CURRENT);

		// Logical sector 16

	//	SetFilePointer(hDevice, 16*2064, NULL, FILE_BEGIN);
		SetFilePointer(hDevice, 16*2048, NULL, FILE_BEGIN);

		ULONG nRead;
		ReadFile(hDevice, buffer, 2048, &nRead, NULL);
		sTag tag = *(sTag*)buffer;

		tag.TagIdentifier = LittleEndian16(tag.TagIdentifier);
		tag.DescriptorVersion = LittleEndian16(tag.DescriptorVersion);
		tag.TagLocation = LittleEndian32(tag.TagLocation);

		// Anchor volume descriptor pointer
		SetFilePointer(hDevice, 256*2048, NULL, FILE_BEGIN);
		ReadFile(hDevice, buffer, 2048, &nRead, NULL);
		uint8* p = buffer;
		tag = *(sTag*)p; p += sizeof(sTag);
		tag.TagIdentifier = LittleEndian16(tag.TagIdentifier);
		tag.DescriptorVersion = LittleEndian16(tag.DescriptorVersion);
		tag.TagLocation = LittleEndian32(tag.TagLocation);

		extent_ad MainVolume = *(extent_ad*)p; p += sizeof(extent_ad);
		MainVolume.Location = LittleEndian32(MainVolume.Location);

		extent_ad ReserveVolume = *(extent_ad*)p; p += sizeof(extent_ad);
		ReserveVolume.Location = LittleEndian32(ReserveVolume.Location);

		uint32 location = MainVolume.Location;

		uint32 PartitionStartingLocation;
		uint32 PartitionLength;

		uint32 filelen;
		ULONGLONG FSD_Location;

		for (int i = 0; i < MainVolume.Length>>11; i++)
		{
			SetFilePointer(hDevice, location<<11, NULL, FILE_BEGIN);
			ReadFile(hDevice, buffer, 2048, &nRead, NULL);
			p = buffer;
			tag = *(sTag*)p; p += sizeof(sTag);

			if (tag.TagIdentifier == 5)	// Partition descriptor
			{
				uint32 VolumeDescriptorSequenceNumber = LittleEndian32(*(uint32*)p); p += 4;
				uint16 PartitionFlags = LittleEndian16(*(uint16*)p); p += 2;
				uint16 PartitionNumber = LittleEndian16(*(uint16*)p); p += 2;
				EntityID PartitionContents = *(EntityID*)p; p += sizeof(EntityID);
				p += 128;	// PartitionContentsUse
				uint32 AccessType = *(uint32*)p; p += 4;
				PartitionStartingLocation = *(uint32*)p; p += 4;
				PartitionLength = *(uint32*)p; p += 4;
				EntityID ImplementationIdentifier = *(EntityID*)p; p += sizeof(EntityID);
				p += 128;	// ImplementationUse
				p += 156;	// reserved
			}
			else if (tag.TagIdentifier == 6)	// Logical Volume Descriptor
			{
				uint32 VolumeDescriptorSequenceNumber = *(uint32*)p; p += 4;
				charspec DescriptorCharacterSet = *(charspec*)p; p += sizeof(charspec);
				uint8 LogicalVolumeIdentifier[128];
				memcpy(LogicalVolumeIdentifier, p, 128); p += 128;
				uint32 LogicalBlockSize = *(uint32*)p; p += 4;
				EntityID DomainIdentifier = *(EntityID*)p; p += sizeof(EntityID);
				//p += 16;	// LogicalVolumeContentsUse
				filelen = *(uint32*)p; p += 4;
				FSD_Location = *p++;
				FSD_Location |= (*p++)<<8;
				FSD_Location |= (*p++)<<16;
				FSD_Location |= (*p++)<<24;
				FSD_Location |= (*p++)<<32;
				FSD_Location |= (*p++)<<40;
				p += 6;
				uint32 MapTableLength = *(uint32*)p; p += 4;
				uint32 NumberofPartitionMaps = *(uint32*)p; p += 4;
				EntityID ImplementationIdentifier = *(EntityID*)p; p += sizeof(EntityID);
				p += 128;	// ImplementationUse
				extent_ad IntegritySequenceExtent = *(extent_ad*)p; p += sizeof(extent_ad);

			}

			location++;
		}

		uint32 RootDirectoryICBLength;
		ULONGLONG RootDirectoryICBLocation;

		for (i = 0; i < filelen>>11; i++)
		{
			SetFilePointer(hDevice, (PartitionStartingLocation + FSD_Location + i)<<11, NULL, FILE_BEGIN);
			ReadFile(hDevice, buffer, 2048, &nRead, NULL);
			p = buffer;
			tag = *(sTag*)p; p += sizeof(sTag);

		// FileSetDescriptor
			if (tag.TagIdentifier == 256)
			{
				timestamp RecordingDateandTime = *(timestamp*)p; p += sizeof(timestamp);
				uint16 InterchangeLevel = *(uint16*)p; p += 2;
				uint16 MaximumInterchangeLevel = *(uint16*)p; p += 2;
				uint32 CharacterSetList = *(uint32*)p; p += 4;
				uint32 MaximumCharacterSetList = *(uint32*)p; p += 4;
				uint32 FileSetNumber = *(uint32*)p; p += 4;
				uint32 FileSetDescriptorNumber = *(uint32*)p; p += 4;
				charspec LogicalVolumeIdentifierCharacterSet = *(charspec*)p; p += sizeof(charspec);
				uint8 LogicalVolumeIdentifier[128];
				memcpy(LogicalVolumeIdentifier, p, 128); p += 128;
				charspec FileSetCharacterSet = *(charspec*)p; p += sizeof(charspec);

				uint8 FileSetIdentifier[32];
				memcpy(FileSetIdentifier, p, 32); p += 32;

				uint8 CopyrightFileIdentifier[32];
				memcpy(CopyrightFileIdentifier, p, 32); p += 32;
				
				uint8 AbstractFileIdentifier[32];
				memcpy(AbstractFileIdentifier, p, 32); p += 32;

				RootDirectoryICBLength = *(uint32*)p; p += 4;
				RootDirectoryICBLocation = *p++;
				RootDirectoryICBLocation |= (*p++)<<8;
				RootDirectoryICBLocation |= (*p++)<<16;
				RootDirectoryICBLocation |= (*p++)<<24;
				RootDirectoryICBLocation |= (*p++)<<32;
				RootDirectoryICBLocation |= (*p++)<<40;
			}
		}

		Dir rootDir;
		Build(&rootDir, hDevice, PartitionStartingLocation, RootDirectoryICBLocation);

		FEntry* pChild = rootDir.m_entries["VIDEO_TS"];
		if (pChild)
		{
			Dir dir;
			Build(&dir, hDevice, PartitionStartingLocation, pChild->m_location);

			if (false)
			{
				pChild = dir.m_entries["VIDEO_TS.IFO"];

				if (pChild)
				{
					File file;
					FileEntry(hDevice, PartitionStartingLocation, pChild->m_location, &file);

					UDFStream* ufsstream = new UDFStream(&file);

					ISequentialByteStream* stream = ufsstream;
					stream->AddRef();

					ReadIFO(stream);
				}
			}

			if (true)
			{
				pChild = dir.m_entries["VTS_01_0.VOB"];

				if (pChild)
				{
					File file;
					FileEntry(hDevice, PartitionStartingLocation, pChild->m_location, &file);

					UDFStream* ufsstream = new UDFStream(&file);

					ISequentialByteStream* stream = ufsstream;
					stream->AddRef();

					//ReadIFO(stream);
					uint8 buffer[10000];
					ULONG nRead = stream->Read(buffer, 10000);
				}
			}
		}

		/*
		for (int i = 0; i < nRead; i++)
		{
			if (buffer[i] != 0)
			{
				MessageBeep(-1);
			}
		}
		*/

#if 0
//		DeviceIOControl(

		DWORD bytesReturned;

		BOOL bSuccess = DeviceIoControl(
		  (HANDLE) hDevice,        // handle to device of interest
		  IOCTL_STORAGE_EJECT_MEDIA,   // dwIoControlCode, control code of
											// operation to perform
		  NULL,                    // lpInBuffer is not used; must be NULL
		  0,                       // nInBufferSize is not used; must be zero
		  NULL,                    // lpOutBuffer is not used; must be NULL
		  0,                       // nOutBufferSize is not used;
											// must be zero
		  &bytesReturned,   // pointer to variable to receive
											// output byte count
		  NULL//(LPOVERLAPPED) lpOverlapped  // pointer to OVERLAPPED structure
											// for asynchronous operation
		);
#endif
		CloseHandle(hDevice);
	}
	return 0;
#endif

	FileByteStream* stream = new FileByteStream(ASTR("C:/PappaDVD/Video_ts/VIDEO_TS.IFO"));
	//stream->AddRef();

	ReadVideo_IFO(stream);

	return Success;
}

}
