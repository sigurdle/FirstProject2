// TODO; UICore
#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/GUI.typeinfo"
#else
#include "GUI/GUI.h"
#endif

#ifdef __LERSTAD__
#import "../../bin/Win32/Debug/ZIP.typeinfo"
#else
#include "ZIP/ZIP.h"
#endif

namespace System
{

typedef LDraw::vector3f point3f;

#pragma pack(push,2)

struct point3s
{
	short x;
	short y;
	short z;
};

struct bsp_lump
{
	uint32    offset;     // offset (in bytes) of the data from the beginning of the file
	uint32    length;     // length (in bytes) of the data
};

struct bsp_header
{
	uint32 magic;      // magic number ("IBSP")
	uint32 version;    // version of the BSP format (38)
	bsp_lump lump[19];   // directory of the lumps
};

struct bsp_plane
{
	point3f normal;      // A, B, C components of the plane equation
	float distance;    // D component of the plane equation
	uint32 type;        // ?
};

struct bsp_plane_v3
{
	point3f normal;      // A, B, C components of the plane equation
	float distance;    // D component of the plane equation
};

struct bsp_vertex_v3
{
	LDraw::vector3f position;		// Vertex position.
	LDraw::vector2f texcoord[2];	// Vertex texture coordinates. 0=surface, 1=lightmap.
	LDraw::vector3f normal;			// Vertex normal.
	uint8 color[4];					// Vertex color. RGBA.
};

struct bsp_face
{
	uint16 plane;             // index of the plane the face is parallel to
	uint16 plane_side;        // set if the normal is parallel to the plane normal

	uint32 first_edge;        // index of the first edge (in the face edge array)
	uint16 num_edges;         // number of consecutive edges (in the face edge array)

	uint16 texture_info;      // index of the texture info structure	

	uint8 lightmap_syles[4]; // styles (bit flags) for the lightmaps
	uint32 lightmap_offset;   // offset of the lightmap (in bytes) in the lightmap lump
};

struct bsp_face_v3
{
	int32 texture;//  Texture index.
	int32 effect;//  Index into lump 12 (Effects), or -1.
	int32 type;//  Face type. 1=polygon, 2=patch, 3=mesh, 4=billboard
	int32 vertex;//  Index of first vertex.
	int32 n_vertexes;//  Number of vertices.
	int32 meshvert;//  Index of first meshvert.
	int32 n_meshverts;//  Number of meshverts.
	int32 lm_index;//  Lightmap index.  
	int32 lm_start[2];//  Corner of this face's lightmap image in lightmap.
	int32 lm_size[2];//  Size of this face's lightmap image in lightmap.
	LDraw::vector3f lm_origin;//  World space origin of lightmap.
	LDraw::vector3f lm_vecs[2];//  World space lightmap s and t unit vectors.
	LDraw::vector3f normal;//  Surface normal.
	int32 size[2];//  Patch dimensions.
};

struct bsp_edge
{
	uint16 v[2];
};

struct bsp_node
{
	uint32 plane;             // index of the splitting plane (in the plane array)

	int32 front_child;       // index of the front child node or leaf
	int32 back_child;        // index of the back child node or leaf

	point3s bbox_min;          // minimum x, y and z of the bounding box
	point3s bbox_max;          // maximum x, y and z of the bounding box

	uint16 first_face;        // index of the first face (in the face array)
	uint16 num_faces;         // number of consecutive edges (in the face array)
};

struct bsp_node_v3
{
	int32 plane;//  Plane index.  
	int32 children[2];//  Children indices. Negative numbers are leaf indices: -(leaf+1).  
	int32 mins[3];//  Integer bounding box min coord.  
	int32 maxs[3];//  Integer bounding box max coord.  
};

struct bsp_leaf
{
	uint32 brush_or;          // ?

	uint16 cluster;           // -1 for cluster indicates no visibility information
	uint16 area;              // ?

	point3s bbox_min;          // bounding box minimums
	point3s bbox_max;          // bounding box maximums

	uint16 first_leaf_face;   // index of the first face (in the face leaf array)
	uint16 num_leaf_faces;    // number of consecutive edges (in the face leaf array)

	uint16 first_leaf_brush;  // ?
	uint16 num_leaf_brushes;  // ?
};

struct bsp_leaf_v3
{
	int cluster;//  Visdata cluster index.  
	int area;//  Areaportal area.  
	int mins[3];//  Integer bounding box min coord.  
	int maxs[3];//  Integer bounding box max coord.  
	int leafface;//  First leafface for leaf.  
	int n_leaffaces;//  Number of leaffaces for leaf.  
	int leafbrush;//  First leafbrush for leaf.  
	int n_leafbrushes;//  Number of leafbrushes for leaf.  
};

struct bsp_texinfo
{
	point3f u_axis;
	float u_offset;

	point3f v_axis;
	float v_offset;
	uint32 flags;
	uint32 value;
	char texture_name[32];
	uint32 next_texinfo;
};

struct bsp_texinfo_v3
{
	char name[64];//  Texture name.  
	int32 flags;//  Surface flags.  
	int32 contents;//  Content flags.  
};

struct bsp_lightmap
{
	uint8 data[128*128*3];
};

struct wal_header
{
	char name[32];        // name of the texture

	uint32 width;           // width (in pixels) of the largest mipmap level
	uint32 height;          // height (in pixels) of the largest mipmap level

	int32 offset[4];       // byte offset of the start of each of the 4 mipmap levels

	char next_name[32];   // name of the next texture in the animation

	uint32 flags;           // ?
	uint32 contents;        // ?
	uint32 value;           // ?
};

struct pakheader
{
	char magic[4];//= "PACK";     // Name of the new WAD format
	uint32 diroffset;              // Position of WAD directory from start of file
	uint32 dirsize;                // Number of entries * 0x40 (64 char)
};

struct pakentry
{
	char filename[56];       // Name of the file, Unix style, with extension,
                               // 50 chars, padded with '\0'.
	uint32 offset;                 // Position of the entry in PACK file
	uint32 size;                   // Size of the entry in PACK file
};

#pragma pack(pop)

class PakFile
{
public:

	bool Open(const char* filename);

#ifndef __LERSTAD__
	std::FILE* m_fp;
#else
	void* m_fp;
#endif
	pakheader m_header;
	pakentry* m_entries;
	unsigned int m_nentries;
};

class BSPFile : public Object
{
public:

	char m_filename[512];

	bsp_header& header()
	{
		return *(bsp_header*)m_buffer;
	}

	char* m_buffer;

	unsigned int m_nplanes;
	bsp_plane* m_planes;
	bsp_plane_v3* m_planes_v3;

	unsigned int m_nedges;
	bsp_edge* m_edges;

	unsigned int m_nvertices;
	LDraw::vector3f* m_vertices;
	bsp_vertex_v3* m_vertices_v3;

	unsigned int m_nfaces;
	bsp_face* m_faces;

	bsp_face_v3* m_faces_v3;

	unsigned int m_nnodes;
	bsp_node* m_nodes;
	bsp_node_v3* m_nodes_v3;

	unsigned int m_nleaves;
	bsp_leaf* m_leaves;
	bsp_leaf_v3* m_leaves_v3;

	unsigned int m_nleaffaces;
	uint16* m_leaffaces;
	uint32* m_leaffaces_v3;

	unsigned int m_nfaceedges;
	uint32* m_faceedges;

	unsigned int m_ntexinfos;
	bsp_texinfo* m_texinfos;
	bsp_texinfo_v3* m_texinfos_v3;

	unsigned int m_lightmapssize;
	uint8* m_lightmaps;

	unsigned int m_nmeshverts;
	int* m_meshverts;

	unsigned int m_nlightmaps;
	bsp_lightmap* m_lightmaps_v3;
};

class MD3Model;

class Q3Texture : public Object
{
public:
	LDraw::Bitmap* m_bitmap;
	unsigned int m_id;
};

class FrameAnimation
{
public:
	int m_firstFrame;
	int m_frameCount;
};

enum
{
	BOTH_DEATH1,
	BOTH_DEAD1,
	BOTH_DEATH2,
	BOTH_DEAD2,
	BOTH_DEATH3,
	BOTH_DEAD3,

	TORSO_GESTURE, //---TEST

	TORSO_ATTACK,//		(MUST NOT CHANGE -- hand animation is synced to this)
	TORSO_ATTACK2,//	(MUST NOT CHANGE -- hand animation is synced to this)

	TORSO_DROP,//		(MUST NOT CHANGE -- hand animation is synced to this)
	TORSO_RAISE,//		(MUST NOT CHANGE -- hand animation is synced to this)

	TORSO_STAND,
	TORSO_STAND2,

	//******************************************

	LEGS_WALKCR,
	LEGS_WALK,
	LEGS_RUN,
	LEGS_BACK,
	LEGS_SWIM,
	LEGS_JUMP,
	LEGS_LAND,

	LEGS_JUMPB,
	LEGS_LANDB,

	LEGS_IDLE,
	LEGS_IDLECR,

	LEGS_TURN,

	ANIMATION_MAX
};

class ModelTiming
{
public:
	float m_headFrame;
	float m_upperFrame;
	float m_lowerFrame;
};

class Q3Model : public Object
{
public:

	void LoadAnimation(IO::ISequentialByteStream* stream);

	MD3Model* m_head;
	MD3Model* m_upper;
	MD3Model* m_lower;
// TODO
//	vector<MD3Model*> m_parts;

	FrameAnimation m_animations[ANIMATION_MAX];

	vector<Q3Texture*> m_textures;
	map<String, unsigned int> m_textureNames;
};

class MD3Model : public Object
{
public:

	struct Vertex
	{
		LDraw::vector3f position;
		LDraw::vector3f normal;
	};

	class Frame : public Object
	{
	public:
		LDraw::vector3f m_minBounds;
		LDraw::vector3f m_maxBounds;
		LDraw::vector3f m_localOrigin;
		float m_radius;
		char m_name[16];
	};

	class Tag : public Object
	{
	public:
		char m_name[64];

		struct Frame
		{
			LDraw::vector3f m_origin;
			LDraw::vector3f m_axis[3];
		};

		Frame* m_frames;

		LDraw::matrix4f GetMatrix(unsigned int nframe) const
		{
			const Frame* frame = &m_frames[nframe];

			LDraw::matrix4f mat;

			mat[0][0] = frame->m_axis[0][0];
			mat[0][1] = frame->m_axis[0][1];
			mat[0][2] = frame->m_axis[0][2];

			mat[1][0] = frame->m_axis[1][0];
			mat[1][1] = frame->m_axis[1][1];
			mat[1][2] = frame->m_axis[1][2];

			mat[2][0] = frame->m_axis[2][0];
			mat[2][1] = frame->m_axis[2][1];
			mat[2][2] = frame->m_axis[2][2];

			mat[3][0] = frame->m_origin[0];
			mat[3][1] = frame->m_origin[1];
			mat[3][2] = frame->m_origin[2];
			mat[3][3] = 1.0f;

			return mat;
		}

		LDraw::matrix4f GetMatrix(unsigned int nframe0, unsigned int nframe1, float t) const
		{
			const Frame* frame0 = &m_frames[nframe0];
			const Frame* frame1 = &m_frames[nframe1];

			LDraw::matrix4f mat;

			mat[0][0] = frame0->m_axis[0][0] + (frame1->m_axis[0][0] - frame0->m_axis[0][0])*t;
			mat[0][1] = frame0->m_axis[0][1] + (frame1->m_axis[0][1] - frame0->m_axis[0][1])*t;
			mat[0][2] = frame0->m_axis[0][2] + (frame1->m_axis[0][2] - frame0->m_axis[0][2])*t;

			mat[1][0] = frame0->m_axis[1][0] + (frame1->m_axis[1][0] - frame0->m_axis[1][0])*t;
			mat[1][1] = frame0->m_axis[1][1] + (frame1->m_axis[1][1] - frame0->m_axis[1][1])*t;
			mat[1][2] = frame0->m_axis[1][2] + (frame1->m_axis[1][2] - frame0->m_axis[1][2])*t;

			mat[2][0] = frame0->m_axis[2][0] + (frame1->m_axis[2][0] - frame0->m_axis[2][0])*t;
			mat[2][1] = frame0->m_axis[2][1] + (frame1->m_axis[2][1] - frame0->m_axis[2][1])*t;
			mat[2][2] = frame0->m_axis[2][2] + (frame1->m_axis[2][2] - frame0->m_axis[2][2])*t;

			mat[3][0] = frame0->m_origin[0] + (frame1->m_origin[0] - frame0->m_origin[0])*t;
			mat[3][1] = frame0->m_origin[1] + (frame1->m_origin[1] - frame0->m_origin[1])*t;
			mat[3][2] = frame0->m_origin[2] + (frame1->m_origin[2] - frame0->m_origin[2])*t;
			mat[3][3] = 1.0f;

			return mat;
		}
	};

	class Shader : public Object
	{
	public:
		char m_name[64];
		int m_id;
	};

	class Surface : public Object
	{
	public:
		char m_name[64];

		unsigned int m_nframes;

		unsigned int m_ntriangles;
		uint16* m_triangleIndices16;

		unsigned int m_nvertices;
		Vertex* m_vertices;
		LDraw::vector2f* m_texcoords;

		unsigned int m_indicesName;
		unsigned int m_verticesName;
		unsigned int m_texcoordsName;

		unsigned int m_vertexDeclaration;

		vector<Shader*> m_shaders;

		Q3Texture* m_texture;
	};

	int Load(IO::ISequentialByteStream* stream);
	int LoadSkin(IO::ISequentialByteStream* stream, Q3Model* model, ZIP::Archive* archive);

	void GenBuffers(LDraw::Graphics3D* p3D);

	void Render(LDraw::Graphics3D* p3D, int frame);
	void Render(LDraw::Graphics3D* p3D, int frame0, int frame1, float t);

	Q3Model* m_parent;

	vector<Frame*> m_frames;

	vector<Surface*> m_surfaces;
	map<StringA*, Surface*, Ref_Less<StringA> > m_surfaceNames;

	vector<Tag*> m_tags;
	map<StringA*, Tag*, Ref_Less<StringA> > m_tagNames;

	LDraw::Bitmap* m_textureBitmap;
	unsigned int* m_textureID;

protected:

	void ReadSurface(IO::ISequentialByteStream* stream, Surface* surface);
	void ReadVertex(IO::ISequentialByteStream* stream, Vertex* vertex);

	int8 ReadByte(IO::ISequentialByteStream* stream)
	{
		int8 v;
		if (stream->Read(&v, 1) != 1)
			raise(Exception("End of file"));
		return v;
	}

	int16 ReadInt16(IO::ISequentialByteStream* stream)
	{
		int16 v;
		if (stream->Read(&v, 2) != 2)
			raise(Exception("End of file"));
		return LittleEndian16(v);
	}

	int32 ReadInt32(IO::ISequentialByteStream* stream)
	{
		int32 v;
		if (stream->Read(&v, 4) != 4)
			raise(Exception("End of file"));
		return LittleEndian32(v);
	}

	float ReadFloat(IO::ISequentialByteStream* stream)
	{
		int32 v;
		if (stream->Read(&v, 4) != 4)
			raise(Exception("End of file"));
		v = LittleEndian32(v);
		return *(float*)&v;
	}

	LDraw::vector3f ReadVector(IO::ISequentialByteStream* stream)
	{
		return LDraw::vector3f(ReadFloat(stream), ReadFloat(stream), ReadFloat(stream));
	}

	char m_name[64];
};

/*
class BSPFile3 : public Object
{
public:

	char m_filename[512];

	bsp_header& header()
	{
		return *(bsp_header*)m_buffer;
	}

	char* m_buffer;

	unsigned int m_nplanes;
	bsp_plane* m_planes;

	unsigned int m_nedges;
	bsp_edge* m_edges;

	unsigned int m_nvertices;
	LDraw::vector3f* m_vertices;

	unsigned int m_nfaces;
	bsp_face* m_faces;

	unsigned int m_nnodes;
	bsp_node* m_nodes;

	unsigned int m_nleaves;
	bsp_leaf* m_leaves;

	unsigned int m_nleaffaces;
	uint16* m_leaffaces;

	unsigned int m_nfaceedges;
	uint32* m_faceedges;

	unsigned int m_ntexinfos;
	bsp_texinfo* m_texinfos;

	unsigned int m_lightmapssize;
	uint8* m_lightmaps;
};
*/

}

#include "BSPViewer.h"
