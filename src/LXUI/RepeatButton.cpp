#include "stdafx.h"
#include "LXUI2.h"
#include "RepeatButton.h"

namespace System
{
namespace UI
{

__live_object_ptr<Style> RepeatButtonStyle;

RepeatButton::RepeatButton()
{
	if (RepeatButtonStyle == NULL)
	{
		XmlData::Document* document = new XmlData::Document;

		StringW* filename = MakeFilePath(_Module, L"../../../RepeatButtonStyle.lxui");
		document->load(filename);

		Type* returnType;
		RepeatButtonStyle = dynamic_cast<Style*>(CreateObjectFromElement(NULL, NULL, document->get_documentElement(), &returnType));
	}

	set_Style(RepeatButtonStyle);
/*
	ApplyStyle(get_Style(), this);
	InitScript();
	*/
}

}	// UI
}
