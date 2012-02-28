#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(FillMode, PolygonGeometry, FillMode, FillMode_Winding)

DependencyClass* PolygonGeometry::get_Class()
{
	static DependencyClass depclass(typeid(PolygonGeometry), Geometry::get_Class());

	static DependencyProperty* properties[] =
	{
		get_FillModeProperty(),
	};

	return &depclass;
}

DependencyClass* PolygonGeometry::pClass(get_Class());

PolygonGeometry::PolygonGeometry() : Geometry(get_Class())
{
}

void PolygonGeometry::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_FillModeProperty())
	{
		if (m_D2DGeometry)
		{
			m_D2DGeometry->Release();
			m_D2DGeometry = NULL;
		}
	}

	Geometry::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

HRGN PolygonGeometry::CreateHRGN()
{
	ASSERT(0);
	return NULL;
}

ID2D1PathGeometry* PolygonGeometry::GetD2DGeometry()
{
	if (m_D2DGeometry == NULL)
	{
		Graphics::Direct10::s.m_D2DFactory->CreatePathGeometry(&m_D2DGeometry);

		ID2D1GeometrySink* pGeometrySink;
		m_D2DGeometry->Open(&pGeometrySink);

		if (m_points.size() > 0)
		{
			gm::PointF point = m_points[0];
			pGeometrySink->BeginFigure(D2D1::Point2F(point.X, point.Y), D2D1_FIGURE_BEGIN_FILLED);

			for (uint i = 1; i < m_points.size(); ++i)
			{
				gm::PointF point = m_points[i];

				pGeometrySink->AddLine(D2D1::Point2F(point.X, point.Y));
			}

			pGeometrySink->EndFigure(D2D1_FIGURE_END_CLOSED);
		}

		FillMode fillMode = get_FillMode();

		pGeometrySink->SetFillMode(fillMode == FillMode_Alternate? D2D1_FILL_MODE_ALTERNATE: D2D1_FILL_MODE_WINDING);

		pGeometrySink->Close();
	//	pGeometrySink->Release();
	//	pGeometrySink = NULL;
	}

	return m_D2DGeometry;
}

}	// Gui
}	// System
