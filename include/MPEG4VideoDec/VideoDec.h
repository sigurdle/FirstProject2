#ifndef Mpeg4_VideoDec_h
#define Mpeg4_VideoDec_h

namespace System
{
namespace Mpeg4
{

enum SpriteTransmit
{
	SpriteTransmit_stop = 0,//00
	SpriteTransmit_piece = 1,//01
	SpriteTransmit_update = 2,//10
	SpriteTransmit_pause = 3,//11
};

struct MPEG4VideoDecExt MacroBlock
{
public:

	CTOR MacroBlock();

	int m_intra;

//	int m_pred[6];
	int QF[6][8][8];
	short F[6][8][8];
	int motion_vector[4][2];

	int m_quantiser_scale;	// Qp for this macroblock
};

enum VisualObjectType
{
	VisualObjectType_reserved = 0,//0000 reserved
	VisualObjectType_videoID = 1,//0001 video ID
	VisualObjectType_stillTextureID = 2,//0010 still texture ID
	VisualObjectType_meshID = 3,//0011 mesh ID
	VisualObjectType_FBAID = 4,//0100 FBA ID
	VisualObjectType_3DmeshID = 5,//0101 3D mesh ID
	/*
	01101 reserved
	: :
	: :
	1111 reserved
	*/
};

enum LayerShape
{
	LayerShape_rectangular = 0,//00
	LayerShape_binary = 1,//01
	LayerShape_binary_only = 2,//10
	LayerShape_grayscale = 3,//11
};

enum SpriteEnabled
{
	SpriteEnabled_notused = 0,
	SpriteEnabled_static  = 1,
	SpriteEnabled_GMC = 2,
	SpriteEnabled_reserved = 3,
};

enum Coded
{
	Coded_I = 0,//intra-coded = 0,//00  (I)
	Coded_P = 1,//predictive-coded = 1,//01 (P)
	Coded_B = 2,//10 bidirectionally-predictive-coded (B)
	Coded_S = 3,//11 sprite (S)
};

class MPEG4VideoDecExt MP4VConfig// : public CDecoderSpecificInfo
{
public:

	CTOR MP4VConfig()
	{
		// TODO, set default values before reading, not just here in constructor
		m_visual_object_verid = 1;

		m_short_video_header = 0;
		m_chroma_format = 0;

		m_vop_time_increment_resolution = 0;

		m_newpred_enable = 0;
		m_video_object_layer_shape = 0;
		m_sprite_enable = 0;
		m_reduced_resolution_vop_enable = 0;
		m_complexity_estimation_disable = 0;
		m_interlaced = 0;
		m_scalability = 0;
		m_resync_marker_disable = 0;
		m_data_partitioned = 0;
		m_low_latency_sprite_enable = 0;

		m_quant_type = 0;	// 1=use first method,0=use second mathod
		m_sadct_disable = 0;

		m_bits_per_pixel = 0;
		m_quant_precision = 0;

		m_reversible_vlc = 0;

		m_video_object_layer_width = 0;	// When layershape is rectangular
		m_video_object_layer_height = 0;	// When layershape is rectangular
	}

	int VideoObjectLayer(System::IO::CBitStream32* pBitStream, int start_code);
	void define_vop_complexity_estimation_header(System::IO::CBitStream32* pBitStream);

public:

	uint16 m_video_object_layer_width;	// When layershape is rectangular
	uint16 m_video_object_layer_height;	// When layershape is rectangular

	uint16 m_vop_time_increment_resolution;

	unsigned int m_visual_object_verid : 4;	// VisualObject
	unsigned int m_bits_per_pixel : 4;
	unsigned int m_quant_precision : 4;

	unsigned int m_chroma_format : 2;
	unsigned int m_video_object_layer_shape : 2;
	unsigned int m_sprite_enable : 2;

	unsigned int m_short_video_header : 1;
	unsigned int m_newpred_enable : 1;
	unsigned int m_reduced_resolution_vop_enable : 1;
	unsigned int m_complexity_estimation_disable : 1;
	unsigned int m_interlaced : 1;
	unsigned int m_scalability : 1;
	unsigned int m_resync_marker_disable;
	unsigned int m_data_partitioned : 1;
	unsigned int m_low_latency_sprite_enable : 1;

	unsigned int m_quant_type : 1;	// 1=use first method,0=use second mathod
	unsigned int m_sadct_disable : 1;

	unsigned int m_reversible_vlc : 1;
};

class MPEG4VideoDecExt VideoObjectPlane : public Object
{
public:
	CTOR VideoObjectPlane();
	~VideoObjectPlane();

	inline MacroBlock* GetMacroBlock(int col, int row)
	{
		return m_macroblocks + row*m_mb_cols + col;
	}

	void ReadVideoObjectPlane(System::IO::CBitStream32* pBitStream);

	void video_packet_header(System::IO::CBitStream32* pBitStream);
	void motion_shape_texture(System::IO::CBitStream32* pBitStream);
	void combined_motion_shape_texture(System::IO::CBitStream32* pBitStream);

	void macroblock(System::IO::CBitStream32* pBitStream, int mb_address);
	void interlaced_information(System::IO::CBitStream32* pBitStream, int mb_type, int derived_mb_type, int mcsel);

	void motion_vector(System::IO::CBitStream32* pBitStream, int mode);

	void block(System::IO::CBitStream32* pBitStream, int mb_address, int i, int derived_mb_type, int inter, int pattern_code[6], int QFS[8*8]);
	void decode_block(int mb_address, int i, int ac_pred_flag, int macroblock_intra, int QFS[8*8], short f[8][8]);

	void mc(short pred[8][8], uint8* ref, int component_size, int x, int y, int width, int height, int dx_halfpel, int dy_halfpel);
	int clip_ref(uint8* ref, int component_size, int x, int y);

	uint8* m_ybuf;
	uint8* m_crbuf;
	uint8* m_cbbuf;

	MP4VConfig* m_config;
	VideoObjectPlane* m_pPrevVOP;

//	VideoDec* m_pDecoder;

// Bitstream values

	unsigned int m_vop_coding_type : 2;
	unsigned int m_ref_select_code : 2;
	unsigned int m_sprite_transmit_mode : 4;
	unsigned int m_intra_dc_vlc_thr : 3;
	unsigned int m_vop_reduced_resolution : 1;
//	unsigned int m_vop_quant;	// Don't need to remember this
	unsigned int m_vop_fcode_forward : 3;
	unsigned int m_vop_fcode_backward : 3;

// Member values
//	int m_quantiser_scale;	// Qp for current macroblock?
	MacroBlock* m_macroblocks;
	uint m_mb_cols;
	uint m_mb_rows;

	int m_Qp[2];	// running Qp, one for luminance and one for chrominance?
//	int MVx;
//	int MVy;

	int m_horizontal_mv_data;
	int m_horizontal_mv_residual;
	int m_vertical_mv_data;
	int m_vertical_mv_residual;

	int mb_address;
};

class MPEG4VideoDecExt VideoDec : public Object
{
public:
	CTOR VideoDec();

	ErrorCode Read();

	void VisualObjectSequence(System::IO::CBitStream32* pBitStream, int start_code);
	int VisualObject(System::IO::CBitStream32* pBitStream, int start_code);
	int Group_of_VideoObjectPlane(System::IO::CBitStream32* pBitStream);

public:

	_Ptr<IO::Stream> m_stream;
//	CTrack* m_pTrack;	// Kind of input pin.. ??
	MP4VConfig* m_config;

#if 0
	MP4VSampleDescription* m_pSampleDescription;
#endif

	int32 m_start_code;
};

}	// Mpeg4
}	// System

#endif // Mpeg4_VideoDec_h
