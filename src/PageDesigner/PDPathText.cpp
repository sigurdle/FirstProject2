#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "PDPathText.h"

#include "PDContentText.h"	// TODO remove

#include "PDDocument.h"

#include "ObjectMap.h"
#include "PDLayer.h"
#include "PDObjectGroup.h"
#include "PDObjectShape.h"
#include "PDPath.h"
#include "PDSubPath.h"
#include "PDStory.h"

///////////////
// CPWordBox

void CPWordBox::CalculateDimensions(CTextPathContext* pC)
{
	ATLASSERT(pC->m_pFont);

	const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

	Gdiplus::FontFamily family;
	pC->m_pFont->GetFamily(&family);

	m_charOffsets.RemoveAll();

	Gdiplus::RectF m_innerRect;

	m_innerRect.Width = 0;
	m_innerRect.Height = 0;

	for (int i = 0; i < m_text.length(); i++)
	{
		m_charOffsets.Add(m_innerRect.Width);

		WCHAR ch2[2] = {((BSTR)m_text)[i], 0};

		Gdiplus::RectF size(0,0,0,0);
		pC->m_pGraphics->MeasureString(ch2, 1, pC->m_pFont, Gdiplus::PointF(0,0), pStringFormat, &size);

		m_innerRect.Width += size.Width;
		m_innerRect.Height = size.Height;
	}

	m_charOffsets.Add(m_innerRect.Width);
	m_height = m_innerRect.Height;
}

//virtual
void CPWordBox::Render(CTextPathContext* pC)
{
	ATLASSERT(pC->m_pPathText);

	Gdiplus::SolidBrush blackBrush(Gdiplus::Color(255, 0, 0, 0));

	const Gdiplus::StringFormat* pStringFormat = Gdiplus::StringFormat::GenericTypographic();

	Gdiplus::FontFamily fontFamily;
	pC->m_pFont->GetFamily(&fontFamily);

	// 14.484375 = 16.0 * 1854 / 2048
	UINT ascent = fontFamily.GetCellAscent(Gdiplus::FontStyleRegular);
	float ascentPixel = pC->m_pFont->GetSize() * ascent / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

	// 3.390625 = 16.0 * 434 / 2048
	UINT descent = fontFamily.GetCellDescent(Gdiplus::FontStyleRegular);
	float descentPixel = pC->m_pFont->GetSize() * descent / fontFamily.GetEmHeight(Gdiplus::FontStyleRegular);

	float addY;

	switch (pC->m_pPathText->m_pathTextAlign)
	{
	case PATHTEXTALIGN_BASELINE:
		{
			addY = - (ascentPixel + descentPixel);
		}
		break;
		
	case PATHTEXTALIGN_ASCENDER:
		{
			addY = + descentPixel;
		}
		break;
		
	case PATHTEXTALIGN_DESCENDER:
		{
			addY = - (ascentPixel + descentPixel)-descentPixel;
		}
		break;
		
	case PATHTEXTALIGN_CENTER:
		{
			addY = - (ascentPixel + descentPixel)/2;
		}
		break;

	default:
		ATLASSERT(0);
	}

	for (int i = 0; i < m_text.length(); i++)
	{
		Gdiplus::Matrix matrix;
		matrix.RotateAt(m_charRotations[i], Gdiplus::PointF(m_charPositions[i].x, m_charPositions[i].y));

		Gdiplus::Matrix oldmat;
		pC->m_pGraphics->GetTransform(&oldmat);
		pC->m_pGraphics->MultiplyTransform(&matrix);

		Gdiplus::PointF point(m_charPositions[i].x, m_charPositions[i].y + addY);

		pC->m_pGraphics->DrawString(&((BSTR)m_text)[i], 1, pC->m_pFont, point, pStringFormat, &blackBrush);

		pC->m_pGraphics->SetTransform(&oldmat);
	}
}

//virtual
BOOL CPWordBox::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset)
{
	for (int i = 0; i < m_text.length(); i++)
	{
		gmMatrix3 mat = gmMatrix3::identity();

		mat *= gmMatrix3::translate(-m_charPositions[i].x, -m_charPositions[i].y);
		mat *= gmMatrix3::rotate(m_charRotations[i]);
		mat *= gmMatrix3::translate(m_charPositions[i].x, m_charPositions[i].y);

		gmMatrix3 imat = mat.inverse();

		RectD rect;
		rect.X = m_charPositions[i].x;
		rect.Y = m_charPositions[i].y;
		rect.Width = m_charOffsets[i+1] - m_charOffsets[i];
		rect.Height = m_height;

		gmVector2 xpt = imat.transform(gmVector2(x, y));

		if (xpt[0] >= rect.X && xpt[1] >= rect.Y &&
			xpt[0] <= rect.X+rect.Width && xpt[1] <= rect.Y+rect.Height)
		{
			*pNode = m_node;
			(*pNode)->AddRef();

			*pOffset = m_start + i;

			return TRUE;
		}
	}

	return FALSE;
}

//virtual
void CPWordBox::RenderSelection(CTextPathContext* pContext, HDC hDC, IPDMatrix* matrix, ILDOMRange* range)
{
	CComPtr<ILDOMNode> startContainer;
	long startOffset;

	CComPtr<ILDOMNode> endContainer;
	long endOffset;

	range->get_startContainer(&startContainer);
	range->get_startOffset(&startOffset);

	range->get_endContainer(&endContainer);
	range->get_endOffset(&endOffset);

	int startChar = -1;
	int endChar = -1;

	if (!pContext->m_bInSelection)
	{
		// Check for start of selection
		if ((startContainer == m_node) &&
			(startOffset >= m_start && startOffset <= m_start+m_text.length()))
		{
			pContext->m_bInSelection = TRUE;
			startChar = startOffset - m_start;
		}
	}
	else
		startChar = 0;

	if (pContext->m_bInSelection)
	{
		// Check for end of selection
		if ((endContainer == m_node) &&
			(endOffset >= m_start && endOffset <= m_start+m_text.length()))
		{
			pContext->m_bInSelection = FALSE;
			endChar = endOffset - m_start;
		}
		else
			endChar = m_text.length();
	}

	if (startChar >= 0 && endChar >= 0)
	{
		for (int i = startChar; i < endChar; i++)
		{
			CComQIPtr<IPDObject> parent = pContext->m_pPathText->m_parentFrame;

			CComPtr<IPDMatrix> ctm0;
			parent->getScreenCTM(&ctm0);

			CComPtr<IPDMatrix> ctm2;
			ctm0->translate(-m_charPositions[i].x, -m_charPositions[i].y, &ctm2);

			CComPtr<IPDMatrix> ctm3;
			ctm2->rotate(m_charRotations[i], &ctm3);

			CComPtr<IPDMatrix> ctm4;
			ctm3->translate(m_charPositions[i].x, m_charPositions[i].y, &ctm4);

			CComPtr<IPDMatrix> ctm;
			ctm4->multiply(matrix, &ctm);

			RectD rect;
			rect.X = m_charPositions[i].x;
			rect.Y = m_charPositions[i].y;
			rect.Width = m_charOffsets[i+1] - m_charOffsets[i];
			rect.Height = m_height;

			PointD pt[4] =
			{
				rect.X, rect.Y,
				rect.X+rect.Width, rect.Y,
				rect.X+rect.Width, rect.Y+rect.Height,
				rect.X, rect.Y+rect.Height,
			};

			POINT xpt[4];

			for (int i = 0; i < 4; i++)
			{
				PointD dxpt;
				ctm->transformPoint(&pt[i], &dxpt);

				xpt[i].x = dxpt.x;
				xpt[i].y = dxpt.y;
			}

			Polygon(hDC, xpt, 4);
		}
	}

	/*

		if (startChar == endChar)
		{
			rect.X = rc.X + m_charOffsets[startChar];
			rect.Y = rc.Y;
			rect.Width = 2;
			rect.Height = rc.Height;
		}
		else
		{
			rect.X = rc.X + m_charOffsets[startChar];
			rect.Y = rc.Y;
			rect.Width = m_charOffsets[endChar]-m_charOffsets[startChar];
			rect.Height = rc.Height;
		}

		PointD pt[4] =
		{
			rect.X, rect.Y,
			rect.X+rect.Width, rect.Y,
			rect.X+rect.Width, rect.Y+rect.Height,
			rect.X, rect.Y+rect.Height,
		};

		CComPtr<IPDMatrix> ctm0;
		pContext->m_pContentText->getScreenCTM(&ctm0);

		CComPtr<IPDMatrix> ctm;
		ctm0->multiply(matrix, &ctm);

		POINT xpt[4];

		for (int i = 0; i < 4; i++)
		{
			PointD dxpt;
			ctm->transformPoint(&pt[i], &dxpt);

			xpt[i].x = dxpt.x;
			xpt[i].y = dxpt.y;
		}

		Polygon(hDC, xpt, 4);
	}
	*/
}

/////////////////////////////////
// CPElementBox

//virtual
void CPElementBox::Render(CTextPathContext* pC)
{
	if (m_pElement)
	{
		ATLASSERT(m_pElement);
		m_pElement->SetupFont(pC);
	}

	for (int i = 0; i < m_children.GetSize(); i++)
	{
		m_children[i]->Render(pC);
	}

	if (m_pElement)
		m_pElement->SetdownFont(pC);
}

//virtual
BOOL CPElementBox::getPosUnderPoint(double x, double y, ILDOMNode **pNode, long *pOffset)
{
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		BOOL b = m_children[i]->getPosUnderPoint(x, y, pNode, pOffset);
		if (b)
			return TRUE;
	}

	return FALSE;
}

//virtual
void CPElementBox::RenderSelection(CTextPathContext* pC, HDC hDC, IPDMatrix* matrix, ILDOMRange* range)
{
	for (int i = 0; i < m_children.GetSize(); i++)
	{
		m_children[i]->RenderSelection(pC, hDC, matrix, range);
	}
}

//////////////////////////////////
// CTextPathContext

//virtual
BOOL CTextPathContext::PlaceWord(CNode* node, int start, _bstr_t data)
{
	CPWordBox* pWord = new CPWordBox;
	pWord->m_start = start;
	pWord->m_text = data;
	pWord->m_node = node->m_node;

	pWord->m_parent = m_pCurElementBox;
	m_pCurElementBox->m_children.Add(pWord);

	pWord->CalculateDimensions(this);

	for (int i = 0; i < pWord->m_text.length(); i++)
	{
		double x;
		double y;
		double rotation;

		double charWidth = (pWord->m_charOffsets[i+1] - pWord->m_charOffsets[i]);

		HRESULT hr = m_path->getPointOnLength(m_lengthSoFar+charWidth/2, &x, &y, &rotation);
		if (FAILED(hr))
		{
			delete pWord;
			return FALSE;
		}

		pWord->m_charRotations.Add(rotation);
		pWord->m_charPositions.Add(CDblPoint(x, y));

		m_lengthSoFar += charWidth;
	}

	m_lengthSoFar += 8;	// TODO space

	return TRUE;
}

//virtual
BOOL CTextPathContext::PlaceObject(IPDObject* object)
{
	ATLASSERT(0);
	return FALSE;
}

//virtual
CTextContext* CTextPathContext::SetupElement(CElement* pElement)
{
	CTextPathContext* pC = new CTextPathContext;
	pC->m_pGraphics = m_pGraphics;
	pC->m_pFont = m_pFont;
	pC->m_path = m_path;
	pC->m_pPathText = m_pPathText;

	pC->m_pCurElementBox = new CPElementBox;	// Create new element box
	pC->m_pCurElementBox->m_pElement = pElement;

	if (m_pCurElementBox == NULL)	// outermost container box
	{
		m_pPathText->m_pBox = pC->m_pCurElementBox;
	}
	else
	{
		pC->m_pCurElementBox->m_parent = m_pCurElementBox;
		m_pCurElementBox->m_children.Add(pC->m_pCurElementBox);
	}

	return pC;
}

//virtual
void CTextPathContext::SetdownElement(CElement* pElement, CTextContext* _pC)
{
	CTextPathContext* pC = (CTextPathContext*)_pC;

	delete pC;
}

//////////////////////////////////////
// CPDPathText

//virtual
CTextContext* CPDPathText::SetupBox(CStoryFlowContext* pContext)
{
	ATLASSERT(m_pBox == NULL);

	CPDObjectFrame* pFrame = (CPDObjectFrame*)m_parentFrame;
	ATLASSERT(pFrame);

	CTextPathContext* pC = new CTextPathContext;
	pC->m_pPathText = this;
	pFrame->m_path->getSubPath(0, &pC->m_path);

	return pC;
}

//virtual
void CPDPathText::SetdownBox(CTextContext* _pC)
{
	CTextPathContext* pC = (CTextPathContext*)_pC;
	delete pC;
}

//virtual
void CPDPathText::Clear()
{
	if (m_pBox)
	{
		delete m_pBox;
		m_pBox = NULL;
	}
}

//virtual
void CPDPathText::Render(CPDRenderer* pRenderer, Gdiplus::Graphics* pGraphics, double scaleX, double scaleY)
{
	CTextPathContext* pC = new CTextPathContext;
	pC->m_pGraphics = pGraphics;
	pC->m_pPathText = this;

	pGraphics->SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAlias);

	if (m_pBox)
	{
		m_pBox->Render(pC);
	}

	delete pC;
}

STDMETHODIMP CPDPathText::RenderSelection(/*[in]*/ HDC hDC, /*[in]*/ IPDMatrix* matrix, /*[in]*/ ILDOMRange* range)
{
	if (m_pBox)
	{
		HPEN hOldPen = (HPEN)SelectObject(hDC, GetStockObject(NULL_PEN));
		HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, GetStockObject(BLACK_BRUSH));

		CTextPathContext* pC = new CTextPathContext;
		pC->m_pPathText = this;

		m_pBox->RenderSelection(pC, hDC, matrix, range);

		delete pC;

		SelectObject(hDC, hOldPen);
		SelectObject(hDC, hOldBrush);
	}

	return S_OK;
}

STDMETHODIMP CPDPathText::getPosUnderPoint(/*[in]*/ double x, /*[in]*/ double y, /*[out]*/ ILDOMNode* *pNode, /*[out]*/ long *pOffset, /*[out,retval]*/ BOOL *bHit)
{
	ATLASSERT(pNode);
	ATLASSERT(pOffset);
	ATLASSERT(bHit);

	if (pNode == NULL) return E_POINTER;
	if (pOffset == NULL) return E_POINTER;
	if (bHit == NULL) return E_POINTER;

	*pNode = NULL;
	*pOffset = 0;

	if (m_pBox)
	{
		*bHit = m_pBox->getPosUnderPoint(x, y, pNode, pOffset);
	}
	else
	{
		*bHit = FALSE;
	}

	return S_OK;
}

STDMETHODIMP CPDPathText::get_startOnLength(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_startOnLength;
	return S_OK;
}

STDMETHODIMP CPDPathText::put_startOnLength(double newVal)
{
	m_startOnLength = newVal;
	return S_OK;
}

STDMETHODIMP CPDPathText::get_endOnLength(double *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_endOnLength;
	return S_OK;
}

STDMETHODIMP CPDPathText::put_endOnLength(double newVal)
{
	m_endOnLength = newVal;
	return S_OK;
}

#if 0
STDMETHODIMP CPDPathText::saveAsXML(/*[in]*/ IDOMDocument* document, /*[in]*/ IDOMNode* node, BOOL saveId)
{
	HRESULT hr;
	hr = CPDObjectTextImpl<IPDPathText>::saveAsXML(document, node, saveId);
	if (FAILED(hr)) return hr;

	ATLASSERT(0);
	return S_OK;
}

STDMETHODIMP CPDPathText::loadXML(/*[in]*/ IDOMNode* node)
{
	HRESULT hr;
	hr = CPDObjectTextImpl<IPDPathText>::loadXML(node);
	if (FAILED(hr)) return hr;

	ATLASSERT(0);
	return S_OK;
}
#endif

STDMETHODIMP CPDPathText::get_wrapPath(IPDPath **pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDPathText::put_wrapPath(IPDPath *newVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}

STDMETHODIMP CPDPathText::get_pathTextAlign(PDPathTextAlign *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pathTextAlign;
	return S_OK;
}

STDMETHODIMP CPDPathText::put_pathTextAlign(PDPathTextAlign newVal)
{
	m_pathTextAlign = newVal;
	// TODO update
	return S_OK;
}

STDMETHODIMP CPDPathText::get_pathTextAlignToPath(PDPathTextAlignToPath *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pathTextAlignToPath;
	return S_OK;
}

STDMETHODIMP CPDPathText::put_pathTextAlignToPath(PDPathTextAlignToPath newVal)
{
	m_pathTextAlignToPath = newVal;
	// TODO update
	return S_OK;
}

STDMETHODIMP CPDPathText::getExpandedBBox(RectD *pVal)
{
	// TODO: Add your implementation code here

	return S_OK;
}
