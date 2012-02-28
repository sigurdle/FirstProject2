#ifndef __SVGTextContentElementImpl_h_
#define __SVGTextContentElementImpl_h_

namespace System
{
namespace Web
{

class SVGEnumerationLengthAdjustTypeValue :
	public CSingleObject
{
public:

	CTOR SVGEnumerationLengthAdjustTypeValue()
	{
		m_value = LENGTHADJUST_UNKNOWN;	// undefined
	}

	/*
	SVGEnumerationLengthAdjustTypeValue* operator -> ()
	{
		return this;
	}
	*/

	operator SVGLengthAdjustType () const
	{
		return m_value;
	}

	SVGEnumerationLengthAdjustTypeValue& operator = (SVGLengthAdjustType value)
	{
		m_value = value;
		return *this;
	}

	SVGEnumerationLengthAdjustTypeValue& operator += (SVGLengthAdjustType value)
	{
		m_value = value;
		return *this;
	}

	void setStringValue(StringIn str)
	{
		if (str == L"spacing")
			m_value = LENGTHADJUST_SPACING;
		else if (str == L"spacingAndGlyphs")
			m_value = LENGTHADJUST_SPACINGANDGLYPHS;
		else
		{
			m_value = LENGTHADJUST_UNKNOWN;
			ASSERT(0);
		}
	}

	String getStringValue()
	{
		if (m_value == LENGTHADJUST_SPACING)
			return WSTR("spacing");
		else if (m_value == LENGTHADJUST_SPACINGANDGLYPHS)
			return WSTR("spacingAndGlyphs");
		else
			return NULL;
	}

	void InterpolateValue(const SVGEnumerationLengthAdjustTypeValue& a, const SVGEnumerationLengthAdjustTypeValue& b, double t)
	{
		m_value = a.m_value;
	}

/*
	IUnknown* GetUnknown()
	{
		return NULL;
	}
	*/

	SVGLengthAdjustType m_value;
};

#if 0
class SVGEXT SVGTextContentElementImplImpl : public SVGTransformableElement // SVGElement
{
public:
	CTOR SVGTextContentElementImplImpl(PSVGElement* pelement, NamedNodeMap* attributes) : SVGTransformableElement(pelement, attributes)
	{
		m_textLength = NULL;
		m_lengthAdjust = NULL;
	}

//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedLength>, CValueTypeWrapper<CreateInstanceT<SVGLengthMutable> > >* m_textLength;
};
#endif

class SVGEXT SVGTextContentElementImpl : public SVGTransformableElement//SVGTextContentElementImplImpl
{
protected:
	CTOR SVGTextContentElementImpl(PSVGElement* pelement, NamedNodeMap* attributes) : SVGTransformableElement(pelement, attributes)
	{
	//	/*static_cast<T*>(this)->*/AddXMLAttribute(NewXMLAttr(&m_textLength, NULL, WSTR("textLength")));
//		/*static_cast<T*>(this)->*/AddXMLAttribute(NewXMLAttr(&m_lengthAdjust, NULL, WSTR("lengthAdjust"), WSTR("spacing")));
	}

public:
	ISVGAnimatedLength* get_textLength()
	{
		return m_textLength;
	}

	ISVGAnimatedEnumeration* get_lengthAdjust()
	{
		return NULL;//m_lengthAdjust->m_animated;
	}

	long getNumberOfChars()
	{
		ASSERT(0);
		return 0;
#if 0
		CComPtr<ILDOMNode> node;
		static_cast<T*>(this)->get_firstChild(&node);
		while (node)
		{
			LDOMNodeType nodeType;
			node->get_nodeType(&nodeType);

			if (nodeType == LNODE_ELEMENT)
			{
				CComQIPtr<ILSVGTextContentElement> textContent = node;
				if (textContent)
				{
					long length;
					textContent->getNumberOfChars(&length);

					(*pVal) += length;
				}
				else
				{
					// TODO
				}
			}
			else if (nodeType == LNODE_TEXT)
			{
				CComQIPtr<ILDOMCharacterData> charnode = node;

				long length;
				charnode->get_length(&length);

				(*pVal) += length;
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		return S_OK;
#endif
	}

	double getComputedTextLength()
	{
		ASSERT(0);
		return 0;
#if 0
		if (m_pNodes.GetSize() > 0)
		{
			*pVal = ((PSVGElement*)m_pNodes[0])->m_textLength;
			return S_OK;
		}
		else
		{
			ASSERT(0);
			return E_FAIL;
		}
#endif
	}

	double getSubStringLength(long charnum, long nchars)
	{
		ASSERT(0);
		return 0;
	}

	SVGPoint* getStartPositionOfChar(long charnum)
	{
		ASSERT(0);
		return NULL;
	}

	SVGPoint* getEndPositionOfChar(long charnum)
	{
		ASSERT(0);
		return NULL;
	}

	ISVGRect* getExtentOfChar(long charnum)
	{
		ASSERT(0);
		return NULL;
	}

	double getRotationOfChar(long charnum)
	{
		ASSERT(0);
		return 0;
	}

	long getCharNumAtPosition(const SVGPoint* point)
	{
		ASSERT(0);
		return 0;
	}

	void selectSubString(unsigned long charnum, unsigned long nchars)
	{
		ASSERT(0);
	}

	SVGAnimatedLength* m_textLength;

//	CATXMLAttr2T<CreateInstanceT<SVGAnimatedEnumerationT<SVGEnumerationLengthAdjustTypeValue> >, CValueTypeWrapper<SVGEnumerationLengthAdjustTypeValue> >* m_lengthAdjust;
};

}	// Web
}	// System

#endif // __SVGTextContentElementImpl_h_
