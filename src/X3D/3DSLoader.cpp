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
#include "LX3D.h"
#include "3ds.h"

#include "LX3DScene.h"

#define TRACE ATLTRACE

//------ global vars

char *viewports [11]={
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


/*----------------------------------------------------------------------------*/
unsigned char C3DSLoader::ReadChar (void)
{
	char v;
	ULONG nRead;
	m_pStream->Read(&v, 1, &nRead);
	return v;
}

/*----------------------------------------------------------------------------*/
unsigned short C3DSLoader::ReadInt (void)
{
	unsigned short v;

	ULONG nRead;
	m_pStream->Read(&v, 2, &nRead);
	return v;

//	unsigned short temp = ReadChar();
//	return ( temp | (ReadChar () << 8));
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadLong (void)
{
	unsigned long v;
	ULONG nRead;
	m_pStream->Read(&v, 4, &nRead);
	return v;

/*
	unsigned long temp1,temp2;
	unsigned long temp3,temp4;
	
	temp1=ReadInt ();
	temp2=ReadInt ();
	
	return (temp3+(temp4*0x10000L));
*/
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadChunkPointer (void)
{
	return (ReadLong ());
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::GetChunkPointer (void)
{
	LARGE_INTEGER li;
	li.QuadPart = 0;
	ULARGE_INTEGER pos;
		m_pStream->Seek(li, STREAM_SEEK_CUR, &pos);
	return ((long)pos.QuadPart-2); // compensate for the already read Marker
//	return (ftell (bin3ds)-2); // compensate for the already read Marker
}
/*----------------------------------------------------------------------------*/
void C3DSLoader::ChangeChunkPointer (unsigned long temp_pointer)
{
	LARGE_INTEGER li;
	li.QuadPart = temp_pointer;
	m_pStream->Seek(li, STREAM_SEEK_SET, NULL);
}
/*----------------------------------------------------------------------------*/
int C3DSLoader::ReadName (void)
{
	unsigned int teller=0;
	unsigned char letter;
	
	strcpy (temp_name,"Default name");
	
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
	
	strcpy (temp_name,"Default name");
	
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
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadUnknownChunk (unsigned int chunk_id)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	
	chunk_id=chunk_id;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
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
/*----------------------------------------------------------------------------*/
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
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadBooleanChunk (unsigned char *boolean)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	*boolean=ReadChar ();
	
	ChangeChunkPointer (current_pointer+temp_pointer); // move to the new chunk position
	return (temp_pointer);
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadSpotChunk (void)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	float target [4];
	float hotspot,falloff;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	Read(&(target [0]),sizeof (float));
	Read(&(target [1]),sizeof (float));
	Read(&(target [2]),sizeof (float));
	Read(&hotspot,sizeof (float));
	Read(&falloff,sizeof (float));
	
	TRACE("      The target of the spot is at: X:%5.2f Y:%5.2f Y:%5.2f\n",
		target [0],
		target [1],
		target [2]);
	TRACE("      The hotspot of this light is : %5.2f\n",hotspot);
	TRACE("      The falloff of this light is : %5.2f\n",falloff);
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}
/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadLightChunk (void)
{
	unsigned char end_found=FALSE,boolean;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L; // 2 id + 4 pointer
	float light_coors [3];
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	Read(&(light_coors [0]),sizeof (float));
	Read(&(light_coors [1]),sizeof (float));
	Read(&(light_coors [2]),sizeof (float));
	
	TRACE("     Found light at coordinates: X: %5.2f, Y: %5.2f,Z: %5.2f\n",
		light_coors [0],
		light_coors [1],
		light_coors [2]);

 while (end_found==FALSE)
 {
   temp_int=ReadInt ();

       switch (temp_int)
       {
        case LIT_UNKNWN01 :
                           TRACE(" Found Light unknown chunk id of %0X\n",LIT_UNKNWN01);
                           tellertje+=ReadUnknownChunk (LIT_UNKNWN01);
                           break;
        case LIT_OFF      :
                           TRACE(" Light is (on/off) chunk: %0X\n",LIT_OFF);
                           tellertje+=ReadBooleanChunk (&boolean);
                           if (boolean==TRUE)
                             TRACE("      Light is on\n");
                           else
                             TRACE("      Light is off\n");
                           break;
        case LIT_SPOT     :
                           TRACE(" Light is SpotLight: %0X\n",TRI_VERTEXL);
                           tellertje+=ReadSpotChunk ();
                           break;
        case COL_RGB      :
                           TRACE(" Found Color def (RGB) chunk id of %0X\n",temp_int);
                           tellertje+=ReadRGBColor ();
                           break;
        case COL_TRU      :
                           TRACE(" Found Color def (24bit) chunk id of %0X\n",temp_int);
                           tellertje+=ReadTrueColor ();
                           break;
        default           :break;
       }

   tellertje+=2;
   if (tellertje>=temp_pointer)
     end_found=TRUE;
 }

 ChangeChunkPointer (current_pointer+temp_pointer); 
 // move to the new chunk position
 return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadCameraChunk (void)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	float camera_eye [3];
	float camera_focus [3];
	float rotation,lens;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
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

	if ((temp_pointer-38) > 0) // this means more chunks are to follow
	{
		TRACE("     **** found extra cam chunks ****\n");
		if (ReadInt ()==CAM_UNKNWN01)
		{
			TRACE("     **** Found cam 1 type ch ****\n");
			ReadUnknownChunk (CAM_UNKNWN01);
		}
		if (ReadInt ()==CAM_UNKNWN02)
		{
			TRACE("     **** Found cam 2 type ch ****\n");
			ReadUnknownChunk (CAM_UNKNWN02);
		}
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadVerticesChunk (CLX3DNode* pModel)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	float vertices [3]; // x,y,z
	unsigned int numb_v;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	numb_vertices  =ReadInt ();
	
	TRACE("      Found (%d) number of vertices\n",numb_vertices);
	
	CLX3DNode* coordinate = m_pScene->createNode(L"Coordinate");

	CLMFVec3f* point = (CLMFVec3f*)coordinate->getField(L"point");

	CLSFNode* coord = (CLSFNode*)pModel->getField(L"coord");
	coord->setValue(coordinate);

//	ASSERT(pModel->vertexArray.GetSize() == 0);

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
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}
/*----------------------------------------------------------------------------*/ 
unsigned long C3DSLoader::ReadSmoothingChunk ()
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long smoothing;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	for (int i=0;i<numb_faces;i++)
	{
		smoothing=ReadLong();
	//	smoothing=smoothing; // compiler warnig depressor *:)
		TRACE("      The smoothing group for face [%5d] is %d\n",i,smoothing);
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadFacesChunk (ILX3DNode* geometry, ILX3DNode* shape)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned int temp_diff;
	unsigned short faces [6]; // a,b,c,Diff (Diff= AB: BC: CA: )
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	numb_faces = ReadInt ();
	TRACE("      Found (%d) number of faces\n",numb_faces);

	CComPtr<ILMFInt32> coordIndex;
	geometry->getField(L"coordIndex", (ILX3DField**)&coordIndex);

	for (int i = 0; i < numb_faces; i++)
	{
	//	int* polydata = pModel->AddPoly(3);

		faces [0]=ReadInt();
		faces [1]=ReadInt();
		faces [2]=ReadInt();

		temp_diff = ReadInt() & 0x000F;
		faces [3] = (temp_diff & 0x0004) >> 2;
		faces [4] = (temp_diff & 0x0002) >> 1;
		faces [5] = (temp_diff & 0x0001);

	
		coordIndex->append1Value(faces[0]);
		coordIndex->append1Value(faces[1]);
		coordIndex->append1Value(faces[2]);
		coordIndex->append1Value(-1);
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
	
	//BOOL end_found = FALSE;
	// subchunks
	while ((GetChunkPointer()+2) < current_pointer + temp_pointer)
	{
		WORD chunk_id = ReadInt ();
		//tellertje+=2;
		
		switch (chunk_id)
		{
		case TRI_SMOOTH:
			ReadSmoothingChunk ();
			break;
			/*
		TRACE("      No smoothing groups found, assuming autosmooth\n");
		*/
		case TRI_FACES_MAT:
			{
				ULONG cur = GetChunkPointer();
				ULONG length = ReadChunkPointer();

				TRACE("Faces Material list\n");

				ReadLongName();
				//temp_name
				{
					for (int i = 0; i < m_materials.size(); i++)
					{
						if (!stricmp(m_materials[i]->m_name.c_str(), temp_name))
						{
							CComPtr<ILSFNode> appearanceField;
							shape->getField(L"appearance", (ILX3DField**)&appearanceField);
							appearanceField->setValue(m_materials[i]->m_appearance);
							break;
						}
					}
				}

				WORD entries = ReadInt();
				for (int i = 0; i < entries; i++)
				{
				}

				ChangeChunkPointer (cur+length); 
			}
			break;
		}

		/*
		if (tellertje>=temp_pointer)
			end_found=TRUE;
			*/
	}	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadTranslationChunk (void)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
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
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadObjChunk (CLX3DNode* pShape)
{
	ILX3DGeometryNode* geometry = m_pScene->createNode(L"IndexedFaceSet");
	CLSFNode* geometryField = (CLSFNode*)pShape->getField(L"geometry");
	geometryField->setValue(geometry);

	/*
	CComPtr<ILAppearance> appearance;
	m_pScene->createNode(L"Appearance", (ILX3DNode**)&appearance);
	CComPtr<ILSFNode> appearanceField;
	pShape->getField(L"appearance", (ILX3DField**)&appearanceField);
	appearanceField->setValue(appearance);
	*/

	unsigned char end_found=FALSE,boolean=TRUE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L; // 2 id + 4 pointer
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case TRI_VERTEXL :
			TRACE(" Found Object vertices chunk id of %0X\n", temp_int);
			tellertje+=ReadVerticesChunk (geometry);
			break;

		case TRI_FACEL1  :
			TRACE(" Found Object faces (1) chunk id of %0X\n", temp_int);
			tellertje+=ReadFacesChunk (geometry, pShape);
			break;

		case TRI_TEX_VERTS:	// Mapping coordinates list
			{
				ATLTRACE("");
			}
			break;

		case TRI_FACEL2  :
			TRACE (" Found Object faces (2) chunk id of %0X\n", temp_int);
			tellertje+=ReadUnknownChunk (temp_int);
			break;

		case TRI_LOCAL  :
			TRACE(" Found Object translation chunk id of %0X\n", temp_int);
			tellertje+=ReadTranslationChunk ();
			break;

		case TRI_VISIBLE :
			TRACE(" Found Object vis/invis chunk id of %0X\n", temp_int);
			tellertje+=ReadBooleanChunk (&boolean);
			
			if (boolean==TRUE)
				TRACE("      Object is (visible)\n");
			else
				TRACE("      Object is (not visible)\n");
			break;

		default:
			TRACE(" chunk id of %0X\n", temp_int);
			break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadObjectChunk ()
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L; // 2 id + 4 pointer
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	
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

	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case OBJ_UNKNWN01: tellertje += ReadUnknownChunk (OBJ_UNKNWN01);break;
		case OBJ_UNKNWN02: tellertje += ReadUnknownChunk (OBJ_UNKNWN02);break;

		case OBJ_TRIMESH :
			{
				TRACE(" Found Obj/Mesh chunk id of %0X\n", OBJ_TRIMESH);

				CLX3DNode* pShape;
				m_pScene->createNode(L"Shape", &pShape);
				if (pShape)
				{
					tellertje += ReadObjChunk (pShape);
					m_pScene->m_root->m_children->append1Value(pShape);
				}
			}
			break;

		case OBJ_LIGHT   :
			TRACE(" Found Light chunk id of %0X\n", OBJ_LIGHT);
			tellertje+=ReadLightChunk ();
			break;

		case OBJ_CAMERA  :
			TRACE(" Found Camera chunk id of %0X\n", OBJ_CAMERA);
			tellertje+=ReadCameraChunk ();
			break;
		default:
			//TRACE(" chunk id of %0X\n", temp_int);
			break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}

#if 0
	pModel->BuildEdges();
#endif

	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadBackgrChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L; // 2 id + 4 pointer
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case COL_RGB :
			TRACE(" Found Color def (RGB) chunk id of %0X\n", temp_int);
			tellertje+=ReadRGBColor ();
			break;

		case COL_TRU :
			TRACE(" Found Color def (24bit) chunk id of %0X\n", temp_int);
			tellertje+=ReadTrueColor ();
			break;

		default:      break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadColorChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L; // 2 id + 4 pointer
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case COL_RGB :
			TRACE(" Found Color def (RGB) chunk id of %0X\n", temp_int);
			tellertje+=ReadRGBColor ();
			break;

		case COL_TRU :
			TRACE(" Found Color def (24bit) chunk id of %0X\n", temp_int);
			tellertje+=ReadTrueColor ();
			break;

		default:      break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadAmbientChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L; // 2 id + 4 pointer
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int = ReadInt ();
		
		switch (temp_int)
		{
		case COL_RGB :
			TRACE(" Found Color def (RGB) chunk id of %0X\n", temp_int);
			tellertje+=ReadRGBColor ();
			break;

		case COL_TRU :
			TRACE(" Found Color def (24bit) chunk id of %0X\n", temp_int);
			tellertje+=ReadTrueColor ();
			break;

		default:      break;
		}
		
		tellertje += 2;
		if (tellertje >= temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::FindCameraChunk (void)
{
	long temp_pointer=0L;
	
	for (int i = 0; i < 12; i++)
		ReadInt ();
	
	temp_pointer=11L;
	temp_pointer=ReadName ();
	
	if (temp_pointer == -1)
		TRACE("* No Camera name found\n");
	
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadViewPortChunk (void)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned int port,attribs;
	
	views_read++;
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	
	attribs = ReadInt ();

	if (attribs == 3)
	{
		TRACE(" active in viewport\n");
	}
	if (attribs == 5)
	{
		TRACE(" active in viewport\n");
	}
	
	for (int i = 1; i < 6; i++) ReadInt(); // read 5 ints to get to the viewport
	
	port=ReadInt ();
	if ((port==0xFFFF) || (port==0))
	{
		FindCameraChunk ();
		port=CAMERA;
	}
	
	TRACE("Reading [%s] information with id:%d\n",viewports [port],port);
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadViewChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L;
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case EDIT_VIEW_P1 :
			TRACE(" Found Viewport1 chunk id of %0X\n", temp_int);
			tellertje += ReadViewPortChunk ();
			break;

		case EDIT_VIEW_P2 :
			TRACE(" Found Viewport2 (bogus) chunk id of %0X\n", temp_int);
			tellertje += ReadUnknownChunk (EDIT_VIEW_P2);
			break;

		case EDIT_VIEW_P3 :
			TRACE(" Found Viewport chunk id of %0X\n", temp_int);
			tellertje += ReadViewPortChunk ();
			break;

		default           :break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
		
		if (views_read > 3)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadMatDefChunk (ULONG size)
{
	unsigned long current_pointer;
	unsigned long temp_pointer;
	
	current_pointer=GetChunkPointer ()-4;
	temp_pointer   = size;//ReadChunkPointer ();
	
	if (ReadLongName ()==-1)
	{
		TRACE("* No Material name found\n");
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadMaterialChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L;
	
	CMaterial* pMaterial = new CMaterial;
	m_materials.push_back(pMaterial);

	CComPtr<ILAppearance> appearance;
	m_pScene->createNode(L"Appearance", (ILX3DNode**)&appearance);
	pMaterial->m_appearance = appearance;

	CComPtr<ILMaterial> material;
	m_pScene->createNode(L"Material", (ILX3DNode**)&material);

	CComPtr<ILSFNode> materialField;
	appearance->getField(L"material", (ILX3DField**)&materialField);
	materialField->setValue(material);

	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		ULONG current = GetChunkPointer();
		ULONG size = ReadLong();
		
		switch (temp_int)
		{
		case MAT_NAME01  :
			TRACE(" Found Material def chunk id of %0X\n", temp_int);
			tellertje+=ReadMatDefChunk (size);
			pMaterial->m_name = temp_name;
			break;

		case MAT_SPECULAR:
			{
				//temp_int
				CComPtr<ILSFColor> colorField;
				material->getField(L"specularColor", (ILX3DField**)&colorField);

				WORD chunk_id = ReadInt();
				ULONG size = ReadLong();

				float rgb[3];

				if (chunk_id == COL_RGB)
				{
					Read(&rgb[0], 4);
					Read(&rgb[1], 4);
					Read(&rgb[2], 4);
				}
				else if (chunk_id == COL_TRU)
				{
					rgb[0] = ReadChar()/255.0;
					rgb[1] = ReadChar()/255.0;
					rgb[2] = ReadChar()/255.0;
				}

				colorField->setValue(rgb);
			}
			break;

		case MAT_AMBIENT:
			{
				// emissiveColor ???
				CComPtr<ILSFColor> colorField;
				material->getField(L"emissiveColor", (ILX3DField**)&colorField);

				WORD chunk_id = ReadInt();
				size = ReadLong();

				float rgb[3];

				if (chunk_id == COL_RGB)
				{
					Read(&rgb[0], 4);
					Read(&rgb[1], 4);
					Read(&rgb[2], 4);
				}
				else if (chunk_id == COL_TRU)
				{
					rgb[0] = ReadChar()/255.0;
					rgb[1] = ReadChar()/255.0;
					rgb[2] = ReadChar()/255.0;
				}

				colorField->setValue(rgb);
			}
			break;

		case MAT_DIFFUSE:
			{
				//temp_int
				CComPtr<ILSFColor> colorField;
				material->getField(L"diffuseColor", (ILX3DField**)&colorField);

				WORD chunk_id = ReadInt();
				ULONG size = ReadLong();

				float rgb[3];

				if (chunk_id == COL_RGB)
				{
					Read(&rgb[0], 4);
					Read(&rgb[1], 4);
					Read(&rgb[2], 4);
				}
				else if (chunk_id == COL_TRU)
				{
					rgb[0] = ReadChar()/255.0;
					rgb[1] = ReadChar()/255.0;
					rgb[2] = ReadChar()/255.0;
				}

				colorField->setValue(rgb);
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
				while (GetChunkPointer()+2 < current+size)
				{
					{
						WORD chunk_id = ReadInt();
						ULONG current = GetChunkPointer();
						ULONG size = ReadLong();

						if (chunk_id == 0xa300)	// MAT_MAPNAME
						{
							if (ReadLongName ()==-1)
							{
							}
							ATLTRACE("%s\n", temp_name);

							CComPtr<ILImageTexture> texture;
							m_pScene->createNode(L"ImageTexture", (ILX3DNode**)&texture);
							if (texture)
							{
								CComPtr<ILMFString> urlField;
								texture->getField(L"url", (ILX3DField**)&urlField);
								urlField->append1Value(_bstr_t(temp_name));
							}
						}

						ChangeChunkPointer (current+size); 
					}
				}
			}
			break;

		case 0xA33A:	// Texture map 2
			{
				ATLTRACE("");
			}
			break;

		default:break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadEditChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L;
	
	current_pointer=GetChunkPointer ();
	temp_pointer   =ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case EDIT_UNKNW01:tellertje+=ReadUnknownChunk (EDIT_UNKNW01);break;
		case EDIT_UNKNW02:tellertje+=ReadUnknownChunk (EDIT_UNKNW02);break;
		case EDIT_UNKNW03:tellertje+=ReadUnknownChunk (EDIT_UNKNW03);break;
		case EDIT_UNKNW04:tellertje+=ReadUnknownChunk (EDIT_UNKNW04);break;
		case EDIT_UNKNW05:tellertje+=ReadUnknownChunk (EDIT_UNKNW05);break;
		case EDIT_UNKNW06:tellertje+=ReadUnknownChunk (EDIT_UNKNW06);break;
		case EDIT_UNKNW07:tellertje+=ReadUnknownChunk (EDIT_UNKNW07);break;
		case EDIT_UNKNW08:tellertje+=ReadUnknownChunk (EDIT_UNKNW08);break;
		case EDIT_UNKNW09:tellertje+=ReadUnknownChunk (EDIT_UNKNW09);break;
		case EDIT_UNKNW10:tellertje+=ReadUnknownChunk (EDIT_UNKNW10);break;
		case EDIT_UNKNW11:tellertje+=ReadUnknownChunk (EDIT_UNKNW11);break;
		case EDIT_UNKNW12:tellertje+=ReadUnknownChunk (EDIT_UNKNW12);break;
		case EDIT_UNKNW13:tellertje+=ReadUnknownChunk (EDIT_UNKNW13);break;
			
		case EDIT_MATERIAL :
			TRACE(" Found Materials chunk id of %0X\n", temp_int);
			tellertje+=ReadMaterialChunk ();
			break;

		case EDIT_VIEW1    :
			TRACE(" Found View main def chunk id of %0X\n", temp_int);
			tellertje+=ReadViewChunk ();
			break;

		case EDIT_BACKGR   :
			TRACE(" Found Backgr chunk id of %0X\n", temp_int);
			tellertje+=ReadBackgrChunk ();
			break;

		case EDIT_AMBIENT  :
			TRACE(" Found Ambient chunk id of %0X\n", temp_int);
			tellertje+=ReadAmbientChunk ();
			break;

		case EDIT_OBJECT   :
			TRACE(" Found Object chunk id of %0X\n", temp_int);
			tellertje+=ReadObjectChunk ();
			break;

		default:            break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadKeyfChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L;
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int=ReadInt ();
		
		switch (temp_int)
		{
		case KEYF_UNKNWN01 :tellertje+=ReadUnknownChunk (temp_int);break;
		case KEYF_UNKNWN02 :tellertje+=ReadUnknownChunk (temp_int);break;

		case KEYF_FRAMES:
			TRACE(" Found Keyframer frames chunk id of %0X\n", temp_int);
			tellertje+=ReadUnknownChunk (temp_int);
			break;

		case KEYF_OBJDES:
			TRACE(" Found Keyframer object description chunk id of %0X\n", temp_int);
			tellertje+=ReadUnknownChunk (temp_int);
			break;

		case EDIT_VIEW1    :
			TRACE(" Found View main def chunk id of %0X\n", temp_int);
			tellertje+=ReadViewChunk ();
			break;

		default:            break;
		}
		
		tellertje+=2;
		if (tellertje>=temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
unsigned long C3DSLoader::ReadMainChunk (void)
{
	unsigned char end_found=FALSE;
	unsigned int temp_int;
	unsigned long current_pointer;
	unsigned long temp_pointer;
	unsigned long tellertje=6L;
	
	current_pointer = GetChunkPointer ();
	temp_pointer = ReadChunkPointer ();
	
	while (end_found==FALSE)
	{
		temp_int = ReadInt ();
		
		switch (temp_int)
		{
		case KEYF3DS :
			TRACE(" Found *Keyframer* chunk id of %0X\n",KEYF3DS);
			tellertje+=ReadKeyfChunk ();
			break;

		case EDIT3DS :
			TRACE(" Found *Editor* chunk id of %0X\n",EDIT3DS);
			tellertje+=ReadEditChunk ();
			break;

		default:
//			char msg[256];
//			sprintf(msg, "%X", temp_int);
//			AfxMessageBox(msg);
			break;
		}
		
		tellertje+=2;
		if (tellertje >= temp_pointer)
			end_found=TRUE;
	}
	
	ChangeChunkPointer (current_pointer+temp_pointer); 
	// move to the new chunk position
	return (temp_pointer);
}

/*----------------------------------------------------------------------------*/
int C3DSLoader::ReadPrimaryChunk (void)
{
	unsigned char version;
	
	if (ReadInt ()==MAIN3DS)
	{
		TRACE(" Found Main chunk id of %0X\n", MAIN3DS);

		//---------- find version number
		LARGE_INTEGER li;
		li.QuadPart = 28L;
		m_pStream->Seek(li, STREAM_SEEK_SET, NULL);
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

		li.QuadPart = 2;
		m_pStream->Seek(li, STREAM_SEEK_SET, NULL);
		ReadMainChunk ();
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
