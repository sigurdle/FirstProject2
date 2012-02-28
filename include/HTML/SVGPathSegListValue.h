#ifndef __SVGPathSegListValue_h__
#define __SVGPathSegListValue_h__

#include "SVGPathSegList.h"

namespace System
{
namespace Web
{

class HTMLEXT SVGPathSegListValue :
	public ISVGPathSegListListener,
	public CSingleObject
{
public:

	CTOR SVGPathSegListValue();
	~SVGPathSegListValue();

	SVGPathSegListValue& operator = (const SVGPathSegListValue& value);
	SVGPathSegListValue& operator += (const SVGPathSegListValue& value);
	void setStringValue(StringIn str);
	String getStringValue();
	void InterpolateValue(SVGPathSegListValue* a, SVGPathSegListValue* b, double t);

	SVGPathSegList* get_pathSegList();
	SVGPathSegList* get_normalizedPathSegList();

protected:

	virtual void OnPathSegListChange(SVGPathSegList* pSegList);

public:

	SVGPathSegList* m_seglist;
	SVGPathSegList* m_normalizedseglist;
};

}	// Web
}

#endif // __SVGPathSegListValue_h__
