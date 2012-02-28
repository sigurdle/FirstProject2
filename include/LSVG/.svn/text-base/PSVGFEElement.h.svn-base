#ifndef w3c_PSVGFEElement_h
#define w3c_PSVGFEElement_h

namespace System
{
namespace Web
{

#if 0
interface IEffect
{
	virtual unsigned int GetInputCount() = 0;
	virtual IEffect* GetInput(unsigned int index) = 0;
	virtual void SetInput(unsigned int index, IEffect* input) = 0;
	virtual void RenderOutput(LDraw::GraphicsO* pGraphics) = 0;
	virtual void RenderOutputNormalMap(LDraw::GraphicsO* pGraphics) = 0;
	virtual void Render(LDraw::GraphicsO* pGraphics, LDraw::RectF destRect, const LDraw::matrix4f& modelView, const LDraw::matrix4f& projection) = 0;
	virtual LDraw::Bitmap* GetOutputBitmap() = 0;
	virtual LDraw::Bitmap* GetOutputNormalMap() = 0;
};

class SVGEXT CEffect : public Object, public IEffect
{
protected:

	CTOR CEffect()
	{
		m_outImage = NULL;
	}

public:

	virtual ~CEffect()
	{
		if (m_outImage)
		{
		//	delete m_outImage;
			m_outImage = NULL;
		}
	}

	/*
	virtual unsigned int GetInputCount() = 0;
	virtual CEffect* GetInput(unsigned int index) = 0;
	virtual void Render(LDraw::GraphicsO* pGraphics, LDraw::RectF destRect, const LDraw::matrix4f& modelView, const LDraw::matrix4f& projection) = 0;
	*/

	virtual void RenderOutput(LDraw::GraphicsO* pGraphics);
	virtual void RenderOutputNormalMap(LDraw::GraphicsO* pGraphics);

	virtual LDraw::Bitmap* GetOutputBitmap()
	{
		return m_outImage;
	}

	virtual LDraw::Bitmap* GetOutputNormalMap()
	{
		return m_outNormalMap;
	}

protected:

	void DrawBitmap(LDraw::GraphicsO* pGraphics, LDraw::RectF destRect);

public:
	LDraw::RectF m_subRegion;
	LDraw::Bitmap* m_outImage;
	LDraw::Bitmap* m_outNormalMap;

	int m_scaledWidth;
	int m_scaledHeight;
};
#endif

class SVGEXT SVGFilterCommand : public Object//public LDraw::Command
{
public:

	virtual void Render(Gui::RenderContext* renderContext);

	gm::RectF m_destRect;
	float m_srcX;
	float m_srcY;
	float m_srcWidth;
	float m_srcHeight;
//	LDraw::WrapMode m_wrapMode;

	Gui::IEffect* m_effect;
};

class SVGEXT PSVGFEElement : public PSVGElement
{
public:
	CTOR PSVGFEElement(SVGElement* element) : PSVGElement(element)
	{
		m_effect = NULL;
	}

	void CalculatePrimitiveSubRegion(PSVGFilterElement* pFilterElement, PSVGElement* pReferencingElement, gm::RectF& subRegion);

	virtual int GetInCount() = 0;
	virtual Gui::CEffect* Filter(Gui::RenderContext* renderContext, Gui::CEffect* inEffect[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY) = 0;

	Gui::CEffect* m_effect;
};

}	// Web
}	// System

#endif // Web_PSVGFEElement_h
