#ifndef BIFSDec_h
#define BIFSDec_h

namespace System
{
namespace Mpeg4
{

enum BIFSFieldType
{
	BIFS_MFBool, 
	BIFS_MFColor, 
	BIFS_MFColorRGBA,
	BIFS_MFDouble,
	BIFS_MFFloat, 
	BIFS_MFImage, 
	BIFS_MFInt32, 
	BIFS_MFNode, 
	BIFS_MFRotation, 
	BIFS_MFString, 
	BIFS_MFTime, 
	BIFS_MFVec2d, 
	BIFS_MFVec2f, 
	BIFS_MFVec3d, 
	BIFS_MFVec3f, 

// BIFS_Specific
	BIFS_MFURL,
	BIFS_MFCommandBuffer,
	BIFS_MFScript,

	BIFS_MFTopNode,
	BIFS_MF2DNode,
	BIFS_MF3DNode,
	BIFS_MFAppearanceNode,
	BIFS_MFGeometryNode,
	BIFS_MFMaterialNode,
	BIFS_MFTextureNode,
	BIFS_MFTextureTransform,
	BIFS_MFLinePropertiesNode,
	BIFS_MFCoordinate2DNode,
	BIFS_MFAudioNode,
	BIFS_MFColorNode,
	BIFS_MFTextureCoordinateNode,
	BIFS_MFFontStyleNode,

	BIFS_SFBool, 
	BIFS_SFColor, 
	BIFS_SFColorRGBA, 
	BIFS_SFDouble, 
	BIFS_SFFloat, 
	BIFS_SFImage, 
	BIFS_SFInt32, 
	BIFS_SFNode, 
	BIFS_SFRotation, 
	BIFS_SFString, 
	BIFS_SFTime, 
	BIFS_SFVec2d, 
	BIFS_SFVec2f, 
	BIFS_SFVec3d, 
	BIFS_SFVec3f,

// BIFS_Specific
	BIFS_SFURL,
	BIFS_SFCommandBuffer,
	BIFS_SFScript,

	BIFS_SFTopNode,
	BIFS_SF2DNode,
	BIFS_SF3DNode,
	BIFS_SFAppearanceNode,
	BIFS_SFGeometryNode,
	BIFS_SFMaterialNode,
	BIFS_SFTextureNode,
	BIFS_SFTextureTransform,
	BIFS_SFLinePropertiesNode,
	BIFS_SFCoordinate2DNode,
	BIFS_SFAudioNode,
	BIFS_SFColorNode,
	BIFS_SFTextureCoordinateNode,
	BIFS_SFFontStyleNode,
};

enum QuantType
{
	Quant_None = 0,
	Quant_3D_position = 1,
	Quant_2D_positions = 2,
	Quant_Drawing_order = 3,
	Quant_SFColor = 4,
	Quant_Texture_Coordinate = 5,
	Quant_Angle = 6,
	Quant_Scale = 7,
	Quant_Interpolator_keys = 8,
	Quant_Normals = 9,
	Quant_Rotations = 10,
	Quant_Object_Size_3D = 11,// (1)
	Quant_Object_Size_2D = 12,// (2)
	Quant_Linear_Scalar_Quantization = 13,
	Quant_CoordIndex = 14,
	Quant_Reserved = 15,
};

struct Field
{
#if 0
	CTOR Field(	System::StringW* _name,
					BIFSFieldType _fieldType,
					bool _bDef,
					bool _bIn,
					bool _bOut,
					bool _bDyn,
					double/*float*/ _m,
					double/*float*/ _M,
					int _quantType,
					int _defaultNbBits)
	{
		name = _name;
		fieldType = _fieldType;
		bDef = _bDef;
		bIn = _bIn;
		bOut = _bOut;
		bDyn = _bDyn;
		m = _m;
		M = _M;
		quantType = _quantType;
		defaultNbBits = _defaultNbBits;
	}

	CTOR Field()
	{
		name = NULL;
	}
#endif

	ImmutableString<WCHAR>* name;
	BIFSFieldType fieldType;
	bool bDef;
	bool bIn;
	bool bOut;
	bool bDyn;
	double/*float*/ m;
	double/*float*/ M;
	int quantType;
	int defaultNbBits;
};

struct Node
{
	ImmutableString<WCHAR>* nodeName;
//	WCHAR* nodeName;
//	int nDEFbits;
//	int nINbits;
//	int nOUTbits;
//	int nDYNbits;
	Field* fields;
};

struct NodeDataTypeNode
{
	int index;
	int nDEFbits;
	int nINbits;
	int nOUTbits;
};

struct NodeDataType
{
	int nbits;
	NodeDataTypeNode* nodes;
};

class FieldData
{
public:
	CTOR FieldData()
	{
		field = NULL;
		isQuantized = false;
		useEfficientCoding = false;
	}

	Field* field;
	bool	isQuantized : 1,
			useEfficientCoding : 1;
	int nbBits;// The number of bits used for the quantization of the field.

	float floatMin[4];
	float floatMax[4];
	int intMin[1];
};

class NodeData : public Object
{
public:
	CTOR NodeData()
	{
		nINbits = 0;
		nOUTbits = 0;
		node = NULL;
	}

	int nodeDataType;
	int localNodeType;
	Node* node;

	int nINbits;
	int nOUTbits;

	x3d::X3DNode* x3dnode;
};

class Identifier
{
public:
	String m_name;
};

class ScriptNode// : public Object (instantiated on stack)
{
public:
	CTOR ScriptNode()
	{
		m_INFields = 0;
		m_OUTFields = 0;

#if 0
		m_pEngine = NULL;
#endif
	}

	int m_INFields;
	int m_OUTFields;

	vector<Identifier> m_identifiers;

//	CComObject<CLScriptEngine>* m_pEngine;
};

//class CTrack;

class MP4SSampleDescription : public SampleDescription
{
public:
	ESDescriptor es_descriptor;
	BIFSConfiguration m_BIFSConfig;
};

class BIFSDec : public Object
{
public:
	CTOR BIFSDec()
	{
		m_currentPosition = 0;
		m_currentFrame = -1;

		m_pBIFSConfig = NULL;
		m_pBIFSConfig = new BIFSConfiguration;
	}

	~BIFSDec()
	{
		ResetDefs();

		if (m_pBIFSConfig)
		{
			delete m_pBIFSConfig;
			m_pBIFSConfig = NULL;
		}
	}

	class NodeDef : public Object
	{
	public:
		CTOR NodeDef()
		{
			m_nodeID = 0;
		//	m_nodeDataType = NULL;
		//	m_x3dnode = NULL;

		//	nINbits = 0;
		}

		//int m_nodeDataType;
		//int m_localNodeType;

		int m_nodeID;
		NodeData* nodeData;
		//NodeDataTypeNode* m_nodeDataType;

		//int nINbits;

		//ILX3DNode* m_x3dnode;
	};

	void ResetDefs();

	void ReadSFScript(IO::CBitStream32* pBitStream, NodeData& nodeData);

	void ReadChildNode(IO::CBitStream32* pBitStream, FieldData& field, int fieldType, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep, x3d::X3DNode* *pVal);
	void ReadSFNode(IO::CBitStream32* pBitStream, int nodeDataType, x3d::QuantizationParameter* lqp, bool lqp_deep, x3d::X3DNode* *pVal);
	void ReadField(IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep);

	void ReadSFField(IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, int fieldType, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep);
	void ReplaceSFField(IO::CBitStream32* pBitStream, FieldData& field, int fieldType, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep, int where);

	void ReadMFField(IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep);

	void ReadMFListDescription(IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep);
	void ReadMFVectorDescription(IO::CBitStream32* pBitStream, NodeData& nodeData, FieldData& field, x3d::X3DField* x3dfield, x3d::QuantizationParameter* lqp, bool lqp_deep);

	void ReadMaskNodeDescription(IO::CBitStream32* pBitStream, NodeData* node, x3d::QuantizationParameter* lqp, bool lqp_deep);
	void ReadListNodeDescription(IO::CBitStream32* pBitStream, NodeData* node, x3d::QuantizationParameter* lqp, bool lqp_deep);

#if 0
	void ReadScriptFieldsListDescription(CBitStream* pBitStream, CScriptNode& scriptNode, NodeData& nodeData);
	void ReadScriptFieldsVectorDescription(CBitStream* pBitStream, CScriptNode& scriptNode, NodeData& nodeData);
	void ReadScriptField(CBitStream* pBitStream, CScriptNode& scriptNode, NodeData& nodeData);
	sysstring ReadIdentifier(CBitStream* pBitStream, CScriptNode& scriptNode);
	void ReadArguments(CBitStream* pBitStream, CScriptNode& scriptNode);
	NODEP ReadExpression(CBitStream* pBitStream, CScriptNode& scriptNode);
	NODEP ReadCompoundExpression(CBitStream* pBitStream, CScriptNode& scriptNode);
	void ReadOptionalExpression(CBitStream* pBitStream, CScriptNode& scriptNode);
	CStatement* ReadStatement(CBitStream* pBitStream, CScriptNode& scriptNode);
	void ReadIFStatement(CBitStream* pBitStream, CScriptNode& scriptNode, CIfStatement& stmt);
	void ReadFORStatement(CBitStream* pBitStream, CScriptNode& scriptNode, CForStatement& stmt);
	void ReadRETURNStatement(CBitStream* pBitStream, CScriptNode& scriptNode);
	void ReadStatementBlock(CBitStream* pBitStream, CScriptNode& scriptNode, CStatementBlock& statementBlock);
	void ReadFunction(CBitStream* pBitStream, CScriptNode& scriptNode, CScriptItem* pItem);
	void ReadParams(CBitStream* pBitStream, CScriptNode& scriptNode);
	void ReadEncodedScript(CBitStream* pBitStream, CScriptNode& scriptNode);
#endif

	NodeDef* FindNode(int nodeID)
	{
		for (unsigned int i = 0; i < m_defs.size(); i++)
		{
			if (m_defs[i]->m_nodeID == nodeID)
			{
				return m_defs[i];
			}
		}

		return NULL;
	}

	void ReadROUTE(IO::CBitStream32* pBitStream);

	ErrorCode IndexedValueInsertion(IO::CBitStream32* pBitStream);

	ErrorCode FieldReplacement(IO::CBitStream32* pBitStream);
	ErrorCode IndexedValueReplacement(IO::CBitStream32* pBitStream);

	ErrorCode ReadScene(IO::CBitStream32* pBitStream);

	void InsertionCommand(IO::CBitStream32* pBitStream);
	void ReplacementCommand(IO::CBitStream32* pBitStream);

	x3d::Scene* m_scene;
	vector<NodeDef*> m_defs;

	Stream m_stream;

	ULONGLONG m_chunkOffset;
	LONGLONG m_currentPosition;

	BIFSConfiguration* m_pBIFSConfig;
	Track* m_pTrack;
	long m_currentFrame;

	bool m_USENAMES : 1;
};

}	// Mpeg4
}

#endif // BIFSDec_h
