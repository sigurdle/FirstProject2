namespace System
{
namespace x3d
{

enum ShaderType
{
	ShaderType_None = 0,
	ShaderType_Vertex = 1,
	ShaderType_Fragment = 2,
	ShaderType_Geometry = 3,
};

class X3DEXT BufferVar
{
public:

	CTOR BufferVar() :
		m_nbuffer(-1),
		m_offset(0),
		m_count(0)
	{
	}

	CTOR BufferVar(int nbuffer, uint offset, uint count) :
		m_nbuffer(nbuffer),
		m_offset(offset),
		m_count(count)
	{
	}

	int m_nbuffer;

	uint m_offset;
	uint m_count;
};

class X3DEXT ShaderProgram : public X3DNode, public X3DUrlObject, public X3DProgrammableShaderObject
{
public:
	CTOR ShaderProgram();
	~ShaderProgram();

	/*
	virtual MFURL* getUrlField() override
	{
		return m_url;
	}
	*/

	X3DMFIELD(MFString, url, Url)
	X3DSFIELD(SFString, type, ShaderType)

	virtual uint getFieldCount() throw() override;
	virtual X3DField* getField(uint index) throw(ArgumentOutOfRangeException) override;
	virtual X3DField* getField(StringIn name) throw() override;

	virtual void ApplyFields(Graphics::RenderTarget* rt);

	virtual void AddField(X3DField* field) override;

	virtual bool CreateShader(StringIn language, Graphics::RenderTarget* p3D);

	void Apply(X3DDrawContext* p3DX);
	void End(X3DDrawContext* p3DX);

	X3DNODE(ShaderProgram, X3DNode)

	ShaderType m_shaderType;

private:

/*
	SFNode    [in,out] metadata  NULL         [X3DMetadataObject]
	MFString  [in,out] url       []           [URI]
	SFString  []       type      "VERTEX"     ["VERTEX"|"FRAGMENT"]

	# And any number of:
	fieldType [in]     fieldName
	fieldType [in,out] fieldName initialValue
	fieldType [out]    fieldName
	fieldType []       fieldName initialValue
*/

//	MFURL* m_url;

	//
	Graphics::GraphicsO_3D* m_device;

	int/*CGprofile*/ m_cgProfile;
	CGprogram m_cgProgram;

	// D3D9
	ID3DXConstantTable* m_constantTable;

public:	// TODO

//	vector<X3DField*> m_fields;
	vector<X3DField*> m_addfields;

	// D3D10
	vector<ID3D10Buffer*> m_buffers;
	vector<ubyte*> m_bufferData;

	map<String, BufferVar> m_variables;

	vector<ID3D10ShaderResourceView*> m_resources;

	BufferVar m_model;
	BufferVar m_view;
	BufferVar m_projection;
	BufferVar m_modelView;
	BufferVar m_modelViewProjection;
	BufferVar m_viewPosition;

	BufferVar m_modelI;
	BufferVar m_viewI;
	BufferVar m_projectionI;
	BufferVar m_modelViewI;
	BufferVar m_modelViewProjectionI;
	BufferVar m_viewPositionI;

	BufferVar m_modelT;
	BufferVar m_viewT;
	BufferVar m_projectionT;
	BufferVar m_modelViewT;
	BufferVar m_modelViewProjectionT;
	BufferVar m_viewPositionT;

	BufferVar m_modelIT;
	BufferVar m_viewIT;
	BufferVar m_projectionIT;
	BufferVar m_modelViewIT;
	BufferVar m_modelViewProjectionIT;
	BufferVar m_viewPositionIT;

	ID3D10Blob* m_shaderBlob;
	ID3D11InputLayout* m_inputLayout;

	union
	{
		void* p;
		IDirect3DVertexShader9* vertex;
		IDirect3DPixelShader9* pixel;
	}
	m_hlslShader;

	union
	{
		void* p;
		ID3D10VertexShader* vertex;
		ID3D10PixelShader* pixel;

		ID3D10VertexShader* vertex10;
		ID3D10PixelShader* pixel10;

		ID3D11VertexShader* vertex11;
		ID3D11PixelShader* pixel11;
	}
	m_hlsl_10_Shader;
};

}	// x3d
}	// System
