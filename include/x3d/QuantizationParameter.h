#ifndef x3d_QuantizationParameter_h
#define x3d_QuantizationParameter_h

namespace System
{
namespace x3d
{

class X3DEXT QuantizationParameter : public X3DChildNode
{
public:
	CTOR QuantizationParameter();
	~QuantizationParameter();

/*
	field SFBool isLocal FALSE
	field SFBool position3DQuant FALSE
	field SFVec3f position3DMin -., -., -.
	field SFVec3f position3DMax +., +., +.
	field SFInt32 position3DNbBits 16
	field SFBool position2DQuant FALSE
	field SFVec2f position2DMin -., -.
	field SFVec2f position2DMax +., +.
	field SFInt32 position2DNbBits 16
	field SFBool drawOrderQuant TRUE
	field SFVec3f drawOrderMin -.
	field SFVec3f drawOrderMax +.
	field SFInt32 drawOrderNbBits 8
	field SFBool colorQuant TRUE
	field SFFloat colorMin 0.0
	field SFFloat colorMax 1.0
	field SFInt32 colorNbBits 8
	field SFBool textureCoordinateQuant TRUE
	field SFFloat textureCoordinateMin 0.0
	field SFFloat textureCoordinateMax 1.0
	field SFInt32 textureCoordinateNbBits 16
	field SFBool angleQuant TRUE
	field SFFloat angleMin 0.0
	field SFFloat angleMax 2¶
	field SFInt32 angleNbBits 16
	field SFBool scaleQuant FALSE
	field SFFloat scaleMin 0.0
	field SFFloat scaleMax +.
	field SFInt32 scaleNbBits 8
	field SFBool keyQuant TRUE
	field SFFloat keyMin 0.0
	field SFFloat keyMax 1.0
	field SFInt32 keyNbBits 8
	field SFBool normalQuant TRUE
	field SFInt32 normalNbBits 8
	field SFBool sizeQuant FALSE
	field SFFloat sizeMin 0.0
	field SFFloat sizeMax +.
	field SFInt32 sizeNbBits 8
	field SFBool useEfficientCoding FALSE
*/

	bool getIsLocal() const
	{
		return m_isLocal->getValue();
	}

	bool getPosition2DQuant() const
	{
		return m_position2DQuant->getValue();
	}
	void getPosition2DMin(/*[out]*/ float value[2]) const
	{
		if (value == NULL) throw -1;
		value[0] = m_position2DMin->m_value[0];
		value[1] = m_position2DMin->m_value[1];
	}
	void getPosition2DMax(/*[out]*/ float value[2]) const
	{
		if (value == NULL) throw -1;
		value[0] = m_position2DMax->m_value[0];
		value[1] = m_position2DMax->m_value[1];
	}
	long getPosition2DNbBits() const
	{
		return m_position2DNbBits->getValue();
	}

	bool getColorQuant() const
	{
		return m_colorQuant->getValue();
	}
	float getColorMin() const
	{
		return m_colorMin->getValue();
	}
	float getColorMax() const
	{
		return m_colorMax->getValue();
	}
	long getColorNbBits() const
	{
		return m_colorNbBits->getValue();
	}

	bool getSizeQuant() const
	{
		return m_sizeQuant->getValue();
	}

	float getSizeMin() const
	{
		return m_sizeMin->getValue();
	}
	float getSizeMax() const
	{
		return m_sizeMax->getValue();
	}
	long getSizeNbBits() const
	{
		return m_sizeNbBits->getValue();
	}

	static NodeType s_nodeType;

public:

	SFBool* m_isLocal;

	SFBool* m_position2DQuant;
	SFVec2f* m_position2DMin;
	SFVec2f* m_position2DMax;
	SFInt32* m_position2DNbBits;

	SFBool* m_colorQuant;
	SFFloat* m_colorMin;
	SFFloat* m_colorMax;
	SFInt32* m_colorNbBits;

	SFBool* m_sizeQuant;
	SFFloat* m_sizeMin;
	SFFloat* m_sizeMax;
	SFInt32* m_sizeNbBits;
};

}	// x3d
}	// System

#endif // x3d_QuantizationParameter_h
