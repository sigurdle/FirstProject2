#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

RenderContext::RenderContext() :
	m_colorTransform(gm::matrix4f::getIdentity()),
	m_colorTranslate(gm::vector4f(0, 0, 0, 0))
{
}

/*
void RenderContext::StrokeGeometry(Geometry* geometry, Brush* brush, float width)
{
}

void RenderContext::FillGeometry(Geometry* geometry, Brush* brush)
{
}
*/

}
}
