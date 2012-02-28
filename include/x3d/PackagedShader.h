namespace System
{
namespace x3d
{

class X3DEXT PackagedShader : public X3DShaderNode, public X3DUrlObject, public X3DProgrammableShaderObject
{
public:
	CTOR PackagedShader();

	/*
	virtual MFURL* getUrlField()
	{
		return m_url;
	}
	*/

	virtual bool CreateShader(Graphics::RenderTarget* p3D) override;

//	virtual void Apply(X3DDrawContext* p3DX);
	virtual void Begin(X3DDrawContext* p3DX, UINT* nPasses) override;
	virtual void End(X3DDrawContext* p3DX) override;
	virtual void BeginPass(X3DDrawContext* p3DX, UINT nPass) override;
	virtual void EndPass(X3DDrawContext* p3DX) override;

	X3DMFIELD(MFString, url, Url)

	X3DNODE(PackagedShader, X3DShaderNode)

private:

	// D3D9
	ID3DXEffect* m_effect;

	// D3D10
	ID3DX10Effect* m_d3d10_effect;

	ID3DX10EffectMatrixVariable* m_model;
	ID3DX10EffectMatrixVariable* m_view;
	ID3DX10EffectMatrixVariable* m_projection;
	ID3DX10EffectMatrixVariable* m_modelView;
	ID3DX10EffectMatrixVariable* m_modelViewProjection;

	ID3DX10EffectMatrixVariable* m_modelI;
	ID3DX10EffectMatrixVariable* m_viewI;
	ID3DX10EffectMatrixVariable* m_projectionI;
	ID3DX10EffectMatrixVariable* m_modelViewI;
	ID3DX10EffectMatrixVariable* m_modelViewProjectionI;

	ID3DX10EffectMatrixVariable* m_modelT;
	ID3DX10EffectMatrixVariable* m_viewT;
	ID3DX10EffectMatrixVariable* m_projectionT;
	ID3DX10EffectMatrixVariable* m_modelViewT;
	ID3DX10EffectMatrixVariable* m_modelViewProjectionT;

	ID3DX10EffectMatrixVariable* m_modelIT;
	ID3DX10EffectMatrixVariable* m_viewIT;
	ID3DX10EffectMatrixVariable* m_projectionIT;
	ID3DX10EffectMatrixVariable* m_modelViewIT;
	ID3DX10EffectMatrixVariable* m_modelViewProjectionIT;

	/*
	SFBool    [in]     activate
	SFNode    [in,out] metadata   NULL [X3DMetadataObject]
	MFString  [in,out] url        []   [URI]
	SFBool    [out]    isSelected
	SFBool    [out]    isValid
	SFString  []       language   ""

	# And any number of:
	fieldType [in]     fieldName
	fieldType [in,out] fieldName initialValue
	fieldType [out]    fieldName
	fieldType []       fieldName initialValue
	*/

	/*
	MFURL* m_url;

	static NodeType* nodeType;
	*/
};

}	// x3d
}	// System
