#include "stdafx.h"
#include "X3D2.h"
#include "Shape.h"
#include "CollidableShape.h"
#include "GUI/physics.h"

namespace System
{
namespace x3d
{

#ifdef NX_PHYSICS_NXPHYSICS

class MyContactReport : public NxUserContactReport
{
public:
	virtual void onContactNotify(NxContactPair& pair, NxU32 events)
	{
		// Iterate through contact points
		NxContactStreamIterator i(pair.stream);
		//user can call getNumPairs() here
		while(i.goNextPair())
		{
			//user can also call getShape() and getNumPatches() here
			while(i.goNextPatch())
			{
				//user can also call getPatchNormal() and getNumPoints() here
				const NxVec3& contactNormal = i.getPatchNormal();
				while(i.goNextPoint())
				{
					//user can also call getPoint() and getSeparation() here
					if(i.getSeparation()<0.0f)
					{
						const NxVec3& contactPoint = i.getPoint();

						NxU32 faceIndex = i.getFeatureIndex0();
						if(faceIndex==0xffffffff)	faceIndex = i.getFeatureIndex1();
						if(faceIndex!=0xffffffff)
						{
						//	gTouchedTris.pushBack(faceIndex);
						}
					}
				}
			}
		}
	}

}
gMyContactReport;

#endif

NodeType* CollidableShape::GetNodeType()
{
	static TypedX3DFieldDefinition<SFNode> shape("shape", SAIFieldAccess_inputOutput, offsetof(CollidableShape, m_shape));

	static X3DFieldDefinition* fields[] =
	{
		&shape,
	};

	static NodeType nodeType("CollidableShape", typeid(CollidableShape), fields, _countof(fields), baseClass::GetNodeType());
	return &nodeType;
}

NodeType* CollidableShape::nodeType(GetNodeType());

CollidableShape::CollidableShape() : X3DNBodyCollidableNode(GetNodeType()),
	m_shape(new TypedSFNode<Shape*>(this))
{
}

/*
void CollidableShape::addActors(NxScene* nxScene, D3DXMATRIX model)
{
	Shape* shape = dynamic_cast<Shape*>(m_shape->getValue());
	if (shape)
	{
		shape->addActors(nxScene, model);
	}
}
*/

#if 0
void CollidableShape::UpdatePos()
{
	Shape* shape = dynamic_cast<Shape*>(m_shape->getValue());
	if (shape)
	{
		X3DGeometryNode* geometry = shape->getGeometry();
		if (geometry)
		{
			/*
			if (geometry->m_actor)
			{
				NxVec3 pos = geometry->m_actor->getGlobalPosition();
				NxQuat orient = geometry->m_actor->getGlobalOrientationQuat();

				NxReal angle;
				NxVec3 axis;
				orient.getAngleAxis(angle, axis);

				m_translation->setValue(pos.x, pos.y, pos.z);
				m_rotation->setValue(AxisAngle(axis.x, axis.y, axis.z, NxMath::degToRad(angle)));

				m_scene->Invalidate();
			}
			*/
		}
	}
}
#endif

Shape* CollidableShape::getShape()
{
	return static_cast<Shape*>(m_shape->getValue());
}

void CollidableShape::Draw(X3DDrawContext* pDC)
{
	Shape* shape = dynamic_cast<Shape*>(m_shape->getValue());
	if (shape)
	{
		D3DXMATRIX translationMatrix;
		Vec3f translation = m_translation->getValue();
		D3DXMatrixTranslation(&translationMatrix, translation[0], translation[1], translation[2]);

		D3DXMATRIX rotationMatrix;
		Rotation rotation = m_rotation->getValue();
		D3DXMatrixRotationAxis(&rotationMatrix, (D3DXVECTOR3*)&rotation.m_axis, rotation.m_angle);

	//	pDC->m_renderContext->PushModelView(pDC->m_renderContext->modelViewMatrix() * translationMatrix * rotationMatrix);
		pDC->m_renderContext->PushModelView(rotationMatrix * translationMatrix * pDC->m_renderContext->modelViewMatrix());

		shape->Draw(pDC);

		pDC->m_renderContext->PopMatrix();
	}
}

}	// x3d
}	// System
