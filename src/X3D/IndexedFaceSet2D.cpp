#include "stdafx.h"
#include "X3D2.h"
#include "IndexedFaceSet2D.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* IndexedFaceSet2DFields[] =
{
	&X3DFieldDefinition("color", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("colorPerVertex", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("convex", FieldType_SFBool, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("coord", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("coordIndex", FieldType_MFInt32, SAIFieldAccess_initializeOnly,-1),
	&X3DFieldDefinition("texCoordIndex", FieldType_MFInt32, SAIFieldAccess_initializeOnly,-1),
	/*
	eventIn MFInt32 set_colorIndex
	eventIn MFInt32 set_coordIndex
	eventIn MFInt32 set_texCoordIndex
	exposedField SFNode color NULL
	exposedField SFNode coord NULL
	exposedField SFNode texCoord NULL
	field MFInt32 colorIndex []
	field SFBool colorPerVertex TRUE
	field SFBool convex TRUE
	field MFInt32 coordIndex []
	field MFInt32 texCoordIndex []
	*/
};

NodeType IndexedFaceSet2D::s_nodeType(WSTR("IndexedFaceSet2D"), typeid(IndexedFaceSet2D), IndexedFaceSet2DFields, _countof(IndexedFaceSet2DFields));

IndexedFaceSet2D::IndexedFaceSet2D() : X3DGeometryNode(&s_nodeType)
{
// Cache pointers to relevant fields
	m_coord = static_cast<SFNode*>(getField(WSTR("coord")));
	m_coordIndex = static_cast<MFInt32*>(getField(WSTR("coordIndex")));
	m_convex = static_cast<SFBool*>(getField(WSTR("convex")));

// Set defaults
//	m_convex->m_value = true;
}

IndexedFaceSet2D::~IndexedFaceSet2D()
{
}

void IndexedFaceSet2D::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	ASSERT(0);
#if 0
	if (pDC->m_pGraphics2D)
	{
		Coordinate2D* coordinate2D = dynamic_cast<Coordinate2D*>(m_coord->m_value);
		if (coordinate2D)
		{
			MFVec2f* point = coordinate2D->getPoint();

			//MFVec2f* texpoint;

			//MFInt32* useTexCoordIndex;

			/*
			if (texcoordinate)
			{
				texpoint = static_cast<MFVec2f*>(static_cast<CLTextureCoordinate*>(texcoordinate.p)->m_point);

				if (texCoordIndex->m_items.GetSize() > 0)
				{
					if (texCoordIndex->m_items.GetSize() != coordIndex->m_items.GetSize())
					{
						// TODO, mark this object with some kind of error flag
						// m_bError = TRUE
						return;	// Error
					}
					useTexCoordIndex = texCoordIndex;
				}
				else
				{
					useTexCoordIndex = coordIndex;
				}
			}
			*/

			LDraw::Brush* pBrush = pDC->m_pBrush;

			if (m_convex->m_value != false)
			{
				if (m_coordIndex->m_items.GetSize() == 0)
				{
				//	LDraw::GraphicsPath path;

					/*
					for (int i = 0; i < point->m_items.GetSize(); i++)
					{
						gmVector2& v = point->m_items[i];
						glVertex2(v);
					}
					*/

					pDC->m_pGraphics2D->FillPolygon(pBrush, (LDraw::PointF*)point->m_items.GetData(), point->m_items.GetSize());
				}
				else
				{
					int i = 0;
					while (i < m_coordIndex->m_items.GetSize())
					{
						//CArray<gmVector3,gmVector3&> vertices;

						int j = i;
						int count = 0;
						while (j < m_coordIndex->m_items.GetSize())
						{
							long index = m_coordIndex->m_items[j];
							if (index == -1)
							{
								j++;
								break;
							}

							count++;
							//glVertex3(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
						//	vertices.Add(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
							j++;
						}
						//int count = j-i;

						ASSERT(count >= 3);

						pDC->m_pGraphics2D->FillPolygon(pBrush, (LDraw::PointD*)point->m_items.GetData() + i, count);

#if 0
						glBegin(GL_POLYGON);

						/*
						LDraw::gmVector3f v2 = point->m_items[coordIndex->m_items[i+2]];
						LDraw::gmVector3f v1 = point->m_items[coordIndex->m_items[i+1]];
						LDraw::gmVector3f v0 = point->m_items[coordIndex->m_items[i]];
						lglNormal(v2, v1, v0);
						*/

						if (TRUE)
						{
							for (int k = count-1; k >= 0; k--)
							{
								/*
								if (texcoordinate)
								{
									long texIndex = useTexCoordIndex->m_items[i+k];
									gmVector2& texvec = texpoint->m_items[texIndex];
									glTexCoord2f(texvec[0], texvec[1]);
								}
								*/
								gmVector2& v = point->m_items[m_coordIndex->m_items[i+k]];
								glVertex2(v);
							}
						}
						else
						{
							/*
							for (int k = 0; k < count; k++)
							{
								if (texcoordinate)
								{
									long texIndex = useTexCoordIndex->m_items[i+k];
									gmVector2& texvec = texpoint->m_items[texIndex];
									glTexCoord2f(texvec[0], texvec[1]);
								}
								LDraw::gmVector3f& v = point->m_items[coordIndex->m_items[i+k]];
								glVertex3(v);
							}
							*/
						}

						i = j;

						glEnd();
#endif
					}
				}
			}
			else
			{
				int i = 0;
				while (i < m_coordIndex->m_items.GetSize())
				{
					//CArray<gmVector3,gmVector3&> vertices;

					int j = i;
					int count = 0;
					while (j < m_coordIndex->m_items.GetSize())
					{
						long index = m_coordIndex->m_items[j];
						if (index == -1)
						{
							j++;
							break;
						}

						count++;
						//glVertex3(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
					//	vertices.Add(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
						j++;
					}
					//int count = j-i;

					ASSERT(count >= 3);

					pDC->m_pGraphics3D->glBegin(GL_LINE_STRIP);

					/*
					LDraw::gmVector3f v2 = point->m_items[coordIndex->m_items[i+2]];
					LDraw::gmVector3f v1 = point->m_items[coordIndex->m_items[i+1]];
					LDraw::gmVector3f v0 = point->m_items[coordIndex->m_items[i]];
					lglNormal(v2, v1, v0);
					*/

					if (true)
					{
						for (int k = count-1; k >= 0; k--)
						{
							/*
							if (texcoordinate)
							{
								long texIndex = useTexCoordIndex->m_items[i+k];
								gmVector2& texvec = texpoint->m_items[texIndex];
								glTexCoord2f(texvec[0], texvec[1]);
							}
							*/
							LDraw::vector2f& v = point->m_items[m_coordIndex->m_items[i+k]];
							pDC->m_pGraphics3D->glVertex(v);
						}
					}
					else
					{
						/*
						for (int k = 0; k < count; k++)
						{
							if (texcoordinate)
							{
								long texIndex = useTexCoordIndex->m_items[i+k];
								gmVector2& texvec = texpoint->m_items[texIndex];
								glTexCoord2f(texvec[0], texvec[1]);
							}
							LDraw::gmVector3f& v = point->m_items[coordIndex->m_items[i+k]];
							glVertex3(v);
						}
						*/
					}

					i = j;

					pDC->m_pGraphics3D->glEnd();
				}
			}
		}

		return;
	}

	Coordinate2D* coordinate2D = dynamic_cast<Coordinate2D*>(m_coord->m_value);
	if (coordinate2D)
	{
		MFVec2f* point = coordinate2D->getPoint();

		//MFVec2f* texpoint;

		//MFInt32* useTexCoordIndex;

		/*
		if (texcoordinate)
		{
			texpoint = static_cast<MFVec2f*>(static_cast<CLTextureCoordinate*>(texcoordinate.p)->m_point);

			if (texCoordIndex->m_items.GetSize() > 0)
			{
				if (texCoordIndex->m_items.GetSize() != coordIndex->m_items.GetSize())
				{
					// TODO, mark this object with some kind of error flag
					// m_bError = TRUE
					return;	// Error
				}
				useTexCoordIndex = texCoordIndex;
			}
			else
			{
				useTexCoordIndex = coordIndex;
			}
		}
		*/

		if (m_convex->m_value != false)
		{
			if (m_coordIndex->m_items.GetSize() == 0)
			{
				pDC->m_pGraphics3D->glBegin(GL_POLYGON);

				for (int i = 0; i < point->m_items.GetSize(); i++)
				{
					LDraw::vector2f& v = point->m_items[i];
					pDC->m_pGraphics3D->glVertex(v);
				}

				pDC->m_pGraphics3D->glEnd();
			}
			else
			{
				int i = 0;
				while (i < m_coordIndex->m_items.GetSize())
				{
					//CArray<gmVector3,gmVector3&> vertices;

					int j = i;
					int count = 0;
					while (j < m_coordIndex->m_items.GetSize())
					{
						long index = m_coordIndex->m_items[j];
						if (index == -1)
						{
							j++;
							break;
						}

						count++;
						//glVertex3(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
					//	vertices.Add(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
						j++;
					}
					//int count = j-i;

					ASSERT(count >= 3);

					pDC->m_pGraphics3D->glBegin(GL_POLYGON);

					/*
					LDraw::gmVector3f v2 = point->m_items[coordIndex->m_items[i+2]];
					LDraw::gmVector3f v1 = point->m_items[coordIndex->m_items[i+1]];
					LDraw::gmVector3f v0 = point->m_items[coordIndex->m_items[i]];
					lglNormal(v2, v1, v0);
					*/

					if (true)
					{
						for (int k = count-1; k >= 0; k--)
						{
							/*
							if (texcoordinate)
							{
								long texIndex = useTexCoordIndex->m_items[i+k];
								gmVector2& texvec = texpoint->m_items[texIndex];
								glTexCoord2f(texvec[0], texvec[1]);
							}
							*/
							LDraw::vector2f& v = point->m_items[m_coordIndex->m_items[i+k]];
							pDC->m_pGraphics3D->glVertex(v);
						}
					}
					else
					{
						/*
						for (int k = 0; k < count; k++)
						{
							if (texcoordinate)
							{
								long texIndex = useTexCoordIndex->m_items[i+k];
								gmVector2& texvec = texpoint->m_items[texIndex];
								glTexCoord2f(texvec[0], texvec[1]);
							}
							LDraw::gmVector3f& v = point->m_items[coordIndex->m_items[i+k]];
							glVertex3(v);
						}
						*/
					}

					i = j;

					pDC->m_pGraphics3D->glEnd();
				}
			}
		}
		else
		{
			int i = 0;
			while (i < m_coordIndex->m_items.GetSize())
			{
				//CArray<gmVector3,gmVector3&> vertices;

				int j = i;
				int count = 0;
				while (j < m_coordIndex->m_items.GetSize())
				{
					long index = m_coordIndex->m_items[j];
					if (index == -1)
					{
						j++;
						break;
					}

					count++;
					//glVertex3(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
				//	vertices.Add(static_cast<SFVec3f*>(<ILSFVec3f>(point->m_items[index]).p)->m_v);
					j++;
				}
				//int count = j-i;

				ASSERT(count >= 3);

				pDC->m_pGraphics3D->glBegin(GL_LINE_STRIP);

				/*
				LDraw::gmVector3f v2 = point->m_items[coordIndex->m_items[i+2]];
				LDraw::gmVector3f v1 = point->m_items[coordIndex->m_items[i+1]];
				LDraw::gmVector3f v0 = point->m_items[coordIndex->m_items[i]];
				lglNormal(v2, v1, v0);
				*/

				if (true)
				{
					for (int k = count-1; k >= 0; k--)
					{
						/*
						if (texcoordinate)
						{
							long texIndex = useTexCoordIndex->m_items[i+k];
							gmVector2& texvec = texpoint->m_items[texIndex];
							glTexCoord2f(texvec[0], texvec[1]);
						}
						*/
						LDraw::vector2f& v = point->m_items[m_coordIndex->m_items[i+k]];
						pDC->m_pGraphics3D->glVertex(v);
					}
				}
				else
				{
					/*
					for (int k = 0; k < count; k++)
					{
						if (texcoordinate)
						{
							long texIndex = useTexCoordIndex->m_items[i+k];
							gmVector2& texvec = texpoint->m_items[texIndex];
							glTexCoord2f(texvec[0], texvec[1]);
						}
						LDraw::gmVector3f& v = point->m_items[coordIndex->m_items[i+k]];
						glVertex3(v);
					}
					*/
				}

				i = j;

				pDC->m_pGraphics3D->glEnd();
			}
		}
	}
#endif
}

}	// x3d
}
