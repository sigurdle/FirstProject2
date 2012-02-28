#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* CompoundGeometry::get_Class()
{
	static DependencyClass depclass(typeid(CompoundGeometry), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{

		get_FontSizeProperty(),
		get_FontFamilyProperty(),
		get_FontWeightProperty(),
		get_FontStyleProperty(),
		get_TextSourceProperty(),
		get_TextProperty(),
		get_BrushProperty(),
//		get_CursorPositionProperty(),
//		get_CursorLineProperty(),
//		get_CursorColumnProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* CompoundGeometry::pClass(get_Class());

CompoundGeometry::CompoundGeometry() : Geometry(get_Class())
{
}

ID2D1PathGeometry* CompoundGeometry::GetD2DGeometry()
{
	if (m_D2DGeometry == NULL)
	{
		ASSERT(0);
	}

	return m_D2DGeometry;
}

HRGN CompoundGeometry::CreateHRGN()
{
	HRGN hRgn = CreateRectRgn(0, 0, 0, 0);	// Empty

	int mode;
	switch (m_combineOp)
	{
	case CombineOp_Union:
		mode = RGN_OR;
		break;

	case CombineOp_Intersect:
		mode = RGN_AND;
		break;

	case CombineOp_Complement:
		mode = RGN_XOR;
		break;

	case CombineOp_Subtract:
		mode = RGN_DIFF;
		break;
	}

	list<Geometry*>::iterator it = m_children.begin();
	while (it != m_children.end())
	{
		Geometry* child = *it;
		++it;

		HRGN hRgn2 = child->CreateHRGN();

		CombineRgn(hRgn, hRgn, hRgn2, mode);
	}

	return hRgn;
}

/*
void CompoundGeometry::RenderFill(ManagedRenderContext renderContext, Brush* brush)
{
}

void CompoundGeometry::RenderStroke(ManagedRenderContext renderContext, Brush* brush, float width)
{
}
*/

}	// Gui
}	// System
