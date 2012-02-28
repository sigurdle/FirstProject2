namespace System
{
namespace x3d
{

class X3DEXT TimeSensor : 
	public X3DTimeDependentNode
//	public X3DSensorNode
{
public:
	CTOR TimeSensor();

	virtual void DoTime(double gt);

	SFTime* getCycleIntervalField() const
	{
		return m_cycleInterval;
	}

	SFTime* getCycleTimeField() const
	{
		return m_cycleTime;
	}

	SFFloat* getFractionChangedField() const
	{
		return m_fractionChanged;
	}

	static NodeType* nodeType;
	static NodeType* GetNodeType();

	static X3DFieldDefinition* get_cycleIntervalFieldDef();
	static X3DFieldDefinition* get_cycleTimeFieldDef();
	static X3DFieldDefinition* get_fractionChangedFieldDef();
	static X3DFieldDefinition* get_enabledFieldDef();

	bool bActive;

protected:

	SFTime* m_cycleInterval;
	SFTime* m_cycleTime;
	SFFloat* m_fractionChanged;
	SFBool* m_enabled;
};

}	// x3d
}	// System
