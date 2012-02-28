#ifndef Draw_gl_h
#define Draw_gl_h

/*
struct IDirect3DDevice8;
struct IDirect3DVertexBuffer8;
struct IDirect3DIndexBuffer8;
struct IDirect3DBaseTexture8;
*/

#if _WIN32

#define LIGHTS_MAX		32
#define CLIP_PLANES_MAX	32
#define TEXTURES_MAX		32

#elif AMIGA

#define LIGHTS_MAX		8
#define CLIP_PLANES_MAX	8
#define TEXTURES_MAX		8

#else

#error Unknown OS

#endif

/*
#include "vector2.h"
#include "Vector3.h"
*/
//#include "Matrix4f.h"

//#include "Vector4.h"

#define USE_GL	0

#if USE_GL

#include <gl/gl.h>
#include <gl/glu.h>

#include "c:/opengl/glsdk/gl/glprocs.h"

#pragma comment(lib, "glut32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "opengl32.lib")

#endif

/* AccumOp */
#define GL_ACCUM                          0x0100
#define GL_LOAD                           0x0101
#define GL_RETURN                         0x0102
#define GL_MULT                           0x0103
#define GL_ADD                            0x0104

/* AlphaFunction */
#define GL_NEVER                          0x0200
#define GL_LESS                           0x0201
#define GL_EQUAL                          0x0202
#define GL_LEQUAL                         0x0203
#define GL_GREATER                        0x0204
#define GL_NOTEQUAL                       0x0205
#define GL_GEQUAL                         0x0206
#define GL_ALWAYS                         0x0207

/* AttribMask */
#define GL_CURRENT_BIT                    0x00000001
#define GL_POINT_BIT                      0x00000002
#define GL_LINE_BIT                       0x00000004
#define GL_POLYGON_BIT                    0x00000008
#define GL_POLYGON_STIPPLE_BIT            0x00000010
#define GL_PIXEL_MODE_BIT                 0x00000020
#define GL_LIGHTING_BIT                   0x00000040
#define GL_FOG_BIT                        0x00000080
#define GL_DEPTH_BUFFER_BIT               0x00000100
#define GL_ACCUM_BUFFER_BIT               0x00000200
#define GL_STENCIL_BUFFER_BIT             0x00000400
#define GL_VIEWPORT_BIT                   0x00000800
#define GL_TRANSFORM_BIT                  0x00001000
#define GL_ENABLE_BIT                     0x00002000
#define GL_COLOR_BUFFER_BIT               0x00004000
#define GL_HINT_BIT                       0x00008000
#define GL_EVAL_BIT                       0x00010000
#define GL_LIST_BIT                       0x00020000
#define GL_TEXTURE_BIT                    0x00040000
#define GL_SCISSOR_BIT                    0x00080000
#define GL_ALL_ATTRIB_BITS                0x000fffff

/* BeginMode */
#define GL_POINTS                         0x0000
#define GL_LINES                          0x0001
#define GL_LINE_LOOP                      0x0002
#define GL_LINE_STRIP                     0x0003
#define GL_TRIANGLES                      0x0004
#define GL_TRIANGLE_STRIP                 0x0005
#define GL_TRIANGLE_FAN                   0x0006
#define GL_QUADS                          0x0007
#define GL_QUAD_STRIP                     0x0008
#define GL_POLYGON                        0x0009

/* BlendingFactorDest */
#define GL_ZERO                           0
#define GL_ONE                            1
#define GL_SRC_COLOR                      0x0300
#define GL_ONE_MINUS_SRC_COLOR            0x0301
#define GL_SRC_ALPHA                      0x0302
#define GL_ONE_MINUS_SRC_ALPHA            0x0303
#define GL_DST_ALPHA                      0x0304
#define GL_ONE_MINUS_DST_ALPHA            0x0305

/* BlendingFactorSrc */
/*      GL_ZERO */
/*      GL_ONE */
#define GL_DST_COLOR                      0x0306
#define GL_ONE_MINUS_DST_COLOR            0x0307
#define GL_SRC_ALPHA_SATURATE             0x0308
/*      GL_SRC_ALPHA */
/*      GL_ONE_MINUS_SRC_ALPHA */
/*      GL_DST_ALPHA */
/*      GL_ONE_MINUS_DST_ALPHA */

/* DrawBufferMode */
#define GL_NONE                           0
#define GL_FRONT_LEFT                     0x0400
#define GL_FRONT_RIGHT                    0x0401
#define GL_BACK_LEFT                      0x0402
#define GL_BACK_RIGHT                     0x0403
#define GL_FRONT                          0x0404
#define GL_BACK                           0x0405
#define GL_LEFT                           0x0406
#define GL_RIGHT                          0x0407
#define GL_FRONT_AND_BACK                 0x0408
#define GL_AUX0                           0x0409
#define GL_AUX1                           0x040A
#define GL_AUX2                           0x040B
#define GL_AUX3                           0x040C

/* RenderingMode */
#define GL_RENDER                         0x1C00
#define GL_FEEDBACK                       0x1C01
#define GL_SELECT                         0x1C02

/* MaterialParameter */
#define GL_EMISSION                       0x1600
#define GL_SHININESS                      0x1601
#define GL_AMBIENT_AND_DIFFUSE            0x1602
#define GL_COLOR_INDEXES                  0x1603
/*      GL_AMBIENT */
/*      GL_DIFFUSE */
/*      GL_SPECULAR */

/* MatrixMode */
#define GL_MODELVIEW                      0x1700
#define GL_PROJECTION                     0x1701
#define GL_TEXTURE                        0x1702

/* LightName */
#define GL_LIGHT0                         0x4000
#define GL_LIGHT1                         0x4001
#define GL_LIGHT2                         0x4002
#define GL_LIGHT3                         0x4003
#define GL_LIGHT4                         0x4004
#define GL_LIGHT5                         0x4005
#define GL_LIGHT6                         0x4006
#define GL_LIGHT7                         0x4007

/* LightParameter */
#define GL_AMBIENT                        0x1200
#define GL_DIFFUSE                        0x1201
#define GL_SPECULAR                       0x1202
#define GL_POSITION                       0x1203
#define GL_SPOT_DIRECTION                 0x1204
#define GL_SPOT_EXPONENT                  0x1205
#define GL_SPOT_CUTOFF                    0x1206
#define GL_CONSTANT_ATTENUATION           0x1207
#define GL_LINEAR_ATTENUATION             0x1208
#define GL_QUADRATIC_ATTENUATION          0x1209

/* GetTarget */
#define GL_CURRENT_COLOR                  0x0B00
#define GL_CURRENT_INDEX                  0x0B01
#define GL_CURRENT_NORMAL                 0x0B02
#define GL_CURRENT_TEXTURE_COORDS         0x0B03
#define GL_CURRENT_RASTER_COLOR           0x0B04
#define GL_CURRENT_RASTER_INDEX           0x0B05
#define GL_CURRENT_RASTER_TEXTURE_COORDS  0x0B06
#define GL_CURRENT_RASTER_POSITION        0x0B07
#define GL_CURRENT_RASTER_POSITION_VALID  0x0B08
#define GL_CURRENT_RASTER_DISTANCE        0x0B09
#define GL_POINT_SMOOTH                   0x0B10
#define GL_POINT_SIZE                     0x0B11
#define GL_POINT_SIZE_RANGE               0x0B12
#define GL_POINT_SIZE_GRANULARITY         0x0B13
#define GL_LINE_SMOOTH                    0x0B20
#define GL_LINE_WIDTH                     0x0B21
#define GL_LINE_WIDTH_RANGE               0x0B22
#define GL_LINE_WIDTH_GRANULARITY         0x0B23
#define GL_LINE_STIPPLE                   0x0B24
#define GL_LINE_STIPPLE_PATTERN           0x0B25
#define GL_LINE_STIPPLE_REPEAT            0x0B26
/*      GL_SMOOTH_POINT_SIZE_RANGE */
/*      GL_SMOOTH_POINT_SIZE_GRANULARITY */
/*      GL_SMOOTH_LINE_WIDTH_RANGE */
/*      GL_SMOOTH_LINE_WIDTH_GRANULARITY */
/*      GL_ALIASED_POINT_SIZE_RANGE */
/*      GL_ALIASED_LINE_WIDTH_RANGE */
#define GL_LIST_MODE                      0x0B30
#define GL_MAX_LIST_NESTING               0x0B31
#define GL_LIST_BASE                      0x0B32
#define GL_LIST_INDEX                     0x0B33
#define GL_POLYGON_MODE                   0x0B40
#define GL_POLYGON_SMOOTH                 0x0B41
#define GL_POLYGON_STIPPLE                0x0B42
#define GL_EDGE_FLAG                      0x0B43
#define GL_CULL_FACE                      0x0B44
#define GL_CULL_FACE_MODE                 0x0B45
#define GL_FRONT_FACE                     0x0B46
#define GL_LIGHTING                       0x0B50
#define GL_LIGHT_MODEL_LOCAL_VIEWER       0x0B51
#define GL_LIGHT_MODEL_TWO_SIDE           0x0B52
#define GL_LIGHT_MODEL_AMBIENT            0x0B53
#define GL_SHADE_MODEL                    0x0B54
#define GL_COLOR_MATERIAL_FACE            0x0B55
#define GL_COLOR_MATERIAL_PARAMETER       0x0B56
#define GL_COLOR_MATERIAL                 0x0B57
#define GL_FOG                            0x0B60
#define GL_FOG_INDEX                      0x0B61
#define GL_FOG_DENSITY                    0x0B62
#define GL_FOG_START                      0x0B63
#define GL_FOG_END                        0x0B64
#define GL_FOG_MODE                       0x0B65
#define GL_FOG_COLOR                      0x0B66
#define GL_DEPTH_RANGE                    0x0B70
#define GL_DEPTH_TEST                     0x0B71
#define GL_DEPTH_WRITEMASK                0x0B72
#define GL_DEPTH_CLEAR_VALUE              0x0B73
#define GL_DEPTH_FUNC                     0x0B74
#define GL_ACCUM_CLEAR_VALUE              0x0B80
#define GL_STENCIL_TEST                   0x0B90
#define GL_STENCIL_CLEAR_VALUE            0x0B91
#define GL_STENCIL_FUNC                   0x0B92
#define GL_STENCIL_VALUE_MASK             0x0B93
#define GL_STENCIL_FAIL                   0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL        0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS        0x0B96
#define GL_STENCIL_REF                    0x0B97
#define GL_STENCIL_WRITEMASK              0x0B98
#define GL_MATRIX_MODE                    0x0BA0
#define GL_NORMALIZE                      0x0BA1
#define GL_VIEWPORT                       0x0BA2
#define GL_MODELVIEW_STACK_DEPTH          0x0BA3
#define GL_PROJECTION_STACK_DEPTH         0x0BA4
#define GL_TEXTURE_STACK_DEPTH            0x0BA5
#define GL_MODELVIEW_MATRIX               0x0BA6
#define GL_PROJECTION_MATRIX              0x0BA7
#define GL_TEXTURE_MATRIX                 0x0BA8
#define GL_ATTRIB_STACK_DEPTH             0x0BB0
#define GL_CLIENT_ATTRIB_STACK_DEPTH      0x0BB1
#define GL_ALPHA_TEST                     0x0BC0
#define GL_ALPHA_TEST_FUNC                0x0BC1
#define GL_ALPHA_TEST_REF                 0x0BC2
#define GL_DITHER                         0x0BD0
#define GL_BLEND_DST                      0x0BE0
#define GL_BLEND_SRC                      0x0BE1
#define GL_BLEND                          0x0BE2
#define GL_LOGIC_OP_MODE                  0x0BF0
#define GL_INDEX_LOGIC_OP                 0x0BF1
#define GL_COLOR_LOGIC_OP                 0x0BF2
#define GL_AUX_BUFFERS                    0x0C00
#define GL_DRAW_BUFFER                    0x0C01
#define GL_READ_BUFFER                    0x0C02
#define GL_SCISSOR_BOX                    0x0C10
#define GL_SCISSOR_TEST                   0x0C11
#define GL_INDEX_CLEAR_VALUE              0x0C20
#define GL_INDEX_WRITEMASK                0x0C21
#define GL_COLOR_CLEAR_VALUE              0x0C22
#define GL_COLOR_WRITEMASK                0x0C23
#define GL_INDEX_MODE                     0x0C30
#define GL_RGBA_MODE                      0x0C31
#define GL_DOUBLEBUFFER                   0x0C32
#define GL_STEREO                         0x0C33
#define GL_RENDER_MODE                    0x0C40
#define GL_PERSPECTIVE_CORRECTION_HINT    0x0C50
#define GL_POINT_SMOOTH_HINT              0x0C51
#define GL_LINE_SMOOTH_HINT               0x0C52
#define GL_POLYGON_SMOOTH_HINT            0x0C53
#define GL_FOG_HINT                       0x0C54
#define GL_TEXTURE_GEN_S                  0x0C60
#define GL_TEXTURE_GEN_T                  0x0C61
#define GL_TEXTURE_GEN_R                  0x0C62
#define GL_TEXTURE_GEN_Q                  0x0C63
#define GL_PIXEL_MAP_I_TO_I               0x0C70
#define GL_PIXEL_MAP_S_TO_S               0x0C71
#define GL_PIXEL_MAP_I_TO_R               0x0C72
#define GL_PIXEL_MAP_I_TO_G               0x0C73
#define GL_PIXEL_MAP_I_TO_B               0x0C74
#define GL_PIXEL_MAP_I_TO_A               0x0C75
#define GL_PIXEL_MAP_R_TO_R               0x0C76
#define GL_PIXEL_MAP_G_TO_G               0x0C77
#define GL_PIXEL_MAP_B_TO_B               0x0C78
#define GL_PIXEL_MAP_A_TO_A               0x0C79
#define GL_PIXEL_MAP_I_TO_I_SIZE          0x0CB0
#define GL_PIXEL_MAP_S_TO_S_SIZE          0x0CB1
#define GL_PIXEL_MAP_I_TO_R_SIZE          0x0CB2
#define GL_PIXEL_MAP_I_TO_G_SIZE          0x0CB3
#define GL_PIXEL_MAP_I_TO_B_SIZE          0x0CB4
#define GL_PIXEL_MAP_I_TO_A_SIZE          0x0CB5
#define GL_PIXEL_MAP_R_TO_R_SIZE          0x0CB6
#define GL_PIXEL_MAP_G_TO_G_SIZE          0x0CB7
#define GL_PIXEL_MAP_B_TO_B_SIZE          0x0CB8
#define GL_PIXEL_MAP_A_TO_A_SIZE          0x0CB9
#define GL_UNPACK_SWAP_BYTES              0x0CF0
#define GL_UNPACK_LSB_FIRST               0x0CF1
#define GL_UNPACK_ROW_LENGTH              0x0CF2
#define GL_UNPACK_SKIP_ROWS               0x0CF3
#define GL_UNPACK_SKIP_PIXELS             0x0CF4
#define GL_UNPACK_ALIGNMENT               0x0CF5
#define GL_PACK_SWAP_BYTES                0x0D00
#define GL_PACK_LSB_FIRST                 0x0D01
#define GL_PACK_ROW_LENGTH                0x0D02
#define GL_PACK_SKIP_ROWS                 0x0D03
#define GL_PACK_SKIP_PIXELS               0x0D04
#define GL_PACK_ALIGNMENT                 0x0D05
#define GL_MAP_COLOR                      0x0D10
#define GL_MAP_STENCIL                    0x0D11
#define GL_INDEX_SHIFT                    0x0D12
#define GL_INDEX_OFFSET                   0x0D13
#define GL_RED_SCALE                      0x0D14
#define GL_RED_BIAS                       0x0D15
#define GL_ZOOM_X                         0x0D16
#define GL_ZOOM_Y                         0x0D17
#define GL_GREEN_SCALE                    0x0D18
#define GL_GREEN_BIAS                     0x0D19
#define GL_BLUE_SCALE                     0x0D1A
#define GL_BLUE_BIAS                      0x0D1B
#define GL_ALPHA_SCALE                    0x0D1C
#define GL_ALPHA_BIAS                     0x0D1D
#define GL_DEPTH_SCALE                    0x0D1E
#define GL_DEPTH_BIAS                     0x0D1F
#define GL_MAX_EVAL_ORDER                 0x0D30
#define GL_MAX_LIGHTS                     0x0D31
#define GL_MAX_CLIP_PLANES                0x0D32
#define GL_MAX_TEXTURE_SIZE               0x0D33
#define GL_MAX_PIXEL_MAP_TABLE            0x0D34
#define GL_MAX_ATTRIB_STACK_DEPTH         0x0D35
#define GL_MAX_MODELVIEW_STACK_DEPTH      0x0D36
#define GL_MAX_NAME_STACK_DEPTH           0x0D37
#define GL_MAX_PROJECTION_STACK_DEPTH     0x0D38
#define GL_MAX_TEXTURE_STACK_DEPTH        0x0D39
#define GL_MAX_VIEWPORT_DIMS              0x0D3A
#define GL_MAX_CLIENT_ATTRIB_STACK_DEPTH  0x0D3B
#define GL_SUBPIXEL_BITS                  0x0D50
#define GL_INDEX_BITS                     0x0D51
#define GL_RED_BITS                       0x0D52
#define GL_GREEN_BITS                     0x0D53
#define GL_BLUE_BITS                      0x0D54
#define GL_ALPHA_BITS                     0x0D55
#define GL_DEPTH_BITS                     0x0D56
#define GL_STENCIL_BITS                   0x0D57
#define GL_ACCUM_RED_BITS                 0x0D58
#define GL_ACCUM_GREEN_BITS               0x0D59
#define GL_ACCUM_BLUE_BITS                0x0D5A
#define GL_ACCUM_ALPHA_BITS               0x0D5B
#define GL_NAME_STACK_DEPTH               0x0D70
#define GL_AUTO_NORMAL                    0x0D80
#define GL_MAP1_COLOR_4                   0x0D90
#define GL_MAP1_INDEX                     0x0D91
#define GL_MAP1_NORMAL                    0x0D92
#define GL_MAP1_TEXTURE_COORD_1           0x0D93
#define GL_MAP1_TEXTURE_COORD_2           0x0D94
#define GL_MAP1_TEXTURE_COORD_3           0x0D95
#define GL_MAP1_TEXTURE_COORD_4           0x0D96
#define GL_MAP1_VERTEX_3                  0x0D97
#define GL_MAP1_VERTEX_4                  0x0D98
#define GL_MAP2_COLOR_4                   0x0DB0
#define GL_MAP2_INDEX                     0x0DB1
#define GL_MAP2_NORMAL                    0x0DB2
#define GL_MAP2_TEXTURE_COORD_1           0x0DB3
#define GL_MAP2_TEXTURE_COORD_2           0x0DB4
#define GL_MAP2_TEXTURE_COORD_3           0x0DB5
#define GL_MAP2_TEXTURE_COORD_4           0x0DB6
#define GL_MAP2_VERTEX_3                  0x0DB7
#define GL_MAP2_VERTEX_4                  0x0DB8
#define GL_MAP1_GRID_DOMAIN               0x0DD0
#define GL_MAP1_GRID_SEGMENTS             0x0DD1
#define GL_MAP2_GRID_DOMAIN               0x0DD2
#define GL_MAP2_GRID_SEGMENTS             0x0DD3
#define GL_TEXTURE_1D                     0x0DE0
#define GL_TEXTURE_2D                     0x0DE1
#define GL_FEEDBACK_BUFFER_POINTER        0x0DF0
#define GL_FEEDBACK_BUFFER_SIZE           0x0DF1
#define GL_FEEDBACK_BUFFER_TYPE           0x0DF2
#define GL_SELECTION_BUFFER_POINTER       0x0DF3
#define GL_SELECTION_BUFFER_SIZE          0x0DF4

/* PixelFormat */
#define GL_COLOR_INDEX                    0x1900
#define GL_STENCIL_INDEX                  0x1901
#define GL_DEPTH_COMPONENT                0x1902
#define GL_RED                            0x1903
#define GL_GREEN                          0x1904
#define GL_BLUE                           0x1905
#define GL_ALPHA                          0x1906
#define GL_RGB                            0x1907
#define GL_RGBA                           0x1908
#define GL_LUMINANCE                      0x1909
#define GL_LUMINANCE_ALPHA                0x190A

/* ClipPlaneName */
#define GL_CLIP_PLANE0                    0x3000
#define GL_CLIP_PLANE1                    0x3001
#define GL_CLIP_PLANE2                    0x3002
#define GL_CLIP_PLANE3                    0x3003
#define GL_CLIP_PLANE4                    0x3004
#define GL_CLIP_PLANE5                    0x3005

/* DataType */
#define GL_BYTE                           0x1400
#define GL_UNSIGNED_BYTE                  0x1401
#define GL_SHORT                          0x1402
#define GL_UNSIGNED_SHORT                 0x1403
#define GL_INT                            0x1404
#define GL_UNSIGNED_INT                   0x1405
#define GL_FLOAT                          0x1406
#define GL_2_BYTES                        0x1407
#define GL_3_BYTES                        0x1408
#define GL_4_BYTES                        0x1409
#define GL_DOUBLE                         0x140A

/* TextureCoordName */
#define GL_S                              0x2000
#define GL_T                              0x2001
#define GL_R                              0x2002
#define GL_Q                              0x2003

/* TexCoordPointerType */
/*      GL_SHORT */
/*      GL_INT */
/*      GL_FLOAT */
/*      GL_DOUBLE */

/* TextureEnvMode */
#define GL_MODULATE                       0x2100
#define GL_DECAL                          0x2101
/*      GL_BLEND */
/*      GL_REPLACE */
//#define GL_ADD										0x2102	// TODO

/* TextureEnvParameter */
#define GL_TEXTURE_ENV_MODE               0x2200
#define GL_TEXTURE_ENV_COLOR              0x2201

/* TextureEnvTarget */
#define GL_TEXTURE_ENV                    0x2300

/* TextureGenMode */
#define GL_EYE_LINEAR                     0x2400
#define GL_OBJECT_LINEAR                  0x2401
#define GL_SPHERE_MAP                     0x2402

/* TextureGenParameter */
#define GL_TEXTURE_GEN_MODE               0x2500
#define GL_OBJECT_PLANE                   0x2501
#define GL_EYE_PLANE                      0x2502

/* TextureWrapMode */
#define GL_CLAMP                          0x2900
#define GL_REPEAT                         0x2901

/* TextureMagFilter */
#define GL_NEAREST                        0x2600
#define GL_LINEAR                         0x2601

/* ClientAttribMask */
#define GL_CLIENT_PIXEL_STORE_BIT         0x00000001
#define GL_CLIENT_VERTEX_ARRAY_BIT        0x00000002
#define GL_CLIENT_ALL_ATTRIB_BITS         0xffffffff

/* TextureParameterName */
#define GL_TEXTURE_MAG_FILTER             0x2800
#define GL_TEXTURE_MIN_FILTER             0x2801
#define GL_TEXTURE_WRAP_S                 0x2802
#define GL_TEXTURE_WRAP_T                 0x2803
/*      GL_TEXTURE_BORDER_COLOR */
/*      GL_TEXTURE_PRIORITY */

/* PolygonMode */
#define GL_POINT                          0x1B00
#define GL_LINE                           0x1B01
#define GL_FILL                           0x1B02

/* LogicOp */
#define GL_CLEAR                          0x1500
#define GL_AND                            0x1501
#define GL_AND_REVERSE                    0x1502
#define GL_COPY                           0x1503
#define GL_AND_INVERTED                   0x1504
#define GL_NOOP                           0x1505
#define GL_XOR                            0x1506
#define GL_OR                             0x1507
#define GL_NOR                            0x1508
#define GL_EQUIV                          0x1509
#define GL_INVERT                         0x150A
#define GL_OR_REVERSE                     0x150B
#define GL_COPY_INVERTED                  0x150C
#define GL_OR_INVERTED                    0x150D
#define GL_NAND                           0x150E
#define GL_SET                            0x150F

/* StencilOp */
/*      GL_ZERO */
#define GL_KEEP                           0x1E00
#define GL_REPLACE                        0x1E01
#define GL_INCR                           0x1E02
#define GL_DECR                           0x1E03
/*      GL_INVERT */

/* vertex_array */
#define GL_VERTEX_ARRAY                   0x8074
#define GL_NORMAL_ARRAY                   0x8075
#define GL_COLOR_ARRAY                    0x8076
#define GL_INDEX_ARRAY                    0x8077
#define GL_TEXTURE_COORD_ARRAY            0x8078
#define GL_EDGE_FLAG_ARRAY                0x8079
#define GL_VERTEX_ARRAY_SIZE              0x807A
#define GL_VERTEX_ARRAY_TYPE              0x807B
#define GL_VERTEX_ARRAY_STRIDE            0x807C
#define GL_NORMAL_ARRAY_TYPE              0x807E
#define GL_NORMAL_ARRAY_STRIDE            0x807F
#define GL_COLOR_ARRAY_SIZE               0x8081
#define GL_COLOR_ARRAY_TYPE               0x8082
#define GL_COLOR_ARRAY_STRIDE             0x8083
#define GL_INDEX_ARRAY_TYPE               0x8085
#define GL_INDEX_ARRAY_STRIDE             0x8086
#define GL_TEXTURE_COORD_ARRAY_SIZE       0x8088
#define GL_TEXTURE_COORD_ARRAY_TYPE       0x8089
#define GL_TEXTURE_COORD_ARRAY_STRIDE     0x808A
#define GL_EDGE_FLAG_ARRAY_STRIDE         0x808C
#define GL_VERTEX_ARRAY_POINTER           0x808E
#define GL_NORMAL_ARRAY_POINTER           0x808F
#define GL_COLOR_ARRAY_POINTER            0x8090
#define GL_INDEX_ARRAY_POINTER            0x8091
#define GL_TEXTURE_COORD_ARRAY_POINTER    0x8092
#define GL_EDGE_FLAG_ARRAY_POINTER        0x8093
#define GL_V2F                            0x2A20
#define GL_V3F                            0x2A21
#define GL_C4UB_V2F                       0x2A22
#define GL_C4UB_V3F                       0x2A23
#define GL_C3F_V3F                        0x2A24
#define GL_N3F_V3F                        0x2A25
#define GL_C4F_N3F_V3F                    0x2A26
#define GL_T2F_V3F                        0x2A27
#define GL_T4F_V4F                        0x2A28
#define GL_T2F_C4UB_V3F                   0x2A29
#define GL_T2F_C3F_V3F                    0x2A2A
#define GL_T2F_N3F_V3F                    0x2A2B
#define GL_T2F_C4F_N3F_V3F                0x2A2C
#define GL_T4F_C4F_N3F_V4F                0x2A2D

// ??
#define GL_T2F_T2F_N3F_V3F                0x2A2E
#define GL_T2F										0x2A2F
#define GL_N1_3F_V1_3F							0x2A30

/* FogMode */
/*      GL_LINEAR */
#define GL_EXP                            0x0800
#define GL_EXP2                           0x0801


/* FogParameter */
/*      GL_FOG_COLOR */
/*      GL_FOG_DENSITY */
/*      GL_FOG_END */
/*      GL_FOG_INDEX */
/*      GL_FOG_MODE */
/*      GL_FOG_START */

// Version 1.2
#define GL_UNSIGNED_BYTE_3_3_2            0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4         0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1         0x8034
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_10_10_10_2        0x8036
#define GL_RESCALE_NORMAL                 0x803A
#define GL_TEXTURE_BINDING_3D             0x806A
#define GL_PACK_SKIP_IMAGES               0x806B
#define GL_PACK_IMAGE_HEIGHT              0x806C
#define GL_UNPACK_SKIP_IMAGES             0x806D
#define GL_UNPACK_IMAGE_HEIGHT            0x806E
#define GL_TEXTURE_3D                     0x806F
#define GL_PROXY_TEXTURE_3D               0x8070
#define GL_TEXTURE_DEPTH                  0x8071
#define GL_TEXTURE_WRAP_R                 0x8072
#define GL_MAX_3D_TEXTURE_SIZE            0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV        0x8362
#define GL_UNSIGNED_SHORT_5_6_5           0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV       0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV     0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV     0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV    0x8368
#define GL_BGR                            0x80E0
#define GL_BGRA                           0x80E1
#define GL_MAX_ELEMENTS_VERTICES          0x80E8
#define GL_MAX_ELEMENTS_INDICES           0x80E9
#define GL_CLAMP_TO_EDGE                  0x812F
#define GL_TEXTURE_MIN_LOD                0x813A
#define GL_TEXTURE_MAX_LOD                0x813B
#define GL_TEXTURE_BASE_LEVEL             0x813C
#define GL_TEXTURE_MAX_LEVEL              0x813D
#define GL_LIGHT_MODEL_COLOR_CONTROL      0x81F8
#define GL_SINGLE_COLOR                   0x81F9
#define GL_SEPARATE_SPECULAR_COLOR        0x81FA
#define GL_SMOOTH_POINT_SIZE_RANGE        0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY  0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE        0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY  0x0B23
#define GL_ALIASED_POINT_SIZE_RANGE       0x846D
#define GL_ALIASED_LINE_WIDTH_RANGE       0x846E

// imaging
#define GL_CONSTANT_COLOR                 0x8001
#define GL_ONE_MINUS_CONSTANT_COLOR       0x8002
#define GL_CONSTANT_ALPHA                 0x8003
#define GL_ONE_MINUS_CONSTANT_ALPHA       0x8004
#define GL_BLEND_COLOR                    0x8005
#define GL_FUNC_ADD                       0x8006
#define GL_MIN                            0x8007
#define GL_MAX                            0x8008
#define GL_BLEND_EQUATION                 0x8009
#define GL_FUNC_SUBTRACT                  0x800A
#define GL_FUNC_REVERSE_SUBTRACT          0x800B

// Version 1.3
#define GL_TEXTURE0                       0x84C0
#define GL_TEXTURE1                       0x84C1
#define GL_TEXTURE2                       0x84C2
#define GL_TEXTURE3                       0x84C3
#define GL_TEXTURE4                       0x84C4
#define GL_TEXTURE5                       0x84C5
#define GL_TEXTURE6                       0x84C6
#define GL_TEXTURE7                       0x84C7
#define GL_TEXTURE8                       0x84C8
#define GL_TEXTURE9                       0x84C9
#define GL_TEXTURE10                      0x84CA
#define GL_TEXTURE11                      0x84CB
#define GL_TEXTURE12                      0x84CC
#define GL_TEXTURE13                      0x84CD
#define GL_TEXTURE14                      0x84CE
#define GL_TEXTURE15                      0x84CF
#define GL_TEXTURE16                      0x84D0
#define GL_TEXTURE17                      0x84D1
#define GL_TEXTURE18                      0x84D2
#define GL_TEXTURE19                      0x84D3
#define GL_TEXTURE20                      0x84D4
#define GL_TEXTURE21                      0x84D5
#define GL_TEXTURE22                      0x84D6
#define GL_TEXTURE23                      0x84D7
#define GL_TEXTURE24                      0x84D8
#define GL_TEXTURE25                      0x84D9
#define GL_TEXTURE26                      0x84DA
#define GL_TEXTURE27                      0x84DB
#define GL_TEXTURE28                      0x84DC
#define GL_TEXTURE29                      0x84DD
#define GL_TEXTURE30                      0x84DE
#define GL_TEXTURE31                      0x84DF
#define GL_ACTIVE_TEXTURE                 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE          0x84E1
#define GL_MAX_TEXTURE_UNITS              0x84E2
#define GL_TRANSPOSE_MODELVIEW_MATRIX     0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX    0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX       0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX         0x84E6
#define GL_MULTISAMPLE                    0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE       0x809E
#define GL_SAMPLE_ALPHA_TO_ONE            0x809F
#define GL_SAMPLE_COVERAGE                0x80A0
#define GL_SAMPLE_BUFFERS                 0x80A8
#define GL_SAMPLES                        0x80A9
#define GL_SAMPLE_COVERAGE_VALUE          0x80AA
#define GL_SAMPLE_COVERAGE_INVERT         0x80AB
#define GL_MULTISAMPLE_BIT                0x20000000
#define GL_NORMAL_MAP                     0x8511
#define GL_REFLECTION_MAP                 0x8512
#define GL_TEXTURE_CUBE_MAP               0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP       0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X    0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X    0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y    0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y    0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z    0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z    0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP         0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE      0x851C
#define GL_COMPRESSED_ALPHA               0x84E9
#define GL_COMPRESSED_LUMINANCE           0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA     0x84EB
#define GL_COMPRESSED_INTENSITY           0x84EC
#define GL_COMPRESSED_RGB                 0x84ED
#define GL_COMPRESSED_RGBA                0x84EE
#define GL_TEXTURE_COMPRESSION_HINT       0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE  0x86A0
#define GL_TEXTURE_COMPRESSED             0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS     0x86A3
#define GL_CLAMP_TO_BORDER                0x812D
#define GL_COMBINE                        0x8570
#define GL_COMBINE_RGB                    0x8571
#define GL_COMBINE_ALPHA                  0x8572
#define GL_SOURCE0_RGB                    0x8580
#define GL_SOURCE1_RGB                    0x8581
#define GL_SOURCE2_RGB                    0x8582
#define GL_SOURCE0_ALPHA                  0x8588
#define GL_SOURCE1_ALPHA                  0x8589
#define GL_SOURCE2_ALPHA                  0x858A
#define GL_OPERAND0_RGB                   0x8590
#define GL_OPERAND1_RGB                   0x8591
#define GL_OPERAND2_RGB                   0x8592
#define GL_OPERAND0_ALPHA                 0x8598
#define GL_OPERAND1_ALPHA                 0x8599
#define GL_OPERAND2_ALPHA                 0x859A
#define GL_RGB_SCALE                      0x8573
#define GL_ADD_SIGNED                     0x8574
#define GL_INTERPOLATE                    0x8575
#define GL_SUBTRACT                       0x84E7
#define GL_CONSTANT                       0x8576
#define GL_PRIMARY_COLOR                  0x8577
#define GL_PREVIOUS                       0x8578
#define GL_DOT3_RGB                       0x86AE
#define GL_DOT3_RGBA                      0x86AF

// version 1.4
#define GL_BLEND_DST_RGB                  0x80C8
#define GL_BLEND_SRC_RGB                  0x80C9
#define GL_BLEND_DST_ALPHA                0x80CA
#define GL_BLEND_SRC_ALPHA                0x80CB
#define GL_POINT_SIZE_MIN                 0x8126
#define GL_POINT_SIZE_MAX                 0x8127
#define GL_POINT_FADE_THRESHOLD_SIZE      0x8128
#define GL_POINT_DISTANCE_ATTENUATION     0x8129
#define GL_GENERATE_MIPMAP                0x8191
#define GL_GENERATE_MIPMAP_HINT           0x8192
#define GL_DEPTH_COMPONENT16              0x81A5
#define GL_DEPTH_COMPONENT24              0x81A6
#define GL_DEPTH_COMPONENT32              0x81A7
#define GL_MIRRORED_REPEAT                0x8370
#define GL_FOG_COORDINATE_SOURCE          0x8450
#define GL_FOG_COORDINATE                 0x8451
#define GL_FRAGMENT_DEPTH                 0x8452
#define GL_CURRENT_FOG_COORDINATE         0x8453
#define GL_FOG_COORDINATE_ARRAY_TYPE      0x8454
#define GL_FOG_COORDINATE_ARRAY_STRIDE    0x8455
#define GL_FOG_COORDINATE_ARRAY_POINTER   0x8456
#define GL_FOG_COORDINATE_ARRAY           0x8457
#define GL_COLOR_SUM                      0x8458
#define GL_CURRENT_SECONDARY_COLOR        0x8459
#define GL_SECONDARY_COLOR_ARRAY_SIZE     0x845A
#define GL_SECONDARY_COLOR_ARRAY_TYPE     0x845B
#define GL_SECONDARY_COLOR_ARRAY_STRIDE   0x845C
#define GL_SECONDARY_COLOR_ARRAY_POINTER  0x845D
#define GL_SECONDARY_COLOR_ARRAY          0x845E
#define GL_MAX_TEXTURE_LOD_BIAS           0x84FD
#define GL_TEXTURE_FILTER_CONTROL         0x8500
#define GL_TEXTURE_LOD_BIAS               0x8501
#define GL_INCR_WRAP                      0x8507
#define GL_DECR_WRAP                      0x8508
#define GL_TEXTURE_DEPTH_SIZE             0x884A
#define GL_DEPTH_TEXTURE_MODE             0x884B
#define GL_TEXTURE_COMPARE_MODE           0x884C
#define GL_TEXTURE_COMPARE_FUNC           0x884D
#define GL_COMPARE_R_TO_TEXTURE           0x884E

#define GL_ARRAY_BUFFER							0x8892 
#define GL_ELEMENT_ARRAY_BUFFER				0x8893
#define GL_ARRAY_BUFFER_BINDING				0x8894 
#define GL_ELEMENT_ARRAY_BUFFER_BINDING	0x8895

#define GL_STREAM_DRAW                    0x88E0
#define GL_STREAM_READ                    0x88E1
#define GL_STREAM_COPY                    0x88E2
#define GL_STATIC_DRAW                    0x88E4
#define GL_STATIC_READ                    0x88E5
#define GL_STATIC_COPY                    0x88E6
#define GL_DYNAMIC_DRAW                   0x88E8
#define GL_DYNAMIC_READ                   0x88E9
#define GL_DYNAMIC_COPY                   0x88EA

namespace System
{
namespace LDraw
{

typedef bool GLboolean;
typedef unsigned int GLenum;
typedef int GLint;
typedef unsigned int GLuint;
typedef int GLsizei;
typedef double GLdouble;
typedef float GLfloat;
typedef float GLclampf;	// [0..1]

#define GL_TRUE	1
#define GL_FALSE	0

class GraphicsO_3D;

class Buffers
{
public:
	CTOR Buffers();
	~Buffers();

//	int m_bufferoffset;
//	uint8* m_p;
	vector<uint8*> m_buffers;
};

#if 0
class DrawExt stream_writer
{
public:
	inline CTOR stream_writer()
	{
		m_p = NULL;
		m_pos = 0;
	}

	inline CTOR stream_writer(Buffers* p)
	{
		m_p = p;
		m_pos = 0;
	}

	inline stream_writer& operator << (char value)
	{
		Write(&value, 1);
		return *this;
	}

	inline stream_writer& operator << (unsigned char value)
	{
		Write(&value, 1);
		return *this;
	}

	inline stream_writer& operator << (short value)
	{
		Write(&value, 2);
		return *this;
	}

	inline stream_writer& operator << (unsigned short value)
	{
		Write(&value, 2);
		return *this;
	}

	inline stream_writer& operator << (int value)
	{
		Write(&value, 4);
		return *this;
	}

	inline stream_writer& operator << (unsigned int value)
	{
		Write(&value, 4);
		return *this;
	}

	inline stream_writer& operator << (long value)
	{
		Write(&value, 4);
		return *this;
	}

	inline stream_writer& operator << (unsigned long value)
	{
		Write(&value, 4);
		return *this;
	}

	inline stream_writer& operator << (float value)
	{
		Write(&value, 4);
		return *this;
	}

	inline stream_writer& operator << (double value)
	{
		Write(&value, 8);
		return *this;
	}

	void Write(const void* data, ULONG count);

	Buffers* m_p;
	ULONG m_pos;
};
#endif

class GfxExt TexImage
{
public:
	CTOR TexImage();
	~TexImage();

	uint m_wrap_s;
	uint m_wrap_t;
	uint m_compareFunc;
	uint m_compareMode;
	uint m_depthTextureMode;

	uint m_width;
	uint m_height;
	uint m_widthShift;
	uint m_heightShift;

	uint8* m_data;
	uint32 m_pixelFormat;
//	Bitmap* m_pBitmap;

	IDirect3DBaseTexture9* m_d3dTexture;

//	int* x_table;
//	int* y_table;
};

class TexEnv
{
public:
	int m_envMode;
	int m_combineRGB;
	int m_combineAlpha;

	int m_source_rgb[3];
	int m_source_alpha[3];
	int m_operand_rgb[3];
	int m_operand_alpha[3];

	gm::vector4f m_envColor;
};

class GfxExt MapSpec
{
public:

	CTOR MapSpec();

	virtual ~MapSpec();

	double m_u1;
	double m_u2;
	int m_uorder;

	int m_ncomponents;

	double m_binomial_coefficients[10];
};

class GfxExt MapSpec1 : public MapSpec
{
public:
	CTOR MapSpec1();
	~MapSpec1();

	float* m_values[4];

	vector3f EvalCoordf(GLfloat u);
	vector3f EvalCoordNormalf(GLfloat u);
};

class GfxExt MapSpec2 : public MapSpec
{
public:

	CTOR MapSpec2();
	~MapSpec2();

	double m_binomial_coefficients_v[10];

	double m_v1;
	double m_v2;
	int m_vorder;

	float *(m_values2[4]);

	vector3f EvalCoordf(float u, float v);
	vector3d EvalCoordd(double u, double v);
	vector3f EvalCoordNormalf(float u, float v);
	vector3d EvalCoordNormalf(double u, double v);
};

DrawExt void glOrtho(double m[16], double left, double right, double bottom, double top, double zNear, double zFar);
DrawExt void gluOrtho2D(double m[16], double left, double right, double bottom, double top);

class GfxExt DisplayList : public System::Object
{
public:
	CTOR DisplayList();
	~DisplayList();

	Buffers* m_buffers;
};

class GfxExt ShaderData
{
public:

// inputs
	union
	{
		float gl_Color[4];
		float gl_SecondaryColor[4];
		float gl_TexCoord[1][4];
		float gl_FragCoord[4];

//		float variables[32];
	}
	varying;

	int gl_FrontFacing;	// boolean

// outputs
	float gl_FragColor[4];
	float gl_FragDepth;
};

typedef void (*VERTEX_SHADER_FUNC)();
typedef void (*FRAGMENT_SHADER_FUNC)(ShaderData* data);

class GfxExt Program
{
public:
	inline CTOR Program()
	{
		m_vertex = NULL;
		m_fragment = NULL;
	}

	VERTEX_SHADER_FUNC m_vertex;
	FRAGMENT_SHADER_FUNC m_fragment;
};

class Buffer
{
public:
	unsigned int m_id;
	IDirect3DVertexBuffer9* m_d3dBuffer;
	IDirect3DIndexBuffer9* m_d3dIndexBuffer;
	unsigned int m_size;
//	uint32 m_fvf;
	int m_stride;
};

class __DECLSPEC_ALIGN_16__ GfxExt Light
{
public:
	CTOR Light();

	gm::vector4f m_ambient;
	gm::vector4f m_diffuse;
	gm::vector4f m_specular;
	gm::vector4f m_position;	// m_direction
	float m_constant_attenuation;
	float m_linear_attenuation;
	float m_quadratic_attenuation;
	int m_type;
};

#undef new

class __DECLSPEC_ALIGN_16__ GfxExt GLState : public System::Object
{
public:
	CTOR GLState();

#ifndef __LERSTAD__ // WIN32 && !defined(__LERSTAD__)

	void* operator new (size_t size);
	void* operator new (size_t size, const char* file, int line);
	void operator delete (void* p);

#endif

	bool Equals(const GLState& other) const;

	class EnableState
	{
	public:
#if LIGHTS_MAX <= 8
		uint8 m_lightEnabledFlag;
#elif LIGHTS_MAX <= 16
		uint16 m_lightEnabledFlag;
#else
		uint32 m_lightEnabledFlag;
#endif

#if CLIP_PLANES_MAX <= 8
		uint8 m_clipEnabledFlag;
#elif CLIP_PLANES_MAX <= 16
		uint16 m_clipEnabledFlag;
#else
		uint32 m_clipEnabledFlag;
#endif

#if TEXTURES_MAX <= 8
		uint8 m_texEnabledFlag;
		uint8 m_texture_gen_s;
		uint8 m_texture_gen_t;
		uint8 m_texture_gen_r;
		uint8 m_texture_gen_q;
#elif TEXTURES_MAX <= 16
		uint16 m_texEnabledFlag;
		uint16 m_texture_gen_s;
		uint16 m_texture_gen_t;
		uint16 m_texture_gen_r;
		uint16 m_texture_gen_q;
#else
		uint32 m_texEnabledFlag;
		uint32 m_texture_gen_s;
		uint32 m_texture_gen_t;
		uint32 m_texture_gen_r;
		uint32 m_texture_gen_q;
#endif
		uint8 m_activeTexturesCount;
		uint8 m_activeTextureIndex[TEXTURES_MAX];
		uint8 m_activeLightsCount;
		uint8 m_activeLightIndex[LIGHTS_MAX];

		union
		{
			uint32 m_flags;
			struct
			{
				bool m_map1_vertex_3 : 1;
				bool m_map2_vertex_3 : 1;
				bool m_map2_texture_coord_2 : 1;
				bool m_lighting : 1;
				bool m_color_material : 1;
				bool m_line_stipple : 1;
				bool m_polygon_stipple : 1;
				bool m_alpha_test : 1;
				bool m_stencil_test : 1;
				bool m_depth_test : 1;
				bool m_cull_face : 1;
				bool m_normalize : 1;
				bool m_rescale_normal : 1;
				bool m_blend : 1;
				bool m_fog : 1;
			}
			s;
		}
		u;
	};

	class ModelViewMatrix
	{
	public:
		inline CTOR ModelViewMatrix()
		{
			bInverseValid = false;
		}

		inline void EnsureInverse();

		matrix4f Matrix;
		matrix4f MatrixInverse;
		matrix3f MatrixInverse3;
		bool bInverseValid;
	};

	void Enable(uint cap);
	void Disable(uint cap);

	void GetFloatv(GLenum pname, GLfloat* params);
	void GetLightfv(GLenum light, GLenum pname, GLfloat *params);

	void GenBuffers(unsigned int n, unsigned int* buffers);
//	void BindBuffer(GLenum target, unsigned int buffer);

	void GenTextures(unsigned int n, unsigned int *textures);

	void BindTexture(GLenum target, unsigned int texture);
	void TexImage2D(GLenum target, Bitmap* pBitmap);
	void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);

	vector<Buffer*> m_buffers;

	vector<IDirect3DVertexDeclaration9*> m_vertexDeclarations;

//	uint m_vertexDeclarationBinding;	// TODO remove
	VertexDeclarationGL* m_vertexDeclaration;

	uint m_activeTexture;

	vector<TexImage*> m_texImage;
	uint m_texBinding[TEXTURES_MAX][2];

	TexEnv m_texEnv[TEXTURES_MAX];
	/*
	int m_envMode[TEXTURES_MAX];
	int m_combineRGB[TEXTURES_MAX];
	int m_combineAlpha[TEXTURES_MAX];

	int m_source_rgb[TEXTURES_MAX][3];
	int m_operand_rgb[TEXTURES_MAX][3];
	*/

	Light m_light[LIGHTS_MAX];

	vector<uint> m_nameStack;

	__DECLSPEC_ALIGN_16__ ModelViewMatrix m_modelview;
	__DECLSPEC_ALIGN_16__ matrix4f m_projectionMatrix;
	__DECLSPEC_ALIGN_16__ matrix4f m_textureMatrix[TEXTURES_MAX];

	inline void LoadMatrix(uint matrixMode, const matrix4f& matrix);
	inline void MultMatrix(uint matrixMode, const matrix4f& matrix);

	double m_clearDepth;
	vector4f m_clearColor;

	EnableState m_enable;
	stack<EnableState> m_enableMaskStack;

	stack<ModelViewMatrix> m_modelviewMatrixStack;
	stack<matrix4f> m_projectionMatrixStack;
	stack<matrix4f> m_textureMatrixStack[TEXTURES_MAX];	// One stack for each texture matrix

	MapSpec1 m_map1[9];
	MapSpec2 m_map2[9];

	uint m_nprograms;
	map<uint,Program*> m_programs;

	map<int,DisplayList*> m_displayList;

protected:

	~GLState();
};

#define new _new

#if 0
class DrawExt GLState	// Server State
{
public:
	GLState();
	GLState(const GLState & other);
	GLState(_GLState * p);
	~GLState();

	GLState & operator = (const GLState& other);

	bool Equals(const GLState& other) const;

	inline bool operator == (const GLState& other) const
	{
		return Equals(other);
	}

	inline bool operator != (const GLState& other) const
	{
		return !Equals(other);
	}

	void GetFloatv(GLenum pname, GLfloat* params);
	void GetLightfv(GLenum light, GLenum pname, GLfloat* params);

	_GLState* m_p;

	void GenTextures(int n, unsigned int* textures);

	uint CreateShader(int type);
	uint CreateProgram();
	void AttachShader(uint program, uint shader);

	Program* GetProgram(uint program);

//	void SetProgramFunc(uint program, FRAGMENT_SHADERFUNC func);

	/*
	virtual void glNewList(int n);
	virtual void glEndList();
	virtual void glCallList(int n);
	*/
};
#endif

class DrawExt ClientArray
{
public:

	inline CTOR ClientArray();
	inline CTOR ClientArray(int size, int type, int stride, const void* pointer);

	GLint m_size;
	GLenum m_type;
	GLsizei m_stride;
	const void *m_pointer;
	uint m_buffer;

	inline uint8* GetStartData(int index) const
	{
		switch (m_type)
		{
		case GL_FLOAT:
			return (uint8*)m_pointer + index * (m_size*4 + m_stride);

		case GL_DOUBLE:
			return (uint8*)m_pointer + index * (m_size*8 + m_stride);

		default:
			ASSERT(0);
			return NULL;
		}
	}

	class Element
	{
	public:
		inline CTOR Element(int type, int size, const uint8* data)
		{
			m_type = type;
			m_size = size;
			m_data = data;
		}

		int m_type;
		int m_size;
		const uint8* m_data;

		operator vector3f () const;
		operator vector4f () const;
	};

	Element GetElement(int index) const;
};

/*
__DECLSPEC_ALIGN_16__ class _ClientState : public System::Object
{
public:
};
*/

class DrawExt ClientState : public System::Object
{
public:
	CTOR ClientState();
	~ClientState();

//	_ClientState * m_p;

	void BindBuffer(GLenum target, unsigned int buffer);

	void EnableClientState(GLenum _array);
	void DisableClientState(GLenum _array);

	void InterleavedArrays(GLenum format, uint stride, const void* pointer);
	void VertexPointer(int index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	void NormalPointer(int index, GLenum type, GLsizei stride, const void* pointer);
	void TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
	void ColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
	void EdgeFlagPointer(GLsizei stride, const GLboolean* pointer);

	uint m_array_buffer_binding;
	uint m_element_array_buffer_binding;
	uint m_activeTexture;

	class ArrayState
	{
	public:
		ClientArray m_vertexArray[2];
		ClientArray m_normalArray[2];
		ClientArray m_colorArray;
		ClientArray m_edgeflagArray;
		ClientArray m_texcoordArray[TEXTURES_MAX];

		uint32 m_TexcoordArrayEnabledMask;
		bool m_bVertexArrayEnabled[2];
		bool m_bNormalArrayEnabled[2];
		bool m_bColorArrayEnabled : 1;
		bool m_bEdgeflagArrayEnabled : 1;
	};

	ArrayState m_arrays;

	stack<uint8> m_attribMaskStack;
	stack<ArrayState> m_arrayStateStack;
};

struct __DECLSPEC_ALIGN_16__ DrawExt Vertex
{
public:
	vector3f p;
	float w;

//	vector4f win;

	vector4f texcoord[TEXTURES_MAX];
	/*
	vector4f ambient;
	vector4f emission;
	vector4f diffuse;
	vector4f specular;
	*/
	vector4f color;
	vector4f secondarycolor;
	vector3f normal;
	vector2f m_winxy;
	float m_winz;
//	float m_shininess;
	float m_fog_f;
	float w_inv;
//	bool lightingEnabled;
	uint m_viewclipmask;
};

class DrawExt Software3D_I : public GraphicsI
{
public:

	CTOR Software3D_I(GLState* state);
	CTOR Software3D_I(GLState* state, _Graphics* p);
//	CTOR GraphicsO_3D(GLState* state, IDirect3DDevice9* d3dDevice);

	_Graphics* m_p;	// bitmap/depth/stencil etc.

	GLState* m_state;

	/*
#if WIN32
	void* operator new (size_t size);
	void operator delete (void* p);
#endif
	*/

	/*
	enum
	{
		Wrap_repeat,
		Wrap_clamp,
	};
	*/

	void SelectBuffer(GLsizei size, GLuint* buffer);

	void ReleaseGraphics();

	void Init();

	void CallList(DisplayList* displaylist);

	void InitNames();
	void LoadName(GLuint name);
	void PushName(GLuint name);
	void PopName();

	void MatrixMode(GLenum mode);
	void PushMatrix();
	void PopMatrix();

	void Enable(GLenum cap);
	void Disable(GLenum cap);

	void Lightf(GLenum light, GLenum pname, float param);
	void Lightfv(GLenum light, GLenum pname, const float *params);
	void GetLightfv(GLenum light, GLenum pname, GLfloat *params);

	void ClipPlane(GLenum plane, const double *equation);

	void LightModeli(GLenum pname, int param);
	void LightModelfv(GLenum pname, const float *params);

//	void glViewport(int x, int y, int width, int height);
	void Viewport(int x, int y, int width, int height);
//	void VertexPointer(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer);

//	void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);

	template<class T>	void DrawElements(GLenum mode, GLsizei count, const T* indices, const ClientArray vertexArray[], const ClientArray normalArray[], uint32 texEnabledMask, const ClientArray texcoordArray[]);

	Texture CreateTexture(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
	Texture CreateTexture(Bitmap* pBitmap);
	void SetTexture(int stage, Texture texture);

	void LoadIdentity();
	void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
	void Perspective(double fovy, double aspect, double zNear, double zFar);
	void LoadMatrixf(const float m[16]);
	void LoadMatrixd(const double m[16]);
	void MultMatrixf(const float m[16]);
	void MultMatrixd(const double m[16]);
	void LoadTransposeMatrixf(const float m[16]);
	void LoadTransposeMatrixd(const double m[16]);
	void MultTransposeMatrixf(const float m[16]);
	void MultTransposeMatrixd(const double m[16]);
	void Translatef(float x, float y, float z);
	void Translated(double x, double y, double z);
//	void glTranslate(const vector3f& v);
//	void glTranslate(const vector3d& v);
	void Scalef(float x, float y, float z);
	void Scaled(double x, double y, double z);
	void Rotatef(float angle, float x, float y, float z);
	void Rotated(double angle, double x, double y, double z);

	void Map1f(int target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points);
	void Map2f(int target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points);

	void EvalCoordf(GLfloat u);
	void EvalCoordf(GLfloat u, GLfloat v);

	void ClearColor(float r, float g, float b, float a);
	void ClearDepth(double depth);

	void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void DepthMask(GLboolean mask);

	void AlphaFunc(GLenum func, GLclampf ref);
	void StencilFunc(GLenum func, GLint ref, GLuint mask);
	void StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	void DepthFunc(GLenum func);
	void BlendEquation(GLenum mode);
	void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	void BlendFunc(GLenum src, GLenum dst);
	void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void LogicOp(GLenum opcode);
	void Fogi(GLenum pname, int param);
	void Fogf(GLenum pname, float param);
	void Fogfv(GLenum pname, const float *params);
	void Clear(uint32 mask);
	void CullFace(GLenum mode);

	void Materialf(GLenum face, GLenum pname, float param);
	void Materialfv(GLenum face, GLenum pname, const float *params);

	void Begin(int mode);
	void End();
	void TexCoordf(float s);
	void TexCoordf(float s, float t);
	void TexCoordf(float s, float t, float r);
	void MultiTexCoordf(GLenum texture, float s);
	void MultiTexCoordf(GLenum texture, float s, float t);
	void MultiTexCoordf(GLenum texture, float s, float t, float r);
	void Normalf(float x, float y, float z);
	void Normald(double x, double y, double z);
	void Vertexf(float x, float y);
	void Vertexf(float x, float y, float z);
	void Vertexf(float x, float y, float z, float w);
	void Vertexd(double x, double y);
	void Vertexd(double x, double y, double z);
	void Vertexd(double x, double y, double z, double w);
	void Colorf(float r, float g, float b);
	void Colorf(float r, float g, float b, float a);
	void SecondaryColorf(float r, float g, float b);
	void ColorMaterial(GLenum face, GLenum mode);
	void PolygonMode(GLenum face, GLenum mode);
	void EdgeFlag(GLboolean flag);
	void LineStipple(int factor, uint16 pattern);
	void PolygonStipple(const uint8 *mask);
	void PointSize(GLfloat size);
	void Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void FillRectangle(const Brush* pBrush, float x, float y, float width, float height);
	void GetBooleanv(GLenum pname, GLboolean *params);
//	void glGetFloatv(GLenum pname, GLfloat* params);
	void UseProgram(uint program);
	void PushAttrib(uint32 mask);
	void PopAttrib();
	void TexEnvf(int target, int pname, GLfloat param);
	void TexEnvi(int target, int pname, GLint param);
	void TexEnvfv(int target, int pname, const GLfloat *params);
	void TexParameteri(GLenum target, GLenum pname, GLint param);
//	void TexImage2D(int target, Bitmap* pBitmap);
//	void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
	void TexGeni(GLenum coord, GLenum pname, GLint param);
	void TexGenfv(GLenum coord, GLenum pname, const GLfloat *params);

//	void GenTextures(unsigned int n, unsigned int *textures);
//	void DeleteTextures(unsigned int n, const unsigned int * textures);

	//void BindTexture(GLenum target, unsigned int texture);

	LDraw::GraphicsO* m_pGraphics;

	uint16 m_linepattern;
	uint16 m_linepatternfactor;
	int m_line_s;

	uint8 m_colorMask;
	bool m_depthMask;

	int m_depthFunc;

	int m_stencilFunc_func[2];
	int m_stencilFunc_ref[2];
	GLuint m_stencilFunc_mask[2];

	int m_stencilOp_fail[2];
	int m_stencilOp_zfail[2];
	int m_stencilOp_zpass[2];

	uint16 m_blendEquationRGB;
	uint16 m_blendEquationAlpha;

	uint16 m_blendFuncSrcRGB;
	uint16 m_blendFuncSrcAlpha;
	uint16 m_blendFuncDstRGB;
	uint16 m_blendFuncDstAlpha;

	float m_pointSize;

	int m_fogMode;
	float m_fogDensity;
	float m_fogStart;
	float m_fogEnd;
	vector4f m_fogColor;

	uint m_texGenMode[TEXTURES_MAX][4];
	vector4f m_object_plane[TEXTURES_MAX][4];
	vector4f m_eye_plane[TEXTURES_MAX][4];

	uint m_renderMode;

	uint m_selectBufferSize;
	uint* m_selectBuffer;
	uint* m_pselect;
	int m_nhits;
	float m_minz;
	float m_maxz;
	bool m_bHitSinceLast;

	void HitRecord();

	void processVertex(const vector4f& obj, const vector3f& normal, const vector4f texcoord[], Vertex& v);
	void processVertex(Vertex& v);

//protected:

#if !USE_GL

	//void UpdateModelViewMatrixInverse();

	void Vertexf(const vector4f& obj, const vector3f& normal, const vector4f texcoord[8]);

	void Prep();
	void UnPrep();

//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector4f color);
//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector4f color[3]);
//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector2f texcoord[3], const double q[3], const Bitmap* pTextureBitmap, uint32 flags);
//	void FillTriangle(const vector2f winxy[3], const float winz[3], const vector4f color[3], const vector4f* texcoord[3], const float q[3], const float fog_f[3], uint32 flags);
	void FillTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector4f color[3], const vector4f secondarycolor[3], const vector4f texcoord[3], const TexImage* pTexture, Program* pProgram, uint32 flags);

	void point(const Vertex& v);

	void line(const Vertex& v0, const Vertex& v1);
	void line2(const Vertex& v0, const Vertex& v1);
	void line3(const Vertex& v0, const Vertex& v1);

	void triangle3(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void triangle2(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

	void quad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3);

	class CurrentState
	{
	public:
		vector4f m_color;
		vector4f m_secondarycolor;
		vector4f m_texcoord[TEXTURES_MAX];
		vector3f m_normal;
	};

protected:

	double m_viewport[4];

	uint m_polygonMode[2];

	uint m_program;	// Active shader program

//	bool m_matrixModelView3iValid;

	vector4f m_colortranslate;	// extension ?

	int m_colorMaterialFace;
	int m_colorMaterialMode;

	vector4f m_ambient;
	vector4f m_diffuse;
	vector4f m_specular;
	vector4f m_emission;
	float m_shininess;

	uint m_matrixMode;

	/*
	vector4f m_color;
	vector4f m_secondarycolor;
	vector4f m_texcoord;
	vector3f m_normal;
	*/

	int m_beginMode;
	int m_nvertex;
	vector<Vertex> m_vertices;
//	float m_clearDepth;

	stack<uint32> m_attribMaskStack;

	class LineState
	{
	public:
		CTOR LineState(bool line_stipple, uint16 linepattern, uint16 linepatternfactor)
		{
			m_line_stipple = line_stipple;
			m_linepattern = linepattern;
			m_linepatternfactor = linepatternfactor;
		}

		uint16 m_linepattern;
		uint16 m_linepatternfactor;
		bool m_line_stipple : 1;
	};

	class PolygonStippleData
	{
	public:
		uint32 m_data[32];
	};

public:

	int m_alphaFunc;

	float m_alphaRef;

	int m_logicOp;
	int m_cullFaceMode;
	PolygonStippleData m_polygonStipple;

//	IDirect3DDevice9* m_d3dDevice;

protected:

	CurrentState m_current;

	stack<CurrentState> m_currentStateStack;
	stack<PolygonStippleData> m_polygonStippleStack;
	stack<LineState> m_lineStateStack;

	bool m_edgeFlag : 1;

	vector4f m_clipplane[32];

	vector4f m_ambientLightModel;

#endif

	BitmapData m_bitmapData;
	__DECLSPEC_ALIGN_16__ matrix3f m_transform2d;
};

#if 0
class DrawExt Graphics3D : public GraphicsBase
{
public:

	GLState* m_state;

	virtual IDirect3DDevice9* GetDirect3DDevice9() = 0;
	virtual ID3D10Device* GetD3D10Device() = 0;

	virtual void SetVertexBlend(int b) = 0;
	virtual void SetTweenFactor(float tweenFactor) = 0;

	virtual void CallList(DisplayList* displaylist) = 0;
	virtual void MatrixMode(GLenum mode) = 0;
	virtual void PushMatrix() = 0;
	virtual void PopMatrix() = 0;
	virtual void Enable(GLenum cap) = 0;
	virtual void Disable(GLenum cap) = 0;
	virtual void Lightf(GLenum light, GLenum pname, float param) = 0;
	virtual void Lightfv(GLenum light, GLenum pname, const float* params) = 0;
	virtual void GetLightfv(GLenum light, GLenum pname, GLfloat* params) = 0;
	virtual void ClipPlane(GLenum plane, const double* equation) = 0;
	virtual void GetClipPlane(GLenum plane, double* equation) = 0;
	virtual void LightModeli(GLenum pname, int param) = 0;
	virtual void LightModelfv(GLenum pname, const float* params) = 0;
	virtual void Viewport(double x, double y, double width, double height) = 0;
	virtual void EnableClientState(GLenum _array) = 0;
	virtual void DisableClientState(GLenum _array) = 0;
	virtual void PushClientAttrib(uint32 mask) = 0;
	virtual void PopClientAttrib() = 0;
	virtual void InterleavedArrays(GLenum format, uint stride, const void* pointer) = 0;
	virtual void InterleavedData(GLenum format, int stride, const void* pointer, int size) = 0;
	virtual void VertexPointer(int index, GLint size, GLenum type, GLsizei stride, const void* pointer) = 0;
	virtual void NormalPointer(int index, GLenum type, GLsizei stride, const void *pointer) = 0;
	virtual void TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) = 0;
	virtual void ColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer) = 0;
	virtual void EdgeFlagPointer(GLsizei stride, const GLboolean* pointer) = 0;
	virtual void DrawArrays(GLenum mode, GLsizei first, GLsizei count) = 0;
//	virtual void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices) = 0;
	virtual void DrawIndexed(GLenum mode, GLsizei start, GLsizei end, GLsizei count, GLenum type, int startIndex) = 0;
	virtual void LoadIdentity() = 0;
	virtual void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) = 0;
	virtual void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar) = 0;
	virtual void Ortho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) = 0;
	virtual void Perspective(double fovy, double aspect, double zNear, double zFar) = 0;
	virtual void LoadMatrixf(const float m[16]) = 0;
	virtual void LoadMatrixd(const double m[16]) = 0;
	virtual void MultMatrixf(const float m[16]) = 0;
	virtual void MultMatrixd(const double m[16]) = 0;
	virtual void LoadTransposeMatrixf(const float m[16]) = 0;
	virtual void LoadTransposeMatrixd(const double m[16]) = 0;
	virtual void MultTransposeMatrixf(const float m[16]) = 0;
	virtual void MultTransposeMatrixd(const double m[16]) = 0;
	virtual void glTranslatef(float x, float y, float z) = 0;
	virtual void glTranslated(double x, double y, double z) = 0;
	virtual void glScalef(float x, float y, float z) = 0;
	virtual void glScaled(double x, double y, double z) = 0;
	virtual void glRotatef(float angle, float x, float y, float z) = 0;
	virtual void glRotated(double angle, double x, double y, double z) = 0;
	virtual void glMap1f(int target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat* points);
	virtual void glMap2f(int target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat* points);
	virtual void glEvalCoordf(GLfloat u) = 0;
	virtual void glEvalCoordf(GLfloat u, GLfloat v) = 0;
	virtual void ClearColor(float r, float g, float b, float a) = 0;
	virtual void ClearDepth(double depth) = 0;
	virtual void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) = 0;
	virtual void DepthMask(GLboolean mask) = 0;
	virtual void CullFace(GLenum mode) = 0;
	virtual void DepthFunc(GLenum func) = 0;
	virtual void AlphaFunc(GLenum func, GLclampf ref) = 0;
	virtual void StencilFunc(GLenum func, GLint ref, GLuint mask) = 0;
	virtual void StencilOp(GLenum fail, GLenum zfail, GLenum zpass) = 0;
	virtual void BlendEquation(GLenum mode) = 0;
	virtual void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) = 0;
	virtual void BlendFunc(GLenum src, GLenum dst) = 0;
	virtual void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) = 0;
	virtual void LogicOp(GLenum opcode) = 0;
	virtual void Clear(uint32 mask) = 0;
	virtual void Materialf(GLenum face, GLenum pname, float param) = 0;
	virtual void Materialfv(GLenum face, GLenum pname, const float *params) = 0;
	virtual void glBegin(int mode) = 0;
	virtual void glEnd() = 0;
	virtual void glTexCoordf(float s) = 0;
	virtual void glTexCoordf(float s, float t) = 0;
	virtual void glTexCoordf(float s, float t, float r) = 0;
	virtual void glMultiTexCoordf(GLenum texture, float s) = 0;
	virtual void glMultiTexCoordf(GLenum texture, float s, float t) = 0;
	virtual void glMultiTexCoordf(GLenum texture, float s, float t, float r) = 0;
	virtual void glNormalf(float x, float y, float z) = 0;
	virtual void glNormald(double x, double y, double z) = 0;
	virtual void glVertexf(float x, float y) = 0;
	virtual void glVertexf(float x, float y, float z) = 0;
	virtual void glVertexf(float x, float y, float z, float w) = 0;
	virtual void glVertexd(double x, double y) = 0;
	virtual void glVertexd(double x, double y, double z) = 0;
	virtual void glVertexd(double x, double y, double z, double w) = 0;
	virtual void glColorf(float r, float g, float b) = 0;
	virtual void glColorf(float r, float g, float b, float a) = 0;
	virtual void glSecondaryColorf(float r, float g, float b) = 0;
	virtual void ColorMaterial(GLenum face, GLenum mode) = 0;
	virtual void PushAttrib(uint32 mask) = 0;
	virtual void PopAttrib() = 0;
	virtual void ActiveTexture(GLenum pname) = 0;
	virtual void ClientActiveTexture(GLenum pname) = 0;
	virtual void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void* pixels) = 0;
//	virtual void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels) = 0;

	virtual Texture CreateTexture(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels) = 0;
	virtual Texture CreateTexture(Bitmap* pBitmap) = 0;

	virtual void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *data) = 0;
//	virtual void TexImage2D(GLenum target, Bitmap* pBitmap) = 0;
	virtual void TexEnvf(GLenum target, GLenum pname, GLfloat param) = 0;
	virtual void TexEnvi(GLenum target, GLenum pname, GLint param) = 0;
	virtual void TexEnvfv(GLenum target, GLenum pname, const GLfloat *params) = 0;
	virtual void TexParameteri(GLenum target, GLenum pname, GLint param) = 0;
	virtual void TexGeni(GLenum coord, GLenum pname, GLint param) = 0;
	virtual void TexGenfv(GLenum coord, GLenum pname, const GLfloat *params) = 0;
//	virtual void GenBuffers(unsigned int n, unsigned int* buffers) = 0;
//	virtual void BindBuffer(GLenum target, unsigned int buffer) = 0;
//	virtual void BufferData(GLenum target, unsigned int size, const void* data, uint usage) = 0;

	virtual IndexBuffer CreateIndexBuffer(int type, unsigned int size, const void* data) = 0;

	virtual VertexBuffer CreateVertexBuffer(unsigned int size, const void* data) = 0;
	virtual void DeleteVertexBuffer(VertexBuffer vertexBuffer) = 0;

	virtual VertexDeclaration CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count) = 0;
	virtual void SetVertexDeclaration(VertexDeclaration vertexDecl) = 0;
	virtual void DeleteVertexDeclaration(VertexDeclaration vertexDecl) = 0;

	virtual IndexBuffer GetIndices() = 0;
	virtual void SetIndices(IndexBuffer indexBuffer) = 0;

	virtual void SetStreamSource(int stream, VertexBuffer vertexBuffer, int byteOffset, int stride) = 0;

//	virtual void GenTextures(int n, unsigned int *textures) = 0;
//	virtual void DeleteTextures(int n, const unsigned int * textures) = 0;
	//virtual void BindTexture(GLenum target, unsigned int texture) = 0;

	virtual void SetTexture(int stage, Texture texture) = 0;

	virtual void GetFloatv(GLenum pname, GLfloat* params) = 0;
	virtual void UseProgram(uint program) = 0;
	virtual void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) = 0;
	virtual void FillRectangle(Brush* pBrush, float x, float y, float width, float height) = 0;
	virtual void PolygonMode(GLenum face, GLenum mode) = 0;
	virtual void EdgeFlag(GLboolean flag) = 0;
	virtual void LineStipple(int factor, uint16 pattern) = 0;
	virtual void PolygonStipple(const uint8 *mask) = 0;
	virtual void PointSize(GLfloat size) = 0;
	virtual void Fogi(GLenum pname, int param) = 0;
	virtual void Fogf(GLenum pname, float param) = 0;
	virtual void Fogfv(GLenum pname, const float *params) = 0;
	virtual void InitNames() = 0;
	virtual void LoadName(GLuint name) = 0;
	virtual void PushName(GLuint name) = 0;
	virtual void PopName() = 0;
	virtual void SelectBuffer(GLsizei size, GLuint* buffer) = 0;
	virtual int RenderMode(GLenum mode) = 0;
	virtual void Flush() = 0;

	inline void glVertex(const vector3f& v)
	{
		glVertexf(v[0], v[1], v[2]);
	}

	inline void glVertex(const vector3d& v)
	{
		glVertexd(v[0], v[1], v[2]);
	}

	inline void glVertex(const vector2f& v)
	{
		glVertexf(v[0], v[1], 0);
	}

	inline void glNormal(const vector3f& v)
	{
		glNormalf(v[0], v[1], v[2]);
	}

	inline void glColor(const vector4f& v)
	{
		glColorf(v[0], v[1], v[2], v[3]);
	}

	inline void glTranslate(const vector3f& v)
	{
		glTranslatef(v[0], v[1], v[2]);
	}

	inline void glTranslate(const vector3d& v)
	{
		glTranslated(v[0], v[1], v[2]);
	}

	inline void glRotate(float angle, const vector3f& v)
	{
		glRotatef(angle, v[0], v[1], v[2]);
	}

	inline void glRotate(double angle, const vector3d& v)
	{
		glRotated(angle, v[0], v[1], v[2]);
	}

	inline void glScale(const vector3f& v)
	{
		glScalef(v[0], v[1], v[2]);
	}

	inline void glScale(const vector3d& v)
	{
		glScaled(v[0], v[1], v[2]);
	}
};
#endif

class TextureManager
{
public:
	CTOR TextureManager();

	void AddTexture(uint8* data, int width, int height);

	class Texture
	{
	public:
		uint8* m_data;
		int m_width;
		int m_height;
	};

	vector<Texture*> m_textures;

	int m_width;
	int m_height;

	void Build();
};

#if 0
class DrawExt Graphics3DList : public Graphics3D
{
public:
	CTOR Graphics3DList(GLState* state, ClientState* clientState, DisplayList* displaylist);

	ClientState* m_clientState;
	DisplayList* m_list;

	virtual int GetMode() const;
	virtual IDirect3DDevice9* GetDirect3DDevice9();
	virtual ID3D10Device* GetD3D10Device();

	void CallList(DisplayList* displaylist);

	void glBegin(int mode);
	void glEnd();
	void glVertexf(float x, float y);
	void glVertexf(float x, float y, float z);
	void glVertexf(float x, float y, float z, float w);
	void glVertexd(double x, double y);
	void glVertexd(double x, double y, double z);
	void glVertexd(double x, double y, double z, double w);
	void PushMatrix();
	void PopMatrix();
	void glColorf(float r, float g, float b);
	void glColorf(float r, float g, float b, float a);
	void glSecondaryColorf(float r, float g, float b);
	void PushAttrib(uint32 mask);
	void PopAttrib();
	void LoadMatrixd(const double m[16]);
	void LoadMatrixf(const float m[16]);
	void MultMatrixd(const double m[16]);
	void MultMatrixf(const float m[16]);
	void LoadTransposeMatrixd(const double m[16]);
	void LoadTransposeMatrixf(const float m[16]);
	void MultTransposeMatrixd(const double m[16]);
	void MultTransposeMatrixf(const float m[16]);
	void glTranslatef(float x, float y, float z);
	void glTranslated(double x, double y, double z);
	void glRotatef(float angle, float x, float y, float z);
	void glRotated(double angle, double x, double y, double z);
	void glScalef(float x, float y, float z);
	void glScaled(double x, double y, double z);
	void MatrixMode(GLenum mode);
	void Enable(GLenum cap);
	void Disable(GLenum cap);
	void Viewport(double x, double y, double width, double height);
	void EnableClientState(GLenum _array);
	void DisableClientState(GLenum _array);
	void PushClientAttrib(uint32 mask);
	void PopClientAttrib();
	void InterleavedArrays(GLenum format, uint stride, const void* pointer);
	void InterleavedData(GLenum format, int stride, const void* pointer, int size);
	void VertexPointer(int index, GLint size, GLenum type, GLsizei stride, const void *pointer);
	void NormalPointer(int index, GLenum type, GLsizei stride, const void *pointer);
	void TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void *pointer);
	void ColorPointer(GLint size, GLenum type, GLsizei stride, const void * pointer);
	void EdgeFlagPointer(GLsizei stride, const GLboolean * pointer);
	void DrawArrays(GLenum mode, GLsizei first, GLsizei count);
//	void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
	void DrawIndexed(GLenum mode, GLsizei start, GLsizei end, GLsizei count, GLenum type, int startIndex);

	void Lightf(GLenum light, GLenum pname, float param);
	void Lightfv(GLenum light, GLenum pname, const GLfloat *params);
	void GetLightfv(GLenum light, GLenum pname, GLfloat *params);

	void ClipPlane(GLenum plane, const double *equation);
	void GetClipPlane(GLenum plane, double * equation);

	void LightModeli(GLenum pname, int param);
	void LightModelfv(GLenum pname, const float *params);

	void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
	void Perspective(double fovy, double aspect, double zNear, double zFar);

	void glEvalCoordf(GLfloat u);
	void glEvalCoordf(GLfloat u, GLfloat v);
	void ClearColor(float r, float g, float b, float a);
	void ClearDepth(double depth);
	void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void DepthMask(GLboolean mask);
	void CullFace(GLenum mode);
	void AlphaFunc(GLenum func, GLclampf ref);
	void StencilFunc(GLenum func, GLint ref, GLuint mask);
	void StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	void DepthFunc(GLenum func);
	void BlendEquation(GLenum mode);
	void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	void BlendFunc(GLenum src, GLenum dst);
	void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void LogicOp(GLenum opcode);
	void Clear(uint32 mask);
	void Materialf(GLenum face, GLenum pname, float param);
	void Materialfv(GLenum face, GLenum pname, const float *params);
	void glTexCoordf(float s);
	void glTexCoordf(float s, float t);
	void glTexCoordf(float s, float t, float r);
	void glMultiTexCoordf(GLenum texture, float s);
	void glMultiTexCoordf(GLenum texture, float s, float t);
	void glMultiTexCoordf(GLenum texture, float s, float t, float r);
	void glNormalf(float x, float y, float z);
	void glNormald(double x, double y, double z);
	void ColorMaterial(GLenum face, GLenum mode);
	void PolygonMode(GLenum face, GLenum mode);
	void EdgeFlag(GLboolean flag);
	void LineStipple(int factor, uint16 pattern);
	void PolygonStipple(const uint8 *mask);
	void PointSize(GLfloat size);
	void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void FillRectangle(Brush* pBrush, float x, float y, float width, float height);
	void GetFloatv(GLenum pname, GLfloat* params);
	void UseProgram(uint program);
	void ActiveTexture(GLenum pname);
	void ClientActiveTexture(GLenum pname);
	void TexEnvf(GLenum target, GLenum pname, GLfloat param);
	void TexEnvi(GLenum target, GLenum pname, GLint param);
	void TexEnvfv(GLenum target, GLenum pname, const GLfloat *params);
	void TexParameteri(GLenum target, GLenum pname, GLint param);
	void TexGeni(GLenum coord, GLenum pname, GLint param);
	void TexGenfv(GLenum coord, GLenum pname, const GLfloat *params);
	void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
//	void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
	void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *data);
//	void TexImage2D(GLenum target, Bitmap* pBitmap);
//	void GenBuffers(unsigned int n, unsigned int* buffers);
//	void BindBuffer(GLenum target, unsigned int buffer);
//	void BufferData(GLenum target, unsigned int size, const void* data, uint usage);
//	void GenTextures(int n, unsigned int *textures);
//	void DeleteTextures(int n, const unsigned int * textures);
	void BindTexture(GLenum target, unsigned int texture);
	void LoadIdentity();
	void Fogi(GLenum pname, int param);
	void Fogf(GLenum pname, float param);
	void Fogfv(GLenum pname, const float *params);
	void InitNames();
	void LoadName(GLuint name);
	void PushName(GLuint name);
	void PopName();
	void SelectBuffer(GLsizei size, GLuint* buffer);
	int RenderMode(GLenum mode);
	void Flush();

	stream_writer m_stream;

protected:

	~Graphics3DList();
};
#endif

#if 0
class DrawExt Graphics3DImmediate : public Graphics3D
{
public:
	CTOR Graphics3DImmediate(GLState* state, ClientState* clientState, GraphicsO* pGraphics);
//	CTOR Graphics3DImmediate(GLState* state, ClientState* clientState, IDirect3DDevice9* d3dDevice);

	virtual int GetMode() const
	{
		return 1;
	}

	virtual IDirect3DDevice9* GetDirect3DDevice9();
	virtual ID3D10Device* GetD3D10Device();

	void ReleaseGraphics();

	void CallList(DisplayList* displaylist);

	void SetVertexBlend(int b);
	void SetTweenFactor(float tweenFactor);

	void glBegin(int mode);
	void glEnd();
	void glVertexf(float x, float y);
	void glVertexf(float x, float y, float z);
	void glVertexf(float x, float y, float z, float w);
	void glVertexd(double x, double y);
	void glVertexd(double x, double y, double z);
	void glVertexd(double x, double y, double z, double w);
	void PushMatrix();
	void PopMatrix();
	void glColorf(float r, float g, float b);
	void glColorf(float r, float g, float b, float a);
	void glSecondaryColorf(float r, float g, float b);
	void PushAttrib(uint32 mask);
	void PopAttrib();
	void LoadMatrixd(const double m[16]);
	void LoadMatrixf(const float m[16]);
	void MultMatrixd(const double m[16]);
	void MultMatrixf(const float m[16]);
	void LoadTransposeMatrixd(const double m[16]);
	void LoadTransposeMatrixf(const float m[16]);
	void MultTransposeMatrixd(const double m[16]);
	void MultTransposeMatrixf(const float m[16]);
	void glTranslatef(float x, float y, float z);
	void glTranslated(double x, double y, double z);
	void glRotatef(float angle, float x, float y, float z);
	void glRotated(double angle, double x, double y, double z);
	void glScalef(float x, float y, float z);
	void glScaled(double x, double y, double z);
	void MatrixMode(GLenum mode);
	void Enable(GLenum cap);
	void Disable(GLenum cap);
	void Viewport(double x, double y, double width, double height);
	void EnableClientState(GLenum _array);
	void DisableClientState(GLenum _array);
	void PushClientAttrib(uint32 mask);
	void PopClientAttrib();
	void InterleavedArrays(GLenum format, uint stride, const void* pointer);
	void InterleavedData(GLenum format, int stride, const void* pointer, int size);
	void VertexPointer(int index, GLint size, GLenum type, GLsizei stride, const void* pointer);
	void NormalPointer(int index, GLenum type, GLsizei stride, const void* pointer);
	void TexCoordPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
	void ColorPointer(GLint size, GLenum type, GLsizei stride, const void* pointer);
	void EdgeFlagPointer(GLsizei stride, const GLboolean * pointer);
	void DrawArrays(GLenum mode, GLsizei first, GLsizei count);
//	void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);
	void DrawIndex(GLenum mode, GLsizei start, GLsizei end, GLsizei count, GLenum type, int startIndex);
	void Lightf(GLenum light, GLenum pname, float param);
	void Lightfv(GLenum light, GLenum pname, const float* params);
	void GetLightfv(GLenum light, GLenum pname, GLfloat* params);
	void ClipPlane(GLenum plane, const double* equation);
	void GetClipPlane(GLenum plane, double* equation);
	void LightModeli(GLenum pname, int param);
	void LightModelfv(GLenum pname, const float* params);
	void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
	void Perspective(double fovy, double aspect, double zNear, double zFar);
	void glEvalCoordf(GLfloat u);
	void glEvalCoordf(GLfloat u, GLfloat v);
	void ClearColor(float r, float g, float b, float a);
	void ClearDepth(double depth);
	void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void DepthMask(GLboolean mask);
	void CullFace(GLenum mode);
	void AlphaFunc(GLenum func, GLclampf ref);
	void StencilFunc(GLenum func, GLint ref, GLuint mask);
	void StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	void DepthFunc(GLenum func);
	void BlendEquation(GLenum mode);
	void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	void BlendFunc(GLenum src, GLenum dst);
	void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void LogicOp(GLenum opcode);
	void Clear(uint32 mask);
	void Materialf(GLenum face, GLenum pname, float param);
	void Materialfv(GLenum face, GLenum pname, const float *params);
	void glTexCoordf(float s);
	void glTexCoordf(float s, float t);
	void glTexCoordf(float s, float t, float r);
	void glMultiTexCoordf(GLenum texture, float s);
	void glMultiTexCoordf(GLenum texture, float s, float t);
	void glMultiTexCoordf(GLenum texture, float s, float t, float r);
	void glNormalf(float x, float y, float z);
	void glNormald(double x, double y, double z);
	void ColorMaterial(GLenum face, GLenum mode);
	void PolygonMode(GLenum face, GLenum mode);
	void EdgeFlag(GLboolean flag);
	void LineStipple(int factor, uint16 pattern);
	void PolygonStipple(const uint8 *mask);
	void PointSize(GLfloat size);
	void glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void FillRectangle(Brush* pBrush, float x, float y, float width, float height);
	void GetFloatv(GLenum pname, GLfloat* params);
	void UseProgram(uint program);
	void ActiveTexture(GLenum pname);
	void ClientActiveTexture(GLenum pname);
	void TexEnvf(GLenum target, GLenum pname, GLfloat param);
	void TexEnvi(GLenum target, GLenum pname, GLint param);
	void TexEnvfv(GLenum target, GLenum pname, const GLfloat *params);
	void TexGeni(GLenum coord, GLenum pname, GLint param);
	void TexGenfv(GLenum coord, GLenum pname, const GLfloat *params);
	void TexParameteri(GLenum target, GLenum pname, GLint param);
	void TexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const void *pixels);
//	void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
	void TexImage3D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const void *data);
//	void TexImage2D(GLenum target, Bitmap* pBitmap);
	void GenBuffers(unsigned int n, unsigned int* buffers);
	virtual VertexBuffer CreateVertexBuffer(unsigned int size, const void* data);
	virtual void DeleteVertexBuffer(VertexBuffer vertexBuffer);

	virtual Texture CreateTexture(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
	virtual Texture CreateTexture(Bitmap* pBitmap);
	virtual void SetTexture(int stage, Texture texture);

	virtual IndexBuffer CreateIndexBuffer(int type, unsigned int size, const void* data);

//	void BindBuffer(GLenum target, unsigned int buffer);
//	void BufferData(GLenum target, unsigned int size, const void* data, uint usage);

	virtual VertexDeclaration CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count);
	virtual void SetVertexDeclaration(VertexDeclaration vertexDecl);
	virtual void DeleteVertexDeclaration(VertexDeclaration vertexDecl);

	virtual IndexBuffer GetIndices();
	virtual void SetIndices(IndexBuffer indexBuffer);

	virtual void SetStreamSource(int stream, VertexBuffer vertexBuffer, int byteOffset, int stride);

//	void GenTextures(int n, unsigned int *textures);
//	void DeleteTextures(int n, const unsigned int * textures);
//	void BindTexture(GLenum target, unsigned int texture);
	void LoadIdentity();
	void Fogi(GLenum pname, int param);
	void Fogf(GLenum pname, float param);
	void Fogfv(GLenum pname, const float *params);
	void InitNames();
	void LoadName(GLuint name);
	void PushName(GLuint name);
	void PopName();
	void SelectBuffer(GLsizei size, GLuint* buffer);
	int RenderMode(GLenum mode);
	void Flush();

	ClientState* m_clientState;
	GraphicsO_3D* m_pG;

protected:

	~Graphics3DImmediate();
};
#endif

class __DECLSPEC_ALIGN_16__ DrawExt GraphicsO_3D : public System::Object
{
public:
//	CTOR GraphicsO_3D(GLState* state);
	CTOR GraphicsO_3D(/*GLState* state,*/ GraphicsO* pGraphics);
//	CTOR GraphicsO_3D(GLState* state, IDirect3DDevice9* d3dDevice);

	//GLState* m_state;

	/*
#if WIN32
	void* operator new (size_t size);
	void operator delete (void* p);
#endif
	*/

	/*
	enum
	{
		Wrap_repeat,
		Wrap_clamp,
	};
	*/

	void ReleaseGraphics();

//	void Init();

//	void CallList(DisplayList* displaylist);

	IndexBuffer CreateIndexBuffer(unsigned int type, unsigned int size, const void* data);

	VertexDeclaration CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count);
	void SetVertexDeclaration(VertexDeclaration vertexDecl);

	VertexBuffer CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage);

	void SetMatrixMode(GLenum mode);
	void PushMatrix();
	void PopMatrix();

	void Enable(GLenum cap);
	void Disable(GLenum cap);

	void GetFloatv(GLenum pname, GLfloat* params);

	void SetVertexBuffer(int stream, VertexBuffer vertexBuffer, int byteOffset, int stride);

	void Lightf(GLenum light, GLenum pname, float param);
	void Lightfv(GLenum light, GLenum pname, const float *params);
	void GetLightfv(GLenum light, GLenum pname, GLfloat *params);

	void ClipPlane(GLenum plane, const double *equation);

	void LightModeli(GLenum pname, int param);
	void LightModelfv(GLenum pname, const float *params);

//	void glViewport(int x, int y, int width, int height);
	void Viewport(int x, int y, int width, int height);
//	void VertexPointer(GLint size, GLenum type, GLsizei stride, GLsizei count, const void *pointer);

//	void DrawElements(GLenum mode, GLsizei count, GLenum type, const void* indices);

//	template<class T>	void DrawElements(GLenum mode, GLsizei count, const T* indices, const ClientArray vertexArray[], const ClientArray normalArray[], uint32 texEnabledMask, const ClientArray texcoordArray[]);

	Texture CreateTexture(GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void* pixels);
	Texture CreateTexture(Bitmap* pBitmap);
	void SetTexture(int stage, Texture texture);

	void LoadIdentity();
	void Frustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble zNear, GLdouble zFar);
	void Ortho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top);
	void Perspective(double fovy, double aspect, double zNear, double zFar);
	void LoadMatrixf(const float m[16]);
	void LoadMatrixd(const double m[16]);
	void MultMatrixf(const float m[16]);
	void MultMatrixd(const double m[16]);
	void LoadTransposeMatrixf(const float m[16]);
	void LoadTransposeMatrixd(const double m[16]);
	void MultTransposeMatrixf(const float m[16]);
	void MultTransposeMatrixd(const double m[16]);

	void TranslateTransform(float x, float y, float z);
	inline void TranslateTransform(LDraw::vector3f xyz)
	{
		TranslateTransform(xyz[0], xyz[1], xyz[2]);
	}

//	void Translated(double x, double y, double z);
//	void glTranslate(const vector3f& v);
//	void glTranslate(const vector3d& v);
	void ScaleTransform(float x, float y, float z);
	inline void ScaleTransform(LDraw::vector3f xyz)
	{
		ScaleTransform(xyz[0], xyz[1], xyz[2]);
	}

//	void Scaled(double x, double y, double z);
	void RotateTransform(float angleDegrees, float x, float y, float z);
	inline void RotateTransform(float angleDegrees, LDraw::vector3f axis)
	{
		RotateTransform(angleDegrees, axis[0], axis[1], axis[2]);
	}

//	void Rotated(double angle, double x, double y, double z);

	void SetPrimitiveTopology(unsigned int mode);
	void Draw(/*unsigned int mode,*/ UINT first, UINT count);

	void EvalCoordf(GLfloat u);
	void EvalCoordf(GLfloat u, GLfloat v);

	void ClearColor(float r, float g, float b, float a);
	void ClearDepth(double depth);

	void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	void DepthMask(GLboolean mask);

	void AlphaFunc(GLenum func, GLclampf ref);
	void StencilFunc(GLenum func, GLint ref, GLuint mask);
	void StencilOp(GLenum fail, GLenum zfail, GLenum zpass);
	void DepthFunc(GLenum func);
	void BlendEquation(GLenum mode);
	void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	void BlendFunc(GLenum src, GLenum dst);
	void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
	void LogicOp(GLenum opcode);
	void Fogi(GLenum pname, int param);
	void Fogf(GLenum pname, float param);
	void Fogfv(GLenum pname, const float *params);
	void Clear(uint32 mask);
	void CullFace(GLenum mode);

	void Materialf(GLenum face, GLenum pname, float param);
	void Materialfv(GLenum face, GLenum pname, const float *params);

	void Begin(int mode);
	void End();
	void TexCoordf(float s);
	void TexCoordf(float s, float t);
	void TexCoordf(float s, float t, float r);
	void MultiTexCoordf(GLenum texture, float s);
	void MultiTexCoordf(GLenum texture, float s, float t);
	void MultiTexCoordf(GLenum texture, float s, float t, float r);
	void Normalf(float x, float y, float z);
	void Normald(double x, double y, double z);
	void Vertexf(float x, float y);
	void Vertexf(float x, float y, float z);
	void Vertexf(float x, float y, float z, float w);
	void Vertexd(double x, double y);
	void Vertexd(double x, double y, double z);
	void Vertexd(double x, double y, double z, double w);
	void Colorf(float r, float g, float b);
	void Colorf(float r, float g, float b, float a);
	void SecondaryColorf(float r, float g, float b);
	void ColorMaterial(GLenum face, GLenum mode);
	void PolygonMode(GLenum face, GLenum mode);
	void EdgeFlag(GLboolean flag);
	void LineStipple(int factor, uint16 pattern);
	void PolygonStipple(const uint8 *mask);
	void PointSize(GLfloat size);
	void Rectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2);
	void FillRectangle(const Brush* pBrush, float x, float y, float width, float height);
	void GetBooleanv(GLenum pname, GLboolean *params);
//	void glGetFloatv(GLenum pname, GLfloat* params);
	void UseProgram(uint program);
	void PushAttrib(uint32 mask);
	void PopAttrib();
	void TexEnvf(int target, int pname, GLfloat param);
	void TexEnvi(int target, int pname, GLint param);
	void TexEnvfv(int target, int pname, const GLfloat *params);
	void TexParameteri(GLenum target, GLenum pname, GLint param);
//	void TexImage2D(int target, Bitmap* pBitmap);
//	void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void *pixels);
	void TexGeni(GLenum coord, GLenum pname, GLint param);
	void TexGenfv(GLenum coord, GLenum pname, const GLfloat *params);

//	void GenTextures(unsigned int n, unsigned int *textures);
//	void DeleteTextures(unsigned int n, const unsigned int * textures);

	//void BindTexture(GLenum target, unsigned int texture);

	LDraw::GraphicsO* m_pGraphics;

#if 0
	uint16 m_linepattern;
	uint16 m_linepatternfactor;
	int m_line_s;

	uint8 m_colorMask;
	bool m_depthMask;

	int m_depthFunc;

	int m_stencilFunc_func[2];
	int m_stencilFunc_ref[2];
	GLuint m_stencilFunc_mask[2];

	int m_stencilOp_fail[2];
	int m_stencilOp_zfail[2];
	int m_stencilOp_zpass[2];

	uint16 m_blendEquationRGB;
	uint16 m_blendEquationAlpha;

	uint16 m_blendFuncSrcRGB;
	uint16 m_blendFuncSrcAlpha;
	uint16 m_blendFuncDstRGB;
	uint16 m_blendFuncDstAlpha;

	float m_pointSize;

	int m_fogMode;
	float m_fogDensity;
	float m_fogStart;
	float m_fogEnd;
	vector4f m_fogColor;

	uint m_texGenMode[TEXTURES_MAX][4];
	vector4f m_object_plane[TEXTURES_MAX][4];
	vector4f m_eye_plane[TEXTURES_MAX][4];

	uint m_renderMode;

	uint m_selectBufferSize;
	uint* m_selectBuffer;
	uint* m_pselect;
	int m_nhits;
	float m_minz;
	float m_maxz;
	bool m_bHitSinceLast;

	void HitRecord();

	void processVertex(const vector4f& obj, const vector3f& normal, const vector4f texcoord[], Vertex& v);
	void processVertex(Vertex& v);

//protected:

#if !USE_GL

	//void UpdateModelViewMatrixInverse();

	void Vertexf(const vector4f& obj, const vector3f& normal, const vector4f texcoord[8]);

	void Prep();
	void UnPrep();

//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector4f color);
//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector4f color[3]);
//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector2f texcoord[3], const double q[3], const Bitmap* pTextureBitmap, uint32 flags);
//	void FillTriangle(const vector2f winxy[3], const float winz[3], const vector4f color[3], const vector4f* texcoord[3], const float q[3], const float fog_f[3], uint32 flags);
	void FillTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);
//	void FillTriangle(const PointF xpt[3], const vector4f points[3], const vector4f color[3], const vector4f secondarycolor[3], const vector4f texcoord[3], const TexImage* pTexture, Program* pProgram, uint32 flags);

	void point(const Vertex& v);

	void line(const Vertex& v0, const Vertex& v1);
	void line2(const Vertex& v0, const Vertex& v1);
	void line3(const Vertex& v0, const Vertex& v1);

	void triangle3(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void triangle2(const Vertex& v0, const Vertex& v1, const Vertex& v2);
	void triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2);

	void quad(const Vertex& v0, const Vertex& v1, const Vertex& v2, const Vertex& v3);

	class CurrentState
	{
	public:
		vector4f m_color;
		vector4f m_secondarycolor;
		vector4f m_texcoord[TEXTURES_MAX];
		vector3f m_normal;
	};

protected:

	double m_viewport[4];

	uint m_polygonMode[2];

	uint m_program;	// Active shader program

//	bool m_matrixModelView3iValid;

	vector4f m_colortranslate;	// extension ?

	int m_colorMaterialFace;
	int m_colorMaterialMode;

	vector4f m_ambient;
	vector4f m_diffuse;
	vector4f m_specular;
	vector4f m_emission;
	float m_shininess;

	uint m_matrixMode;

	/*
	vector4f m_color;
	vector4f m_secondarycolor;
	vector4f m_texcoord;
	vector3f m_normal;
	*/

	int m_beginMode;
	int m_nvertex;
	vector<Vertex> m_vertices;
//	float m_clearDepth;

	stack<uint32> m_attribMaskStack;

	class LineState
	{
	public:
		CTOR LineState(bool line_stipple, uint16 linepattern, uint16 linepatternfactor)
		{
			m_line_stipple = line_stipple;
			m_linepattern = linepattern;
			m_linepatternfactor = linepatternfactor;
		}

		uint16 m_linepattern;
		uint16 m_linepatternfactor;
		bool m_line_stipple : 1;
	};

	class PolygonStippleData
	{
	public:
		uint32 m_data[32];
	};

public:

	int m_alphaFunc;

	float m_alphaRef;

	int m_logicOp;
	int m_cullFaceMode;
	PolygonStippleData m_polygonStipple;

//	IDirect3DDevice9* m_d3dDevice;

protected:

	CurrentState m_current;

	stack<CurrentState> m_currentStateStack;
	stack<PolygonStippleData> m_polygonStippleStack;
	stack<LineState> m_lineStateStack;

	bool m_edgeFlag : 1;

	vector4f m_clipplane[32];

	vector4f m_ambientLightModel;

#endif

	BitmapData m_bitmapData;
	__DECLSPEC_ALIGN_16__ matrix3f m_transform2d;
#endif

	~GraphicsO_3D();
};

typedef GraphicsO_3D Graphics3D;

DrawExt void FrustumMatrix(float m[16], double left, double right, double bottom, double top, double zNear, double zFar);
DrawExt void FrustumMatrix(double m[16], double left, double right, double bottom, double top, double zNear, double zFar);
DrawExt int gluProject(const float obj[3], const float model[16], const float proj[16], const GLdouble viewport[4], float win[3]);

DrawExt void gluPickMatrix(GraphicsO_3D* pG, double x, double y, double width, double height, double viewport[4]);

unsigned int factorial(unsigned int n);
unsigned int binomial_coefficient(unsigned int n, unsigned int k);
double B(int n, int i, double u, const double* coefs);

}	// LDraw
}

#endif // Draw_gl_h
