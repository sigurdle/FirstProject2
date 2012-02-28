#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{
namespace Media3D
{

DependencyClass* Group::get_Class()
{
	static DependencyClass depclass(typeid(Group), baseClass::get_Class());

	/*
	static DependencyProperty* properties[] =
	{
		get_EyeProperty(),
		get_AtProperty(),
		get_UpProperty(),
	};
	*/

	return &depclass;
}

DependencyClass* Group::pClass(get_Class());

Group::Group() : Visual3D(get_Class())
{
}

void Group::Render(ManagedRenderContext renderContext)
{
	for (size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->Render(renderContext);
	}
}

void Group::SetLight(ImmediateRenderContext* renderContext)
{
	for (size_t i = 0; i < m_children.size(); ++i)
	{
		m_children[i]->SetLight(renderContext);
	}
}

size_t Group::GetChildrenCount() throw ()
{
	return m_children.size();
}

void Group::AddChild(Visual3D* obj)
{
	VerifyArgumentNotNull(obj);

	obj->SetRoot(GetRoot());
	m_children.push_back(obj);
}

Visual3D* Group::GetChild(size_t index)
{
	if (index >= m_children.size())
	{
		raise(ArgumentOutOfRangeException());
	}

	return m_children[index];
}

}	// Media3D
}	// Gui
}	// System
