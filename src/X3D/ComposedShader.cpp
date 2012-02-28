#include "stdafx.h"
#include "X3D2.h"
#include "ComposedShader.h"
#include "ShaderPart.h"

#include <windows.h>
//#include <d3d9.h>
//#include <D3dx9math.h>
//#define D3D_MODELVIEW	D3DTS_WORLD

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
//#include "../Draw/opengl.h"
#include "Graphics/openglext.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <Cg/cgD3D9.h>

namespace System
{
namespace x3d
{

X3DFieldDefinition* ComposedShaderFields[] =
{
	// X3DShaderNode
	&X3DFieldDefinition("activate", FieldType_SFBool, SAIFieldAccess_inputOnly,-1),
	&X3DFieldDefinition("isSelected", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("isValid", FieldType_SFBool, SAIFieldAccess_outputOnly,-1),
	&X3DFieldDefinition("language", FieldType_SFString, SAIFieldAccess_initializeOnly,-1),

	// ComposedShader
	&X3DFieldDefinition("parts", FieldType_MFNode, SAIFieldAccess_inputOutput,-1),
/*
  SFBool    [in]     activate
  SFNode    [in,out] metadata   NULL [X3DMetadataObject]
  MFNode    [in,out] parts      []   [ShaderPart]
  SFBool    [out]    isSelected
  SFBool    [out]    isValid
  SFString  []       language   ""  

  # And any number of:
  fieldType []       fieldName
  fieldType [in]     fieldName
  fieldType [out]    fieldName
  fieldType [in,out] fieldName
  */
};

NodeType ComposedShader::s_nodeType(WSTR("ComposedShader"), typeid(ComposedShader), ComposedShaderFields, _countof(ComposedShaderFields));

ComposedShader::ComposedShader() : X3DShaderNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_parts = static_cast<MFNode*>(getField(WSTR("parts")));

	m_glProgram = 0;
	m_linked = false;
}

ComposedShader::~ComposedShader()
{
	/*
	if (m_cgContext)
	{
		cgDestroyContext(m_cgContext);
		m_cgContext = NULL;
	}
	*/
}

bool ComposedShader::CreateShader(Gui::ImmediateRenderContext* p3D)
{
//	LDraw::Graphics3DImmediate* p3D = (LDraw::Graphics3DImmediate*)p3d;

	ASSERT(0);
#if 0

	m_device = p3D;

	LDraw::OpenGL_I* pGL = dynamic_cast<LDraw::OpenGL_I*>(p3D->m_pGraphics->m_device);

	if (getLanguage() == L"GLSL")
	{
		if (m_glProgram != 0)	// Already created
			return true;

		if (pGL->m_glprocs->glCreateProgram == NULL)
			return false;

		pGL->MakeCurrent();

		m_glProgram = pGL->m_glprocs->glCreateProgram();
		if (m_glProgram == 0)
			return false;

		ASSERT(::glGetError() == 0);
	}
	/*
	else if (*getLanguage() == L"CG")
	{

		if (m_cgContext != NULL)	// Already created
			return true;

		m_cgContext = cgCreateContext();

		if (m_cgContext == NULL)
			return false;
	}
	*/
	else
		return false;

	unsigned int nparts = m_parts->get_size();
	for (unsigned int npart = 0; npart < nparts; npart++)
	{
		X3DNode* node = m_parts->get1Value(npart);

		ShaderPart* part = dynamic_cast<ShaderPart*>(node);
		if (part)
		{
			bool success = part->CreateShader(getLanguage(), p3D);
			if (!success)
				return false;

			if (m_glProgram)
			{
				pGL->m_glprocs->glAttachShader(m_glProgram, part->getGLShader());
				ASSERT(::glGetError() == 0);
			}
		}
	}

	if (m_glProgram)
	{
		pGL->m_glprocs->glLinkProgram(m_glProgram);
		ASSERT(::glGetError() == 0);

		GLint linked;
		pGL->m_glprocs->glGetProgramiv(m_glProgram, GL_LINK_STATUS, &linked);
		if (linked)
		{
			m_linked = true;
			return true;
		}
		else
		{
			m_linked = false;
			return false;
		}
	}
	/*
	else if (m_cgContext)
	{
	}
	*/
#endif
	return false;
}

void ComposedShader::Begin(X3DDrawContext* p3DX, UINT* nPasses)
{
	if (nPasses == NULL) throw std::exception("null pointer");

	*nPasses = 1;
}

void ComposedShader::End(X3DDrawContext* p3DX)
{
}

void ComposedShader::BeginPass(X3DDrawContext* p3DX, UINT nPass)
{
	Graphics::OpenGL_I* pGL = p3DX->m_renderContext->m_rt->m_opengl;
	//Graphics::OpenGL_I* pGL = dynamic_cast<Graphics::OpenGL_I*>(p3DX->m_pGraphics3D->m_pGraphics->m_device);

	if (m_glProgram)
	{
		pGL->MakeCurrent();
		pGL->m_glprocs->glUseProgram(m_glProgram);
		ASSERT(::glGetError() == 0);
	}
#if 0
	else if (m_cgContext)
	{
		unsigned int nparts = m_parts->get_size();
		for (int npart = 0; npart < nparts; npart++)
		{
			X3DNode* node = m_parts->get1Value(npart);

			ShaderPart* part = dynamic_cast<ShaderPart*>(node);
			if (part)
			{
				p3D->m_pG->m_pGraphics->cgLoadProgram(part->GetCGProgram());
				p3D->m_pG->m_pGraphics->cgBindProgram(part->GetCGProgram());

				/*
				if (p3D->m_pG->m_pGraphics->m_d3dDevice)
				{
					cgD3D9LoadProgram(part->GetCGProgram(), CG_FALSE, 0);
				}
				else
				{
					cgGLLoadProgram(part->GetCGProgram());
				}
				*/
			}
		}
	}
#endif

	p3DX->m_shader = this;
}

void ComposedShader::EndPass(X3DDrawContext* ctx)
{
//	LDraw::Graphics3DImmediate* p3D = (LDraw::Graphics3DImmediate*)p3DX->m_pGraphics3D;

//	Graphics::OpenGL_I* pGL = (Graphics::OpenGL_I*)ctx->m_pGraphics3D->m_pGraphics->m_device;
	Graphics::OpenGL_I* pGL = ctx->m_renderContext->m_rt->m_opengl;

	pGL->m_glprocs->glUseProgram(0);
	ctx->m_shader = NULL;
}

/*
void ComposedShader::Apply(X3DDrawContext* p3DX)
{
	ASSERT(0);
}
*/

}	// x3d
}
