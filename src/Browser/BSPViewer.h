namespace System
{
namespace UI
{

class Camera
{
public:
	LDraw::vector3f m_pos;
	LDraw::vector3f m_forward;
	LDraw::vector3f m_up;
};

class BSPViewer : public FrameworkElement
{
public:
	CTOR BSPViewer();

	virtual void OnRender(Graphics* pGraphics);

	void set_Map(BSPFile* bspfile);

	Q3Model* m_model;

protected:

	virtual void SetOwnerWindow(VisualContentSource* pWindow);

	virtual void OnMouseDown(MouseButtonEventArgs* args);
	virtual void OnMouseUp(MouseButtonEventArgs* args);
	virtual void OnMouseMove(MouseEventArgs* args);

	LDraw::VertexDeclaration m_vertexDeclaration;
	LDraw::VertexBuffer m_vertexBuffer;
	LDraw::IndexBuffer m_indicesBuffer;
	LDraw::IndexBuffer m_triangleIndices;
	uint m_nVertices;
	uint m_nIndices;

	//LDraw::vector3f m_cameraPosition;
	Camera m_camera;

	Point m_oldmousepos;
	int m_dragging;

private:

	void RenderFace(LDraw::Graphics3D* p3D, bsp_face* face, int iface);
	void RenderNode(LDraw::Graphics3D* p3D, bsp_node* node);
	void RenderLeaf(LDraw::Graphics3D* p3D, bsp_leaf* leaf);

	void RenderFace(LDraw::Graphics3D* p3D, bsp_face_v3* face, int iface);
	void RenderNode(LDraw::Graphics3D* p3D, bsp_node_v3* node);
	void RenderLeaf(LDraw::Graphics3D* p3D, bsp_leaf_v3* leaf);

	class Texture
	{
	public:
		unsigned int m_width;
		unsigned int m_height;
	};

	struct Face
	{
		int start;
		int end;
		int lightmap_width;
		int lightmap_height;
	};

	Face* m_faces;

	BSPFile* m_bspfile;
	unsigned int* m_textureIndex;
	Texture* m_texture;
	LDraw::Texture* m_textureID;
	LDraw::Texture* m_lightmapID;
	LDraw::Texture m_lightmapsTextureName;
	map<const char*, unsigned int, cstr_less> m_textureNames;
//	LDraw::GLState* m_serverState;
//	LDraw::ClientState* m_clientState;

	bool m_initialized;
};

}	// UI
}
