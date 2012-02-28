#include "stdafx.h"
#include "CSS.h"

#if 0
#include "ViewCSS.h"

#include "cssproperty.h"
#include "CSSStyleRule.h"
#include "CSSRuleList.h"
#include "CSSStyleSheet.h"
#include "CSSImportRule.h"
#include "StyleSheetList.h"
//#include "DocumentStyleImpl.h"

#include "CSSStyleDeclaration.h"
#endif

namespace System
{
namespace Style
{

/*
Since child elements (generally) inherit the computed values of their parent, in
the following example, the children of the P element will inherit a value
of 12pt for 'line-height', not the percentage value (120%): 

*/

/*
Conflicting rules are intrinsic to the CSS mechanism. To find the value for an element/property combination, the following algorithm must be followed: 

Find all declarations that apply to the element/property in question.
Declarations apply if the selector matches the element in question.
If no declarations apply, the inherited value is used. If there
is no inherited value (this is the case for the 'HTML' element and
for properties that do not inherit), the initial value is used. 

  1.
Sort the declarations by explicit weight: declarations marked '!important' carry
more weight than unmarked (normal) declarations. 

  2.
Sort by origin: the author's style sheets override the reader's style sheet which
override the UA's default values. An imported style sheet has the same origin as
the style sheet from which it is imported. 

  3.
Sort by specificity of selector: more specific selectors will override more general
ones. To find the specificity, count the number of ID attributes in the selector (a),
the number of CLASS attributes in the selector (b), and the number of tag names in the selector (c). Concatenating the three numbers (in a number system with a large base) gives the specificity. Some examples: 

LI            {...}  // a=0 b=0 c=1 -> specificity =   1
UL LI         {...}  // a=0 b=0 c=2 -> specificity =   2
UL OL LI      {...}  // a=0 b=0 c=3 -> specificity =   3
LI.red        {...}  // a=0 b=1 c=1 -> specificity =  11
UL OL LI.red  {...}  // a=0 b=1 c=3 -> specificity =  13 
#x34y         {...}  // a=1 b=0 c=0 -> specificity = 100

Pseudo-elements and pseudo-classes are counted as normal elements and classes, respectively. 

  4.
Sort by order specified: if two rules have the same weight, the latter specified wins.
Rules in imported style sheets are considered to be before any rules in the style sheet
itself. 

  The search for the property value can be terminated whenever one rule has a higher
  weight than the other rules that apply to the same element/property combination. 

This strategy gives author's style sheets considerably higher weight than those of the reader. It is therefore important that the reader has the ability to turn off the influence of a certain style sheet, e.g. through a pull-down menu. 

A declaration in the 'STYLE' attribute of an element (see section 1.1 for an example) has the same weight as a declaration with an ID-based selector that is specified at the end of the style sheet: 

*/

/*
In HTML, values of an element's "style" attribute are style sheet rules.
These rules have no selectors, but for the purpose of step 3 of the
cascade algorithm, they are considered to have an ID selector
(specificity: a=1, b=0, c=0). For the purpose of step 4, they are
considered to be after all other rules. 
*/

#if 0
class CDecl
{
public:
	CComPtr<ILCSSValue> cssvalue;

	DWORD specificity;
	BOOL important;
};
#endif

bool SimpleSelectorSequence::SimpleSelectorSequenceMatches(ICSSElementResolver* pElement)
{
	for (size_t i = 0; i < m_items.size(); ++i)
	{
		SimpleSelector* pSimpleSelector = m_items[i];

		bool bMatches = pSimpleSelector->MatchesElement(pElement);
		if (!bMatches)
		{
			return false;
		}
	}

	return true;
}

bool Selector::SelectorMatches(ICSSElementResolver* element)
{
	SimpleSelectorSequence* pSimpleSelectorSequence = m_pRight;

	bool bMatches = pSimpleSelectorSequence->SimpleSelectorSequenceMatches(element);
	if (!bMatches)
		return false;

	SimpleSelectorSequence* pLeftSimpleSelectorSequence = pSimpleSelectorSequence->m_pLeft;

	while (pLeftSimpleSelectorSequence)
	{
		if (pLeftSimpleSelectorSequence->m_combinator == L' ')
		{
			ICSSElementResolver* element2 = element->get_rparent();

			while (element2)
			{
				bool bMatches = pLeftSimpleSelectorSequence->SimpleSelectorSequenceMatches(element2);
				if (bMatches)
					break;

				ICSSElementResolver* rparent = element2->get_rparent();
				element2 = rparent;
			}

			if (element2)
			{
				element = element2;
			}
			else
				return false;
		}
		else if (pLeftSimpleSelectorSequence->m_combinator == L'+')
		{
			ICSSElementResolver* element2 = element->get_prevSibling();
			if (element2)
			{
				bool bMatches = pLeftSimpleSelectorSequence->SimpleSelectorSequenceMatches(element2);
				if (bMatches)
				{
					element = element2;
				}
				else
					return false;
			}
			else
				return false;
#if 0
			UPOSITION pos = element->m_parent->m_childList.Find(element);

			element->m_parent->m_childList.GetPrev(pos);
			if (pos)
			{
				CPElementBase* element2 = (CPElementBase*)element->m_parent->m_childList.GetAt(pos);

		// TODO
				BOOL bMatches = pLeftSimpleSelectorSequence->SimpleSelectorSequenceMatches(element2);
				if (bMatches)
				{
					element = element2;
				}
				else
					return FALSE;
			}
			else
				return FALSE;
#endif
		}
		else if (pLeftSimpleSelectorSequence->m_combinator == L'>')
		{
			ICSSElementResolver* pParentElement = element->get_rparent();

			if (pParentElement)
			{
				bool bMatches = pLeftSimpleSelectorSequence->SimpleSelectorSequenceMatches(pParentElement);
				if (bMatches)
				{
					element = pParentElement;
				}
				else
					return false;
			}
			else
				return false;
		}
		else	// Unknown combinator
			ASSERT(0);

		pLeftSimpleSelectorSequence = pLeftSimpleSelectorSequence->m_pLeft;
	}

	return true;
}

uint SingleSelectorRule::GetSpecificity()
{
	if (m_selector)
		return m_selector->m_specificity;
	else
		return 100;	// style attribute
}

// Find all selectors that match the element
// static
void StyleSheet::GetStyleSheetMatches(IStyleSheet* styleSheet, CSSElementMatches* matches, ICSSElementResolver* pPElement)
{
	VerifyArgumentNotNull(styleSheet);
//	ICSSRuleList* ruleList = get_cssRules();

	size_t nrules = styleSheet->GetRuleCount();

	for (size_t nrule = 0; nrule < nrules; ++nrule)
	{
		ICSSRule* rule = styleSheet->GetRule(nrule);

		switch (rule->get_type())
		{
		case STYLE_RULE:
			{
				ICSSStyleRule* styleRule = static_cast<ICSSStyleRule*>(rule);

				SelectorList* selectorList = styleRule->get_selectorList();
				size_t nselectors = selectorList->get_length();

				for (size_t i = 0; i < nselectors; ++i)
				{
					Selector* pSelector = selectorList->item(i);

					/*
					if (!wcscmp(pRule->m_selectorText, L".navBlock h2.navhead"))
					{
					}
					*/
					/*
					if (pSelector->m_pseudoElement.length() > 0)
					{
					MessageBeep(-1);
					}
					*/
					String pseudoElementName = pPElement->get_pseudoElementName();

					if (pSelector->m_pseudoElement == pseudoElementName)
					{
						bool bMatches = pSelector->SelectorMatches(pPElement);

						if (bMatches)
						{
							if (pSelector->m_singleSelectorRule == NULL)
							{
								pSelector->m_singleSelectorRule = new SingleSelectorRule(pSelector, styleRule->get_declaration());
							}

							matches->m_rules.push_back(pSelector->m_singleSelectorRule);
						}
					}
				}
			}
			break;

		case IMPORT_RULE:
			{
				ICSSImportRule* importRule = static_cast<ICSSImportRule*>(rule);

				// Recurse
				IStyleSheet* styleSheet = importRule->get_styleSheet();

				StyleSheet::GetStyleSheetMatches(styleSheet, matches, pPElement);
			}
			break;
		}
	}
}

// static
CSSElementMatches* ViewCSS::GetDeclMatches(IDocumentStyle* documentStyle, ICSSElementResolver* pPElement)
{
	CSSElementMatches* pMatches = new CSSElementMatches;

	pMatches->m_elementResolver = pPElement;

#if 0
	{
		for (int i = 0; i < pPElement->m_declMatches.GetSize(); i++)
		{
			delete pPElement->m_declMatches[i];
		}
		pPElement->m_declMatches.RemoveAll();
	}
#endif

// Try all the document's stylesheets
	IStyleSheetList* styleSheets = documentStyle->get_styleSheets();
	if (styleSheets)
	{
		size_t count = styleSheets->get_length();

		for (size_t i = 0; i < count; ++i)
		{
			IStyleSheet* styleSheet = styleSheets->item(i);

			StyleSheet::GetStyleSheetMatches(styleSheet, pMatches, pPElement);
		}
	}

#if 0	// TODO
	LSVG::SVGElement* svgStylable = dynamic_cast<LSVG::SVGElement*>(dynamic_cast<LXML::CPElementBase*>(pPElement)->m_pNode);
	if (svgStylable)
	{
//		fstyle = svgStylable->m_presentationAttributes->getPropertyCSSValue(csstyleList[propertyIndex].m_name);
			CStyleDeclarationMatch* pMatch = new CStyleDeclarationMatch;
			//pMatch->GetSpecificity = 100;	// a=1

			pMatch->m_style = svgStylable->m_presentationAttributes;
			pMatches->m_declMatches.Add(pMatch);
	}
#endif

	{
		IStyleDeclaration* inlineStyle = pPElement->get_inlineStyle(1);
		if (inlineStyle)
		{
			SingleSelectorRule* rule = new SingleSelectorRule(NULL, inlineStyle);
			pMatches->m_rules.Add(rule);
		}
	}

	IStyleDeclaration* inlineStyle = pPElement->get_inlineStyle(0);
	if (inlineStyle)
	{
		SingleSelectorRule* rule = new SingleSelectorRule(NULL, inlineStyle);
		pMatches->m_rules.Add(rule);
	}

#if 0	// TODO
	CComQIPtr<ILElementCSSInlineStyle> stylableElement;
	if (stylableElement = pPElement->m_pNode)
	{
		CComQIPtr<ILCSSStyleDeclaration> inlinestyle;
		stylableElement->get_style(&inlinestyle);

		if (inlinestyle)
		{
			CStyleDeclarationMatch* pMatch = new CStyleDeclarationMatch;
			//pMatch->GetSpecificity = 100;	// a=1

			pMatch->m_style = static_cast<CLCSSStyleDeclaration*>(inlinestyle.p);
			pPElement->m_declMatches.Add(pMatch);
		}
	}
#endif

	return pMatches;
}

/*
ICSSStyleDeclaration* ViewCSS::getComputedStyle(Element *elt, StringW* pseudoElt)
{
	ASSERT(0);
	return NULL;
}
*/

/* NOTE (this note should appear somewhere else though)

	width/height/left/top.. I cache the 'specified' PropertyValue for these once
	(in CalcDims()), and on every reflow I compute a new 'computed' value based on the
	cached 'specified' value and any parent element's width for example
	(if the specified value is a % .. )

*/

#if 0
int CLViewCSS::GetComputedPropertyValue(ILDocumentStyle* documentStyle, CPElement* pElement, int propertyIndex, CSSProperty* cssstyle, ILCSSValue** value)
{
	if (pElement->GetCachedComputedProperty(propertyIndex, value) == 0)
		return 0;

	ASSERT(0);

	return 1;
}
#endif

/*
6.4.4 Precedence of non-CSS presentational hints

The UA may choose to honor presentational hints from other sources than style
sheets, for example the FONT element or the "align" attribute in HTML. If so,
the non-CSS presentational hints must be translated to the corresponding CSS
rules with specificity equal to zero. The rules are assumed to be at the
start of the author style sheet and may be overridden by subsequent style
sheet rules. 
*/

#if 0
int CLViewCSS::GetSpecifiedPropertyValue(ILDocumentStyle* documentStyle, CPElement* pElement, int propertyIndex, CSSProperty* cssstyle, /*BSTR pseudoElt,*/ ILCSSValue** value, BOOL bIncludeOverride)
{
	ASSERT(0);
#if 0
//	CSSDecl* pFDecl = NULL;
	DWORD specificity = 0;
	CComQIPtr<ILCSSValue> fstyle;

	//CComQIPtr<ILSMILAnimationTarget> overrideStyleElement = pElement->m_pNode;
	//if (overrideStyleElement)
	if (bIncludeOverride)
	{
		if (pElement->m_pOverrideStyle->m_decls.GetSize() > 0)
		{
			ILCSSValue* cssvalue;
			pElement->m_pOverrideStyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);

			if (cssvalue != NULL)
			{
				fstyle = cssvalue;
			}
		}
	}

	if (fstyle == NULL)	// ??
	{
		ILSVGStylable* svgStylable = dynamic_cast<ILSVGStylable*>(pElement->m_pNode);
		if (svgStylable)
		{
			svgStylable->getPresentationAttribute(csstyleList[propertyIndex].m_name, &fstyle);
		}

		for (int i = pElement->m_declMatches.GetSize()-1; i >= 0; i--)
		{
			CStyleDeclarationMatch* pMatch = pElement->m_declMatches[i];

#if 0
			if (pMatch->m_selector == NULL ||
				!cmpbstr(pMatch->m_selector->m_pseudoElement, pElement->m_pseudoElementName))
#endif
				/*
				((pMatch->m_selector->m_pseudoElement.Length() == pElement->m_pseudoElementName.Length()) &&
				(pMatch->m_selector->m_pseudoElement.Length()==0 || !wcscmp(pMatch->m_selector->m_pseudoElement, pElement->m_pseudoElementName))))
				*/
			{
				CSSDecl* pPropertyDecl = pMatch->m_style->FindDecl(propertyIndex);
				if (pPropertyDecl)	// Property is declared
				{
					if (fstyle == NULL/*pFDecl == NULL*/)
					{
						//pFDecl = pPropertyDecl;
						fstyle.Release();
						CComPtr<IUnknown> unk;
						pPropertyDecl->m_pValue->getObject(&unk);
						fstyle = unk;

						specificity = pMatch->GetSpecificity();
					}
					else
					{
						/*
						// Sort by importance
						if (pPropertyDecl->m_priority.length() && pFDecl->m_priority.length() == 0)
						{
							pFDecl = pPropertyDecl;
							specificity = pMatch->m_specificity;
						}
						// Sort by specificity of selector
						else
							*/
							if (pMatch->GetSpecificity() > specificity)
						{
						//	pFDecl = pPropertyDecl;

							fstyle.Release();
							CComPtr<IUnknown> unk;
							pPropertyDecl->m_pValue->getObject(&unk);
							fstyle = unk;

							specificity = pMatch->GetSpecificity();
						}
							/*
						// Sort by order specified
						else
						{
							pFDecl = pPropertyDecl;
							specificity = pMatch->m_specificity;
						}
						*/
					}
				}
			}
		}
	}

	//CComQIPtr<ILCSSValue> fstyle;
	
//	if (pFDecl)
//		pFDecl->m_pValue->getCSSValue(&fstyle);

#if 0
	CComQIPtr<ILDOMElement> element = pElement->m_pNode;

	CComQIPtr<ILCSSValue> fstyle;

	ILSMILAnimationTarget* overrideStyleElement = element;
	if (overrideStyleElement)
	{
		if (static_cast<CAnimationTarget*>(overrideStyleElement)->m_overrideStyle->m_decls.GetSize() > 0)
		{
			ILCSSValue* cssvalue;
			static_cast<CAnimationTarget*>(overrideStyleElement)->m_overrideStyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);

			if (cssvalue != NULL)
			{
				fstyle = cssvalue;
			}
		}
	}

	if (fstyle == NULL)
	{
		CArray<CDecl,CDecl&> decls;
		decls.SetSize(0, 20);

	// Try all the document's stylesheets
		CComQIPtr<ILStyleSheetList> styleSheets;
		documentStyle->get_styleSheets(&styleSheets);

		long count;
		styleSheets->get_length(&count);

		for (long i = 0; i < count; i++)
		{
			ILCSSStyleSheet* styleSheet;
			styleSheets->item(i, (ILStyleSheet**)&styleSheet);

			GetStyleSheetDecls(styleSheet, element, cssstyle->m_name, decls);
		}

		DWORD	fspecificity = 0;

		for (i = 0; i < decls.GetSize(); i++)
		{
			if (decls[i].specificity > fspecificity)
			{
				fstyle = decls[i].cssvalue;
				fspecificity = decls[i].specificity;
			}
		}

	// Try the inline style attribute
		if (fspecificity <= 10000)
		{
			CComQIPtr<ILCSSStyleDeclaration> inlinestyle;

			CComQIPtr<ILElementCSSInlineStyle> stylableElement;
			if (stylableElement = element)
			{
				stylableElement->get_style(&inlinestyle);
			}

			if (inlinestyle)
			{
				ILCSSValue* cssvalue;
				inlinestyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);
				if (cssvalue != NULL)
				{
					fstyle = cssvalue;
				}
			}
		}

		if (fspecificity == 0)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);
			if (!WCSCMP(tagName, L"font", m_isXML))
			{
				if (propertyIndex == CSSProperty_font_size)
				{
					BSTR bsize;
					element->getAttribute(L"size", &bsize);
					if (bsize)
					{
						CComObject<CSSPrimitiveValue>* pCSSValue;
						CComObject<CSSPrimitiveValue>::CreateInstance(&pCSSValue);
						pCSSValue->AddRef();
						pCSSValue->m_propertyIndex = propertyIndex;

						if (bsize[0] == L'-')
						{
							BSTR brel = &bsize[1];
							long lrel = str2int(brel);
							pCSSValue->setFloatValue(CSS_PERCENTAGE, 100-lrel*5);
						}
						else if (bsize[0] == L'+')
						{
							BSTR brel = &bsize[1];
							long lrel = str2int(brel);
							pCSSValue->setFloatValue(CSS_PERCENTAGE, 100+lrel*5);
						}
						else
						{
							long labs = str2int(bsize);
							pCSSValue->setFloatValue(CSS_PX, 10+labs*3);
						}

						SysFreeString(bsize);

						fstyle = pCSSValue;

						pCSSValue->Release();
					}
				}
				else if (propertyIndex == CSSProperty_color)
				{
					BSTR b;
					element->getAttribute(L"color", &b);
					if (b)
					{
						COLORREF clr = ConvertColor(_bstr_t(b, false));
						if (clr != -1)
						{
							CComObject<CSSPrimitiveValue>* pCSSValue = CreateCSSUnitRGBValue(propertyIndex, Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));
							fstyle = pCSSValue;
							pCSSValue->Release();
						}
					}
				}
			}
		}
	}
#endif

	if (fstyle)
	{
		CSSValueType valueType;
		fstyle->get_cssValueType(&valueType);
		if (valueType == CSS_INHERIT)
		{
			fstyle.Release();

			CPElement* parentElement = pElement->m_parent;
			if (parentElement != NULL)
			{
				if (cssstyle)
				{
					GetComputedPropertyValue(documentStyle, parentElement, propertyIndex, cssstyle, &fstyle);
				}
			}
		}
	}

	if (fstyle == NULL)
	{
// Try inherited value from parent element (it inherits the computed value (TODO, not always?))

		// NOTE: Use the parent from the modified tree (after bindings etc.)
		CPElement* parentElement = pElement->m_rparent;
		if (parentElement != NULL)
		{
			if (cssstyle && cssstyle->m_bInherited)
			{
				GetComputedPropertyValue(documentStyle, parentElement, propertyIndex, cssstyle, &fstyle);
			}
		}
	}

	if (fstyle == NULL)
	{
		// Set initial value
		if (cssstyle)
		{
			if (cssstyle->m_initialValue == NULL)
			{
				if (cssstyle->m_initialCSS)
				{
					CComQIPtr<ILCSSValue> cssvalue;

					// Create the value of correct type
					if (*cssstyle->m_cssType == CLSID_LCSSPrimitiveValue)
					{
						CComObject<CSSPrimitiveValue>* pCSSValue;
						CComObject<CSSPrimitiveValue>::CreateInstance(&pCSSValue);
						pCSSValue->m_propertyIndex = propertyIndex;

						cssvalue = pCSSValue;
					}
					else if (*cssstyle->m_cssType == IID_ILCSSValueList)
					{
						CComObject<CLCSSValueList>* pCSSValue;
						CComObject<CLCSSValueList>::CreateInstance(&pCSSValue);
						pCSSValue->m_propertyIndex = propertyIndex;

						cssvalue = pCSSValue;
					}
					else if (*cssstyle->m_cssType == CLSID_LSVGColor)
					{
						CComObject<CLSVGColor>* pCSSValue;
						CComObject<CLSVGColor>::CreateInstance(&pCSSValue);
					//	pCSSValue->m_propertyIndex = propertyIndex;

						cssvalue = pCSSValue;
					}
					else if (*cssstyle->m_cssType == CLSID_LSVGPaint)
					{
						CComObject<CLSVGPaint>* pCSSValue;
						CComObject<CLSVGPaint>::CreateInstance(&pCSSValue);
					//	pCSSValue->m_propertyIndex = propertyIndex;

						cssvalue = pCSSValue;
					}
					else
					{
						cssvalue.CoCreateInstance(*cssstyle->m_cssType);
					}
					cssvalue->set_cssText(cssstyle->m_initialCSS);
					(cssstyle->m_initialValue = cssvalue)->AddRef();
				}
			}

			fstyle = cssstyle->m_initialValue;
		}
		else	// Unknown property
			fstyle.CoCreateInstance(CLSID_LCSSValue);
	}

	(*value = fstyle);
	if (*value) (*value)->AddRef();
#endif

	return 0;
}
#endif

#if 0
Object* Style::GetPropertyValue(DependencyObject* depobj CSSElementMatches* matches, int propertyIndex, /*BSTR pseudoElt,*/ bool bIncludeOverride, CSSValue** value)
{
}
#endif

int CSSElementMatches::GetSpecifiedPropertyValue2(Object* pProperty, bool bIncludeOverride, Variant* pvalue)
{
	//CSSProperty* cssstyle = &csspropertyList[propertyIndex];

//	CSSDecl* pFDecl = NULL;
	uint specificity = 0;
	Variant value;

	//CComQIPtr<ILSMILAnimationTarget> overrideStyleElement = pElement->m_pNode;
	//if (overrideStyleElement)
	if (bIncludeOverride)
	{
#if 0	// Had this
		if (pElement->m_pOverrideStyle->m_decls.GetSize() > 0)
		{
			CComPtr<ILCSSValue> cssvalue;
			pElement->m_pOverrideStyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);

			if (cssvalue != NULL)
			{
				fstyle = cssvalue;
			}
		}
#endif
	}

	if (value.IsUndefined())	// ??
	{
#if 0	// Had this
		IElementCSSInlineStyle* svgStylable = dynamic_cast<IElementCSSInlineStyle*>(dynamic_cast<PElementBase*>(pElement->m_elementResolver)->m_pNode);
		if (svgStylable)
		{
			fstyle = svgStylable->get_style()->getPropertyCSSValue(&csspropertyList[propertyIndex].m_name);
			if (fstyle)
			{
			}
		}
#endif

		int nrules = m_rules.size();
		for (int i = nrules-1; i >= 0; i--)
		{
			SingleSelectorRule* rule = m_rules[i];

#if 0
			if (pMatch->m_selector == NULL ||
				!cmpbstr(pMatch->m_selector->m_pseudoElement.c_str(), pElement->m_pseudoElementName.c_str()))

//				((pMatch->m_selector->m_pseudoElement.Length() == pElement->m_pseudoElementName.Length()) &&
//				(pMatch->m_selector->m_pseudoElement.Length()==0 || !wcscmp(pMatch->m_selector->m_pseudoElement, pElement->m_pseudoElementName))))
#endif
			{
				Variant value2 = rule->m_declaration->GetPropertyValue(pProperty);
				if (!value2.IsUndefined())	// Property is declared
				{
					if (value.IsUndefined()/*pFDecl == NULL*/)
					{
						value = value2;
						specificity = rule->GetSpecificity();
					}
					else
					{
						/*
						// Sort by importance
						if (pPropertyDecl->m_priority.length() && pFDecl->m_priority.length() == 0)
						{
							pFDecl = pPropertyDecl;
							specificity = pMatch->m_specificity;
						}
						// Sort by specificity of selector
						else
							*/

						uint rulespecifity = rule->GetSpecificity();
						if (rulespecifity > specificity)
						{
							value = value2;
							specificity = rulespecifity;
						}
							/*
						// Sort by order specified
						else
						{
							pFDecl = pPropertyDecl;
							specificity = pMatch->m_specificity;
						}
						*/
					}
				}
			}
		}
	}

#if 0
	CComQIPtr<ILDOMElement> element = pElement->m_pNode;

	CComQIPtr<ILCSSValue> fstyle;

	CComQIPtr<ILSMILAnimationTarget> overrideStyleElement = element;
	if (overrideStyleElement)
	{
		if (static_cast<CAnimationTarget*>(overrideStyleElement.p)->m_overrideStyle->m_decls.GetSize() > 0)
		{
			CComPtr<ILCSSValue> cssvalue;
			static_cast<CAnimationTarget*>(overrideStyleElement.p)->m_overrideStyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);

			if (cssvalue != NULL)
			{
				fstyle = cssvalue;
			}
		}
	}

	if (fstyle == NULL)
	{
		CArray<CDecl,CDecl&> decls;
		decls.SetSize(0, 20);

	// Try all the document's stylesheets
		CComQIPtr<ILStyleSheetList> styleSheets;
		documentStyle->get_styleSheets(&styleSheets);

		long count;
		styleSheets->get_length(&count);

		for (long i = 0; i < count; i++)
		{
			CComPtr<ILCSSStyleSheet> styleSheet;
			styleSheets->item(i, (ILStyleSheet**)&styleSheet);

			GetStyleSheetDecls(styleSheet, element, cssstyle->m_name, decls);
		}

		DWORD	fspecificity = 0;

		for (i = 0; i < decls.GetSize(); i++)
		{
			if (decls[i].specificity > fspecificity)
			{
				fstyle = decls[i].cssvalue;
				fspecificity = decls[i].specificity;
			}
		}

	// Try the inline style attribute
		if (fspecificity <= 10000)
		{
			CComQIPtr<ILCSSStyleDeclaration> inlinestyle;

			CComQIPtr<ILElementCSSInlineStyle> stylableElement;
			if (stylableElement = element)
			{
				stylableElement->get_style(&inlinestyle);
			}

			if (inlinestyle)
			{
				CComPtr<ILCSSValue> cssvalue;
				inlinestyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);
				if (cssvalue != NULL)
				{
					fstyle = cssvalue;
				}
			}
		}

		if (fspecificity == 0)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);
			if (!WCSCMP(tagName, L"font", m_isXML))
			{
				if (propertyIndex == CSSProperty_font_size)
				{
					BSTR bsize;
					element->getAttribute(L"size", &bsize);
					if (bsize)
					{
						CComObject<CSSPrimitiveValue>* pCSSValue;
						CComObject<CSSPrimitiveValue>::CreateInstance(&pCSSValue);
						pCSSValue->AddRef();
						pCSSValue->m_propertyIndex = propertyIndex;

						if (bsize[0] == L'-')
						{
							BSTR brel = &bsize[1];
							long lrel = str2int(brel);
							pCSSValue->setFloatValue(CSS_PERCENTAGE, 100-lrel*5);
						}
						else if (bsize[0] == L'+')
						{
							BSTR brel = &bsize[1];
							long lrel = str2int(brel);
							pCSSValue->setFloatValue(CSS_PERCENTAGE, 100+lrel*5);
						}
						else
						{
							long labs = str2int(bsize);
							pCSSValue->setFloatValue(CSS_PX, 10+labs*3);
						}

						SysFreeString(bsize);

						fstyle = pCSSValue;

						pCSSValue->Release();
					}
				}
				else if (propertyIndex == CSSProperty_color)
				{
					BSTR b;
					element->getAttribute(L"color", &b);
					if (b)
					{
						COLORREF clr = ConvertColor(_bstr_t(b, false));
						if (clr != -1)
						{
							CComObject<CSSPrimitiveValue>* pCSSValue = CreateCSSUnitRGBValue(propertyIndex, Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));
							fstyle = pCSSValue;
							pCSSValue->Release();
						}
					}
				}
			}
		}
	}
#endif

	if (!value.IsUndefined())
	{
	//	CSSValueType valueType = value->get_cssValueType();
	//	if (valueType == CSS_INHERIT)
		if (m_elementResolver->IsValueInherit(value))
		{
		// NOTE: Use the parent from the modified tree (after bindings etc.)
			ICSSElementResolver* parentElement = m_elementResolver->get_rparent();
			if (parentElement != nullptr)
			{
				if (pProperty)	// TODO, why??
				{
					return Value_Inherited;
				}
			}
		}
	}

	if (value.IsUndefined())
	{
// Try inherited value from parent element (it inherits the computed value (TODO, not always?))

		// NOTE: Use the parent from the modified tree (after bindings etc.)
		ICSSElementResolver* parentElement = m_elementResolver->get_rparent();
		if (parentElement != nullptr)
		{
			if (pProperty && m_elementResolver->IsInherited(pProperty))
			{
				return Value_Inherited;
			}
		}
	}

	if (value.IsUndefined())
	{
		// Set initial value
		return Value_Default;
	}

	*pvalue = value;
	return Value_Specified;
}

#if 0
// static
int ViewCSS::GetSpecifiedPropertyValue2(IDocumentStyle* documentStyle, CSSElementMatches* matches, Object* pPproperty, /*BSTR pseudoElt,*/ bool bIncludeOverride, CSSValue** value)
{
	CSSElementMatches* pElement = matches;//static_cast<CLCSSElementMatches*>(matches);
//	CSSProperty* cssstyle = &csspropertyList[propertyIndex];

//	CSSDecl* pFDecl = NULL;
	uint specificity = 0;
	Object* value = NULL;

	//CComQIPtr<ILSMILAnimationTarget> overrideStyleElement = pElement->m_pNode;
	//if (overrideStyleElement)
	if (bIncludeOverride)
	{
#if 0	// Had this
		if (pElement->m_pOverrideStyle->m_decls.GetSize() > 0)
		{
			CComPtr<ILCSSValue> cssvalue;
			pElement->m_pOverrideStyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);

			if (cssvalue != NULL)
			{
				fstyle = cssvalue;
			}
		}
#endif
	}

	if (value == NULL)	// ??
	{
		IElementCSSInlineStyle* svgStylable = dynamic_cast<IElementCSSInlineStyle*>(dynamic_cast<PElementBase*>(pElement->m_elementResolver)->m_pNode);
		if (svgStylable)
		{
			fstyle = svgStylable->get_style()->getPropertyCSSValue(&csspropertyList[propertyIndex].m_name);
			if (fstyle)
			{
			}
		}

#if 0	// TODO
		CComQIPtr<ILSVGStylable> svgStylable = pElement->m_pNode;
		if (svgStylable)
		{
			svgStylable->getPresentationAttribute(csstyleList[propertyIndex].m_name, &fstyle);
		}
#endif

		int nmatches = pElement->m_declMatches.GetSize();
		for (int i = nmatches-1; i >= 0; i--)
		{
			StyleDeclarationMatch* pMatch = pElement->m_declMatches[i];

#if 0
			if (pMatch->m_selector == NULL ||
				!cmpbstr(pMatch->m_selector->m_pseudoElement.c_str(), pElement->m_pseudoElementName.c_str()))

//				((pMatch->m_selector->m_pseudoElement.Length() == pElement->m_pseudoElementName.Length()) &&
//				(pMatch->m_selector->m_pseudoElement.Length()==0 || !wcscmp(pMatch->m_selector->m_pseudoElement, pElement->m_pseudoElementName))))
#endif
			{
				CSSDecl* pPropertyDecl = pMatch->m_style->FindDecl(propertyIndex);
				if (pPropertyDecl)	// Property is declared
				{
					if (fstyle == NULL/*pFDecl == NULL*/)
					{
						//pFDecl = pPropertyDecl;
					//	fstyle = NULL;//.Release();
						//ASSERT(0);
						fstyle = pPropertyDecl->m_pValue;
						/*
						IUnknown* unk;
						pPropertyDecl->m_pValue->getObject(&unk);
						fstyle = CComQIPtr<ILCSSValue, &IID_ILCSSValue>(unk);
						*/
					//	fstyle = pPropertyDecl->m_pValue;

						specificity = pMatch->GetSpecificity();
					}
					else
					{
						/*
						// Sort by importance
						if (pPropertyDecl->m_priority.length() && pFDecl->m_priority.length() == 0)
						{
							pFDecl = pPropertyDecl;
							specificity = pMatch->m_specificity;
						}
						// Sort by specificity of selector
						else
							*/
							if (pMatch->GetSpecificity() > specificity)
						{
						//	pFDecl = pPropertyDecl;

						//	fstyle = NULL;//.Release();
							fstyle = pPropertyDecl->m_pValue;
						//	ASSERT(0);
#if 0
							CComPtr<IUnknown> unk;
							pPropertyDecl->m_pValue->getObject(&unk);
							fstyle = CComQIPtr<ILCSSValue, &IID_ILCSSValue>(unk);
#endif
							specificity = pMatch->GetSpecificity();
						}
							/*
						// Sort by order specified
						else
						{
							pFDecl = pPropertyDecl;
							specificity = pMatch->m_specificity;
						}
						*/
					}
				}
			}
		}
	}

	//CComQIPtr<ILCSSValue> fstyle;
	
//	if (pFDecl)
//		pFDecl->m_pValue->getCSSValue(&fstyle);

#if 0
	CComQIPtr<ILDOMElement> element = pElement->m_pNode;

	CComQIPtr<ILCSSValue> fstyle;

	CComQIPtr<ILSMILAnimationTarget> overrideStyleElement = element;
	if (overrideStyleElement)
	{
		if (static_cast<CAnimationTarget*>(overrideStyleElement.p)->m_overrideStyle->m_decls.GetSize() > 0)
		{
			CComPtr<ILCSSValue> cssvalue;
			static_cast<CAnimationTarget*>(overrideStyleElement.p)->m_overrideStyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);

			if (cssvalue != NULL)
			{
				fstyle = cssvalue;
			}
		}
	}

	if (fstyle == NULL)
	{
		CArray<CDecl,CDecl&> decls;
		decls.SetSize(0, 20);

	// Try all the document's stylesheets
		CComQIPtr<ILStyleSheetList> styleSheets;
		documentStyle->get_styleSheets(&styleSheets);

		long count;
		styleSheets->get_length(&count);

		for (long i = 0; i < count; i++)
		{
			CComPtr<ILCSSStyleSheet> styleSheet;
			styleSheets->item(i, (ILStyleSheet**)&styleSheet);

			GetStyleSheetDecls(styleSheet, element, cssstyle->m_name, decls);
		}

		DWORD	fspecificity = 0;

		for (i = 0; i < decls.GetSize(); i++)
		{
			if (decls[i].specificity > fspecificity)
			{
				fstyle = decls[i].cssvalue;
				fspecificity = decls[i].specificity;
			}
		}

	// Try the inline style attribute
		if (fspecificity <= 10000)
		{
			CComQIPtr<ILCSSStyleDeclaration> inlinestyle;

			CComQIPtr<ILElementCSSInlineStyle> stylableElement;
			if (stylableElement = element)
			{
				stylableElement->get_style(&inlinestyle);
			}

			if (inlinestyle)
			{
				CComPtr<ILCSSValue> cssvalue;
				inlinestyle->getPropertyCSSValue(cssstyle->m_name, &cssvalue);
				if (cssvalue != NULL)
				{
					fstyle = cssvalue;
				}
			}
		}

		if (fspecificity == 0)
		{
			BSTR btagName;
			element->get_tagName(&btagName);
			_bstr_t tagName = _bstr_t(btagName, false);
			if (!WCSCMP(tagName, L"font", m_isXML))
			{
				if (propertyIndex == CSSProperty_font_size)
				{
					BSTR bsize;
					element->getAttribute(L"size", &bsize);
					if (bsize)
					{
						CComObject<CSSPrimitiveValue>* pCSSValue;
						CComObject<CSSPrimitiveValue>::CreateInstance(&pCSSValue);
						pCSSValue->AddRef();
						pCSSValue->m_propertyIndex = propertyIndex;

						if (bsize[0] == L'-')
						{
							BSTR brel = &bsize[1];
							long lrel = str2int(brel);
							pCSSValue->setFloatValue(CSS_PERCENTAGE, 100-lrel*5);
						}
						else if (bsize[0] == L'+')
						{
							BSTR brel = &bsize[1];
							long lrel = str2int(brel);
							pCSSValue->setFloatValue(CSS_PERCENTAGE, 100+lrel*5);
						}
						else
						{
							long labs = str2int(bsize);
							pCSSValue->setFloatValue(CSS_PX, 10+labs*3);
						}

						SysFreeString(bsize);

						fstyle = pCSSValue;

						pCSSValue->Release();
					}
				}
				else if (propertyIndex == CSSProperty_color)
				{
					BSTR b;
					element->getAttribute(L"color", &b);
					if (b)
					{
						COLORREF clr = ConvertColor(_bstr_t(b, false));
						if (clr != -1)
						{
							CComObject<CSSPrimitiveValue>* pCSSValue = CreateCSSUnitRGBValue(propertyIndex, Gdiplus::Color(GetRValue(clr), GetGValue(clr), GetBValue(clr)));
							fstyle = pCSSValue;
							pCSSValue->Release();
						}
					}
				}
			}
		}
	}
#endif

	if (fstyle)
	{
		CSSValueType valueType = fstyle->get_cssValueType();
		if (valueType == CSS_INHERIT)
		{
		//	fstyle.Release();

		// NOTE: Use the parent from the modified tree (after bindings etc.)
			ICSSElementResolver* parentElement = pElement->m_elementResolver->get_rparent();
			if (parentElement != NULL)
			{
				if (cssstyle)
				{
					return 1;
				}
			}
		}
	}

	if (fstyle == NULL)
	{
// Try inherited value from parent element (it inherits the computed value (TODO, not always?))

		// NOTE: Use the parent from the modified tree (after bindings etc.)
		ICSSElementResolver* parentElement = pElement->m_elementResolver->get_rparent();
		if (parentElement != NULL)
		{
			if (cssstyle && cssstyle->m_bInherited)
			{
				return 1;
			}
		}
	}

	if (fstyle == NULL)
	{
		// Set initial value
		return 2;
	}

	(*value = fstyle);
//	if (*value) (*value)->AddRef();
	return 0;
}
#endif

#if 0
//////////////////////////////////////////////////////////////////////////////
// CLViewCSSImplImpl

STDMETHODIMP CLViewCSSImplImpl::getComputedStyle(ILDOMElement *elt, BSTR pseudoElt, ILCSSStyleDeclaration **pVal)
{
	ASSERT(0);
#if 0
	ASSERT(pVal != NULL);
	ASSERT(elt != NULL);
	if (pVal == NULL) return E_POINTER;
	if (elt == NULL) return E_INVALIDARG;

	*pVal = NULL;

	CPElement* pElement = NULL;
	for (int i = 0; i < CComQIPtr<CLDOMElementImplImpl>(elt)->m_pNodes.GetSize(); i++)
	{
		if (static_cast<ILViewCSS*>(CComQIPtr<CLDOMElementImplImpl>(elt)->m_pNodes[i]->m_pWindow) == this)
		{
			pElement = (CPElement*)CComQIPtr<CLDOMElementImplImpl>(elt)->m_pNodes[i];
			break;
		}
	}

	ASSERT(pElement);
	if (pElement)
	{
		*pVal = pElement->m_pComputedStyle;
		(*pVal)->AddRef();
	}
#endif
	return S_OK;
}

STDMETHODIMP CLViewCSSImplImpl::getOverrideStyle(/*[in]*/ ILDOMElement* elt, /*[in]*/ BSTR pseudoElt, /*[out, retval]*/ ILCSSStyleDeclaration* *pVal)
{
	return S_OK;
}

STDMETHODIMP CLViewCSSImplImpl::GetPresentation(/*[out, retval]*/ ILPresentation* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_pView;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

}	// Web
}	// System
