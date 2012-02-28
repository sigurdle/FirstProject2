#ifndef System_Graphics_h
#define System_Graphics_h

#ifdef __LERSTAD__
#import "Imaging/Imaging.h"
#else
#include "Imaging/Imaging.h"
#endif

#include "gm/BBox.h"

#ifndef GfxExt
#define GfxExt DECLSPEC_DLLIMPORT
#endif

// D3D9

struct IDirect3DDevice9;
struct IDirect3DSwapChain9;
struct IDirect3DSurface9;
struct IDirect3DBaseTexture9;
struct IDirect3DTexture9;
struct IDirect3DVertexBuffer9;
struct IDirect3DIndexBuffer9;
struct IDirect3DVertexDeclaration9;
struct IDirect3DVertexShader9;
struct IDirect3DPixelShader9;

struct ID3DXBuffer;
struct ID3DXConstantTable;
struct ID3DXEffect;
struct ID3DXEffectCompiler;
struct ID3DXEffectPool;

struct _D3DVERTEXELEMENT9;

typedef LPCSTR D3DXHANDLE;

// D3D10
#ifndef __LERSTAD__

#undef new

#include <D3D10_1.h>
#include <D3DX10Mesh.h>

#include <D3D11.h>

#include <D2D1.h>
#include <DWrite.h>

#include <D3DX11async.h>
#include <D3DX11Effect.h>
#include <D3Dcompiler.h>

#define new _new

#else

struct IDXGIFactory : public IUnknown {};
struct IDXGIFactory1 : public IUnknown {};
struct IDXGIDevice : public IUnknown {};
struct IDXGIDevice1 : public IUnknown {};
struct IDXGIAdapter : public IUnknown {};
struct IDXGIAdapter1 : public IUnknown {};
struct IDXGISwapChain : public IUnknown {};

// D3D10
struct ID3D10Device : public IUnknown {};
struct ID3D10Device1 : public IUnknown {};
struct ID3D10Buffer : public IUnknown {};
struct ID3D10Blob : public IUnknown {};
struct ID3D10Resource : public IUnknown {};
struct ID3D10Texture1D : public IUnknown {};
struct ID3D10Texture2D : public IUnknown {};
struct ID3D10VertexShader : public IUnknown {};
struct ID3D10PixelShader : public IUnknown {};
struct ID3D10InputLayout : public IUnknown {};
struct ID3D10RenderTargetView : public IUnknown {};
struct ID3D10DepthStencilView : public IUnknown {};
struct ID3D10ShaderResourceView : public IUnknown {};
struct ID3D10RasterizerState : public IUnknown {};
struct ID3D10DepthStencilState : public IUnknown {};

struct ID3D10Effect : public IUnknown {};
struct ID3D10EffectVariable : public IUnknown {};
struct ID3D10EffectScalarVariable : public IUnknown {};
struct ID3D10EffectVectorVariable : public IUnknown {};
struct ID3D10EffectMatrixVariable : public IUnknown {};
struct ID3D10EffectShaderResourceVariable : public IUnknown {};
struct ID3D10EffectTechnique : public IUnknown {};

typedef struct _D3D10_EFFECT_DESC
{
	BOOL    IsChildEffect;          // TRUE if this is a child effect, 
									// FALSE if this is standalone or an effect pool.
                                    
	UINT    ConstantBuffers;        // Number of constant buffers in this effect,
									// excluding the effect pool.
	UINT    SharedConstantBuffers;  // Number of constant buffers shared in this
									// effect's pool.
                                    
	UINT    GlobalVariables;        // Number of global variables in this effect,
									// excluding the effect pool.
	UINT    SharedGlobalVariables;  // Number of global variables shared in this
									// effect's pool.
                                    
	UINT    Techniques;             // Number of techniques in this effect,
									// excluding the effect pool.
} D3D10_EFFECT_DESC;

typedef struct _D3DX11_EFFECT_DESC
{
    UINT    ConstantBuffers;        // Number of constant buffers in this effect
    UINT    GlobalVariables;        // Number of global variables in this effect
    UINT    InterfaceVariables;     // Number of global interfaces in this effect
    UINT    Techniques;             // Number of techniques in this effect
    UINT    Groups;                 // Number of groups in this effect
} D3DX11_EFFECT_DESC;

typedef struct D3D10_VIEWPORT
    {
    int TopLeftX;
    int TopLeftY;
    unsigned int Width;
    unsigned int Height;
    float MinDepth;
    float MaxDepth;
    } 	D3D10_VIEWPORT;

typedef 
enum D3D10_MAP
    {	D3D10_MAP_READ	= 1,
	D3D10_MAP_WRITE	= 2,
	D3D10_MAP_READ_WRITE	= 3,
	D3D10_MAP_WRITE_DISCARD	= 4,
	D3D10_MAP_WRITE_NO_OVERWRITE	= 5
    } 	D3D10_MAP;

typedef 
enum D3D10_FEATURE_LEVEL1
    {	D3D10_FEATURE_LEVEL_10_0	= 0xa000,
	D3D10_FEATURE_LEVEL_10_1	= 0xa100,
	D3D10_FEATURE_LEVEL_9_1	= 0x9100,
	D3D10_FEATURE_LEVEL_9_2	= 0x9200,
	D3D10_FEATURE_LEVEL_9_3	= 0x9300
    } 	D3D10_FEATURE_LEVEL1;

// D3D11
struct ID3D11Device : public IUnknown {};
struct ID3D11DeviceContext : public IUnknown {};
struct ID3D11Buffer : public IUnknown {};
struct ID3D11Resource : public IUnknown {};
struct ID3D11Texture1D : public IUnknown {};
struct ID3D11Texture2D : public IUnknown {};
struct ID3D11VertexShader : public IUnknown {};
struct ID3D11PixelShader : public IUnknown {};
struct ID3D11InputLayout : public IUnknown {};
struct ID3D11RenderTargetView : public IUnknown {};
struct ID3D11DepthStencilView : public IUnknown {};
struct ID3D11RasterizerState : public IUnknown {};
struct ID3D11DepthStencilState : public IUnknown {};

struct ID3DX11Effect : public IUnknown {};
struct ID3DX11EffectVariable : public IUnknown {};
struct ID3DX11EffectScalarVariable : public IUnknown {};
struct ID3DX11EffectVectorVariable : public IUnknown {};
struct ID3DX11EffectMatrixVariable : public IUnknown {};
struct ID3DX11EffectShaderResourceVariable : public IUnknown {};
struct ID3DX11EffectTechnique : public IUnknown {};
struct ID3D11ShaderResourceView : public IUnknown {};

typedef struct D3D11_VIEWPORT
    {
    int TopLeftX;
    int TopLeftY;
    unsigned int Width;
    unsigned int Height;
    float MinDepth;
    float MaxDepth;
    } 	D3D11_VIEWPORT;

typedef 
enum D3D_FEATURE_LEVEL
    {	D3D_FEATURE_LEVEL_9_1	= 0x9100,
	D3D_FEATURE_LEVEL_9_2	= 0x9200,
	D3D_FEATURE_LEVEL_9_3	= 0x9300,
	D3D_FEATURE_LEVEL_10_0	= 0xa000,
	D3D_FEATURE_LEVEL_10_1	= 0xa100,
	D3D_FEATURE_LEVEL_11_0	= 0xb000
    } 	D3D_FEATURE_LEVEL;

typedef 
enum D3D11_MAP
    {	D3D11_MAP_READ	= 1,
	D3D11_MAP_WRITE	= 2,
	D3D11_MAP_READ_WRITE	= 3,
	D3D11_MAP_WRITE_DISCARD	= 4,
	D3D11_MAP_WRITE_NO_OVERWRITE	= 5
    } 	D3D11_MAP;

//
struct IDWriteFontFamily : public IUnknown {};
struct IDWriteFontFace : public IUnknown {};
struct IDWriteTextFormat : public IUnknown {};
struct IDWriteTextLayout : public IUnknown {};

typedef struct D2D_POINT_2F
{
    float x;
    float y;

} D2D_POINT_2F;

typedef D2D_POINT_2F D2D1_POINT_2F;

struct D2D_MATRIX_3X2_F
{
	float _11;
	float _12;
	float _21;
	float _22;
	float _31;
	float _32;
};

typedef D2D_MATRIX_3X2_F D2D1_MATRIX_3X2_F;

namespace D2D1
{
	class Matrix3x2F : public D2D1_MATRIX_3X2_F
	{
	public:
	};
}

// Direct2D

struct ID2D1Factory : public IUnknown {};
struct IDWriteFactory : public IUnknown {};

struct ID2D1RenderTarget : public IUnknown {};

struct ID2D1StrokeStyle : public IUnknown {};

struct ID2D1Bitmap : public IUnknown {};
struct ID2D1Brush : public IUnknown {};
struct ID2D1SolidColorBrush : public ID2D1Brush {};
struct ID2D1LinearGradientBrush : public ID2D1Brush {};
struct ID2D1RadialGradientBrush : public ID2D1Brush {};
struct ID2D1BitmapBrush : public ID2D1Brush {};

struct ID2D1GradientStopCollection : public IUnknown {};
struct ID2D1GeometrySink : public IUnknown {};

struct ID2D1Geometry : public IUnknown{ };
struct ID2D1RectangleGeometry : public ID2D1Geometry {};
struct ID2D1RoundedRectangleGeometry : public ID2D1Geometry {};
struct ID2D1EllipseGeometry : public ID2D1Geometry {};
struct ID2D1PathGeometry : public ID2D1Geometry {};

struct D3DXVECTOR3
{
    float x, y, z;
};

struct D3DXVECTOR4
{
    float x, y, z, w;
};

#ifndef D3DMATRIX_DEFINED
typedef struct _D3DMATRIX {
    union {
        struct {
            float        _11, _12, _13, _14;
            float        _21, _22, _23, _24;
            float        _31, _32, _33, _34;
            float        _41, _42, _43, _44;

        };
        float m[4][4];
    };
} D3DMATRIX;
#define D3DMATRIX_DEFINED
#endif

typedef D3DMATRIX D3DXMATRIX;

struct DWRITE_GLYPH_OFFSET
{
    /// <summary>
    /// Offset in the advance direction of the run. A positive advance offset moves the glyph to the right
    /// (in pre-transform coordinates) if the run is left-to-right or to the left if the run is right-to-left.
    /// </summary>
    float advanceOffset;

    /// <summary>
    /// Offset in the ascent direction, i.e., the direction ascenders point. A positive ascender offset moves
    /// the glyph up (in pre-transform coordinates).
    /// </summary>
    float ascenderOffset;
};

#endif

typedef ID3D10Effect ID3DX10Effect;
typedef ID3D10EffectVariable ID3DX10EffectVariable;
typedef ID3D10EffectScalarVariable ID3DX10EffectScalarVariable;
typedef ID3D10EffectVectorVariable ID3DX10EffectVectorVariable;
typedef ID3D10EffectMatrixVariable ID3DX10EffectMatrixVariable;
typedef ID3D10EffectShaderResourceVariable ID3DX10EffectShaderResourceVariable;
typedef ID3D10EffectTechnique ID3DX10EffectTechnique;

#ifndef __LERSTAD__
typedef D3D10_STATE_BLOCK_MASK D3DX10_STATE_BLOCK_MASK;
typedef D3D10_PASS_DESC D3DX10_PASS_DESC;
typedef D3D10_TECHNIQUE_DESC D3DX10_TECHNIQUE_DESC;
#endif

typedef D3D10_EFFECT_DESC D3DX10_EFFECT_DESC;

#ifndef __LERSTAD__
GfxExt HRESULT D3DX11CreateEffectFromFileW(LPCWSTR pFileName, CONST D3D10_SHADER_MACRO *pDefines, 
    ID3D10Include *pInclude, LPCSTR pProfile, UINT HLSLFlags, UINT FXFlags, ID3D11Device *pDevice, 
    ID3D10EffectPool *pEffectPool, ID3DX11ThreadPump* pPump, ID3DX11Effect **ppEffect, ID3D10Blob **ppErrors, HRESULT* pHResult);
#endif

GfxExt HRESULT MapBuffer(ID3D10Device*, ID3D10Buffer* buffer, D3D10_MAP mapType, void** p);
GfxExt void UnmapBuffer(ID3D10Device*, ID3D10Buffer* buffer);

GfxExt HRESULT MapBuffer(ID3D11DeviceContext* deviceContext, ID3D11Buffer* buffer, D3D11_MAP mapType, void** p);
GfxExt void UnmapBuffer(ID3D11DeviceContext* deviceContext, ID3D11Buffer* buffer);

#ifndef __LERSTAD__
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#endif

// CG

typedef struct _CGcontext *CGcontext;
typedef struct _CGprogram *CGprogram;
typedef struct _CGparameter *CGparameter;
typedef struct _CGobj *CGobj;
typedef struct _CGbuffer *CGbuffer;
typedef struct _CGeffect *CGeffect;
typedef struct _CGtechnique *CGtechnique;
typedef struct _CGpass *CGpass;
typedef struct _CGstate *CGstate;
typedef struct _CGstateassignment *CGstateassignment;
typedef struct _CGannotation *CGannotation;

//#if AMIGA
//struct RastPort;
//#endif

namespace System
{
namespace gm
{
GfxExt D3DXMATRIX MatrixTranslation(float x, float y, float z);
GfxExt D3DXMATRIX MatrixTranslation(gm::vector3f vec3);
GfxExt D3DXMATRIX MatrixScale(gm::vector3f vec3);
GfxExt D3DXMATRIX MatrixRotationAxis(gm::vector3f vec3, float angle);
}

namespace Graphics
{

	/*
class PixelLum;
class PixelLumAP;
class PixelRGB_24;
class PixelRGB_32;
class PixelRGBAP_32;
class PixelRGBAP_4444;
*/
class GraphicsI;
class OpenGL_I;
class Direct3D10_I;
class Bitmap;

class GfxExt WindowSurfDesc
{
public:
	ubyte m_depthBits;
};

}
}

#include "RenderTarget.h"

namespace System
{
namespace Graphics
{

struct VERTEX_XYZ
{
	gm::vector3f position;
};

struct VERTEX_XYZ_T2
{
	gm::vector3f position;
	gm::vector2f texcoord;
};

struct VERTEX_XYZ_T2_T2
{
	gm::vector3f position;
	gm::vector2f texcoord[2];
};

class GfxExt ColorMatrix
{
public:

	CTOR ColorMatrix() : m_transform(gm::matrix4f::getIdentity())
	{
	}

	CTOR ColorMatrix(
		float a00, float a01, float a02, float a03,
		float a10, float a11, float a12, float a13,
		float a20, float a21, float a22, float a23,
		float a30, float a31, float a32, float a33,
		float a40 = 0, float a41 = 0, float a42 = 0, float a43 = 0
		) :
	m_transform(
		a00, a01, a02, a03,
		a10, a11, a12, a13,
		a20, a21, a22, a23,
		a30, a31, a32, a33),
	m_translate(a40, a41, a42, a43)
	{
	}

	gm::matrix4f m_transform;
	gm::vector4f m_translate;
};

class GfxExt Texture
{
public:
	CTOR Texture()
	{
		m_device = NULL;
		u.d3d = NULL;
	}

	CTOR Texture(GraphicsI* device, IDirect3DTexture9* d3d)
	{
		m_device = device;
		u.d3d = d3d;
	}

	CTOR Texture(GraphicsI* device, ID3D10ShaderResourceView* d3d10view)
	{
		m_device = device;
		u.d3d10view = d3d10view;
	}

	/*
	CTOR Texture(GraphicsI* device, ID3D10Texture1D* d3d10)
	{
		m_device = device;
		u.d3d10tex1D = d3d10;
	}

	CTOR Texture(GraphicsI* device, ID3D10Texture2D* d3d10)
	{
		m_device = device;
		u.d3d10tex2D = d3d10;
	}
	*/

	CTOR Texture(GraphicsI* device, unsigned int n, int target)
	{
		m_device = device;
		u.n = n;
		m_target = target;
	}

	bool operator == (IDirect3DTexture9* d3d) const
	{
		return u.d3d == d3d;
	}

	inline bool operator != (IDirect3DTexture9* d3d) const
	{
		return !(*this == d3d);
	}

	int GetWidth();
	int GetHeight();

	union
	{
		IDirect3DTexture9* d3d;
		ID3D10ShaderResourceView* d3d10view;
		ID3D11ShaderResourceView* d3d11view;
		/*
		ID3D10Resource* d3d10res;
		ID3D10Texture1D* d3d10tex1D;
		ID3D10Texture2D* d3d10tex2D;
		*/
		unsigned int n;
	}
	u;

	int m_target;

	GraphicsI* m_device;
};

class DrawBitmapArgs
{
public:
	CTOR DrawBitmapArgs(const ColorMatrix& colorTransform) : m_colorTransform(colorTransform)
	{
	}

	ColorMatrix m_colorTransform;
};

class GfxExt Direct10
{
public:

	class GfxExt Imp
	{
	public:

		CTOR Imp();
		~Imp();

		bool Init();

		void Render(RenderTarget* rt, Bitmap* bitmap, gm::RectF dstRect, gm::vector4f colorMultiply = gm::vector4f(1.0f, 1.0f, 1.0f, 1.0f), gm::vector4f colorTranslate = gm::vector4f());
		void Render(RenderTarget* rt, Bitmap* bitmap, gm::RectF dstRect, gm::RectF srcRect, DrawBitmapArgs* args = NULL);

		D3D_FEATURE_LEVEL m_featureLevel;

		ID3D10Device* m_device;
		ID3D10Device1* m_device1;
		ID3D11Device* m_device11;
		ID3D11DeviceContext* m_deviceContext;

		IDXGIFactory* m_DXGIFactory;
		IDXGIFactory1* m_DXGIFactory1;

		IDXGIDevice* m_pDXGIDevice;
		IDXGIDevice1* m_pDXGIDevice1;

		IDXGIAdapter* m_pDXGIAdapter;
		IDXGIAdapter1* m_pDXGIAdapter1;

		ID2D1Factory* m_D2DFactory;
		IDWriteFactory* m_DWriteFactory;

		ID3D10DepthStencilState* m_pDepthStencilState[2/*DepthEnable*/];
		ID3D10RasterizerState* m_pRasterizerState[2/*frontccw*/][2/*solid*/][2/*multiSampleEnable*/];

		ID3D10Effect* m_effect;
		ID3D10EffectTechnique* m_RenderTextureTechnique;
		ID3D10EffectTechnique* m_RenderSolidColorTechnique;

		union
		{
			byte dummy[512];
#ifndef __LERSTAD__
		D3DX10_STATE_BLOCK_MASK m_RenderTextureStateBlockMask;
#endif
		};

		union
		{
			byte dummy[512];
#ifndef __LERSTAD__
		D3DX10_STATE_BLOCK_MASK m_RenderSolidColorStateBlockMask;
#endif
		};

		ID3DX10EffectTechnique* m_RenderTextureMaskTechnique;
		ID3DX10EffectTechnique* m_RenderTextureColorMatrixTechnique;

		ID3DX10EffectMatrixVariable* m_modelViewVariable;
		ID3DX10EffectMatrixVariable* m_projectionVariable;
		ID3DX10EffectMatrixVariable* m_modelViewProjectionVariable;

		ID3DX10EffectShaderResourceVariable* m_texture1Variable;

		ID3DX10EffectShaderResourceVariable* m_texture0Variable;
		ID3DX10EffectMatrixVariable* m_textureMatrix0Variable;

		ID3DX10EffectMatrixVariable* m_colorTransformVariable;
		ID3DX10EffectVectorVariable* m_colorTranslateVariable;
		ID3DX10EffectVectorVariable* m_colorMultiplyVariable;

		ID3D10InputLayout* m_vertexLayout0;
		ID3D10InputLayout* m_vertexLayout1;
		ID3D10InputLayout* m_vertexLayout2;

		ID3D10Buffer* m_DrawImageVertexBuffer;

		HRESULT m_hr;
	};

//	static ID3D10Device* get_DeviceContext();
	static ID3D10Device* get_D3DDevice();
	static ID3D10Device1* get_D3DDevice1();
	static ID2D1Factory* get_D2DFactory();
	static IDWriteFactory* get_DWriteFactory();

	static void ReleaseD3DDevice(ID3D10Device* device);

	static int m_deviceRefCount;

	static Imp s;

private:

	CTOR Direct10();
};

class GfxExt Direct11
{
public:

	class GfxExt Imp
	{
	public:

		CTOR Imp();
		~Imp();

		bool Init();

		void Render(RenderTarget* rt, Bitmap* bitmap, gm::RectF dstRect, gm::vector4f colorMultiply = gm::vector4f(1.0f, 1.0f, 1.0f, 1.0f), gm::vector4f colorTranslate = gm::vector4f());
		void Render(RenderTarget* rt, Bitmap* bitmap, gm::RectF dstRect, gm::RectF srcRect, DrawBitmapArgs* args = NULL);

		D3D_FEATURE_LEVEL m_featureLevel;

		ID3D10Device1* m_device1;
		ID3D11Device* m_device;
		ID3D11DeviceContext* m_deviceContext;

		IDXGIFactory* m_DXGIFactory;
		IDXGIFactory1* m_DXGIFactory1;

		IDXGIDevice* m_pDXGIDevice;
		IDXGIDevice1* m_pDXGIDevice1;

		IDXGIAdapter* m_pDXGIAdapter;
		IDXGIAdapter1* m_pDXGIAdapter1;

		ID2D1Factory* m_D2DFactory;
		IDWriteFactory* m_DWriteFactory;

		ID3D11DepthStencilState* m_pDepthStencilState[2/*DepthEnable*/];
		ID3D11RasterizerState* m_pRasterizerState[2/*frontccw*/][2/*solid*/][2/*multiSampleEnable*/];

		ID3DX11Effect* m_effect;
		ID3DX11EffectTechnique* m_RenderTextureTechnique;
		ID3DX11EffectTechnique* m_RenderSolidColorTechnique;

		union
		{
			byte dummy[512];
#ifndef __LERSTAD__
		D3DX11_STATE_BLOCK_MASK m_RenderTextureStateBlockMask;
#endif
		};

		union
		{
			byte dummy[512];
#ifndef __LERSTAD__
		D3DX11_STATE_BLOCK_MASK m_RenderSolidColorStateBlockMask;
#endif
		};

		ID3DX11EffectTechnique* m_RenderTextureMaskTechnique;
		ID3DX11EffectTechnique* m_RenderTextureColorMatrixTechnique;

		ID3DX11EffectMatrixVariable* m_modelViewVariable;
		ID3DX11EffectMatrixVariable* m_projectionVariable;
		ID3DX11EffectMatrixVariable* m_modelViewProjectionVariable;

		ID3DX11EffectShaderResourceVariable* m_texture1Variable;

		ID3DX11EffectShaderResourceVariable* m_texture0Variable;
		ID3DX11EffectMatrixVariable* m_textureMatrix0Variable;

		ID3DX11EffectMatrixVariable* m_colorTransformVariable;
		ID3DX11EffectVectorVariable* m_colorTranslateVariable;
		ID3DX11EffectVectorVariable* m_colorMultiplyVariable;

		ID3D11InputLayout* m_vertexLayout0;
		ID3D11InputLayout* m_vertexLayout1;
		ID3D11InputLayout* m_vertexLayout2;

		ID3D11Buffer* m_DrawImageVertexBuffer;

		HRESULT m_hr;
	};

	static ID3D11DeviceContext* get_DeviceContext();
	static ID3D11Device* get_D3DDevice();
	static ID3D10Device1* get_D3DDevice1();
	static ID2D1Factory* get_D2DFactory();
	static IDWriteFactory* get_DWriteFactory();

	static void ReleaseD3DDevice(ID3D11Device* device);

	static int m_deviceRefCount;

	static Imp s;

private:

	CTOR Direct11();
};

struct VERTEX_XYZ_DIFFUSE
{
	gm::vector3f position;
	uint32 diffuse;
};

enum DeclType
{
	DECLTYPE_FLOAT1    =  0,  // 1D float expanded to (value, 0., 0., 1.)
	DECLTYPE_FLOAT2    =  1,  // 2D float expanded to (value, value, 0., 1.)
	DECLTYPE_FLOAT3    =  2,  // 3D float expanded to (value, value, value, 1.)
	DECLTYPE_FLOAT4    =  3,  // 4D float
};

struct VertexDeclElement
{
	const char* usage;
	int stream;
	int offset;
	DeclType type;
	int usageIndex;
};

interface __IUnknown
{
	virtual HRESULT QueryInterface(const GUID&, void**p) = 0;	// Unused
	virtual ULONG AddRef() = 0;
	virtual ULONG Release() = 0;
};

class GraphicsO_3D;

class GfxExt VertexDeclarationGL : public __IUnknown
{
public:
	CTOR VertexDeclarationGL();
	~VertexDeclarationGL();

	virtual HRESULT QueryInterface(const GUID&, void**p)
	{
		return -1;
	}

	virtual ULONG AddRef()
	{
		return ++m_refcount;
	}

	virtual ULONG Release();

	_D3DVERTEXELEMENT9* m_elements;
	unsigned int m_count;

	ULONG m_refcount;

	GraphicsO_3D* m_device;
};

class GfxExt VertexDeclaration
{
public:
	CTOR VertexDeclaration()
	{
		u.d3d = NULL;
//		device = NULL;
	}

	inline CTOR VertexDeclaration(VertexDeclarationGL* gl)
	{
		u.gl = gl;
	}

	inline CTOR VertexDeclaration(IDirect3DVertexDeclaration9* d3d)
	{
		u.d3d = d3d;
	}

	inline CTOR VertexDeclaration(ID3D10InputLayout* d3d10)
	{
		u.d3d10 = d3d10;
	}

	bool operator == (const __IUnknown* p) const
	{
		return u.gl == p;
	}

	inline bool operator != (const __IUnknown* p) const
	{
		return !(*this == p);
	}

	union
	{
		IDirect3DVertexDeclaration9* d3d;
		ID3D10InputLayout* d3d10;
		ID3D11InputLayout* d3d11;
		VertexDeclarationGL* gl;
	}
	u;
};

class GfxExt VertexBuffer
{
public:
	CTOR VertexBuffer()
	{
		u.d3d = NULL;
		m_device = NULL;
	}

	CTOR VertexBuffer(IDirect3DVertexBuffer9* d3d9)
	{
		u.d3d = d3d9;
		m_device = NULL;
	}

	CTOR VertexBuffer(ID3D10Buffer* d3d10)
	{
		u.d3d10 = d3d10;
		m_device = NULL;
	}

	CTOR VertexBuffer(unsigned int n)
	{
		u.n = n;
		m_device = nullptr;
	}

	CTOR VertexBuffer(decltype(nullptr))
	{
		u.n = 0;
		m_device = nullptr;
	}

	/*
	CTOR VertexBuffer(CGbuffer cgBuffer)
	{
		u.cg = cgBuffer;
	}
	*/

	VertexBuffer& operator = (IDirect3DVertexBuffer9* d3d9)
	{
		u.d3d = d3d9;
		return *this;
	}

	bool operator == (const VertexBuffer& other) const
	{
		return u.d3d == other.u.d3d;
	}

	bool operator == (unsigned int n) const
	{
		return u.n == n;
	}

	bool operator != (unsigned int n) const
	{
		return u.n != n;
	}

	bool operator == (decltype(nullptr)) const
	{
		return u.d3d == nullptr;
	}

	bool operator != (decltype(nullptr)) const
	{
		return u.d3d != nullptr;
	}

	union
	{
		IDirect3DVertexBuffer9* d3d;
		ID3D10Buffer* d3d10;
		ID3D11Buffer* d3d11;
		//CGbuffer cg;
		unsigned int n;
	}
	u;

	GraphicsO_3D* m_device;
};

class GfxExt IndexBuffer
{
public:
	CTOR IndexBuffer()
	{
		u.d3d = NULL;
		m_device = NULL;
	}

	CTOR IndexBuffer(unsigned int n)
	{
		u.d3d = NULL;
		m_type = 0;
		m_device = NULL;
	}

	CTOR IndexBuffer(unsigned int n, unsigned int type)
	{
		u.n = n;
		m_type = type;
		m_device = NULL;
	}

	CTOR IndexBuffer(IDirect3DIndexBuffer9* d3d, unsigned int type)
	{
		u.d3d = d3d;
		m_type = type;
		m_device = NULL;
	}

	CTOR IndexBuffer(ID3D10Buffer* d3d, unsigned int type)
	{
		u.d3d10 = d3d;
		m_type = type;
		m_device = NULL;
	}

	bool operator == (const IndexBuffer& other) const
	{
		return u.d3d == other.u.d3d;
	}

	inline bool operator != (const IndexBuffer& other) const
	{
		return !(*this == other);
	}

	bool operator == (unsigned int n) const
	{
		return u.n == n;
	}

	bool operator != (unsigned int n) const
	{
		return u.n != n;
	}

	union
	{
		IDirect3DIndexBuffer9* d3d;
		ID3D10Buffer* d3d10;
		ID3D11Buffer* d3d11;
		unsigned int n;
	}
	u;

	unsigned int m_type;	// 16/32 indices
	GraphicsO_3D* m_device;
};

class BufferData
{
public:
	CTOR BufferData()
	{
		m_vertexOffsetInBytes = 0;
		m_indexOffset = 0;
	}

	VertexBuffer m_vertexBuffer;
	IndexBuffer m_indexBuffer;

	int m_vertexOffsetInBytes;
	int m_indexOffset;

	uint8* m_bufferedVertexBufferData;
	uint8* m_bufferedIndexBufferData;
};

class GfxExt GraphicsI : public Object
{
public:

//	virtual void Present() abstract;

	virtual void Shutdown() = 0;
//	virtual bool WindowResized() = 0;

	virtual void BeginDraw() = 0;
	virtual void EndDraw() = 0;

	virtual IDirect3DDevice9* GetD3D9Device() = 0;
	virtual CGcontext GetCGContext() = 0;
	virtual int cgGetLatestProfile(unsigned int type) = 0;

	virtual void Viewport(int x, int y, int width, int height) = 0;

	virtual void SetClipPlane(int n, const float equation[4]) = 0;
	virtual void EnableClipPlanes(UINT mask) = 0;

	virtual void SetPrimitiveTopology(unsigned int mode) = 0;
	virtual void Draw(UINT first, UINT count) = 0;
	virtual void DrawIndexed(int start, int end, UINT count/*, unsigned int type, int startIndex*/) = 0;
	virtual void DrawUP(UINT count, void* data, int stride) = 0;

	void IndexBufferSubData(IndexBuffer buffer, unsigned int offset, unsigned int size, const void* data);

	virtual IndexBuffer CreateIndexBuffer(unsigned int type, unsigned int size, const void* data) = 0;
	virtual void IndexBufferSubData_(IndexBuffer buffer, unsigned int offset, unsigned int size, const void* data) = 0;

	virtual VertexDeclaration CreateVertexDeclaration(VertexDeclElement* elements, unsigned int count, void* shader) = 0;
	virtual void SetVertexDeclaration(VertexDeclaration vertexDecl) = 0;
	virtual void DeleteVertexDeclaration(VertexDeclaration vertexDecl) = 0;

	virtual void SetMatrixMode(unsigned int mode) = 0;

	virtual void PushMatrix() = 0;
	virtual void PopMatrix() = 0;

	virtual void IdentityTransform() = 0;
	virtual void TranslateTransform(float x, float y, float z) = 0;
	virtual void ScaleTransform(float sx, float sy, float sz) = 0;
	virtual void RotateTransform(float angleDegrees, float x, float y, float z) = 0;
	virtual void MultiplyTransform(const float m[16]) = 0;
	virtual void SetTransform(const float m[16]) = 0;

	void VertexBufferSubData(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data);

	virtual VertexBuffer CreateVertexBuffer(unsigned int size, const void* data, unsigned int bufferUsage) = 0;
	virtual void VertexBufferSubData_(VertexBuffer buffer, unsigned int offset, unsigned int size, const void* data) = 0;

	virtual IndexBuffer GetIndexBuffer(unsigned int* pOffsetInBytes) = 0;
	virtual void SetIndexBuffer(IndexBuffer indexBuffer, unsigned int offsetInBytes) = 0;

	//virtual void SetVertexDeclaration(VertexDeclaration vertexDecl) = 0;
	virtual void SetVertexBuffer(UINT stream, VertexBuffer vertexBuffer, UINT byteOffset, UINT stride) = 0;

	virtual void Enable(unsigned int cap) = 0;
	virtual void Disable(unsigned int cap) = 0;

	virtual void Clear(uint32 mask) = 0;
	virtual void DepthMask(bool mask) = 0;

	virtual Texture CreateTexture1D(int level, int internalformat, int width, int border, unsigned int format, unsigned int type, const void *pixels) = 0;
	virtual Texture CreateTexture2D(int level, int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void *pixels) = 0;

	virtual void SetTexture(int stage, Texture texture) = 0;

	virtual void GetFloatv(unsigned int pname, float* params) = 0;

	// CG
	virtual void cgBindProgram(CGprogram cgProgram) = 0;
	virtual void cgLoadProgram(CGprogram cgProgram) = 0;

	RenderTarget* m_currentRenderTarget;
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

typedef uint32 ARGB;

class GfxExt Color
{
public:

	enum
	{
		Transparent = 0x00000000,
		Black = 0xFF000000,
		White = 0xFFFFFFFF,
		Red = 0xFFFF0000,
		Green = 0xFF00FF00,
		Blue = 0xFF0000FF,
		Yellow = 0xFFFFFF00,
	};

	inline CTOR Color() : Argb(0)
	{
	}

	inline CTOR Color(ARGB argb) : Argb(argb)
	{
	}

	inline CTOR Color(uint8 r, uint8 g, uint8 b)
	{
		Argb = MakeARGB(255, r, g, b);
	}
	
	inline CTOR Color(uint8 a, uint8 r, uint8 g, uint8 b)
	{
		Argb = MakeARGB(a, r, g, b);
	}
	
	inline ARGB GetValue() const
	{
		return Argb;
	}

	inline void SetValue(ARGB argb)
	{
		Argb = argb;
	}
	
	inline uint8 GetA() const
	{
		return (uint8)(Argb>>24);
	}

	inline uint8 GetAlpha() const
	{
		return (uint8)(Argb>>24);
	}

	inline uint8 GetR() const
	{
		return (uint8)(Argb>>16);
	}

	inline uint8 GetRed() const
	{
		return (uint8)(Argb>>16);
	}

	inline uint8 GetG() const
	{
		return (uint8)(Argb>>8);
	}

	inline uint8 GetGreen() const
	{
		return (uint8)(Argb>>8);
	}

	inline uint8 GetB() const
	{
		return (uint8)(Argb);
	}

	inline uint8 GetBlue() const
	{
		return (uint8)(Argb);
	}

	inline static ARGB MakeARGB(uint8 a, uint8 r, uint8 g, uint b)
	{
		return ((uint32)a<<24) | ((uint32)r<<16) | ((uint32)g<<8) | ((uint32)b);
	}

	inline bool operator == (Color other) const
	{
		return Argb == other.Argb;
	}

	/*
#if WIN32
	inline static ARGB FromCOLORREF(DWORD rgb)
	{
		return MakeARGB(255, GetRValue(rgb), GetGValue(rgb), GetBValue(rgb));
	}
#endif
	*/

	/*
	inline static ARGB FromHLS(float h, float l, float s)
	{
		hls_to_rgb(&h, &l, &s);
		return MakeARGB(255, (uint8)(h*255), (uint8)(l*255), (uint8)(s*255));
	}
	*/

protected:

	ARGB Argb;
};

}	// Graphics
}	// System

#include "Bitmap.h"
#include "Direct3D9.h"
#include "Direct3D10.h"
//#include "Direct3D11.h"
#include "OpenGL.h"
#include "wmf.h"

#endif // System_Graphics_h
