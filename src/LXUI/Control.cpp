#include "stdafx.h"
#include "LXUI2.h"
#include "Control.h"
#include "LXUIBoxWindow.h"

#include "SolidColorBrush.h"
#include "ChildWindow.h"
#include "Polyline.h"
#include "Cursor.h"

//#include "MenuItem.h"	// TODO remove

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{
namespace UI
{

//void SetValue(Dispatch* dispatch, void* _this, Method* method, Object* pObject, Type* pSourceType);

void InvalidateRenderChildren(Visual* visual);

DependencyProperty* Control::s_ForegroundProperty = RegisterProperty(WSTR("Foreground"), typeid(Brush), typeid(Control), NULL, PropertyMetaData(AffectsRender));
DependencyProperty* Control::s_BackgroundProperty = RegisterProperty(WSTR("Background"), typeid(Brush), typeid(Control), NULL, PropertyMetaData(AffectsRender));

#if AMIGA
//__live_object_ptr<DependencyProperty> Control::m_FontFamilyProperty = RegisterProperty(WSTR("FontFamily"), typeid(FontFamily), new FontFamily(WSTR("courier.font")), true);
//__live_object_ptr<DependencyProperty> Control::m_FontSizeProperty = RegisterProperty(WSTR("FontSize"), typeid(double), new System::DoubleObject(13), true);

DependencyProperty Control::s_FontFamilyProperty = RegisterProperty(WSTR("FontFamily"), typeid(FontFamily), typeid(Control), new FontFamily(WSTR("helvetica.font")), PropertyMetaData(ChildInherits | AffectsMeasure));
DependencyProperty Control::s_FontSizeProperty = RegisterProperty(WSTR("FontSize"), typeid(double), typeid(Control), System::DoubleObject::GetObject(11), PropertyMetaData(ChildInherits | AffectsMeasure));

#else
DependencyProperty* Control::s_FontFamilyProperty = RegisterProperty(WSTR("FontFamily"), typeid(FontFamily), typeid(Control), new FontFamily(WSTR("Courier New")), PropertyMetaData(ChildInherits | AffectsMeasure));
DependencyProperty* Control::s_FontSizeProperty = RegisterProperty(WSTR("FontSize"), typeid(double), typeid(Control), System::DoubleObject::GetObject(14), PropertyMetaData(ChildInherits | AffectsMeasure));
#endif
DependencyProperty* Control::s_FontWeightProperty = RegisterProperty(WSTR("FontWeight"), typeid(FontWeights::FontWeight), typeid(Control), IntObject::GetObject(FontWeights::Normal), PropertyMetaData(ChildInherits | AffectsMeasure));
DependencyProperty* Control::s_FontStyleProperty = RegisterProperty(WSTR("FontStyle"), typeid(FontStyles::FontStyle), typeid(Control), IntObject::GetObject(FontStyles::Normal), PropertyMetaData(ChildInherits | AffectsMeasure));
DependencyProperty* Control::s_TemplateProperty = RegisterProperty(WSTR("Template"), typeid(ControlTemplate), typeid(Control), NULL, PropertyMetaData(AffectsMeasure));
DependencyProperty* Control::s_HorizontalContentAlignmentProperty = RegisterProperty(WSTR("HorizontalContentAlignment"), typeid(HorizontalAlignment), typeid(Control), IntObject::GetObject(HorizontalAlignment_Stretch), PropertyMetaData(None));

Accel::Accel(uint16 _flags, uint16 _key, long _cmdId)
{
	flags = _flags;
	key = _key;
	cmdId = _cmdId;
}

Accel::Accel(const Accel& other)
{
	flags = other.flags;
	key = other.key;
	cmdId = other.cmdId;
}

Control::Control()
{
	m_VisualTree = NULL;
}

Control::~Control()
{
}

HorizontalAlignment Control::get_HorizontalContentAlignment()
{
	return (HorizontalAlignment)static_cast<IntObject*>(GetValue(get_HorizontalContentAlignmentProperty()))->GetValue();
}

void Control::set_HorizontalContentAlignment(HorizontalAlignment alignment)
{
	SetValue(get_HorizontalContentAlignmentProperty(), IntObject::GetObject(alignment));
}

FontWeights::FontWeight Control::get_FontWeight()
{
	return (FontWeights::FontWeight)static_cast<IntObject*>(GetValue(get_FontWeightProperty()))->GetValue();
}

void Control::set_FontWeight(FontWeights::FontWeight newVal)
{
	SetValue(get_FontWeightProperty(), IntObject::GetObject(newVal));
}

double Control::get_FontSize()
{
	return static_cast<DoubleObject*>(GetValue(get_FontSizeProperty()))->GetValue();
}

void Control::set_FontSize(double newVal)
{
	SetValue(get_FontSizeProperty(), DoubleObject::GetObject(newVal));
}

// static
FontFamily* Control::GetFontFamily(DependencyObject* object)
{
	return static_cast<FontFamily*>(object->GetValue(get_FontFamilyProperty()));
}

// static
void Control::SetFontFamily(DependencyObject* object, FontFamily* family)
{
	object->SetValue(get_FontFamilyProperty(), family);
}

FontFamily* Control::get_FontFamily()
{
	return static_cast<FontFamily*>(GetValue(get_FontFamilyProperty()));
}

void Control::set_FontFamily(FontFamily* family)
{
	SetValue(get_FontFamilyProperty(), family);
}

// static
FontStyles::FontStyle Control::GetFontStyle(DependencyObject* object)
{
	return (FontStyles::FontStyle)static_cast<IntObject*>(object->GetValue(get_FontStyleProperty()))->GetValue();
}

// static
double Control::GetFontSize(DependencyObject* object)
{
	return static_cast<DoubleObject*>(object->GetValue(get_FontSizeProperty()))->GetValue();
}

// static
void Control::SetFontSize(DependencyObject* object, double newVal)
{
	object->SetValue(get_FontSizeProperty(), DoubleObject::GetObject(newVal));
}

FontStyles::FontStyle Control::get_FontStyle()
{
	return (FontStyles::FontStyle)static_cast<IntObject*>(GetValue(get_FontStyleProperty()))->GetValue();
}

void Control::set_FontStyle(FontStyles::FontStyle newVal)
{
	if (newVal != FontStyles::Normal &&
		newVal != FontStyles::Italic &&
		newVal != FontStyles::Oblique)
	{
		ASSERT(0);
		THROW(std::exception("Invalid FontStyle value"));
	}

	SetValue(get_FontStyleProperty(), IntObject::GetObject(newVal));
}

// static
FontWeights::FontWeight Control::GetFontWeight(DependencyObject* object)
{
	return (FontWeights::FontWeight)static_cast<IntObject*>(object->GetValue(get_FontWeightProperty()))->GetValue();
}

Brush* Control::get_Background()
{
	return static_cast<Brush*>(GetValue(get_BackgroundProperty()));
}

void Control::set_Background(Brush* pBrush)
{
	SetValue(get_BackgroundProperty(), pBrush);
}

Brush* Control::get_Foreground()
{
	return static_cast<Brush*>(GetValue(get_ForegroundProperty()));
}

void Control::set_Foreground(Brush* pBrush)
{
	SetValue(get_ForegroundProperty(), pBrush);
}

void Control::OnRenderBackground(Graphics* pGraphics)
{
#if 0
	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
		LDraw::SizeD actualSize = get_ActualSize();
		__release<LDraw::Brush> brush = pBackgroundBrush->CreateBrush(this, 1, 1);
		pGraphics->FillRectangle(brush, 0, 0, actualSize.Width, actualSize.Height);
	}
#endif

//	OnRender(pGraphics);

	//OnRender3(pGraphics);
}

/*
//virtual
void Control::OnRender3(Graphics* pGraphics)
{
	// override this
}
*/

#if 0
// virtual
void Control::CreateLayerStuff(Graphics* pGraphics)
{
	UIElement::CreateLayerStuff(pGraphics);

	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
#if 0//AMIGA

		pGraphics->MultiplyTransform(m_transformMatrix);

		LDraw::gmVector2f xpt = pGraphics->GetTransform()->Transform(LDraw::PointF(m_expandedBBox.X, m_expandedBBox.Y));
		LDraw::Rect rect(xpt[0], xpt[1], m_expandedBBox.Width, m_expandedBBox.Height);

		pGraphics->PopTransform();//oldTransform);

		m_layer = CreateUpfrontLayer(GetRParent()->m_layerInfo, NULL, rect.X, rect.Y, rect.GetRight(), rect.GetBottom(), LAYERSIMPLE, NULL);
		ASSERT(m_layer);
#else

#endif
	}
}
#endif

// virtual
__release<LDraw::Region> Control::OnGetOpaqueRegion(LDraw::Matrix3f* transform)
{
	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
		m_bDrawsOutsideOpaqueRegion = false;	// TODO

		return new LDraw::Region(m_expandedBBox, transform->m_matrix, 10, false);

	//	LDraw::PointD xpt = transform->Transform(LDraw::PointD(m_expandedBBox.X, m_expandedBBox.Y));
	//	return new LDraw::Region(LDraw::Rect(ceil(xpt.X), ceil(xpt.Y), m_expandedBBox.Width, m_expandedBBox.Height));
	}

	return UIElement::OnGetOpaqueRegion(transform);
}

// virtual
__release<LDraw::Region> Panel::OnGetOpaqueRegion(LDraw::Matrix3f* transform)
{
	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
		m_bDrawsOutsideOpaqueRegion = false;	// TODO

		return new LDraw::Region(m_expandedBBox, transform->m_matrix, 10, false);

	//	LDraw::PointD xpt = transform->Transform(LDraw::PointD(m_expandedBBox.X, m_expandedBBox.Y));
	//	return new LDraw::Region(LDraw::Rect(ceil(xpt.X), ceil(xpt.Y), m_expandedBBox.Width, m_expandedBBox.Height));
	}

	return UIElement::OnGetOpaqueRegion(transform);
}

// virtual
__release<LDraw::Region> Border::OnGetOpaqueRegion(LDraw::Matrix3f* transform)
{
	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
		m_bDrawsOutsideOpaqueRegion = false;	// TODO

		return new LDraw::Region(m_expandedBBox, transform->m_matrix, 10, false);

	//	LDraw::PointD xpt = transform->Transform(LDraw::PointD(m_expandedBBox.X, m_expandedBBox.Y));
	//	return new LDraw::Region(LDraw::Rect(ceil(xpt.X), ceil(xpt.Y), m_expandedBBox.Width, m_expandedBBox.Height));
	}

	return UIElement::OnGetOpaqueRegion(transform);
}

#if 0
// virtual
void Control::Clip(Graphics* pGraphics, LDraw::Region * rgn)
{
	// The default is not to clip
//	if (m_computedRectangleWidth > 0 && m_computedRectangleHeight > 0)
	Brush* pBackgroundBrush = get_Background();
	if (pBackgroundBrush)
	{
#if 1
		/*release<LDraw::Matrix3f> oldTransform =*/ pGraphics->PushTransform();
		pGraphics->MultiplyTransform(m_transformMatrix);

#if 0
		LDraw::GraphicsPathF path;
		path.AddRectangle(m_expandedBBox);
		path.Transform(pGraphics->m_transform);

		LDraw::Region rectrgn(&path);

		rgn.Exclude(&rectrgn);
#else

	//	HRGN rect = CreateRectRgn(xpt[0], xpt[1], xpt[0]+m_expandedBBox.Width, xpt[1]+m_expandedBBox.Height);
	//	CombineRgn(rgn.m_hRgn, rgn.m_hRgn, rect, RGN_DIFF);
	//	DeleteObject(rect);

		LDraw::gmVector2f xpt = pGraphics->GetTransform()->Transform(LDraw::PointF(m_expandedBBox.X, m_expandedBBox.Y));
		LDraw::Rect rect(xpt[0], xpt[1], m_expandedBBox.Width, m_expandedBBox.Height);
		rgn = rgn->GetExcluded(new LDraw::Region(rect));
#endif

		pGraphics->PopTransform();//oldTransform);
#endif
	}
	else
	{
		UIElement::Clip(pGraphics, rgn);
	}
}
#endif

long Control::FindAccelerator(bool bAlt, bool bControl, bool bShift, uint16 virtKey, uint16 asciiKey)
{
	for (int i = 0; i < m_accelerators.GetSize(); i++)
	{
		const Accel& accel = m_accelerators[i];

		if (accel.flags & 1)
		{
			if (
					((accel.flags>>1) & 1) == bAlt &&
					((accel.flags>>2) & 1) == bControl &&
					((accel.flags>>3) & 1) == bShift &&
					(accel.key == virtKey))
			{
				return accel.cmdId;
			}
		}
		else
		{
			if (
					((accel.flags>>1) & 1) == bAlt &&
					((accel.flags>>2) & 1) == bControl &&
					((accel.flags>>3) & 1) == bShift &&
					(accel.key == asciiKey))
			{
				return accel.cmdId;
			}
		}
	}

	return 0;
}

/*
bool Control::handleAccelerator(Event* evt)
{
	return false;
}
*/

#if 0
void Control::handleEvent(Event* evt)
{
	if (evt->get_eventPhase() != CAPTURING_PHASE)
	{
		if (*evt->get_type() == L"accelerator"/* ||
			evt->get_type() == WSTR("char")*/)
		{
			long cmdId;

		//	if (evt->get_type() == WSTR("keydown"))
			{
				KeyEvent* keyEvt = dynamic_cast<KeyEvent*>(evt);
				cmdId = FindAccelerator(keyEvt->bAlt, keyEvt->bControl, keyEvt->bShift, keyEvt->vk, keyEvt->ascii);
			}
			/*
			else
			{
				CharEvent* charEvt = dynamic_cast<CharEvent*>(evt);
				cmdId = FindAccelerator(false, charEvt->bAlt, charEvt->bControl, charEvt->bShift, charEvt->cCharCode);
			}
			*/

			if (cmdId)
			{
				evt->stopPropagation();

				CommandInvokeEvent* cmdEvt = new CommandInvokeEvent;
				cmdEvt->InitCommandInvokeEvent(WSTR("command"), cmdId);

				evt->get_target()->dispatchEvent(cmdEvt);

				evt->preventDefault();
			}
		}
	}
}
#endif

void Control::OnPropertyChanged(DependencyPropertyChangedEventArgs args)	// The effective value has changed
{
	if (*args.get_Property()->m_name == L"Template")
	{
		if (m_VisualTree)
		{
			RemoveVisualChild(m_VisualTree);
			//m_VisualTree->SetRParent(NULL);
			m_VisualTree = NULL;
		}

		/*
		m_VisualTree = (UIElement*)GetValue(pProperty);

		if (m_VisualTree)
		{
			m_VisualTree->SetRParent(this);

			m_VisualTree->SetOwnerWindow(m_pOwnerWindow);	// must update this right ?

//			m_VisualTree->InvalidateMeasure();
//			m_VisualTree->Invalidate();
		}
		*/
	}

	FrameworkElement::OnPropertyChanged(args);

	ControlTemplate* pTemplate = get_Template();
	if (pTemplate)
	{
		UIElement* visualTree = get_VisualTree();
		if (visualTree)
		{
			ASSERT(visualTree->GetRParent() == this);

			TriggerCollection* triggers = pTemplate->get_Triggers();
			if (triggers)
			{
				unsigned int count = triggers->GetCount();
				for (unsigned int i = 0; i < count; i++)
				{
					TriggerBase* triggerbase = triggers->get_Item(i);

					Trigger* trigger = dynamic_cast<Trigger*>(triggerbase);
					if (trigger)
					{
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

								if (MenuItem* menuItem = dynamic_cast<MenuItem*>(this))
								{
									if (*dynamic_cast<StringW*>(menuItem->get_Header()) == L"Close" && value == BoolObject::get_False())
									{
										MessageBeep(-1);
									}
								}
								*/

								Setters* setters = trigger->get_Setters();

								for (int i = 0; i < setters->m_items.size(); i++)
								{
									Setter* setter = setters->m_items[i];

									StringW* targetName = setter->get_TargetName();

									FrameworkElement* child = dynamic_cast<FrameworkElement*>(visualTree->FindName(targetName));
									ASSERT(child);
									if (child)
									{
										ASSERT(IsAncestorOf(child));
										ASSERT(child->GetOwnerWindow() == GetOwnerWindow());

									//	int depPropertyIndex = setter->get_Property()->gindex;
									//	child->m_style_depproperties[depPropertyIndex] = setter;

										// TODO, check if locally set, don't need to do anything

									//	child->InvalidateProperty(setter->get_Property());
										child->SetValue(setter->get_Property(), setter->get_Value());
									}
								}
							}
						}
					}
				}
			}
		}
	}

#if 1
	PropertyChanged(args.get_Property()->m_name->ToStringA());
#endif
}

/*
// virtual
LDraw::RectD Control::GetViewBox()
{
	return LDraw::RectD(0, 0, m_computedSize.Width, m_computedHeight);
}
*/

ControlTemplate* Control::get_Template()
{
	return static_cast<ControlTemplate*>(GetValue(get_TemplateProperty()));
}

void Control::set_Template(ControlTemplate* pTemplate)
{
	SetValue(get_TemplateProperty(), pTemplate);
//	m_ControlTemplate = p;
//	EnsureVisuals();
}

#if 0
// virtual
void Control::EnsureVisuals()
{
	ASSERT(0);
#if 0
	if (m_pTemplate)
	{
#if 0
		for (int i = 0; i < m_ControlTemplate->m_propertyValues.size(); i++)
		{
			DataTemplateNode* p2 = m_ControlTemplate->m_propertyValues[i];

			DataTemplateNode* p = p2->m_properties[new StringA("Name")];

		//	Class* pType = GetType(p->m_LiteralObject);
			StringW* name = static_cast<StringW*>(p->m_LiteralObject);

		//	PropertyValue* p = static_cast<PropertyValue*>(
		//	Property* pProperty = properties[propertyName];

		//	SetValue(pDispatch, obj, pProperty->put_method, child, childnode->m_pType);

		//	Property* pProperty = properties[propertyName];

			Object* vobject;
			Type* vType;
			{
				Dispatch* pdisp2 = GetDispatch(this->GetType());
				Dispatch::propertymap_t properties;
			//	pdisp2->GetProperties(properties);
				Property* pProperty = pdisp2->GetProperty(name->ToStringA());//(Property*)properties[name->ToStringA()];

				vType = pProperty->get_GetType();//get_method->m_decl->m_pType->GetFunction()->m_pReturnType;
				vobject = (Object*)pdisp2->Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
			}

			Property* pProperty = pDispatch->GetProperty(propertyName);
			if (pProperty)//(property_it != properties.end())
			{
				SetValue(pDispatch, obj, pProperty->put_method, child, pRealType);
			//	printf("After SetValue at %s(%d)\n", __FILE__, __LINE__);
			}
			else
				ASSERT(0);
		}
#endif

		Type* pRealType;
		UI::UIElement* pVisualTree = (UI::UIElement*)DynamicCast(m_Template->m_RootNode->Create(this, &pRealType), m_ControlTemplate->m_RootNode->m_pType, typeid(UI::UIElement).GetType()/*pD->LookupNamedType(new StringA("UI::UIElement"))*/);

		ASSERT(pVisualTree);

		set_VisualTree(pVisualTree);
		UpdatedVisualTree();
	}
#endif
}
#endif

/*
// virtual
void Control::UpdatedVisualTree()
{
}
*/

// virtual
void Control::PlaceControls(PlatformWindow hWndParent)
{
	UIElement::PlaceControls(hWndParent);

	UIElement* pVisual = dynamic_cast<UIElement*>(get_VisualTree());
	if (pVisual)
	{
		pVisual->PlaceControls(hWndParent);
	}
}

// virtual
LDraw::SizeD Control::MeasureOverride(LDraw::SizeD availSize)
{
	LDraw::SizeD desiredSize;

	UIElement* visualTree = get_VisualTree();
	if (visualTree)
	{
#if 0
		ASSERT(pVisual->GetRParent() == this);
#endif
		visualTree->Measure(availSize/*LDraw::SizeD(m_desiredWidth, m_desiredHeight)*/);

		desiredSize = visualTree->get_DesiredSize();

		ASSERT(desiredSize.Width >= 0 && desiredSize.Height >= 0);

	//	TRACE("%f,%f\n", desiredSize.Width, desiredSize.Height);
	}

	return desiredSize;
//	return UIElement::OnMeasure(availSize);

#if 0
	Length* m_Width = get_Width();
	Length* m_Height = get_Height();

	if (m_Width)
	{
		double Value = m_Width->get_Value();
		if (m_Width->get_UnitType() == Length::UnitPercentage)
		{
			m_desiredWidth = Value * viewBox.Width;
		}
		else
		{
			m_desiredWidth = Value;
		}
	}
	else
	{
		m_desiredWidth = 0;//viewBox.Width;
	}

	if (m_Height)
	{
		double Value = m_Height->get_Value();
		if (m_Height->get_UnitType() == Length::UnitPercentage)
		{
			m_desiredHeight = Value * viewBox.Height;
		}
		else
		{
			m_desiredHeight = Value;
		}
	}
	else
	{
		m_desiredHeight = 0;//viewBox.Height;
	}

	if (get_VisualTree())
	{
		UIElement* pVisual = dynamic_cast<UIElement*>(m_VisualTree);

		ASSERT(pVisual->GetRParent() == this);
		pVisual->Measure(LDraw::SizeD(m_desiredWidth, m_desiredHeight));

		viewBox.Width = pVisual->m_desiredWidth;//pVisual->m_expandedBBox.Width;
		viewBox.Height = pVisual->m_desiredHeight;//pVisual->m_expandedBBox.Height;
	}

	if (m_Width)
	{
		double Value = m_Width->get_Value();
		if (m_Width->get_UnitType() == Length::UnitPercentage)
		{
			m_desiredWidth = Value * viewBox.Width;
		}
		else
		{
			m_desiredWidth = Value;
		}
	}
	/*
	else
	{
		m_desiredWidth = 0;//viewBox.Width;
	}
	*/

	if (m_Height)
	{
		double Value = m_Height->get_Value();
		if (m_Height->get_UnitType() == Length::UnitPercentage)
		{
			m_desiredHeight = Value * viewBox.Height;
		}
		else
		{
			m_desiredHeight = Value;
		}
	}
	/*
	else
	{
		m_desiredHeight = viewBox.Height;
	}
	*/

	//	m_specifiedWidth = m_computedSize.Width;
	//	m_specifiedHeight = m_computedHeight;

	/*
	m_expandedBBox.X = 0;
	m_expandedBBox.Y = 0;
	m_expandedBBox.Width = m_computedSize.Width;
	m_expandedBBox.Height = m_computedHeight;
	*/

	//UIElement::CalculateBoundsAndChildren();	// First calculate children
	//CalculateBounds();
#endif
}

LDraw::SizeD Control::ArrangeOverride(LDraw::SizeD finalSize)
{
	UIElement* visualTree = get_VisualTree();
	if (visualTree)
	{
		visualTree->Arrange(LDraw::RectD(LDraw::PointD(0,0), finalSize));

	//	m_computedSize = pVisual->m_computedSize;
	//	m_expandedBBox = pVisual->m_expandedBBox;
	}

	return finalSize;
}

void Control::AddAccel(const Accel& accel)
{
	m_accelerators.Add(accel);
}

void Control::PropertyChanged(StringA* name)
{
	Dispatch* pDispatch = GetDispatch(GetType());

	map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator>::iterator it = m_objectpropertymap.find(name);
	if (it != m_objectpropertymap.end())
	{
		Type* propertyType;
		Object* propertyValue;
		{
			Property* pProperty = pDispatch->GetProperty(name);
			propertyType = pProperty->get_GetType();

			switch (propertyType->get_Kind())
			{
			case type_double:
				{
					double val = pDispatch->double_Invoke(this, pProperty->get_GetMethod(), NULL, 0);
					propertyValue = DoubleObject::GetObject(val);
				}
				break;

			default:
				{
					propertyValue = pDispatch->Object_Invoke(this, pProperty->get_GetMethod(), NULL, 0);
					propertyType = propertyType->GetPointerTo();
				}
			}

		//	propertyValue = pDispatch->Object_Invoke(this, pProperty->get_GetMethod(), NULL, 0);
		//	propertyType = propertyType->GetPointerTo();
			// TODO, convert primitives to objects
		}

		ObjectProperty& objectproperty = (*it).second;

		Dispatch* pDispatch = GetDispatch(objectproperty.m_object->GetType());
		Property* pProperty = pDispatch->GetProperty(objectproperty.m_propertyName);
	//	printf("PropertyChanged calling SetValue() for method %s\n", pProperty->get_SetMethod()->get_MethodName()->c_str());

		pDispatch->SetValue(objectproperty.m_object, pProperty->get_SetMethod(), (Object*)propertyValue, propertyType);
	}
}

unsigned int Control::get_VisualChildrenCount()
{
	return m_VisualTree != NULL? 1: 0;
}

Visual* Control::GetVisualChild(unsigned int index)
{
	if (m_VisualTree == NULL || index != 0)
	{
		throw std::exception("Index out of range");
	}

	return m_VisualTree;
}

void Control::Do(Object* sourceObject)
{
	map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator>::iterator it = m_objectpropertymap.begin();
	while (it != m_objectpropertymap.end())
	{
		StringA* name = it->first;
		ObjectProperty& objectproperty = (*it).second;

		Type* propertyType;
		Object* propertyValue;
		if (*name == "/")	// The value is the templated object itself, and not one of its properties
		{
			propertyValue = sourceObject;
			propertyType = propertyValue->GetType();
		}
		else
		{
			Dispatch* pDispatch = GetDispatch(sourceObject->GetType());
			Property* pProperty = pDispatch->GetProperty(name);
			propertyType = pProperty->get_GetType();

			switch (propertyType->get_Kind())
			{
			case type_double:
				{
					double val = pDispatch->double_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
					propertyValue = DoubleObject::GetObject(val);
				}
				break;

			case type_bool:
				ASSERT(0);
				break;

			default:
				{
					propertyValue = pDispatch->Object_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
					propertyType = propertyType->GetPointerTo();
				}
			}
		}

		Dispatch* pDispatch = GetDispatch(objectproperty.m_object->GetType());
		Property* pProperty = pDispatch->GetProperty(objectproperty.m_propertyName);
		pDispatch->SetValue(objectproperty.m_object, pProperty->set_method, propertyValue, propertyType);

		++it;
	}
}

void ContentPresenter::Do(Object* sourceObject)
{
	map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator>::iterator it = m_objectpropertymap.begin();
	while (it != m_objectpropertymap.end())
	{
		StringA* name = it->first;
		ObjectProperty& objectproperty = (*it).second;

		Type* propertyType;
		Object* propertyValue;
		if (*name == "/")	// The value is the templated object itself, and not one of its properties
		{
			propertyValue = sourceObject;
			propertyType = propertyValue->GetType();
		}
		else
		{
			Dispatch* pDispatch = GetDispatch(sourceObject->GetType());
			Property* pProperty = pDispatch->GetProperty(name);
			propertyType = pProperty->get_GetType();

			switch (propertyType->get_Kind())
			{
			case type_double:
				{
					double val = pDispatch->double_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
					propertyValue = DoubleObject::GetObject(val);
				}
				break;

			case type_bool:
				ASSERT(0);
				break;

			default:
				{
					propertyValue = pDispatch->Object_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
					propertyType = propertyType->GetPointerTo();
				}
			}
		}

		Dispatch* pDispatch = GetDispatch(objectproperty.m_object->GetType());
		Property* pProperty = pDispatch->GetProperty(objectproperty.m_propertyName);
		pDispatch->SetValue(objectproperty.m_object, pProperty->set_method, propertyValue, propertyType);

		++it;
	}
}

void ItemsPresenter::Do(Object* sourceObject)
{
	map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator>::iterator it = m_objectpropertymap.begin();
	while (it != m_objectpropertymap.end())
	{
		StringA* name = it->first;
		ObjectProperty& objectproperty = (*it).second;

		Type* propertyType;
		Object* propertyValue;
		if (*name == "/")	// The value is the templated object itself, and not one of its properties
		{
			propertyValue = sourceObject;
			propertyType = propertyValue->GetType();
		}
		else
		{
			Dispatch* pDispatch = GetDispatch(sourceObject->GetType());
			Property* pProperty = pDispatch->GetProperty(name);
			propertyType = pProperty->get_GetType();

			switch (propertyType->get_Kind())
			{
			case type_double:
				{
					double val = pDispatch->double_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
					propertyValue = DoubleObject::GetObject(val);
				}
				break;

			case type_bool:
				ASSERT(0);
				break;

			default:
				{
					propertyValue = pDispatch->Object_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
					propertyType = propertyType->GetPointerTo();
				}
			}
		}

		Dispatch* pDispatch = GetDispatch(objectproperty.m_object->GetType());
		Property* pProperty = pDispatch->GetProperty(objectproperty.m_propertyName);
		pDispatch->SetValue(objectproperty.m_object, pProperty->set_method, propertyValue, propertyType);

		++it;
	}
}

UIElement* Control::get_VisualTree()
{
	ASSERT(this);

	if (m_VisualTree == NULL)
	{
		/*
		if (dynamic_cast<ScrollBar*>(this))
		{
			MessageBeep(-1);
		}
		*/

		ControlTemplate* pTemplate = get_Template();
		if (pTemplate)
		{

#if 1
			m_objectpropertymap.clear();

			// TODO, clear this
			ASSERT(m_objectpropertymap.size() == 0);
#endif
			Type* pRealType;
			Object* obj = pTemplate->get_VisualTree()->Create4(this, &pRealType, this, m_objectpropertymap);
			m_VisualTree = dynamic_cast<UIElement*>(obj);
			if (m_VisualTree)
			{
				AddVisualChild(m_VisualTree);
				/*
				m_VisualTree->SetRParent(this);
				m_VisualTree->SetOwnerWindow(GetOwnerWindow());
				*/
			}

			//Object* sourceObject = this;
			Do(this);

			OnApplyTemplate();

		//	SetProperties();
		//	UpdatedVisualTree();
		}
	}

#if 0
//	printf("UIElement::get_VisualTree()\n");
//	return m_VisualTree;
	Object* pObject = GetValue(VisualTreeProperty);

	VERIFY(m_VisualTree == pObject);

	if (pObject)
	{
	/*
	if (m_VisualTree == NULL)
	{
		m_VisualTree = (UIElement*)pObject;

		if (m_VisualTree)
		{
			m_VisualTree->SetRParent(this);

			m_VisualTree->SetOwnerWindow(m_pOwnerWindow);	// must update this right ?

//			m_VisualTree->InvalidateMeasure();
//			m_VisualTree->Invalidate();
		}
	}
	else
	*/
		VERIFY(m_VisualTree->GetRParent() == this);
		VERIFY(m_VisualTree->get_OwnerWindow() == get_OwnerWindow());
	}
#endif

	return m_VisualTree;
}

Visual* Control::HitTestElement(LDraw::Matrix3f* matrix, LDraw::PointD pt)
{
	/*
	gmMatrix3 matrix2 = GetLocalAnimatedMatrix() * matrix;

	LDraw::PointD xpt = matrix2.inverse().transform(pt);

	if (m_expandedBBox.Contains(xpt.X, xpt.Y))
	{
		if (m_VisualTree)
		{
			UIElement* pVisual = dynamic_cast<UIElement*>(m_VisualTree);

			return pVisual->HitTestElement(matrix2, pt);
		}
	}
	*/

	return UIElement::HitTestElement(matrix, pt);
}

Mover::Mover()
{
	m_dragging = 0;
}

Sizer::Sizer()
{
#if 0//WIN32
	set_Cursor(new Cursor(MSWindows::LoadCursorA(NULL, _IDC_SIZENWSE)));
#endif

	m_dragging = 0;

//	put_BackgroundBrush(new SolidColorBrush(Color(100, 100, 190)));
	{
		Shapes::Polyline* p = new Shapes::Polyline;
		PointCollection* points = new PointCollection;

		points->Add(Point(16, 0));
		points->Add(Point(16, 16));
		points->Add(Point(0, 16));

		p->set_Fill(new SolidColorBrush(Color::FromRgb(82, 116, 167)));

		p->set_Points(points);

		set_VisualTree(p);
	}
}

////////////////////////////////////////////////////////////////////////
// Mover

#if 0
void Mover::handleEvent(Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != CAPTURING_PHASE)
	{
		if (type == MouseEvent::mousedown)
		{
			MouseEvent* mouseevt = static_cast<MouseEvent*>(evt);

			/*
			Point* point = mouseevt->GetPosition(this);
			m_oldPoint.X = point->get_X();
			m_oldPoint.Y = point->get_Y();
			*/

			if (true)
			{
				oldx = mouseevt->get_ScreenX();
				oldy = mouseevt->get_ScreenY();

			//	m_path.AddMove(LDraw::PointF(point->get_X(), point->get_Y()));
				m_dragging = true;

				CaptureMouse();
			}
			else
			{
				/*
				m_npt = -1;
				for (int i = 0; i < m_path.m_points.size(); i++)
				{
					LDraw::PointF point = m_path.m_points[i];

					if (fabs(m_oldPoint.X - point.X) < 4 && fabs(m_oldPoint.Y - point.Y) < 4)
					{
						m_npt = i;
						break;
					}
				}

				if (m_npt >= 0)
				{
					m_dragging = true;
				}
				*/
			}
			evt->stopPropagation();
		}
		else if (type == MouseEvent::mouseup)
		{
			//OnLButtonUp(dynamic_cast<MouseEvent*>(evt));
			ReleaseMouseCapture();
			evt->stopPropagation();
			m_dragging = false;
		}
		else if (type == MouseEvent::mousemove)
		{
			evt->stopPropagation();
			MouseEvent* mouseevt = static_cast<MouseEvent*>(evt);
			//OnMouseMove(dynamic_cast<MouseEvent*>(evt));
			if (m_dragging)
			{
			//	MessageBeep(-1);

			//	printf("Mover::mousemove\n");

				long dx = mouseevt->get_ScreenX() - oldx;
				long dy = mouseevt->get_ScreenY() - oldy;

//				printf("Mover\n");

				UIElement* window = NULL;

				{
					Visual* pParent = GetRParent();
					while (pParent)
					{
						window = dynamic_cast<ChildWindow*>(pParent);
						if (window)
						{
							break;
						}

						pParent = pParent->GetRParent();
					}
				}

				if (window)
				{
					Canvas::SetLeft(window, Canvas::GetLeft(window) + dx);
					Canvas::SetTop(window, Canvas::GetTop(window) + dy);

				//	window->SetPosition(Canvas::GetLeft(window)->get_Value(), Canvas::GetTop(window)->get_Value());
				}

				oldx = mouseevt->get_ScreenX();
				oldy = mouseevt->get_ScreenY();

			//	Invalidate();
#if 0
				Point* point = mouseevt->GetPosition(this);

				if (point->get_X() != m_oldPoint.X || point->get_Y() != m_oldPoint.Y)
				{
				//m_points.push_back(LDraw::Point(point->get_X(), point->get_Y()));
					if (TRUE)
					{
						m_path.AddLine(LDraw::PointF(point->get_X(), point->get_Y()));
					}
					else
					{
						m_path.m_points[m_npt].X = point->get_X();
						m_path.m_points[m_npt].Y = point->get_Y();
					}

					m_oldPoint.X = point->get_X();
					m_oldPoint.Y = point->get_Y();

					printf("Here\n");
					Invalidate();
				}
#endif
			}
		}
	}
}
#endif

void Sizer::OnMouseDown(MouseButtonEventArgs* args)
{
//	MouseEvent* mouseevt = static_cast<MouseEvent*>(evt);

	/*
	Point* point = mouseevt->GetPosition(this);
	m_oldPoint.X = point->get_X();
	m_oldPoint.Y = point->get_Y();
	*/

	if (true)
	{
		double screenX = args->GetScreenPosition().X;
		double screenY = args->GetScreenPosition().Y;

		m_oldx = screenX;
		m_oldy = screenY;

	//	Point* point = mouseevt->GetPosition(this);

	//	m_path.AddMove(LDraw::PointF(point->get_X(), point->get_Y()));

		ChildWindow* window = NULL;
		UIElement* pParent = dynamic_cast<UIElement*>(GetRParent());
		while (pParent)
		{
			window = dynamic_cast<ChildWindow*>(pParent);
			if (window)
			{
				break;
			}
			pParent = dynamic_cast<UIElement*>(pParent->GetRParent());
		}

		if (window)
		{
			m_dragging = true;

			CaptureMouse();

			m_size = window->get_ActualSize();
		}
		else
		{
#if WIN32
			HwndSource* pOwnerWindow = dynamic_cast<HwndSource*>(GetOwnerWindow()->m_pSite);
			if (pOwnerWindow)
			{
				MSWindows::Hwnd hwnd = pOwnerWindow->GetHwnd();
				hwnd.SendMessage(WM_NCLBUTTONDOWN, HTBOTTOMRIGHT/*HTSIZE*/, MSWindows::MakeLPARAM(screenX, screenY));
			}
#endif
		}
	}
	else
	{
		/*
		m_npt = -1;
		for (int i = 0; i < m_path.m_points.size(); i++)
		{
			LDraw::PointF point = m_path.m_points[i];

			if (fabs(m_oldPoint.X - point.X) < 4 && fabs(m_oldPoint.Y - point.Y) < 4)
			{
				m_npt = i;
				break;
			}
		}

		if (m_npt >= 0)
		{
			m_dragging = true;
		}
		*/
	}
}

void Sizer::OnMouseUp(MouseButtonEventArgs* args)
{
	if (m_dragging)
	{
		//OnLButtonUp(dynamic_cast<MouseEvent*>(evt));
		ReleaseMouseCapture();
		m_dragging = false;
	}
}

void Sizer::OnMouseMove(MouseEventArgs* args)
{
//	MouseEvent* mouseevt = dynamic_cast<MouseEvent*>(evt);
	//OnMouseMove(dynamic_cast<MouseEvent*>(evt));
	if (m_dragging)
	{
		double screenX = args->GetScreenPosition().X;
		double screenY = args->GetScreenPosition().Y;

		double dx = screenX - m_oldx;
		double dy = screenY - m_oldy;

		m_size.Width += dx;
		m_size.Height += dy;

//				printf("Sizer\n");

		ChildWindow* window = NULL;
		Visual* pParent = GetRParent();
		while (pParent)
		{
			window = dynamic_cast<ChildWindow*>(pParent);
			if (window)
			{
				break;
			}
			pParent = pParent->GetRParent();
		}

		if (window)
		{
			//window->Invalidate();

			window->set_Width(m_size.Width);
			window->set_Height(m_size.Height);

		//	window->m_width = new Length(m_size.Width);
		//	window->m_height = new Length(m_size.Height);
		//	window->InvalidateMeasure();
			/*
			window->SetPositionAndSize(window->m_expandedBBoxParent.X, window->m_expandedBBoxParent.Y, m_size.Width, m_size.Height);
			*/
#if 0
			// TODO
			window->InvalidateMeasure();
		//	window->SetLayoutOffset(window->m_computedLeft, window->m_computedTop);
		//	window->CalculateBoundsAndChildren(LDraw::SizeD(0,0));
		//	window->Arrange(window->m_desiredSize);
		//	window->RecalculateParentBounds();
#endif


		//	window->Invalidate();
		}

		m_oldx = screenX;
		m_oldy = screenY;

	//	Invalidate();
	}
}

}	// UI
}
