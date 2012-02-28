#include "stdafx.h"
#include "X3D2.h"
#include "ShaderProgram.h"

#include <d3d9.h>
#include <D3dx9math.h>

#define INITGUID

#ifdef __LERSTAD__

typedef 
enum D3D_PRIMITIVE
    {	D3D_PRIMITIVE_UNDEFINED	= 0,
	D3D_PRIMITIVE_POINT	= 1,
	D3D_PRIMITIVE_LINE	= 2,
	D3D_PRIMITIVE_TRIANGLE	= 3,
	D3D_PRIMITIVE_LINE_ADJ	= 6,
	D3D_PRIMITIVE_TRIANGLE_ADJ	= 7,
	D3D_PRIMITIVE_1_CONTROL_POINT_PATCH	= 8,
	D3D_PRIMITIVE_2_CONTROL_POINT_PATCH	= 9,
	D3D_PRIMITIVE_3_CONTROL_POINT_PATCH	= 10,
	D3D_PRIMITIVE_4_CONTROL_POINT_PATCH	= 11,
	D3D_PRIMITIVE_5_CONTROL_POINT_PATCH	= 12,
	D3D_PRIMITIVE_6_CONTROL_POINT_PATCH	= 13,
	D3D_PRIMITIVE_7_CONTROL_POINT_PATCH	= 14,
	D3D_PRIMITIVE_8_CONTROL_POINT_PATCH	= 15,
	D3D_PRIMITIVE_9_CONTROL_POINT_PATCH	= 16,
	D3D_PRIMITIVE_10_CONTROL_POINT_PATCH	= 17,
	D3D_PRIMITIVE_11_CONTROL_POINT_PATCH	= 18,
	D3D_PRIMITIVE_12_CONTROL_POINT_PATCH	= 19,
	D3D_PRIMITIVE_13_CONTROL_POINT_PATCH	= 20,
	D3D_PRIMITIVE_14_CONTROL_POINT_PATCH	= 21,
	D3D_PRIMITIVE_15_CONTROL_POINT_PATCH	= 22,
	D3D_PRIMITIVE_16_CONTROL_POINT_PATCH	= 23,
	D3D_PRIMITIVE_17_CONTROL_POINT_PATCH	= 24,
	D3D_PRIMITIVE_18_CONTROL_POINT_PATCH	= 25,
	D3D_PRIMITIVE_19_CONTROL_POINT_PATCH	= 26,
	D3D_PRIMITIVE_20_CONTROL_POINT_PATCH	= 28,
	D3D_PRIMITIVE_21_CONTROL_POINT_PATCH	= 29,
	D3D_PRIMITIVE_22_CONTROL_POINT_PATCH	= 30,
	D3D_PRIMITIVE_23_CONTROL_POINT_PATCH	= 31,
	D3D_PRIMITIVE_24_CONTROL_POINT_PATCH	= 32,
	D3D_PRIMITIVE_25_CONTROL_POINT_PATCH	= 33,
	D3D_PRIMITIVE_26_CONTROL_POINT_PATCH	= 34,
	D3D_PRIMITIVE_27_CONTROL_POINT_PATCH	= 35,
	D3D_PRIMITIVE_28_CONTROL_POINT_PATCH	= 36,
	D3D_PRIMITIVE_29_CONTROL_POINT_PATCH	= 37,
	D3D_PRIMITIVE_30_CONTROL_POINT_PATCH	= 38,
	D3D_PRIMITIVE_31_CONTROL_POINT_PATCH	= 39,
	D3D_PRIMITIVE_32_CONTROL_POINT_PATCH	= 40,
	D3D10_PRIMITIVE_UNDEFINED	= D3D_PRIMITIVE_UNDEFINED,
	D3D10_PRIMITIVE_POINT	= D3D_PRIMITIVE_POINT,
	D3D10_PRIMITIVE_LINE	= D3D_PRIMITIVE_LINE,
	D3D10_PRIMITIVE_TRIANGLE	= D3D_PRIMITIVE_TRIANGLE,
	D3D10_PRIMITIVE_LINE_ADJ	= D3D_PRIMITIVE_LINE_ADJ,
	D3D10_PRIMITIVE_TRIANGLE_ADJ	= D3D_PRIMITIVE_TRIANGLE_ADJ,
	D3D11_PRIMITIVE_UNDEFINED	= D3D_PRIMITIVE_UNDEFINED,
	D3D11_PRIMITIVE_POINT	= D3D_PRIMITIVE_POINT,
	D3D11_PRIMITIVE_LINE	= D3D_PRIMITIVE_LINE,
	D3D11_PRIMITIVE_TRIANGLE	= D3D_PRIMITIVE_TRIANGLE,
	D3D11_PRIMITIVE_LINE_ADJ	= D3D_PRIMITIVE_LINE_ADJ,
	D3D11_PRIMITIVE_TRIANGLE_ADJ	= D3D_PRIMITIVE_TRIANGLE_ADJ,
	D3D11_PRIMITIVE_1_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_1_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_2_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_2_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_3_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_3_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_4_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_4_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_5_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_5_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_6_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_6_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_7_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_7_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_8_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_8_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_9_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_9_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_10_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_10_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_11_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_11_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_12_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_12_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_13_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_13_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_14_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_14_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_15_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_15_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_16_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_16_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_17_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_17_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_18_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_18_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_19_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_19_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_20_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_20_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_21_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_21_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_22_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_22_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_23_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_23_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_24_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_24_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_25_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_25_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_26_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_26_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_27_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_27_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_28_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_28_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_29_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_29_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_30_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_30_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_31_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_31_CONTROL_POINT_PATCH,
	D3D11_PRIMITIVE_32_CONTROL_POINT_PATCH	= D3D_PRIMITIVE_32_CONTROL_POINT_PATCH
    } 	D3D_PRIMITIVE;

#endif

typedef D3D_PRIMITIVE D3D11_PRIMITIVE;

#include <D3Dcompiler.h>

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <Cg/cgD3D9.h>

#include "ImageTexture.h"	// TODO remove

/*
#define DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) EXTERN_C const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }

DEFINE_GUID(IID_ID3D11ShaderReflection, 
0x17f27486, 0xa342, 0x4d10, 0x88, 0x42, 0xab, 0x08, 0x74, 0xe7, 0xf6, 0x70);
*/

namespace System
{
namespace x3d
{

NodeType* ShaderProgram::nodeType(GetNodeType());

NodeType* ShaderProgram::GetNodeType()
{
	static X3DFieldDefinition type("type", FieldType_SFString, SAIFieldAccess_initializeOnly, offsetof(ShaderProgram, m_type));
	static X3DFieldDefinition url("url", FieldType_MFURL, SAIFieldAccess_inputOutput, offsetof(ShaderProgram, m_url));

	static X3DFieldDefinition* fields[] =
	{
		&type,
		&url,

		/*
		SFNode    [in,out] metadata  NULL         [X3DMetadataObject]
		MFString  [in,out] url       []           [URI]
		SFString  []       type      "VERTEX"     ["VERTEX"|"FRAGMENT"]

		# And any number of:
		fieldType [in]     fieldName
		fieldType [in,out] fieldName initialValue
		fieldType [out]    fieldName
		fieldType []       fieldName initialValue
		*/
	};

	static NodeType nodeType(WSTR("ShaderProgram"), typeid(ShaderProgram), fields, _countof(fields), X3DNode::GetNodeType());
	return &nodeType;
}

ShaderProgram::ShaderProgram() : X3DNode(GetNodeType())
{
	// Set defaults
	m_type->m_value = WSTR("VERTEX");

	m_shaderType = ShaderType_None;
}

ShaderProgram::~ShaderProgram()
{
	if (m_cgProgram)
	{
		cgDestroyProgram(m_cgProgram);
		ASSERT(cgGetError() == 0);
		m_cgProgram = NULL;
	}
}

_Ptr<IO::TextReader> BindToObject(StringIn uri, Net::IBindCallback* callback)
{
	if (uri.LeftOf(7) == "http://")
	{
		ASSERT(0);
		return NULL;
#if 0
		DownloadDocument* downloader = new DownloadDocument;
		downloader->AddRef();
		downloader->m_callback = callback;

		downloader->m_url = uri;

		const char* p = url->c_str() + 7;
		const char* p2 = strchr(p, '/');
		if (p2 == NULL)
		{
			downloader->m_server = new StringA(string_copy(p));
		}
		else
		{
			downloader->m_server = new StringA(string_copy(p, p2-p));
		}

#if WIN32
		downloader->m_hEvent = CreateEvent(NULL, false, false, NULL);

		DWORD threadId;
		::CreateThread(NULL, 0, DownloadDocument::DownloadDocumentThread, (LPVOID)downloader, 0, &threadId);
#else
		ASSERT(0);
#endif

		return downloader;
#endif
	}
	// TODO
	else if (uri.LeftOf(9) == "inline://")
	{
		VERIFY(callback == NULL);	// TODO

		return new IO::StringReader(String(uri.RightOf(9)));
	}
	else
	{
		String localfilename;

	//	const char* p;
		if (uri.LeftOf(7) == "file://")
		{
			localfilename = uri.RightOf(7);
		}
		else
		{
			localfilename = uri;
		}

#if 0
		BufferImp<char> buffer;
		StringBuilderA strbuilder(&buffer);
		while (*p)
		{
			if (*p == '%')
			{
				// TODO improve
				p += 3;
				// 20 is space
				strbuilder << ' ';
			}
			else
			{
				strbuilder << *p++;
			}
		}
		StringA* localfilename = buffer.DetachToString();
#endif

		if (callback) callback->OnObjectAvailable(NULL, uri);

		IO::FileStream* fs = new IO::FileStream(localfilename, IO::FileMode_Open, IO::FileAccess_Read);

		// TODO
	//	if (callback) callback->OnDataAvailable(fs.GetSize(), file);
	//	if (callback) callback->OnDone();

		return new IO::StreamReader(fs);
	}

	return NULL;
}

void ShaderProgram::AddField(X3DField* x3dfield)
{
//	// TODO, insert sorted
//	m_fields.Add(x3dfield);

	m_addfields.Add(x3dfield);
}

uint ShaderProgram::getFieldCount()
{
	return X3DNode::getFieldCount() + m_addfields.size();
}

X3DField* ShaderProgram::getField(uint index)
{
	uint bcount = X3DNode::getFieldCount();
	if (index < bcount)
	{
		return X3DNode::getField(index);
	}

	index -= bcount;
	if (index >= m_addfields.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_addfields[index];
}

X3DField* ShaderProgram::getField(StringIn name)
{
	X3DField* field = X3DNode::getField(name);
	if (field)
	{
		return field;
	}

	for (uint i = 0; i < m_addfields.size(); ++i)
	{
		if (m_addfields[i]->m_fieldName == name)
			return m_addfields[i];
	}

	return NULL;
}

bool ShaderProgram::CreateShader(StringIn language, Graphics::RenderTarget* p3D)
{
//	LDraw::Graphics3DImmediate* p3D = (LDraw::Graphics3DImmediate*)p3d;

	if (language == L"HLSL")
	{
		ASSERT(0);
#if 0
		IDirect3DDevice9* d3dDevice = p3D->m_device->GetD3D9Device();
		if (d3dDevice == NULL)
			return false;

		if (m_shaderType == ShaderType_None)
		{
			HRESULT hr;

			if (m_type->getValue() == L"VERTEX")
			{
				m_shaderType = ShaderType_Vertex;

				LPCSTR vertexShaderProfile = D3DXGetVertexShaderProfile(d3dDevice);
				ID3DXBuffer* shaderBuffer = NULL;
				ID3DXBuffer* errorMsgsBuffer = NULL;
				CStringw filename(m_url->m_items[0].string);
				hr = D3DXCompileShaderFromFileW(filename/*"C:/mmstudio/vertex_shader.shader"*/, NULL, NULL, "main", vertexShaderProfile, 0, &shaderBuffer, &errorMsgsBuffer, &m_constantTable);
				if (FAILED(hr))
				{
					if (errorMsgsBuffer)
					{
						char* str = (char*)errorMsgsBuffer->GetBufferPointer();
						// TODO, some more cleanup
						return false;
						//MessageBeep(-1);
					}
				}
				if (errorMsgsBuffer)
				{
					errorMsgsBuffer->Release();
				}

				ASSERT(SUCCEEDED(hr));

				if (shaderBuffer)
				{
					hr = d3dDevice->CreateVertexShader((const DWORD*)shaderBuffer->GetBufferPointer(), &m_hlslShader.vertex);
					ASSERT(SUCCEEDED(hr));
					shaderBuffer->Release();
				}
			}
			else if (m_type->getValue() == L"FRAGMENT")
			{
				m_shaderType = ShaderType_Fragment;

				LPCSTR pixelShaderProfile = D3DXGetPixelShaderProfile(d3dDevice);

				ID3DXBuffer* shaderBuffer = NULL;
				ID3DXBuffer* errorMsgsBuffer = NULL;
				CStringw filename(m_url->m_items[0].string);
				hr = D3DXCompileShaderFromFileW(filename.c_str()/*"C:/mmstudio/vertex_shader.shader"*/, NULL, NULL, "main", pixelShaderProfile, 0, &shaderBuffer, &errorMsgsBuffer, &m_constantTable);
				if (FAILED(hr))
				{
					if (errorMsgsBuffer)
					{
						char* str = (char*)errorMsgsBuffer->GetBufferPointer();
					//	MessageBeep(-1);
						// TODO, some more cleanup
						return false;
					}
				}
				if (errorMsgsBuffer)
				{
					errorMsgsBuffer->Release();
				}

				ASSERT(SUCCEEDED(hr));

				if (shaderBuffer)
				{
					hr = d3dDevice->CreatePixelShader((const DWORD*)shaderBuffer->GetBufferPointer(), &m_hlslShader.pixel);
					ASSERT(SUCCEEDED(hr));
					shaderBuffer->Release();
				}
			}
		}
#endif
		return true;
	}
	else if (language == L"HLSL_10")
	{
		if (m_shaderType == ShaderType_None)
		{
			LPCSTR profile;
			HRESULT hr;

			if (m_type->getValue() == L"VERTEX")
			{
				m_shaderType = ShaderType_Vertex;
				profile = "vs_4_0";
			}
			else if (m_type->getValue() == L"FRAGMENT")
			{
				m_shaderType = ShaderType_Fragment;
				profile = "ps_4_0";
			}
			else
				return false;

			ID3D10Blob* pShader;

			Net::UrlBinding file;
			_Ptr<IO::TextReader> stream = BindToObject(m_url->get1Value(0)/*.string*/, NULL);
			if (stream != NULL)
			{
			//	int filesize = (int)stream->GetSize();
			//	if (filesize < 0) return false;

			//	char* source = new char[filesize+1];

				char source[8001];
				int filesize = stream->ReadChars(source, 8000);
				source[filesize] = 0;

				ID3D10Blob* pErrorMsgs;
				HRESULT hresult;

				hr = D3DX10CompileFromMemory(
				  source,
				  filesize,
				  NULL,//LPCSTR pFileName,
				  NULL,//CONST D3D10_SHADER_MACRO *pDefines,
				  NULL,//LPD3D10INCLUDE pInclude,
				  "main",//LPCSTR pFunctionName,
				  profile,
				  0,//UINT Flags1,
				  0,//UINT Flags2,
				  NULL,//ID3DX11ThreadPump *pPump,
				  &pShader,
				  &pErrorMsgs,
				  &hresult
				);
				if (FAILED(hr))
				{
					String errormsg;
					if (pErrorMsgs)
					{
						errormsg = (char*)pErrorMsgs->GetBufferPointer();
						pErrorMsgs->Release();
					}

					return false;
				}

				ID3D10ShaderReflection* pReflection;
				hr = D3DReflect(pShader->GetBufferPointer(), pShader->GetBufferSize(), IID_ID3D10ShaderReflection, reinterpret_cast<void**>(&pReflection));
				if (FAILED(hr))
				{
					return false;
				}

				ASSERT(pReflection);

				D3D10_SHADER_DESC shaderDesc;
				pReflection->GetDesc(&shaderDesc);

				/*
				D3D10_INPUT_ELEMENT_DESC inputDesc[64] = {0};

				for (uint i = 0; i < shaderDesc.InputParameters; ++i)
				{
					D3D11_SIGNATURE_PARAMETER_DESC desc;
					pReflection->GetInputParameterDesc(i, &desc);

					inputDesc[i].SemanticName = desc.SemanticName;   // Name of the semantic
					inputDesc[i].SemanticIndex = desc.SemanticIndex;  // Index of the semantic
					if (desc.ComponentType == D3D10_REGISTER_COMPONENT_FLOAT32)
					{
						switch (desc.Mask)
						{
						case 15:	inputDesc[i].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;	break;
						case 7:	inputDesc[i].Format = DXGI_FORMAT_R32G32B32_FLOAT;	break;
						case 3:	inputDesc[i].Format = DXGI_FORMAT_R32G32_FLOAT;	break;
						case 1:	inputDesc[i].Format = DXGI_FORMAT_R32_FLOAT;	break;
						}
					}
					else if (desc.ComponentType == D3D10_REGISTER_COMPONENT_SINT32)
					{
						ASSERT(0);
					}
					else if (desc.ComponentType == D3D10_REGISTER_COMPONENT_UINT32)
					{
						ASSERT(0);
					}
					else
					{
						ASSERT(0);
					}
					
					inputDesc[i].InputSlot = 0;
					inputDesc[i].InputSlotClass = D3D10_INPUT_PER_VERTEX_DATA;

				//	inputDesc[i].Register = desc.Register;       // Number of member variables
				//	inputDesc[i].SystemValueType = desc.SystemValueType;// A predefined system value, or D3D10_NAME_UNDEFINED if not applicable
				//	inputDesc[i].ComponentType = desc.ComponentType;// Scalar type (e.g. uint, float, etc.)
				//	inputDesc[i].Mask = desc.Mask;           // Mask to indicate which components of the register
																	// are used (combination of D3D10_COMPONENT_MASK values)
				//	inputDesc[i].ReadWriteMask = desc.ReadWriteMask;  // Mask to indicate whether a given component is 
																	// never written (if this is an output signature) or
																	// always read (if this is an input signature).
																	// (combination of D3D10_COMPONENT_MASK values)
				}
				*/

				for (uint n = 0; n < shaderDesc.BoundResources; ++n)
				{
					D3D10_SHADER_INPUT_BIND_DESC desc;
					pReflection->GetResourceBindingDesc(n, &desc);

					if (desc.Type == D3D10_SIT_TEXTURE)
					{
						m_variables[desc.Name] = BufferVar(-2, desc.BindPoint, desc.BindCount);
					}
				}
				m_resources.resize(shaderDesc.BoundResources);

				for (uint nbuffer = 0; nbuffer < shaderDesc.ConstantBuffers; ++nbuffer)
				{
					ID3D10ShaderReflectionConstantBuffer* cBuffer = pReflection->GetConstantBufferByIndex(nbuffer);
					D3D10_SHADER_BUFFER_DESC bufferDesc;
					cBuffer->GetDesc(&bufferDesc);

				//	byte* bufferData = new byte[bufferDesc.Size];

					ID3D10Buffer* buffer;
					
					// Create a constant buffer
					D3D10_BUFFER_DESC cbDesc;
					cbDesc.ByteWidth = bufferDesc.Size;
					cbDesc.Usage = D3D10_USAGE_DYNAMIC;
					cbDesc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
					cbDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
					cbDesc.MiscFlags = 0;
					p3D->m_d3d10->m_device->CreateBuffer(&cbDesc, nullptr, &buffer);

					//// Fill buffer with default values
					for (uint n = 0; n < bufferDesc.Variables; ++n)
					{
						ID3D10ShaderReflectionVariable* var = cBuffer->GetVariableByIndex(n);
						D3D10_SHADER_VARIABLE_DESC vardesc;
						var->GetDesc(&vardesc);

						m_variables[vardesc.Name] = BufferVar(nbuffer, vardesc.StartOffset, vardesc.Size);

						/*
						if (vardesc.DefaultValue)
						{
							memcpy(bufferData + vardesc.StartOffset, vardesc.DefaultValue, vardesc.Size);
						}
						*/
					}

					m_buffers.push_back(buffer);
					m_bufferData.push_back(nullptr);

				//	ID3D11ShaderReflectionVariable* var;
					D3D10_SHADER_VARIABLE_DESC vardesc;

					if (SUCCEEDED(cBuffer->GetVariableByName("view")->GetDesc(&vardesc)) && vardesc.Size == 16*4)
					{
						m_view.m_nbuffer = nbuffer;
						m_view.m_offset = vardesc.StartOffset;
					}
					else
						m_view.m_nbuffer = -1;

					if (SUCCEEDED(cBuffer->GetVariableByName("model")->GetDesc(&vardesc)) && vardesc.Size == 16*4)
					{
						m_model.m_nbuffer = nbuffer;
						m_model.m_offset = vardesc.StartOffset;
					}
					else
						m_model.m_nbuffer = -1;

					if (SUCCEEDED(cBuffer->GetVariableByName("projection")->GetDesc(&vardesc)) && vardesc.Size == 16*4)
					{
						m_projection.m_nbuffer = nbuffer;
						m_projection.m_offset = vardesc.StartOffset;
					}
					else
						m_projection.m_nbuffer = -1;

					if (SUCCEEDED(cBuffer->GetVariableByName("modelView")->GetDesc(&vardesc)) && vardesc.Size == 16*4)
					{
						m_modelView.m_nbuffer = nbuffer;
						m_modelView.m_offset = vardesc.StartOffset;
					}
					else
						m_modelView.m_nbuffer = -1;

					if (SUCCEEDED(cBuffer->GetVariableByName("modelViewProjection")->GetDesc(&vardesc)) && vardesc.Size == 16*4)
					{
						m_modelViewProjection.m_nbuffer = nbuffer;
						m_modelViewProjection.m_offset = vardesc.StartOffset;
					}
					else
						m_modelViewProjection.m_nbuffer = -1;

					if (SUCCEEDED(cBuffer->GetVariableByName("viewPosition")->GetDesc(&vardesc)) && vardesc.Size == 16*4)
					{
						m_viewPosition.m_nbuffer = nbuffer;
						m_viewPosition.m_offset = vardesc.StartOffset;
					}
					else
						m_viewPosition.m_nbuffer = -1;
				}
				
				if (m_shaderType == ShaderType_Vertex)
				{
					hr = p3D->m_d3d10->m_device->CreateVertexShader((DWORD*)pShader->GetBufferPointer(),
						pShader->GetBufferSize(), &m_hlsl_10_Shader.vertex);
				}
				else if (m_shaderType == ShaderType_Fragment)
				{
					hr = p3D->m_d3d10->m_device->CreatePixelShader((DWORD*)pShader->GetBufferPointer(),
						pShader->GetBufferSize(), &m_hlsl_10_Shader.pixel);
				}

				pReflection->Release();

			//	pShader->Release();
				m_shaderBlob = pShader;

				if (FAILED(hr))
				{
					return false;
				}
			}
		}

		return true;
	}
	else if (language == L"GLSL")
	{
		ASSERT(0);
	}
	else if (language.LeftOf(3) == L"CG_")
	{
		Graphics::OpenGL_I* pGL = p3D->m_opengl;

		if (language == L"CG_OPENGL_ARB")
		{
			if (m_type->getValue() == L"VERTEX")
				m_cgProfile = CG_PROFILE_ARBVP1;
			else
				m_cgProfile = CG_PROFILE_ARBFP1;
		}
		/*
		else if (*language == L"CG_OPENGL_NV30")
		{
			if (*m_type->getValue() == L"VERTEX")
				m_cgProfile = CG_PROFILE_VP30;
			else
				m_cgProfile = CG_PROFILE_ARBFP1;
		}
		*/
		else if (language == L"CG_D3D_SHADER_3.0")
		{
			if (m_type->getValue() == L"VERTEX")
				m_cgProfile = CG_PROFILE_VS_3_0;
			else
				m_cgProfile = CG_PROFILE_PS_3_0;
		}
		else if (language == L"CG_D3D_SHADER_2.0")
		{
			if (m_type->getValue() == L"VERTEX")
				m_cgProfile = CG_PROFILE_VS_2_0;
			else
				m_cgProfile = CG_PROFILE_PS_2_0;
		}
		/*
		else if (*language == L"CG_D3D_SHADER_1.3")
		{
			if (*m_type->getValue() == L"VERTEX")
				m_cgProfile = CG_PROFILE_VS_1_3;
			else
				m_cgProfile = CG_PROFILE_PS_1_3;
		}
		*/
		else
			return false;

		if (m_type->getValue() == L"VERTEX")
		{
			m_shaderType = ShaderType_Vertex;
		}
		else if (m_type->getValue() == L"FRAGMENT")
		{
			m_shaderType = ShaderType_Fragment;
		}
		else
			return false;

		Net::UrlBinding file;
		IO::Stream* stream = file.BindToObject(m_url->get1Value(0)/*.string*/, nullptr);
		if (stream != nullptr)
		{
			int filesize = (int)stream->GetSize();
			if (filesize < 0) return false;

			char* source = new char[filesize+1];
			stream->Read(source, filesize);
			source[filesize] = 0;

			const char* entry = nullptr;	// Defaults to 'main'
			const char** args = nullptr;

			m_cgProgram = cgCreateProgram(pGL->m_cgContext, 
				CG_SOURCE,
				source,//program,
				(CGprofile)m_cgProfile,
				entry,
				args);

			if (m_cgProgram)
			{
				pGL->cgLoadProgram(m_cgProgram);
				ASSERT(cgGetError() == 0);

				return true;
			}
		}
	}

	return false;
}

void ShaderProgram::ApplyFields(Graphics::RenderTarget* rt)
{
	for (size_t i = 0; i < m_addfields.size(); ++i)
	{
		X3DField* field = m_addfields[i];

		auto it = m_variables.find(field->getFieldName());
		if (it != m_variables.end())
		{
			BufferVar var = it->second;
			if (var.m_nbuffer == -2)
			{
				X3DNode* value = static_cast<SFNode*>(field)->getValue();
				ImageTexture* texture = dynamic_cast<ImageTexture*>(value);
				if (texture)
				{
					texture->CreateTexture(rt);

					if (m_shaderType == ShaderType_Fragment)
					{
						rt->m_d3d10->m_device1->PSSetShaderResources(var.m_offset, 1, &texture->m_bitmap->m_d3d10_shaderResourceView);
					}
				}
			}
			else
			{
				switch (field->getFieldType())
				{
				case FieldType_SFColorRGBA:
					*(Vec4f*)(m_bufferData[var.m_nbuffer] +  var.m_offset) = static_cast<SFColorRGBA*>(field)->getValue();
					break;

				case FieldType_SFVec4f:
					*(Vec4f*)(m_bufferData[var.m_nbuffer] +  var.m_offset) = static_cast<SFVec4f*>(field)->getValue();
					break;

				default:
					raise(Exception("TODO"));
				}
			}
		}
	}
}

void ShaderProgram::Apply(X3DDrawContext* p3DX)
{
	ASSERT(0);
#if 0
	/*
	D3DXMATRIX model;
	D3DXMATRIX view;
	D3DXMATRIX projection;
	D3DXMATRIX modelView;
	D3DXMATRIX modelViewProjection;
//	D3DXVECTOR viewPosition;
*/
	LDraw::Graphics3D* p3D = p3DX->m_pGraphics3D;

	if (m_cgProgram)
	{

		// TODO, MakeCurrent

		if (m_shaderType == ShaderType_Vertex)
		{
			CGparameter modelView = cgGetNamedParameter(m_cgProgram, "modelView");
			CGparameter modelViewProjection = cgGetNamedParameter(m_cgProgram, "modelViewProjection");

			CGparameter modelViewI = cgGetNamedParameter(m_cgProgram, "modelViewI");
			CGparameter modelViewProjectionI = cgGetNamedParameter(m_cgProgram, "modelViewProjectionI");

			CGparameter modelViewT = cgGetNamedParameter(m_cgProgram, "modelViewT");
			CGparameter modelViewProjectionT = cgGetNamedParameter(m_cgProgram, "modelViewProjectionT");

			CGparameter modelViewIT = cgGetNamedParameter(m_cgProgram, "modelViewIT");
			CGparameter modelViewProjectionIT = cgGetNamedParameter(m_cgProgram, "modelViewProjectionIT");

			if (modelView) cgGLSetStateMatrixParameter(modelView, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_IDENTITY);
			if (modelViewProjection) cgGLSetStateMatrixParameter(modelViewProjection, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_IDENTITY);

			if (modelViewI) cgGLSetStateMatrixParameter(modelViewI, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_INVERSE);
			if (modelViewProjectionI) cgGLSetStateMatrixParameter(modelViewProjectionI, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_INVERSE);

			if (modelViewT) cgGLSetStateMatrixParameter(modelViewT, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_TRANSPOSE);
			if (modelViewProjectionT) cgGLSetStateMatrixParameter(modelViewProjectionT, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_TRANSPOSE);

			if (modelViewIT) cgGLSetStateMatrixParameter(modelViewIT, CG_GL_MODELVIEW_MATRIX, CG_GL_MATRIX_INVERSE_TRANSPOSE);
			if (modelViewProjectionIT) cgGLSetStateMatrixParameter(modelViewProjectionIT, CG_GL_MODELVIEW_PROJECTION_MATRIX, CG_GL_MATRIX_INVERSE_TRANSPOSE);
		}
		else
		{
		}

		cgGLEnableProfile((CGprofile)m_cgProfile);
		ASSERT(cgGetError() == 0);
		p3D->m_pGraphics->m_device->cgBindProgram(m_cgProgram);
		ASSERT(cgGetError() == 0);
	}
	else
	{
		IDirect3DDevice9* d3dDevice = p3D->m_pGraphics->m_device->GetD3D9Device();

		HRESULT hr;

		if (m_shaderType == ShaderType_Vertex)
		{
			hr = d3dDevice->SetVertexShader(m_hlslShader.vertex);
			ASSERT(SUCCEEDED(hr));

			hr = m_constantTable->SetMatrix(d3dDevice, "model", (D3DXMATRIX*)(float*)p3DX->m_model);
			hr = m_constantTable->SetMatrix(d3dDevice, "view", (D3DXMATRIX*)(float*)p3DX->m_view);
			hr = m_constantTable->SetMatrix(d3dDevice, "projection", (D3DXMATRIX*)(float*)p3DX->m_projection);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelView", (D3DXMATRIX*)(float*)p3DX->m_modelView);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewProjection", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjection);

			hr = m_constantTable->SetMatrix(d3dDevice, "modelI", (D3DXMATRIX*)(float*)p3DX->m_modelI);
			hr = m_constantTable->SetMatrix(d3dDevice, "viewI", (D3DXMATRIX*)(float*)p3DX->m_viewI);
			hr = m_constantTable->SetMatrix(d3dDevice, "projectionI", (D3DXMATRIX*)(float*)p3DX->m_projectionI);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewI", (D3DXMATRIX*)(float*)p3DX->m_modelViewI);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewProjectionI", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjectionI);

			hr = m_constantTable->SetMatrix(d3dDevice, "modelT", (D3DXMATRIX*)(float*)p3DX->m_modelT);
			hr = m_constantTable->SetMatrix(d3dDevice, "viewT", (D3DXMATRIX*)(float*)p3DX->m_viewT);
			hr = m_constantTable->SetMatrix(d3dDevice, "projectionT", (D3DXMATRIX*)(float*)p3DX->m_projectionT);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewT", (D3DXMATRIX*)(float*)p3DX->m_modelViewT);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewProjectionT", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjectionT);

			hr = m_constantTable->SetMatrix(d3dDevice, "modelIT", (D3DXMATRIX*)(float*)p3DX->m_modelIT);
			hr = m_constantTable->SetMatrix(d3dDevice, "viewIT", (D3DXMATRIX*)(float*)p3DX->m_viewIT);
			hr = m_constantTable->SetMatrix(d3dDevice, "projectionIT", (D3DXMATRIX*)(float*)p3DX->m_projectionIT);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewIT", (D3DXMATRIX*)(float*)p3DX->m_modelViewIT);
			hr = m_constantTable->SetMatrix(d3dDevice, "modelViewProjectionIT", (D3DXMATRIX*)(float*)p3DX->m_modelViewProjectionIT);

			//m_constantTable->SetMatrix(d3dDevice, "viewPosition", &modelView);
		}
		else // if (m_shaderType == ShaderType_Fragment)
		{
			hr = d3dDevice->SetPixelShader(m_hlslShader.pixel);
			ASSERT(SUCCEEDED(hr));
		}
	}
#endif
}

void ShaderProgram::End(X3DDrawContext* p3DX)
{
	if (m_cgProgram)
	{
		cgGLDisableProfile((CGprofile)m_cgProfile);
		ASSERT(cgGetError() == 0);
	}
}

}	// x3d
}	// System
