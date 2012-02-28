// Read Imagine IFF FORM TDDD files
// Copyright (c) 2004 Sigurd Lerstad

#include "stdafx.h"

#include "LImagine.h"
#include "TDDDLoader.h"

struct edge
{
	long v[2];
};

/*
This is the standard way to store a polyhedron as a hierarchical
graph.

Assume that a tetrahedron is to be represented. It has got 4 vertices,
6 edge and 4 faces.

The vertex array

Index     0       1       2       3  
Data   (0,0,0) (1,0,0) (0,1,0) (0,0,1)


The edge array contains the pairs of indices (w.r.t. to the vertex
array) of the pairs of vertices making up an edge.

Index     0     1     2     3     4     5    
 Data   (0,1) (1,2) (2,0) (4,0) (4,1) (4,2)


The face array contains the triples of indices (w.r.t. to the edge
array) of the edges making up a face.

Index     0       1       2       3    
 
Data   (0,4,3) (1,5,4) (2,3,5) (0,2,1) 


In order to convert a face entry to a polygon point list pointing to
indices of (the same) point array and translating the edge sequencce
to the corresponding point sequence, you would have to retrieve for
any Faces[i] the three edges.

e0=Faces[i][0], e1=Faces[i][1], e2=Faces[i][2]

Now you retrieve 3 pairs of points for the three edges

p0 = Edges[e0][0] ; p1 = Edges[e0][1]
p2 = Edges[e1][0] ; p3 = Edges[e1][1]
p4 = Edges[e2][0] ; p5 = Edges[e2][1]

One of (p0,p1) should be identical to one of (p2,p3), the other one of
(p2,p3) to one of (p4,p5) and the other one of (p4,p5) to the other
one of (p0,p1). Otherwise the structure is not consistent (error).


Now you set

Polygon[i][0] = the common element of (p0,p1) and (p2,p3)
Polygon[i][1] = the common element of (p2,p3) and (p4,p5)
Polygon[i][2] = the common element of (p4,p5) and (p0,p1)


For my example you should get the polygon array


Index       0       1       2       3

Data     (1,3,0) (2,4,1) (0,4,2) (0,2,1)

*/

#pragma pack(push, 1)

typedef unsigned char UBYTE;
typedef unsigned short UWORD;

typedef LONG    FRACT;                /* 4 bytes */
typedef UBYTE   COLOR[3];             /* 3 bytes */

typedef struct vectors
{
	FRACT X;          /* 4 bytes */
	FRACT Y;          /* 4 bytes */
	FRACT Z;          /* 4 bytes */
}             /* 12 bytes total */
VECTOR;

typedef struct matrices
{
	VECTOR I;         /* 12 bytes */
	VECTOR J;         /* 12 bytes */
	VECTOR K;         /* 12 bytes */
}             /* 36 bytes total */
MATRIX;

typedef struct _tform
{
	VECTOR r;         /* 12 bytes - position */
	VECTOR a;         /* 12 bytes - x axis */
	VECTOR b;         /* 12 bytes - y axis */
	VECTOR c;         /* 12 bytes - z axis */
	VECTOR s;         /* 12 bytes - size */
}              /*  60 bytes total */
TFORM;

typedef struct _pthd
{
	TFORM   PData;    /* axis data */
	UWORD   inFrom;   /* previous axis number */
	UWORD   outTo;    /* next axis number */
	UWORD   flags;    /* flags for this axis */
							/*   Bit 0 - reserved - zero for "Detail Editor" paths */
							/*   Bit 1 - an axis connects in to this axis */
							/*   Bit 2 - an axis connects out of this axis */
							/*   Bits 3 thru 15 - reserved */
	UWORD   pad;      /* reserved */
}
PTHD;

typedef struct _BRS5
{
	WORD    Type;           // brush type:
	WORD    WFlags;         // brush wrapping flags:
	TFORM   TForm;          // local coordinates of brush axes.

	WORD    FullScale;      // full scale value
	WORD    MaxSeq;         // highest number for sequenced brushes
	BYTE    Subgrp[18];     // subgroup name, for "restrict to subgroup"
	BYTE    Stname[18];     // "tacking" state name - NULL terminated
	BYTE    Label[18];      // User label - NULL terminated
	FRACT   Mixing;         // "mixing intensity" (0...1) - default 1.0
	FRACT   FogLo;          // minimum fog length - for fog brushes
	FRACT   FogHi;          // maximum fog length - for fog brushes

	BYTE    FileLength;     // length of brush file name
//	BYTE    FileName[];     // brush file name (not null terminated)
	// (note: odd chunk size is possible)
}
BRS5;

#pragma pack(pop)

#define ID_TDDD	MakeID('T','D','D','D')
#define ID_SHAP	MakeID('S','H','A','P')
#define ID_POSI	MakeID('P','O','S','I')
#define ID_AXIS	MakeID('A','X','I','S')
#define ID_EDGE	MakeID('E','D','G','E')
#define ID_EDG2	MakeID('E','D','G','2')
#define ID_FACE	MakeID('F','A','C','E')
#define ID_TXT3	MakeID('T','X','T','3')
#define ID_PNTS	MakeID('P','N','T','S')
#define ID_PNT2	MakeID('P','N','T','2')
#define ID_BRS3	MakeID('B','R','S','3')
#define ID_BRS5	MakeID('B','R','S','5')
#define ID_TOBJ	MakeID('T','O','B','J')
#define ID_OBJ		MakeID('O','B','J',' ')
#define ID_DESC	MakeID('D','E','S','C')
#define ID_COLR	MakeID('C','O','L','R')
#define ID_REFL	MakeID('R','E','F','L')
#define ID_TRAN	MakeID('T','R','A','N')
#define ID_SPC1	MakeID('S','P','C','1')

/////////////////////////////////////////////////////////////////////////////
// CTDDDLoader

ILX3DNode* CTDDDLoader::ParseDESC(IStream* pStream, ILMFNode* parentChildren)
{
/*
	ProjectSuite*	sPrj;
	filterrec->basic->AcquireSuite(MMSX_Project_SuiteName, MMSX_Project_SuiteVersion, (void**)&sPrj);
	ASSERT(sPrj);
*/
	IFFRESULT	iffresult;

	IFFCHUNK	ck;
/*
	CModel* pModel = new CModel;
	pModel->type = OBJT_POLYGON;

	MMLayerRef layerRef = NULL;

		filterrec->layer->AddLayerTags(parentLayer, NULL, 'SLER', 'OB3D', NULL,
		(LAYER_UserData),	pModel,
		(TAG_DONE));
	if (!layerRef) return NULL;
*/
#if 0
	CI3DLayer* pModel = (CI3DLayer*)sBasic->CreateCmdTarget("3DLAYER");
	ASSERT(pModel);
	if (!pModel) return NULL;
	pModel->SetType(OBJT_POLYGON);
	pModel->AddLayerParams();

	parentLayer->InsertObject(pModel, NULL);
#endif

	CComPtr<ILShape> shapeNode;
	m_scene->createNode(L"Shape", (ILX3DNode**)&shapeNode);

	CComPtr<ILAppearance> appearanceNode;
	m_scene->createNode(L"Appearance", (ILX3DNode**)&appearanceNode);
	shapeNode->setAppearance(appearanceNode);

	CComPtr<ILMaterial> materialNode;
	m_scene->createNode(L"Material", (ILX3DNode**)&materialNode);

	CComPtr<ILSFNode> materialField;
	appearanceNode->getField(L"material", (ILX3DField**)&materialField);
	materialField->setValue(materialNode);

	CComPtr<ILX3DGeometryNode> geometryNode;	// Not yet known what type of geometry

	edge* edges = NULL;

	float fposi[3] = {0, 0, 0};

	do
	{
		IFFDescendChunk(pStream, &ck);

		switch (ck.ckID)
		{
		case ID_NAME:
			{
				ATLASSERT(ck.ckSize == 18);

				char name[19] = {0};
				IFFReadChunkBytes(pStream, name, 18);
#if 0
				pModel->SetName(name);
#endif
			}
			break;

		case ID_SHAP:
			{
				ATLASSERT(ck.ckSize == 4);

				WORD shape, lamp;
				IFFReadChunkBytes(pStream, &shape, 2);
				IFFReadChunkBytes(pStream, &lamp, 2);
				shape = ENDIANWORD(shape);
				lamp = ENDIANWORD(lamp);

				if (shape == 0)
				{
					MessageBox(NULL, "Sphere", "", MB_OK);
				}
				else if (shape == 2)
				{
					MessageBox(NULL, "Axis", "", MB_OK);
				}
				else if (shape == 5)
				{
					MessageBox(NULL, "Ground", "", MB_OK);
				}
				else
				{
					ATLASSERT(0);
					iffresult = -1;
				}
			}
			break;

		case ID_POSI:
			{
				ATLASSERT(ck.ckSize == sizeof(VECTOR));

				VECTOR posi;

				IFFReadChunkBytes(pStream, &posi, sizeof(VECTOR));
				posi.X = ENDIANLONG(posi.X);
				posi.Y = ENDIANLONG(posi.Y);
				posi.Z = ENDIANLONG(posi.Z);

				fposi[0] = posi.X/65536.0;
				fposi[1] = posi.Y/65536.0;
				fposi[2] = posi.Z/65536.0;

				MessageBeep(-1);	// TODO
#if 0
				pModel->FindParam('posi', 0)->SetParamTags(
					(PARAM_VECTOR_Value), fposi,
					(TAG_DONE));
#endif
			}
			break;

	/*
		case ID_AXIS:
			{
			}
			break;
	*/

		case ID_PNTS:
		case ID_PNT2:
			{
				ATLASSERT(geometryNode == NULL);
				m_scene->createNode(L"IndexedFaceSet", (ILX3DNode**)&geometryNode);

				DWORD pcount = 0;

				if (ck.ckID == ID_PNTS)
				{
					UWORD	pcountw;
					IFFReadChunkBytes(pStream, &pcountw, sizeof(UWORD));
					pcount = ENDIANWORD(pcountw);

					ATLASSERT(ck.ckSize == (2 + pcount*sizeof(VECTOR)));
				}
				else
				{
					DWORD	pcountl;
					IFFReadChunkBytes(pStream, &pcountl, sizeof(DWORD));
					pcount = ENDIANLONG(pcountl);

					ATLASSERT(ck.ckSize == (4 + pcount*sizeof(VECTOR)));
				}

#if 0
				pModel->SetVertexDataSize(pcount);
				evec3* data = pModel->GetVertexData();
#endif
				CComPtr<ILCoordinate> coordinateNode;
				m_scene->createNode(L"Coordinate", (ILX3DNode**)&coordinateNode);
				CComPtr<ILMFVec3f> pointField;
				coordinateNode->getField(L"point", (ILX3DField**)&pointField);

				CComPtr<ILSFNode> coordField;
				geometryNode->getField(L"coord", (ILX3DField**)&coordField);
				coordField->setValue(coordinateNode);

				VECTOR* buf = (VECTOR*)malloc(sizeof(VECTOR)*pcount);
				if (buf)
				{
					IFFReadChunkBytes(pStream, buf, sizeof(VECTOR)*pcount);

					for (int i = 0; i < pcount; i++)
					{
						VECTOR* pnt = &buf[i];
						pnt->X = ENDIANLONG(pnt->X);
						pnt->Y = ENDIANLONG(pnt->Y);
						pnt->Z = ENDIANLONG(pnt->Z);

						float v[3];
						v[0] = pnt->X / 65536.0;
						v[1] = pnt->Y / 65536.0;
						v[2] = pnt->Z / 65536.0;

						pointField->append1Value(v);
#if 0
						data[i].v[0] = x;
						data[i].v[1] = y;
						data[i].v[2] = z;
#endif
					}

					free(buf);
				}
			}
			break;

		case ID_EDGE:
			{
				UWORD	ecount;
				IFFReadChunkBytes(pStream, &ecount, sizeof(UWORD));
				ecount = ENDIANWORD(ecount);

				ATLASSERT(ck.ckSize == (2 + ecount*4));

				edges = new edge[ecount];
				edge* data = edges;//pModel->GetEdgeData();

				for (int i = 0; i < ecount; i++)
				{
					UWORD edg[2];
					IFFReadChunkBytes(pStream, edg, 4);
					edg[0] = ENDIANWORD(edg[0]);
					edg[1] = ENDIANWORD(edg[1]);

					data[i].v[0] = edg[0];
					data[i].v[1] = edg[1];
				}
			}
			break;

		case ID_EDG2:
			{
				ULONG	ecount;
				IFFReadChunkBytes(pStream, &ecount, sizeof(ULONG));
				ecount = ENDIANLONG(ecount);

				ATLASSERT(ck.ckSize == (4 + ecount*8));

//				pModel->SetEdgeDataSize(ecount);
//				edge* data = pModel->GetEdgeData();
				edges = new edge[ecount];
				edge* data = edges;//pModel->GetEdgeData();

				for (int i = 0; i < ecount; i++)
				{
					ULONG edge[2];
					IFFReadChunkBytes(pStream, edge, 8);
					edge[0] = ENDIANLONG(edge[0]);
					edge[1] = ENDIANLONG(edge[1]);

					data[i].v[0] = edge[0];
					data[i].v[1] = edge[1];
				}
			}
			break;

		case ID_FACE:
			{
				UWORD	fcount;
				IFFReadChunkBytes(pStream, &fcount, sizeof(UWORD));
				fcount = ENDIANWORD(fcount);

				//edge* edges = pModel->GetEdgeData();

				CComPtr<ILMFInt32> coordIndex;
				geometryNode->getField(L"coordIndex", (ILX3DField**)&coordIndex);

				ATLASSERT(ck.ckSize == (2 + fcount*6));

				for (int i = 0; i < fcount; i++)
				{
					int polyindex[3];// = pModel->AddPoly(3);

					UWORD face[3];
					IFFReadChunkBytes(pStream, face, 6);
					face[0] = ENDIANWORD(face[0]);
					face[1] = ENDIANWORD(face[1]);
					face[2] = ENDIANWORD(face[2]);

					int e0=face[0], e1=face[1], e2=face[2];

// Now you retrieve 3 pairs of points for the three edges

					int p0 = edges[e0].v[0] ; int p1 = edges[e0].v[1];
					int p2 = edges[e1].v[0] ; int p3 = edges[e1].v[1];
					int p4 = edges[e2].v[0] ; int p5 = edges[e2].v[1];

					if (p0 == p2 || p0 == p3)			polyindex[0] = p0;
					else if (p1 == p2 || p1 == p3)	polyindex[0] = p1;
					else ATLASSERT(0);

					if (p2 == p4 || p2 == p5)			polyindex[1] = p2;
					else if (p3 == p4 || p3 == p5)	polyindex[1] = p3;
					else ATLASSERT(0);

					if (p4 == p0 || p4 == p1)			polyindex[2] = p4;
					else if (p5 == p0 || p5 == p1)	polyindex[2] = p5;
					else ATLASSERT(0);

					coordIndex->append1Value(polyindex[0]);
					coordIndex->append1Value(polyindex[1]);
					coordIndex->append1Value(polyindex[2]);
					coordIndex->append1Value(-1);
				}
			}
			break;

		case ID_COLR:
			{
				BYTE pad;
				IFFReadChunkBytes(pStream, &pad, 1);

				COLOR color;
				IFFReadChunkBytes(pStream, &color, sizeof(color));

				CComPtr<ILSFColor> colorField;
				materialNode->getField(L"diffuseColor", (ILX3DField**)&colorField);

				float colorf[3] = {color[0]/255.0, color[1]/255.0, color[2]/255.0};
				colorField->setValue(colorf);
			}
			break;

		case ID_REFL:
			{
				BYTE pad;
				IFFReadChunkBytes(pStream, &pad, 1);

				COLOR color;
				IFFReadChunkBytes(pStream, &color, sizeof(color));

				//MessageBeep(-1);
			}
			break;

		case ID_TRAN:
			{
				BYTE pad;
				IFFReadChunkBytes(pStream, &pad, 1);

				COLOR color;
				IFFReadChunkBytes(pStream, &color, sizeof(color));

			}
			break;

		case ID_SPC1:
			{
				BYTE pad;
				IFFReadChunkBytes(pStream, &pad, 1);

				COLOR color;
				IFFReadChunkBytes(pStream, &color, sizeof(color));

			}
			break;

		case ID_BRS5:
			{
#if 0
				BRS5 brs5;
				char filename[258] = {0};

				IFFReadChunkBytes(pStream, &brs5, sizeof(BRS5));
				brs5.Type = ENDIANWORD(brs5.Type);
				brs5.WFlags = ENDIANWORD(brs5.WFlags);

				IFFReadChunkBytes(r, filename, brs5.FileLength);

			// Import the texture as footage into project
				if (sPrj)
				{
					MMPrjRef	prjRef = filterrec->layer->GetProject(filterrec->layerRef);
					ASSERT(prjRef);

					MMPrjItemRef itemRef = sPrj->ImportFootage(prjRef, NULL, filename, 0, NULL);

					if (itemRef)
					{
						;	// Do something with it
					}
				}
#endif
			}
			break;

/*		case ID_BRS3:
			{
			}
			break;
*/

		case ID_DESC:	// Child description
			{
#if 0	// ??
				CComPtr<ILX3DField> field;
				node->getField(L"children", &field);

				CComQIPtr<ILMFNode> children = field;
#endif

				ParseDESC(pStream, parentChildren);
			}
			break;

		default:
			IFFAscendChunk(pStream, &ck);
			ATLTRACE("%4.4s\n", &ck.ckID);
		}
	}
	while (ck.ckID != ID_TOBJ);

#if 0	// TODO have this
	pModel->Move(-fposi[0], -fposi[1], -fposi[2]);
#endif

/*
	if (sPrj)
	{
		filterrec->basic->ReleaseSuite(MMSX_Project_SuiteName, MMSX_Project_SuiteVersion);
	}
*/
	shapeNode->setGeometry(geometryNode);

	parentChildren->append1Value(shapeNode);

	delete edges;

	return shapeNode;
}

HRESULT CTDDDLoader::ParseOBJ(IStream* pStream, ILMFNode* parentChildren)
{
	IFFRESULT	iffresult;

	IFFCHUNK	ck;

	while ((iffresult = IFFDescendChunk(pStream, &ck)) == IFF_OK)
	{
		switch (ck.ckID)
		{
		case ID_DESC:
			{
				CComPtr<ILX3DNode> layerRef = ParseDESC(pStream, parentChildren);
			}
			break;

		default:
			IFFAscendChunk(pStream, &ck);
			ATLTRACE("%4.4s\n", &ck.ckID);
		}

//		iffresult = IFFAscendChunk(r, &ck);
		
		if (iffresult < IFF_EOC) break;
	}
	
	return iffresult;
}

HRESULT CTDDDLoader::ParseTDDD(IStream* pStream, ILMFNode* parentChildren)
{
	IFFRESULT iffresult;

	IFFCHUNK	ck;

	while ((iffresult = IFFDescendChunk(pStream, &ck)) == IFF_OK)
	{
		switch (ck.ckID)
		{
		case ID_OBJ:
			{
				ParseOBJ(pStream, parentChildren);
			}
			break;
			
		default:
			ATLTRACE("%4.4s\n", &ck.ckID);
		}
		
		if (iffresult < 0) break;
		
		iffresult = IFFAscendChunk(pStream, &ck);
	}

	return iffresult;
}

/*
//IMETHOD
long CImagineLoader::FileTypeInfo(CIFormatFileType* lpTypeInfo)
{
	lpTypeInfo->SetDescr("Imagine");
	lpTypeInfo->SetExts("*.iob");
//	lpTypeInfo->defext = "iob";

	return 0;
}
*/

STDMETHODIMP CTDDDLoader::Run(double tStart)
{
	return S_OK;
}

HRESULT CTDDDLoader::CInputPin::CompleteConnect(ILPin* pConnector)
{
	IFFCHUNK formck;
	IFFDescendChunk(stream, &formck);
	if (formck.ckID == ID_FORM)
	{
		if (formck.grpID == ID_TDDD)
		{
			m_scene = scene;
			hr = ParseTDDD(stream, children);
		}

		IFFAscendChunk(stream, &formck);
	}

	return S_OK;
}

#if 0
// ILX3DLoader
STDMETHODIMP CTDDDLoader::Load(/*[in]*/ IStream* stream, /*[in]*/ ILX3DScene* scene, /*[in]*/ ILMFNode* children)
{
	HRESULT hr = E_FAIL;	// Assume error

	IFFCHUNK formck;
	IFFDescendChunk(stream, &formck);
	if (formck.ckID == ID_FORM)
	{
		if (formck.grpID == ID_TDDD)
		{
			m_scene = scene;
			hr = ParseTDDD(stream, children);
		}

		IFFAscendChunk(stream, &formck);
	}

	return hr;
}
#endif
