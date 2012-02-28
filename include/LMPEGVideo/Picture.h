#ifndef __MpegPicture_h_
#define __MpegPicture_h_

namespace System
{
namespace MediaShow
{

enum
{
	PictureStructure_reserved = 0,
	PictureStructure_Top_Field = 1,
	PictureStructure_Bottom_Field = 2,
	PictureStructure_Frame_picture = 3,
};

class ImageBuffer
{
public:
	CTOR ImageBuffer()
	{
		m_bInUse = false;
	}
	bool m_bInUse;
	uint8* m_buf[3];
};

enum
{
	PictureType_I = 1,
	PictureType_P = 2,
	PictureType_B = 3,
};

class Picture : public System::Object
{
public:
	CTOR Picture();

	uint8 m_picture_coding_type/* : 3*/;// I=1, P=2, B=3
	uint16 m_temporal_reference/* : 10*/;

	int m_iGroup;
	ULONG m_index;
	ULONG m_temporal_reference_abs;

//	LONGLONG m_headerpos;
	LONGLONG m_datapos;
//	ULONG m_bitcnt;

	PictureDecoder* m_decoder;
	int m_keepAliveCount;
};

class MpegVideoExt PictureDecoder : public System::Object
{
public:
	CTOR PictureDecoder(MpegVideoSequenceFormat* sequence, BitStreamEx* file);

	PictureDecoder* m_pRefPic[2];

	list<PictureDecoder*, System::__gc_allocator>::iterator m_pos;

	Picture* m_pic;

	MpegVideoSequenceFormat* m_sequence;
	BitStreamEx* m_file;

	int m_mb_row;
	int m_mb_column;

	int m_macroblock_address;
	int m_previous_macroblock_address;

	unsigned char
			m_intra_dc_precision,
			m_picture_structure,
			m_frame_pred_frame_dct,
			m_q_scale_type,
			m_alternate_scan,
			m_concealment_motion_vectors,
			m_intra_vlc_format,

			m_macroblock_intra,
			m_macroblock_pattern,
			m_macroblock_quant,
			m_macroblock_motion_backward,
			m_macroblock_motion_forward,
			m_spatial_temporal_weight_code_flag,

			m_repeat_first_field,
			m_progressive_frame,
			m_quantiser_scale_code,

			m_frame_motion_type,
			m_field_motion_type;

	/*
	uint8	
			m_intra_dc_precision : 2,
			m_picture_structure : 2,
			m_frame_pred_frame_dct : 1,
			m_q_scale_type : 1,
			m_alternate_scan : 1,
			m_concealment_motion_vectors : 1,
			m_intra_vlc_format : 1,

			m_macroblock_intra : 1,
			m_macroblock_pattern : 1,
			m_macroblock_quant : 1,
			m_macroblock_motion_backward : 1,
			m_macroblock_motion_forward : 1,
			m_spatial_temporal_weight_code_flag : 1,

			m_repeat_first_field : 1,
			m_progressive_frame : 1,
			m_quantiser_scale_code : 5,

			m_frame_motion_type : 2,
			m_field_motion_type : 2;
			*/

	/*
// Am I using these?
	uint8 m_macroblock_motion_forward_prev :1,	// Used by B-picture for skipped macroblocks
			m_macroblock_motion_backward_prev;
*/

	short m_dc_dct_pred[3];	// one for each channel

	bool m_pattern_code[12];	// 1 or 0

	int m_macroblock_type;

	int m_spatial_temporal_weight_class;

	int m_dmv;	// TODO, how many bits
	int m_mv_format;

//	long m_dc_y_past;

	ImageBuffer* m_buffer;
	uint8* m_ybuf;
	uint8* m_crbuf;
	uint8* m_cbbuf;
//	CMacroBlock* m_macroblocksBuffer;

//	uint8 m_intra_quantiser_matrix[64];
//	uint8 m_non_intra_quantiser_matrix[64];

	bool m_full_pel[2];
	uint8 m_f_code[2][2];
	char m_motion_code[2][2][2];
	char m_motion_residual[2][2][2];

	int m_PMV[2][2][2];	// Motion vector predictions (?)

	ErrorCode picture_header();
	void picture_coding_extension();
	void picture_data();
	void slice(int next_code);
	void macroblock();
	void macroblock2(int macroblock_address);

	void ComputeMotionVector(int r, int s, int t, int vector_[2][2][2]);

	void macroblock_modes();
	void motion_vectors(int s);
	void motion_vector(int r, int s);
	int coded_block_pattern();	// return cbp
	void block(int i, short QFS[64]);
	void decode_block(int i, short QFS[64]/*, short f[64]*/);

	void extension_and_user_data(int i);
	void extension_data(int i);
	void quant_matrix_extension();

//	ErrorCode CreateBuffers();
};

}	// Media
}

#endif // __MpegPicture_h_
