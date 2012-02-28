namespace System
{
namespace x3d
{

class X3DEXT ShaderPart : public X3DNode, public X3DUrlObject
{
public:
	CTOR ShaderPart();
	~ShaderPart();

	virtual MFURL* get_urlField()
	{
		return m_url;
	}

	String getShaderType() const
	{
		return m_type->getValue();
	}

	bool CreateShader(StringIn language, Graphics::Graphics3D* p3D/*, CGcontext cgContext = NULL*/);

	unsigned int getGLShader() const
	{
		return m_glShader;
	}

	CGprogram getCGProgram() const
	{
		return m_cgProgram;
	}

	static NodeType s_nodeType;

private:

	Graphics::GraphicsO_3D* m_device;

	CGprogram m_cgProgram;

	unsigned int m_glShader;
	bool m_compiled;

	/*
	SFNode   [in,out] metadata NULL       [X3DMetadataObject]
	MFString [in,out] url      []         [URI]
	SFString []       type     "VERTEX"   ["VERTEX"|"FRAGMENT"]
	*/

	MFURL* m_url;
	SFString* m_type;
};

}	// x3d
}
