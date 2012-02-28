#ifndef x3d_X3DNode_h
#define x3d_X3DNode_h

namespace System
{
namespace x3d
{

class X3DEXT X3DNode : public Object
{
public:

	struct avlnode
	{
		X3DNode* parent_;
		X3DNode* left_;
		X3DNode* right_;
		int balance_;
	}
	bytype;

	virtual ~X3DNode();

	virtual X3DNode* GetNode()
	{
		return this;
	}

	virtual void Change(X3DField* pSourceField);
	virtual void Set(X3DField* pSourceField, X3DField* pDestField);
	virtual void OnFieldChanged(X3DField* pField);

	virtual void DoTime(double gt)
	{
	}

	NodeType* getType() const throw ();

	String getTypeName() const throw ()
	{
		return getType()->get_name();
	}

	String get_typeName() const throw ()
	{
		return getType()->get_name();
	}

	String getNodeName() const throw ()
	{
		return getType()->get_name();
	}

	virtual uint getFieldCount() throw();
	virtual X3DField* getField(uint index) throw (ArgumentOutOfRangeException*);
	virtual X3DField* getField(StringIn name) throw ();

	virtual X3DFieldDefinitions* getFieldDefinitions()
	{
		return getType()->getFieldDefinitions();
	}

//	virtual String toVRMLString();
//	virtual String toXMLString();
	virtual String ToString() override;

	virtual IO::TextWriter& WriteVRML(IO::TextWriter& stream);

#ifndef __LERSTAD__
//	X3DSFIELD(TypedSFNode<X3DMetadataObject*>, metadata, Metadata)
	X3DSFIELD(TypedSFNode<X3DNode*>, metadata, Metadata)
#else
	X3DSFIELD(SFNode, metadata, Metadata)
#endif

#if 0
///	X3DMetadataObject* getMetadata() const
	X3DMetadataObject* getMetadata()
	{
		return dynamic_cast<X3DMetadataObject*>(m_metadata->getValue());
//		return m_metadata->getValue();
	}

	void setMetadata(X3DMetadataObject* metadata);
#endif
#if 0

	TypedSFNode<X3DNode*>* getMetadataField()
	{
		return m_metadata;
	}
#endif

	MFNode* GetFirstParentOfFieldName(StringIn fieldname);
	X3DNode* GetFirstParentNodeOfFieldName(StringIn fieldname);

	virtual void addActors()
	{
	}

	virtual void UpdatePos()
	{
	}

	virtual uint32 GetLights()
	{
		return 0;
	}

	String getDefName()
	{
		return m_name;
	}

	Event2<X3DNode*, X3DField*>& get_FieldChanged()
	{
		return FieldChanged;
	}

	static NodeType* GetNodeType();
	//static X3DFieldDefinition* get_metadataFieldDef();

	bool m_selected;	// TODO? not like this?

protected:

	CTOR X3DNode(NodeType* nodeType);

	friend class X3DScene;
	friend class SFNode;
	friend class MFNode;
	friend class NodeType;
	friend class X3DPrototypeInstance;
	friend class SAIProtoDeclaration;
	friend class VRMLLoader;
	friend class COGLSceneRenderer;

	friend void DrawGlobalLightsChildren(X3DDrawContext* pDC, MFNode* children);
	friend int HitTestChildren(MFNode* children, const D3DXMATRIX& projection, const D3DXMATRIX& view, const D3DXMATRIX& model, const D3D10_VIEWPORT& vp, int type, Vec2f mousepos, Vec3f pos, IHitTest* hitTest);

	void RemoveParent(MFNode* mfnode);

/* Fields:
	SFNode [in,out] metadata NULL [X3DMetadataObject]
*/

//	TypedSFNode<X3DMetadataObject*>* m_metadata;
//	TypedSFNode<X3DNode*>* m_metadata;

public:
	X3DScene* m_scene;
	X3DLayerNode* m_ownerLayer;

protected:
	String m_name;
	Event2<X3DNode*, X3DField*> FieldChanged;

public:	// TODO: protected
	vector<MFNode*> m_parents;
//	vector<X3DField*> m_fields;
//	vector<int> m_fields;
};

class X3DNodeAVL : public X3DNode
{
public:
	CTOR X3DNodeAVL() : X3DNode(&avlnodeType)
	{
	}

	static NodeType avlnodeType;
};

//Define our own avltree_node_traits
struct X3DNode_avltree_node_traits
{
   typedef X3DNode                                    node;
   typedef X3DNode *                                  node_ptr;
   typedef const X3DNode *                            const_node_ptr;
   typedef int                                        balance;

   static node_ptr get_parent(const_node_ptr n)       {  return n->bytype.parent_;   }
   static void set_parent(node_ptr n, node_ptr parent){  n->bytype.parent_ = parent; }
   static node_ptr get_left(const_node_ptr n)         {  return n->bytype.left_;     }
   static void set_left(node_ptr n, node_ptr left)    {  n->bytype.left_ = left;     }
   static node_ptr get_right(const_node_ptr n)        {  return n->bytype.right_;    }
   static void set_right(node_ptr n, node_ptr right)  {  n->bytype.right_ = right;   }
   static balance get_balance(const_node_ptr n)       {  return n->bytype.balance_;  }
   static void set_balance(node_ptr n, balance b)     {  n->bytype.balance_ = b;     }
   static balance negative()                          {  return -1; }
   static balance zero()                              {  return 0;  }
   static balance positive()                          {  return 1;  }
};

struct X3DNode_compareByType
{
	bool operator () (X3DNode* x, X3DNode* y) const
	{
		return x->getTypeName() < y->getTypeName();
	}

	bool operator () (NodeType* x, X3DNode* y) const
	{
		return x->get_name() < y->getTypeName();
	}

	bool operator () (const char* x, X3DNode* y) const
	{
		return x < y->getTypeName();
	}

	bool operator () (X3DNode* x, const char* y) const
	{
		return x->getTypeName() < y;
	}

	bool operator () (X3DNode* x, StringIn y) const
	{
		return x->getTypeName() < y;
	}

	bool operator () (StringIn x, X3DNode* y) const
	{
		return x < y->getTypeName();
	}
};

#ifndef __LERSTAD__

typedef boost::intrusive::avltree_algorithms<X3DNode_avltree_node_traits> X3DByType_avl;

#endif

X3DEXT Object* asxml(X3DNode* node);
X3DEXT void asxml(IXmlWriter* xmlwriter, X3DNode* x3dnode);
X3DEXT TextDocument* asvrml(X3DNode* node);

}	// x3d
}	// System

#endif // x3d_X3DNode_h
