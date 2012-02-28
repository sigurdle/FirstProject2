#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

Object3DVisual::Object3DVisual() : UIElement(get_Class())
{
}

DependencyClass* Object3DVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_CameraProperty(),
		get_Object3DProperty(),
	};

	return &depclass;
}

IMP_DEPENDENCY_PROPERTY(Camera*, Object3DVisual, Camera, nullptr/*, new PropertyMetadata(true)*/);
IMP_DEPENDENCY_PROPERTY(Visual3D*, Object3DVisual, Object3D, nullptr/*, new PropertyMetadata(true)*/);

void Object3DVisual::OnSetRoot(IRootVisual* root)
{
	Visual3D* object = get_Object3D();

	if (object)
	{
		object->SetRoot(root);
	}
}

void Object3DVisual::OnComputedPropertyValueChanged(PropertyValue* pPropertyValue, bool handled)
{
	if (pPropertyValue->m_dp == get_Object3DProperty())
	{
		Visual3D* obj = get_Object3D();
		if (obj)
		{
			obj->SetRoot(GetRoot());
		}
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyValue, handled);
}

void Object3DVisual::Render(ManagedRenderContext renderContext)
{
	ASSERT(GetRoot());
	ImmediateRenderContext* imm = dynamic_cast<ImmediateRenderContext*>(renderContext.m_p);

	Visual3D* object = get_Object3D();

	Camera* camera = get_Camera();
	if (camera)
	{
		D3DXMATRIX world = camera->GetViewMatrix();

		float w = 400;
		float h = 300;

/*
		D3DXMATRIX world;
		D3DXMatrixIdentity(&world);
		D3DXMatrixTranslation(&world, 0, 0, -10);
*/
		D3DXMATRIX projection = camera->GetProjectionMatrixRH(w, h, 0.5, 800);
	//	D3DXMatrixPerspectiveFovLH(&projection, gmRadians(45), aspect, 0.5, 500);

		imm->m_modelViewIMatrix_Valid = false;
		imm->m_modelViewProjectionMatrix_Valid = false;

		imm->m_projectionMatrix = projection;
		imm->m_modelViewMatrix = world;
		imm->m_modelViewProjectionMatrix = world * projection;

		/*
		float determinant;

		D3DXMatrixInverse(&renderContext.m_p->m_modelViewMatrix, &determinant, &renderContext.m_p->m_modelViewIMatrix);
		renderContext.m_p->m_modelViewIMatrix_Valid = true;

		D3DXMatrixTranspose(&renderContext.m_p->m_modelViewMatrix, &renderContext.m_p->m_modelViewTMatrix);
		renderContext.m_p->m_modelViewTMatrix_Valid = true;

		D3DXMatrixTranspose(&renderContext.m_p->m_modelViewIMatrix, &renderContext.m_p->m_modelViewITMatrix);
		renderContext.m_p->m_modelViewITMatrix_Valid = true;
*/
		
		//g_pLightPosition->Set

		if (renderContext.m_p->GetRT()->m_opengl)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();	// ??
			glLoadMatrixf(imm->projectionMatrix());

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();	// ??
			glLoadMatrixf(imm->modelViewMatrix());
		}
		else
		{
#if 0
			if (g_pWorld)
			{
				g_pWorld->SetMatrix(world);
				g_pWorldViewProjection->SetMatrix(imm->modelViewProjectionMatrix()/*m_modelViewProjectionMatrix*/);

			}
#endif
		}
	}

	if (object)
	{
		object->SetLight(imm);

		object->Render(renderContext);
		imm->m_lights.clear();
		imm->m_nLight = 0;
	}
}

}	// Media3D
}	// Gui
}	// System
