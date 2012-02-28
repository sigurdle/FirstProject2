#include "stdafx.h"
#include "LXUI2.h"

#include "SolidColorBrush.h"
#include "LinearGradientBrush.h"
#include "Grid.h"

#include "Track.h"	// TODO remove

//#include <stdio.h>	// TODO remove

namespace System
{

// This version assumes c is a legal hex digit
static int Hex2Number(WCHAR c)
{
	ASSERT(std::isxdigit(c));

	if (c <= '9')
		return c - '0';
	else
		return 10 + std::tolower(c) - 'a';
}

ErrorCode ParseRGBColor(/*[in]*/ const WCHAR* p, /*[out]*/ const WCHAR** pp, /*[out,retval]*/ LDraw::Color* pVal)
{
	ASSERT(pVal != NULL);
	ASSERT(pp != NULL);
	*pp = NULL;

	if (*p == '#')
	{
		p++;

		const WCHAR* s = p;
		while (*p && std::isxdigit(*p))
		{
			p++;
		}

		if (p-s == 3)
		{
			*pp = p;

			*pVal = LDraw::Color(255,
							(Hex2Number(s[0])<<4) | Hex2Number(s[0]),
							(Hex2Number(s[1])<<4) | Hex2Number(s[1]),
							(Hex2Number(s[2])<<4) | Hex2Number(s[2]));

			return 0;
		}
		else if (p-s == 6)
		{
			*pp = p;

			*pVal = LDraw::Color(255,
							(Hex2Number(s[0])<<4) | Hex2Number(s[1]),
							(Hex2Number(s[2])<<4) | Hex2Number(s[3]),
							(Hex2Number(s[4])<<4) | Hex2Number(s[5]));

			return 0;
		}
	}
	else if ((p[0] == 'r') && (p[1] == 'g') && (p[2] == 'b'))
	{
		p += 3;

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L'(') return -1;	// Error

		while (*p && *p == L' ') p++;	// Skip spaces
		double red = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			red = red * 255 / 100;
		}
		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double green = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			green = green * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double blue = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			blue = blue * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L')') return -1;	// Error

		*pp = p;

		if (red < 0) red = 0;
		else if (red > 255) red = 255;

		if (green < 0) green = 0;
		else if (green > 255) green = 255;

		if (blue < 0) blue = 0;
		else if (blue > 255) blue = 255;

		*pVal = LDraw::Color(255, (uint8)red, (uint8)green, (uint8)blue);
		return 0;
	}
	else	// Named color
	{
		// TODO, smarter search given that array is sorted
		// TODO, make one array only
		int i = 0;

		ASSERT(0);

#if 0
		while (ColorNames[i].name)
		{
			int len = wcslen(ColorNames[i].name);

			if (!wcsncmp(ColorNames[i].name, p, len))
			{
				*pp = p + len;
				*pVal = ColorNames[i].clr | 0xff000000;
				return 0;
			}

			i++;
		}

		i = 0;
		while (SystemColors[i].name)
		{
			int len = wcslen(SystemColors[i].name);

			if (!wcsncmp(SystemColors[i].name, p, len))
			{
				*pp = p + len;
				*pVal = SystemColors[i].clr | 0xff000000;
				return 0;
			}

			i++;
		}
#endif
	}

	return -1;
}

ErrorCode ParseRGBAColor(/*[in]*/ const WCHAR* p, /*[out]*/ const WCHAR** pp, /*[out,retval]*/ LDraw::Color* pVal)
{
	if ((p[0] == 'r') && (p[1] == 'g') && (p[2] == 'b') && (p[3] == 'a'))
	{
		p += 4;

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L'(') return -1;	// Error

		while (*p && *p == L' ') p++;	// Skip spaces
		double red = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			red = red * 255 / 100;
		}
		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double green = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			green = green * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double blue = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			blue = blue * 255 / 100;
		}

		while (*p && *p == L' ') p++;	// Skip spaces
		if (*p++ != L',') return -1;

		while (*p && *p == L' ') p++;	// Skip spaces
		double alpha = getfnumber(&p);
		if (p == NULL) return -1;
		if (*p == L'%')
		{
			p++;
			alpha = alpha * 255 / 100;
		}
		else
		{
			alpha *= 255;	// ?? TODO: Not sure, check what CSS does
		}

		while (*p && *p == L' ') p++;	// Skip spaces

		if (*p++ != L')') return -1;	// Error

		*pp = p;

		if (red < 0) red = 0;
		else if (red > 255) red = 255;

		if (green < 0) green = 0;
		else if (green > 255) green = 255;

		if (blue < 0) blue = 0;
		else if (blue > 255) blue = 255;

		if (alpha < 0) alpha = 0;
		else if (alpha > 255) alpha = 255;

		*pVal = LDraw::Color((uint8)alpha, (uint8)red, (uint8)green, (uint8)blue);
		return 0;
	}
	else
	{
		return ParseRGBColor(p, pp, pVal);
	}
}

ErrorCode ParseSingleRGBAColor(/*[in]*/ const WCHAR* p, /*[out,retval]*/ LDraw::Color* pVal)
{
	LDraw::Color clr;
	const WCHAR* pp;
	if (ParseRGBAColor(p, &pp, &clr) >= 0)
	{
		if (*pp == 0)	// End of string
		{
			if (pVal)
			{
				*pVal = clr;
			}

			return 0;
		}
	}

	return -1;
}

LFCEXT StringA* getparts(const char * p);

}

namespace System
{
namespace UI
{

Brush* ParseBrush(StringW* textdata)
{
	if (!std::wcsncmp(textdata->c_str(), L"HorizontalGradientBrush ", 24))
	{
		const WCHAR* str = textdata->c_str() + 24;

		while (std::isspace(*str)) str++;
		LDraw::Color startColor;
		ParseRGBAColor(str, &str, &startColor);

		while (std::isspace(*str)) str++;
		LDraw::Color endColor;
		ParseRGBAColor(str, &str, &endColor);

		return new UI::LinearGradientBrush(startColor, endColor, Point(0, 0), Point(1, 0));
	}
	else if (!std::wcsncmp(textdata->c_str(), L"VerticalGradientBrush ", 22))
	{
//printf("here %d\n", __LINE__);
		const WCHAR* str = textdata->c_str() + 22;

		while (std::isspace(*str)) str++;
		LDraw::Color startColor;
		ParseRGBAColor(str, &str, &startColor);

		while (std::isspace(*str)) str++;
		LDraw::Color endColor;
		ParseRGBAColor(str, &str, &endColor);

		return new UI::LinearGradientBrush(startColor, endColor, Point(0, 0), Point(0, 1));
	}
	else
	{
//	printf("here %d\n", __LINE__);
		LDraw::Color color;
		const WCHAR* pp;
		ErrorCode res = ParseRGBAColor(textdata->c_str(), &pp, &color);
		if (res == 0)
		{
			while (std::isspace(*pp)) pp++;

			double opacity = 1;
			if (*pp == ',')
			{
				pp++;
				while (std::isspace(*pp)) pp++;
				opacity = getfnumber(pp);
			}
			else if (*pp != 0)
			{
				ASSERT(0);
			}
			return new UI::SolidColorBrush(Color(color), opacity);
		}
		else
		{
			// TODO
			ASSERT(0);
		}
	}

	return NULL;
}

struct token
{
	enum
	{
		tok_eof = 0,
		tok_double,
		tok_symbol,
	}
	kind;

	union
	{
		int symbolVal;
		double doubleVal;
	}
	u;

	operator double () const
	{
		if (kind != tok_double)
			throw std::exception("Expected number");

		return u.doubleVal;
	}
};

static const WCHAR* p;
static token curtok;

void adv()
{
	while (*p == ' ')
		p++;

	if (*p)
	{
		if (std::isdigit(*p) || *p == '-' || *p == '+')
		{
			curtok.u.doubleVal = getfnumber(&p);
			curtok.kind = token::tok_double;
		}
		else
		{
			ASSERT(0);
		}
	}
	else
	{
		curtok.kind = token::tok_eof;
	}
}

Thickness* ParseThickness(StringW* textdata)
{
	p = textdata->c_str();
	double num[4];
	
	adv();
	num[0] = (double)curtok;

	adv();
	if (curtok.kind != token::tok_eof)
	{
		num[1] = (double)curtok;

		adv();
		num[2] = (double)curtok;

		adv();
		num[3] = (double)curtok;
	}
	else
	{
		num[1] = num[0];
		num[2] = num[0];
		num[3] = num[0];
	}

	return new Thickness(num[0], num[1], num[2], num[3]);
}

StringW* PropertyValue::get_Name()
{
	return m_property;
}

void PropertyValue::set_Name(StringW* value)
{
	m_property = value;
}

FrameworkTemplate::FrameworkTemplate()
{
	m_RootNode = NULL;
}

DependencyObject* FrameworkTemplate::LoadContent()
{
	ASSERT(0);
	return NULL;
//	Type* pType;
//	m_pRootNode->Create4(NULL, &pType, 
}

#if 0
void SetValue(Dispatch* dispatch, void* _this, Method* method, Object* pObject, Type* pSourceType)
{
	dispatch->SetValue(_this, method, pObject, pSourceType);
#if 0
	printf("SetValue...\n");

	Type* ArgType = method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0].m_pType->GetStripped();
	if (ArgType->get_Kind() == type_class)
	{
		PointerType* pPointerType = new PointerType(/*type_pointer,*/ pSourceType);
	//	pPointerType->AddRef();

		Conv* pConv = Convert(pPointerType, ArgType, 0);
		if (pConv == NULL)
		{
			StringA* sourceTypeString = pSourceType->ToString();

			printf("Couldn't convert from %s to %s\n", sourceTypeString->c_str(), ArgType->GetClass()->m_qname->c_str());
			VERIFY(0);
		}
		void * newObject = DoConvert(pObject, pConv);
		//TRACE("\n");
		if (newObject)
	//	if (true)
		{
			/*
			if (method->m_decl->m_name == "put_BorderThickness")
			{
				printf("cheat\n");

			//	Thickness thickness;

				_Thickness* p = new _Thickness;

				Thickness* th = &thickness;
				Thickness thickness(p);

				dispatch->Invoke(_this, method, &th, 4);
			}
			else
				*/
			{
				printf("real thing\n");
#if WIN32
				dispatch->Invoke(_this, method, newObject, ArgType->get_sizeof());
#else
				dispatch->Invoke(_this, method, &newObject, 4);
#endif
				delete (uint8*)newObject;
			}
		}
		else
		{
			MessageBoxA(NULL, "Failed to convert", "", MB_OK);
		}
		printf("done convert\n");
	}
	else if (ArgType->get_Kind() == type_pointer)
	{
		ArgType = ArgType->GetPointerTo()->GetStripped();

//		ASSERT(pSourceType->m_type == type_pointer);
		if (ArgType->get_Kind() == type_class)
		{
			void* properType;
			if (pObject)
			{
			//	Class* psrc = GetType(pObject);	// debug
			//	ASSERT(psrc->m_qname == ((Class*)pSourceType)->m_qname);	// debug
				
				properType = DynamicCast(pObject, pSourceType/*->GetPointerTo()*/, ArgType);
			}
			else
				properType = NULL;

			dispatch->Invoke(_this, method, &properType, 4);
		}
		else
		{
			ASSERT(0);
		}
	}
	else if (ArgType->get_Kind() == type_double)
	{
		double value = ((DoubleObject*)pObject)->GetValue();
		dispatch->Invoke(_this, method, &value, 8);
	}
	else
	{
		unsigned int size = ArgType->get_sizeof();

		// TODO not sure about this ?

		void* arg = (void*)(pObject+1);	// skip virtual table

#if WIN32
		size = (size + 3) & ~3;	// aligned on 4 bytes
#else
		size = (size + 1) & ~1;	// aligned on 2 bytes
#endif
		dispatch->Invoke(_this, method, arg, size);
	}
#if 0
		if (ArgType->m_type == type_enum)
	{
		dispatch->Invoke(_this, method, pObject, 4);
	}
	else if (ArgType->m_type == type_unsigned_char)
	{
		dispatch->Invoke(_this, method, pObject, 4);
	}
	else if (ArgType->m_type == type_float)
	{
		dispatch->Invoke(_this, method, pObject, 4);
	}
	else if (ArgType->m_type == type_double)
	{
		dispatch->Invoke(_this, method, pObject, 8);
	}
	else if (ArgType->m_type == type_bool)
	{
		// TODO
		ASSERT(0);
		/*
		IntObject* iobject = dynamic_cast<IntObject*>(pObject);
		long lval = *iobject;

		dispatch.Invoke(method, &lval, 4);
		*/

	}
	else
		ASSERT(0);
#endif

	printf("done SetValue\n");
#endif
}
#endif

void ParsePointList(PointCollection* points, StringW* s)
{
//	RemoveAll();

	const WCHAR* p = s->c_str();

	while (std::isspace(*p)) p++;

	while (*p)
	{
		double x = getfnumber(&p);
		if (p == NULL)
		{
			break;
		}

		while (std::isspace(*p)) p++;

		if (*p == ',') p++;
		while (std::isspace(*p)) p++;

		double y = getfnumber(&p);
		if (p == NULL)
		{
			break;
		}

		while (std::isspace(*p)) p++;

		if (*p == ',') p++;
		while (std::isspace(*p)) p++;

		points->Add(Point(x, y));
	}
}

StringA* GetContentPropertyName(ClassType* pType)
{
	for (int i = 0; i < pType->m_attributes.size(); i++)
	{
		ContentPropertyAttribute* contentPropertyAttribute = dynamic_cast<ContentPropertyAttribute*>(pType->m_attributes[i]);
		if (contentPropertyAttribute)
		{
			return contentPropertyAttribute->m_propertyName;
		}
	}

	if (pType->m_bases.size())
		return GetContentPropertyName(pType->m_bases[0]->m_pClass->GetClass());

	return NULL;

	/*
	if (pType->IsDerivedFrom((ClassType*)typeid(Panel).GetType()))
	{
		return ASTR("Children");
	}
	else if (pType->IsDerivedFrom((ClassType*)typeid(Decorator).GetType()))
	{
		return ASTR("Child");
	}
	else if (pType->IsDerivedFrom((ClassType*)typeid(ContentControl).GetType()))
	{
		return ASTR("Content");
	}
	else
		return NULL;
		*/
}

StringA* GetClassName(StringW* namespaceURI, StringW* localName)
{
	if (*localName == L"DataTemplate")
	{
		MessageBeep(-1);
	}

	if (*namespaceURI == L"http://www.lerstad.com/ui" ||
		*namespaceURI == L"http://schemas.microsoft.com/winfx/2006/xaml/presentation")
	{
		if (*localName == L"Storyboard" ||
			*localName == L"ParallelTimeline" ||
			*localName == L"DoubleAnimation" ||
			*localName == L"DoubleAnimationUsingKeyFrames" ||
			*localName == L"ColorAnimation" ||
			*localName == L"ColorAnimationUsingKeyFrames")
		{
			char buffer[512];
			sprintf_s(buffer, "System::UI::Media::%.*S", localName->Length(), localName->GetData());
			return new StringA(string_copy(buffer));
		}
		else if (*localName == L"Polygon" ||
			*localName == L"Polyline" ||
			*localName == L"Ellipse" ||
			*localName == L"Rectangle" ||
			*localName == L"Line")
		{
			char buffer[512];
			sprintf_s(buffer, "System::UI::Shapes::%.*S", localName->Length(), localName->GetData());
			return new StringA(string_copy(buffer));
		}
		else if (*localName == L"ColumnDefinition" ||
					*localName == L"RowDefinition")
		{
			char buffer[512];
			sprintf_s(buffer, "System::UI::Grid::%.*S", localName->Length(), localName->GetData());
			return new StringA(string_copy(buffer));
		}
		else if (*localName == L"Binding")
		{
			char buffer[512];
			sprintf_s(buffer, "System::UI::Data::%.*S", localName->Length(), localName->GetData());
			return new StringA(string_copy(buffer));
		}
		else
		{
			char buffer[512];
			sprintf_s(buffer, "System::UI::%.*S", localName->Length(), localName->GetData());
			return new StringA(string_copy(buffer));
		}
	}
	else
		throw new Exception(WSTR("Unknown namespace"));
#if 0

	int len = tagName->Length();
	const WCHAR* p = tagName->begin();
	BufferImp<char> buffer;
	StringBuilderA strbuilder(&buffer);
	while (len--)
	{
		//fprintf(stdout, "%c", (char)*p);

		if (*p == '.')
		{
			strbuilder << "::";
		}
		else
		{
			ASSERT((uint32)*p >= 0 && (uint32)*p < 128);
			strbuilder << (char)*p;
		}

		p++;
	}

	//fprintf(stdout, "\n");

	return buffer.DetachToString();
#endif
}

TemplateNode* FrameworkTemplate::CreateElement2(Type* pArgType, XmlData::Node* node)
{
//	printf("CreateElement2()\n");

	VERIFY(node);

	if (node->get_nodeType() == XmlData::NODE_ELEMENT)
	{
		XmlData::Element* element = static_cast<XmlData::Element*>(node);
	//	StringW* tagName = element->get_tagName();

		StringA* className = GetClassName(element->get_namespaceURI(), element->get_localName());

	//	printf("%s %d\n", className->c_str(), className->Length());

		NamedType* pType = pD->LookupNamedType(className);
		if (pType == NULL)
		{
			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			strbuilder << "Couldn't find type ";
			strbuilder << *className;
			MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
			ASSERT(0);
			return NULL;
		}

#if 0
		if (*className == "UI::Binding")
		{
			TemplateNode* templatenode = new TemplateNode(this);
			templatenode->m_pType = pArgType;
			//templatenode->m_pType = pType;

			Type* pReturnType;
			templatenode->m_pBinding = static_cast<UI::Binding*>((Object*)CreateElement(pType, node, &pReturnType));

			return templatenode;
		}
#endif

		if (pType)
		{
			TemplateNode* templatenode = new TemplateNode(this);
			templatenode->m_pType = pType;
			//templatenode->m_pType = pType;

			Dispatch* dispatch = GetDispatch(pType->GetClass());
		//	Dispatch::propertymap_t properties;
		//	dispatch->GetProperties(properties);

			XmlData::NamedNodeMap* attributes = element->get_attributes();
			int nattributes = attributes->get_length();
			for (int i = 0; i < nattributes; i++)
			{
				XmlData::Attr* attr = static_cast<XmlData::Attr*>(attributes->item(i));
				StringA* name = attr->get_nodeName()->ToStringA();

			//	StringA methodName = "put_";
			//	methodName += name;

						//printf("hello1\n");

						Property* pProperty = dispatch->GetProperty(name);

			//	Dispatch::propertymap_t::iterator property_it = properties.find(name);
			//	if (property_it != properties.end())
						if (pProperty)
				{
						//printf("hello4\n");

					Type* ArgType = pProperty->get_SetType();//(*property_it).second->put_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType;
					ArgType = ArgType->GetStripped();

					XmlData::Node* firstChild = attr->get_firstChild();
					if (firstChild)
					{
						TemplateNode* pObject2 = CreateElement2(ArgType, firstChild);
						ASSERT(pObject2);
						//printf("dggd %d\n", __LINE__);
						templatenode->m_properties.insert(TemplateNode::template_propertymap_t::value_type(name, pObject2));
					}
					else
					{
						MessageBoxA(NULL, "attribute was empty", "", MB_OK);
					}
				}
				else if (pType->GetClass()->IsOfType(typeid(UI::DependencyObject).GetType()/*pD->LookupNamedType(new StringA("UI::DependencyObject"))->GetClass()*/))
				{
					StringW* localName = attr->get_localName();

					StringW* namespaceURI = attr->get_namespaceURI();
					if (namespaceURI == NULL) namespaceURI = element->get_namespaceURI();

					int npunct = localName->Find('.');
					VERIFY(npunct != -1);
					StringW* className2 = localName->LeftOf(npunct);
					StringW* propertyName = localName->RightOf(npunct+1);
					StringA* className = GetClassName(namespaceURI, className2);

					NamedType* pNamedType = pD->LookupNamedType(className);
					if (pNamedType == NULL) THROW(std::exception("Couldn't find type"));
					if (pNamedType->get_Kind() != type_class) THROW(std::exception("Type is not class type"));

					ClassType* pClassType = static_cast<ClassType*>(pNamedType);

					DependencyProperty* pProperty = GetProperty(pClassType, propertyName);

					/*
					int count = GetPropertyCount();
					for (int i = 0; i < count; i++)
					{
						DependencyProperty* pProperty2 = GetProperty(i);

						printf(" %s\n", pProperty2->GetName()->ToStringA()->c_str());

						if (*pProperty2->GetName() == *attr->get_nodeName())
						{
							pProperty = pProperty2;
							break;
						}
					}
					*/

					if (pProperty)
					{
						Type* ArgType;

						if (pProperty->m_type == typeid(int))
						{
							ArgType = &System::Types::type_int;
						}
						else
						{
							ArgType = pProperty->m_type.GetType();
							VERIFY(ArgType != NULL);
						}

						ArgType = ArgType->GetStripped();
						TemplateNode* pObject2 = CreateElement2(ArgType, attr->get_firstChild());

						templatenode->m_depproperties.insert(TemplateNode::template_deppropertymap_t::value_type(pProperty, pObject2));
					//	templatenode->m_properties.insert(TemplateNode::template_propertymap_t::value_type(name, pObject2));

						/*
						if (pObject)
						{
						//	SetValue(dispatch, method, ArgType, pObject);
							pDepObject->SetValue(pProperty, pObject);
						}
						*/

						//UI::Length length(atof(ConvertS2A(value).c_str()));
						// TODO, call copy constructor
					//	dispatch.Invoke(method, &length, sizeof(length));
					//	length.Detach();	// TODO remove

						//pDepObject->SetValue(pProperty, length);
						//printf("ahrem %d\n", __LINE__);
					}
					else
					{
						BufferImp<char> buffer;
						StringBuilderA strbuilder(&buffer);
						strbuilder << "Undefined property name " << *name;
						MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
					}
				}
			}

			/*
			Property* contentProperty = NULL;
			StringA* contentPropertyName = GetContentPropertyName(pType->GetClass());
			if (contentPropertyName)
			{
				contentProperty = pDispatch->GetProperty(contentPropertyName);
			}
			*/

			XmlData::NodeList *childNodes = element->get_childNodes();
			int nchildren = childNodes->get_length();

						//printf("yoy %d\n", __LINE__);

			//printf("addr: %p\n", &typeid(IAddChild));
			//printf("%4.4s\n", typeid(IAddChild).name());

			//Type* pl = pD->LookupNamedType(new StringA("IAddChild"));
#if 0
			if (pType->GetClass()->IsOfType(typeid(IAddChild).GetType()->GetClass()))
			{
						//printf("ahrem2 %d\n", __LINE__);

				for (int i = 0; i < nchildren; i++)
				{
					XmlData::Node* node = childNodes->item(i);
					if (node->get_nodeType() == XmlData::NODE_ELEMENT)
					{
						XmlData::Element* element = static_cast<XmlData::Element*>(node);



						TemplateNode* pObject2 = CreateElement2(NULL/*??*/, element);

						//printf("children %d\n", __LINE__);

						templatenode->m_children.Add(pObject2);
					}
					else
						ASSERT(0);
				}
			}
			else
#endif
			{
				for (int i = 0; i < nchildren; i++)
				{
					XmlData::Node* node = childNodes->item(i);
					XmlData::NodeType nodeType = node->get_nodeType();
					if (nodeType == XmlData::NODE_ELEMENT)
					{
						XmlData::Element* element = static_cast<XmlData::Element*>(node);
			
						StringW* localName = element->get_localName();
						int npunct = localName->Find('.');
						if (npunct != -1)	// Property
						{
							StringW* propertyName = localName->RightOf(npunct+1);
							StringA* name = propertyName->ToStringA();

					//	StringA methodName = "put_";
					//	methodName += tagName;

							//Dispatch::propertymap_t::iterator propertyit = properties.find(name);
							Property* pProperty = dispatch->GetProperty(name);
							//if (propertyit != properties.end())
							if (pProperty)
							{
								if (pProperty->get_GetMethod() && pProperty->get_GetType()->GetStripped()->get_Kind() == type_pointer && pProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(IObjectCollection).GetType()))
								{
									TemplateNode* templatenodeChild = new TemplateNode(this);
									templatenodeChild->m_pType = pProperty->get_GetType()->GetStripped()->GetPointerTo();

									templatenode->m_properties[name] = templatenodeChild;

									XmlData::NodeList *childNodes = element->get_childNodes();
									int nchildren = childNodes->get_length();

									for (int i = 0; i < nchildren; i++)
									{
										XmlData::Node* node = childNodes->item(i);
										if (node->get_nodeType() == XmlData::NODE_ELEMENT)
										{
											XmlData::Element* element = static_cast<XmlData::Element*>(node);

											TemplateNode* pObject2 = CreateElement2(NULL/*??*/, element);

									//printf("children %d\n", __LINE__);

											templatenodeChild->m_children.Add(pObject2);
										}
									}
								}
								else
								{
									//Property* pProperty = (*propertyit).second;

									XmlData::Node* firstChild = element->get_firstChild();
									if (firstChild)
									{
							//printf("ahrem9 %d\n", __LINE__);

										Type* ArgType = pProperty->get_SetType();//put_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType;
										ArgType = ArgType->GetStripped();

										TemplateNode* pObject2 = CreateElement2(ArgType, firstChild);

									//SetValue(dispatch, method, ArgType, pObject);

										templatenode->m_properties[name] = pObject2;
									}
									else
										ASSERT(0);
								}
							}
							else //if (UI::DependencyObject* pDepObject = dynamic_cast<UI::DependencyObject*>(pObject))
							{
								ASSERT(0);
								DependencyProperty* pProperty = NULL;//GetProperty(propertyName);

								if (pProperty)
								{
									XmlData::Node* firstChild = dynamic_cast<XmlData::Node*>(element->get_firstChild());
									if (firstChild)
									{
							//printf("ahrem9 %d\n", __LINE__);

										Type* ArgType = pProperty->m_type.GetType();//get_SetType();//put_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType;
										ArgType = ArgType->GetStripped();

										TemplateNode* pObject2 = CreateElement2(ArgType, firstChild);

									//SetValue(dispatch, method, ArgType, pObject);

										templatenode->m_properties[name] = pObject2;
									}
									else
										ASSERT(0);

//									templatenode->m_properties[name] = 
								}
								else
								{
									pType->GetClass()->IsOfType(typeid(IAddChild).GetType()->GetClass());

									BufferImp<char> buffer;
									StringBuilderA strbuilder(&buffer);
									strbuilder << "Couldn't find property " << *name;
									MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
								}
							}
						}
						else
						{
							TemplateNode* pObject2 = CreateElement2(NULL/*??*/, element);

							//printf("children %d\n", __LINE__);

							templatenode->m_children.Add(pObject2);

							/*
							if (contentProperty)
							{
							}
							*/
						}
					}
					else if (nodeType == XmlData::NODE_TEXT ||
							nodeType == XmlData::NODE_CDATA_SECTION)
					{
						XmlData::CharacterData* chardata = static_cast<XmlData::CharacterData*>(node);
						StringW* data = chardata->get_data();

						TemplateNode* childtemplatenode = new TemplateNode(this);//CreateElement2(NULL/*??*/, element);

						childtemplatenode->m_pType = data->GetType();
						childtemplatenode->m_LiteralObject = data;

						//printf("children %d\n", __LINE__);

						templatenode->m_children.push_back(childtemplatenode);
					}
				}
			}

			return templatenode;
		}
	}
	else
	{
		XmlData::Text* text = static_cast<XmlData::Text*>(node);
		StringW* textdata = text->get_data();
		textdata = textdata->TrimLeft();
		textdata = textdata->TrimRight();

		if (textdata->begin()[0] == '{')
		{
			WCHAR* p = textdata->begin();
			++p;

			if (wcsncmp(p, L"StaticResource ", 15) == 0)
			{
				p += 15;

				StaticResourceExtension* extension = new StaticResourceExtension;

				WCHAR* start = p;

				while (*p != '}')
				{
					++p;
				}

				StringW* key = new StringW(string_copy(start, p-start));

				extension->set_ResourceKey(key);

				TemplateNode* node = new TemplateNode(this);
				node->m_pType = extension->GetType();//typeid(System::StringW).GetType();//pD->LookupNamedType(new StringA("System::StringW"));
				node->m_LiteralObject = extension;
			//	node->m_pType = pArgType;	// ???
			//	node->m_extension = extension;
				return node;
			}
			else
			{
				// TODO
				ASSERT(0);
			}
		}
		else
		{
			if (pArgType->get_Kind() == type_class)
			{

	#if 0
				if (*pArgType->GetClass()->m_qname == "UI::Length")
				{
				//	StringA texta = textdata.ToStringA();
					LengthUnits::LengthUnit unit;
					if (textdata->c_str()[textdata->Length()-1] == '%')
						unit = LengthUnits::Percentage;
					else
						unit = LengthUnits::Absolute;

				//printf("here %d\n", __LINE__);

					TemplateNode* node = new TemplateNode(this);
					node->m_pType = typeid(UI::Length).GetType();//pD->LookupNamedType(new StringA("UI::Length"));
					node->m_LiteralObject = new Length(getfnumber(textdata->c_str()), unit);
				//	node->m_LiteralObject->AddRef();
					//((Length*)node->m_LiteralObject)->AddRef();

				//printf("here %d\n", __LINE__);

					return node;
				}
				else
	#endif
	#if 0
					if (*pArgType->GetClass()->m_qname == "UI::Thickness")
				{
					TemplateNode* node = new TemplateNode(this);
					node->m_pType = typeid(UI::Thickness).GetType();//pD->LookupNamedType(new StringA("UI::Thickness"));
					node->m_LiteralObject = ParseThickness(textdata);//new Thickness(getfnumber(textdata->c_str()));
					return node;
				}
				/*
				else if (pType->m_pClass->m_name == "UI::Length")
				{
					StringA texta = ConvertS2A(textdata);
					Length::UnitType unit;
					if (texta[texta.Length()-1] == '%')
						unit = Length::UnitPercentage;
					else
						unit = Length::UnitAbsolute;

					return new _Length(atof(texta.c_str()), unit);
				}
				*/
			//	else if (*pArgType->GetClass()->m_qname == "System::StringW")
				else
	#endif
				if (pArgType == typeid(System::StringW).GetType())
				{
				//printf("here %d\n", __LINE__);
					TemplateNode* node = new TemplateNode(this);
					node->m_pType = typeid(System::StringW).GetType();//pD->LookupNamedType(new StringA("System::StringW"));
					node->m_LiteralObject = textdata;
				//printf("here %d\n", __LINE__);
					//((_StringW*)node->m_LiteralObject)->AddRef();
					return node;
				}
				else if (pArgType == typeid(UI::Color).GetType())
				{
				//printf("here %d\n", __LINE__);

					LDraw::Color color;
					ErrorCode res = ParseSingleRGBAColor(textdata->c_str(), &color);
					if (res < 0)
						THROW(-1);
					TemplateNode* node = new TemplateNode(this);
					node->m_pType = typeid(UI::Color).GetType();//pD->LookupNamedType(new StringA("UI::Color"));
					node->m_LiteralObject = new Color(color);
				//printf("here %d\n", __LINE__);
					//((Color*)node->m_LiteralObject)->AddRef();
					return node;
				}
				else
				{
				//	printf("unknown: %s\n", pArgType->GetClass()->m_qname->c_str());
					ASSERT(0);
				}
			}
			else if (pArgType->get_Kind() == type_enum)
			{
				//printf("here %d\n", __LINE__);
				StringA* texta = textdata->ToStringA();

				int count = ((EnumType*)pArgType)->m_deflist.GetSize();
				for (int i = 0; i < count; i++)
				{
					EnumDef& def = ((EnumType*)pArgType)->m_deflist[i];
					if (*def.m_name == *texta)
					{
						TemplateNode* node = new TemplateNode(this);
						node->m_pType = pArgType;//new PrimitiveType(type_);
						node->m_LiteralObject = IntObject::GetObject(def.m_value);//new IntObject(def.m_value);
				//printf("here %d\n", __LINE__);

						return node;//new IntObject(def.m_value);
					}
				}

				MessageBoxA(NULL, "Undefined enum value", "", MB_OK);
				THROW(-1);
			}
			else if (pArgType->get_Kind() == type_double)
			{
				//printf("here %d\n", __LINE__);
				TemplateNode* node = new TemplateNode(this);
				node->m_pType = &System::Types::type_double;
				node->m_LiteralObject = DoubleObject::GetObject(getfnumber(textdata->c_str()));
				//printf("here %d\n", __LINE__);
				return node;
			}
			else if (pArgType->get_Kind() == type_int)
			{
				TemplateNode* node = new TemplateNode(this);
				node->m_pType = &System::Types::type_int;
				node->m_LiteralObject = IntObject::GetObject(str2int(textdata->c_str()));
				return node;
			}
	#if 0
			else if (pType->m_type == type_unsigned_char)
			{
				return new IntObject(str2int(textdata.c_str()));
			}
	#endif
			else if (pArgType->get_Kind() == type_bool)
			{
				bool value;

				if (*textdata == L"1" || *textdata == L"true")
					value = true;
				else if (*textdata == L"0" || *textdata == L"false")
					value = false;
				else
					throw new Exception(WSTR("Invalid bool value"));

				TemplateNode* node = new TemplateNode(this);
				node->m_pType = &System::Types::type_bool;
				node->m_LiteralObject = BoolObject::GetObject(value);
				return node;
			}
			else if (pArgType->get_Kind() == type_pointer)
			{
				pArgType = pArgType->GetPointerTo()->GetStripped();

				if (pArgType->get_Kind() == type_class)
				{
					//StringA* classname = pArgType->GetClass()->m_qname;
					//printf("here %d\n", __LINE__);

					if (pArgType->GetClass() == typeid(System::StringW).GetType())
					//if (*classname == "System::StringW")
					{
					//	printf("here %d\n", __LINE__);
						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(System::StringW).GetType();//pD->LookupNamedType(new StringA("System::StringW"));
					//	printf("here %d\n", __LINE__);
						node->m_LiteralObject = textdata;
						return node;
					}
	#if 0
					else if (pArgType->GetClass() == typeid(UI::Length).GetType())
					{
						LengthUnits::LengthUnit unit;
						if (textdata->c_str()[textdata->Length()-1] == '%')
							unit = LengthUnits::Percentage;
						else
							unit = LengthUnits::Absolute;
					//printf("here %d\n", __LINE__);

						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::Length).GetType();//pD->LookupNamedType(new StringA("UI::Length"));
						node->m_LiteralObject = new Length(getfnumber(textdata->c_str()), unit);
					//printf("here %d\n", __LINE__);
						return node;
					}
	#endif
					else if (pArgType->GetClass() == typeid(UI::Thickness).GetType())
					{
						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::Thickness).GetType();//pD->LookupNamedType(new StringA("UI::Thickness"));
						node->m_LiteralObject = ParseThickness(textdata);
						return node;
					}
					else if (pArgType->GetClass() == typeid(UI::KeyTime).GetType())
					{
						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::KeyTime).GetType();//pD->LookupNamedType(new StringA("UI::Thickness"));

						if (*textdata == L"Uniform")
						{
							node->m_LiteralObject = KeyTime::s_Uniform;
						}
						else if (*textdata == L"Paced")
						{
							node->m_LiteralObject = KeyTime::s_Paced;
						}
						else
						{
							// TODO

							node->m_LiteralObject = KeyTime::FromTimeSpan(getfnumber(textdata->c_str()));

						}

						return node;
					}
					else if (pArgType->GetClass() == typeid(UI::PointCollection).GetType())
					{
						UI::PointCollection* pPoints = new UI::PointCollection;
						ParsePointList(pPoints, textdata);

						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::PointCollection).GetType();//pD->LookupNamedType(new StringA("UI::PointCollection"));
						node->m_LiteralObject = pPoints;
						return node;
					}
					else if (pArgType == typeid(UI::Color).GetType())
					{
						LDraw::Color color;
						const WCHAR* pp;
						ErrorCode res = ParseRGBAColor(textdata->c_str(), &pp, &color);
						if (res == 0)
						{
							/*
							while (isspace(*pp)) pp++;

							double opacity = 1;
							if (*pp == ',')
							{
								pp++;
								while (isspace(*pp)) pp++;
								opacity = getfnumber(pp);
							}
							else if (*pp != 0)
							{
								ASSERT(0);
							}
							UI::SolidColorBrush* pBrush = new UI::SolidColorBrush(new Color(color), opacity);
							*/
							UI::Color* pColor = new Color(color);
			
							TemplateNode* node = new TemplateNode(this);
							node->m_pType = typeid(UI::Color).GetType();
							node->m_LiteralObject = pColor;
			//	printf("dfgdfg %d\n", __LINE__);
			//	printf("%s\n", ((NamedType*)node->m_pType)->m_qname->c_str());
							return node;
						}
						else
						{
							// TODO
							ASSERT(0);
						}
					}
					else if (pArgType == typeid(UI::CornerRadius).GetType())
					{
						double value = getfnumber(textdata->c_str());

						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::CornerRadius).GetType();
						node->m_LiteralObject = new CornerRadius(value);
						return node;
					}
					else if (pArgType == typeid(UI::Brush).GetType())
					{
						TemplateNode* node = new TemplateNode(this);
						node->m_LiteralObject = ParseBrush(textdata);
						node->m_pType = node->m_LiteralObject->GetType();//typeid(UI::Brush).GetType();
						return node;
					}
					else if (pArgType == typeid(UI::Grid::GridLength).GetType())
					{
						Grid::GridLength::GridLengthUnit unit;
						if (textdata->c_str()[textdata->Length()-1] == '*')
							unit = Grid::GridLength::Weighted;
						else
							unit = Grid::GridLength::Absolute;

						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::Grid::GridLength).GetType();
						node->m_LiteralObject = new UI::Grid::GridLength(getfnumber(textdata->c_str()), unit);
						return node;
					}
					else if (pArgType == typeid(UI::Data::PropertyPath).GetType())
					{
						TemplateNode* node = new TemplateNode(this);
						node->m_pType = typeid(UI::Data::PropertyPath).GetType();
						node->m_LiteralObject = new UI::Data::PropertyPath(textdata);
						return node;
					}
					/*
					else if (*classname == "UI::Script")
					{
					}
					*/
					else
					{
						StringA* classname = pArgType->GetClass()->get_QName();

					//	printf("class name = %s\n", classname->c_str());
					//	printf("%p\n", typeid(System::StringW).GetType());
					//	printf("%p\n", pArgType->GetClass());
					//	printf("%s\n", ((NamedType*)typeid(System::StringW).GetType())->m_qname->c_str());
						ASSERT(0);
					}
				}
				else
				{
					std::printf("ASSERT at ArgType = pointer to %d\n", pArgType->get_Kind());
					ASSERT(0);
				}
			}
			else
			{
				std::printf("ASSERT at ArgType = %d\n", pArgType->get_Kind());

				ASSERT(0);
			}
		}
	}

	return NULL;
}

Object* CreateObjectFromElement(Type* pType, ScopeProvider* scope, Object* parentObject, XmlData::Node* node, Type** pReturnType);

void LoadXmlAttributes(Object* object, XmlData::Element* element, ScopeProvider* scope)
{
	Dispatch* pDispatch = GetDispatch(object->GetType());

	XmlData::NamedNodeMap* attributes = element->get_attributes();
	int nattributes = attributes->get_length();
	for (int i = 0; i < nattributes; i++)
	{
		XmlData::Attr* attr = static_cast<XmlData::Attr*>(attributes->item(i));
		if (attr->get_localName() == NULL)	// hm... xmlns
			continue;

		StringW* wname = attr->get_nodeName();
		StringA* name = wname->ToStringA();

		Property* pProperty = pDispatch->GetProperty(name);

	//	StringA methodName = "put_";
	//	methodName += name;

	//	const Method* method = pDispatch->GetMethod(methodName);
		if (pProperty && pProperty->set_method)
		{
			Type* ArgType = pProperty->get_SetType();//put_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0]->m_pType;
			ArgType = ArgType->GetStripped();

			if (object->GetType() == typeid(Trigger).GetType() && *attr->get_localName() == L"Value")
			{
				DependencyProperty* depproperty = dynamic_cast<Trigger*>(object)->get_Property();
				// TODO, shouldn't be necessary
				if (depproperty->m_type == typeid(bool))
					ArgType = &Types::type_bool;
				else if (depproperty->m_type == typeid(int))
					ArgType = &Types::type_int;
				else if (depproperty->m_type == typeid(double))
					ArgType = &Types::type_double;
				else
					ArgType = depproperty->m_type.GetType();

				Type* pReturnType = NULL;
				Object* pObject = CreateObjectFromElement(ArgType, scope, NULL, attr->get_firstChild(), &pReturnType);
				if (pObject)
				{
					pReturnType = typeid(Object).GetType();
					pDispatch->SetValue(object, pProperty->set_method, pObject, pReturnType);
				}
			}
			else if (object->GetType() == typeid(Setter).GetType() && *attr->get_localName() == L"Value")
			{
				DependencyProperty* depproperty = dynamic_cast<Setter*>(object)->get_Property();
				// TODO, shouldn't be necessary
				if (depproperty->m_type == typeid(bool))
					ArgType = &Types::type_bool;
				else if (depproperty->m_type == typeid(int))
					ArgType = &Types::type_int;
				else if (depproperty->m_type == typeid(double))
					ArgType = &Types::type_double;
				else
					ArgType = depproperty->m_type.GetType();

				Type* pReturnType = NULL;
				Object* pObject = CreateObjectFromElement(ArgType, scope, NULL, attr->get_firstChild(), &pReturnType);
				if (pObject)
				{
					pReturnType = typeid(Object).GetType();
					pDispatch->SetValue(object, pProperty->set_method, pObject, pReturnType);
				}
			}
			else
			{
				Type* pReturnType = NULL;
				Object* pObject = CreateObjectFromElement(ArgType, scope, NULL, attr->get_firstChild(), &pReturnType);
				if (pObject)
				{
					pDispatch->SetValue(object, pProperty->set_method, pObject, pReturnType);
				}
			}
		}
		else if (UI::DependencyObject* pDepObject = dynamic_cast<UI::DependencyObject*>(object))
		{
			StringW* namespaceURI = attr->get_namespaceURI();
			if (namespaceURI == NULL) namespaceURI = element->get_namespaceURI();

			int npunct = wname->Find('.');
			if (npunct != -1)
			{
				VERIFY(npunct != -1);
				StringW* className2 = wname->LeftOf(npunct);
				StringW* propertyName = wname->RightOf(npunct+1);
				StringA* className = GetClassName(namespaceURI, className2);

				NamedType* pNamedType = pD->LookupNamedType(className);
				if (pNamedType == NULL) THROW(std::exception("Couldn't find type"));
				if (pNamedType->get_Kind() != type_class) THROW(std::exception("Type is not class type"));

				ClassType* pClassType = static_cast<ClassType*>(pNamedType);

				DependencyProperty* pProperty = GetProperty(pClassType, propertyName);

				if (pProperty)
				{
					//__live_object_ptr<StringA> classname = new StringA(pProperty->m_type.name() + 6);

					Type* ArgType = pProperty->m_type.GetType();//pD->LookupNamedType(classname);
					ASSERT(ArgType != NULL);

					Type* pReturnType = NULL;
					void* pObject = CreateObjectFromElement(ArgType, scope, NULL, attr->get_firstChild(), &pReturnType);
					if (pObject)
					{
					//	SetValue(dispatch, method, ArgType, pObject);
						pDepObject->SetValue(pProperty, (Object*)pObject);
					}

					//UI::Length length(atof(ConvertS2A(value).c_str()));
					// TODO, call copy constructor
				//	dispatch.Invoke(method, &length, sizeof(length));
				//	length.Detach();	// TODO remove

					//pDepObject->SetValue(pProperty, length);
				}
				else
				{
					BufferImp<char> buffer;
					StringBuilderA strbuilder(&buffer);
					strbuilder << "Undefined property name " << *name;
					MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
				}
			}
		}
	}
}

namespace
{
void LoadObjectFromElement(Object* object, XmlData::Element* element, ScopeProvider* scope)
{
	ClassType* pType = object->GetType();

	ILoadXml* loadXml = dynamic_cast<ILoadXml*>(object);
	if (loadXml)
	{
		loadXml->Load(element);
	}
	else
	{
		LoadXmlAttributes(object, element, scope);

	//	Dispatch dispatch(object, pType);
		Dispatch* pDispatch = GetDispatch(pType);

		//Dispatch::propertymap_t properties;
		//pDispatch->GetProperties(properties);

		Property* contentProperty = NULL;
		StringA* contentPropertyName = GetContentPropertyName(pType->GetClass());
		if (contentPropertyName)
		{
			contentProperty = pDispatch->GetProperty(contentPropertyName);
		}

		IDictionary* dictionary = NULL;
		IObjectCollection* collection = NULL;
		if (contentProperty)
		{
			if (contentProperty->get_GetMethod() && contentProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(IDictionary).GetType()))
			{
				// TODO
				ASSERT(0);
			//	dictionary = dynamic_cast<IDictionary*>(propertyValue);
			}
			else if (contentProperty->get_GetMethod() && contentProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(IObjectCollection).GetType()))
			{
				Object* propertyValue = (Object*)pDispatch->pointer_Invoke(object, contentProperty->get_GetMethod(), NULL, 0);
				if (propertyValue == NULL)
				{
					propertyValue = newobj(contentProperty->get_GetType()->GetPointerTo()->GetClass());

					pDispatch->void_Invoke(object, contentProperty->get_SetMethod(), &propertyValue, sizeof(Object*));
				}

				collection = dynamic_cast<IObjectCollection*>(propertyValue);
			}

			/*
			if (contentProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(ICollection).GetType()))
			{
			}
			*/
		}
		else
		{
			dictionary = dynamic_cast<IDictionary*>(object);
			collection = dynamic_cast<IObjectCollection*>(object);
		}

		XmlData::NodeList* childNodes = element->get_childNodes();
		unsigned int nchildren = childNodes->get_length();

		IAddChild* pAddChild = dynamic_cast<IAddChild*>(object);

		for (unsigned int i = 0; i < nchildren; i++)
		{
			XmlData::Node* node = childNodes->item(i);
			XmlData::NodeType nodeType = node->get_nodeType();
			if (nodeType != XmlData::NODE_COMMENT)
			{
				if (nodeType == XmlData::NODE_ELEMENT)
				{
					XmlData::Element* element = static_cast<XmlData::Element*>(node);

					StringW* localName = element->get_localName();
					int npunct = localName->Find('.');
					if (npunct != -1)	// Property
					{
						StringW* className = localName->LeftOf(npunct);

					//	if (*className != 

						StringW* propertyName = localName->RightOf(npunct+1);
						StringA* name = propertyName->ToStringA();

						Property* pProperty = pDispatch->GetProperty(name);

						if (pProperty == NULL)
						{
							BufferImp<char> buffer;
							StringBuilderA strbuilder(&buffer);
							strbuilder << "object doesn't have property " << *name;
							MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
						}
						else if (pProperty->set_method == NULL)
						{
							BufferImp<char> buffer;
							StringBuilderA strbuilder(&buffer);
							strbuilder << "object doesn't have set property " << *name;
							MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
						}
						else
						{
							if (pProperty->get_method && pProperty->get_GetType()->get_Kind() == type_pointer && pProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(IDictionary).GetType()))
							{
								void* p = pDispatch->pointer_Invoke(object, pProperty->get_GetMethod(), NULL, 0);
								VERIFY(p);
								IDictionary* dictionary = (IDictionary*)DynamicCast(p, (ClassType*)pProperty->get_GetType()->GetPointerTo(), (ClassType*)typeid(IDictionary).GetType());

								XmlData::NodeList* childNodes = element->get_childNodes();
								unsigned int nchildren = childNodes->get_length();

								for (unsigned int i = 0; i < nchildren; i++)
								{
									XmlData::Node* node = childNodes->item(i);
									XmlData::NodeType nodeType = node->get_nodeType();
									if (nodeType != XmlData::NODE_COMMENT)
									{
										if (nodeType == XmlData::NODE_ELEMENT)
										{
											XmlData::Element* element = static_cast<XmlData::Element*>(node);

											StringW* key = element->getAttributeNS(WSTR("http://schemas.microsoft.com/winfx/2006/xaml"), WSTR("Key"));

											Type* pReturnType = NULL;
											Object* child = CreateObjectFromElement(NULL/*ArgType*/, scope, NULL, element, &pReturnType);
											if (child)
											{
												if (key)
												{
													dictionary->Add(key, child);
												}
												else
												{
													// TODO, improve

													ResourceDictionary* resourceDictionary = dynamic_cast<ResourceDictionary*>(dictionary);
													ResourceDictionary* childResourceDictionary = dynamic_cast<ResourceDictionary*>(child);

													if (resourceDictionary && childResourceDictionary)
													{
														resourceDictionary->get_MergedDictionaries()->Add(childResourceDictionary);
													}
													else
													{
														throw new Exception(WSTR("Missing key"));
													}
												}
											}
											else
												throw new Exception(WSTR("child = NULL"));
										}
										else
										{
											ASSERT(0);
											throw new Exception(WSTR("Unexpected non-element node"));
										}
									}
								}
							}
							else
							{
								XmlData::NodeList* childNodes = element->get_childNodes();
								unsigned int nchildren = childNodes->get_length();

								XmlData::Element* firstElement = NULL;

								for (unsigned int i = 0; i < nchildren; i++)
								{
									firstElement = dynamic_cast<XmlData::Element*>(childNodes->item(i));
									if (firstElement)
									{
										break;
									}
								}

								if (firstElement)
								{
									StringA* className = GetClassName(firstElement->get_namespaceURI(), firstElement->get_localName());
									NamedType* pNamedType = pD->LookupNamedType(className);
									if (pNamedType == NULL)
									{
										VERIFY(0);	// TODO
									}
									ClassType* pClassType = pNamedType->GetClass();

									if (pClassType == NULL)
									{
										VERIFY(0);	// TODO
									}

									if (pClassType->IsDerivedFrom(pProperty->get_GetType()->GetPointerTo()->GetClass()) ||
										pClassType->IsDerivedFrom((ClassType*)typeid(MarkupExtension).GetType()))
									{
										Type* ArgType = pProperty->set_method->m_decl->m_pType->GetFunction()->m_parameters.m_parameters[0].m_pType;
										ArgType = ArgType->GetStripped();

										Type* pReturnType = NULL;
										Object* child = CreateObjectFromElement(ArgType, scope, NULL, firstElement, &pReturnType);
										if (child)
										{
											if (child->GetType()->IsDerivedFrom(pProperty->get_GetType()->GetPointerTo()->GetClass()))
											{
												pDispatch->SetValue(object, pProperty->set_method, child, pReturnType);
											}
										}
									}
									else
									{
										if (pProperty->get_method && pProperty->get_GetType()->get_Kind() == type_pointer && pProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(IObjectCollection).GetType()))
										{
											void* p = pDispatch->pointer_Invoke(object, pProperty->get_GetMethod(), NULL, 0);
											if (p == NULL)	// ??
											{
												Type* pType = pProperty->get_SetType()->GetPointerTo();
												Object* obj = newobj(pType->GetClass());

												pDispatch->SetValue(object, pProperty->get_SetMethod(), obj, NULL);//sizeof(Object*));
												p = obj;
											}

											VERIFY(p);
											IObjectCollection* collection = (IObjectCollection*)DynamicCast(p, (ClassType*)pProperty->get_GetType()->GetPointerTo(), (ClassType*)typeid(IObjectCollection).GetType());

										//	XmlData::NodeList* childNodes = element->get_childNodes();
										//	unsigned int nchildren = childNodes->get_length();

											for (int i = 0; i < nchildren; i++)
											{
												XmlData::Node* node = childNodes->item(i);
												XmlData::NodeType nodeType = node->get_nodeType();
												if (nodeType != XmlData::NODE_COMMENT)
												{
													if (nodeType == XmlData::NODE_ELEMENT)
													{
														XmlData::Element* element = static_cast<XmlData::Element*>(node);

														Type* pReturnType = NULL;
														Object* child = CreateObjectFromElement(NULL/*ArgType*/, scope, NULL, element, &pReturnType);
														if (child)
														{
															collection->AddObject(child);
														}
														else
															throw new Exception(WSTR("child = NULL"));
													}
													else
													{
														ASSERT(0);
														throw new Exception(WSTR("Unexpected non-element node"));
													}
												}
											}
										}
										else
										{
											ASSERT(0);	// TODO
											throw new Exception(WSTR("error"));
										}
									}
								}
							}
						}
					}
					else
					{
						Type* pHintType = NULL;
						if (collection)
						{
							pHintType = collection->GetItemType().GetType();
						}
						else if (contentProperty)
						{
							pHintType = contentProperty->get_GetType();
						}

						Type* pReturnType = NULL;
						Object* child = CreateObjectFromElement(pHintType, scope, object, element, &pReturnType);
						if (child)
						{
							if (dictionary)
							{
								StringW* key = element->getAttributeNS(WSTR("http://schemas.microsoft.com/winfx/2006/xaml"), WSTR("Key"));

								if (key)
								{
									dictionary->Add(key, child);
								}
								else if (Style* style = dynamic_cast<Style*>(child))
								{
									Type* pType = style->get_TargetType();
									if (pType == NULL)
									{
										throw new Exception(WSTR("Style did not have TargetType set"));
									}

									dictionary->Add(pType, child);
								}
								else if (DataTemplate* dataTemplate = dynamic_cast<DataTemplate*>(child))
								{
									Type* pType = dataTemplate->get_DataType();
									if (pType == NULL)
									{
										throw new Exception(WSTR("DataType did not have DataType set"));
									}

									dictionary->Add(pType, child);
								}
								else
								{
									// TODO, improve

								//	ResourceDictionary* p = dynamic_cast<ResourceDictionary*>(dictionary);
									ResourceDictionary* resourceDictionary = dynamic_cast<ResourceDictionary*>(dictionary);
									ResourceDictionary* childResourceDictionary = dynamic_cast<ResourceDictionary*>(child);

									if (resourceDictionary && childResourceDictionary)
									{
										resourceDictionary->get_MergedDictionaries()->Add(childResourceDictionary);
									}
									else
									{
										throw new Exception(WSTR("Missing key"));
									}
								}
							}
							else if (collection)
							{
								collection->AddObject(child);
							}
							else if (pAddChild)
							{
								pAddChild->AddChild(child);
							}
							else
							{
								if (contentProperty)
								{
									pDispatch->SetValue(object, contentProperty->get_SetMethod(), child, pReturnType);
								}
								else
								{
									VERIFY(0);
								}
							}
						}
						else
						{
							throw new Exception(WSTR("child = NULL"));
							VERIFY(0);
						}
					}
				}
				else if (nodeType == XmlData::NODE_TEXT ||
						nodeType == XmlData::NODE_CDATA_SECTION)
				{
					XmlData::CharacterData* chardata = static_cast<XmlData::CharacterData*>(node);

					if (contentProperty == NULL)
					{
						ASSERT(0);
						throw new Exception(WSTR("Text content not valid for this element"));
					}

					StringW* data = chardata->get_data();

					pDispatch->SetValue(object, contentProperty->get_SetMethod(), data, typeid(StringW).GetType());

				//	XmlData::CharacterData* chardata = static_cast<XmlData::CharacterData*>(node);
				//	pAddChild->AddText(chardata->get_data());
				}
			}
		}
	}
}

}

void LoadInto(Object* object, XmlData::Element* element)
{
	StringA* className = GetClassName(element->get_namespaceURI(), element->get_localName());
	Type* pType = pD->LookupNamedType(className);
	if (pType->get_Kind() != type_class)
	{
		throw new Exception(WSTR("element name is not a class"));
	}

	if (!object->GetType()->IsDerivedFrom(static_cast<ClassType*>(pType)))
	{
		throw new Exception(WSTR("Object is not of correct type"));
	}

	ScopeProvider* scope = new ScopeProvider;
	scope->m_scope.push(object);

	LoadObjectFromElement(object, element, scope);
}

Object* CreateObjectFromElement(Type* pType, ScopeProvider* scope, Object* parentObject, XmlData::Node* node, Type** pReturnType)
{
	if (pType && pType->get_Kind() == type_pointer && pType->GetPointerTo() == typeid(TemplateNode).GetType())
	{
		if (node->get_nodeType() != XmlData::NODE_ELEMENT)
			throw new Exception(WSTR("expected element"));

		XmlData::Element* element = static_cast<XmlData::Element*>(node);

		*pReturnType = typeid(TemplateNode).GetType();
		return dynamic_cast<FrameworkTemplate*>(parentObject)->CreateElement2(typeid(UI::UIElement).GetType(), element);
	}

	if (node->get_nodeType() == XmlData::NODE_ELEMENT)
	{
		XmlData::Element* element = static_cast<XmlData::Element*>(node);

		StringA* className = GetClassName(element->get_namespaceURI(), element->get_localName());

		Type* pType = pD->LookupNamedType(className);

		*pReturnType = pType;
		if (pType)
		{
			Object* object = newobj(pType->GetClass());
			scope->m_scope.push(object);

			LoadObjectFromElement(object, element, scope);

			if (MarkupExtension* markupExtension = dynamic_cast<MarkupExtension*>(object))
			{
				object = markupExtension->ProvideValue(scope);
				ASSERT(object);
				if (object == NULL)
				{
					throw new Exception(WSTR("null object"));
				}
			}

			scope->m_scope.pop();
			return object;
		}
		else
		{
			BufferImp<char> buffer;
			StringBuilderA strbuilder(&buffer);
			strbuilder << "Couldn't find Type " << *className;
			MessageBoxA(NULL, buffer.DetachToString()->c_str(), "", MB_OK);
		}
	}
	else
	{
		XmlData::Text* text = static_cast<XmlData::Text*>(node);
		StringW* textdata = text->get_data();
		textdata = textdata->TrimLeft();
		textdata = textdata->TrimRight();

		if (textdata->begin()[0] == '{')
		{
			WCHAR* p = textdata->begin();
			++p;

			if (wcsncmp(p, L"StaticResource ", 15) == 0)
			{
				p += 15;

				StaticResourceExtension* extension = new StaticResourceExtension;

				WCHAR* start = p;

				while (*p != '}')
				{
					++p;
				}

				StringW* key = new StringW(string_copy(start, p-start));

				extension->set_ResourceKey(key);

				Object* value = extension->ProvideValue(scope);
				*pReturnType = value->GetType();
				return value;

				/*
				TemplateNode* node = new TemplateNode(this);
				node->m_pType = extension->GetType();//typeid(System::StringW).GetType();//pD->LookupNamedType(new StringA("System::StringW"));
				node->m_LiteralObject = extension;
			//	node->m_pType = pArgType;	// ???
			//	node->m_extension = extension;
				return node;
				*/
			}
			else
			{
				// TODO
				ASSERT(0);
			}
		}

		StringW* namespaceURI = WSTR("http://www.lerstad.com/ui");	// TODO

		if (pType->get_Kind() == type_pointer)
		{
			pType = pType->GetPointerTo()->GetStripped();

			StringA* classname = pType->GetClass()->m_qname;
			if (pType->get_Kind() == type_class)
			{
				if (pType == typeid(System::StringA).GetType())
				{
					*pReturnType = typeid(StringA).GetType();
					StringA* r = textdata->ToStringA();
					return r;
				}
				else if (pType == typeid(System::StringW).GetType())
				{
					*pReturnType = typeid(StringW).GetType();
					StringW* r = textdata;
					return r;
				}
				else if (pType == typeid(System::Uri).GetType())
				{
					*pReturnType = typeid(Uri).GetType();
					Uri* r = new Uri(textdata);
					return r;
				}
				else if (pType == typeid(UI::Color).GetType())
				{
					LDraw::Color color;
					int hr = ParseSingleRGBAColor(textdata->c_str(), &color);
					if (hr < 0)
					{
						throw new Exception(WSTR("Invalid color"));
					}

					*pReturnType = typeid(UI::Color).GetType();
					Color* r = new Color(color);
					return r;
				}
				else if (pType == typeid(UI::PointCollection).GetType())
				{
					UI::PointCollection* pPoints = new UI::PointCollection;
					ParsePointList(pPoints, textdata);
					*pReturnType = pType;
					return pPoints;
				}
				else if (*classname == "System::Int32Collection")
				{
					ASSERT(0);
#if 0

					Int32Collection* pval = new Int32Collection;

					const WCHAR* p = textdata->c_str();
					while (*p)
					{
						long value = getnumber(&p);
						if (p == NULL) break;

						pval->m_items.Add(value);

						while (isspace(*p)) p++;
					}
					*pReturnType = pType;
					return pval;
#endif
				}
				else if (pType == typeid(UI::Media3D::Point3D).GetType())
				{
					const WCHAR* p = textdata->c_str();

					double x = getfnumber(&p);
					if (p == NULL) return NULL;
					while (std::isspace(*p)) p++;
					if (*p == ',') p++;

					while (std::isspace(*p)) p++;
					double y = getfnumber(&p);
					if (p == NULL) return NULL;
					while (std::isspace(*p)) p++;
					if (*p == ',') p++;

					while (std::isspace(*p)) p++;
					double z = getfnumber(&p);
					if (p == NULL) return NULL;
					while (std::isspace(*p)) p++;
					if (*p != 0) return NULL;

					*pReturnType = typeid(UI::Media3D::Point3D).GetType();
					return new UI::Media3D::Point3D(x, y, z);
				}
				else if (pType == typeid(System::Type).GetType())
				{
					Type* p = pD->LookupNamedType(textdata->ToStringA());
					*pReturnType = p;
					return p;
				}
				else if (pType == typeid(System::UI::DependencyProperty).GetType())
				{
					*pReturnType = typeid(System::UI::DependencyProperty).GetType();

					int npunct = textdata->Find('.');
					if (npunct != -1)
					{
						StringW* className2 = textdata->LeftOf(npunct);
						StringW* propertyName = textdata->RightOf(npunct+1);
						StringA* className = GetClassName(namespaceURI, className2);

						NamedType* pNamedType = pD->LookupNamedType(className);
						if (pNamedType == NULL)
						{
							throw new Exception(WSTR("Couldn't find type"));
						}

						if (pNamedType->get_Kind() != type_class)
						{
							throw new Exception(WSTR("Type is not class type"));
						}

						ClassType* pClassType = static_cast<ClassType*>(pNamedType);

						DependencyProperty* pProperty = GetProperty(pClassType, propertyName);
						if (pProperty == NULL)
						{
							throw new Exception(WSTR("property doesn't exist"));
						}

						return pProperty;
					}
					else
					{
						// TODO
						VERIFY(0);
					}
				}
				else if (pType == typeid(System::Object).GetType())
				{
					// hm... ResourceKey

					*pReturnType = typeid(StringW).GetType();
					return textdata;
				}
				else
				{
					ASSERT(0);
					throw std::exception("Unsupported type parsing");
				}
			}
			else
			{
				ASSERT(0);
				throw std::exception("only supports pointer to class type");
			}
		}
		else if (pType->get_Kind() == type_class)
		{
			StringA* classname = pType->GetClass()->m_qname;
			if (pType == typeid(UI::PointCollection).GetType())
			{
				UI::PointCollection* pPoints = new UI::PointCollection;
				ParsePointList(pPoints, textdata);
				*pReturnType = pType;
				return pPoints;
			}
#if 0
			else if (pType == typeid(UI::Length).GetType())
			{
				//StringA texta = textdata.ToStringA();
				LengthUnits::LengthUnit unit;
				if (textdata->c_str()[textdata->Length()-1] == '%')
					unit = LengthUnits::Percentage;
				else
					unit = LengthUnits::Absolute;

				*pReturnType = typeid(UI::Length).GetType();//pD->LookupNamedType(new StringA("UI::Length"));
				Length* r = new Length(getfnumber(textdata->c_str()), unit);
				//r->AddRef();
				return r;
			}
#endif
			/*
			else if (pType->m_pClass->m_name == "UI::Length")
			{
				StringA texta = ConvertS2A(textdata);
				Length::UnitType unit;
				if (texta[texta.Length()-1] == '%')
					unit = Length::UnitPercentage;
				else
					unit = Length::UnitAbsolute;

				return new _Length(atof(texta.c_str()), unit);
			}
			*/
			else if (pType == typeid(System::StringA).GetType())
			{
				*pReturnType = typeid(StringA).GetType();//pD->LookupNamedType(new StringA("System::StringA"));
				StringA* r = textdata->ToStringA();//new StringA(textdata.ToStringA().c_str());
			//	r->AddRef();
				return r;
			}
			else if (pType == typeid(System::StringW).GetType())
			{
				*pReturnType = typeid(StringW).GetType();//pD->LookupNamedType(new StringA("System::StringW"));
				StringW* r = textdata;
				//r->AddRef();
				return r;
			}
			else if (pType == typeid(UI::Color).GetType())
			{
				LDraw::Color color;
				int hr = ParseSingleRGBAColor(textdata->c_str(), &color);
				if (hr < 0)
					throw new Exception(WSTR("Invalid color"));
				*pReturnType = typeid(UI::Color).GetType();//pD->LookupNamedType(new StringA("UI::Color"));
				Color* r = new Color(color);
				return r;
			}
			else if (pType == typeid(UI::Brush).GetType())
			{
				Brush* pBrush = ParseBrush(textdata);
				*pReturnType = pBrush->GetType();
				return pBrush;
			}
			else if (pType == typeid(UI::Thickness).GetType())
			{
				Thickness* pThickness = ParseThickness(textdata);
				*pReturnType = pThickness->GetType();
				return pThickness;
			}
			else if (pType == typeid(UI::Point).GetType())
			{
				const WCHAR* p = textdata->c_str();
				double x = getfnumber(&p);
				while (std::isspace(*p)) p++;
				if (*p == ',')
				{
					p++;
					while (std::isspace(*p)) p++;
				}
				double y = getfnumber(&p);

				*pReturnType = typeid(Point).GetType();
				return new Point(x, y);
			}
			else
				ASSERT(0);
		}
		else if (pType->get_Kind() == type_enum)
		{
			EnumType* pEnum = (EnumType*)pType;
			StringA* texta = textdata->ToStringA();
			int count = pEnum->m_deflist.GetSize();
			for (int i = 0; i < count; i++)
			{
				EnumDef& def = pEnum->m_deflist[i];
				if (*def.m_name == *texta)
				{
					*pReturnType = pType;//new Type(type_enum);
					return IntObject::GetObject(def.m_value);
				}
			}

			MessageBoxA(NULL, "Undefined enum value", "", MB_OK);
			THROW(-1);
		}
		else if (pType->get_Kind() == type_double)
		{
			*pReturnType = pType;//new Type(type_double);
			return DoubleObject::GetObject(getfnumber(textdata->c_str()));
		}
		else if (pType->get_Kind() == type_unsigned_char)
		{
			VERIFY(0);
#if 0
			*pReturnType = pType;//new Type(type_unsigned_char);
			return new unsigned char(str2int(textdata->c_str()));
#endif
			return NULL;
		}
		else if (pType->get_Kind() == type_bool)
		{
			bool value;
			if (*textdata == L"1" || *textdata == L"true")
				value = true;
			else if (*textdata == L"0" || *textdata == L"false")
				value = false;
			else
				THROW(-1);

			*pReturnType = pType;//new Type(type_bool);
			return BoolObject::GetObject(value);
		}
		else
			ASSERT(0);
	}

	return NULL;
}

Object* CreateObjectFromElement(Type* pType, Object* parentObject, XmlData::Node* node, Type** pReturnType)
{
	ASSERT(parentObject == NULL);

	ScopeProvider* scope = new ScopeProvider;
	return CreateObjectFromElement(pType, scope, NULL, node, pReturnType);
}

TemplateNode* FrameworkTemplate::get_VisualTree()
{
	return m_RootNode;
}

void FrameworkTemplate::set_VisualTree(TemplateNode* visualTree)
{
	m_RootNode = visualTree;
}

Type* ControlTemplate::get_DataType()
{
	return m_dataType;
}

void ControlTemplate::set_DataType(Type* dataType)
{
	m_dataType = dataType;
}

TriggerCollection* ControlTemplate::get_Triggers()
{
	return m_triggers;
}

void ControlTemplate::set_Triggers(TriggerCollection* triggers)
{
	m_triggers = triggers;
}

Type* DataTemplate::get_DataType()
{
	return m_dataType;
}

void DataTemplate::set_DataType(Type* dataType)
{
	m_dataType = dataType;
}

void LoadXmlAttributes(Object* object, XmlData::Element* element);

#if 0
void FrameworkTemplate::Load(XmlData::Element* element)
{
	//XmlData::Element* firstChild = static_cast<XmlData::Element*>(element->get_firstChild());

	LoadXmlAttributes(this, element);

#if 1
	m_RootNode = CreateElement2(typeid(UI::UIElement).GetType(), element->get_firstChild());

	printf("RootNode %d\n", __LINE__);

#else
	m_RootNode = CreateElement2(pD->LookupNamedType(new StringA("UI::UIElement")), element->get_firstChild());
#endif
}
#endif

PropertyValue::PropertyValue()
{
	m_property = NULL;
}

/////////////////////////////////////////////////////////////////
// TemplateNode

TemplateNode::TemplateNode(FrameworkTemplate* pOwner)
{
	m_pOwner = pOwner;
	m_pType = NULL;
	m_LiteralObject = NULL;
//	m_pBinding = NULL;
}

/*
Object* EvaluateProperty(TemplateNode* childnode, Object* sourceObject, Object* pObject, map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator>& objectpropertymap, Type** pRealType)
{
}
*/

void TemplateNode::SetProperties(Object* sourceObject, Object* pObject, DependencyObject* dObject, map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator>& objectpropertymap)
{
	Dispatch* pDispatch = GetDispatch(m_pType->GetClass());

	map<StringA*, TemplateNode*, Ref_Less<StringA>, System::__gc_allocator>::iterator it = m_properties.begin();
	while (it != m_properties.end())
	{
		StringA* propertyName = (*it).first;
		TemplateNode* childnode = (*it).second;

	//	printf("property: %s %p\n", propertyName->c_str(), childnode);

#if 0
		if (childnode->m_pType->GetStripped()->get_Kind() == type_class && childnode->m_pType->GetStripped()->GetClass() == typeid(UI::StaticResourceExtension).GetType())
		{
			StaticResourceExtension* extension = dynamic_cast<StaticResourceExtension*>(childnode->m_LiteralObject);

		
		}
		else
#endif
			if (childnode->m_pType->GetStripped()->get_Kind() == type_class && childnode->m_pType->GetStripped()->GetClass() == typeid(UI::Data::Binding).GetType())
		{
		//	TemplateNode* p = childnode->m_properties[ASTR("Path")];
		//	StringW* name = static_cast<Data::PropertyPath*>(p->m_LiteralObject)->get_Path();

			map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator> objectpropertymap2;
			Type* type;
			Data::Binding* binding = dynamic_cast<Data::Binding*>(childnode->Create4(NULL, &type, NULL, objectpropertymap2));

			if (binding->get_Source() == NULL)	// TODO
			{
				binding->set_Source(sourceObject);
			}

			DependencyProperty* dp = GetProperty(pObject->GetType(), propertyName->ToStringW());
			if (dp == NULL)
			{
				throw new Exception(WSTR("property is not dependency property"));
			}

			// ??
			dynamic_cast<DependencyObject*>(pObject)->m_isValidProperties[dp->gindex] = false;

			dynamic_cast<DependencyObject*>(pObject)->SetBindingInternal(dp, binding);

			// ??
		//	dynamic_cast<DependencyObject*>(pObject)->InvalidateProperty(dp);

			/*
			ObjectProperty op;
			op.m_object = pObject;
			op.m_propertyName = propertyName;

			if (*name == L"/")	// The value is the templated object itself, and not one of its properties
			{
			//	MessageBeep(-1);
			}

			objectpropertymap[name->ToStringA()] = op;
			*/
		}
		else if (childnode->m_pType->GetStripped()->get_Kind() == type_class && childnode->m_pType->GetStripped()->GetClass() == typeid(UI::PropertyValue).GetType())
		{
			TemplateNode* p = childnode->m_properties[ASTR("Name")];
			StringW* name = static_cast<StringW*>(p->m_LiteralObject);

			ObjectProperty op;
			op.m_object = pObject;
			op.m_propertyName = propertyName;

			if (*name == L"/")	// The value is the templated object itself, and not one of its properties
			{
				//MessageBeep(-1);
			}

			objectpropertymap[name->ToStringA()] = op;

			if (false)	// ??
			{
				Type* propertyType;
				Object* propertyValue;
				if (*name == L"/")	// The value is the templated object itself, and not one of its properties
				{
					propertyValue = sourceObject;
					propertyType = propertyValue->GetType();
				}
				else
				{
					Dispatch* pDispatch = GetDispatch(sourceObject->GetType());
					Property* pProperty = pDispatch->GetProperty(name->ToStringA());
					propertyType = pProperty->get_GetType();

					switch (propertyType->get_Kind())
					{
					case type_double:
						{
							double val = pDispatch->double_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
							propertyValue = DoubleObject::GetObject(val);
						}
						break;

					default:
						{
							propertyValue = pDispatch->Object_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
							propertyType = propertyType->GetPointerTo();
						}
					}

					// TODO, convert primitives to objects
				}

				Property* pProperty = pDispatch->GetProperty(propertyName);
				pDispatch->SetValue(pObject/*obj*/, pProperty->set_method, propertyValue, propertyType);
			}
		}
#if 0
		else if (childnode->m_pBinding)
		{
			ASSERT(0);
	#if 0
			childnode->m_pBinding->sourceObject = sourceObject;
			childnode->m_pBinding->targetObject = pObject;
			childnode->m_pBinding->targetProperty = pDispatch->GetProperty(propertyName);//(Property*)properties[propertyName];

			childnode->m_pBinding->OnSourceChanged();
	#endif
		}
#endif
		else
		{
			Type* pRealType;
			Object* child = childnode->Create4(sourceObject, &pRealType, NULL, objectpropertymap);

			StaticResourceExtension* extension = dynamic_cast<StaticResourceExtension*>(child);
			if (extension)
			{
				ScopeProvider scopeProvider;
				scopeProvider.m_element = pObject;

				child = extension->ProvideValue(&scopeProvider);
			}

			Property* pProperty = pDispatch->GetProperty(propertyName);
			if (pProperty)
			{
				if (pProperty->set_method)
				{
					pDispatch->SetValue(pObject/*obj*/, pProperty->set_method, child, pRealType->GetStripped());
				}
				else
				{
					ASSERT(0);
					//MessageBeep(-1);
				}
			}
			else if (UI::DependencyObject* pDepObject = dynamic_cast<UI::DependencyObject*>(pObject))
			{
				VERIFY(0);
				DependencyProperty* pProperty = NULL;//GetProperty(propertyName->ToStringW());

				if (pProperty)
				{
					pDepObject->SetValue(pProperty, child);//new IntObject(*(int*)child));
				}
			}
			else
			{
				VERIFY(0);
			}
		}

		++it;
	}

	map<DependencyProperty*, TemplateNode*, Ref_Less<DependencyProperty>, System::__gc_allocator>::iterator it2 = m_depproperties.begin();
	while (it2 != m_depproperties.end())
	{
		DependencyProperty* dp = (*it2).first;
		TemplateNode* childnode = (*it2).second;

		Object* propertyValue;

		if (childnode->m_pType->GetStripped()->get_Kind() == type_class && childnode->m_pType->GetStripped()->GetClass() == typeid(UI::PropertyValue).GetType())
		{
			VERIFY(0);
		}
		else
		{
			Type* pRealType;
			propertyValue = childnode->Create4(sourceObject, &pRealType, NULL, objectpropertymap);
		}

		UI::DependencyObject* pDepObject = dynamic_cast<UI::DependencyObject*>(pObject);

		if (dynamic_cast<Track*>(pDepObject) && *dp->m_name == L"Value")
		{
			MessageBeep(-1);
		}

		pDepObject->SetValue(dp, propertyValue);

		++it2;
	}

//	if (m_pType->GetClass()->IsOfType(typeid(IObjectCollection).GetType())
	IDictionary* dictionary = NULL;
	IObjectCollection* collection = NULL;
	Property* contentProperty = NULL;

	dictionary = dynamic_cast<IDictionary*>(pObject);
	collection = dynamic_cast<IObjectCollection*>(pObject);
	if (collection == NULL && dictionary == NULL)
	{
		StringA* contentPropertyName = GetContentPropertyName(m_pType->GetClass());
		if (contentPropertyName)
		{
			contentProperty = pDispatch->GetProperty(contentPropertyName);
		}
		
		if (contentProperty)
		{
			if (contentProperty->get_GetMethod() && contentProperty->get_GetType()->GetPointerTo()->IsOfType(typeid(IObjectCollection).GetType()))
			{
				Object* propertyValue = (Object*)pDispatch->pointer_Invoke(pObject, contentProperty->get_GetMethod(), NULL, 0);
				if (propertyValue == NULL)
				{
					propertyValue = newobj(contentProperty->get_GetType()->GetPointerTo()->GetClass());

					pDispatch->void_Invoke(pObject, contentProperty->get_SetMethod(), &propertyValue, sizeof(Object*));
				}

				collection = dynamic_cast<IObjectCollection*>(propertyValue);
			}
		}
	}

	IAddChild* pAddChild = dynamic_cast<IAddChild*>(pObject);

	for (int i = 0; i < m_children.size(); i++)
	{
		Type* pReturnType;
		Object* child = m_children[i]->Create4(sourceObject, &pReturnType, dynamic_cast<DependencyObject*>(pObject), objectpropertymap);

		if (dictionary)
		{
			ASSERT(0);
		}
		else if (collection)
		{
			collection->AddObject(child);
		}
		else if (pAddChild)
		{
			pAddChild->AddChild(child);
		}
		else
		{
			if (contentProperty)
			{
				pDispatch->SetValue(pObject, contentProperty->get_SetMethod(), child, pReturnType);
			}
			else
			{
				VERIFY(0);
			}
		}
	}
}

Object* TemplateNode::Create4(Object* sourceObject, Type** pRealType, DependencyObject* dObject, map<System::StringA*, ObjectProperty, Ref_Less<System::StringA>, System::__gc_allocator> & objectpropertymap)
{
	//printf("TemplateNode::Create(sourceObject=%p)\n", sourceObject);

	if (m_LiteralObject)
	{
		*pRealType = m_pType;

		StringA* str = m_pType->ToString();

	//	printf("Create returns LiteralObject %p, %s\n", m_LiteralObject, str->c_str());

		/*
		if (m_pType->m_type == type_class)
		{
			ASSERT(GetType(m_LiteralObject)->m_qname == ((ClassType*)m_pType)->m_qname);
		}
		else if (m_pType->m_type == type_pointer && m_pType->GetPointerTo()->m_type == type_class)
		{
			ASSERT(GetType(m_LiteralObject)->m_qname == ((ClassType*)m_pType->GetPointerTo())->m_qname);
		}
		*/

		return m_LiteralObject;
	}
	else if (m_pType->GetStripped()->get_Kind() == type_class && m_pType->GetStripped()->GetClass() == typeid(UI::PropertyValue).GetType())
	{
		ASSERT(0);
#if 0
	//	printf("*********************************************** UI::PropertyValue\n");

		TemplateNode* p = m_properties[new StringA("Name")];

	//	Class* pType = GetType(p->m_LiteralObject);
		StringW* name = static_cast<StringW*>(p->m_LiteralObject);

	//	PropertyValue* p = static_cast<PropertyValue*>(
	//	Property* pProperty = properties[propertyName];

	//	SetValue(pDispatch, obj, pProperty->put_method, child, childnode->m_pType);

	//	Property* pProperty = properties[propertyName];

		ObjectProperty op;
		op.m_propertyName = 

		objectpropertymap[name->ToStringA()] = op;

		return NULL;
#if 0
		Object* vobject;
		Type* vType;
		{
			Dispatch* pdisp2 = GetDispatch(sourceObject->GetType());
			Dispatch::propertymap_t properties;
		//	pdisp2->GetProperties(properties);
			Property* pProperty = pdisp2->GetProperty(name->ToStringA());//(Property*)properties[name->ToStringA()];

			vType = pProperty->get_GetType();//get_method->m_decl->m_pType->GetFunction()->m_pReturnType;
			vobject = (Object*)pdisp2->Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
		}

//			pdisp2->get_method


	//	SetValue(pDispatch, obj, pProperty->put_method, vobject, vType->GetPointerTo());
		*pRealType = vType->GetPointerTo();

		/*
		if ((*pRealType)->m_type == type_class)
		{
			*pRealType = GetType(vobject);
		}
		*/

		return vobject;
#endif
#endif
	}
		
	/*
	else if (m_pBinding)
	{
		//m_pBinding->
		m_pBinding->sourceObject = sourceObject;
	}
	*/

	//printf("Before newobj\n");

	Object* pObject = newobj(m_pType->GetClass());
	if (pObject == NULL)
	{
		VERIFY(0);
	}

	/*
	if (dynamic_cast<BitmapVisual*>(pObject))
	{
		MessageBeep(-1);
	}
	*/

#if 0//WIN32
	//StringA dname = DecorateName(m_pType->GetClass()->m_qname);
	//Type_Info* ti = (Type_Info*)pD->LookupSymbol(dname);
	//_Object* pObject = (_Object*)__RTDynamicCast(obj, 0, (void*)ti, (void*)&typeid(_Object), 0);
#else
//	Object* pObject = (Object*)DynamicCast(obj, m_pType->GetClass(), typeid(Object).GetType()/*pD->LookupNamedType(ASTR("System::Object"))*/);

	//printf("diff after cast %d\n", (ULONG)pObject - (ULONG)obj);

#endif

	ContentPresenter* pCP = dynamic_cast<ContentPresenter*>(pObject);
	if (pCP)
	{
		//MessageBeep(-1);
	}

	SetProperties(sourceObject, pObject, dObject, objectpropertymap);

	if (pCP)
	{
	//	pCP->m_pTemplatedParent = sourceObject;
	//	pCP->m_Content = sourceObject;
		//pCP->Apply();
	}

//	printf("after AddChildren\n");

	*pRealType = m_pType;

//	printf("Create returns \n");

	ASSERT(*System::GetType(pObject)->m_qname == *m_pType->GetClass()->m_qname);

//	printf("%p\n", obj);

	return pObject;
}

Object* TemplateNode::Create(Object* sourceObject, Type** pRealType)
{
	//printf("TemplateNode::Create(sourceObject=%p)\n", sourceObject);

	if (m_LiteralObject)
	{
		*pRealType = m_pType;

		//StringA* str = m_pType->ToString();

	//	printf("Create returns LiteralObject %p, %s\n", m_LiteralObject, str->c_str());

		/*
		if (m_pType->m_type == type_class)
		{
			ASSERT(GetType(m_LiteralObject)->m_qname == ((ClassType*)m_pType)->m_qname);
		}
		else if (m_pType->m_type == type_pointer && m_pType->GetPointerTo()->m_type == type_class)
		{
			ASSERT(GetType(m_LiteralObject)->m_qname == ((ClassType*)m_pType->GetPointerTo())->m_qname);
		}
		*/

		return m_LiteralObject;
	}
	else if (m_pType->GetStripped()->get_Kind() == type_class && m_pType->GetStripped()->GetClass() == typeid(UI::Data::Binding).GetType())
	{
		ASSERT(0);
	}
	else if (m_pType->GetStripped()->get_Kind() == type_class && m_pType->GetStripped()->GetClass() == typeid(UI::PropertyValue).GetType())
	{
	//	printf("*********************************************** UI::PropertyValue\n");

		TemplateNode* p = m_properties[ASTR("Name")];

	//	Class* pType = GetType(p->m_LiteralObject);
		StringW* name = static_cast<StringW*>(p->m_LiteralObject);

	//	PropertyValue* p = static_cast<PropertyValue*>(
	//	Property* pProperty = properties[propertyName];

	//	SetValue(pDispatch, obj, pProperty->put_method, child, childnode->m_pType);

	//	Property* pProperty = properties[propertyName];

		Object* vobject;
		Type* vType;
		{
			Dispatch* pdisp2 = GetDispatch(sourceObject->GetType());
			Dispatch::propertymap_t properties;
		//	pdisp2->GetProperties(properties);
			Property* pProperty = pdisp2->GetProperty(name->ToStringA());//(Property*)properties[name->ToStringA()];

			vType = pProperty->get_GetType();//get_method->m_decl->m_pType->GetFunction()->m_pReturnType;
			vobject = pdisp2->Object_Invoke(sourceObject, pProperty->get_GetMethod(), NULL, 0);
		}

//			pdisp2->get_method


	//	SetValue(pDispatch, obj, pProperty->put_method, vobject, vType->GetPointerTo());
		*pRealType = vType->GetPointerTo();

		/*
		if ((*pRealType)->m_type == type_class)
		{
			*pRealType = GetType(vobject);
		}
		*/

		return vobject;
	}
		
	/*
	else if (m_pBinding)
	{
		//m_pBinding->
		m_pBinding->sourceObject = sourceObject;
	}
	*/

	//printf("Before newobj\n");

	Object* obj = (Object*)newobj(m_pType->GetClass());
	if (obj == NULL)
	{
		VERIFY(0);
	}
#if 0//WIN32
	//StringA dname = DecorateName(m_pType->GetClass()->m_qname);
	//Type_Info* ti = (Type_Info*)pD->LookupSymbol(dname);
	//_Object* pObject = (_Object*)__RTDynamicCast(obj, 0, (void*)ti, (void*)&typeid(_Object), 0);
#else
	Object* pObject = obj;//(Object*)DynamicCast(obj, m_pType->GetClass(), pD->LookupNamedType(ASTR("System::Object")));

	//printf("diff after cast %d\n", (ULONG)pObject - (ULONG)obj);

#endif

	Dispatch* pDispatch = GetDispatch(m_pType->GetClass());

//	Dispatch::propertymap_t properties;
//	pDispatch->GetProperties(properties);

	map<StringA*, TemplateNode*, Ref_Less<StringA>, System::__gc_allocator>::iterator it = m_properties.begin();
	while (it != m_properties.end())
	{
		StringA* propertyName = (*it).first;
		TemplateNode* childnode = (*it).second;

	//	printf("property: %s %p\n", propertyName->c_str(), childnode);

#if 0
		if (childnode->m_pBinding)
		{
			childnode->m_pBinding->sourceObject = sourceObject;
			childnode->m_pBinding->targetObject = pObject;
			childnode->m_pBinding->targetProperty = pDispatch->GetProperty(propertyName);//(Property*)properties[propertyName];

			childnode->m_pBinding->OnSourceChanged();
		}
		else
#endif
		{
			{
				Type* pRealType;
				Object* child = childnode->Create(sourceObject, &pRealType);
				/*
				if (child)
				{
					ASSERT(GetType(child)->ToString() == pRealType->ToString());
				}
				*/

			//	Dispatch::propertymap_t::iterator property_it = properties.find(propertyName);
				Property* pProperty = pDispatch->GetProperty(propertyName);
				if (pProperty)//(property_it != properties.end())
				{
					pDispatch->SetValue(obj, pProperty->set_method, child, pRealType);
				//	printf("After SetValue at %s(%d)\n", __FILE__, __LINE__);
				}
				else if (UI::DependencyObject* pDepObject = dynamic_cast<UI::DependencyObject*>(pObject))
				{
					ASSERT(0);
					DependencyProperty* pProperty = NULL;//GetProperty(propertyName->ToStringW());

					if (pProperty)
					{
						if (pRealType->get_Kind() == type_enum)
						{
							pDepObject->SetValue(pProperty, child);//new IntObject(*(int*)child));
						}
						else
						{
							pDepObject->SetValue(pProperty, (Object*)child);
						}
					}
				}
			}
		}

		++it;
	}
	//printf("Properties done\n");

	IAddChild* pAddChild = dynamic_cast<IAddChild*>(pObject);
	//printf("after dyn cast\n");
	if (pAddChild)
	{
	//	printf("AddChildren\n");

		for (int i = 0; i < m_children.GetSize(); i++)
		{
			Type* pRealType;
			void* child = m_children[i]->Create(sourceObject, &pRealType);

			Object* pObj = (Object*)DynamicCast(child, pRealType->GetClass(), typeid(Object).GetType()->GetClass());//typeid(_Object));
			pAddChild->AddChild(pObj);
		}
	}
//	printf("after AddChildren\n");

	*pRealType = m_pType;

//	printf("Create returns \n");

	ASSERT(*System::GetType(obj)->m_qname == *((ClassType*)m_pType)->m_qname);

//	printf("%p\n", obj);

	return obj;
}

}
}
