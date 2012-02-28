#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* Visuals::get_Class()
{
	static DependencyClass depclass(typeid(Visuals), UIElement::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_ParentProperty(),
		get_TransformProperty(),
		get_VisibleGeometryProperty(),
		get_HitGeometryProperty(),
		get_OpacityProperty(),
		get_OpacityMaskProperty(),
		get_ClipProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* Visuals::pClass(get_Class());

Visuals::Visuals() : UIElement(get_Class())
{
}
/*
Visuals::Visuals(DependencyClass* depClass) : Visual(depClass)
{
}
*/

void Visuals::AddChild(Visual* visual)
{
	if (visual == NULL)
	{
		raise(ArgumentNullException());
	}

//	VERIFY(visual->GetRoot() == NULL);
	visual->SetRoot(GetRoot());

	m_items.push_back(visual);

	if (GetRoot())
	{
		GetRoot()->InvalidateRender();
	}
}

size_t Visuals::GetChildrenCount()
{
	return m_items.size();
}

Visual* Visuals::GetChild(size_t index)
{
	return m_items[index];
}

void Visuals::Render(ManagedRenderContext renderContext)
{
	for (auto it = m_items.begin(); it != m_items.end(); ++it)
	{
		Visual* visual = *it;
		ASSERT(visual);

		visual->Render_(renderContext);
	}
}

/*
UIElement* Visuals::HitTest(LDraw::PointF point)
{
	<Visual*>::iterator it = m_items.end();
	--it;
	while (it != m_items.end())
	{
		Visual* visual = *it;
		--it;

		ASSERT(visual);
		UIElement* hitVisual = visual->HitTest_(point);
		if (hitVisual)
		{
			return hitVisual;
		}
	}

	return NULL;
}
*/

}
}
