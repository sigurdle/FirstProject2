#ifndef Web_PSVGFilterElement_h
#define Web_PSVGFilterElement_h

namespace System
{
namespace Web
{

class SVGEXT SourceGraphic : public Gui::CEffect
{
public:
	CTOR SourceGraphic(PSVGElement* pPElement);

	virtual unsigned int GetInputCount()
	{
		return 0;
	}

	virtual Gui::IEffect* GetInput(unsigned int index)
	{
		throw new Exception(WSTR("Index out of bounds"));
	}

	virtual void SetInput(unsigned int index, Gui::IEffect* input)
	{
		throw new Exception(WSTR("Index out of bounds"));
	}

	virtual void Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);
	virtual void RenderOutput(Gui::RenderTarget* rt);

	friend class SourceAlpha;

	PSVGElement* m_pPElement;
};

class SVGEXT SourceAlpha : public Gui::CEffect
{
public:
	CTOR SourceAlpha(SourceGraphic* pSourceGraphic);

	virtual unsigned int GetInputCount()
	{
		return 0;
	}

	virtual Gui::IEffect* GetInput(unsigned int index)
	{
		throw std::exception("Index out of bounds");
	}

	virtual void SetInput(unsigned int index, Gui::IEffect* input)
	{
		throw std::exception("Index out of bounds");
	}

	virtual void RenderOutput(Gui::RenderTarget* rt);
	virtual void Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	SourceGraphic* m_pSourceGraphic;
};

class SVGEXT SVGColorMatrixEffect : public Gui::CEffect
{
public:

	virtual unsigned int GetInputCount();
	virtual Gui::IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, Gui::IEffect* input);

	virtual void Render(Gui::RenderTarget* rt, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	Gui::IEffect* m_inEffect;

	static ID3D10EffectTechnique* s_technique;

//	D3DXHANDLE m_technique;
	//LDraw::ColorMatrixF m_colorMatrix;
	gm::matrix4f m_colorTransform;
	gm::vector4f m_colorTranslate;
};

class SVGEXT SVGGaussianBlurEffect : public Gui::GaussianBlurEffect
{
public:
/*
	virtual void Render(Gui::RenderTarget* rt, LDraw::RectF destRect, const LDraw::matrix4f& modelView, const LDraw::matrix4f& projection);

	virtual unsigned int GetInputCount();
	virtual Gui::IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, Gui::IEffect* input);

	float m_stdDeviationX;
	float m_stdDeviationY;

	Gui::IEffect* m_inEffect;

	D3DXHANDLE m_techniqueH;
	D3DXHANDLE m_techniqueV;
	*/
};

class SVGEXT SVGOffsetEffect : public Gui::CEffect
{
public:

	virtual unsigned int GetInputCount();
	virtual Gui::IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, Gui::IEffect* input);
	virtual void Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	float m_dx;
	float m_dy;
	Gui::IEffect* m_inEffect;

	D3DXHANDLE m_technique;
};

class SVGEXT SVGMergeEffect : public Gui::CEffect
{
public:

	virtual unsigned int GetInputCount();
	virtual Gui::IEffect* GetInput(unsigned int index);
	virtual void SetInput(unsigned int index, Gui::IEffect* input);

	virtual void Render(Gui::RenderContext* renderContext, gm::RectF destRect, const gm::matrix4f& modelView, const gm::matrix4f& projection);

	vector<Gui::IEffect*> m_nodes;
};

class SVGEXT PSVGFilterElement : public PSVGElement
{
public:
	CTOR PSVGFilterElement(SVGFilterElement* element);

	SVGFilterCommand* ProcessEffects(Gui::RenderContext* renderContext, PSVGElement* pReferencingElement, double scaleX, double scaleY);
	Gui::CEffect* GetInEffect(Gui::RenderContext* renderContext, StringIn instr, int i);
	gm::RectD CalculateFilterRegion(PSVGElement* pReferencingElement);
	virtual void RecalculateParentBounds();

public:

	double m_scaleX;
	double m_scaleY;

//	vector<CEffect*, __gc_allocator> m_effects;
	vector<PSVGFEElement*> m_effectElements;

	PSVGElement* m_pReferencingElement;
	SourceGraphic* m_pSourceGraphic;
	SourceAlpha* m_pSourceAlpha;
	Gui::CEffect* m_pBackgroundImage;
	Gui::CEffect* m_pBackgroundAlpha;

	int m_scaledWidth;
	int m_scaledHeight;
};

}	// Web
}	// System

#endif // Web_PSVGFilterElement_h
