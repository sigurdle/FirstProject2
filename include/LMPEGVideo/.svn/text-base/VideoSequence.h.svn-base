#ifndef VideoSequence_h
#define VideoSequence_h

namespace System
{
namespace MediaShow
{

class Picture;
class PictureDecoder;
class BitStreamEx;
class ImageBuffer;

class MpegVideoExt MpegVideoSequenceFormat : public Object
{
public:
	CTOR MpegVideoSequenceFormat();

	bool Open(IO::CByteStream* byteStream);

	uint16 GetWidth() const
	{
		return m_horizontal_size;
	}

	uint16 GetHeight() const
	{
		return m_vertical_size;
	}

	ErrorCode video_sequence();

public:

	void sequence_header();
	ErrorCode sequence_extension();
	void extension_and_user_data(int i);
	void extension_data(int i);
	void group_of_pictures_header();
	void user_data();

	BitStreamEx* m_file;

	uint16 m_horizontal_size;
	uint16 m_vertical_size;

	int m_mb_width;

	uint8 m_intra_quantiser_matrix[64];
	uint8 m_non_intra_quantiser_matrix[64];

	uint8 m_chroma_intra_quantiser_matrix[64];
	uint8 m_chroma_non_intra_quantiser_matrix[64];

	uint8	m_aspect_ratio_information : 4,
			m_frame_rate_code : 4;
	uint8	m_chroma_format : 2,
			m_progressive_sequence : 1,
			m_quantiser_scale_code : 5;

	uint8 m_profile_and_level_indication;
	bool m_mpeg1;

	uint32 m_bitrate;

	list<PictureDecoder*> m_groupPictures;
};

class MpegVideoExt CVideoSequence : public Object
{
public:

	CTOR CVideoSequence();

	void SeekFrame(long frame);
	void SetSampleRGBData(PictureDecoder* pPic, LSampleData* sampledata);

	void Scan();

	MpegVideoSequenceFormat* m_mpeg_video;

	IMemAllocator* m_allocator;

	uint m_temporal_offset;

	int m_currentFrame;

	vector<Picture*> m_pictures;
	vector<Picture*> m_displayPictures;
	list<Picture*> m_cached;

//

	int64 m_time;
	list<Picture*> list2;
//	WORD nbuffer;
	ImageBuffer* buffers[512];
	int nbuffers;

	//void Frame();

	//void ShowFrame(PictureDecoder* pPicture);
};

}	// MediaShow
}	// System

#endif // VideoSequence_h
