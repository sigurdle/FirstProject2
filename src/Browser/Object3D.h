#ifndef __UI_Media3D_Object3D__h__
#define __UI_Media3D_Object3D__h__

namespace System
{

namespace UI
{

class ObjectAction
{
public:
	virtual void Do(void* p) = 0;
};

class UndoManager;

namespace Media3D
{

void OrthoReally2D(LDraw::Graphics3D* pG, double left, double right, double bottom, double top);
__release<LDraw::Matrix4> GetOrthoReally2D(double left, double right, double bottom, double top);
__release<LDraw::Matrix4> GetPerspective(double fovy, double aspect, double zNear, double zFar);

class Group;
class Shape;
class IndexedFaceSet;
class Object3D;

class Reference : public System::Object
{
public:
	CTOR Reference()
	{
		m_name = NULL;
		m_object = NULL;
		m_referencing = NULL;
	}

	System::Object* m_referencing;
	System::StringA* m_name;
	Object3D* m_object;
};

class VertexWeight
{
public:
	CTOR VertexWeight(ULONG index, float weight)
	{
		m_index = index;
		m_weight = weight;
	}
	ULONG m_index;
	float m_weight;
};

class Deformer
{
public:

	virtual LDraw::vector3f Deform(const LDraw::vector3f& v) = 0;
};

class IdentityDeformer : public Deformer
{
public:
	LDraw::vector3f Deform(const LDraw::vector3f& v)
	{
		return v;
	}
};

class Point3DfCollection : public System::Object, public IAddChild
{
public:
	CTOR Point3DfCollection();

	unsigned int GetCount()
	{
		return m_items.size();
	}

	LDraw::vector3f GetItem(unsigned int index)
	{
		return m_items[index];
	}

	void Add(LDraw::vector3f element)
	{
		m_items.push_back(element);
	}

//	vector<Point3D*> m_items;
	vector<LDraw::vector3f> m_items;

	void AddChild(System::Object* child);
	void AddText(System::StringW* text);

	void append1Value(const float value[3]);
};

class SelectedObject;

class Object3D : public DependencyObject
{
public:
	CTOR Object3D();

	System::StringA* m_name;

	__release<LDraw::Matrix4> m_transform;
	LDraw::matrix4f m_combinedTransform;

	vector<Reference*> m_references;

	bool m_bSelected;	// TODO, appended data
	SelectedObject* m_selectedObject;	// TODO, appended data

	virtual DependencyObject* GetDependencyParent();

	virtual void OnRender(LDraw::Graphics3D* pGraphics3D, int mode, Deformer* pDeformer) = 0;
};

class Geometry : public DependencyObject
{
public:
	virtual DependencyObject* GetDependencyParent();

	virtual void OnRender(Shape* pShape, LDraw::Graphics3D* pGraphics3D, int mode, Deformer* pDeformer) = 0;
};

class Bone : public System::Object
{
public:
	Reference* m_TransformNode;
	__release<LDraw::Matrix4> m_matrixOffset;

	__release<LDraw::Matrix4> m_finalMatrix;

	vector<VertexWeight> m_vertexWeights;

	IndexedFaceSet* m_IndexedFaceSet;
};

class Edge
{
public:

	CTOR Edge(unsigned int _v0, unsigned int _v1)
	{
		v[0] = _v0;
		v[1] = _v1;
	}

	unsigned int v[2];
	unsigned int face[2];
};

/*
class IndexIterator
{
public:
};
*/

class DirectedEdge
{
public:
	inline CTOR DirectedEdge(const DirectedEdge& src)
	{
		edgeindex = src.edgeindex;
	}

	inline CTOR DirectedEdge(uint index, bool backward)
	{
		edgeindex = (index<<1) | (uint)backward;
	}

	inline uint GetIndex() const
	{
		return edgeindex>>1;
	}

	inline bool IsBackward() const
	{
		return edgeindex & 1;
	}

protected:
	uint edgeindex;
};

class Face
{
public:

	/*
	void AddVertex(uint n)
	{
		m_vertex.Add(n);
	}

	vector<uint> m_vertex;
*/
	/*
	void AddEdge(DirectedEdge edge)
	{
		m_edges.Add(edge);
	}
	*/

	vector<DirectedEdge> m_edges;
};

struct EdgeList
{
	CTOR EdgeList(DirectedEdge _edge, EdgeList* _next) : edge(_edge)
	{
		next = _next;
	}

	DirectedEdge edge;
	EdgeList* next;
};

struct FaceList
{
	CTOR FaceList(uint _nface, FaceList* _next)
	{
		nface = _nface;
		next = _next;
	}

	uint nface;
	FaceList* next;
};

/*
class FaceIterator
{
public:
	Face* face;
};
*/

class IndexedFaceSet : public Geometry
{
public:
	CTOR IndexedFaceSet();

	void Transform(const LDraw::matrix4f& transform);

	vector<LDraw::vector3f> m_transformedVertices;
	vector<LDraw::vector3f> m_transformedNormals;
	vector<LDraw::vector3f> m_transformedVertexNormals;
	vector<LDraw::vector3f> m_texcoords;

	vector<Edge> m_edges;

	vector<Face> m_faces;

	vector<EdgeList*> m_vertexEdges;
	vector<FaceList*> m_vertexFaces;

	vector<LDraw::vector3f> m_faceNormals;
	vector<LDraw::vector3f> m_vertexNormals;

	virtual uint AddVertex(LDraw::vector3f v);

	virtual uint GetFaceEdges(uint nface) const
	{
		return m_faces[nface].m_edges.GetSize();
	}

	virtual uint GetFaceVertex(uint nface, uint nvertex) const
	{
		return m_edges[m_faces[nface].m_edges[nvertex].GetIndex()].v[m_faces[nface].m_edges[nvertex].IsBackward()];
	}

	virtual uint GetEdgeVertex(DirectedEdge edge, uint n) const
	{
		return m_edges[edge.GetIndex()].v[(edge.IsBackward() + n) & 1];
	}

	virtual void AddFaceEdge(uint nface, DirectedEdge edge);

	//void BuildEdges();
	virtual DirectedEdge AddEdge(uint v0, uint v1);

	Point3DfCollection* get_Points();
	void set_Points(Point3DfCollection* points);

	//IterateFaces(Face

//	System::Int32Collection* get_PointIndices();
//	void set_PointIndices(System::Int32Collection* indices);

//	Point3DCollection* get_Normals();
//	void set_Normals(Point3DCollection* points);

//	System::Int32Collection* get_NormalIndices();
//	void set_NormalIndices(System::Int32Collection* indices);

	Point3DfCollection* get_TexCoords();
	void set_TexCoords(Point3DfCollection* texcoords);

	System::UI::Int32Collection* get_TexCoordIndices();
	void set_TexCoordIndices(System::UI::Int32Collection* indices);

	virtual void OnRender(Shape* pShape, LDraw::Graphics3D* pGraphics3D, int mode, Deformer* pDeformer);

	Point3DfCollection* m_points;
//	System::Int32Collection* m_pointIndices;

//	Point3DCollection* m_normals;
//	System::Int32Collection* m_normalIndices;

	Point3DfCollection* m_texCoords;
	System::UI::Int32Collection* m_texCoordIndices;

	vector<unsigned int> m_materialFaceIndices;

	vector<Bone*> m_Bones;
};

class Texture : public Object
{
public:
	virtual LDraw::vector4f GetAt(float x, float y, float z) = 0;
};

class CloudTexture : public Texture
{
public:
	virtual LDraw::vector4f GetAt(float x, float y, float z);
};

class TexturePreview : public Control
{
public:
	CTOR TexturePreview();

	virtual void OnRender(Graphics* graphics);

	Texture* m_texture;
	LDraw::Bitmap* m_bitmap;
};

class Sphere : public Geometry
{
public:
	CTOR Sphere();
	~Sphere();

	double get_Radius() const;
	void set_Radius(double radius);

	double m_Radius;

	virtual void OnRender(Shape* pShape, LDraw::Graphics3D* pGraphics3D, Deformer* pDeformer);
};

class Box : public Geometry
{
public:
	CTOR Box();
	~Box();
};

class BezierPatch : public Geometry
{
public:
	CTOR BezierPatch();

	void set_Points(Point3DfCollection* points);

	virtual void OnRender(Shape* pShape, LDraw::Graphics3D* pGraphics3D, Deformer* pDeformer);

	Point3DfCollection* m_points;
};

class Camera : public Object3D
{
public:
	CTOR Camera();

	/*
	virtual DependencyObject* GetDependencyParent()
	{
		return NULL;
	}
	*/

	double get_FieldOfView();
	void set_FieldOfView(double fov);

	LDraw::vector3f get_Position();
	void set_Position(LDraw::vector3f position);

	bool get_Orthographic();
	void set_Orthographic(bool orthographic);

	AxisAngle get_Orientation();
	void set_Orientation(const AxisAngle& orientation);

protected:

	AxisAngle m_Orientation;
	LDraw::vector3f m_Position;
	double m_FieldOfView;
	bool m_Orthographic;

	virtual void OnRender(LDraw::Graphics3D* pGraphics3D, int mode, Deformer* pDeformer);

	virtual void Apply(LDraw::Graphics3D* pGraphics3D, double w, double h);
};

/*
class PerspectiveCamera : public Camera
{
public:
	CTOR PerspectiveCamera();

	virtual DependencyObject* GetDependencyParent()
	{
		return NULL;
	}

	Point3D* get_Position();
	void put_Position(Point3D* position);

	double get_FieldOfView();
	void set_FieldOfView(double fov);

protected:

	void Apply(LDraw::Graphics3D* pGraphics3D, double w, double h);

	Point3D* m_Position;
	double m_FieldOfView;
};
*/

class ObjectDeformer : public Object3D, public Deformer
{
public:
};

class Material : public System::Object
{
public:
	CTOR Material();

	System::StringA* m_name;

	LDraw::vector4f m_diffuseColor;
	LDraw::vector4f m_specularColor;

	unsigned int m_texName;
	LDraw::Bitmap* m_textureBitmap;
};

class Shape : public Object3D
{
public:
	CTOR Shape();
	~Shape();

	Geometry* get_Geometry();
	void set_Geometry(Geometry* geometry);

	LDraw::matrix4f m_geometryTransform;

	virtual void OnRender(LDraw::Graphics3D* pGraphics3D, int mode, Deformer* pDeformer);

	Geometry* m_Geometry;
	vector<Material*> m_materialList;
//	vector<unsigned int> m_materialFaceIndices;
};

class Object3DCollection : public System::Object, public IAddChild
{
public:
	CTOR Object3DCollection();

	void AddChild(System::Object* child);
	void AddText(System::StringW* text);

	vector<Object3D*> m_items;
};

class Group : public Object3D
{
public:
	CTOR Group();
	~Group();

	/*
	_Transform3D* m_Transform;

	_Transform3D* get_Transform();
	void put_Transform(_Transform3D* Transform);
	*/
//	__release<LDraw::Matrix4> m_transform;
//	LDraw::Matrix4 m_parentCombinedTransform;

	virtual void OnRender(LDraw::Graphics3D* pGraphics, int mode, Deformer* pDeformer);

	Object3DCollection* get_Children();
	void set_Children(Object3DCollection* children);

	Object3DCollection* m_Children;
};

/*
class Transform : public Object3D, public IAddChild
{
public:
	Transform();
	~Transform();

	void AddChild(Object child);
	void AddText(const sysstring& text);
	virtual void OnRender(LDraw::Graphics3D* pGraphics);

	std::vector<Object3D*> m_children;
};
*/

class Light : public Object3D
{
public:
	CTOR Light();

	virtual void OnRender(LDraw::Graphics3D* pGraphics, int mode, Deformer* pDeformer);

	unsigned int get_Samples();
	void set_Samples(unsigned int samples);

	LDraw::vector3f m_location;
	LDraw::vector3f m_color;
	float m_intensity;
	float m_radius;

	unsigned int m_samples;

	LDraw::vector3f m_transformedLocation;	// TODO, not have this ?
};

class View3D;
class SelectedObject;

enum ObjectMode
{
	Mode_Model,
	Mode_Axis,
	Mode_Points,
	Mode_Edges,
	Mode_Faces,
};

class AnimationKey : public System::Object
{
public:
	double m_time;
};

class Animation : public System::Object
{
public:
	Object3D* m_Target;

	vector<AnimationKey*> m_keys;
};

class MatrixAnimationKey : public AnimationKey
{
public:
	CTOR MatrixAnimationKey()
	{
		m_value = NULL;
	}

	__release<LDraw::Matrix4> m_value;
};

class MatrixAnimation : public Animation
{
public:
	CTOR MatrixAnimation()
	{
		m_Target = NULL;
	}
};

class Document3D : public System::Object
{
public:
	CTOR Document3D();

	//void MakeList();
	void Invalidate();

	map<System::StringA*, Object3D*, Ref_Less<System::StringA> > m_namedObjects;

	vector<Reference*> m_references;

	vector<Animation*> m_animations;

	//LDraw::Bitmap m_bitmap;

	double m_currentTime;

	vector<SelectedObject*> m_selectedObjects;
//	std::vector<SelectedGeometry*> m_selection;

	ObjectMode m_objectMode;

	ObjectMode get_Mode();
	void put_Mode(ObjectMode mode);

	View3D* m_views[4];

	UndoManager* m_undoManager;

	UI::Media3D::Group* m_object;

	LDraw::GLState* m_glState;
	LDraw::ClientState* m_clientState;
//	LDraw::DisplayList* m_list;

	LDraw::vector3f m_position;
	AxisAngle m_orientation;

//	int m_dragging;

	void SetCurrentTime(double currentTime);

	void UpdateScene();

	vector<Light*> m_lights;

protected:

	void ScanLights(Group* pGroup);
};

class Document3D;

class Display2 : public Control
{
public:

	/*
	int get_test()
	{
		return 0;
	}
	void put_test(int x)
	{
	}
	*/

	CTOR Display2(UI::Media3D::Group* visual);

	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);

	class Item : public System::Object//, public System::IEventListener
	{
	public:
		CTOR Item()
		{
			m_treeItem = NULL;
			m_Visual = NULL;
//			m_eventCtl = new UI::TextString(OLESTR(""));
		}

		UI::TreeItem* m_treeItem;
		UI::Media3D::Object3D* m_Visual;

//		UI::TextString* m_eventCtl;

		/*
		void handleEvent(System::Event* evt)
		{
		//	m_eventCtl->put_TextContent(evt->get_type());
			//m_treeItem->
		}
		*/
	};

	void BuildChildren(UI::TreeControl* tree, UI::Media3D::Group* visual, ITreeParent* parent);

	//virtual void handleEvent(System::Event* evt);

public:

	Item* m_item;

	UI::TreeControl* m_tree;
	UI::Media3D::Group* root;

	UI::Media3D::Document3D* m_document;
};

}	// Media3D
}	// UI
}	// System

#endif // __UI_Media3D_Object3D_h__
