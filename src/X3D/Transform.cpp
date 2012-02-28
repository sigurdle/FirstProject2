#include "stdafx.h"
#include "X3D2.h"
#include "Transform.h"

namespace System
{

bool point_near_line_2d(const gm::vector3f& A, const gm::vector3f& B, const gm::vector2f& P, double* t)
{
	double bboxX1 = MIN(A[0], B[0])-2;
	double bboxY1 = MIN(A[1], B[1])-2;
	double bboxX2 = MAX(A[0], B[0])+2;
	double bboxY2 = MAX(A[1], B[1])+2;

	if (P[0] >= bboxX1 && P[1] >= bboxY1 && P[0] <= bboxX2 && P[1] <= bboxY2)
	{
		double a2 = (P[1]-A[1])*(B[0]-A[0]) - (P[0]-A[0])*(B[1]-A[1]);

		double d1 = (a2*a2)/((B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]));

		if (d1 < 3*3)
		{
		//	hit->element = this;
		//	hit->segment = i-1;

			double L2 = (B[0]-A[0])*(B[0]-A[0]) + (B[1]-A[1])*(B[1]-A[1]);
			*t = ((P[0]-A[0])*(B[0]-A[0]) + (P[1]-A[1])*(B[1]-A[1]))/L2;

		//	if (*t >= -0.0001 && *t <= 1.0001)
			{
				return true;
			}
		}
	}

	return false;
}

namespace x3d
{

IMP_X3DFIELD0(Transform, SFVec3f, center, inputOutput)
IMP_X3DFIELD1(Transform, SFRotation, rotation, inputOutput, Rotation(Vec3f(0.0f, 0.0f, 1.0f), 0.0f))
IMP_X3DFIELD1(Transform, SFVec3f, scale, inputOutput, Vec3f(1.0f, 1.0f, 1.0f))
IMP_X3DFIELD1(Transform, SFRotation, scaleOrientation, inputOutput, Rotation(Vec3f(0.0f, 0.0f, 1.0f), 0.0f))
IMP_X3DFIELD0(Transform, SFVec3f, translation, inputOutput)

NodeType* Transform::GetNodeType()
{
	static X3DFieldDefinition* fields[] =
	{
		/*
		X3DFieldDefinition(WSTR("addChildren"), FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
		X3DFieldDefinition(WSTR("removeChildren"), FieldType_MFNode, SAIFieldAccess_inputOnly,-1),
		X3DFieldDefinition(WSTR("bboxCenter"), FieldType_SFVec3f, SAIFieldAccess_initializeOnly,-1),
		X3DFieldDefinition(WSTR("bboxSize"), FieldType_SFVec3f, SAIFieldAccess_initializeOnly,-1),
		*/
		get_centerFieldDef(),
		get_rotationFieldDef(),
		get_scaleFieldDef(),
		get_scaleOrientationFieldDef(),
		get_translationFieldDef(),
		/*
		MFNode     [in]     addChildren               [X3DChildNode]
		MFNode     [in]     removeChildren            [X3DChildNode]
		SFVec3f    [in,out] center           0 0 0    (-8,8)
		MFNode     [in,out] children         []       [X3DChildNode]
		SFNode     [in,out] metadata         NULL     [X3DMetadataObject]
		SFRotation [in,out] rotation         0 0 1 0  [-1,1] or (-8,8)
		SFVec3f    [in,out] scale            1 1 1    (0,8)
		SFRotation [in,out] scaleOrientation 0 0 1 0  [-1,1] or (-8,8)
		SFVec3f    [in,out] translation      0 0 0    (-8,8)
		SFVec3f    []       bboxCenter       0 0 0    (-8,8)
		SFVec3f    []       bboxSize         -1 -1 -1 (0,8) or -1 -1 -1
		*/
	};

	static NodeType nodeType(WSTR("Transform"), typeid(Transform), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* Transform::nodeType(GetNodeType());

Transform::Transform() : X3DGroupingNode(GetNodeType()),
	m_center(new SFVec3f(get_centerFieldDef(), this)),
	m_rotation(new SFRotation(get_rotationFieldDef(), this)),
	m_scale(new SFVec3f(get_scaleFieldDef(), this)),
	m_scaleOrientation(new SFRotation(get_scaleOrientationFieldDef(), this)),
	m_translation(new SFVec3f(get_translationFieldDef(), this))
{
}

D3DXMATRIX Transform::GetTransform()
{
	Vec3f T = getTranslation();
	Vec3f C = getCenter();
	Vec3f S = getScale();
	Rotation R = getRotation();
	Rotation SR = getScaleOrientation();

	gm::matrix4f m =
		gm::matrix4f::getTranslate(T) *
		gm::matrix4f::getTranslate(C) *
		gm::matrix4f::getRotate(gmDegrees(R.m_angle), R.m_axis) *
		gm::matrix4f::getRotate(gmDegrees(SR.m_angle), SR.m_axis) *
		gm::matrix4f::getScale(S) *
		gm::matrix4f::getRotate(gmDegrees(SR.m_angle), -SR.m_axis) *
		gm::matrix4f::getTranslate(-C);

	return *(D3DXMATRIX*)&m;
}

// virtual
void Transform::DrawGlobalLights(X3DDrawContext* pDC)
{
	D3DXMATRIX transform = GetTransform();
	pDC->m_renderContext->PushModelView(transform * pDC->m_renderContext->modelViewMatrix());

	DrawGlobalLightsChildren(pDC, getChildrenField());

	pDC->m_renderContext->PopMatrix();

#if 0
	pDC->m_pGraphics3D->PushMatrix();

// P' = T * C * R * SR * S * -SR * -C * P

		pDC->m_pGraphics3D->TranslateTransform(m_T->m_value);
		pDC->m_pGraphics3D->TranslateTransform(m_C->m_value);
		pDC->m_pGraphics3D->RotateTransform(gmDegrees(m_R->m_value.m_angle), m_R->m_value.m_axis);
		pDC->m_pGraphics3D->RotateTransform(gmDegrees(m_SR->m_value.m_angle), m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->ScaleTransform(m_S->m_value);
		pDC->m_pGraphics3D->RotateTransform(gmDegrees(m_SR->m_value.m_angle), -m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->TranslateTransform(-m_C->m_value);

	DrawGlobalLightsChildren(pDC, get_children());

	pDC->m_pGraphics3D->PopMatrix();
#endif
}

/*
void Transform::addActors(NxScene* nxScene, D3DXMATRIX modelView)
{
	X3DGroupingNode::addActors(nxScene, GetTransform() * modelView);
}
*/

BoundingBox Transform::CalculateBoundingBox(gm::matrix4f& transform)
{
	return X3DGroupingNode::CalculateBoundingBox(transform);
}

// virtual
void Transform::Draw(X3DDrawContext* pDC)
{
	Vec3f S = getScale();

	if (S[0] == 0 && S[1] == 0 && S[2] == 0)
		return;

	D3DXMATRIX transform = GetTransform();

	pDC->m_renderContext->PushModelView(transform * pDC->m_renderContext->modelViewMatrix());

#if 0	// Had this
	pDC->m_pGraphics3D->PushMatrix();

// P' = T * C * R * SR * S * -SR * -C * P

		pDC->m_pGraphics3D->TranslateTransform(m_T->m_value);
		pDC->m_pGraphics3D->TranslateTransform(m_C->m_value);
		if (m_R->m_value.m_angle) pDC->m_pGraphics3D->RotateTransform(gmDegrees(m_R->m_value.m_angle), m_R->m_value.m_axis);
		if (m_SR->m_value.m_angle) pDC->m_pGraphics3D->RotateTransform(gmDegrees(m_SR->m_value.m_angle), m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->ScaleTransform(m_S->m_value);
		if (m_SR->m_value.m_angle) pDC->m_pGraphics3D->RotateTransform(gmDegrees(m_SR->m_value.m_angle), -m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->TranslateTransform(-m_C->m_value);
#endif
	// Draw axes
#if 0
	if (FALSE)
	{
		pDC->m_pGraphics3D->glPushAttrib(GL_ENABLE_BIT);

		float len = 4;

		pDC->m_pGraphics3D->glDisable(GL_LIGHTING);

		pDC->m_pGraphics3D->glBegin(GL_LINES);

		pDC->m_pGraphics3D->glColor3f(1.0, 0, 0);	// red
		pDC->m_pGraphics3D->glVertex3f(0, 0, 0);
		pDC->m_pGraphics3D->glVertex3f(1*len, 0, 0);

		pDC->m_pGraphics3D->glColor3f(0.0, 1.0, 0);	// blue
		pDC->m_pGraphics3D->glVertex3f(0, 0, 0);
		pDC->m_pGraphics3D->glVertex3f(0, 1*len, 0);

		glColor3f(0, 0, 1.0);	// green
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 1*len);

		glEnd();

		glPopAttrib();
	}
#endif

	DrawChildren(pDC, getChildrenField());

	/*
	int nLight = pDC->m_nLight;
	int nNames = pDC->m_namedNodes.GetSize();

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (m_children->m_items[i])
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (m_children->m_items[i])
		{
			RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
			if (render)
			{
				render->Draw(pDC);
			}
		}
	}

	for (i = pDC->m_namedNodes.GetSize(); i >= nNames; i--)
	{
//		glPopName();
	}
	for (i = pDC->m_nLight; i >= nLight; i--)
	{
		pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
	}
	pDC->m_nLight = nLight;
	*/

	pDC->m_renderContext->PopMatrix();
	//pDC->m_transformStack.pop();
#if 0
	pDC->m_pGraphics3D->PopMatrix();
#endif
}

void Transform::DrawOverlay(X3DDrawContext* pDC)
{
	Vec3f S = getScale();

	if (S[0] == 0 && S[1] == 0 && S[2] == 0)
		return;

	D3DXMATRIX transform = GetTransform();
	pDC->m_renderContext->PushModelView(transform * pDC->m_renderContext->modelViewMatrix());

	// TODO: not here
	if (m_selected)
	{
	//	pDC->m_renderContext->PushModelView(pDC->m_renderContext->modelViewMatrix() * MatrixTranslation(getLocation()));

		D3DXMATRIX m = pDC->m_renderContext->modelViewMatrix();
		DrawBoundingBox(pDC, CalculateBoundingBox(*(gm::matrix4f*)&m));

		DrawAxis(pDC);

	//	pDC->m_renderContext->PopMatrix();
	//	pDC->m_renderContext->GetRT()->m_d3d10->m_device->OMSetDepthStencilState(depthStencilState, stencilRef);
	}

	DrawOverlayChildren(pDC, getChildrenField());

	pDC->m_renderContext->PopMatrix();

#if 0
	/*
	SFVec3f*		C = static_cast<SFVec3f*>(m_C);
	SFRotation*	R = static_cast<SFRotation*>(m_R);
	SFVec3f*		S = static_cast<SFVec3f*>(m_S);
	SFVec3f*		SR = static_cast<SFVec3f*>(m_SR);
	SFVec3f*		T = static_cast<SFVec3f*>(m_T);
	MFNode*		children = static_cast<MFNode*>(m_children);
	*/

	pDC->m_pGraphics3D->glPushMatrix();

		pDC->m_pGraphics3D->glTranslate(m_T->m_value);
		pDC->m_pGraphics3D->glTranslate(m_C->m_value);
		pDC->m_pGraphics3D->glRotate(gmDegrees(m_R->m_value.m_angle), m_R->m_value.m_axis);
		pDC->m_pGraphics3D->glRotate(gmDegrees(m_SR->m_value.m_angle), m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->glScale(m_S->m_value);
		pDC->m_pGraphics3D->glRotate(gmDegrees(m_SR->m_value.m_angle), -m_SR->m_value.m_axis);
		pDC->m_pGraphics3D->glTranslate(-m_C->m_value);

		// Draw axes
	{
		//DrawBoundBox();

		pDC->m_pGraphics3D->glPushAttrib(GL_ENABLE_BIT);

		float len = 4;

		pDC->m_pGraphics3D->glDisable(GL_LIGHTING);

		pDC->m_pGraphics3D->glBegin(GL_LINES);

		pDC->m_pGraphics3D->glColorf(1.0, 0, 0);	// red
		pDC->m_pGraphics3D->glVertexf(0, 0, 0);
		pDC->m_pGraphics3D->glVertexf(1*len, 0, 0);

		pDC->m_pGraphics3D->glColorf(0.0, 1.0, 0);	// blue
		pDC->m_pGraphics3D->glVertexf(0, 0, 0);
		pDC->m_pGraphics3D->glVertexf(0, 1*len, 0);

		pDC->m_pGraphics3D->glColorf(0, 0, 1.0);	// green
		pDC->m_pGraphics3D->glVertexf(0, 0, 0);
		pDC->m_pGraphics3D->glVertexf(0, 0, 1*len);

		pDC->m_pGraphics3D->glEnd();

		pDC->m_pGraphics3D->glColorf(1,1,1);	// white
	//	GLUquadricObj* q = gluNewQuadric();
		LDraw::gluSphere(pDC->m_pGraphics3D, 0.1, 8, 8);
	//	gluDeleteQuadric(q);

		pDC->m_pGraphics3D->glPopAttrib();
	}

	int nLight = pDC->m_nLight;

	int i;

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (m_children->m_items[i])
		{
			CLRenderImplImpl* render = dynamic_cast<CLRenderImplImpl*>(m_children->m_items[i]->GetNode());
			if (render)
			{
				render->PreDraw(pDC);
			}
		}
	}

	for (i = 0; i < m_children->m_items.GetSize(); i++)
	{
		if (m_children->m_items[i])
		{
			CLRenderImplImpl* render = dynamic_cast<CLRenderImplImpl*>(m_children->m_items[i]->GetNode());
			if (render)
			{
				render->DrawOverlay(pDC);
			}
		}
	}

	for (i = pDC->m_nLight; i >= nLight; i--)
	{
		pDC->m_pGraphics3D->glDisable(GL_LIGHT0+i);
	}
	pDC->m_nLight = nLight;

	pDC->m_pGraphics3D->glPopMatrix();
#endif
}

Vec4f operator * (const Vec4f& v, const D3DXMATRIX& m)
{
	return Vec4f(
		v[0]*m._11 + v[0]*m._12 + v[0]*m._13 + v[0]*m._14,
		v[1]*m._21 + v[1]*m._22 + v[1]*m._23 + v[1]*m._24,
		v[2]*m._31 + v[2]*m._32 + v[2]*m._33 + v[2]*m._34,
		v[3]*m._41 + v[3]*m._42 + v[3]*m._43 + v[3]*m._44);

	return Vec4f(
		v[0] * m._11 + v[1] * m._12 + v[2] * m._13 + v[3] * m._14,
		v[0] * m._21 + v[1] * m._22 + v[2] * m._23 + v[3] * m._24,
		v[0] * m._31 + v[1] * m._32 + v[2] * m._33 + v[3] * m._34,
		v[0] * m._41 + v[1] * m._42 + v[2] * m._43 + v[3] * m._44);

}

Vec3f VecProject(Vec3f obj, const D3D10_VIEWPORT& vp, const D3DXMATRIX& proj, const D3DXMATRIX& view, const D3DXMATRIX& model)
{
	D3DXVECTOR3 in(obj[0], obj[1], obj[2]);

	D3DXVECTOR3 out;
	D3DXVec3Project(&out, &in, &vp, &proj, &view, &model);
	return Vec3f(out.x, out.y, out.z);

//	Vec4f in = Vec4f(obj[0], obj[1], obj[2], 1) * model;
//	in = in * view;
//	in = in * proj;

#if 0
	D3DXVECTOR4 in(obj[0], obj[1], obj[2], 1);

	D3DXVECTOR4 out;
	D3DXVec4Transform(&out, &in, &model);
	D3DXVec4Transform(&in, &out, &view);
	D3DXVec4Transform(&out, &in, &proj);
	in = out;

//	transform_point_unaligned(out, in, model);
//	transform_point_unaligned(in, out, proj);

	if (in[3] == 0.0f)
	{
		// ??
		in[3] = 0.00001f;
	//	return GL_FALSE;
	}

	in[0] /= in[3];
	in[1] /= in[3];
	in[2] /= in[3];

    /* Map x, y and z to range 0-1 */
    in[0] = in[0] * 0.5 + 0.5;
    in[1] = in[1] * 0.5 + 0.5;
    in[2] = in[2] * 0.5 + 0.5;

    /* Map x,y to viewport */
	in[0] = in[0] * vp.Width + vp.TopLeftX;
	in[1] = in[1] * vp.Height + vp.TopLeftY;
//	in[2] = 1 -in[2];

	return Vec3f(in[0], in[1], in[2]);

	/*
	// window coordinates
	win[0] = viewport[0]+(1+in[0])*viewport[2]/2;
	win[1] = viewport[1]+(1+in[1])*viewport[3]/2;
//	win[1] = viewport[3] - win[1];
		
	// 0..1
	win[2] = (1+in[2])/2;
	*/
#endif
}

int Transform::HitTest(const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest)
{
	D3DXMATRIX transform = GetTransform();

	D3DXMATRIX model2 = model * transform;

//	D3DXVECTOR3 location(0,0,0);
//	D3DXVECTOR4 v;
//	D3DXVec3Transform(&v, &location, &transform);

	float scale = 10;

	D3DXVECTOR3 out;

	D3DXVECTOR3 _obj = *D3DXVec3Project(&out, &D3DXVECTOR3(0,0,0), &vp, &projection, &view, &model2);
	D3DXVECTOR3 _xaxis = *D3DXVec3Project(&out, &D3DXVECTOR3(scale,0,0), &vp, &projection, &view, &model2);
	D3DXVECTOR3 _yaxis = *D3DXVec3Project(&out, &D3DXVECTOR3(0,scale,0), &vp, &projection, &view, &model2);
	D3DXVECTOR3 _zaxis = *D3DXVec3Project(&out, &D3DXVECTOR3(0,0,scale), &vp, &projection, &view, &model2);

	Vec3f obj = VecProject(Vec3f(0,0,0), vp, projection, view, model2);
	Vec3f xaxis = VecProject(Vec3f(scale,0,0), vp, projection, view, model2);
	Vec3f yaxis = VecProject(Vec3f(0,scale,0), vp, projection, view, model2);
	Vec3f zaxis = VecProject(Vec3f(0,0,scale), vp, projection, view, model2);

	if (fabs(mousepos[0]-obj[0]) < 3 &&
		fabs(mousepos[1]-obj[1]) < 3)
	{
		hitTest->OnHit(this, type, *(Vec3f*)&obj);
		return 1;
	}
	else
	{
	//

		int axis = 0;

		double t;
		if (point_near_line_2d(obj, xaxis, mousepos, &t))
		{
			axis = 1;
		}
		else if (point_near_line_2d(obj, yaxis, mousepos, &t))
		{
			axis = 2;
		}
		else if (point_near_line_2d(obj, zaxis, mousepos, &t))
		{
			axis = 3;
		}

		if (axis)
		{
			hitTest->OnHit(this, type, obj, axis, t);

#if 0
			SelectedObject* p = object->m_selectedObject;
		//	p->m_object = object;
			p->m_wtransform = model;

			// ??
			if (m_document->m_objectMode == Mode_Model || m_document->m_objectMode == Mode_Axis)
				p->m_startTransform = object->m_transform->m_matrix;
			else
				p->m_startTransform = LDraw::matrix4f::getIdentity();

			p->m_z = obj[2];

			p->m_axis = axis;
			p->m_axis_t = t;

			selectedObjects.Add(p);
#endif
		}
	}

	return 0;
}

}	// x3d
}	// System
