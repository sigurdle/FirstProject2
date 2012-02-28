#include "stdafx.h"
#include "X3D2.h"
#include "ShaderPart.h"

#include <windows.h>
//#include <d3d9.h>
//#include <D3dx9math.h>
//#define D3D_MODELVIEW	D3DTS_WORLD

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "Graphics/openglext.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <Cg/cgD3D9.h>

namespace System
{
namespace x3d
{

X3DFieldDefinition* ShaderPartFields[] =
{
	&X3DFieldDefinition("metadata", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),

	&X3DFieldDefinition("type", FieldType_SFString, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("url", FieldType_MFURL, SAIFieldAccess_inputOutput,-1),

	/*
	SFNode   [in,out] metadata NULL       [X3DMetadataObject]
	MFString [in,out] url      []         [URI]
	SFString []       type     "VERTEX"   ["VERTEX"|"FRAGMENT"]
	*/
};

NodeType ShaderPart::s_nodeType("ShaderPart", typeid(ShaderPart), ShaderPartFields, _countof(ShaderPartFields));

ShaderPart::ShaderPart() : X3DNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_type = static_cast<SFString*>(getField(WSTR("type")));
	m_url = dynamic_cast<MFURL*>(getField(WSTR("url")));
	VERIFY(m_url);

	// Set defaults
	m_type->m_value = WSTR("VERTEX");

	m_device = NULL;

	m_glShader = 0;
	m_compiled = false;
}

ShaderPart::~ShaderPart()
{
	if (m_cgProgram)
	{
		cgDestroyProgram(m_cgProgram);
		m_cgProgram = NULL;
	}
}

bool ShaderPart::CreateShader(StringIn language, Graphics::Graphics3D* p3D/*, CGcontext cgContext*/)
{
	ASSERT(0);
#if 0
	m_device = p3D;//->m_pGraphics->m_device;

	if (language == L"GLSL")
	{
		Graphics::OpenGL_I* pGL = (Graphics::OpenGL_I*)p3D->m_pGraphics->m_device;

		GLenum type;

		if (m_type->getValue() == L"VERTEX")
			type = GL_VERTEX_SHADER;
		else if (m_type->getValue() == L"FRAGMENT")
			type = GL_FRAGMENT_SHADER;
		else
			return false;

		Net::UrlBinding file;
		_Ptr<IO::Stream> stream = file.BindToObject(m_url->m_items[0].string, NULL);
		if (stream != null)
		{
			int filesize = (int)stream->GetSize();
			if (filesize < 0) return false;

			char* source = new char[filesize+1];
			stream->Read(source, filesize);
			source[filesize] = 0;

			pGL->MakeCurrent();

			m_glShader = pGL->m_glprocs->glCreateShader(type);
			ASSERT(::glGetError() == 0);

			if (m_glShader)
			{
				pGL->m_glprocs->glShaderSource(m_glShader, 1/*number of strings*/, (const char**)&source, &filesize);
				ASSERT(::glGetError() == 0);

				pGL->m_glprocs->glCompileShader(m_glShader);
			//	ASSERT(::glGetError() == 0);

				GLint compiled;
				pGL->m_glprocs->glGetShaderiv(m_glShader, GL_COMPILE_STATUS, &compiled);

				if (!compiled)
				{
					m_compiled = false;
				//	p3D->m_pG->m_pGraphics->m_glprocs->m_glShader
					return false;
				}
				m_compiled = true;

				return true;
			}
		}
	}
#if 0
	else if (*language == L"CG")
	{
		if (cgContext == NULL)
		{
			throw std::exception("non-null CGcontext required");
		}

		CGprofile profile;

		if (*m_type->getValue() == L"VERTEX")
		{
			// TODO
			profile = CG_PROFILE_ARBVP1;
		}
		else if (*m_type->getValue() == L"FRAGMENT")
		{
			// TODO
			profile = CG_PROFILE_ARBFP1;
		}
		else
			return false;

		UrlBinding file;
		IO::ISequentialByteStream* stream = file.BindToObject(m_url->m_items[0].string, NULL);
		if (stream)
		{
			int filesize = (int)stream->GetSize();
			if (filesize < 0) return false;

			char* source = new char[filesize+1];
			stream->Read(source, filesize);
			source[filesize] = 0;

			const char* entry = NULL;	// Defaults to 'main'
			const char** args = NULL;

			m_cgProgram = cgCreateProgram(cgContext, 
				CG_SOURCE,
				source,//program,
				profile,
				entry,
				args);
		}
	}
#endif
#endif
	return false;
}

}	// x3d
}	// System
