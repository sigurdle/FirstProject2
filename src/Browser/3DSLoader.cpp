/*----------------------------------------------------------------------------*\
     This is a lib which reads 3d-studio binary files from version 3.0
     and higher
     (v1.05)
     author: Martin van Velsen
             ( and some great help by Gert van der Spoel )
     email:  vvelsen@ronix.ptf.hro.nl
 
     If you happen to come across some variables with strange names, then
     that will possible be Dutch names, sorry for that :)

\*----------------------------------------------------------------------------*/

#include "stdafx.h"
#include "Browser.h"
#include "Object3D.h"
#include "3ds.h"

namespace System
{
using namespace IO;

namespace UI
{
namespace Media3D
{

/*
char *viewports[11] =
{
	"Bogus",
	"Top",
	"Bottom",
	"Left",
	"Right",
	"Front",
	"Back",
	"User",
	"Camera",
	"Light",
	"Disabled"
};
*/

C3DSLoader::Chunk::Chunk()
{
	m_offset = 0xffffffff;
}

void C3DSLoader::Chunk::Descend(System::IO::ISequentialByteStream* m_pStream)
{
	ASSERT(m_offset == 0xffffffff);
	m_offset = m_pStream->Seek(0, IO::STREAM_SEEK_CUR);
	m_pStream->Read(&m_id, 2);
	m_pStream->Read(&m_size, 4);
}

void C3DSLoader::Chunk::Ascend(System::IO::ISequentialByteStream* m_pStream)
{
	ASSERT(m_offset != 0xffffffff);

	ULONG cur = m_pStream->Seek(0, IO::STREAM_SEEK_CUR);

	if (cur > m_offset + m_size)
	{
		ASSERT(0);
		throw -1;
	}

	m_pStream->Seek(m_offset + m_size, IO::STREAM_SEEK_SET);
}

bool C3DSLoader::Chunk::More(System::IO::ISequentialByteStream* m_pStream) const
{
	ULONG cur = m_pStream->Seek(0, IO::STREAM_SEEK_CUR);
	return cur < (m_offset + m_size);
}

C3DSLoader::C3DSLoader()
{
	m_pStream = NULL;

	m_pScene = NULL;

//	bin3ds = NULL;
	current_chunk=0L;
	views_read=0;
//	numb_faces=0;
//	numb_vertices=0;
	temp_name[0] = 0;
	std::memset(trans_mat, 0, sizeof(trans_mat));
}

C3DSLoader::~C3DSLoader()
{
}

/*----------------------------------------------------------------------------*/
unsigned char C3DSLoader::ReadChar (void)
{
	char v;
	ULONG nRead = m_pStream->Read(&v, 1);
	return v;
}

/*----------------------------------------------------------------------------*/
unsigned short C3DSLoader::ReadInt()
{
	unsigned short v;
	ULONG nRead = m_pStream->Read(&v, 2);
	return v;
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadLong()
{
	unsigned long v;
	ULONG nRead = m_pStream->Read(&v, 4);
	return v;

/*
	unsigned long temp1,temp2;
	unsigned long temp3,temp4;
	
	temp1=ReadInt ();
	temp2=ReadInt ();
	
	return (temp3+(temp4*0x10000L));
*/
}

float C3DSLoader::ReadFloat()
{
	float v;
	ULONG nRead = m_pStream->Read(&v, 4);
	return v;
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadChunkPointer (void)
{
	return (ReadLong ());
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::GetChunkPointer (void)
{
	LONG pos = m_pStream->Seek(0, System::IO::STREAM_SEEK_CUR);
	return ((long)pos-2); // compensate for the already read Marker
//	return (ftell (bin3ds)-2); // compensate for the already read Marker
}
/*----------------------------------------------------------------------------*/
void C3DSLoader::ChangeChunkPointer (unsigned long temp_pointer)
{
	m_pStream->Seek(temp_pointer, System::IO::STREAM_SEEK_SET);
}
/*----------------------------------------------------------------------------*/
int C3DSLoader::ReadName (void)
{
	unsigned int teller=0;
	unsigned char letter;
	
	strcpy_s(temp_name,"Default name");
	
	letter=ReadChar ();
	if (letter==0) return (-1); // dummy object
	temp_name [teller]=letter;
	teller++;
	
	do
	{
		letter=ReadChar ();
		temp_name [teller]=letter;
		teller++;
	}
	while ((letter!=0) && (teller<12));
	
	temp_name [teller-1]=0;
	
	TRACE("     Found name : %s\n",temp_name);
	return (0);
}
/*----------------------------------------------------------------------------*/
int C3DSLoader::ReadLongName (void)
{
	unsigned int teller=0;
	unsigned char letter;
	
	strcpy_s(temp_name,"Default name");
	
	letter=ReadChar ();
	if (letter==0) return (-1); // dummy object
	temp_name [teller]=letter;
	teller++;
	
	do
	{
		letter=ReadChar ();
		temp_name [teller]=letter;
		teller++;
	}
	while (letter!=0);
	
	temp_name [teller-1]=0;
	
   TRACE("Found name : %s\n",temp_name);
	return (0);
}

void C3DSLoader::ReadUnknownChunk(Chunk& parentck)
{
//	unsigned long current_pointer;
//	unsigned long temp_pointer;
	
//	chunk_id=chunk_id;
	
//	current_pointer=GetChunkPointer ();
//	temp_pointer   =ReadChunkPointer ();
	
//	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
//	return (temp_pointer);
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadRGBColor (void)
{
	float rgb_val [3];
	
	for (int i=0;i<3;i++)
	{
		Read(&(rgb_val [i]),sizeof (float));
	}
	
	TRACE("     Found Color (RGB) def of: R:%5.2f,G:%5.2f,B:%5.2f\n",
		rgb_val [0],
		rgb_val [1],
		rgb_val [2]);
	
	return (12L);
}

unsigned long C3DSLoader::ReadTrueColor (void)
{
	unsigned char true_c_val [3];
	
	for (int i=0;i<3;i++)
		true_c_val [i]=ReadChar ();
	
	TRACE("     Found Color (24bit) def of: R:%d,G:%d,B:%d\n",
		true_c_val [0],
		true_c_val [1],
		true_c_val [2]);
	
	return (3L);
}

void C3DSLoader::ReadBooleanChunk(Chunk& parentck, bool *boolean)
{
//	unsigned long current_pointer;
//	unsigned long temp_pointer;
	
//	current_pointer=GetChunkPointer ();
//	temp_pointer   =ReadChunkPointer ();
	
	*boolean=ReadChar () != 0;
	
	//ChangeChunkPointer (current_pointer+temp_pointer); // move to the new chunk position
//	return (temp_pointer);
}

void C3DSLoader::ReadSpotChunk(Chunk& ck)
{
	float target [4];
	float hotspot,falloff;
	
	Read(&(target[0]), sizeof (float));
	Read(&(target[1]), sizeof (float));
	Read(&(target[2]), sizeof (float));
	Read(&hotspot, sizeof (float));
	Read(&falloff, sizeof (float));
	
	TRACE("      The target of the spot is at: X:%5.2f Y:%5.2f Y:%5.2f\n",
		target [0],
		target [1],
		target [2]);
	TRACE("      The hotspot of this light is : %5.2f\n",hotspot);
	TRACE("      The falloff of this light is : %5.2f\n",falloff);
	}

void C3DSLoader::ReadLightChunk(Chunk& ck)
{
	//bool boolean;
	float light_coors[3];
	
//	current_pointer=GetChunkPointer ();
//	temp_pointer   =ReadChunkPointer ();
	
	/*
	Read(&(light_coors [0]),sizeof (float));
	Read(&(light_coors [1]),sizeof (float));
	Read(&(light_coors [2]),sizeof (float));
	*/
	light_coors[0] = ReadFloat();
	light_coors[1] = ReadFloat();
	light_coors[2] = ReadFloat();
	
	TRACE("     Found light at coordinates: X: %5.2f, Y: %5.2f,Z: %5.2f\n",
		light_coors[0],
		light_coors[1],
		light_coors[2]);

	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);
		
		switch (ck.m_id)
		{
		case LIT_UNKNWN01:
			// TRACE(" Found Light unknown chunk id of %0X\n",LIT_UNKNWN01);
			ReadUnknownChunk(ck);
			break;

		case LIT_OFF:
			{
				// TRACE(" Light is (on/off) chunk: %0X\n",LIT_OFF);
				bool boolean;
				ReadBooleanChunk(ck, &boolean);
				if (boolean)
					TRACE("      Light is on\n");
				else
					TRACE("      Light is off\n");
			}
			break;

		case LIT_SPOT:
			// TRACE(" Light is SpotLight: %0X\n",TRI_VERTEXL);
			ReadSpotChunk(ck);
			break;

		case COL_RGB:
			// TRACE(" Found Color def (RGB) chunk id of %0X\n",temp_int);
			ReadRGBColor();
			break;

		case COL_TRU      :
			// TRACE(" Found Color def (24bit) chunk id of %0X\n",temp_int);
			ReadTrueColor();
			break;

		default:
			break;
		}

		ck.Ascend(m_pStream);
	}
}

void C3DSLoader::ReadCameraChunk(Chunk& ck)
{
//	unsigned long current_pointer;
//	unsigned long temp_pointer;
	float camera_eye [3];
	float camera_focus [3];
	float rotation,lens;
	
//	current_pointer=GetChunkPointer ();
//	temp_pointer   =ReadChunkPointer ();
	
	Read(&(camera_eye [0]),sizeof (float));
	Read(&(camera_eye [1]),sizeof (float));
	Read(&(camera_eye [2]),sizeof (float));
	
	TRACE("     Found Camera viewpoint at coordinates: X: %5.2f, Y: %5.2f,Z: %5.2f\n",
		camera_eye [0],
		camera_eye [1],
		camera_eye [2]);
	
	Read(&(camera_focus [0]),sizeof (float));
	Read(&(camera_focus [1]),sizeof (float));
	Read(&(camera_focus [2]),sizeof (float));
	
	TRACE("     Found Camera focus coors at coordinates: X: %5.2f, Y: %5.2f,Z: %5.2f\n",
		camera_focus [0],
		camera_focus [1],
		camera_focus [2]);
	
	Read(&rotation,sizeof (float));
	Read(&lens,sizeof (float));
	
	TRACE("     Rotation of camera is:  %5.4f\n",rotation);
	TRACE("     Lens in used camera is: %5.4fmm\n",lens);
	
	/*
	{
		CComPtr<ILX3DNode> viewpoint;
		m_pScene->createNode(L"Viewpoint", &viewpoint);

		CComPtr<ILSFVec3f> pos;
		viewpoint->getField(L"position", (ILX3DField**)&pos);

		pos->setValue(camera_eye);

		m_pScene->m_root->m_children->append1Value(viewpoint);
	}
	*/

	if (ck.More(m_pStream))//(temp_pointer-38) > 0) // this means more chunks are to follow
	{
		ASSERT(0);

		TRACE("     **** found extra cam chunks ****\n");
		if (ReadInt ()==CAM_UNKNWN01)
		{
			TRACE("     **** Found cam 1 type ch ****\n");
		//	ReadUnknownChunk (CAM_UNKNWN01);
		}
		if (ReadInt ()==CAM_UNKNWN02)
		{
			TRACE("     **** Found cam 2 type ch ****\n");
		//	ReadUnknownChunk (CAM_UNKNWN02);
		}
	}
	
//	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
//	return (temp_pointer);
}

void C3DSLoader::ReadTexVertsChunk(Chunk& ck, IndexedFaceSet* pModel)
{
//	unsigned long current_pointer = GetChunkPointer();
//	unsigned long temp_pointer = ReadChunkPointer();

	uint16 num_verts = ReadInt();

	Point3DfCollection* texcoords = new Point3DfCollection;
//	Int32Collection* texcoordIndices = new Int32Collection;

	texcoords->m_items.reserve(num_verts);

	for (int i = 0; i < num_verts; i++)
	{
		float u = ReadFloat();
		float v = ReadFloat();

		texcoords->m_items.push_back(LDraw::vector3f(u, v, 0));
	}

//	pModel->set_TexCoordIndices(texcoordIndices);
	pModel->set_TexCoords(texcoords);

//	ChangeChunkPointer(current_pointer+temp_pointer); 
	// move to the new chunk position
//	return (temp_pointer);
}

void C3DSLoader::ReadVerticesChunk(Chunk& ck, IndexedFaceSet* pModel)
{
//	unsigned long current_pointer;
//	unsigned long temp_pointer;
	float vertices [3]; // x,y,z
	//unsigned int numb_v;
	
//	current_pointer=GetChunkPointer ();
//	temp_pointer   =ReadChunkPointer ();
	unsigned int numb_vertices = ReadInt();
	
	TRACE("      Found (%d) number of vertices\n", numb_vertices);
	
//	CLX3DNode* coordinate = m_pScene->createNode(L"Coordinate");
	Point3DfCollection* point = new Point3DfCollection;

	//CLMFVec3f* point = (CLMFVec3f*)coordinate->getField(L"point");

//	CLSFNode* coord = (CLSFNode*)pModel->getField(L"coord");
//	coord->setValue(coordinate);

	pModel->set_Points(point);

//	pModel->SetVertexDataSize(numb_vertices);
//	evec3* data = pModel->GetVertexData();

	for (int i = 0; i < numb_vertices; i++)
	{
		Read(&(vertices [0]),sizeof (float));
		Read(&(vertices [1]),sizeof (float));
		Read(&(vertices [2]),sizeof (float));

		/*
		data[i].v[0] = vertices [0];
		data[i].v[1] = vertices [1];
		data[i].v[2] = vertices [2];
		*/
		point->append1Value(vertices);

		/*
		TRACE("      Vertex nr%4d: X: %5.2f  Y: %5.2f  Z:%5.2f\n",
			i,
			vertices [0],
			vertices [1],
			vertices [2]);
			*/
	}
	
//	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
//	return (temp_pointer);
}

void C3DSLoader::ReadSmoothingChunk(Chunk& ck, unsigned int numb_faces)
{
//	unsigned long current_pointer;
//	unsigned long temp_pointer;
	unsigned long smoothing;
	
//	current_pointer=GetChunkPointer ();
//	temp_pointer   =ReadChunkPointer ();
	
	for (int i = 0; i < numb_faces; i++)
	{
		smoothing = ReadLong();
	//	smoothing=smoothing; // compiler warnig depressor *:)
		TRACE("      The smoothing group for face [%5d] is %d\n",i,smoothing);
	}
	
//	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
//	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadFacesChunk(Chunk& ck, IndexedFaceSet* geometry, Shape* shape)
{
	unsigned int temp_diff;
	unsigned short faces [6]; // a,b,c,Diff (Diff= AB: BC: CA: )
	
	unsigned int numb_faces = ReadInt();
	TRACE("      Found (%d) number of faces\n",numb_faces);

#if 0
	CComPtr<ILMFInt32> coordIndex;
	geometry->getField(L"coordIndex", (ILX3DField**)&coordIndex);
#endif
	Int32Collection* coordIndex = new Int32Collection;
	ASSERT(0);
//	geometry->set_PointIndices(coordIndex);

	for (int i = 0; i < numb_faces; i++)
	{
	//	int* polydata = pModel->AddPoly(3);

		faces[0] = ReadInt();
		faces[1] = ReadInt();
		faces[2] = ReadInt();

		temp_diff = ReadInt() & 0x000F;
		faces[3] = (temp_diff & 0x0004) >> 2;
		faces[4] = (temp_diff & 0x0002) >> 1;
		faces[5] = (temp_diff & 0x0001);

	
		coordIndex->Add(faces[0]);
		coordIndex->Add(faces[1]);
		coordIndex->Add(faces[2]);
#if 0
		coordIndex->append1Value(-1);
#endif
		/*
		polydata[0] = faces[0];
		polydata[1] = faces[1];
		polydata[2] = faces[2];
		*/

		/*
		TRACE("      Face nr:%d, A: %d  B: %d  C:%d , AB:%d  BC:%d  CA:%d\n",
			i,
			faces [0],
			faces [1],
			faces [2],
			faces [3],
			faces [4],
			faces [5]);
			*/
	}

	geometry->m_materialFaceIndices.resize(numb_faces);

	// subchunks
	while (ck.More(m_pStream))
	{
		Chunk chunk;
		chunk.Descend(m_pStream);

		//uint16 chunk_id = ReadInt ();
		//tellertje+=2;
		
		switch (chunk.m_id)
		{
		case TRI_SMOOTH:
			ReadSmoothingChunk(ck, numb_faces);
			break;
			/*
		TRACE("      No smoothing groups found, assuming autosmooth\n");
		*/
		case TRI_FACES_MAT:
			{

				TRACE("Faces Material list\n");

				ReadLongName();

				int matIndex = -1;

				//temp_name
				{
					for (int i = 0; i < m_materials.GetSize(); i++)
					{
					//	if (!stricmp(m_materials[i]->m_name->c_str(), temp_name))
						if (!m_materials[i]->m_name->CompareNoCase(temp_name))
						{
							matIndex = i;
#if 0	// TODO
							CComPtr<ILSFNode> appearanceField;
							shape->getField(L"appearance", (ILX3DField**)&appearanceField);
							appearanceField->setValue(m_materials[i]->m_appearance);
#endif
							break;
						}
					}
				}

				int shapeMaterialIndex = shape->m_materialList.size();
				shape->m_materialList.push_back(m_materials[matIndex]->m_material);

				uint16 entries = ReadInt();
				for (int i = 0; i < entries; i++)
				{
					uint16 faceIndex = ReadInt();

					geometry->m_materialFaceIndices[faceIndex] = shapeMaterialIndex;
				}

			//	ChangeChunkPointer(cur+length);
			}
			break;
		}

		chunk.Ascend(m_pStream);
	}	
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadTranslationChunk(Chunk& ck)
{
	for (int j=0;j<4;j++)
	{
		for (int i=0;i<3;i++)
			Read(&(trans_mat [j][i]),sizeof (float));
	}
	
	trans_mat [0][3]=0;
	trans_mat [1][3]=0;
	trans_mat [2][3]=0;
	trans_mat [3][3]=1;
	
#ifdef __DEBUG__
	TRACE ("     The translation matrix is:\n");
	for (int i=0;i<4;i++)
		TRACE("      | %5.2f %5.2f %5.2f %5.2f |\n",
		trans_mat [i][0],
		trans_mat [i][1],
		trans_mat [i][2],
		trans_mat [i][3]);
#endif
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadObjChunk(Chunk& ck, Shape* pShape)
{
	IndexedFaceSet* geometry = new IndexedFaceSet;//m_pScene->createNode(L"IndexedFaceSet");
//	CLSFNode* geometryField = (CLSFNode*)pShape->getField(L"geometry");
//	geometryField->setValue(geometry);
	pShape->set_Geometry(geometry);

	/*
	CComPtr<ILAppearance> appearance;
	m_pScene->createNode(L"Appearance", (ILX3DNode**)&appearance);
	CComPtr<ILSFNode> appearanceField;
	pShape->getField(L"appearance", (ILX3DField**)&appearanceField);
	appearanceField->setValue(appearance);
	*/

	while (ck.More(m_pStream))//end_found==false)
	{
		Chunk ck;
		ck.Descend(m_pStream);

		switch (ck.m_id)
		{
		case TRI_VERTEXL :
			//TRACE(" Found Object vertices chunk id of %0X\n", temp_int);
			ReadVerticesChunk(ck, geometry);
			break;

		case TRI_FACEL1:
			//TRACE(" Found Object faces (1) chunk id of %0X\n", temp_int);
			ReadFacesChunk(ck, geometry, pShape);
			break;

		case TRI_TEX_VERTS:	// Mapping coordinates list
			ReadTexVertsChunk(ck, geometry);
			break;

		case TRI_FACEL2:
				//TRACE(" Found Object faces (2) chunk id of %0X\n", temp_int);
			ReadUnknownChunk(ck);
			break;

		case TRI_LOCAL:
			//TRACE(" Found Object translation chunk id of %0X\n", temp_int);
			ReadTranslationChunk(ck);
			break;

		case TRI_VISIBLE:
			{
			//	TRACE(" Found Object vis/invis chunk id of %0X\n", temp_int);
				bool boolean;
				ReadBooleanChunk(ck, &boolean);
				
				if (boolean)
					TRACE("      Object is (visible)\n");
				else
					TRACE("      Object is (not visible)\n");
			}
			break;

		default:
			//TRACE(" chunk id of %0X\n", temp_int);
			break;
		}
		
		ck.Ascend(m_pStream);
	}
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadObjectChunk(Chunk& ck)
{
	if (ReadName ()==-1)
	{
		TRACE("* Dummy Object found\n");
	}
	
	//ATLASSERT(0);
//	ILX3DNode* pModel = NULL;
#if 0
	CI3DLayer* pModel = (CI3DLayer*)sBasic->CreateCmdTarget("3DLAYER");
	ASSERT(pModel);
	if (!pModel) return 1;
	pModel->SetType(OBJT_POLYGON);
	pModel->SetName(temp_name);
	parentRef->InsertObject(pModel, NULL);
	pModel->AddLayerParams();
#endif

#if 0
		filterrec->layer->AddLayerTags(filterrec->layerRef, NULL, 'SLER', 'OB3D', NULL,
		(LAYER_UserData),	pModel,
		(LAYER_Name),		temp_name,
		(TAG_DONE));
#endif

	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);
		
		switch (ck.m_id)
		{
		case OBJ_UNKNWN01:
			ReadUnknownChunk(ck);
			break;

		case OBJ_UNKNWN02:
			ReadUnknownChunk(ck);
			break;

		case OBJ_TRIMESH:
			{
				//TRACE(" Found Obj/Mesh chunk id of %0X\n", OBJ_TRIMESH);

				Shape* pShape = new Shape;
				//m_pScene->createNode(L"Shape", &pShape);
				if (pShape)
				{
					ReadObjChunk(ck, pShape);

					m_pScene->m_Children->m_items.Add(pShape);
				}
			}
			break;

		case OBJ_LIGHT:
			//TRACE(" Found Light chunk id of %0X\n", OBJ_LIGHT);
			ReadLightChunk(ck);
			break;

		case OBJ_CAMERA:
			//TRACE(" Found Camera chunk id of %0X\n", OBJ_CAMERA);
			ReadCameraChunk(ck);
			break;

		default:
			//TRACE(" chunk id of %0X\n", temp_int);
			break;
		}
	
		ck.Ascend(m_pStream);
	}

#if 0
	pModel->BuildEdges();
#endif
}

void C3DSLoader::ReadBackgrChunk(Chunk& ck)
{
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);

		switch (ck.m_id)
		{
		case COL_RGB :
			//TRACE(" Found Color def (RGB) chunk id of %0X\n", temp_int);
			ReadRGBColor();
			break;

		case COL_TRU :
			//TRACE(" Found Color def (24bit) chunk id of %0X\n", temp_int);
			ReadTrueColor();
			break;

		default:
			break;
		}
	
		ck.Ascend(m_pStream);
	}
}

void C3DSLoader::ReadColorChunk(Chunk& ck)
{
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);
		//temp_int = ReadInt();
		
		switch (ck.m_id)
		{
		case COL_RGB :
			//TRACE(" Found Color def (RGB) chunk id of %0X\n", temp_int);
			ReadRGBColor();
			break;

		case COL_TRU :
			//TRACE(" Found Color def (24bit) chunk id of %0X\n", temp_int);
			ReadTrueColor();
			break;

		default:
			break;
		}
		
		ck.Ascend(m_pStream);
	}
}

void C3DSLoader::ReadAmbientChunk(Chunk& ck)
{
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);

		switch (ck.m_id)
		{
		case COL_RGB :
			//TRACE(" Found Color def (RGB) chunk id of %0X\n", temp_int);
			ReadRGBColor();
			break;

		case COL_TRU :
			//TRACE(" Found Color def (24bit) chunk id of %0X\n", temp_int);
			ReadTrueColor();
			break;

		default:
			break;
		}
		
		ck.Ascend(m_pStream);
	}
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::FindCameraChunk()
{
	//long temp_pointer=0L;
	
	for (int i = 0; i < 12; i++)
		ReadInt ();
	
	//temp_pointer=11L;
	ReadName();
	
	/*
	if (temp_pointer == -1)
		TRACE("* No Camera name found\n");
		*/
	
	//return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadViewPortChunk(Chunk& ck)
{
	unsigned int port,attribs;
	
	views_read++;
	
	attribs = ReadInt();

	if (attribs == 3)
	{
		TRACE(" active in viewport\n");
	}

	if (attribs == 5)
	{
		TRACE(" active in viewport\n");
	}
	
	for (int i = 1; i < 6; i++)
	{
		ReadInt(); // read 5 ints to get to the viewport
	}
	
	port=ReadInt ();
	if ((port==0xFFFF) || (port==0))
	{
		FindCameraChunk();
		port=CAMERA;
	}
	
//	TRACE("Reading [%s] information with id:%d\n",viewports [port],port);
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadViewChunk(Chunk& ck)
{
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);
		
		switch (ck.m_id)
		{
		case EDIT_VIEW_P1:
			//TRACE(" Found Viewport1 chunk id of %0X\n", temp_int);
			ReadViewPortChunk(ck);
			break;

		case EDIT_VIEW_P2:
			//TRACE(" Found Viewport2 (bogus) chunk id of %0X\n", temp_int);
			ReadUnknownChunk(ck);
			break;

		case EDIT_VIEW_P3:
		//	TRACE(" Found Viewport chunk id of %0X\n", temp_int);
			ReadViewPortChunk(ck);
			break;

		default:
			break;
		}
	
		ck.Ascend(m_pStream);
		
		if (views_read > 3)
			break;
	}
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadMatDefChunk()
{
	if (ReadLongName ()==-1)
	{
		TRACE("* No Material name found\n");
	}
}

void C3DSLoader::ReadMaterialChunk(Chunk& ck)
{
	CMaterial* pMaterial;

	pMaterial = new CMaterial;
	pMaterial->m_material = new Material;
	m_materials.Add(pMaterial);

	// TOOD
#if 0
	CComPtr<ILAppearance> appearance;
	m_pScene->createNode(L"Appearance", (ILX3DNode**)&appearance);
	pMaterial->m_appearance = appearance;

	CComPtr<ILMaterial> material;
	m_pScene->createNode(L"Material", (ILX3DNode**)&material);

	CComPtr<ILSFNode> materialField;
	appearance->getField(L"material", (ILX3DField**)&materialField);
	materialField->setValue(material);
#endif

	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);

		switch (ck.m_id)
		{
		case MAT_NAME01:
		//	TRACE(" Found Material def chunk id of %0X\n", temp_int);

	//		mpMaterial = new Material;

			ASSERT(pMaterial->m_name == NULL);
			if (pMaterial->m_name != NULL)
			{
				TRACE("Warning: name specified more than once\n");
			}

			ReadMatDefChunk();

			pMaterial->m_name = new StringA(string_copy(temp_name));
			pMaterial->m_material->m_name = pMaterial->m_name;
			break;

		case MAT_SPECULAR:
			{
				//temp_int
#if 0	// TODO
				CComPtr<ILSFColor> colorField;
				material->getField(L"specularColor", (ILX3DField**)&colorField);
#endif

				Chunk ck;
				ck.Descend(m_pStream);

				float rgb[3];

				if (ck.m_id == COL_RGB)
				{
					Read(&rgb[0], 4);
					Read(&rgb[1], 4);
					Read(&rgb[2], 4);
				}
				else if (ck.m_id == COL_TRU)
				{
					rgb[0] = ReadChar()/255.0;
					rgb[1] = ReadChar()/255.0;
					rgb[2] = ReadChar()/255.0;
				}

				pMaterial->m_material->m_specularColor[0] = rgb[0];
				pMaterial->m_material->m_specularColor[1] = rgb[1];
				pMaterial->m_material->m_specularColor[2] = rgb[2];
				pMaterial->m_material->m_specularColor[3] = 1;

#if 0	// TODO
				colorField->setValue(rgb);
#endif
				ck.Ascend(m_pStream);
			}
			break;

		case MAT_AMBIENT:
			{
				// emissiveColor ???
#if 0	// TODO
				CComPtr<ILSFColor> colorField;
				material->getField(L"emissiveColor", (ILX3DField**)&colorField);
#endif

			//	uint16 chunk_id = ReadInt();
			//	size = ReadLong();
				Chunk ck;
				ck.Descend(m_pStream);

				float rgb[3];

				if (ck.m_id == COL_RGB)
				{
					Read(&rgb[0], 4);
					Read(&rgb[1], 4);
					Read(&rgb[2], 4);
				}
				else if (ck.m_id == COL_TRU)
				{
					rgb[0] = ReadChar()/255.0;
					rgb[1] = ReadChar()/255.0;
					rgb[2] = ReadChar()/255.0;
				}

#if 0	// TODO
				colorField->setValue(rgb);
#endif
				ck.Ascend(m_pStream);
			}
			break;

		case MAT_DIFFUSE:
			{
#if 0	// TODO
				CComPtr<ILSFColor> colorField;
				material->getField(L"diffuseColor", (ILX3DField**)&colorField);
#endif
			//	uint16 chunk_id = ReadInt();
			//	ULONG size = ReadLong();
				Chunk ck;
				ck.Descend(m_pStream);

				float rgb[3];

				if (ck.m_id == COL_RGB)
				{
					Read(&rgb[0], 4);
					Read(&rgb[1], 4);
					Read(&rgb[2], 4);
				}
				else if (ck.m_id == COL_TRU)
				{
					rgb[0] = ReadChar()/255.0;
					rgb[1] = ReadChar()/255.0;
					rgb[2] = ReadChar()/255.0;
				}

				pMaterial->m_material->m_diffuseColor[0] = rgb[0];
				pMaterial->m_material->m_diffuseColor[1] = rgb[1];
				pMaterial->m_material->m_diffuseColor[2] = rgb[2];
				pMaterial->m_material->m_diffuseColor[3] = 1;
#if 0	// TODO
				colorField->setValue(rgb);
#endif
				ck.Ascend(m_pStream);
			}
			break;

#if 0
		case MAT_AMBIENT:
		case MAT_DIFFUSE:
			{
				tellertje += ReadColorChunk();
				/*
				temp_int=ReadInt ();
		
				switch (temp_int)
				{
				case COL_RGB :
					tellertje+=ReadRGBColor ();
				}
			//tellertje+=ReadMatDefChunk ();
			*/
			}
			break;
#endif

		case 0xA200:	// MAT_TEXMAP Texture map 1
			{
				// Subchunks
				while (ck.More(m_pStream)/*GetChunkPointer()+2 < current+size*/)
				{
					{
						Chunk chunk;
						chunk.Descend(m_pStream);

						if (chunk.m_id == 0xa300)	// MAT_MAPNAME
						{
							if (ReadLongName ()==-1)
							{
							}
							TRACE("%s\n", temp_name);

							char buf[512];
							sprintf_s(buf, "C:/Documents and Settings/All Users/Documents/My Pictures/Sample Pictures/%s", temp_name);

						//	filename = *new StringA("C:/dxsdk/samples/Media/") + *filename;
							StringA* filename = new StringA(string_copy(buf));//*new StringA("C:/Documents and Settings/All Users/Documents/My Pictures/Sample Pictures/") + *filename;

							Imaging::BitmapLoader loader;
							LDraw::Bitmap* bitmap = loader.Load(filename);

							pMaterial->m_material->m_textureBitmap = bitmap;

							//ASSERT(0);
#if 0	// TODO
							CComPtr<ILImageTexture> texture;
							m_pScene->createNode(L"ImageTexture", (ILX3DNode**)&texture);
							if (texture)
							{
								CComPtr<ILMFString> urlField;
								texture->getField(L"url", (ILX3DField**)&urlField);
								urlField->append1Value(_bstr_t(temp_name));
							}
#endif
						}

						chunk.Ascend(m_pStream);
					}
				}
			}
			break;

		case 0xA33A:	// Texture map 2
			{
				TRACE("");
			}
			break;

		default:
			break;
		}
		
		ck.Ascend(m_pStream);
	}
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadEditChunk(Chunk& ck)
{
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);

		switch (ck.m_id)
		{
		case EDIT_UNKNW01:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW02:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW03:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW04:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW05:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW06:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW07:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW08:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW09:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW10:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW11:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW12:
			ReadUnknownChunk(ck);
			break;
		case EDIT_UNKNW13:
			ReadUnknownChunk(ck);
			break;
			
		case EDIT_MATERIAL:
			//TRACE(" Found Materials chunk id of %0X\n", temp_int);
			ReadMaterialChunk(ck);
			break;

		case EDIT_VIEW1:
			//TRACE(" Found View main def chunk id of %0X\n", temp_int);
			ReadViewChunk(ck);
			break;

		case EDIT_BACKGR:
			//TRACE(" Found Backgr chunk id of %0X\n", temp_int);
			ReadBackgrChunk(ck);
			break;

		case EDIT_AMBIENT:
		//	TRACE(" Found Ambient chunk id of %0X\n", temp_int);
			ReadAmbientChunk(ck);
			break;

		case EDIT_OBJECT:
		//	TRACE(" Found Object chunk id of %0X\n", temp_int);
			ReadObjectChunk(ck);
			break;

		default:
			break;
		}
		
		ck.Ascend(m_pStream);
	}
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadKeyfChunk(Chunk& ck)
{
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);
		
		switch (ck.m_id)
		{
		case KEYF_UNKNWN01:
			ReadUnknownChunk(ck);
			break;

		case KEYF_UNKNWN02:
			ReadUnknownChunk(ck);
			break;

		case KEYF_FRAMES:
			//TRACE(" Found Keyframer frames chunk id of %0X\n", temp_int);
			ReadUnknownChunk(ck);
			break;

		case KEYF_OBJDES:
			//TRACE(" Found Keyframer object description chunk id of %0X\n", temp_int);
			ReadUnknownChunk(ck);
			break;

		case EDIT_VIEW1:
			//TRACE(" Found View main def chunk id of %0X\n", temp_int);
			ReadViewChunk(ck);
			break;

		default:
			break;
		}
	
		ck.Ascend(m_pStream);
	}
}

/*----------------------------------------------------------------------------*/
void C3DSLoader::ReadMainChunk(Chunk& ck)
{
//	bool end_found = false;
//	unsigned int temp_int;
//	unsigned long current_pointer;
//	unsigned long temp_pointer;
//	unsigned long tellertje=6L;
	
//	current_pointer = GetChunkPointer();
//	temp_pointer = ReadChunkPointer();
	
	while (ck.More(m_pStream))
	{
		Chunk ck;
		ck.Descend(m_pStream);
		//temp_int = ReadInt();
		
		switch (ck.m_id)
		{
		case KEYF3DS:
			TRACE(" Found *Keyframer* chunk id of %0X\n",KEYF3DS);
			ReadKeyfChunk(ck);
			break;

		case EDIT3DS:
			TRACE(" Found *Editor* chunk id of %0X\n",EDIT3DS);
			ReadEditChunk(ck);
			break;

		default:
//			char msg[256];
//			sprintf(msg, "%X", temp_int);
//			AfxMessageBox(msg);
			break;
		}
	
		ck.Ascend(m_pStream);
	}
	
//	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
//	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
int C3DSLoader::ReadPrimaryChunk (void)
{
	unsigned char version;
	
	if (ReadInt ()==MAIN3DS)
	{
		TRACE(" Found Main chunk id of %0X\n", MAIN3DS);

		//---------- find version number
		m_pStream->Seek(28, System::IO::STREAM_SEEK_SET);
		version=ReadChar ();
	/*
		if (version < 3)
		{
			char msg[256];
			sprintf(msg, "Sorry this lib can only read 3ds files of version 3.0 and higher\n"
					"The version of the file you want to read is: %d\n",
					version);

			MessageBox(NULL, msg, "3DS", MB_OK);

			return (1);
		}
		*/

		m_pStream->Seek(0, System::IO::STREAM_SEEK_SET);

		Chunk ck;
		ck.Descend(m_pStream);

		ReadMainChunk(ck);

		ck.Ascend(m_pStream);
	}
	else
		return (1);
	
	return (0);
}

#if 0
//IMETHOD
long C3DSLoader::FileTypeInfo(CIFormatFileType* lpTypeInfo)
{
	lpTypeInfo->SetDescr("3D Studio");
	lpTypeInfo->SetExts("*.3ds");
//	lpTypeInfo->defext = "3ds";

	return 0;
}

// IMETHOD
long C3DSLoader::TryLoad(CIStream* pStream)
{
	void* firstBytes = pStream->GetFirstBytes();
	if (*(WORD*)firstBytes != 0x4d4d) return FORMAT_UNKNOWN;

	return 0;
}

// IMETHOD
long C3DSLoader::Load(CIStream* pStream, CI3DLayer* _parentRef)
{
	m_pStream = pStream;

	parentRef = _parentRef;

//	while (
		ReadPrimaryChunk ();
		//==0);

	return (0);
}

#endif

int C3DSLoader::LoadInto(ISequentialByteStream* pStream, Group* pGroup)
{
	m_pStream = pStream;
	m_pScene = pGroup;

	ReadPrimaryChunk();

	return 0;
}

#if 0
HRESULT C3DSLoader::Load(BSTR url, IStream* pStream, ILX3DScene** pVal)
{
	m_pStream = pStream;

	HRESULT hr;

	CComObject<CLX3DScene>* pScene;
	hr = CComObject<CLX3DScene>::CreateInstance(&pScene);
	if (SUCCEEDED(hr))
	{
		m_pScene = pScene;
		m_pScene->AddRef();
		m_pScene->m_url = url;

		/*
		CComPtr<ILX3DNode> node;
		m_pScene->createNode(L"Transform", &node);
		m_pScene->m_root = static_cast<CComObject<CLGroup>*>(node.Detach());
		*/
		//m_pScene->m_children

		ReadPrimaryChunk();

		*pVal = m_pScene;

		return S_OK;
	}
	return hr;
}
#endif

}	// Media3D
}	// UI
}	// System
