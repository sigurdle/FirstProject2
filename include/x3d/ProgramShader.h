namespace System
{
namespace x3d
{

class X3DEXT ProgramShader : public X3DShaderNode
{
public:
	CTOR ProgramShader();

	virtual bool CreateShader(Graphics::RenderTarget* p3D) override;

//	virtual void Apply(X3DDrawContext* p3DX);
	virtual void Begin(X3DDrawContext* p3DX, UINT* nPasses);
	virtual void End(X3DDrawContext* p3DX);
	virtual void BeginPass(X3DDrawContext* p3DX, UINT nPass);
	virtual void EndPass(X3DDrawContext* p3DX);

	virtual void SetModelMatrix(const float*);
	virtual void SetViewMatrix(const float*);
	virtual void SetProjectionMatrix(const float*);
	virtual void SetModelViewMatrix(const float*);
	virtual void SetModelViewProjectionMatrix(const float*);

	MFNode* get_programsField() const
	{
		return m_programs;
	}

	static NodeType* nodeType;
	static NodeType* GetNodeType();

private:

/*
	SFBool   [in]     activate
	SFNode   [in,out] metadata   NULL [X3DMetadataObject]
	MFNode   [in,out] programs   []   [ShaderProgram]
	SFBool   [out]    isSelected
	SFBool   [out]    isValid
	SFString []       language   ""   ["CG"|"GLSL"|"HLSL"]
*/

	TypedMFNode<ShaderProgram*>* m_programs;

public:	// TODO
	ShaderProgram* m_vertexShader;
	ShaderProgram* m_fragmentShader;
	ShaderProgram* m_geometryShader;

	ID3D11InputLayout* m_inputLayout;

	// CG
	CGprogram m_cgProgram;
};

}	// x3d
}	// System
