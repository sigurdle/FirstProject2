#include "stdafx.h"
#include "X3D2.h"
#include "Shape.h"
#include "Appearance.h"

#include "ShaderProgram.h"	// TODO remove
#include "ProgramShader.h"	// TODO remove

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glext.h>
#include <gl/wglext.h>
#include "Graphics/openglext.h"

#include <Cg/cg.h>
#include <Cg/cgGL.h>
#include <Cg/cgD3D9.h>

#include <d3d9.h>

namespace System
{
namespace x3d
{

extern Graphics::VertexDeclaration m_vertexDeclaration0;

// D3D9
extern ID3DXEffect* m_d3d9_effect;

extern D3DXHANDLE m_d3d9_technique0;

extern D3DXHANDLE m_d3d9_modelViewVariable;
extern D3DXHANDLE m_d3d9_projectionVariable;
extern D3DXHANDLE m_d3d9_modelViewProjectionVariable;
extern D3DXHANDLE m_d3d9_modelViewITVariable;
extern D3DXHANDLE m_d3d9_nlightsVariable;

NodeType* Shape::GetNodeType()
{
	static X3DFieldDefinition appearance("appearance", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Shape, m_appearance));
	static X3DFieldDefinition geometry("geometry", FieldType_SFNode, SAIFieldAccess_inputOutput, offsetof(Shape, m_geometry));

	static X3DFieldDefinition* fields[] =
	{
		&appearance,
		&geometry,
	};

	static NodeType nodeType("Shape", typeid(Shape), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* Shape::nodeType(GetNodeType());

Shape::Shape() : X3DShapeNode(GetNodeType()),

	m_appearance(new TypedSFNode<X3DAppearanceNode*>(this)),
	m_geometry(new TypedSFNode<X3DGeometryNode*>(this))
{
}

void Shape::AddShapeDesc(physx::PxRigidActor* actorDesc)
{
	X3DGeometryNode* geometry = getGeometry();
	if (geometry)
	{
		geometry->AddShapeDesc(actorDesc);
	}
}

void Shape::Draw(X3DDrawContext* pDC)
{
//	SFNode* appearance = m_appearance;
//	SFNode* geometry = m_geometry;

	if (m_geometry)
	{
		// TODO
	//	CalculateBoundingBox();

#if 0
		DrawBoundBox();
#endif
	}

//	if (pDC->m_pGraphics3D)
	//	pDC->m_pGraphics3D->PushAttrib(GL_ENABLE_BIT);

/*
A Shape node is unlit if either of the following is true:

The shape's appearance field is NULL (default). 
The material field in the Appearance node is NULL (default). 
*/

	bool bMaterial = false;
	X3DTextureNodeImplImpl* textureNode = NULL;

	X3DShaderNode* shader = NULL;

//	ASSERT(m_appearance);
//	if (m_appearance)
//	{

		Appearance* appearanceNode = dynamic_cast<Appearance*>(m_appearance->m_value);
		if (appearanceNode)
		{
			MFNode* shaders = appearanceNode->get_shadersField();
			if (shaders)
			{
				for (unsigned int i = 0; i < shaders->get_size(); ++i)
				{
					X3DShaderNode* shaderNode = dynamic_cast<X3DShaderNode*>(shaders->get1Value(i));
					if (shaderNode)
					{
						if (shaderNode->CreateShader(pDC->m_renderContext->GetRT()))
						{
							shader = shaderNode;
							break;
						}
					}
				}
			}

			// TODO, check that it's actually a ILMaterial node
			//SFNode* node;
			
			//node = appearanceNode->getMaterial();
			//if (node)
			{
				X3DMaterialNode* material = appearanceNode->getMaterial();//cast<X3DMaterialNode*>(node->m_value);
				if (material)
				{
				//	Material* pMaterial = static_cast<Material*>(material);
					bMaterial = material->ApplyMaterial(pDC) == 1;

					//bMaterial = true;
				}
				/*
				else
				{
					Material2D* material2D = dynamic_cast<Material2D*>(node->m_value);
					if (material2D)
					{
					//	Material2D* pMaterial2D = static_cast<Material2D*>(material2D);
						bMaterial = material2D->Apply(pDC) == 1;

						//bMaterial = true;
					}
				}
				*/

			}

		//	node = appearanceNode->m_texture;
		//	if (node)
			{
				textureNode = dynamic_cast<X3DTextureNodeImplImpl*>(appearanceNode->getTexture());
				if (textureNode)
				{
					textureNode->CreateTexture(pDC->m_renderContext->GetRT());
					textureNode->ApplyTexture(pDC->m_renderContext);

					//if (static_cast<CLImageTexture*>(imageTexture.p)->m_texName)
					{

					//	bMaterial = TRUE;	// ???
					}
				}
			}
		}
	//}

#if 0
	if (pDC->m_pGraphics3D)
	{
		if (!bMaterial)
		{
			pDC->m_pGraphics3D->Disable(GL_LIGHTING);

			/*
			float m_ambientIntensity;
			float m_diffuseColor[3];
			float m_emissiveColor[3];
			float m_shininess;
			float m_specularColor[3];
			float m_transparency;

			m_ambientIntensity = 0.2f;
			m_diffuseColor[0] = 0.8f; m_diffuseColor[1] = 0.8f; m_diffuseColor[2] = 0.8f;
			m_emissiveColor[0] = 0.0f; m_emissiveColor[1] = 0.0f; m_emissiveColor[2] = 0.0f;
			m_shininess = 0.2f;
			m_specularColor[0] = 0.0f; m_specularColor[1] = 0.0f; m_specularColor[2] = 0.0f;
			m_transparency = 0.0f;

			GLfloat MatAmb[] = { m_ambientIntensity, m_ambientIntensity, m_ambientIntensity, 1.0f};	// ??
			GLfloat MatDiff[] = { m_diffuseColor[0], m_diffuseColor[1], m_diffuseColor[2], 1.0f};
			GLfloat MatEmiss[] = { m_emissiveColor[0], m_emissiveColor[1], m_emissiveColor[2], 1.0f};
			GLfloat MatSpec[] = { m_specularColor[0], m_specularColor[1], m_specularColor[2], 1.0f};

			if (pDC->m_pGraphics3D)
			{
				pDC->m_pGraphics3D->glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MatAmb);
				pDC->m_pGraphics3D->glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MatDiff);
				pDC->m_pGraphics3D->glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, MatEmiss);
				pDC->m_pGraphics3D->glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, MatSpec);

				pDC->m_pGraphics3D->glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m_shininess*128);	// ??
			}
			*/
		}
		else
		{
			pDC->m_pGraphics3D->Enable(GL_LIGHTING);
		}
	}
#endif

	Graphics::Direct3D10_I* pD10 = pDC->m_renderContext->GetRT()->m_d3d10;
	Graphics::OpenGL_I* pGL = pDC->m_renderContext->GetRT()->m_opengl;
	Graphics::Direct3D9_I* pD3D9 = nullptr;//dynamic_cast<LDraw::Direct3D9_I*>(pDC->m_pGraphics3D->m_pGraphics->m_device);

	ProgramShader* pshader = nullptr;

	if (shader)
	{
		pshader = dynamic_cast<ProgramShader*>(shader);
	}

//	if (shader == NULL)
	{
		if (false)
		{
				// Use fixed function pipeline
		}
		else	// Use shaders to emulate fixed function pipeline
		{
			if (pDC->m_renderContext->GetRT()->m_d3d10)	// D3D10
			{
				/*
				LDraw::matrix4f modelView;
				LDraw::matrix4f modelViewIT;
				LDraw::matrix4f projection;

				modelView = pDC->m_modelView;
				modelViewIT = pDC->m_modelViewIT;
				*/

			//	projection = pDC->m_projection;

				if (pshader)
				{
					// Update the Constant Buffer

					
					MapBuffer(pD10->m_device1, pshader->m_vertexShader->m_buffers[0], D3D10_MAP_WRITE_DISCARD, (void**)&pshader->m_vertexShader->m_bufferData[0]);
					MapBuffer(pD10->m_device1, pshader->m_fragmentShader->m_buffers[0], D3D10_MAP_WRITE_DISCARD, (void**)&pshader->m_fragmentShader->m_bufferData[0]);

					//	pConstData->mWorldViewProj = mWorldViewProj;
				//	pConstData->fTime = fBoundedTime;

					pshader->SetModelViewMatrix(pDC->m_renderContext->modelViewMatrix());
					pshader->SetModelViewProjectionMatrix(pDC->m_renderContext->modelViewProjectionMatrix());

					pshader->m_vertexShader->ApplyFields(pDC->m_renderContext->GetRT());

					pshader->m_fragmentShader->ApplyFields(pDC->m_renderContext->GetRT());
					/*
					uint ncustomfields = pshader->m_addfields.size();
					for (uint i = 0; i < ncustomfields; ++i)
					{
						X3DField* field = pshader->m_addfields[i];

						field->

					}
					*/

					UnmapBuffer(pD10->m_device1, pshader->m_fragmentShader->m_buffers[0]);
					UnmapBuffer(pD10->m_device1, pshader->m_vertexShader->m_buffers[0]);

					pD10->m_deviceContext->IASetInputLayout(pshader->m_inputLayout);
				//	pD10->m_device->IASetInputLayout(g_pVertexLayout);
				}
				else
				{
					pD10->m_d3d10_modelVariable->SetMatrix(pDC->m_renderContext->modelMatrix());
					pD10->m_d3d10_viewVariable->SetMatrix(pDC->m_renderContext->viewMatrix());
					pD10->m_d3d10_projectionVariable->SetMatrix(pDC->m_renderContext->projectionMatrix());

					pD10->m_d3d10_modelViewVariable->SetMatrix(pDC->m_renderContext->modelViewMatrix());
					pD10->m_d3d10_modelViewProjectionVariable->SetMatrix(pDC->m_renderContext->modelViewProjectionMatrix());
					pD10->m_d3d10_modelViewITVariable->SetMatrix(pDC->m_renderContext->modelViewITMatrix());

					pD10->m_d3d10_nlightsVariable->SetInt(pDC->m_renderContext->m_nLight);
				}


				/*
				pD3D9->SetVertexDeclaration(m_vertexDeclaration0);

				hr = m_d3d9_effect->SetTechnique(m_d3d9_technique0);
				ASSERT(SUCCEEDED(hr));
				*/

				if (true)
				{
					int nlights = __min(pDC->m_renderContext->m_nLight, 256);
					X3DLight lights[256];

					for (int i = 0; i < nlights; ++i)
					{
					//	char name[256];
					//	sprintf_s(name, "lights[%d]", i);

						lights[i].type = (int)pDC->m_renderContext->m_lights[i].m_position[3];

						lights[i].position[0] = pDC->m_renderContext->m_lights[i].m_position[0];
						lights[i].position[1] = pDC->m_renderContext->m_lights[i].m_position[1];
						lights[i].position[2] = pDC->m_renderContext->m_lights[i].m_position[2];

						lights[i].direction[0] = pDC->m_renderContext->m_lights[i].m_position[0];
						lights[i].direction[1] = pDC->m_renderContext->m_lights[i].m_position[1];
						lights[i].direction[2] = pDC->m_renderContext->m_lights[i].m_position[2];

						lights[i].diffuseColor = pDC->m_renderContext->m_lights[i].m_diffuse;
						lights[i].ambientColor = pDC->m_renderContext->m_lights[i].m_ambient;

						lights[i].attenuation0 = pDC->m_renderContext->m_lights[i].m_constant_attenuation;
						lights[i].attenuation1 = pDC->m_renderContext->m_lights[i].m_linear_attenuation;
						lights[i].attenuation2 = pDC->m_renderContext->m_lights[i].m_quadratic_attenuation;
					}

					pD10->m_d3d10_lightsVariable->SetRawValue(lights, 0, sizeof(X3DLight)*nlights);
				}
			}
			else if (pD3D9)
			{
				HRESULT hr;

				gm::matrix4f modelView;
				gm::matrix4f modelViewIT;
				gm::matrix4f projection;

				modelView = pDC->m_modelView;
				modelViewIT = pDC->m_modelViewIT;

				projection = pDC->m_projection;

				hr = m_d3d9_effect->SetMatrix(m_d3d9_modelViewVariable, (D3DXMATRIX*)&modelView);
				hr = m_d3d9_effect->SetMatrix(m_d3d9_projectionVariable, (D3DXMATRIX*)&projection);
				hr = m_d3d9_effect->SetMatrix(m_d3d9_modelViewProjectionVariable, (D3DXMATRIX*)(float*)(projection * modelView));
			//	hr = m_d3d9_effect->SetVector(m_res->m_d3d9_solidColorVariable, (D3DXVECTOR4*)&fcolor);

				hr = m_d3d9_effect->SetMatrix(m_d3d9_modelViewITVariable, (D3DXMATRIX*)&modelViewIT);

			//	nlights = pGL->m_glprocs->glGetUniformLocation(pDC->m_glFixedShaderProgram, "nlights");
				hr = m_d3d9_effect->SetInt(m_d3d9_nlightsVariable, pDC->m_renderContext->m_nLight);

				pD3D9->SetVertexDeclaration(m_vertexDeclaration0);

				hr = m_d3d9_effect->SetTechnique(m_d3d9_technique0);
				ASSERT(SUCCEEDED(hr));

				if (true)
				{
					for (int i = 0; i < pDC->m_renderContext->m_nLight; i++)
					{
						char name[256];
						sprintf_s(name, "lights[%d]", i);

						X3DLight light;
						light.position[0] = pDC->m_renderContext->m_lights[i].m_position[0];
						light.position[1] = pDC->m_renderContext->m_lights[i].m_position[1];
						light.position[2] = pDC->m_renderContext->m_lights[i].m_position[2];
						light.diffuseColor = pDC->m_renderContext->m_lights[i].m_diffuse;

						D3DXHANDLE location = m_d3d9_effect->GetParameterByName(NULL, name);

					//	hr = m_d3d9_effect->SetValue(NULL, location, pDC->m_lights[i].m_diffuse);
					//	hr = m_d3d9_effect->SetValue(NULL, location, pDC->m_lights[i], sizeof);
						hr = m_d3d9_effect->SetValue(location, &light, sizeof(light));
						ASSERT(SUCCEEDED(hr));
					}
				}
			}
			else if (pGL)
			{
			//	glMatrixMode(GL_MODELVIEW);
				glLoadMatrixf(pDC->m_renderContext->modelViewMatrix());

			//	glLoadMatrixf(pDC->m_renderContext->projectionMatrix());
			//	m_d3d10_modelViewProjectionVariable->SetMatrix(pDC->m_renderContext->modelViewProjectionMatrix());
			//	m_d3d10_modelViewITVariable->SetMatrix(pDC->m_renderContext->modelViewITMatrix());

				pGL->m_glprocs->glUseProgram(pDC->m_glFixedShaderProgram);
				ASSERT(::glGetError() == 0);

				int nlights = pGL->m_glprocs->glGetUniformLocation(pDC->m_glFixedShaderProgram, "nlights");
				ASSERT(::glGetError() == 0);

				if (nlights != -1)
				{
					pGL->m_glprocs->glUniform1i(nlights, pDC->m_renderContext->m_nLight);
					ASSERT(::glGetError() == 0);

					for (int i = 0; i < pDC->m_renderContext->m_nLight; ++i)
					{
						char name[256];
						sprintf_s(name, "lights[%d].diffuse", i);

						int location = pGL->m_glprocs->glGetUniformLocation(pDC->m_glFixedShaderProgram, name);
						ASSERT(::glGetError() == 0);

						pGL->m_glprocs->glUniform4fv(location, 1, pDC->m_renderContext->m_lights[i].m_diffuse);
						int err = ::glGetError();
						ASSERT(err == 0);
					}
				}
			}
		}
	}

	IGeometryRender* renderGeometry = dynamic_cast<IGeometryRender*>(m_geometry->getValue());
	if (renderGeometry)
	{
		if (shader)
		{
			UINT nPasses = 0;
			shader->Begin(pDC, &nPasses);

			for (uint nPass = 0; nPass < nPasses; ++nPass)
			{
				shader->BeginPass(pDC, nPass);

				renderGeometry->Draw(pDC, textureNode);

				shader->EndPass(pDC);
			}

			shader->End(pDC);
		}
		else
		{
			if (pDC->m_renderContext->GetRT()->m_d3d10)	// D3D10
			{
				ID3DX10EffectTechnique* technique;
				if (textureNode)
				{
					technique = pD10->m_phongLightTexTechnique;
					pD10->m_device->IASetInputLayout(pD10->m_phongLightTexInputLayout);
				}
				else
				{
					technique = pD10->m_phongLightTechnique;
					pD10->m_device->IASetInputLayout(pD10->m_phongLightInputLayout);
				}

				// Draw
				D3DX10_TECHNIQUE_DESC techDesc;
				technique->GetDesc(&techDesc);

				for (UINT nPass = 0; nPass < techDesc.Passes; ++nPass)
				{
					technique->GetPassByIndex(nPass)->Apply(0);
					renderGeometry->Draw(pDC, textureNode);

					/*
					if( g_bFirst )
						pd3dDevice->Draw( MAX_PARTICLES, 0 );
					else
						pd3dDevice->DrawAuto();
						*/
				}
			}
			else if (pDC->m_renderContext->GetRT()->m_d3d10)	// D3D11
			{
#if 0
				ID3DX10EffectTechnique* technique;
				if (textureNode)
				{
					technique = pD10->m_phongLightTexTechnique;
					pD10->m_deviceContext->IASetInputLayout(pD10->m_phongLightTexInputLayout);
				}
				else
				{
					technique = pD10->m_phongLightTechnique;
					pD10->m_deviceContext->IASetInputLayout(pD10->m_phongLightInputLayout);
				}

				// Draw
				D3DX10_TECHNIQUE_DESC techDesc;
				technique->GetDesc(&techDesc);

				for (UINT nPass = 0; nPass < techDesc.Passes; ++nPass)
				{
					technique->GetPassByIndex(nPass)->Apply(0, pD10->m_deviceContext);
					renderGeometry->Draw(pDC, textureNode);

					/*
					if( g_bFirst )
						pd3dDevice->Draw( MAX_PARTICLES, 0 );
					else
						pd3dDevice->DrawAuto();
						*/
				}
#endif
			}
			else if (pD3D9)
			{
				HRESULT hr;

				UINT nPasses;
				hr = m_d3d9_effect->Begin(&nPasses, 0);
				ASSERT(SUCCEEDED(hr));
				for (UINT nPass = 0; nPass < nPasses; ++nPass)
				{
					hr = m_d3d9_effect->BeginPass(nPass);
					ASSERT(SUCCEEDED(hr));

					renderGeometry->Draw(pDC, textureNode);

					hr = m_d3d9_effect->EndPass();
					ASSERT(SUCCEEDED(hr));
				}
				hr = m_d3d9_effect->End();
				ASSERT(SUCCEEDED(hr));
			}
			else
			{
				renderGeometry->Draw(pDC, textureNode);
			}
		}
	}

	if (shader == NULL)
	{
		if (pGL)
		{
			pGL->m_glprocs->glUseProgram(0);
		}
	}

	/*
	if (pDC->m_pBrush)
	{
		//delete pDC->m_pBrush;
		pDC->m_pBrush = NULL;
	}
	*/
#if 0
	if (pDC->m_pGraphics3D)
	{
		pDC->m_pGraphics3D->PopAttrib();
	}
#endif
}

BoundingBox Shape::CalculateBoundingBox(gm::matrix4f& transform)
{
	//SFNode* geometry = static_cast<SFNode*>(m_geometry);

	X3DBoundedImplImpl* boundedImpl = dynamic_cast<X3DBoundedImplImpl*>(m_geometry->m_value);
	if (boundedImpl)
	{
		return boundedImpl->CalculateBoundingBox(transform);

	//	m_computedBBoxSize = boundedImpl->m_computedBBoxSize;
	//	m_computedBBoxCenter = boundedImpl->m_computedBBoxCenter;
	}

	return BoundingBox(Vec3f(0,0,0), Vec3f(-1,-1,-1));
}

void Shape::DrawOverlay(X3DDrawContext* pDC)
{
	if (m_selected)
	{
		D3DXMATRIX m = pDC->m_renderContext->modelViewMatrix();
		DrawBoundingBox(pDC, CalculateBoundingBox(*(gm::matrix4f*)&m));
	}
}

X3DGeometryNode* Shape::getGeometry()
{
	return m_geometry->getValue();
}

void Shape::setGeometry(X3DGeometryNode* node)
{
	m_geometry->setValue(node);
}

X3DAppearanceNode* Shape::getAppearance()
{
	return m_appearance->getValue();
}

void Shape::setAppearance(X3DAppearanceNode* node)
{
	m_appearance->setValue(node);
}

/*
void Shape::addActors(NxScene* nxScene, D3DXMATRIX modelView)
{
	X3DGeometryNode* geometry = getGeometry();
	if (geometry)
	{
		geometry->CreateActor(nxScene, modelView);
	}
}
*/

void Shape::UpdatePos()
{
	X3DGeometryNode* geometry = getGeometry();
	if (geometry)
	{
	}
}

}	// x3d
}
