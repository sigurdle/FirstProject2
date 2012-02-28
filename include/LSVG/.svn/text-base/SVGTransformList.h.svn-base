#ifndef w3c_SVGTransformList_h
#define w3c_SVGTransformList_h

namespace System
{
namespace Web
{

/*
interface SVGTransformListListener
{
public:
	virtual void OnTransformListChange(SVGTransformList* pTransformList) = 0;
};
*/

class SVGTransformListData : public Object
{
public:
	vector<SVGTransform*, __gc_allocator> m_items;
};

class SVGEXT SVGTransformList : public Object, public ISVGTransformList
{
public:
	CTOR SVGTransformList();
	CTOR SVGTransformList(SVGTransformListData* p);
	~SVGTransformList();

	unsigned int get_numberOfItems() const;
	void clear();
	SVGTransform* appendItem(SVGTransform* newItem);
	SVGTransform* removeItem(unsigned int index);
	SVGTransform* replaceItem(SVGTransform* newItem, unsigned int index);
	SVGTransform* insertItemBefore(SVGTransform* newItem, unsigned int index);
	SVGTransform* getItem(unsigned int index) const;
	SVGTransform* initialize(SVGTransform* newItem);
	SVGTransform* createSVGTransformFromMatrix(const SVGMatrix* matrix);
	SVGTransform* consolidate();

//	void consolidate(gmMatrix3* mat) const;

	void RemoveAll();

	void ParseTransform(StringIn str);
	String StringFromTransformList() const;

	void setStringValue(StringIn str);

	String getStringValue();
//	SVGTransformList& operator = (const SVGTransformList& value);
//	SVGTransformList& operator += (const SVGTransformList& value);
	void InterpolateValue(const SVGTransformList& a, const SVGTransformList& b, double t);

	void OnChanged();

	/*
	virtual void OnChanged(CSingleObject* pTransform)
	{
		ChangedTransform();
	}
	*/

//	void ChangedTransform();

	gm::matrix3d consolidateToMatrix2() const;
	gm::Matrix3d* consolidateToMatrix();

public:

	friend SVGEXT String GetAsString(SVGTransformList* p);
	friend SVGEXT void SetAsString(SVGTransformList* p, StringIn str);

//	SVGTransformListListener* m_pListener;

	SVGTransformListData* m_p;

	Object* m_changedArg;
	void (*m_changed)(Object* arg);

protected:

	void readOnly();
};

class SVGEXT SVGTransformListMutable : public SVGTransformList
{
public:
	CTOR SVGTransformListMutable();
	CTOR SVGTransformListMutable(SVGTransformListData* p);

	void clear();
	SVGTransform* appendItem(SVGTransform* newItem);
	SVGTransform* removeItem(unsigned int index);
	SVGTransform* replaceItem(SVGTransform* newItem, unsigned int index);
	SVGTransform* insertItemBefore(SVGTransform* newItem, unsigned int index);
	SVGTransform* initialize(SVGTransform* newItem);
	SVGTransform* createSVGTransformFromMatrix(const SVGMatrix* matrix);
	SVGTransform* consolidate();
};

}	// w3c
}

#endif // w3c_SVGTransformList_h
