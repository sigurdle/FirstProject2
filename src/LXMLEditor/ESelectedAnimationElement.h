#pragma once

#include "ESVGElementImpl.h"
#include "ESelectedElementImpl.h"

#include "EXMLViewGroup.h"

namespace System
{
namespace LXmlEdit
{

class CESelectedAnimationElement : 
	public CESelectedElementImpl<IESelectedAnimationElement>,
	public IESVGDrawOutline,
	public IESVGDrawSelection
{
public:
	CESelectedAnimationElement()
	{
	}

	~CESelectedAnimationElement()
	{
	}

	IESelectedElement* m_selectedTargetElement;

	Array<int> m_selectedKeyTimes;	// Keep this sorted

public:

	ErrorCode GetSelectedKeyTimesCount(/*[out,retval]*/ long *pVal)
	{
		*pVal = m_selectedKeyTimes.GetSize();
		return Success;
	}

	ErrorCode GetKeyTimeSelected(/*[in]*/ long index, /*[out,retval]*/ long *pVal)
	{
		*pVal = m_selectedKeyTimes[index];
		return Success;
	}

	ErrorCode IsKeyTimeSelected(/*[in]*/ long index, /*[out,retval]*/ bool *pVal)
	{
		int min = 0;        // beginning of search range 
		int max = m_selectedKeyTimes.GetSize();   // end of search range 

		int n = max / 2;
		while (min < max)
		{
			if (index < m_selectedKeyTimes[n])
				max = n;
			else if (index > m_selectedKeyTimes[n])
				min = n + 1;
			else
			{
				*pVal = true;
				return Success;
			}

			n = (min + max) / 2;
		}

		*pVal = false;
		return Success;
	}

	ErrorCode SelectKeyTime(/*[in]*/ long index)
	{
		for (int i = 0; i < m_selectedKeyTimes.GetSize(); i++)
		{
			if (index == m_selectedKeyTimes[i]) return Success;
			else if (index < m_selectedKeyTimes[i]) break;
		}

		ASSERT(0);
#if 0
		static_cast<CEXMLViewGroup*>(m_viewGroup)->Fire_SelectionChanging();
		m_selectedKeyTimes.InsertAt(i, index);
		static_cast<CEXMLViewGroup*>(m_viewGroup)->Fire_SelectionChanged();
#endif
		return Success;
	}

	ErrorCode DeselectKeyTime(/*[in]*/ long index)
	{
		int i;
		for (i = 0; i < m_selectedKeyTimes.GetSize(); i++)
		{
			if (index == m_selectedKeyTimes[i])
				break;
		}

		if (i < m_selectedKeyTimes.GetSize())
		{
			ASSERT(0);
#if 0
			static_cast<CEXMLViewGroup*>(m_viewGroup)->Fire_SelectionChanging();
			m_selectedKeyTimes.RemoveAt(i);
			static_cast<CEXMLViewGroup*>(m_viewGroup)->Fire_SelectionChanged();
#endif
		}

		return Success;
	}

	ErrorCode DeselectAllKeyTimes()
	{
		ASSERT(0);
#if 0
		static_cast<CEXMLViewGroup*>(m_viewGroup)->Fire_SelectionChanging();
		m_selectedKeyTimes.RemoveAll();
		static_cast<CEXMLViewGroup*>(m_viewGroup)->Fire_SelectionChanged();
#endif
		return Success;
	}
	void Move(ISVGView* view, double dx, double dy);
	ErrorCode MoveSelectedPoints(_SVGHitData* hitdata, LDraw::PointD xnewpt2, LDraw::PointD xoldpt2);

	ErrorCode HitTest(ISVGView* view, Web::SVGSVGElement* svgsvgElement, Web::SVGMatrix* ctm, double ptx, double pty, long tool, _SVGHitData* hit);

	ErrorCode DeleteSelection();

// IESVGDrawOutline
	void DrawOutline(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);

// IESVGDrawSelection
	virtual ErrorCode DrawSelection(UI::Graphics* pGraphics, LDraw::Color color, Web::SVGMatrix* matrix);
};

}	// LXmlEdit
}
