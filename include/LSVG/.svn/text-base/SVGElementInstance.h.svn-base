#ifndef __SVGELEMENTINSTANCE_H_
#define __SVGELEMENTINSTANCE_H_

//#include "resource.h"       // main symbols

namespace System
{
namespace Web
{

class SVGElement;
class SVGUseElement;
class SVGElementInstanceList;

class PSVGElement;

class SVGEXT SVGElementInstance : 
	public EventTarget
{
public:
	CTOR SVGElementInstance();
	~SVGElementInstance();

	SVGElement* get_correspondingElement();
	SVGUseElement* get_correspondingUseElement();
	SVGElementInstance* get_parentNode();
	SVGElementInstanceList* get_childNodes();
	SVGElementInstance* get_firstChild();
	SVGElementInstance* get_lastChild();
	SVGElementInstance* get_previousSibling();
	SVGElementInstance* get_nextSibling();

public:

	void AppendInstance(SVGElementInstance* pInstance);
	void BuildTree(SVGUseElement* correspondingUseElement, SVGElement* correspondingElement);

	SVGElement* m_correspondingElement;
	SVGUseElement* m_correspondingUseElement;

	SVGElementInstanceList* m_childNodes;
	SVGElementInstance* m_parentNode;
	SVGElementInstance* m_nextSibling;
	SVGElementInstance* m_previousSibling;
	SVGElementInstance* m_firstChild;
	SVGElementInstance* m_lastChild;

	vector<PSVGElement*> m_pNodes;
};

}	// w3c
}

#endif // __SVGELEMENTINSTANCE_H_
