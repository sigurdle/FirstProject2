#include "stdafx.h"
#include "LXUI2.h"
#include "ToolBar.h"

#include "DragContext.h"

namespace System
{
namespace UI
{

__live_object_ptr<Style> ToolBarStyle;

ToolBar::ToolBar()
{
	if (ToolBarStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../ToolBarStyle.lxui");
		document->load(filename);

		Type* returnType;
		ToolBarStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));

		/*
		ButtonStyle->Load(document->get_documentElement());
		*/
	}

	set_Style(ToolBarStyle);
/*
	ApplyStyle(get_Style(), this);

	InitScript();
	*/
}

void ToolBar::OnPreviewMouseDown(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

	CDragContext drag;
	drag.m_pBar = this;//m_Content;
	Point screenpos = args->GetScreenPosition();

	drag.StartDrag(LDraw::PointI(screenpos.X, screenpos.Y));
}

void ToolBar::OnMouseDown(MouseButtonEventArgs* args)
{
	args->set_Handled(true);

	CDragContext drag;
	drag.m_pBar = this;//m_Content;
	Point screenpos = args->GetScreenPosition();

	drag.StartDrag(LDraw::PointI(screenpos.X, screenpos.Y));
}

}
}
