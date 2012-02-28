#ifndef w3c_SVGPathSeg_h
#define w3c_SVGPathSeg_h

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSeg : public Object
{
public:
	CTOR SVGPathSeg()
	{
		m_pSegList = NULL;
	}

	virtual SVGPathSegType get_pathSegType() const = 0;
	virtual String get_pathSegTypeAsLetter() const = 0;

public:

	SVGPathSegList* m_pSegList;
};

}	// Web
}

#endif // w3c_SVGPathSeg_h
