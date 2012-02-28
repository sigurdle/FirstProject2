#ifndef x3d_Script_h
#define x3d_Script_h

namespace System
{
namespace x3d
{

class X3DEXT Script : public X3DScriptNode, public X3DUrlObject
{
public:
	CTOR Script();

//	X3DField* createField(System::StringW* name, FieldType fieldType);

	virtual void AddField(X3DField* field) override;

	virtual uint getFieldCount() override;
	virtual X3DField* getField(uint index) override;
	virtual X3DField* getField(StringIn name) override;

	static NodeType* GetNodeType();

protected:

	bool LoadScript();

	MFString* m_url;
	SFBool* m_directOutput;
	SFBool* m_mustEvaluate;

private:

	vector<X3DField*> m_addfields;

	static NodeType* nodeType;
};

}	// x3d
}	// System

#endif // x3d_Script_h
