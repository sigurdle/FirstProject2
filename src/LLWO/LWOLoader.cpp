// LWOLoader.cpp : Implementation of CLWOLoader
#include "stdafx.h"
#include "LLWO.h"
#include "LWOLoader.h"

/////////////////////////////////////////////////////////////////////////////
// CLWOLoader

#define ID_LWOB	MakeID('L','W','O','B')
#define ID_LWO2	MakeID('L','W','O','2')
#define ID_PNTS	MakeID('P','N','T','S')
#define ID_POLS	MakeID('P','O','L','S')
#define ID_SURF	MakeID('S','U','R','F')
#define ID_COLR	MakeID('C','O','L','R')

#if 0
long CLWObjectLoader::ParseSURF(CIStream* pStream, LPBYTE ckdata, long cksize)
{
	char* p = (char*)ckdata;
	char* endp = p + cksize;

	while (p < endp)
	{
		char* name = p;
		int namelen = 0;

	// Get name
		while (*p++ != 0) namelen++;
		if (namelen & 1) p++;

	// Get subchunks
		DWORD ckID = *(DWORD*)p;
		p += 4;
		WORD ckSize = *(WORD*)p;
		ckSize = ENDIANWORD(ckSize);
		p += 2;

		char* p2 = p;

		switch (ckID)
		{
		case ID_COLR:
			{
			}
			break;
		}

		p += ckSize;
	}

	return 0;
}
#endif

HRESULT CLWOLoader::LoadLWOB(IStream* pStream, ILMFNode* children)
{
	IFFRESULT	iffresult;

#if 0
	char filename[256];
	_splitpath(pStream->GetFileName(), NULL, NULL, filename, NULL);
#endif

	IFFCHUNK	ck;
/*
	CModel* pModel = new CModel;
	pModel->type = OBJT_POLYGON;

	MMLayerRef layerRef = NULL;

		filterrec->layer->AddLayerTags(parentRef, NULL, 'SLER', 'OB3D', NULL,
		(LAYER_Name),		filename,
		(LAYER_UserData),	pModel,
		(TAG_DONE));
	if (!layerRef) return NULL;
*/
	/*
	CI3DLayer* pModel = (CI3DLayer*)sBasic->CreateCmdTarget("3DLAYER");
	ASSERT(pModel);
	if (!pModel) return NULL;
	pModel->SetType(OBJT_POLYGON);
	pModel->SetName(filename);
	pModel->AddLayerParams();

	parentRef->InsertObject(pModel, NULL);
	*/

	float (*m_points)[3] = NULL;

	while ((iffresult = IFFDescendChunk(pStream, &ck)) == IFF_OK)
	{
		switch (ck.ckID)
		{
		case ID_PNTS:
			{
				ATLTRACE("PNTS\n");
				
				int numpoints = ck.ckSize / 12;	// 4*3 = 12

				m_points = new float[numpoints][3];

#if 0
				pModel->SetVertexDataSize(numpoints);
				evec3* data = pModel->GetVertexData();
#endif

				for (int i = 0; i < numpoints; i++)
				{
					DWORD	v[3];
					IFFReadChunkBytes(pStream, v, 12);
					
					float vf[3];
					*((DWORD*)&vf[0]) = ENDIANLONG(v[0]);
					*((DWORD*)&vf[1]) = ENDIANLONG(v[1]);
					*((DWORD*)&vf[2]) = ENDIANLONG(v[2]);
				
					m_points[i][0] = vf[0];
					m_points[i][1] = vf[1];
					m_points[i][2] = vf[2];
					
				//	data[i].v[0] = vf[0];
				//	data[i].v[1] = vf[1];
				//	data[i].v[2] = vf[2];
				}
			}
			break;
			
		case ID_POLS:
			{
				ATLTRACE("POLS\n");
				
				long size = ck.ckSize;
				
				// Read all polygons
				while (size > 0)
				{
					CComPtr<ILX3DNode> node;
					m_scene->createNode(L"IndexedFaceSet", &node);

					CComPtr<ILCoordinate> coordinateNode;
					m_scene->createNode(L"Coordinate", (ILX3DNode**)&coordinateNode);
					CComPtr<ILMFVec3f> pointField;
					coordinateNode->getField(L"point", (ILX3DField**)&pointField);

					CComPtr<ILSFNode> coordField;
					node->getField(L"coord", (ILX3DField**)&coordField);
					coordField->setValue(coordinateNode);

					CComPtr<ILMFInt32> coordIndexField;
					node->getField(L"coordIndex", (ILX3DField**)&coordIndexField);

					WORD numvertices;
					IFFReadChunkBytes(pStream, &numvertices, 2);
					numvertices = ENDIANWORD(numvertices);
					size -= 2;
					
					//int* polydata = pModel->AddPoly(numvertices);

					// Read all vertices of polygon
					for (int j = 0; j < numvertices; j++)
					{
						UWORD vertex;
						IFFReadChunkBytes(pStream, &vertex, 2);
						vertex =  ENDIANWORD(vertex);
						size -= 2;
						//polydata[j] = vertex;

						pointField->append1Value(m_points[vertex]);
						coordIndexField->append1Value(j);
					}
					
					// Surface properties of polygon
					SHORT surface;
					IFFReadChunkBytes(pStream, &surface, 2);
					surface = ENDIANWORD(surface);
					size -= 2;

					if (surface < 0)	// This polygon has detail polygons
					{
						MessageBox(NULL, "Detail polygons unsupported", "", MB_OK);
						iffresult = -1;
						break;
					}

					children->append1Value(node);
				}
			}
			break;
			
		case ID_SURF:
			{
				LPBYTE ckdata = (LPBYTE)GlobalAlloc(0, ck.ckSize);
				IFFReadChunkBytes(pStream, ckdata, ck.ckSize);

				//ParseSURF(pStream, ckdata, ck.ckSize);

				GlobalFree(ckdata);
			}
			break;

		default:
			ATLTRACE("%4.4s\n", &ck.ckID);
		}
		
		if (iffresult < 0) break;
		
		iffresult = IFFAscendChunk(pStream, &ck);
	}

	//pModel->BuildEdges();

	return S_OK;//pModel;
}

// ILX3DLoader
STDMETHODIMP CLWOLoader::Load(/*[in]*/ IStream* stream, /*[in]*/ ILX3DScene* scene, /*[in]*/ ILMFNode* children)
{
	HRESULT hr = E_FAIL;	// Assume error

	IFFCHUNK formck;
	IFFDescendChunk(stream, &formck);
	if (formck.ckID == ID_FORM)
	{
		if (formck.grpID == ID_LWOB ||
			formck.grpID == ID_LWO2)
		{
			m_scene = scene;
			hr = LoadLWOB(stream, children);
		}

		IFFAscendChunk(stream, &formck);
	}

	return hr;
}
