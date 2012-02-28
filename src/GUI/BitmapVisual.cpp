#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(IBitmapSource*, BitmapVisual, Bitmap, nullptr);
IMP_DEPENDENCY_PROPERTY(RectangleGeometry*, BitmapVisual, DestRect, nullptr);
IMP_DEPENDENCY_PROPERTY(float, BitmapVisual, DestLeft, _this().getDestRect().getLeft());
IMP_DEPENDENCY_PROPERTY(float, BitmapVisual, DestTop, _this().getDestRect().getTop());
IMP_DEPENDENCY_PROPERTY(float, BitmapVisual, DestWidth, _this().getDestRect().getWidth());
IMP_DEPENDENCY_PROPERTY(float, BitmapVisual, DestHeight, _this().getDestRect().getHeight());
IMP_DEPENDENCY_PROPERTY(float, BitmapVisual, DestRight, _this().getDestRect().getRight());
IMP_DEPENDENCY_PROPERTY(float, BitmapVisual, DestBottom, _this().getDestRect().getBottom());

DependencyClass* BitmapVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_BitmapProperty(),
	};

	return &depclass;
}

BitmapVisual::BitmapVisual() : UIElement(get_Class())
{
}

void BitmapVisual::Render(ManagedRenderContext renderContext)
{
	IBitmapSource* bitmap = get_Bitmap();
	if (bitmap)
	{
		Graphics::RenderTarget* rt = renderContext.m_p->GetRT();

		ImmediateRenderContext* imm = static_cast<ImmediateRenderContext*>(renderContext.m_p);
		rt->m_modelView = imm->m_transform;
		rt->m_modelViewProjection = rt->m_projection * rt->m_modelView;

		gm::RectF dstRect(80, 20, bitmap->GetBitmap()->GetWidth(), bitmap->GetBitmap()->GetHeight());
		//*get_DestRect()

		Graphics::Direct10::s.Render(renderContext.m_p->GetRT(), bitmap->GetBitmap(), dstRect);
	}
}

Graphics::Bitmap* BitmapVisual::GetBitmap(Graphics::RenderTarget* rt, int scaledWidth, int scaledHeight, float scaleX, float scaleY)
{
	IBitmapSource* bitmap = get_Bitmap();
	if (bitmap)
	{
		return bitmap->GetBitmap();
	}

	return nullptr;
}

UIElement* BitmapVisual::HitTest(gm::PointF point)
{
	RectangleGeometry* r = get_DestRect();
	if (r && r->Contains(point))
		return this;
	else
		return nullptr;
}

}	// Gui
}	// System
