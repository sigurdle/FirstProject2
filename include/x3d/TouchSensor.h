#ifndef x3d_TouchSensor_h
#define x3d_TouchSensor_h

namespace System
{
namespace x3d
{

class TouchSensor : 
	public X3DTouchSensorNode,
	public RenderImplImpl	// To have predraw
{
public:
	CTOR TouchSensor();
	~TouchSensor();

	virtual void PreDraw(X3DDrawContext* pDC);

	bool getEnabled() const
	{
		return m_enabled->getValue();
	}

	bool getIsOver() const
	{
		return m_isOver->getValue();
	}

	void setIsOver(bool isOver);

	SFBool* getIsOverField() const
	{
		return m_isOver;
	}

	bool getIsActive() const
	{
		return m_isActive->getValue();
	}

	SFTime* getTouchTime() const
	{
		return m_touchTime;
	}

	static NodeType s_nodeType;

protected:

	SFBool* m_enabled;
	SFBool* m_isOver;
	SFBool* m_isActive;
	SFTime* m_touchTime;
};

}	// x3d
}

#endif // x3d_TouchSensor_h
