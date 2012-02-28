namespace System
{
namespace x3d
{

/* This abstract node type is the base type for all node types that specify arbitrary fields
for interfacing with per-object attribute values. */
interface X3DProgrammableShaderObject : public IX3DAddField
{
//	virtual void AddField(X3DField* field) = 0;
};

class X3DEXT X3DShaderNode : public X3DAppearanceChildNode, public IX3DAddField
{
protected:
	CTOR X3DShaderNode(NodeType* nodeType);

public:
	String getLanguage() const
	{
		return m_language->getValue();
	}

	SFString* get_languageField() const
	{
		return m_language;
	}

	bool get_isSelected() const
	{
		return m_isSelected->getValue();
	}

	SFBool* get_isSelectedField() const
	{
		return m_isSelected;
	}

	bool get_isValid() const
	{
		return m_isValid->getValue();
	}

	SFBool* get_isValidField() const
	{
		return m_isValid;
	}

	virtual bool CreateShader(Graphics::RenderTarget* p3D) = 0;

	virtual void Begin(X3DDrawContext* p3DX, UINT* nPasses) = 0;
	virtual void End(X3DDrawContext* p3DX) = 0;
	virtual void BeginPass(X3DDrawContext* p3DX, UINT nPass) = 0;
	virtual void EndPass(X3DDrawContext* p3DX) = 0;

	virtual void AddField(X3DField* field) override;

	bool isSelected() const;
	bool isValid() const;

	static NodeType* GetNodeType();

protected:

//	friend class VRMLLoader;

//	vector<X3DField*> m_fields;
	vector<X3DField*> m_addfields;

/*
  SFBool   [in]     activate
  SFNode   [in,out] metadata   NULL [X3DMetadataObject]
  SFBool   [out]    isSelected
  SFBool   [out]    isValid
  SFString []       language   ""   ["CG"|"GLSL"|"HLSL"|...]
*/
	SFBool* m_activate;
	SFBool* m_isSelected;
	SFBool* m_isValid;
	SFString* m_language;
};

}	// x3d
}
