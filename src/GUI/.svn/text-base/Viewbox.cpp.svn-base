#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

Viewbox::Viewbox() : Decorator(get_Class())
{
}

void Viewbox::RenderRetained(ManagedRetainedRenderContext renderContext)
{
	gm::matrix3f matrix;

	float width = 500;
	float height = 500;

	matrix = gm::matrix3f::getTranslate(-m_rect.X, -m_rect.Y) *
		gm::matrix3f::getScale(width / m_rect.Width, height / m_rect.Height);

	renderContext.PushTransform(new MatrixTransform(matrix));

	ASSERT(0);
	//get_Child()->Render_(renderContext);

	renderContext.Pop();
}

}
}
