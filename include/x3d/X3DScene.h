#ifndef x3d_Scene_h
#define x3d_Scene_h

namespace System
{

namespace x3d
{

X3DEXT vector<X3DNode*> filter(const vector<X3DNode*>& v, bool (*pred)(X3DNode* node));
X3DEXT void foreach(const vector<X3DNode*>& v, void (*func)(X3DNode* node));

class CDef : public Object
{
public:
	CTOR CDef()
	{
		m_node = nullptr;
	}
	String m_name;
	X3DNode* m_node;
};

class X3DEXT X3DExecutionContext : public Object
{
public:
	virtual vector<ComponentInfo*>& getComponents() abstract;
	virtual EncodingID getEncoding() throw();

protected:

	EncodingID m_encoding;
};

class X3DEXT X3DScene : public X3DExecutionContext
{
public:

	CTOR X3DScene();
	virtual ~X3DScene();

	bool Load(StringIn url);

	virtual SAIProtoDeclaration* FindProto(StringIn name);
//	virtual X3DNode* FindDef(StringIn name);
//	ErrorCode readStream(IO::ISequentialByteStream* stream);
	virtual X3DNode* getNamedNode(StringIn name) throw (InvalidNodeException*);

	virtual String ToString() override;

#if 0
	ILBIFSOutput* m_bifsContext;

	STDMETHOD(getBIFSContext)(/*[out,retval]*/ ILBIFSOutput* *pVal)
	{
		*pVal = m_bifsContext;
	//	if (*pVal) (*pVal)->AddRef();
		return S_OK;
	}
	STDMETHOD(setBIFSContext)(/*[in]*/ ILBIFSOutput *newVal)
	{
		m_bifsContext = newVal;
		return S_OK;
	}
#endif

	virtual IO::TextWriter& WriteVRML(IO::TextWriter& stream);

	virtual String getSpecificationVersion() throw ();
	virtual String getWorldURL() throw ();

	String get_WorldURL() throw ()
	{
		return getWorldURL();
	}

	String get_Title();

	String get_Profile()
	{
		return "Interchange";
	}

	String get_Comment()
	{
		return m_comment;
	}

	virtual X3DNode* CreateNodeOfType(NodeType* pNodeType);
	virtual X3DNode* createNode(StringIn name);
	virtual SAIProtoDeclaration* getProtoDeclaration(StringIn name);
	virtual MFNode* getRootNodes() throw ();
	virtual void removeRootNode(X3DNode* node);

	String getMetadata(StringIn key);
	void setMetadata(StringIn key, StringIn value);

	void addRoute(Route* route);
	void addRoute(X3DNode* sourceNode, StringIn sourceField, X3DNode* destinationNode, StringIn destinationField);

	virtual WorldInfo* get_WorldInfoNode();
	virtual X3DViewpointNode* get_Viewpoint();
	virtual X3DBackgroundNode* get_Background();
	virtual NavigationInfo* get_NavigationInfo();
	virtual Fog* get_Fog();

	virtual vector<ComponentInfo*>& getComponents() override
	{
		return m_components;
	}

	virtual void Invalidate()
	{
		Invalidated(this);
	}

	Event1<X3DScene*>& get_Invalidated()
	{
		return Invalidated;
	}

	void AddNode(X3DNode* node);
	void OnTick(double tim);

	X3DNode* NodeByType(StringIn nodeType) throw();
	vector<X3DNode*> NodesByTypeSnapshot(StringIn nodeType);

	//CLTouchSensor* m_pOver;
	vector<TouchSensor*> m_overList;
	vector<SAIProtoDeclaration*> m_protoDeclarations;
	vector<Route*> m_routes;
	vector<CDef*> m_defs;
	//X3DLayerNode* m_root;	// ??
	Layer* m_root;	// ??
	LayerSet* m_layerSet;
	Gui::Clock* m_clock;
	vector<X3DNode*> m_nodes;
//	vector<X3DLightNode*, __gc_allocator> m_lights;
	map<String, X3DNode*> m_namedNodes;
	SceneVisual3D* m_defaultView;
//	IXAudio2SubmixVoice* m_submixVoice;

protected:

	friend class SceneVisual3D;
	friend class VRMLLoader;
	friend class X3DViewpointNode;

	X3DEXT friend Object* asxml(X3DScene* scene);

	vector<ComponentInfo*> m_components;
	map<String,String> m_metadata;
	Event1<X3DScene*> Invalidated;

	ProfileDeclaration* m_profile;
	String m_version;
	String m_url;
	String m_comment;

	CriticalSection m_nodesByTypeHeaderCS;
	X3DNodeAVL m_nodesByTypeHeader;

	float m_fps;
};

}	// x3d
}	// System

#endif // x3d_Scene_h
