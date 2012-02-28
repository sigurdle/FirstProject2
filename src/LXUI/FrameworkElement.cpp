#include "stdafx.h"
#include "LXUI2.h"
//#include "LXUI.h"

#include "Cursor.h"
#include <cfloat>

//#include "Track.h"	// TODO remove
#include "Button.h"	// TODO remove

namespace System
{
namespace UI
{

DependencyProperty* FrameworkElement::s_WidthProperty = RegisterProperty(WSTR("Width"), typeid(double), typeid(FrameworkElement), DoubleObject::get_NaN(), PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_HeightProperty = RegisterProperty(WSTR("Height"), typeid(double), typeid(FrameworkElement), DoubleObject::get_NaN(), PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_MinWidthProperty = RegisterProperty(WSTR("MinWidth"), typeid(double), typeid(FrameworkElement), DoubleObject::get_NaN(), PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_MaxWidthProperty = RegisterProperty(WSTR("MaxWidth"), typeid(double), typeid(FrameworkElement), DoubleObject::get_NaN(), PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_MinHeightProperty = RegisterProperty(WSTR("MinHeight"), typeid(double), typeid(FrameworkElement), DoubleObject::get_NaN(), PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_MaxHeightProperty = RegisterProperty(WSTR("MaxHeight"), typeid(double), typeid(FrameworkElement), DoubleObject::get_NaN(), PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_MarginProperty = RegisterProperty(WSTR("Margin"), typeid(Thickness), typeid(FrameworkElement), NULL, PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_HorizontalAlignmentProperty = RegisterProperty(WSTR("HorizontalAlignment"), typeid(HorizontalAlignment), typeid(FrameworkElement), IntObject::GetObject(HorizontalAlignment_Stretch), PropertyMetaData(None));
DependencyProperty* FrameworkElement::s_VerticalAlignmentProperty = RegisterProperty(WSTR("VerticalAlignment"), typeid(VerticalAlignment), typeid(FrameworkElement), IntObject::GetObject(VerticalAlignment_Stretch), PropertyMetaData(None));
DependencyProperty* FrameworkElement::s_CursorProperty = RegisterAttached(WSTR("Cursor"), typeid(Cursor), typeid(FrameworkElement), NULL, PropertyMetaData(ChildInherits));
DependencyProperty* FrameworkElement::s_StyleProperty = RegisterProperty(WSTR("Style"), typeid(Style), typeid(FrameworkElement), NULL, PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_LayoutTransformProperty = RegisterProperty(WSTR("LayoutTransform"), typeid(Transform), typeid(FrameworkElement), NULL, PropertyMetaData(AffectsMeasure));
DependencyProperty* FrameworkElement::s_TagProperty = RegisterProperty(WSTR("Tag"), typeid(Object), typeid(FrameworkElement), NULL, PropertyMetaData(None));

extern DepState* depstate;

FrameworkElement::FrameworkElement()
{
	m_overrideFinalSize.Width = -1;

	m_triggers = new TriggerCollection;

	m_resources = new ResourceDictionary;	// ??
}

/*
void FrameworkElement::SetBinding(DependencyProperty* dp, Data::BindingBase* binding)
{
}
*/

void DependencyObject::OnSourcePropertyChanged(DependencyProperty* targetDepProperty, Object* sender, DependencyPropertyChangedEventArgs args)
{
	/*
	if (*targetProperty->m_name == L"Value")
	{
		MessageBeep(-1);
	}
	*/

	if (!m_isDpSetting[targetDepProperty->gindex])
	{
		m_isDpSetting[targetDepProperty->gindex] = true;

	//	SetValue(targetProperty, args.get_NewValue());
		InvalidateProperty(targetDepProperty);

		m_isDpSetting[targetDepProperty->gindex] = false;
	}
}

void DependencyObject::SetBindingInternal(DependencyProperty* dp, Data::BindingBase* binding)
{
	ASSERT(dp);

	Data::BindingExpression* bindingExp = new Data::BindingExpression;
	bindingExp->m_parentBindingBase = binding;
	// Listen to source property
	Object* source = ((Data::Binding*)binding)->get_Source();
	Data::PropertyPath* path = ((Data::Binding*)binding)->get_Path();

	ASSERT(source != this);


	// TODO
//	DependencyProperty* dpSource = path->m_parsedPath->m_name;
	
	DependencyProperty* dpSource = GetProperty(source->GetType(), path->get_Path());
	if (dpSource == NULL)
	{
		dpSource = GetProperty(source->GetType(), path->get_Path());
	}
	if (dpSource)
	{
	//	dpSource = GetProperty(source->GetType(), path->get_Path());

		DependencyObject* dSource = dynamic_cast<DependencyObject*>(source);

	//	mem_fun2(&FrameworkElement::OnPropChanged);

		//mem_fun3(&DependencyObject::OnSourcePropertyChanged);

	//	bind3(mem_fun3(&DependencyObject::OnSourcePropertyChanged), this, dp);;	// Hack, TODO remove
		dSource->m_depPropertyChangedHandlers[dpSource->gindex].connect(bind2st_of_4(mem_fun3(&DependencyObject::OnSourcePropertyChanged), this, dp));

	#if 0
			bind(mem_fun2(&DependencyObject::OnSourcePropertyChanged), this);;	// Hack, TODO remove
			dSource->m_depPropertyChangedHandlers[dpSource->gindex].connect(bind(mem_fun2(&DependencyObject::OnSourcePropertyChanged), this));
	#endif

	}
	m_bindings[dp->gindex] = bindingExp;

#if 0
	else
	{
		/*
		INotifyPropertyChanged* notifyPropertyChanged = dynamic_cast<INotifyPropertyChanged*>(source);
		notifyPropertyChanged->get_PropertyChanged().connect(mem_fun(&Data::BindingExpression::OnPropertyChanged));
		*/
	}
#endif
}

void DependencyObject::SetBinding(DependencyProperty* dp, Data::BindingBase* binding)
{
	SetBindingInternal(dp, binding);
	InvalidateProperty(dp);
}

TriggerCollection* FrameworkElement::get_Triggers()
{
	return m_triggers;
}

// virtual
void FrameworkElement::OnApplyTemplate()
{
}

// virtual
LDraw::SizeD FrameworkElement::MeasureCore(LDraw::SizeD availSize)
{
	double Width = get_Width();
	double Height = get_Height();
	Thickness* margin = get_Margin();
//	HorizontalAlignment horizontalAlignment = get_HorizontalAlignment();
//	VerticalAlignment verticalAlignment = get_VerticalAlignment();

	if (margin)
	{
		availSize.Width -= margin->get_Left() + margin->get_Right();
		availSize.Height -= margin->get_Top() + margin->get_Bottom();
	}

	LDraw::SizeD desiredSize;

	if (!_isnan(Width))
	{
		desiredSize.Width = Width;
		availSize.Width = desiredSize.Width;
	}
	/*
	else if (horizontalAlignment == HorizontalAlignment_Stretch)
	{
		desiredSize.Width = availSize.Width;
	}
	*/

	if (!_isnan(Height) != NULL)
	{
		desiredSize.Height = Height;
		availSize.Height = desiredSize.Height;
	}
	/*
	else if (verticalAlignment == VerticalAlignment_Stretch)
	{
		desiredSize.Height = availSize.Height;
	}
	*/

	if (availSize.Width < 0) availSize.Width = 0;
	if (availSize.Height < 0) availSize.Height = 0;

	LDraw::SizeD newDesiredSize = MeasureOverride(availSize);
//	m_DesiredSizeOverride = newDesiredSize;

	ASSERT(newDesiredSize.Width >= 0 && newDesiredSize.Height >= 0);

	if (!_isnan(Width))
	{
		desiredSize.Width = Width;
	}
	/*
	else if (horizontalAlignment != HorizontalAlignment_Left)
	{
		desiredSize.Width = availSize.Width;
	}
	*/
	else
	{
		desiredSize.Width = newDesiredSize.Width;
	}

	if (!_isnan(Height))
	{
		desiredSize.Height = Height;
	}
	/*
	else if (verticalAlignment != VerticalAlignment_Top)
	{
		desiredSize.Height = availSize.Height;
	}
	*/
	else
	{
		desiredSize.Height = newDesiredSize.Height;
	}

	if (desiredSize.Width < 0) desiredSize.Width = 0;
	if (desiredSize.Height < 0) desiredSize.Height = 0;

	if (margin)
	{
		desiredSize.Width += margin->get_Left() + margin->get_Right();
		desiredSize.Height += margin->get_Top() + margin->get_Bottom();
	}

	return desiredSize;
}

// virtual
void FrameworkElement::ArrangeCore(LDraw::RectD finalRect)
{
//	double Width = get_Width();
//	double Height = get_Height();
	Thickness* margin = get_Margin();
//	HorizontalAlignment horizontalAlignment = get_HorizontalAlignment();
//	VerticalAlignment verticalAlignment = get_VerticalAlignment();

//	LDraw::SizeD desiredSize = get_DesiredSize();

//	else
//		finalSize.Width = finalRect.Width;

//	if (Height != NULL)
//		finalSize.Height = Height->get_Value();
//	else
//		finalSize.Height = finalRect.Height;

	//LDraw::SizeD finalSize = finalRect.GetSize();

#if 0
	if (horizontalAlignment == HorizontalAlignment_Left)
	{
		finalRect.Width = desiredSize.Width;

//		finalSize = desiredSize;
	//	finalRect.Width = desiredSize.Width;
	//	finalRect.Height = desiredSize.Width;
	}
	else if (horizontalAlignment == HorizontalAlignment_Right)
	{
		finalRect.X = finalRect.Width - desiredSize.Width;
		finalRect.Width = desiredSize.Width;
	}
	else if (horizontalAlignment == HorizontalAlignment_Center)
	{
		finalRect.X = (finalRect.Width - desiredSize.Width)/2;
		finalRect.Width = desiredSize.Width;
	}
	else if (horizontalAlignment == HorizontalAlignment_Stretch)
	{
//		finalSize.Width = finalRect.Width;
	}
	else
		VERIFY(0);
#endif

	/*
	// ??
	if (!_isnan(Width))
		finalRect.Width = Width;

	// ??
	if (!_isnan(Height))
		finalRect.Height = Height;
		*/

	if (margin)
	{
		finalRect.X += margin->get_Left();
		finalRect.Y += margin->get_Top();
		finalRect.Width -= margin->get_Left() + margin->get_Right();
		finalRect.Height -= margin->get_Top() + margin->get_Bottom();
	}

//	if (finalRect.Width < 0) finalRect.Width = 0;
//	if (finalRect.Height < 0) finalRect.Height = 0;

// Call base, it will set offset and RenderBounds to the finalRect
	UIElement::ArrangeCore(finalRect);

//	if (m_overrideFinalSize.Width == -1 || m_overrideFinalSize != finalRect.GetSize())
	if (!IsArrangeValid() || m_overrideFinalSize != finalRect.GetSize())
	{
		LDraw::SizeD finalSizeOverride = ArrangeOverride(finalRect.GetSize());

		if (margin)
		{
			finalSizeOverride.Width += margin->get_Left() + margin->get_Right();
			finalSizeOverride.Height += margin->get_Top() + margin->get_Bottom();
		}

		m_overrideFinalSize = finalRect.GetSize();
	}

#if 0
	if (get_VisualTree())
	{
		UIElement* pVisual = dynamic_cast<UIElement*>(get_VisualTree());

	//	pVisual->CalculateBoundsAndChildren(LDraw::RectD(0, 0, m_computedSize.Width, m_computedHeight));
		pVisual->Arrange(LDraw::RectD(LDraw::PointD(0, 0), finalSize));

		m_computedSize = pVisual->m_computedSize;

		m_expandedBBox = pVisual->m_expandedBBox;
	//	m_expandedBBox.Y = 0;
	//	m_expandedBBox.Width = m_computedSize.Width;
	//	m_expandedBBox.Height = m_computedHeight;

//		m_computedSize.Width = pVisual->m_expandedBBox.Width;
//		m_computedHeight = pVisual->m_expandedBBox.Height;
	}
	else
	{
		/*

		double minX = 0;
		double minY = 0;
		double maxX = m_computedSize.Width;
		double maxY = m_computedSize.Height;

		int size = get_VisualChildrenCount();//rchildList()->get_Size();
		for (int i = 0; i < size; i++)
		{
			Visual* pVisual = GetVisualChild(i);//(*get_rchildList())[i];
			pVisual->Arrange(LDraw::RectD(LDraw::PointD(0, 0), pVisual->get_DesiredSize()));

			minX = MIN(minX, pVisual->m_expandedBBox.X);
			minY = MIN(minY, pVisual->m_expandedBBox.Y);
			maxX = MAX(maxX, pVisual->m_expandedBBox.GetRight());
			maxY = MAX(maxY, pVisual->m_expandedBBox.GetBottom());

		}

		m_expandedBBox.X = minX;
		m_expandedBBox.Y = minY;
		m_expandedBBox.Width = maxX-minX;
		m_expandedBBox.Height = maxY-minY;
		*/
	}

	return finalSize;
#endif
}

LDraw::SizeD FrameworkElement::MeasureOverride(LDraw::SizeD availSize)
{
	return LDraw::SizeD(0,0);	// ??
}

LDraw::SizeD FrameworkElement::ArrangeOverride(LDraw::SizeD finalSize)
{
	return finalSize;
}

double FrameworkElement::get_Width()
{
	return static_cast<DoubleObject*>(GetValue(get_WidthProperty()))->GetValue();
}

void FrameworkElement::set_Width(double newVal)
{
	SetValue(get_WidthProperty(), DoubleObject::GetObject(newVal));
}

double FrameworkElement::get_Height()
{
	return static_cast<DoubleObject*>(GetValue(get_HeightProperty()))->GetValue();
}

void FrameworkElement::set_Height(double newVal)
{
	SetValue(get_HeightProperty(), DoubleObject::GetObject(newVal));
}

double FrameworkElement::get_MinWidth()
{
	return static_cast<DoubleObject*>(GetValue(get_MinWidthProperty()))->GetValue();
}

void FrameworkElement::set_MinWidth(double value)
{
	SetValue(get_MinWidthProperty(), DoubleObject::GetObject(value));
}

double FrameworkElement::get_MinHeight()
{
	return static_cast<DoubleObject*>(GetValue(get_MinHeightProperty()))->GetValue();
}

void FrameworkElement::set_MinHeight(double value)
{
	SetValue(get_MinHeightProperty(), DoubleObject::GetObject(value));
}

double FrameworkElement::get_MaxWidth()
{
	return static_cast<DoubleObject*>(GetValue(get_MaxWidthProperty()))->GetValue();
}

void FrameworkElement::set_MaxWidth(double value)
{
	SetValue(get_MaxWidthProperty(), DoubleObject::GetObject(value));
}

double FrameworkElement::get_MaxHeight()
{
	return static_cast<DoubleObject*>(GetValue(get_MaxHeightProperty()))->GetValue();
}

void FrameworkElement::set_MaxHeight(double value)
{
	SetValue(get_MaxHeightProperty(), DoubleObject::GetObject(value));
}

Thickness* FrameworkElement::get_Margin()
{
	return static_cast<Thickness*>(GetValue(get_MarginProperty()));
}

void FrameworkElement::set_Margin(Thickness* margin)
{
	SetValue(get_MarginProperty(), margin);
}

HorizontalAlignment FrameworkElement::get_HorizontalAlignment()
{
	return (HorizontalAlignment)static_cast<IntObject*>(GetValue(get_HorizontalAlignmentProperty()))->GetValue();
}

void FrameworkElement::set_HorizontalAlignment(HorizontalAlignment alignment)
{
	SetValue(get_HorizontalAlignmentProperty(), IntObject::GetObject(alignment));
}

VerticalAlignment FrameworkElement::get_VerticalAlignment()
{
	return (VerticalAlignment)static_cast<IntObject*>(GetValue(get_VerticalAlignmentProperty()))->GetValue();
}

void FrameworkElement::set_VerticalAlignment(VerticalAlignment alignment)
{
	SetValue(get_VerticalAlignmentProperty(), IntObject::GetObject(alignment));
}

Cursor* FrameworkElement::get_Cursor()
{
	return static_cast<Cursor*>(GetValue(get_CursorProperty()));
}

void FrameworkElement::set_Cursor(Cursor* pCursor)
{
	SetValue(get_CursorProperty(), pCursor);
}

Transform* FrameworkElement::get_LayoutTransform()
{
	return static_cast<Transform*>(GetValue(get_LayoutTransformProperty()));
}

void FrameworkElement::set_LayoutTransform(Transform* layoutTransform)
{
	SetValue(get_LayoutTransformProperty(), layoutTransform);
}

Style* FrameworkElement::get_Style()
{
	return static_cast<Style*>(GetValue(get_StyleProperty()));
}

void FrameworkElement::set_Style(Style* style)
{
	SetValue(get_StyleProperty(), style);
}

Object* FrameworkElement::get_Tag()
{
	return GetValue(get_TagProperty());
}

void FrameworkElement::set_Tag(Object* tag)
{
	SetValue(get_TagProperty(), tag);
}

ResourceDictionary* FrameworkElement::get_Resources()
{
	return m_resources;
}

void FrameworkElement::set_Resources(ResourceDictionary* resources)
{
	m_resources = resources;
}

Object* FrameworkElement::FindResource(Object* resourceKey)
{
	Object* resource = TryFindResource(resourceKey);
	if (resource == NULL)
	{
		throw new ResourceReferenceKeyNotFoundException();
	}

	return resource;
}

extern ResourceDictionary* ThemeDictionary;

Object* FrameworkElement::TryFindResource(Object* resourceKey)
{
	if (m_resources)
	{
		Object* resource = m_resources->get_Item(resourceKey);
		if (resource)
		{
			return resource;
		}
	}

	FrameworkElement* parent = dynamic_cast<FrameworkElement*>(GetRParent());
	if (parent)
	{
		return parent->TryFindResource(resourceKey);
	}
	else
	{
		Application* app = Application::get_Current();
		if (app)
		{
			Object* value = app->TryFindResource(resourceKey);
			if (value)
				return value;
		}

		if (ThemeDictionary == NULL)
		{
			ThemeDictionary = dynamic_cast<ResourceDictionary*>(Application::LoadComponent(new Uri(WSTR("C:/mmstudio/theme_dictionary.xaml"))));
		}

		if (ThemeDictionary)
		{
			Object* value = ThemeDictionary->get_Item(resourceKey);
			if (value)
				return value;
		}
	}

	return NULL;
}

void FrameworkElement::OnPropertyChanged(DependencyPropertyChangedEventArgs args)	// The effective value has changed
{
	if (args.get_Property() == get_StyleProperty())
	{
		ApplyStyle(get_Style(), this);
	}
	else
	{
		Style* style = get_Style();

		if (style)
		{
			TriggerCollection* triggers = style->get_Triggers();
			if (triggers)
			{
				unsigned int count = triggers->GetCount();
				for (unsigned int i = 0; i < count; i++)
				{
					Trigger* trigger = dynamic_cast<Trigger*>(triggers->get_Item(i));

					if (trigger->get_Property() == args.get_Property())
					{
						Object* triggerValue = trigger->get_Value();

						Object* value = args.get_NewValue();//GetValue(pProperty);

						if (value->Equals(triggerValue))
						{
							/*
							TRACE("trigger property: %S", trigger->get_Property()->GetName()->c_str());
							if (BoolObject* boolObj = dynamic_cast<BoolObject*>(value))
							{
								TRACE("= %s", boolObj->GetValue()? "true": "false");
							}
							TRACE("\n");
							*/

							Setters* setters = trigger->get_Setters();

							for (unsigned int i = 0; i < setters->GetCount(); i++)
							{
								Setter* setter = setters->get_Item(i);
								DependencyProperty* pDepProperty = setter->get_Property();
								int depPropertyIndex = pDepProperty->gindex;

								m_style_depproperties[depPropertyIndex] = setter;
								m_isValidProperties[depPropertyIndex] = false;

								// TODO, check if locally set, don't need to do anything

						//		this->InvalidateProperty(setter->get_Property());
							}

							for (unsigned int i = 0; i < setters->GetCount(); i++)
							{
								Setter* setter = setters->get_Item(i);
								DependencyProperty* pDepProperty = setter->get_Property();

								if (!m_isValidProperties[pDepProperty->gindex])
								{
									InvalidateProperty(pDepProperty);
								}
							}
						}
					}
				}
			}
		}
	}

	Data::BindingExpression* bindingExp = m_bindings[args.get_Property()->gindex];
	if (bindingExp)
	{
		/*
		if (true)
		{
			Data::PropertyPath* path = ((Data::Binding*)bindingExp->m_parentBindingBase)->get_Path();
			Object* source = ((Data::Binding*)bindingExp->m_parentBindingBase)->get_Source();

			Dispatch* dispatch = GetDispatch(source->GetType());

			Property* property = dispatch->GetProperty(path->get_Path()->ToStringA());

			Object* obj = (Object*)dispatch->pointer_Invoke(source, property->get_GetMethod(), 0, NULL);
		}
		*/
	}

	UIElement::OnPropertyChanged(args);
}

Object* FrameworkElement::ComputeBaseVal(DependencyProperty* dp)
{
	DependencyObject* pParent;

	/*
	if (dynamic_cast<Track*>(this) && *dp->m_name == L"Value")
	{
		MessageBeep(-1);
	}
	*/
	Data::BindingExpression* bindingExp = m_bindings[dp->gindex];

	if (dynamic_cast<Button*>(this)/* && *dp->m_name == L"Content"*/)
	{
		if (get_Width() == 42)
		{
			MessageBeep(-1);
		}

		if (bindingExp)
		{
		MessageBeep(-1);
		}

		MessageBeep(-1);
	}

	if (m_specifiedProperties[dp->gindex] != DependencyProperty::get_UnsetValue())	// Local value set
	{
		if (m_depCookies[dp->gindex] != NULL)
		{
			pParent = GetDependencyParent();

			pParent->RemoveDependant(dp, m_depCookies[dp->gindex]);
			m_depCookies[dp->gindex] = NULL;
		}

		return m_specifiedProperties[dp->gindex];
	}

	if (bindingExp)
	{
		if (true)
		{
			Data::PropertyPath* path = ((Data::Binding*)bindingExp->m_parentBindingBase)->get_Path();
			/*
			if (*path->get_Path() == L"Adjustment")
			{
				MessageBeep(-1);
			}
			*/

			Object* source = ((Data::Binding*)bindingExp->m_parentBindingBase)->get_Source();

			Dispatch* dispatch = GetDispatch(source->GetType());

			Property* prop = dispatch->GetProperty(path->get_Path()->ToStringA());

			Object* obj;

			if (prop->get_GetType()->get_Kind() == type_bool)
			{
				bool val = dispatch->int32_Invoke(source, prop->get_GetMethod(), 0, NULL) & 1;
				obj = BoolObject::GetObject(val);
			}
			else if (prop->get_GetType()->get_Kind() == type_int)
			{
				int val = dispatch->int32_Invoke(source, prop->get_GetMethod(), 0, NULL);
				obj = IntObject::GetObject(val);
			}
			else if (prop->get_GetType()->get_Kind() == type_double)
			{
				double val = dispatch->double_Invoke(source, prop->get_GetMethod(), 0, NULL);
				obj = DoubleObject::GetObject(val);
			}
			else if (prop->get_GetType()->get_Kind() == type_pointer)
			{
				obj = (Object*)dispatch->pointer_Invoke(source, prop->get_GetMethod(), 0, NULL);
				//obj = DoubleObject::GetObject(val);
			}
			else
				VERIFY(0);

			return obj;
		}
	}

	//Style* style = get_Style();
	//if (style)
	{
		Setter* propertyVal = /*m_style->*/ /*get_Setters()->*/m_style_depproperties[dp->gindex];
		if (propertyVal)
		{
			if (m_depCookies[dp->gindex] != NULL)
			{
				pParent = GetDependencyParent();

				pParent->RemoveDependant(dp, m_depCookies[dp->gindex]);
				m_depCookies[dp->gindex] = NULL;
			}

		//	return propertyVal->m_computedValue;
			return propertyVal->get_Value();
		}
	}

	if ((dp->m_metadata.m_flags & ChildInherits) && (pParent = GetDependencyParent()) != NULL)
	{
		if (m_depCookies[dp->gindex] == NULL)
			m_depCookies[dp->gindex] = pParent->AddDependant(dp, this);

		return pParent->ComputeProperty(dp);
	}
	else
	{
		return dp->m_defaultValue;
	}
}

}	// UI
}
