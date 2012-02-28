#ifndef Web_SVGPointList_h
#define Web_SVGPointList_h

namespace System
{
namespace Web
{

//class SVGPointList;

/*
class SVGPointListListener
{
public:
	virtual void OnPointListChange(SVGPointList* pPointList) = 0;
};
*/

class WEBEXT SVGPointListData : public Object//, public ISVGPointListener
{
private:

	CTOR SVGPointListData(const SVGPointListData& other)
	{
	}

public:

	CTOR SVGPointListData();
//	CTOR SVGPointListData(/*ISVGPointListener* owner,*/ const vector<SVGPoint*, __gc_allocator>& items);
	CTOR SVGPointListData(ISVGPointListener* owner, StringIn str);

	String getStringValue() const;
	void setStringValue(StringIn str);

	void ParsePointList(ISVGPointListener* owner, StringIn str);

	void RemoveAll();

	gm::RectD CalculateBoundingBox() const;
	gm::RectD CalculateBoundingBox(const gm::matrix3d& transform) const;

//	virtual void OnPointChanged(SVGPoint* point, double oldx, double oldy);
//	virtual bool OnRemoveItem(SVGPoint* point);

	vector<SVGPoint*> m_items;

//	ISVGPointListener* m_owner;

//	unsigned int m_refcount;
};

class WEBEXT SVGPointList : 
	public Object,
	public ISVGPointList,
	public ISVGPointListener
{
public:
	CTOR SVGPointList();
	CTOR SVGPointList(SVGPointListData* data);
	~SVGPointList();

//	int m_bLockUpdate;
//	int m_nChanges;

	//SVGPointListListener* m_pListener;

	void ParsePointList(StringIn s);
	String StringFromPointList() const;

	void RemoveAll();
	void RemoveItem(SVGPoint* pPoint);

	friend WEBEXT String GetAsString(SVGPointList* pointlist);

//	System::StringW* getStringValue() const;
	void setStringValue(StringIn str);
	void InterpolateValue(const SVGPointList& a, const SVGPointList& b, double t);

#if 0
	void DrawToPath(LDraw::GraphicsPathF* pPath, bool bClose) const;
#endif
	ID2D1PathGeometry* GetD2DGeometry();
	Gui::PolygonGeometry* GetGeometry();

	gm::RectD CalculateBoundingBox() const;
	gm::RectD CalculateBoundingBox(const SVGMatrix* transform) const;
	gm::RectD CalculateBoundingBox(const gm::matrix3d& transform) const;

	virtual bool OnRemoveItem(SVGPoint* pPoint);
	virtual void OnPointChanged(SVGPoint* pPoint, double oldx, double oldy);

	unsigned int get_numberOfItems() const;
	void clear();
	SVGPoint* appendItem(SVGPoint* newItem);
	SVGPoint* removeItem(unsigned int index);
	SVGPoint* replaceItem(SVGPoint* newItem, unsigned int index);
	SVGPoint* insertItemBefore(SVGPoint* newItem, unsigned int index);
	SVGPoint* getItem(unsigned int index) const;
	SVGPoint* initialize(SVGPoint* newItem);

// Extensions
//	void UnlockUpdate();
//	void LockUpdate();

	String OldToString();

	SVGPointListData* m_p;

	Object* m_changedArg;
	void (*m_changed)(Object* arg);

//	bool m_readonly;

protected:

	void OnChanged();

	void readonly();

	SVGPoint* m_pPoint;
	double m_oldx;
	double m_oldy;
	unsigned int m_index;
	enum
	{
		Cleared,
		InsertedPoint,
		RemovedPoint,
		ChangedPointXY,
	}
	m_change;
};

class WEBEXT SVGPointListMutable : public SVGPointList
{
public:
	CTOR SVGPointListMutable(SVGPointListData* data) : SVGPointList(data)
	{
	}

	CTOR SVGPointListMutable(StringIn str);

	void clear();
	SVGPoint* appendItem(SVGPoint* newItem);
	SVGPoint* removeItem(unsigned int index);
	SVGPoint* replaceItem(SVGPoint* newItem, unsigned int index);
	SVGPoint* insertItemBefore(SVGPoint* newItem, unsigned int index);
	SVGPoint* initialize(SVGPoint* newItem);
};

}	// Web
}

#endif // Web_SVGPointList_h
