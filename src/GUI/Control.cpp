#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

IMP_DEPENDENCY_PROPERTY(String, Control, FontFamily, String(L"Courier New"))
IMP_DEPENDENCY_PROPERTY(float, Control, FontSize, 17.0f)
IMP_DEPENDENCY_PROPERTY(int, Control, FontWeight, 400)
IMP_DEPENDENCY_PROPERTY(FontStyle, Control, FontStyle, FontStyle_Normal)

IMP_DEPENDENCY_PROPERTY(Brush*, Control, Foreground, nullptr)
IMP_DEPENDENCY_PROPERTY(Brush*, Control, Background, nullptr)
IMP_DEPENDENCY_PROPERTY(Brush*, Control, BorderBrush, nullptr)

DependencyClass* Control::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_FontFamilyProperty(),
		get_FontSizeProperty(),
		get_FontWeightProperty(),
		get_FontStyleProperty(),

		get_ForegroundProperty(),
		get_BackgroundProperty(),
		get_BorderBrushProperty(),
	};

	return &depclass;
}

Control::Control(DependencyClass* depClass) : FrameworkElement(depClass)
{
}

Control::Control(DependencyClass* depClass, gm::SizeF size) : FrameworkElement(depClass, size)
{
}

Template* Control::get_Template()
{
	return m_Template;
}

void Control::set_Template(Template* pTemplate)
{
// TODO

	m_Template = pTemplate;

	ASSERT(0);
//	m_localProperties[get_ShadowTreeProperty()->m_index]->m_computedValue = Variant();//&PropertyValue::UnsetValue;
}

#if 0
Variant Control::GetLocalPropertyValue(PropertyValue* pPropertyVal)
{
#if 0
	if (pPropertyVal->m_dp == get_ShadowTreeProperty())
	{
		return CreateShadowTree();
		/*
		if (m_ShadowTree == NULL)
		{
			m_ShadowTree = CreateShadowTree();
		}

		return m_ShadowTree;
		*/
	}
#endif

	return baseClass::GetLocalPropertyValue(pPropertyVal);
}
#endif

void Control::RenderRetained(ManagedRetainedRenderContext renderContext)
{
	/*
	Visual* shadowTree = get_ShadowTree();

	if (shadowTree)
	{
		shadowTree->Render_(renderContext);
	}
	*/
}

void Control::Render(ManagedRetainedRenderContext renderContext)
{
	UIElement* shadowTree = get_ShadowTree();

	if (shadowTree)
	{
		shadowTree->RenderRetained(renderContext);
	}
}

////

//DependencyClass AudioSourceVoice::Class(typeid(AudioSourceVoice), &DependencyObject::Class);


//TypedDependencyProperty<float> AudioSourceVoice::VolumeProperty(&Class, WSTR("Volume"), 1.0f);
//TypedDependencyProperty<float> AudioSourceVoice::FrequencyRatioProperty(&Class, WSTR("FrequencyRatio"), 1.0f);
//TypedDependencyProperty<int64> AudioSourceVoice::SamplesPlayedProperty(&Class, WSTR("SamplesPlayed"), 0);

}
}
