#ifndef Web_SVGLengthList_h
#define Web_SVGLengthList_h

namespace System
{
namespace Web
{

class SVGEXT SVGLengthListValueHandler : public IValueHandler
{
public:
	virtual Object* Create() const;
	virtual void ParseString(Object* value, StringIn str) const;
	virtual void InterpolateValue(Object* dest, Object* a, Object* b, double t);

	static SVGLengthListValueHandler s_svgLengthListValueHandler;

	static IValueHandler* GetValueHandler()
	{
		return &s_svgLengthListValueHandler;
	}
};

class SVGLengthListData : public Object
{
public:
	vector<SVGLength*> m_items;
	//ISVGLengthListener* m_owner;
};

class SVGEXT SVGLengthList : public CSingleObject, public ISVGLengthList, public ISVGLengthListener
{
public:
	CTOR SVGLengthList();
	CTOR SVGLengthList(SVGLengthListData* p);
	~SVGLengthList();

	unsigned int get_numberOfItems() const;
	void clear();
	SVGLength* appendItem(SVGLength* newItem);
	SVGLength* removeItem(unsigned int index);
	SVGLength* replaceItem(SVGLength* newItem, unsigned int index);
	SVGLength* insertItemBefore(SVGLength* newItem, unsigned int index);
	SVGLength* getItem(uint index) const;
	SVGLength* initialize(SVGLength* newItem);

	String getStringValue();
	void setStringValue(StringIn str);
//	void operator = (const SVGLengthList& value);
//	void operator += (const SVGLengthList& value);
	void InterpolateValue(const SVGLengthList& a, const SVGLengthList& b, double t);

	SVGLengthListData* m_p;

protected:

	void RemoveAll();

	// ISVGLengthListener
	virtual void OnChanged(SVGLength* pLength);
	virtual bool OnRemoveItem(SVGLength* pLength);
};

String GetAsString(SVGLengthList* p);

}	// Web
}	// System

#endif // Web_SVGLengthList_h
