#include "stdafx.h"
#include "GUI2.h"

namespace System
{

class Views
{
public:

//	static Object* From(Object* ob);

	static multimap<Object*,Object*> s_obj2views;
};

// static
multimap<Object*,Object*> Views::s_obj2views;

GUIEXT void AddView(Object* obj, Object* view)
{
	// TODO remove?
	TextDocument* viewimp = dynamic_cast<TextDocument*>(view);
	if (viewimp)
	{
		if (viewimp->m_Source == nullptr)
		{
			viewimp->m_Source = obj;
		}
	}

	// TODO IViewable

//	pair<multimap<Object*,Object*>::iterator, bool> r =
		Views::s_obj2views.insert(multimap<Object*,Object*>::value_type(obj, view));
}

Object* GetSource(Object* view)
{
	TextDocument* viewimp = dynamic_cast<TextDocument*>(view);
	if (viewimp)
	{
		return viewimp->m_Source;
	}
	else
	{
		ASSERT(0);
	}

	return nullptr;
}

Object* GetView(Object* obj)
{
	auto it = Views::s_obj2views.find(obj);
	if (it == Views::s_obj2views.end()) return nullptr;

	return it->second;
}

IEnumerator<Object*>* GetViews(Object* obj)
{
	return nullptr;
	//return new Map::Enumerator(Views::s_views.find(obj));
}

TextDocument::TextDocument()
{
}

TextDocument::TextDocument(StringIn str) : IO::StringWriter(str)
{
}

// static
TextDocument* TextDocument::FromFile(StringIn filename)
{
	TextDocument* td = new TextDocument;
	td->IncRef();

	IO::FileStream file(filename, IO::FileMode_Open, IO::FileAccess_Read);
	WCHAR buf[256];
	while (size_t len = file.ReadChars(buf, 256))
	{
		td->WriteChars(buf, len);
	}
	return td;
}

bool TextDocument::SaveAs(StringIn filename)
{
	IO::FileStream file(filename, IO::FileMode_Create, IO::FileAccess_Write);

	ASSERT(0);
	/*
	char buf[256];
	while (size_t len = ReadChars(buf, 256))
	{
		file.WriteChars(buf, len);
	}
	*/

	return true;
}

void TextDocument::Insert(StringIn itext, size_t offset)
{
	m_str.Insert(itext, offset);

	TextSourceChangeEventArgs args;
	args.type = TextChangeKind_Insert;
	args.offset = offset;
	args.len = itext.GetLength();

	Changed(this, args);
}

void TextDocument::Delete(size_t offset, size_t len)
{
	m_str.Delete(offset, len);

	TextSourceChangeEventArgs args;
	args.type = TextChangeKind_Delete;
	args.offset = offset;
	args.len = len;

	Changed(this, args);
}

/*
TextDocument* cpp(Type* pType)
{
}
*/

GUIEXT TextDocument* ascpp(ClassType* pType)
{
	TextDocument* td = new TextDocument;
	td->IncRef();
	td->set_Mimetype("text/x-c++");
	printClass(*td, pType, 0);
	return td;
}

namespace Gui
{

Brush* identifierBrush = new SolidColorBrush(0.0f, 0.0f, 0.0f);
Brush* keywordBrush = new SolidColorBrush(0.25f, 0.25f, 0.75f);
Brush* symbolBrush = new SolidColorBrush(0.25f, 0.25f, 0.65f);
Brush* stringBrush = new SolidColorBrush(0.75f, 0.1f, 0.1f);
Brush* commentBrush = new SolidColorBrush(0.1f, 0.75f, 0.1f);
Brush* normalBrush = new SolidColorBrush(0.0f, 0.0f, 0.0f);
DWRITE_FONT_WEIGHT keywordWeight = DWRITE_FONT_WEIGHT_EXTRA_BOLD;

Brush* vrml_headerBrush = new SolidColorBrush(0.7f, 0.4f, 0.0f);
Brush* vmrl_nodenameBrush = new SolidColorBrush(0.2f, 0.2f, 0.0f);
Brush* vmrl_fieldnameBrush = new SolidColorBrush(0.4f, 0.4f, 0.2f);

Brush* cpp_preprocessorBrush = new SolidColorBrush(0.0f, 0.5f, 0.0f);

Brush* xml_headerBrush = new SolidColorBrush(0.25f, 0.75f, 0.25f);
Brush* xml_tagBrush = new SolidColorBrush(0.25f, 0.25f, 0.75f);
Brush* xml_commentBrush = new SolidColorBrush(0.25f, 0.25f, 0.25f);
Brush* xml_errorBrush = new SolidColorBrush(0.9f, 0.0f, 0.0f);

#define MATCHSTR(x) (len == wcslen(x) && wcsncmp(rangestart, x, len) == 0)

void JavaScriptFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
	while (*p)
	{
		Brush* brush;
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

		WCHAR* rangestart = p;

		if (wcsncmp(p, L"function", 8) == 0)
		{
			brush = keywordBrush;
			fontWeight = keywordWeight;
			p += 8;
		}
		else if (wcsncmp(p, L"var", 3) == 0)
		{
			brush = keywordBrush;
			fontWeight = keywordWeight;
			p += 3;
		}
		else if (wcsncmp(p, L"for", 3) == 0)
		{
			brush = keywordBrush;
			fontWeight = keywordWeight;
			p += 3;
		}
		else if (wcsncmp(p, L"while", 5) == 0)
		{
			brush = keywordBrush;
			fontWeight = keywordWeight;
			p += 5;
		}
		else if (wcsncmp(p, L"new", 3) == 0)
		{
			brush = keywordBrush;
			fontWeight = keywordWeight;
			p += 3;
		}
		else if (p[0] == '/' && p[1] == '/')
		{
			p += 2;
			while (*p != '\n')
			{
				++p;
			}

			brush = commentBrush;
		}
		else if (*p == '/' && p[1] == '*')
		{
			p += 2;
			while (p[0] != '*' || p[1] != '/')
			{
				++p;
			}
			p += 2;

			brush = commentBrush;
		}
		else if (*p == '\"')
		{
			p += 1;
			while (*p != '\"')
			{
				++p;
			}
			p += 1;

			brush = stringBrush;
		}
		else if (
			*p == '(' ||
			*p == ')' ||
			*p == '[' ||
			*p == ']' ||
			*p == '{' ||
			*p == '}' ||
			*p == '*' ||
			*p == '/' ||
			*p == '%' ||
			*p == '+' ||
			*p == '-' ||
			*p == '=')
		{
			brush = symbolBrush;
			++p;
		}
		else
		{
			brush = normalBrush;
			++p;
		}

		DWRITE_TEXT_RANGE tr;
		tr.startPosition = rangestart-docstart;
		tr.length = p-rangestart;

		textLayout->SetDrawingEffect(brush->Create(renderContext.m_p, NULL), tr);
		textLayout->SetFontWeight(fontWeight, tr);
	}
}

void CSSFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
}

void XMLFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
	while (*p)
	{
		Brush* brush;
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

		WCHAR* rangestart = p;

		if (*p == '<')
		{
			++p;
			if (*p == '!')
			{
				++p;
				p += 2;

				while (p[0] && p[0] != '-' && p[1] != '-')
				{
					++p;
				}
				p += 2;
				
				int len = p - rangestart;

				brush = xml_commentBrush;
			}
			else
			{
				if (*p == '/')	// End tag
				{
					++p;
					while (isalnum(*p) || *p == '_' || *p == ':')
					{
						++p;
					}

					if (*p == '>')
					{
						++p;
					}

					int len = p - rangestart;

					brush = xml_tagBrush;
					fontWeight = keywordWeight;
				}
				else
				{
					while (isalnum(*p) || *p == '_' || *p == ':')
					{
						++p;
					}

					int len = p - rangestart;

					brush = xml_tagBrush;
					fontWeight = keywordWeight;
				}
			}
		}
		else if (p[0] == '/' && p[1] == '>')	// Immediate end tag
		{
			p += 2;

			brush = xml_tagBrush;
			fontWeight = keywordWeight;
		}
		else if (*p == '=')
		{
			++p;
			brush = symbolBrush;
		}
		else if (*p == '\"')
		{
			p += 1;
			while (*p != '\"')
			{
				if (*p == '\\')
				{
					p += 2;
				}
				else
				{
					++p;
				}
			}
			p += 1;

			brush = stringBrush;
		}
		else
		{
			brush = normalBrush;
			++p;
		}

		DWRITE_TEXT_RANGE tr;
		tr.startPosition = rangestart-docstart;
		tr.length = p-rangestart;

		textLayout->SetDrawingEffect(brush->Create(renderContext.m_p, NULL), tr);
		textLayout->SetFontWeight(fontWeight, tr);
	}
}

void VRMLFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
	while (*p)
	{
		Brush* brush;
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

		WCHAR* rangestart = p;

		if (isalpha(*p) || *p == '_')
		{
			++p;
			while (isalnum(*p) || *p == '_')
			{
				++p;
			}

			int len = p - rangestart;

			if (MATCHSTR(L"DEF"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"USE"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"NULL"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"TRUE"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"FALSE"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"PROTO"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"EXTERNPROTO"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"META"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"COMPONENT"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"PROFILE"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else
			{
				if (islower(*rangestart))
				{
					brush = vmrl_fieldnameBrush;
				}
				else
				{
					brush = vmrl_nodenameBrush;
				}
			}
		}
		else if (*p == '\"')
		{
			p += 1;
			while (*p != '\"')
			{
				if (*p == '\\')
				{
					p += 2;
				}
				else
				{
					++p;
				}
			}
			p += 1;

			brush = stringBrush;
		}
		else if (*p == '#')
		{
			++p;

			if (p[0] == 'X' && p[1] == '3' && p[2] == 'D')
			{
				p += 3;
				while (*p != '\n')
				{
					++p;
				}

				brush = vrml_headerBrush;
			}
			else
			{
				while (*p != '\n')
				{
					++p;
				}

				brush = commentBrush;
			}
		}
		else
		{
			brush = normalBrush;
			++p;
		}

		DWRITE_TEXT_RANGE tr;
		tr.startPosition = rangestart-docstart;
		tr.length = p-rangestart;

		textLayout->SetDrawingEffect(brush->Create(renderContext.m_p, NULL), tr);
		textLayout->SetFontWeight(fontWeight, tr);
	}
}

void SMLFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
	while (*p)
	{
		Brush* brush;
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

		WCHAR* rangestart = p;

		if (isalpha(*p) || *p == '_')
		{
			++p;
			while (isalnum(*p) || *p == '_')
			{
				++p;
			}

			int len = p - rangestart;

			if (MATCHSTR(L"fun"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"type"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"val"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"in"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"end"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"nil"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"if"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"then"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"else"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else
			{
				brush = identifierBrush;
			}
		}
		else if (*p == '\"')
		{
			p += 1;
			while (*p != '\"')
			{
				if (*p == '\\')
				{
					p += 2;
				}
				else
				{
					++p;
				}
			}
			p += 1;

			brush = stringBrush;
		}
		else
		{
			brush = normalBrush;
			++p;
		}

		DWRITE_TEXT_RANGE tr;
		tr.startPosition = rangestart-docstart;
		tr.length = p-rangestart;

		textLayout->SetDrawingEffect(brush->Create(renderContext.m_p, NULL), tr);
		textLayout->SetFontWeight(fontWeight, tr);
	}
}

void SQLFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
}

void CPPFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
	while (*p)
	{
		Brush* brush;
		DWRITE_FONT_WEIGHT fontWeight = DWRITE_FONT_WEIGHT_NORMAL;

		WCHAR* rangestart = p;

		if (isalpha(*p) || *p == '_')
		{
			++p;
			while (isalnum(*p) || *p == '_')
			{
				++p;
			}

			int len = p - rangestart;

			if (MATCHSTR(L"void"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"bool"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"char"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"wchar_t"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"int"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"short"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"long"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"float"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"double"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"signed"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"unsigned"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"class"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"struct"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"union"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"public"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"protected"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"private"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"do"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"for"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"while"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"switch"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"case"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"default"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"break"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"goto"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"new"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"delete"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"inline"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"operator"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"friend"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"typedef"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"enum"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"virtual"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"const"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"volatile"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"template"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"typename"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"namespace"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"using"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"true"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"false"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"this"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"sizeof"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"typeid"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"static_cast"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"dynamic_cast"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"reinterpret_cast"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"const_cast"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__cdecl"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__stdcall"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__fastcall"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			
		///////////////////////////////////////////////
			else if (MATCHSTR(L"interface"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"override"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"abstract"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__int8"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__int16"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__int32"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else if (MATCHSTR(L"__int64"))
			{
				brush = keywordBrush;
				fontWeight = keywordWeight;
			}
			else
			{
				brush = identifierBrush;
			//	fontWeight = keywordWeight;
			}

		//	p += len;
		}
		else if (p[0] == '/' && p[1] == '/')
		{
			p += 2;
			while (*p != '\n')
			{
				++p;
			}

			brush = commentBrush;
		}
		else if (*p == '/' && p[1] == '*')
		{
			p += 2;
			while (p[0] != '*' || p[1] != '/')
			{
				++p;
			}
			p += 2;

			brush = commentBrush;
		}
		else if (*p == '\"')
		{
			p += 1;
			while (*p != '\"')
			{
				if (*p == '\\')
				{
					p += 2;
				}
				else
				{
					++p;
				}
			}
			p += 1;

			brush = stringBrush;
		}
		else if (p[0] == '&' && p[1] == '&')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '|' && p[1] == '|')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '|' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '&' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '^' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '|' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '~' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '!' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '-' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '+' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '*' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '/' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '%' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '>' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '<' && p[1] == '=')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '+' && p[1] == '+')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == '-' && p[1] == '-')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (p[0] == ':' && p[1] == ':')
		{
			brush = symbolBrush;
			p += 2;
		}
		else if (
			*p == '(' ||
			*p == ')' ||
			*p == '[' ||
			*p == ']' ||
			*p == '{' ||
			*p == '}' ||
			*p == '<' ||
			*p == '>' ||
			*p == '*' ||
			*p == '/' ||
			*p == '%' ||
			*p == '+' ||
			*p == '-' ||
			*p == '!' ||
			*p == '~' ||
			*p == '^' ||
			*p == '|' ||
			*p == '&' ||
			*p == ';' ||
			*p == ',' ||
			*p == '?' ||
			*p == ':' ||
			*p == '=')
		{
			brush = symbolBrush;
			++p;
		}
		else
		{
			brush = normalBrush;
			++p;
		}

		DWRITE_TEXT_RANGE tr;
		tr.startPosition = rangestart-docstart;
		tr.length = p-rangestart;

		textLayout->SetDrawingEffect(brush->Create(renderContext.m_p, NULL), tr);
		textLayout->SetFontWeight(fontWeight, tr);
	}
}

void JavaFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
}

void CSharpFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
}

void FXFormat(ManagedRenderContext renderContext, IDWriteTextLayout* textLayout, WCHAR* docstart, WCHAR* p)
{
}

#if 0
DependencyClass* FontFamily::get_Class()
{
	static DependencyClass depclass(typeid(FontFamily), DependencyObject::get_Class());

	static DependencyProperty* properties[] =
	{
		get_NameProperty(),
	};

	return &depclass;
}

DependencyClass* FontFamily::pClass(get_Class());

IMP_DEPENDENCY_PROPERTY(String, FontFamily, Name, String(L"Arial")/*, new PropertyMetadata(true)*/)

FontFamily::FontFamily() : DependencyObject(get_Class())
{
}

FontFamily::FontFamily(StringIn name) : DependencyObject(get_Class())
{
	SetPropertyValue(get_NameProperty(), String(name));
}
#endif

//////////////////////////

IMP_DEPENDENCY_PROPERTY(String, TextVisual, FontFamily, String(L"Courier New"))
IMP_DEPENDENCY_PROPERTY(float, TextVisual, FontSize, 17.0f)
IMP_DEPENDENCY_PROPERTY(int, TextVisual, FontWeight, 400)
IMP_DEPENDENCY_PROPERTY(FontStyle, TextVisual, FontStyle, FontStyle_Normal)

IMP_DEPENDENCY_PROPERTY(TextAlignment, TextVisual, TextAlignment, TextAlignment_Center)
IMP_DEPENDENCY_PROPERTY(TextWrapping, TextVisual, TextWrapping, TextWrapping_NoWrap)
IMP_DEPENDENCY_PROPERTY(TextTrimming, TextVisual, TextTrimming, TextTrimming_None)
IMP_DEPENDENCY_PROPERTY(VerticalAlignment, TextVisual, VerticalAlignment, VerticalAlignment_Center)

IMP_DEPENDENCY_PROPERTY(ITextSource*, TextVisual, TextSource, nullptr)
IMP_DEPENDENCY_PROPERTY(String, TextVisual, Text, nullptr)
IMP_DEPENDENCY_PROPERTY(Geometry*, TextVisual, LayoutRect, nullptr)
IMP_DEPENDENCY_PROPERTY(Brush*, TextVisual, Brush, new SolidColorBrush(0,0,0))

//IMP_DEPENDENCY_PROPERTY(float, TextVisual, Width, _this().getWidth())
IMP_DEPENDENCY_PROPERTY(float, TextVisual, WidthIncludingTrailingWhitespace, _this().getWidthIncludingTrailingWhitespace())
IMP_DEPENDENCY_PROPERTY(float, TextVisual, TextMinWidth, _this().DetermineMinWidth())

IMP_DEPENDENCY_PROPERTY(int, TextVisual, CursorPosition, 0)
IMP_DEPENDENCY_PROPERTY(int, TextVisual, CursorLine, 0)
IMP_DEPENDENCY_PROPERTY(int, TextVisual, CursorColumn, 0)
IMP_DEPENDENCY_PROPERTY(int, TextVisual, LineCount, 0)

DependencyClass* TextVisual::get_Class()
{
	static DependencyClass depclass(typeid(thisClass), baseClass::get_Class());

	static DependencyProperty* properties[] =
	{
		get_FontSizeProperty(),
		get_FontFamilyProperty(),
		get_FontWeightProperty(),
		get_FontStyleProperty(),

		get_TextAlignmentProperty(),
		get_VerticalAlignmentProperty(),
		get_TextWrappingProperty(),
		get_TextTrimmingProperty(),

		get_TextSourceProperty(),
		get_TextProperty(),
		get_LayoutRectProperty(),
		get_BrushProperty(),
		get_WidthIncludingTrailingWhitespaceProperty(),
		get_MinWidthProperty(),
		get_LineCountProperty(),
		get_CursorPositionProperty(),
		get_CursorLineProperty(),
		get_CursorColumnProperty(),
	};

	return &depclass;
}

DependencyClass* TextVisual::pClass(get_Class());

TextVisual::TextVisual() : UIElement(get_Class())
{
	set_IsFocusable(true);
}

TextVisual::TextVisual(typed<String> text, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight) : UIElement(get_Class())
{
	SetBinding(this, get_TextProperty(), text);
	SetBinding(this, get_BrushProperty(), brush);
	SetBinding(this, get_FontFamilyProperty(), fontFamily);
	SetBinding(this, get_FontSizeProperty(), fontSize);
	SetBinding(this, get_FontWeightProperty(), fontWeight);

	set_IsFocusable(true);
}

TextVisual::TextVisual(typed<String> text, typed<ITextSource*> textsource, typed<Brush*> brush, typed<String> fontFamily, typed<float> fontSize, typed<FontStyle> fontStyle, typed<int> fontWeight) : UIElement(get_Class())
{
	SetBinding(this, get_TextProperty(), text);
	SetBinding(this, get_TextSourceProperty(), textsource);
	SetBinding(this, get_BrushProperty(), brush);
	SetBinding(this, get_FontFamilyProperty(), fontFamily);
	SetBinding(this, get_FontSizeProperty(), fontSize);
	SetBinding(this, get_FontWeightProperty(), fontWeight);

	set_IsFocusable(true);
}

void TextVisual::OnTextSourceContentChanged(ITextSource*, TextSourceChangeEventArgs args)
{
	int m_offset = get_CursorPosition();

	int offset = args.offset;
	int len = args.len;

	if (args.type = TextChangeKind_Insert)
	{
		/*
		if (offset < m_selStart)
			m_selStart = m_offset+len;

		if (offset < m_selEnd)
			m_selEnd = m_offset+len;

		if (offset < m_initSel)
			m_initSel = m_offset+len;
			*/

		if (offset < m_offset)
			m_offset = m_offset+len;
	}
	else if (args.type = TextChangeKind_Insert)
	{
		/*
		if (m_selStart >= offset && m_selStart < offset+len)
			m_selStart = offset;
		else if (m_selStart >= offset+len)
			m_selStart = m_selStart - len;

		if (m_selEnd >= offset && m_selEnd < offset+len)
			m_selEnd = offset;
		else if (m_selEnd >= offset+len)
			m_selEnd = m_selEnd - len;

		if (m_initSel >= offset && m_initSel < offset+len)
			m_initSel = offset;
		else if (m_initSel >= offset+len)
			m_initSel = m_initSel - len;
			*/

		if (m_offset >= offset && m_offset < offset+len)
			m_offset = offset;
		else if (m_offset >= offset+len)
			m_offset = m_offset - len;
	}

	set_CursorPosition(m_offset);

	m_DWriteTextLayout = NULL;
	m_formatted = false;

	InvalidateVisual();
	/*
	IRootVisual* root = GetRoot();
	if (root)
	{
		root->InvalidateRender();
	}
	*/
}

void TextVisual::OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled)
{
	if (pPropertyVal->m_dp == get_FontSizeProperty() ||
		pPropertyVal->m_dp == get_FontFamilyProperty() ||
		pPropertyVal->m_dp == get_FontStyleProperty() ||
		pPropertyVal->m_dp == get_FontSizeProperty() ||
		pPropertyVal->m_dp == get_FontWeightProperty())
	{
		m_DWriteTextFormat.Release();
		m_DWriteTextLayout.Release();
	}
	else if (pPropertyVal->m_dp == get_TextProperty())
	{
		m_DWriteTextLayout.Release();
		m_formatted = false;
	}
	else if (pPropertyVal->m_dp == get_TextSourceProperty())
	{
		// TODO, remove old

		ITextSource* ts = get_TextSource();
		ts->get_Changed().Connect(EventHandler(this, &TextVisual::OnTextSourceContentChanged));

		m_DWriteTextLayout.Release();
		m_formatted = false;
	}

	baseClass::OnComputedPropertyValueChanged(pPropertyVal, handled);
}

void TextVisual::OnMouseLeftButtonDown(Gui::MouseButtonEventArgs* args)
{
	gm::PointF mousepos = args->GetPosition(this);

	Focus();

	if (m_DWriteTextLayout)
	{
		DWRITE_HIT_TEST_METRICS hitTestMetrics;
		BOOL isTrailingHit;
		BOOL isInside;

		m_DWriteTextLayout->HitTestPoint(
						mousepos.X, 
						mousepos.Y,
						&isTrailingHit,
						&isInside,
						&hitTestMetrics
						);

		int textPosition = hitTestMetrics.textPosition;
		if (isTrailingHit) ++textPosition;

		set_CursorPosition(textPosition);
	}
}

void TextVisual::OnMouseLeftButtonUp(Gui::MouseButtonEventArgs* args)
{
}

void TextVisual::OnMouseMove(MouseEventArgs* args)
{
	gm::PointF mousepos = args->GetPosition(this);

	if (get_IsMouseCaptured())
	{
		if (m_DWriteTextLayout)
		{
			DWRITE_HIT_TEST_METRICS hitTestMetrics;
			BOOL isTrailingHit;
			BOOL isInside; 

			m_DWriteTextLayout->HitTestPoint(
							mousepos.X, 
							mousepos.Y,
							&isTrailingHit,
							&isInside,
							&hitTestMetrics
							);

			int textPosition = hitTestMetrics.textPosition;
			if (isTrailingHit) ++textPosition;

			set_CursorPosition(textPosition);
		}
	}
}

void TextVisual::OnKey(KeyEventArgs* args)
{
	int textPosition = get_CursorPosition();

	if (args->m_key == VK_LEFT)
	{
		if (textPosition > 0)
		{
			--textPosition;
			set_CursorPosition(textPosition);
		}
	}
	else if (args->m_key == VK_RIGHT)
	{
		if (textPosition < GetTextLength())
		{
			++textPosition;
			set_CursorPosition(textPosition);
		}
	}
	else if (args->m_key == VK_DELETE)
	{
		if (textPosition < GetTextLength())
		{
			ITextSource* textSource = get_TextSource();
			if (textSource)
			{
				textSource->Delete(textPosition, 1);
			}
			else
			{
				String text = get_Text();
				text.Delete(textPosition, 1);
				set_Text(text);
			}
		}
	}
	else if (args->m_key == VK_BACK)
	{
		if (textPosition > 0)
		{
			--textPosition;
			set_CursorPosition(textPosition);

			ITextSource* textSource = get_TextSource();
			if (textSource)
			{
				textSource->Delete(textPosition, 1);
			}
			else
			{
				String text = get_Text();
				text.Delete(textPosition, 1);
				set_Text(text);
			}
		}
	}
}

void TextVisual::OnTextComposition(TextCompositionEventArgs* args)
{
	String itext = args->get_Text();

	int textPosition = get_CursorPosition();

	ITextSource* textSource = get_TextSource();
	if (textSource)
	{
		textSource->Insert(itext, textPosition);
	}
	else
	{
		String text = get_Text();
		text.Insert(itext, textPosition);

		set_Text(text);
	}
	set_CursorPosition(textPosition + itext.GetLength());
}

uint TextVisual::GetTextLength()
{
	String text;
	ITextSource* source = get_TextSource();
	if (source != nullptr)
	{
		text = source->GetObject()->ToString();
	}
	else
	{
		text = get_Text();
	}

	return text.GetLength();
}

void TextVisual::EnsureFormatted(ManagedRenderContext renderContext)
{
	if (!m_formatted)
	{
		String mimetype;
		String text;
		ITextSource* source = get_TextSource();
		if (source != nullptr)
		{
			text = source->GetObject()->ToString();
			mimetype = dynamic_cast<TextDocument*>(source)->get_Mimetype();
		}
		else
		{
			text = get_Text();
		}

		WCHAR* s = (WCHAR*)_alloca((text.GetLength()+1)*sizeof(WCHAR));
		text.CopyTo(s, text.GetLength());
		s[text.GetLength()] = 0;

		if (mimetype == "model/x3d+vrml")
		{
			VRMLFormat(renderContext, m_DWriteTextLayout, s, s);
		}
		else if (mimetype == "text/x-java-source")
		{
			JavaFormat(renderContext, m_DWriteTextLayout, s, s);
		}
		else if (mimetype == "application/x-javascript")
		{
			JavaScriptFormat(renderContext, m_DWriteTextLayout, s, s);
		}
		else if (mimetype == "text/css")
		{
			CSSFormat(renderContext, m_DWriteTextLayout, s, s);
		}
		else if (mimetype == "text/x-c" ||
				mimetype == "text/x-h" ||
				mimetype == "text/x-c++")
		{
			CPPFormat(renderContext, m_DWriteTextLayout, s, s);
		}
		// text/x-script.perl
		// text/x-fortran
		// application/x-lisp
		// text/x-script.lisp
		else
		{
			// plain

			// TODO, not
			XMLFormat(renderContext, m_DWriteTextLayout, s, s);
		}

		m_formatted = true;
	}
}

bool TextVisual::EnsureDWriteTextFormat()
{
	if (m_DWriteTextFormat == nullptr)
	{
		String fontFamily = get_FontFamily();
		if (fontFamily == nullptr)
		{
			fontFamily = S(L"Arial");
		}

		if (fontFamily == nullptr) return false;

		int fontWeight = get_FontWeight();
		FontStyle fontStyle = get_FontStyle();

		Graphics::Direct10::s.m_DWriteFactory->CreateTextFormat(
			fontFamily.c_strw_flen<64>(),                // Font family name.
			nullptr,                       // Font collection (NULL sets it to use the system font collection).
			(DWRITE_FONT_WEIGHT)fontWeight,//DWRITE_FONT_WEIGHT_REGULAR,
			(DWRITE_FONT_STYLE)fontStyle,
			DWRITE_FONT_STRETCH_NORMAL,
			get_FontSize(),
			L"en-us",
			&m_DWriteTextFormat
			);

		DWRITE_TEXT_ALIGNMENT textAlignment;
		switch (get_TextAlignment())
		{
		case TextAlignment_Left: textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING; break;
		case TextAlignment_Right: textAlignment = DWRITE_TEXT_ALIGNMENT_TRAILING; break;
		case TextAlignment_Center: textAlignment = DWRITE_TEXT_ALIGNMENT_CENTER; break;
		case TextAlignment_Justify: textAlignment = DWRITE_TEXT_ALIGNMENT_LEADING;	// Not supported
		}

		DWRITE_PARAGRAPH_ALIGNMENT paragraphAlignment;
		switch (get_VerticalAlignment())
		{
		case VerticalAlignment_Top: paragraphAlignment = DWRITE_PARAGRAPH_ALIGNMENT_NEAR; break;
		case VerticalAlignment_Bottom: paragraphAlignment = DWRITE_PARAGRAPH_ALIGNMENT_FAR; break;
		case VerticalAlignment_Center: paragraphAlignment = DWRITE_PARAGRAPH_ALIGNMENT_CENTER; break;
		}

		m_DWriteTextFormat->SetTextAlignment(textAlignment);
		m_DWriteTextFormat->SetParagraphAlignment(paragraphAlignment);
	}

	return true;
}

gm::SizeF TextVisual::MeasureOverride(gm::SizeF availSize)
{
	EnsureDWriteTextFormat();

	String text;
	ITextSource* source = get_TextSource();
	if (source != nullptr)
	{
		text = source->GetObject()->ToString();
	}
	else
	{
		text = get_Text();
	}

//	availSize.Width = 99999;
//	availSize.Height = 99999;

	ComPtr<IDWriteTextLayout> textLayout;

	WCHAR* s = (WCHAR*)_alloca((text.GetLength())*sizeof(WCHAR));
	text.CopyTo(s, text.GetLength());
	Graphics::Direct10::s.m_DWriteFactory->CreateTextLayout(s, text.GetLength(), m_DWriteTextFormat, availSize.Width, availSize.Height, &textLayout);

	if (textLayout)
	{
		DWRITE_TEXT_METRICS metrics;
		textLayout->GetMetrics(&metrics);

	//	set_LineCount(metrics.lineCount);

		return gm::SizeF(metrics.width, metrics.height);
	}
	else
	{
		return gm::SizeF();
	}
}

gm::SizeF TextVisual::ArrangeOverride(gm::SizeF finalSize)
{
	m_DWriteTextLayout.Release();

	EnsureDWriteTextFormat();

//	Geometry* layoutGeometry = get_LayoutRect();

//	RectangleGeometry* rgeom = dynamic_cast<RectangleGeometry*>(layoutGeometry);
//	if (rgeom == NULL) return false;

	String text;
	ITextSource* source = get_TextSource();
	if (source != nullptr)
	{
		text = source->GetObject()->ToString();
	}
	else
	{
		text = get_Text();
	}

	float maxWidth = finalSize.Width;
	float maxHeight = finalSize.Height;

	WCHAR* s = (WCHAR*)_alloca((text.GetLength()/*+1*/)*sizeof(WCHAR));
	text.CopyTo(s, text.GetLength());
//	s[text.GetLength()] = 0;
	Graphics::Direct10::s.m_DWriteFactory->CreateTextLayout(s, text.GetLength(), m_DWriteTextFormat, maxWidth, maxHeight, &m_DWriteTextLayout);

	DWRITE_TEXT_METRICS metrics;
	m_DWriteTextLayout->GetMetrics(&metrics);

	set_LineCount(metrics.lineCount);
//	set_WidthIncludingTrailingWhitespace(metrics.widthIncludingTrailingWhitespace);

	return finalSize;//gm::SizeF(metrics.width, metrics.height);
}

bool TextVisual::EnsureLayout()
{
	EnsureDWriteTextFormat();

	if (m_DWriteTextLayout == nullptr)
	{
		Geometry* layoutGeometry = get_LayoutRect();

	//	RectangleGeometry* rgeom = dynamic_cast<RectangleGeometry*>(layoutGeometry);
	//	if (rgeom == NULL) return false;

		String text;
		ITextSource* source = get_TextSource();
		if (source != nullptr)
		{
			text = source->GetObject()->ToString();
		}
		else
		{
			text = get_Text();
		}

		float maxWidth = get_Width();//rgeom->get_Width();
		float maxHeight = get_Height();//rgeom->get_Height();

		WCHAR* s = (WCHAR*)_alloca((text.GetLength()+1)*sizeof(WCHAR));
		text.CopyTo(s, text.GetLength());
		s[text.GetLength()] = 0;
		Graphics::Direct10::s.m_DWriteFactory->CreateTextLayout(s, text.GetLength(), m_DWriteTextFormat, maxWidth, maxHeight, &m_DWriteTextLayout);

		DWRITE_TEXT_METRICS metrics;
		m_DWriteTextLayout->GetMetrics(&metrics);

		set_LineCount(metrics.lineCount);
	//	set_ActualWidth(metrics.width);
	//	set_ActualHeight(metrics.height);
	}

	return true;
}

void TextVisual::Render(ManagedRenderContext renderContext)
{
	if (renderContext.m_p->GetRT()->m_spRT == nullptr) return;

	if (!EnsureLayout()) return;

	if (m_DWriteTextLayout)
	{
		EnsureFormatted(renderContext);

	//	Geometry* layoutGeometry = get_LayoutRect();

	//	RectangleGeometry* rgeom = dynamic_cast<RectangleGeometry*>(layoutGeometry);
	//	if (rgeom == NULL) return;

		Brush* brush = get_Brush();
		if (brush)
		{
			renderContext.m_p->GetRT()->m_spRT->DrawTextLayout(
				D2D1::Point2F(0/*rgeom->get_X()*/, 0/*rgeom->get_Y()*/),       // origin
				m_DWriteTextLayout,
				brush->Create(renderContext.m_p, this)     // The brush used to draw the text.
				);

			if (get_HasFocus())
			{
				int textPosition = get_CursorPosition();
				BOOL isTrailingHit = FALSE;

				float ptX;
				float ptY;

				DWRITE_HIT_TEST_METRICS hitTestMetrics2;
				m_DWriteTextLayout->HitTestTextPosition(textPosition, isTrailingHit, &ptX, &ptY, &hitTestMetrics2);

				renderContext.FillRectangle(gm::RectF(hitTestMetrics2.left, hitTestMetrics2.top, 1, hitTestMetrics2.height), brush);
			}
		}
	}
}

float TextVisual::getWidth()
{
	if (!EnsureLayout()) return 0;

	DWRITE_TEXT_METRICS textMetrics;
	m_DWriteTextLayout->GetMetrics(&textMetrics);

	return textMetrics.width;
}

float TextVisual::getWidthIncludingTrailingWhitespace()
{
	if (!EnsureLayout()) return 0;

	DWRITE_TEXT_METRICS textMetrics;
	m_DWriteTextLayout->GetMetrics(&textMetrics);

	return textMetrics.widthIncludingTrailingWhitespace;
}

float TextVisual::getHeight()
{
	if (!EnsureLayout()) return 0;

	DWRITE_TEXT_METRICS textMetrics;
	m_DWriteTextLayout->GetMetrics(&textMetrics);

	return textMetrics.height;
}

float TextVisual::DetermineMinWidth()
{
	if (!EnsureLayout()) return 0;

	float minWidth;
	m_DWriteTextLayout->DetermineMinWidth(&minWidth);

	return minWidth;
}

}	// Gui
}	// System
