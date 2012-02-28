#pragma once

class CPXSLTTemplateElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMPElement
{
public:
	CTOR CPXSLTTemplateElement()
	{
	}

	virtual void Draw(CHTMRenderContext* pC)
	{
		Gdiplus::Font* pFont = m_pFont;

		pC->m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

		CComQIPtr<ILDOMElement> element = m_pNode;

		ATLASSERT(m_pBox);
		Gdiplus::RectF trect = m_pBox->GetAbsOuterRect();
		Gdiplus::SolidBrush textbrush(Gdiplus::Color(255,0,0));	// TODO

		trect.Height = m_contentSize.Height;

		BSTR bmatch;
		element->getAttribute(L"match", &bmatch);
		_bstr_t text = _bstr_t(bmatch, false);

		const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

//		Gdiplus::RectF size(0,0,0,0);
//		pC->m_pGraphics->MeasureString(text, text.length(), pC->m_pFont, Gdiplus::PointF(0,0), &size);
		Gdiplus::RectF sizef(0,0,0,0);
		pC->m_pGraphics->MeasureString(text, text.length(), pFont, Gdiplus::PointF(0,0), &sizef);
		Gdiplus::Rect size((int)sizef.X,(int)sizef.Y,(int)sizef.Width,(int)sizef.Height);

		Gdiplus::PointF pts[] =
		{
			Gdiplus::PointF(trect.X, trect.Y),
			Gdiplus::PointF(trect.X+size.Width, trect.Y),
			Gdiplus::PointF(trect.X+size.Width+size.Height/4, trect.Y+size.Height/2),
			Gdiplus::PointF(trect.X+size.Width, trect.Y+size.Height),
			Gdiplus::PointF(trect.X, trect.Y+size.Height),
			Gdiplus::PointF(trect.X, trect.Y),
		};

		Gdiplus::PointF pts2[] =
		{
			Gdiplus::PointF(trect.X, trect.GetBottom()-size.Height/2),
			Gdiplus::PointF(trect.X+size.Height/4, trect.GetBottom()-size.Height),
			Gdiplus::PointF(trect.X+size.Width+size.Height/4, trect.GetBottom()-size.Height),
			Gdiplus::PointF(trect.X+size.Width+size.Height/4, trect.GetBottom()),
			Gdiplus::PointF(trect.X+size.Height/4, trect.GetBottom()),
			Gdiplus::PointF(trect.X, trect.GetBottom()-size.Height/2),
		};

		pC->m_pGraphics->FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(255, 200, 0)), pts, 6);
		pC->m_pGraphics->DrawPolygon(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0)), pts, 6);
		pC->m_pGraphics->DrawString(text,
				text.length(), pFont,
				Gdiplus::PointF(trect.X+1, trect.Y+1),
				pStringFormat,
				&textbrush);

		pC->m_pGraphics->FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(255, 200, 0)), pts2, 6);
		pC->m_pGraphics->DrawPolygon(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0)), pts2, 6);
		pC->m_pGraphics->DrawString(text,
				text.length(), pFont,
				Gdiplus::PointF(trect.X+size.Height/4, trect.GetBottom()-m_customBlockBottom),
				pStringFormat,
				&textbrush);
	}

	virtual void CalculateDimensions(CHTMCalcContext* pC)
	{
		GetCSSProperties(pC);
		SetupFont(pC);

		Gdiplus::Font* pFont = m_pFont;

		const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

		CComQIPtr<ILDOMElement> element = m_pNode;

		BSTR bmatch;
		element->getAttribute(L"match", &bmatch);
		_bstr_t text = _bstr_t(bmatch, false);

		Gdiplus::RectF size(0,0,0,0);
		pC->m_pGraphics->MeasureString(text, text.length(), m_pFont, Gdiplus::PointF(0,0), &size);

		m_customBlockTop = size.Height;
		m_customBlockBottom = size.Height;

		CalculateChildrenDimensions(pC);
		SetdownFont(pC);
	}

	virtual BOOL HasDistributableChildren()
	{
		return TRUE;
	}

BEGIN_COM_MAP(CPXSLTTemplateElement)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()
};

class CPXSLTForEachElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMPElement
{
public:
	CPXSLTForEachElement()
	{
	}

	virtual void Draw(CHTMRenderContext* pC)
	{
		Gdiplus::Font* pFont = m_pFont;

		pC->m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

		CComQIPtr<ILDOMElement> element = m_pNode;

		ATLASSERT(m_pBox);
		Gdiplus::RectF trect = m_pBox->GetAbsOuterRect();
		Gdiplus::SolidBrush textbrush(Gdiplus::Color(255,0,0));	// TODO

		BSTR bselect;
		element->getAttribute(L"select", &bselect);
		_bstr_t text = _bstr_t(bselect, false);

		const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

		Gdiplus::RectF sizef(0,0,0,0);
		pC->m_pGraphics->MeasureString(text, text.length(), m_pFont, Gdiplus::PointF(0,0), &sizef);
		Gdiplus::Rect size((int)sizef.X,(int)sizef.Y,(int)sizef.Width,(int)sizef.Height);

		Gdiplus::PointF pts[] =
		{
			Gdiplus::PointF(trect.X, trect.Y),
			Gdiplus::PointF(trect.X+size.Width, trect.Y),
			Gdiplus::PointF(trect.X+size.Width+size.Height/4, trect.Y+size.Height/2),
			Gdiplus::PointF(trect.X+size.Width, trect.Y+size.Height),
			Gdiplus::PointF(trect.X, trect.Y+size.Height),
			Gdiplus::PointF(trect.X, trect.Y),
		};

		Gdiplus::PointF pts2[] =
		{
			Gdiplus::PointF(trect.X, trect.GetBottom()-size.Height/2),
			Gdiplus::PointF(trect.X+size.Height/4, trect.GetBottom()-size.Height),
			Gdiplus::PointF(trect.X+size.Width+size.Height/4, trect.GetBottom()-size.Height),
			Gdiplus::PointF(trect.X+size.Width+size.Height/4, trect.GetBottom()),
			Gdiplus::PointF(trect.X+size.Height/4, trect.GetBottom()),
			Gdiplus::PointF(trect.X, trect.GetBottom()-size.Height/2),
		};

		pC->m_pGraphics->FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(255, 200, 0)), pts, 6);
		pC->m_pGraphics->DrawPolygon(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0)), pts, 6);
		pC->m_pGraphics->DrawString(text,
				text.length(), pFont,
				Gdiplus::PointF(trect.X+1, trect.Y+1),
				pStringFormat,
				&textbrush);

		pC->m_pGraphics->FillPolygon(&Gdiplus::SolidBrush(Gdiplus::Color(255, 200, 0)), pts2, 6);
		pC->m_pGraphics->DrawPolygon(&Gdiplus::Pen(Gdiplus::Color(255, 0, 0)), pts2, 6);
		pC->m_pGraphics->DrawString(text,
				text.length(), pFont,
				Gdiplus::PointF(trect.X+size.Height/4, trect.GetBottom()-m_customBlockBottom),
				pStringFormat,
				&textbrush);
	}

	virtual void CalculateDimensions(CHTMCalcContext* pC)
	{
		GetCSSProperties(pC);
		SetupFont(pC);

		Gdiplus::Font* pFont = m_pFont;

		CComQIPtr<ILDOMElement> element = m_pNode;

		BSTR bselect;
		element->getAttribute(L"select", &bselect);
		_bstr_t text = _bstr_t(bselect, false);

		const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

		Gdiplus::RectF size(0,0,0,0);
		pC->m_pGraphics->MeasureString(text, text.length(), pFont, Gdiplus::PointF(0,0), &size);

		m_customBlockTop = size.Height;
		m_customBlockBottom = size.Height;

		CalculateChildrenDimensions(pC);
		SetdownFont(pC);
	}

	virtual BOOL HasDistributableChildren()
	{
		return TRUE;
	}

BEGIN_COM_MAP(CPXSLTForEachElement)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()
};

class CPXSLTApplyTemplatesElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CHTMPElement
{
public:
	CPXSLTApplyTemplatesElement()
	{
	}

	virtual void Draw(CHTMContext* pC)
	{
		Gdiplus::Font* pFont = m_pFont;

		ATLASSERT(m_pBox);
		Gdiplus::RectF trect = m_pBox->GetAbsOuterRect();
		Gdiplus::SolidBrush textbrush(Gdiplus::Color(0,0,0));	// TODO

		const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

		pC->m_pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

		pC->m_pGraphics->DrawString(L"(contents)",
				10, pFont,
				Gdiplus::PointF(trect.X, trect.Y),
				pStringFormat,
				&textbrush);
	}
	virtual void CalculateDimensions(CHTMCalcContext* pC)
	{
		CHTMPElement::CalculateDimensions(pC);

		Gdiplus::Font* pFont = m_pFont;

		const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

		Gdiplus::RectF size(0,0,0,0);
		pC->m_pGraphics->MeasureString(L"(contents)", 10, pFont, Gdiplus::PointF(0,0), &size);
		m_specifiedWidth = m_computedWidth = size.Width;
		m_specifiedHeight = m_computedHeight = size.Height;
	}
	virtual BOOL HasDistributableChildren()
	{
		return FALSE;
	}

BEGIN_COM_MAP(CPXSLTApplyTemplatesElement)
	COM_INTERFACE_ENTRY(IUnknown)
END_COM_MAP()
};
