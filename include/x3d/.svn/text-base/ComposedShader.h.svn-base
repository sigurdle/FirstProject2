#ifndef x3d_ComposedShader_h
#define x3d_ComposedShader_h

namespace System
{
namespace x3d
{

class X3DEXT ComposedShader : public X3DShaderNode, public X3DProgrammableShaderObject
{
public:
	CTOR ComposedShader();
	~ComposedShader();

	virtual bool CreateShader(Gui::ImmediateRenderContext* p3D);

//	virtual void Apply(X3DDrawContext* p3DX);
	virtual void Begin(X3DDrawContext* p3DX, UINT* nPasses);
	virtual void End(X3DDrawContext* p3DX);
	virtual void BeginPass(X3DDrawContext* p3DX, UINT nPass);
	virtual void EndPass(X3DDrawContext* p3DX);

	MFNode* get_partsField() const
	{
		return m_parts;
	}

	unsigned int GetGLProgram()
	{
		return m_glProgram;
	}

	/*
	CGcontext GetCGContext()
	{
		return m_cgContext;
	}
	*/

	static NodeType s_nodeType;

private:

	Graphics::GraphicsO_3D* m_device;

	unsigned int m_glProgram;
	bool m_linked;

/*
  SFBool    [in]     activate
  SFNode    [in,out] metadata   NULL [X3DMetadataObject]
  MFNode    [in,out] parts      []   [ShaderPart]
  SFBool    [out]    isSelected
  SFBool    [out]    isValid
  SFString  []       language   ""  

  # And any number of:
  fieldType []       fieldName
  fieldType [in]     fieldName
  fieldType [out]    fieldName
  fieldType [in,out] fieldName
  */

	MFNode* m_parts;
};

}	// x3d
}

#endif // x3d_ComposedShader_h
