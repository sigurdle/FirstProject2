#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

DependencyClass* MatrixTransform::get_Class()
{
	static DependencyClass depclass(typeid(MatrixTransform), Transform::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_TranslateXProperty(),
		get_TranslateYProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* MatrixTransform::pClass(get_Class());

MatrixTransform::MatrixTransform() : Transform(get_Class())
{
}

MatrixTransform::MatrixTransform(const gm::matrix3f& matrix) : Transform(get_Class())
{
	m_matrix = matrix;
}

}
}
