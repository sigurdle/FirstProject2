#include "stdafx.h"
#include "LXML2.h"
#include "SVGPointList.h"

#include "SVGPoint.h"
#include "SVGMatrix.h"

namespace System
{
namespace Web
{

SVGPointListData::SVGPointListData()
{
//	m_refcount = 0;
}

#if 0
SVGPointListData::SVGPointListData(/*ISVGPointListener* owner,*/ const vector<SVGPoint*, __gc_allocator>& items)
{
//	m_owner = owner;
	m_items = items;
//	m_refcount = 0;
}
#endif

SVGPointListData::SVGPointListData(ISVGPointListener* owner, StringIn str)
{
	//m_owner = owner;
	ParsePointList(owner, str);
}

void SVGPointListData::setStringValue(StringIn str)
{
	ASSERT(0);
	/*
	RemoveAll();
	ParsePointList(str);
	*/
}

/*
void SVGPointListData::OnPointChanged(SVGPoint* point, double oldx, double oldy)
{
	ASSERT(0);
}

bool SVGPointListData::OnRemoveItem(SVGPoint* point)
{
	ASSERT(0);
	return false;
}
*/

void SVGPointListData::ParsePointList(ISVGPointListener* owner, StringIn s)
{
	CStringw cstr(s);

	const WCHAR* p = cstr.c_str();

	while (iswspace(*p)) p++;

	while (*p)
	{
		double x = getfnumber(&p);
		if (p == NULL)
		{
			break;
		}

		while (iswspace(*p)) p++;

		if (*p == L',') p++;
		while (iswspace(*p)) p++;

		double y = getfnumber(&p);
		if (p == NULL)
		{
			break;
		}

		while (iswspace(*p)) p++;

		if (*p == L',') p++;
		while (iswspace(*p)) p++;

		SVGPoint* pPoint = new SVGPoint;
		if (pPoint)
		{
		//	pPoint->AddRef();

			pPoint->m_x = x;
			pPoint->m_y = y;

			pPoint->m_owner = owner;
		//	pPoint->m_pointList = this;
			m_items.Add(pPoint);
		}
		else
			break;
	}
}

///

SVGPointList::SVGPointList()
{
//	m_bLockUpdate = 0;
//	m_nChanges = 0;

	//m_pListener = NULL;
}

SVGPointList::SVGPointList(SVGPointListData* data)
{
	m_p = data;
	/*
	if (m_p)
	{
		++m_p->m_refcount;
	}
	*/
}

SVGPointList::~SVGPointList()
{
	//ASSERT(m_pListener == NULL);
}

WEBEXT String GetAsString(SVGPointList* pointlist)
{
	return pointlist->StringFromPointList();
}

void SVGPointList::readonly()
{
	raise(Exception("SVGPointList is readOnly"));
}

unsigned int SVGPointList::get_numberOfItems() const
{
	return m_p->m_items.GetSize();
}

SVGPoint* SVGPointList::getItem(unsigned int index) const
{
	if (index < m_p->m_items.GetSize())
	{
		return m_p->m_items[index];
	}
	else
		raise(ArgumentOutOfRangeException());
}

void SVGPointList::clear()
{
	readonly();
}

void SVGPointListMutable::clear()
{
	if (m_p->m_items.GetSize() > 0)
	{
		/*
		if (m_p->m_refcount > 1)
		{
			--m_p->m_refcount;
			m_p = new SVGPointListData(this, m_p->m_items);
			++m_p->m_refcount;
		}
		*/

		m_p->RemoveAll();

		OnChanged();
		/*
		if (m_pListener)
		{
			m_pListener->OnChanged(this);
		}
		*/
	}
}

SVGPoint* SVGPointList::initialize(SVGPoint* newItem)
{
	readonly();
	return NULL;
}

SVGPoint* SVGPointListMutable::initialize(SVGPoint* newItem)
{
	/*
	if (m_p->m_refcount > 1)
	{
		--m_p->m_refcount;
		m_p = new SVGPointListData(this, m_p->m_items);
		++m_p->m_refcount;
	}
	*/

	ASSERT(0);
	// TODO: Add your implementation code here

	return NULL;
}

SVGPointListMutable::SVGPointListMutable(StringIn str)
{
	m_p = new SVGPointListData(this, str);
//	++m_p->m_refcount;
}

SVGPoint* SVGPointList::insertItemBefore(SVGPoint *pNewItem, unsigned int index)
{
	readonly();
	return NULL;
}

SVGPoint* SVGPointListMutable::insertItemBefore(SVGPoint* newItem, unsigned int index)
{
	if (newItem == NULL) throw std::exception("null pointer");

	/*
	if (m_p->m_refcount > 1)
	{
		--m_p->m_refcount;
		m_p = new SVGPointListData(this, m_p->m_items);
		++m_p->m_refcount;
	}
	*/

	ASSERT(newItem->m_owner != this);

	if (newItem->m_owner)
	{
	// This should also clear the listener if successful
		if (!newItem->m_owner->OnRemoveItem(newItem))
		{
			throw std::exception("Couldn't insert this point");
		}
		ASSERT(newItem->m_owner == NULL);
	}

	m_change = InsertedPoint;
	m_pPoint = newItem;
	m_index = index;

	m_p->m_items.InsertAt(index, newItem);
//	pNewItem->m_pointList = this;
	newItem->m_owner = this;

	OnChanged();
/*	if (m_pListener)
	{
		m_pListener->OnChanged(this);
	}
*/
	return newItem;
}

SVGPoint* SVGPointList::appendItem(SVGPoint *pNewItem)
{
	readonly();
	return NULL;
}

SVGPoint* SVGPointListMutable::appendItem(SVGPoint *newItem)
{
	if (newItem == NULL) throw std::exception("null pointer");

	/*
	if (m_p->m_refcount > 1)
	{
		--m_p->m_refcount;
		m_p = new SVGPointListData(this, m_p->m_items);
		++m_p->m_refcount;
	}
	*/

	if (newItem->m_owner)
	{
	// This should also clear the listener if successful
		if (!newItem->m_owner->OnRemoveItem(newItem))
		{
			throw std::exception("Could not append point, try to make a copy of it first");
		}
		ASSERT(newItem->m_owner == NULL);
	}

	m_p->m_items.push_back(newItem);
	newItem->m_owner = this;

	OnChanged();
	/*
	if (m_pListener)
		m_pListener->OnChanged(this);
		*/

	return newItem;
}

void SVGPointList::RemoveItem(SVGPoint* pPoint)
{
	/*
	if (m_p->m_refcount > 1)
	{
		--m_p->m_refcount;
		m_p = new SVGPointListData(this, m_p->m_items);
		++m_p->m_refcount;
	}
	*/

	for (int i = 0; i < m_p->m_items.GetSize(); i++)
	{
		if (m_p->m_items[i] == pPoint)
		{
			m_change = RemovedPoint;
			m_index = i;
			m_oldx = pPoint->get_x();
			m_oldy = pPoint->get_y();

		//	pPoint->m_pointList = NULL;
			pPoint->m_owner = NULL;
		//	pPoint->Release();
			m_p->m_items.RemoveAt(i);

			OnChanged();
		/*
		if (m_pListener)
				m_pListener->OnChanged(this);
*/
			return;
		}
	}

	ASSERT(0);
}

SVGPoint* SVGPointList::removeItem(unsigned int index)
{
	readonly();
	return NULL;
}

SVGPoint* SVGPointListMutable::removeItem(unsigned int index)
{
	SVGPoint* pReturn;

	if (index >= 0 && index < m_p->m_items.GetSize())
	{
		pReturn = m_p->m_items[index];
	//	m_items[index]->m_pointList = NULL;
		m_p->m_items[index]->m_owner = NULL;
		m_p->m_items.RemoveAt(index);

		OnChanged();
	/*	if (m_pListener)
		{
			m_pListener->OnChanged(this);
		}
		*/
	}
	else
	{
		ASSERT(0);
		pReturn = NULL;
	}

	return pReturn;
}

SVGPoint* SVGPointList::replaceItem(SVGPoint *newItem, unsigned int index)
{
	readonly();
	return NULL;
}

SVGPoint* SVGPointListMutable::replaceItem(SVGPoint *newItem, unsigned int index)
{
	ASSERT(0);
	return NULL;
}

/*
void SVGPointList::LockUpdate()
{
	m_bLockUpdate++;
}

void SVGPointList::UnlockUpdate()
{
	m_bLockUpdate--;
	ASSERT(m_bLockUpdate >= 0);
	if (m_bLockUpdate == 0)
	{
		if (m_nChanges > 0)
		{
			m_nChanges = 0;
			if (m_pListener)
			{
				m_pListener->OnChanged(this);
			}
		}
	}
}
*/

////////////

#if 0
void SVGPointList::DrawToPath(LDraw::GraphicsPathF* pPath, bool bClose) const
{
//	pPath->StartFigure();
	pPath->AddMove((float)m_p->m_items[0]->m_x, (float)m_p->m_items[0]->m_y);

	for (int i = 1; i < m_p->m_items.GetSize(); i++)
	{
		/*
		pPath->AddLine(
			(float)m_items[i-1]->m_x, (float)m_items[i-1]->m_y,
			(float)m_items[i]->m_x, (float)m_items[i]->m_y);
			*/
		pPath->AddLine((float)m_p->m_items[i]->m_x, (float)m_p->m_items[i]->m_y);
	}

	if (bClose)
	{
		pPath->CloseFigure();
	}
}
#endif
///////////

Gui::PolygonGeometry* SVGPointList::GetGeometry()
{
	Gui::PolygonGeometry* geometry = new Gui::PolygonGeometry;

	for (uint i = 0; i < m_p->m_items.size(); ++i)
	{
		geometry->m_points.Add(gm::PointF(m_p->m_items[i]->get_x(), m_p->m_items[i]->get_y()));
	}

	return geometry;
}

ID2D1PathGeometry* SVGPointList::GetD2DGeometry()
{
	ID2D1PathGeometry* geometry;
	Graphics::Direct10::get_D2DFactory()->CreatePathGeometry(&geometry);

	ID2D1GeometrySink* sink;
	geometry->Open(&sink);

	sink->BeginFigure(D2D1::Point2F(m_p->m_items[0]->get_x(), m_p->m_items[0]->get_y()), D2D1_FIGURE_BEGIN_FILLED);

	for (int i = 1; i < m_p->m_items.size(); i++)
	{
		sink->AddLine(D2D1::Point2F(m_p->m_items[i]->get_x(), m_p->m_items[i]->get_y()));
	}

	sink->EndFigure(D2D1_FIGURE_END_CLOSED);

	sink->Close();
	sink->Release();

	return geometry;
}

void SVGPointList::ParsePointList(StringIn s)
{
	ASSERT(0);
#if 0

//	RemoveAll();

	const OLECHAR* p = s.c_str();

	while (iswspace(*p)) p++;

	while (*p)
	{
		double x = getfnumber(&p);
		if (p == NULL)
		{
			break;
		}

		while (iswspace(*p)) p++;

		if (*p == L',') p++;
		while (iswspace(*p)) p++;

		double y = getfnumber(&p);
		if (p == NULL)
		{
			break;
		}

		while (iswspace(*p)) p++;

		if (*p == L',') p++;
		while (iswspace(*p)) p++;

		SVGPoint* pPoint = new SVGPoint;
		if (pPoint)
		{
		//	pPoint->AddRef();

			pPoint->m_x = x;
			pPoint->m_y = y;

			pPoint->m_pListener = this;
			pPoint->m_pointList = this;
			m_items.Add(pPoint);
		}
		else
			break;
	}
#endif
}

//////////////

String SVGPointList::OldToString()
{
	IO::StringWriter stream;

	unsigned int numberOfItems = m_p->m_items.GetSize();

	if (m_change == Cleared)
	{
		ASSERT(0);	// TODO
	}
	else if (m_change == InsertedPoint)
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			if (m_p->m_items[i] != m_pPoint)
			{
				if (i > 0) stream << ",";

				stream << m_p->m_items[i]->get_x();
				stream << " ";
				stream << m_p->m_items[i]->get_y();
			}
		}
	}
	else if (m_change == RemovedPoint)
	{
		for (int i = 0; i < numberOfItems; )
		{
			if (m_p->m_items[i] == m_pPoint)
			{
				if (i > 0) stream << ",";

				stream << m_oldx;
				stream << " ";
				stream << m_oldy;
			}
			else
			{
				if (i > 0) stream << ",";

				stream << m_p->m_items[i]->get_x();
				stream << " ";
				stream << m_p->m_items[i]->get_y();

				i++;
			}
		}
	}
	else if (m_change == ChangedPointXY)
	{
		for (int i = 0; i < numberOfItems; i++)
		{
			if (i == m_index)
			{
				if (i > 0) stream << ",";

				stream << m_oldx;
				stream << " ";
				stream << m_oldy;
			}
			else
			{
				if (i > 0) stream << ",";

				stream << m_p->m_items[i]->get_x();
				stream << " ";
				stream << m_p->m_items[i]->get_y();
			}
		}
	}

	return stream.str();
}

String SVGPointList::StringFromPointList() const
{
	IO::StringWriter str;

	size_t numberOfItems = m_p->m_items.GetSize();

//	WCHAR str2[128];

	for (size_t i = 0; i < numberOfItems; ++i)
	{
		if (i > 0)
			str << " ";

		if (m_p->m_items[i]->m_y < 0)
		{
			str << m_p->m_items[i]->m_x << m_p->m_items[i]->m_y;
		}
		else
		{
			str << m_p->m_items[i]->m_x << " " << m_p->m_items[i]->m_y;
		}

#if 0
		if (i > 0)
			str += OLESTR(" ");

		if (m_items[i]->m_y < 0)
		{
			swprintf(str2, OLESTR("%g%g"), m_items[i]->m_x, m_items[i]->m_y);
		}
		else
		{
			swprintf(str2, OLESTR("%g %g"), m_items[i]->m_x, m_items[i]->m_y);
		}

		str += str2;
#endif
	}

	return str.str();
}

// virtual
bool SVGPointList::OnRemoveItem(SVGPoint* pPoint)
{
	RemoveItem(pPoint);
	return true;
}

// virtual
void SVGPointList::OnPointChanged(SVGPoint* pPoint, double oldx, double oldy)
{
	m_oldx = oldx;
	m_oldy = oldy;
	m_change = ChangedPointXY;
	m_pPoint = pPoint;

//	if (m_bLockUpdate == 0)
	{
		OnChanged();
		/*
		if (m_pListener)
		{
			m_pListener->OnChanged(this);
		}
		*/
	}
	/*
	else
	{
		m_nChanges++;
	}
	*/
}

///////////

void SVGPointListData::RemoveAll()
{
	for (int i = 0; i < m_items.GetSize(); i++)
	{
	//	m_items[i]->m_pointList = NULL;
		m_items[i]->m_owner = NULL;
//		m_items[i]->Release();
	}

	m_items.RemoveAll();
}

void SVGPointList::OnChanged()
{
	ASSERT(m_changed);
	m_changed(m_changedArg);
}

///////////

void SVGPointList::setStringValue(StringIn str)
{
	m_p->RemoveAll();
	m_p->ParsePointList(this, str);
}

/*
StringW* SVGPointList::getStringValue()
{
	return StringFromPointList();
}
*/

/*
SVGPointList& SVGPointList::operator = (const SVGPointList& value)
{
	RemoveAll();	// hm..

	for (int i = 0; i < value.m_items.GetSize(); i++)
	{
		SVGPoint* pPoint = new SVGPoint;
		if (pPoint)
		{
		//	pPoint->AddRef();

			pPoint->m_x = value.m_items[i]->m_x;
			pPoint->m_y = value.m_items[i]->m_y;

			pPoint->m_pListener = this;
			m_items.Add(pPoint);		
		}
	}

	return *this;
}

SVGPointList& SVGPointList::operator += (const SVGPointList& value)
{
	ASSERT(0);
	return *this;
}
*/

void SVGPointList::InterpolateValue(const SVGPointList& a, const SVGPointList& b, double t)
{
	ASSERT(0);
#if 0

	RemoveAll();	// hm..

	if (a.m_items.GetSize() == b.m_items.GetSize())
	{
		int numberOfItems = a.m_items.GetSize();

		for (int i = 0; i < numberOfItems; i++)
		{
			SVGPoint* pPoint = new SVGPoint;
			if (pPoint)
			{
			//	pPoint->AddRef();

				pPoint->m_x = a.m_items[i]->m_x + (b.m_items[i]->m_x - a.m_items[i]->m_x)*t;
				pPoint->m_y = a.m_items[i]->m_y + (b.m_items[i]->m_y - a.m_items[i]->m_y)*t;

				pPoint->m_pListener = this;
				m_p->m_items.Add(pPoint);		
			}
			else
				break;
		}
	}
	else
		TRACE("SVGPointList::InterpolateValue() different number of points, can't interpolate\n");
#endif
}

/*
LDraw::RectD SVGPointList::CalculateBoundingBox(const gmMatrix3* pMat3)
{
	int numberOfItems = m_items.GetSize();

	if (numberOfItems > 0)
	{
		double minx;// = m_items[0]->m_x;
		double miny;// = m_items[0]->m_y;

		if (pMat3)
		{
			vector2d v2 = pMat3->transform(vector2d(m_items[0]->m_x, m_items[0]->m_y));
			minx = v2[0];
			miny = v2[1];
		}
		else
		{
			minx = m_items[0]->m_x;
			miny = m_items[0]->m_y;
		}

		double maxx = minx;
		double maxy = miny;

		if (pMat3)
		{
			for (int i = 1; i < numberOfItems; i++)
			{
				SVGPoint* pPoint = m_items[i];

				vector2d v2 = pMat3->transform(vector2d(m_items[i]->m_x, m_items[i]->m_y));

				if (v2[0] < minx) minx = v2[0];
				else if (v2[0] > maxx) maxx = v2[0];

				if (v2[1] < miny) miny = v2[1];
				else if (v2[1] > maxy) maxy = v2[1];
			}
		}
		else
		{
			for (int i = 1; i < numberOfItems; i++)
			{
				SVGPoint* pPoint = m_items[i];

				if (pPoint->m_x < minx) minx = pPoint->m_x;
				else if (pPoint->m_x > maxx) maxx = pPoint->m_x;

				if (pPoint->m_y < miny) miny = pPoint->m_y;
				else if (pPoint->m_y > maxy) maxy = pPoint->m_y;
			}
		}

		return LDraw::RectD(minx, miny, maxx-minx, maxy-miny);
	}
	else
	{
		return LDraw::RectD(0, 0, 0, 0);
		//return RectD(9999999, 9999999, -9999999, -9999999);
	}
}
*/

gm::RectD SVGPointList::CalculateBoundingBox(const SVGMatrix* transform) const
{
	if (transform)
		return m_p->CalculateBoundingBox(transform->GetM());
	else
		return m_p->CalculateBoundingBox();
}

gm::RectD SVGPointList::CalculateBoundingBox() const
{
	return m_p->CalculateBoundingBox();
}

gm::RectD SVGPointListData::CalculateBoundingBox() const
{
	size_t numberOfItems = m_items.GetSize();

	if (numberOfItems > 0)
	{
		double minx;// = m_items[0]->m_x;
		double miny;// = m_items[0]->m_y;

		minx = m_items[0]->m_x;
		miny = m_items[0]->m_y;

		double maxx = minx;
		double maxy = miny;

		for (size_t i = 1; i < numberOfItems; ++i)
		{
			SVGPoint* pPoint = m_items[i];

			if (pPoint->m_x < minx) minx = pPoint->m_x;
			else if (pPoint->m_x > maxx) maxx = pPoint->m_x;

			if (pPoint->m_y < miny) miny = pPoint->m_y;
			else if (pPoint->m_y > maxy) maxy = pPoint->m_y;
		}

		return gm::RectD(minx, miny, maxx-minx, maxy-miny);
	}
	else
	{
		return gm::RectD(0, 0, 0, 0);
		//return RectD(9999999, 9999999, -9999999, -9999999);
	}
}

gm::RectD SVGPointList::CalculateBoundingBox(const gm::matrix3d& transform) const
{
	return m_p->CalculateBoundingBox(transform);
}

gm::RectD SVGPointListData::CalculateBoundingBox(const gm::matrix3d& transform) const
{
	size_t numberOfItems = m_items.GetSize();

	if (numberOfItems > 0)
	{
		double minx;// = m_items[0]->m_x;
		double miny;// = m_items[0]->m_y;

		gm::vector2d v2 = transform.transform(gm::PointD(m_items[0]->m_x, m_items[0]->m_y));
		minx = v2[0];
		miny = v2[1];

		double maxx = minx;
		double maxy = miny;

		for (size_t i = 1; i < numberOfItems; ++i)
		{
			SVGPoint* pPoint = m_items[i];

			gm::vector2d v2 = transform.transform(gm::PointD(m_items[i]->m_x, m_items[i]->m_y));

			if (v2[0] < minx) minx = v2[0];
			else if (v2[0] > maxx) maxx = v2[0];

			if (v2[1] < miny) miny = v2[1];
			else if (v2[1] > maxy) maxy = v2[1];
		}

		return gm::RectD(minx, miny, maxx-minx, maxy-miny);
	}
	else
	{
		return gm::RectD(0, 0, 0, 0);
		//return RectD(9999999, 9999999, -9999999, -9999999);
	}
}

}	// Web
}	// System
