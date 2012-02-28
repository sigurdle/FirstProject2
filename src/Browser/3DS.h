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
#ifndef __3DSBIN_H__
#define __3DSBIN_H__

#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

//------ Id Chunk

#define MAIN3DS       0x4D4D

//------ Main Chunks

#define EDIT3DS       0x3D3D  // this is the start of the editor config
#define KEYF3DS       0xB000  // this is the start of the keyframer config

//------ sub defines of EDIT3DS

#define EDIT_MATERIAL 0xAFFF
#define EDIT_CONFIG1  0x0100
#define EDIT_CONFIG2  0x3E3D
#define EDIT_VIEW_P1  0x7012
#define EDIT_VIEW_P2  0x7011
#define EDIT_VIEW_P3  0x7020
#define EDIT_VIEW1    0x7001
#define EDIT_BACKGR   0x1200
#define EDIT_AMBIENT  0x2100
#define EDIT_OBJECT   0x4000

#define EDIT_UNKNW01  0x1100
#define EDIT_UNKNW02  0x1201
#define EDIT_UNKNW03  0x1300
#define EDIT_UNKNW04  0x1400
#define EDIT_UNKNW05  0x1420
#define EDIT_UNKNW06  0x1450
#define EDIT_UNKNW07  0x1500
#define EDIT_UNKNW08  0x2200
#define EDIT_UNKNW09  0x2201
#define EDIT_UNKNW10  0x2210
#define EDIT_UNKNW11  0x2300
#define EDIT_UNKNW12  0x2302 // new chunk type
#define EDIT_UNKNW13  0x3000
#define EDIT_UNKNW14  0xAFFF

//------ sub defines of EDIT_MATERIAL
#define MAT_NAME01    0xA000  // includes name (see mli doc for materials)
#define MAT_AMBIENT	0xa010 //	; followed by color chunk 	   
#define MAT_DIFFUSE	0xa020 	 //; followed by color chunk 	   
#define MAT_SPECULAR 0xa030 	 //; followed by color chunk 	 

//------ sub defines of EDIT_OBJECT

#define OBJ_TRIMESH   0x4100
#define OBJ_LIGHT     0x4600
#define OBJ_CAMERA    0x4700

#define OBJ_UNKNWN01  0x4010
#define OBJ_UNKNWN02  0x4012 //---- Could be shadow

//------ sub defines of OBJ_CAMERA
#define CAM_UNKNWN01  0x4710 // new chunk type
#define CAM_UNKNWN02  0x4720 // new chunk type

//------ sub defines of OBJ_LIGHT
#define LIT_OFF       0x4620
#define LIT_SPOT      0x4610
#define LIT_UNKNWN01  0x465A

//------ sub defines of OBJ_TRIMESH
#define TRI_VERTEXL		0x4110
#define TRI_FACEL2		0x4111 // unknown yet
#define TRI_FACEL1		0x4120
#define TRI_FACES_MAT	0x4130
#define TRI_TEX_VERTS	0x4140
#define TRI_SMOOTH		0x4150
#define TRI_LOCAL			0x4160
#define TRI_VISIBLE		0x4165

//------ sub defs of KEYF3DS

#define KEYF_UNKNWN01 0xB009
#define KEYF_UNKNWN02 0xB00A
#define KEYF_FRAMES   0xB008
#define KEYF_OBJDES   0xB002

#define KEYF_OBJHIERARCH  0xB010
#define KEYF_OBJDUMMYNAME 0xB011
#define KEYF_OBJUNKNWN01  0xB013
#define KEYF_OBJUNKNWN02  0xB014
#define KEYF_OBJUNKNWN03  0xB015  
#define KEYF_OBJPIVOT     0xB020  
#define KEYF_OBJUNKNWN04  0xB021  
#define KEYF_OBJUNKNWN05  0xB022  

//------  these define the different color chunk types
#define COL_RGB  0x0010
#define COL_TRU  0x0011
#define COL_UNK  0x0013 // unknown

//------ defines for viewport chunks

#define TOP           0x0001
#define BOTTOM        0x0002
#define LEFT          0x0003
#define RIGHT         0x0004
#define FRONT         0x0005
#define BACK          0x0006
#define USER          0x0007
#define CAMERA        0x0008 // 0xFFFF is the code read from file
#define LIGHT         0x0009
#define DISABLED      0x0010
#define BOGUS         0x0011


namespace System
{
namespace UI
{
namespace Media3D
{
class C3DSLoader
{
public:

	class Chunk
	{
	public:
		CTOR Chunk();

		void Descend(System::IO::ISequentialByteStream* m_pStream);

		void Ascend(System::IO::ISequentialByteStream* m_pStream);

		bool More(System::IO::ISequentialByteStream* m_pStream) const;

		uint16 m_id;
		ULONG m_offset;
		ULONG m_size;
	};

	class CMaterial
	{
	public:
		CTOR CMaterial()
		{
			m_name = NULL;
			m_material = NULL;
		}

		System::StringA* m_name;
	//	CComPtr<ILMaterial> m_material;

		// Actually map it to an Appearance node
#if 0	// TODO, had this
		CComPtr<ILAppearance> m_appearance;
#endif
		Material* m_material;
	};

	CTOR C3DSLoader();
	~C3DSLoader();

	int LoadInto(System::IO::ISequentialByteStream* pStream, Group* pGroup);

	vector<CMaterial*> m_materials;

	unsigned char ReadChar();
	unsigned short ReadInt();
	unsigned long ReadLong();
	float ReadFloat();

	unsigned long ReadChunkPointer();
	unsigned long GetChunkPointer();
	void ChangeChunkPointer(unsigned long temp_pointer);
	int ReadName();
	int ReadLongName();
	void ReadUnknownChunk(Chunk& ck);
	unsigned long ReadRGBColor();
	unsigned long ReadTrueColor();
	void ReadBooleanChunk(Chunk& ck, bool *boolean);
	void ReadSpotChunk(Chunk& ck);
	void ReadLightChunk(Chunk& ck);
	void ReadCameraChunk(Chunk& ck);
	void ReadVerticesChunk(Chunk& ck, IndexedFaceSet* pModel);
	void ReadTexVertsChunk(Chunk& ck, IndexedFaceSet* pModel);
	void ReadSmoothingChunk(Chunk& ck, unsigned int numb_faces);
	void ReadFacesChunk(Chunk& ck, IndexedFaceSet* geometry, Shape* shape);
	void ReadTranslationChunk(Chunk& ck);
	void ReadObjChunk(Chunk& ck, Shape* pModel);
	void ReadObjectChunk(Chunk& ck);
	void ReadBackgrChunk(Chunk& ck);
	void ReadColorChunk(Chunk& ck);
	void ReadAmbientChunk(Chunk& ck);
	void FindCameraChunk();
	void ReadViewPortChunk(Chunk& ck);
	void ReadViewChunk(Chunk& ck);
	void ReadMatDefChunk(/*ULONG size*/);
	void ReadMaterialChunk(Chunk& ck);
	void ReadEditChunk(Chunk& ck);
	void ReadKeyfChunk(Chunk& ck);
	void ReadMainChunk(Chunk& ck);
	int ReadPrimaryChunk ();
	
	ULONG Read(void* pv, ULONG cb)
	{
		ULONG nRead = m_pStream->Read(pv, cb);
		return nRead;
	}

// Methods
public:
	/*
	IMETHOD long FileTypeInfo(CIFormatFileType* lpTypeInfo);
	IMETHOD long TryLoad(CIStream* pStream);
	IMETHOD void dummy() {};
	*/
//	Object3D* Load(const sysstring& url, ISequentialByteStream* pStream);

protected:
//	FILE *bin3ds;
	unsigned long current_chunk;
	unsigned char views_read;
//	unsigned int numb_faces,numb_vertices;
	char temp_name [100];
	float trans_mat [4][4]; // translation matrix for objects
	Group* m_pScene;

	System::IO::ISequentialByteStream* m_pStream;
};

}	// Media3D
}	// UI
}	// System

#endif
