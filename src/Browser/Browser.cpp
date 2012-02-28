#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>	// TODO remove

//#include "../LFC/TypeArchive.h"
//#include "../LFC/NameMangler.h"

#if AMIGA
#include "../amiga_header.h"
#endif

namespace System
{
LFCEXT void load_t2();
}

using namespace std;

#if WIN32
namespace System
{
LFCEXT void InitTypes();
}

using namespace System;
#endif

#if WIN32
#ifndef _WINNT_

typedef struct _RTL_CRITICAL_SECTION_DEBUG *PRTL_CRITICAL_SECTION_DEBUG;

typedef struct _RTL_CRITICAL_SECTION {
    PRTL_CRITICAL_SECTION_DEBUG DebugInfo;

    //
    //  The following three fields control entering and exiting the critical
    //  section for the resource
    //

    LONG LockCount;
    LONG RecursionCount;
    HANDLE OwningThread;        // from the thread's ClientId->UniqueThread
    HANDLE LockSemaphore;
    ULONG_PTR SpinCount;        // force size on 64-bit systems when packed
}
RTL_CRITICAL_SECTION, *PRTL_CRITICAL_SECTION;

#endif

namespace System
{
namespace MSWindows
{

extern "C"
{

DECLSPEC_IMPORT HDC WINAPI GetDC(HWND);
DECLSPEC_IMPORT int WINAPI ReleaseDC(HWND, HDC);
DECLSPEC_IMPORT int WINAPI GetDeviceCaps(
	HDC hdc,     // handle to the device context
	int nIndex   // index of capability to query
	);
}
}
}

#endif

#define APIENTRY WINAPI

#define ASPECTX       40    /* Length of the X leg                      */
#define ASPECTY       42    /* Length of the Y leg                      */
#define ASPECTXY      44    /* Length of the hypotenuse                 */

#define LOGPIXELSX    88    /* Logical pixels/inch in X                 */
#define LOGPIXELSY    90    /* Logical pixels/inch in Y                 */

/*
#include "../Draw/LDraw.h"
#include "../Draw/Drawing.h"
#include "../Draw/TTFont.h"
*/

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/LFC.lib")
#pragma comment(lib, "../../lib/Win32/Debug/LXUI.lib")
#pragma comment(lib, "../../lib/Win32/Debug/XPath.lib")
#pragma comment(lib, "../../lib/Win32/Debug/LMedia.lib")
#pragma comment(lib, "../../lib/Win32/Debug/UIMedia.lib")
#pragma comment(lib, "../../lib/Win32/Debug/SWF.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/LFC.lib")
#pragma comment(lib, "../../lib/Win32/Release/LXUI.lib")
#pragma comment(lib, "../../lib/Win32/Release/XPath.lib")
#pragma comment(lib, "../../lib/Win32/Release/LMedia.lib")
#pragma comment(lib, "../../lib/Win32/Release/UIMedia.lib")
#pragma comment(lib, "../../lib/Win32/Release/SWF.lib")
#endif

#pragma comment(lib, "winmm.lib")

#include "BrowserFrame.h"

namespace System
{
float pixelsPerInch;
}

System::UI::MessageLoop messageLoop;

Module _Module;

namespace System
{
LFCEXT void checkall();
}

#include "CodeComp/java_parse.h"
#include "CodeComp/java_translate.h"

#include "CodeComp/codegen_java.h"

#if _DEBUG
#pragma comment(lib, "../../lib/Win32/Debug/CodeComp.lib")
#else
#pragma comment(lib, "../../lib/Win32/Release/CodeComp.lib")
#endif

#include "LFC/NameMangler.h"

namespace System
{

using namespace IO;

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

//Web::HTMLDocument* document;

#if 0	// TODO, have this
Web::DocumentFragment* printHtml(Web::HTMLDocument* outfile, Type* pType/*, bool recurseClass*/);
Web::DocumentFragment* printHtml(Web::HTMLDocument* outfile, ClassType* pClass/*, bool recurseClass*/);
Web::DocumentFragment* printHtml(Web::HTMLDocument* outfile, _TemplateArgType* pType);
Web::DocumentFragment* printHtml(Web::HTMLDocument* outfile, CDeclarator* pDeclarator, FunctionType* pType/*, bool recurseClass*/);

static __live_object_ptr<StringW> a_str = WSTR("a");
static __live_object_ptr<StringW> ul_str = WSTR("ul");
static __live_object_ptr<StringW> h2_str = WSTR("h2");
static __live_object_ptr<StringW> div_str = WSTR("div");
static __live_object_ptr<StringW> span_str = WSTR("span");
static __live_object_ptr<StringW> void_str = WSTR("void");
static __live_object_ptr<StringW> bool_str = WSTR("bool");
static __live_object_ptr<StringW> char_str = WSTR("char");
static __live_object_ptr<StringW> signed_char_str = WSTR("signed char");
static __live_object_ptr<StringW> unsigned_char_str = WSTR("unsigned char");
static __live_object_ptr<StringW> int_str = WSTR("int");
static __live_object_ptr<StringW> short_str = WSTR("short");
static __live_object_ptr<StringW> long_str = WSTR("long");
static __live_object_ptr<StringW> unsigned_int_str = WSTR("unsigned int");
static __live_object_ptr<StringW> unsigned_short_str = WSTR("unsigned short");
static __live_object_ptr<StringW> unsigned_long_str = WSTR("unsigned long");
static __live_object_ptr<StringW> long_long_str = WSTR("long long");
static __live_object_ptr<StringW> unsigned_long_long_str = WSTR("unsigned long long");
static __live_object_ptr<StringW> float_str = WSTR("float");
static __live_object_ptr<StringW> double_str = WSTR("double");
static __live_object_ptr<StringW> kw_str = WSTR("kw");
static __live_object_ptr<StringW> typedef_str = WSTR("typedef");
static __live_object_ptr<StringW> address_str = WSTR("&");
static __live_object_ptr<StringW> star_str = WSTR("*");
static __live_object_ptr<StringW> open_paren_str = WSTR("(");
static __live_object_ptr<StringW> close_paren_str = WSTR(")");
static __live_object_ptr<StringW> open_bracket_str = WSTR("[");
static __live_object_ptr<StringW> close_bracket_str = WSTR("]");
static __live_object_ptr<StringW> comma_str = WSTR(",");
static __live_object_ptr<StringW> threedots_str = WSTR("...");
static __live_object_ptr<StringW> space_str = WSTR(" ");

StringW* GetFilename(Type* pType)
{
	BufferImp<WCHAR> buffer;
	StringBuilderW strbuilder(&buffer);
	Mangler<WCHAR> mangler(true/*bPreserveTypedefs*/);
	mangler.MangleType(pType, strbuilder);
	strbuilder << L".html";
	return buffer.DetachToString();
}

Web::DocumentFragment* printHtmlArray(Web::HTMLDocument* document, CDeclarator* pDeclarator, ArrayType* pArrayType)
{
	Web::DocumentFragment* fragment = document->createDocumentFragment();

	if (pArrayType->m_pElemType->get_Kind() == type_array)
	{
		ASSERT(0);
		//fragment->appendChild(printHtmlArray(document, pDeclarator, pArrayType->m_pElemType->));
	}
	else
	{
		fragment->appendChild(printHtml(document, pArrayType->m_pElemType));
		fragment->appendChild(document->createTextNode(space_str));
		fragment->appendChild(document->createTextNode(pDeclarator->m_name->ToStringW()));
		fragment->appendChild(document->createTextNode(open_bracket_str));
		fragment->appendChild(document->createTextNode(close_bracket_str));
	}

	return fragment;
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, CDeclarator* pDeclarator/*, bool recurseClass*/)
{
	//fprintf(outfile, "<div>");

	Web::DocumentFragment* fragment = document->createDocumentFragment();

	Web::HTMLElement* div = (Web::HTMLElement*)document->createElementNS(NULL, div_str);

	if (pDeclarator->m_pType->get_Kind() == type_function)
	{
		FunctionType* pFunctionType = (FunctionType*)pDeclarator->m_pType;
		div->appendChild(printHtml(document, pDeclarator, pFunctionType));
	}
	else if (pDeclarator->m_pType->get_Kind() == type_array)
	{
		ArrayType* pArrayType = (ArrayType*)pDeclarator->m_pType;
		div->appendChild(printHtmlArray(document, pDeclarator, pArrayType));
	}
	else
	{
#if 0

		if (pDeclarator->m_static)
		{
		//	fprintf(outfile, "<span class=\"kw\">static</span> ");
		}

		if (pDeclarator->m_virtual)
		{
		//	fprintf(outfile, "<span class=\"kw\">virtual</span> ");
		}
#endif

		div->appendChild(printHtml(document, pDeclarator->m_pType));
		div->appendChild(document->createTextNode(space_str));
		div->appendChild(document->createTextNode(pDeclarator->m_name->ToStringW()));

//		fprintf(outfile, " ");
//		fprintf(outfile, "%s", pDeclarator->m_name->c_str());
	}

	fragment->appendChild(div);
	return fragment;
//	fprintf(outfile, ";");
//	fprintf(outfile, "</div>");
};

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, Type* pType)//, bool recurseClass)
{
	Web::DocumentFragment* fragment = document->createDocumentFragment();

	switch (pType->get_Kind())
	{
	case type_cv:
		{
			ModifierType* p = (ModifierType*)pType;

			/*
			if (p->m_bConst) fprintf(outfile, "<span class=\"kw\">const</span> ");
			if (p->m_bVolatile) fprintf(outfile, "<span class=\"kw\">volatile</span> ");
			*/

			fragment->appendChild(printHtml(document, p->m_pPointerTo));
		}
		break;

	case type_pointer:
		{
			if (((PointerType*)pType)->m_pPointerTo->get_Kind() == type_function)
			{
				ASSERT(0);
			}
			else
			{
				fragment->appendChild(printHtml(document, ((PointerType*)pType)->m_pPointerTo));
				fragment->appendChild(document->createTextNode(star_str));
			}
		}
		break;

	case type_reference:
		{
			fragment->appendChild(printHtml(document, ((ReferenceType*)pType)->m_pPointerTo));
			fragment->appendChild(document->createTextNode(address_str));
		}
		break;

	case type_typedef:
		{
			Typedef* pTypedef = (Typedef*)pType;

		//	fprintf(outfile, "<a href=\"%s.html\">%s</a>", GetFilename(pTypedef)->c_str(), pTypedef->m_name->c_str());

			Web::HTMLAnchorElement* a = (Web::HTMLAnchorElement*)document->createElementNS(NULL, a_str);
		//	WCHAR buf[256];
		//	swprintf(buf, L"%S.html", GetFilename(pTypedef)->c_str());
			a->set_href(GetFilename(pTypedef));
			a->set_textContent(pTypedef->m_name->ToStringW());

			fragment->appendChild(a);

#if 0
			fprintf(outfile, "typedef ");
			printHtml(outfile, ((Typedef*)pType)->m_pType/*, recurseClass*/);
			fprintf(outfile, "%s", ((Typedef*)pType)->m_name->c_str());
#endif
		}
		break;

	case type_class:
		{
			ClassType* pClass = ((ClassType*)pType);

			if (pClass->m_name)
			{
				Web::HTMLAnchorElement* a = (Web::HTMLAnchorElement*)document->createElementNS(NULL, a_str);
				//WCHAR buf[256];
				//swprintf(buf, L"%S.html", GetFilename(pClass)->c_str());
				a->set_href(GetFilename(pClass));
				a->set_textContent(pClass->m_name->ToStringW());

				fragment->appendChild(a);

				if (pClass->m_pInstantiatedFrom)
				{
					fragment->appendChild(document->createTextNode(WSTR("<")));
					
					for (int i = 0; i < pClass->m_pInstantiatedFrom->m_templateArgs.size(); i++)
					{
						TemplatedClassArg* arg = pClass->m_pInstantiatedFrom->m_templateArgs[i];
						if (i > 0) fragment->appendChild(document->createTextNode(comma_str));
						if (arg->m_pType)
							fragment->appendChild(printHtml(document, arg->m_pType));
						else
						{
							;//fprintf(outfile, "%d", arg->m_value);
						}
					}
					
					fragment->appendChild(document->createTextNode(WSTR(">")));
				//	fprintf(outfile, "&gt;");
				}

				/*
				fprintf(outfile, "<a href=\"%s.html\">%s", GetFilename(pClass)->c_str(), pClass->m_name->c_str());

				if (pClass->m_pInstantiatedFrom)
				{
					fprintf(outfile, "&lt;");
					for (int i = 0; i < pClass->m_pInstantiatedFrom->m_templateArgs.size(); i++)
					{
						TemplatedClassArg* arg = pClass->m_pInstantiatedFrom->m_templateArgs[i];
						if (i > 0) fprintf(outfile, ",");
						if (arg->m_pType)
							printHtml(outfile, arg->m_pType);
						else
							fprintf(outfile, "%d", arg->m_value);
					}
					fprintf(outfile, "&gt;");
				}

				fprintf(outfile, "</a>");
				*/
			}
			else
			{
				// unnamed
			//	return printHtml(document, pClass);
			}
		}
		break;

	case type_enum:
		{
			EnumType* pEnumType = ((EnumType*)pType);
			if (pEnumType->m_name)
			{
			//	fprintf(outfile, "<a href=\"%s.html\">%s</a>", GetFilename(pEnumType)->c_str(), pEnumType->m_name->c_str());

				Web::HTMLAnchorElement* a = (Web::HTMLAnchorElement*)document->createElementNS(NULL, a_str);
			//	WCHAR buf[256];
			//	swprintf(buf, L"%S.html", GetFilename(pEnumType)->c_str());
				a->set_href(GetFilename(pEnumType));
				a->set_textContent(pEnumType->m_name->ToStringW());

				fragment->appendChild(a);
			}
			else
			{
			//	fprintf(outfile, "enum TODO");
			}
		}
		break;

	case type_templatearg:
		{
			//printHtml(outfile, (_TemplateArgType*)pType);
		}
		break;

	case type_array:
		{
			ArrayType* pArrayType = (ArrayType*)pType;

#if 0
			printHtml(outfile, pArrayType->m_pElemType/*, false*/);
			fprintf(outfile, "<span class=\"op\">[</span>");
			fprintf(outfile, "%lu", pArrayType->m_nSize);
			fprintf(outfile, "<span class=\"op\">]</span>");
#endif
		}
		break;

	case type_function:
		{
			return printHtml(document, NULL, (FunctionType*)pType/*, recurseClass*/);
		}
		break;

	default:
		{
		//	fprintf(outfile, "<span class=\"kw\">");
			Web::HTMLElement* element = (Web::HTMLElement*)document->createElementNS(NULL, span_str);
			element->set_className(kw_str);
			fragment->appendChild(element);

			StringW* str;

			switch (((PrimitiveType*)pType)->get_Kind())
			{
			case type_void:							str = void_str; break;
			case type_bool:							str = bool_str; break;
			case type_char:							str = char_str; break;
			case type_signed_char:					str = signed_char_str; break;
			case type_unsigned_char:				str = unsigned_char_str; break;
			case type_wchar:							str = WSTR("wchar_t"); break;
			case type_short_int:						str = short_str; break;
			case type_unsigned_short_int:			str = unsigned_short_str; break;
			case type_int:								str = int_str; break;
			case type_unsigned_int:					str = unsigned_int_str; break;
			case type_long_int:						str = long_str; break;
			case type_unsigned_long_int:			str = unsigned_long_str; break;
			case type_long_long:						str = long_long_str; break;
			case type_unsigned_long_long:			str = unsigned_long_long_str; break;
			case type_float:							str = float_str;	break;
			case type_double:							str = double_str;	break;

			default:
				ASSERT(0);
			}

			element->set_textContent(str);

		//	fprintf(outfile, "</span>");
		}
		break;
	}

	return fragment;
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, TemplateParameter* p)
{
	return printHtml(document, p->m_pType);
	//printf("%s", p->m_name->c_str());

	return NULL;
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* outfile, _TemplateArgType* pType)
{
#if 0
	fprintf(outfile, "%s", pType->m_name->c_str());
	if (pType->m_defaultArg)
	{
		fprintf(outfile, "=");
		if (pType->m_defaultArg->m_pType)
			printHtml(outfile, pType->m_defaultArg->m_pType/*, false*/);
		else
			fprintf(outfile, "%d", pType->m_defaultArg->m_value);
	}
#endif

	return NULL;
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, CDeclarator* pDeclarator, FunctionType* pType/*, bool recurseClass*/)
{
#if 0
	if (pType->m_pTemplateParams)
	{
		fprintf(outfile, "<span class=\"kw\">template</span><");
		for (int i = 0; i < pType->m_pTemplateParams->m_templateParams.size(); i++)
		{
			if (i > 0) fprintf(outfile, ",");
			printHtml(outfile, pType->m_pTemplateParams->m_templateParams[i]);
		}

		fprintf(outfile, "> ");
	}
#endif

	if (pDeclarator)
	{
		/*
		if (pDeclarator->m_virtual)
		{
			fprintf(outfile, "<span class=\"kw\">virtual</span> ");
		}

		if (pDeclarator->m_static)
		{
			fprintf(outfile, "<span class=\"kw\">static</span> ");
		}
		*/
	}

	Web::DocumentFragment* fragment = document->createDocumentFragment();

	if (pType->m_pReturnType)
	{
		fragment->appendChild(printHtml(document, pType->m_pReturnType));
	}

	if (pDeclarator)
	{
		Web::HTMLAnchorElement* a = (Web::HTMLAnchorElement*)document->createElementNS(NULL, a_str);

		a->set_href(pDeclarator->m_name->ToStringW());
		a->set_textContent(pDeclarator->m_name->ToStringW());

		fragment->appendChild(a);
		/*
		fprintf(outfile, " <a href=\"#%s\">", pDeclarator->m_name->c_str());
		fprintf(outfile, "%s", pDeclarator->m_name->c_str());
		fprintf(outfile, "</a>");
		*/
	}

	fragment->appendChild(document->createTextNode(open_paren_str));

	for (int i = 0; i < pType->m_parameters.m_parameters.size(); i++)
	{
		if (i > 0) fragment->appendChild(document->createTextNode(comma_str));

		fragment->appendChild(printHtml(document, pType->m_parameters.m_parameters[i].m_pType));
	}

	if (pType->m_parameters.m_bVarArg)
	{
		fragment->appendChild(document->createTextNode(threedots_str));
	}

	fragment->appendChild(document->createTextNode(close_paren_str));

	return fragment;

	if (pType->m_bConst)
	;//	fprintf(outfile, " <span class=\"kw\">const</span>");

	//printf("%s", pType->m_name->c_str());

	return NULL;
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, Typedef* pTypedef)
{
	Web::DocumentFragment* fragment = document->createDocumentFragment();

	Web::HTMLElement* element = (Web::HTMLElement*)document->createElementNS(NULL, span_str);
	element->set_className(kw_str);
	element->set_textContent(typedef_str);
	fragment->appendChild(element);

	fragment->appendChild(printHtml(document, pTypedef->m_pType));

	fragment->appendChild(document->createTextNode(pTypedef->m_name->ToStringW()));

	//element->put_textContent(

	//fprintf(outfile, "<span class=\"kw\">typedef</span> ");
	//printHtml(document, pTypedef->m_pType);
	//fprintf(outfile, " %s", pTypedef->m_name->c_str());

	return fragment;
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, EnumType* pEnum)
{
	Web::DocumentFragment* fragment = document->createDocumentFragment();
	return fragment;

	/*
	fprintf(outfile, "<div>");
	fprintf(outfile, "<span class=\"kw\">enum</span>");
	fprintf(outfile, " %s", pEnum->m_name->c_str());
	fprintf(outfile, "</div>");
	fprintf(outfile, "{");

	for (int i = 0; i < pEnum->m_deflist.size(); i++)
	{
		EnumDef& def = pEnum->m_deflist[i];

		fprintf(outfile, "<div>");
		fprintf(outfile, "%s <span class=\"op\">=</span> %d", def.m_name->c_str(), def.m_value);
		if (i < pEnum->m_deflist.size()-1) fprintf(outfile, ",");
		fprintf(outfile, "</div>");
	}

	//printHtml(outfile, pTypedef->m_pType);
	fprintf(outfile, "}\n");
	*/

	return NULL;
}

Web::DocumentFragment* printHtmlClassMembers(Web::HTMLDocument* document, ClassType* pClass, int ftypedef, int ffunction, int fstatic, int faccess)
{
	Web::DocumentFragment* fragment = NULL;
	bool bAny = false;

	for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
	{
		CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

		if (ftypedef == ~0 || (int)pMember->m_typedef == ftypedef)
		{
			if (fstatic == ~0 || (int)pMember->m_static == fstatic)
			{
				if (ffunction == ~0 || (pMember->m_pType->get_Kind() == type_function) == ffunction)
				{
					if (faccess == ~0 || pMember->m_access == faccess)
					{
						if (!bAny)
						{
							fragment = document->createDocumentFragment();

							bAny = true;
						//	fprintf(outfile, header);
						//	fprintf(outfile, "<h2>Public Methods</h2>");
						}

						fragment->appendChild(printHtml(document, pMember));
						//fprintf(outfile, "\n");
					}
				}
			}
		}
	}

	return fragment;
}

//XmlData::Document* doc;

/*
Web::HTMLElement* printHtmlBases(Web::HTMLDocument* document, ClassType* pClass)
{
}
*/

Web::DocumentFragment* printHtmlBases(Web::HTMLDocument* document, ClassType* pClass)
{
	Web::DocumentFragment* fragment = document->createDocumentFragment();
//	Web::HTMLElement* ul = (Web::HTMLElement*)document->createElementNS(NULL, WSTR("ul"));

	//fprintf(outfile, "<ul>");
	for (int i = 0; i < pClass->m_bases.size(); i++)
	{
		ClassType* pBase = pClass->m_bases[i]->m_pClass;

		Web::DocumentFragment* ul2 = printHtmlBases(document, pBase);

		fragment->appendChild(ul2);
	}
	//fprintf(outfile, "</ul>");

	Web::HTMLElement* ul = (Web::HTMLElement*)document->createElementNS(NULL, ul_str);
	Web::HTMLAnchorElement* a = (Web::HTMLAnchorElement*)document->createElementNS(NULL, a_str);
//	WCHAR buf[256];
//	swprintf(buf, L"%S.html", GetFilename(pClass)->c_str());
	a->set_href(GetFilename(pClass));
	ASSERT(pClass->m_name);
	a->set_textContent(pClass->m_name->ToStringW());
	ul->appendChild(a);
	fragment->appendChild(ul);

	return fragment;
}

void printHtmlClassMembers(Web::HTMLDocument* document, Web::Node* parentNode, StringW* header, ClassType* pClass, int ftypedef, int ffunction, int fstatic, int faccess)
{
	Web::DocumentFragment* fragment2 = printHtmlClassMembers(document, pClass, ftypedef, ffunction, fstatic, faccess);
	if (fragment2)
	{
		Web::HTMLElement* h = (Web::HTMLElement*)document->createElementNS(NULL, h2_str);
		h->set_textContent(header);

		parentNode->appendChild(h);

		parentNode->appendChild(fragment2);
	}
}

Web::DocumentFragment* printHtml(Web::HTMLDocument* document, ClassType* pClass)
{
	Web::DocumentFragment* fragment = printHtmlBases(document, pClass);

	/*
	Web::HTMLElement* ul = printHtmlBases(document, pClass);

	Web::DocumentFragment* fragment = document->createDocumentFragment();

	fragment->appendChild(ul);

	return fragment;
	*/

	/*
	fprintf(outfile, "<ul>");
	fprintf(outfile, "<div>");
	fprintf(outfile, "<a href=\"%s.html\">%s</a>", GetFilename(pClass)->c_str(), pClass->m_qname? pClass->m_qname->c_str(): NULL);
	fprintf(outfile, "</div>\n");
*/
	{
		//fprintf(outfile, "<ul>");
		for (int i = 0; i < pClass->m_derived.size(); i++)
		{
			ClassType* pDerivedClass = pClass->m_derived[i];

			/*
			fprintf(outfile, "<div>");
			fprintf(outfile, "<a href=\"%s.html\">%s</a>", GetFilename(pDerived)->c_str(), pDerived->m_qname? pDerived->m_qname->c_str(): NULL);
			fprintf(outfile, "</div>\n");
			*/
			Web::HTMLElement* div = (Web::HTMLElement*)document->createElementNS(NULL, div_str);
			Web::HTMLAnchorElement* a = (Web::HTMLAnchorElement*)document->createElementNS(NULL, a_str);
			WCHAR buf[256];
			swprintf(buf, L"%S.html", GetFilename(pDerivedClass)->c_str());
			a->set_href(new StringW(buf));
			a->set_textContent(pDerivedClass->m_name->ToStringW());
			div->appendChild(a);

			fragment->appendChild(div);

		}
		//fprintf(outfile, "</ul>");
	}
	//fprintf(outfile, "</ul>");

/*
	if (pClass->m_pTemplateParams)
	{
		fprintf(outfile, "<span class=\"kw\">template</span><");
		for (int i = 0; i < pClass->m_pTemplateParams->m_templateParams.size(); i++)
		{
			if (i > 0) fprintf(outfile, ",");
			printHtml(outfile, pClass->m_pTemplateParams->m_templateParams[i]);
		}

		fprintf(outfile, "> ");
	}
	*/

#if 0
	BufferImp<char> buffer;
	StringBuilderT<char> strbuilder(&buffer);
	pClass->Write(strbuilder);
	StringA* str = buffer.DetachToString();

	fprintf(outfile, "<div/>");
	fprintf(outfile, "<span class=\"kw\">class</span> ");

	if (pClass->m_pInstantiatedFrom)
	{
		fprintf(outfile, "<a href=\"dg\">%s</a>", str/*pClass->m_name*/->c_str(), pClass);

		fprintf(outfile, "&lt;");
		for (int i = 0; i < pClass->m_pInstantiatedFrom->m_templateArgs.size(); i++)
		{
			TemplatedClassArg* arg = pClass->m_pInstantiatedFrom->m_templateArgs[i];
			if (i > 0) fprintf(outfile, ",");
			if (arg->m_pType)
				printHtml(outfile, arg->m_pType);
			else
				fprintf(outfile, "%d", arg->m_value);
		}
		fprintf(outfile, "&gt;");
	}
	else
	{
		fprintf(outfile, "%s", str/*pClass->m_name*/->c_str(), pClass);
	}

	if (pClass->m_bases.size())
	{
		fprintf(outfile, " : ");

		for (int i = 0; i < pClass->m_bases.size(); i++)
		{
			BaseClass* baseclass = pClass->m_bases[i];
			if (i > 0) fprintf(outfile, ", ");
			fprintf(outfile, "<span class=\"kw\">public</span> ");
		//	printHtml(outfile, pClass->m_bases[i]->m_pClass/*, false*/);
			fprintf(outfile, "<a href=\"%s.html\">%s</a>", GetFilename(baseclass->m_pClass)->c_str(), baseclass->m_pClass->m_qname? baseclass->m_pClass->m_qname->c_str(): "no qname");
		}
	}

	fprintf(outfile, "</div>");
	fprintf(outfile, "{");
#endif

	static __live_object_ptr<StringW> public_methods = WSTR("Public Methods");
	static __live_object_ptr<StringW> protected_methods = WSTR("Protected Methods");
	static __live_object_ptr<StringW> static_public_methods = WSTR("Static Public Methods");
	static __live_object_ptr<StringW> static_protected_methods = WSTR("Static Protected Methods");

	static __live_object_ptr<StringW> public_members = WSTR("Public Members");
	static __live_object_ptr<StringW> protected_members = WSTR("Protected Members");
	static __live_object_ptr<StringW> static_public_members = WSTR("Static Public Members");
	static __live_object_ptr<StringW> static_protected_members = WSTR("Static Protected Members");

	// Methods
	printHtmlClassMembers(document, fragment, public_methods, pClass, false, true, false, 2);
	printHtmlClassMembers(document, fragment, protected_methods, pClass, false, true, false, 1);
	printHtmlClassMembers(document, fragment, static_public_methods, pClass, false, true, true, 2);
	printHtmlClassMembers(document, fragment, static_protected_methods, pClass, false, true, true, 1);

	// Members
	printHtmlClassMembers(document, fragment, public_members, pClass, false, false, false, 2);
	printHtmlClassMembers(document, fragment, protected_members, pClass, false, false, false, 1);
	printHtmlClassMembers(document, fragment, static_public_members, pClass, false, false, true, 2);
	printHtmlClassMembers(document, fragment, static_protected_members, pClass, false, false, true, 1);

	// Members
//	printHtmlClassMembers(document, fragment, WSTR("Public Members"), pClass, false, true, false, 2);
//	printHtmlClassMembers(document, fragment, WSTR("Protected Members"), pClass, false, true, false, 1);

	/*
	printHtmlClassMembers(document, pClass, "Protected Methods</h2>", false, true, false, 1);
	printHtmlClassMembers(document, pClass, "Private Methods</h2>", false, true, false, 0);

	printHtmlClassMembers(document, pClass, "Static Public Methods</h2>", false, true, true, 2);
	printHtmlClassMembers(document, pClass, "Static Protected Methods</h2>", false, true, true, 1);
	printHtmlClassMembers(document, pClass, "Static Private Methods</h2>", false, true, true, 0);

	// Members
	printHtmlClassMembers(document, pClass, "Public Members</h2>", false, false, false, 2);
	printHtmlClassMembers(document, pClass, "Protected Members</h2>", false, false, false, 1);
	printHtmlClassMembers(document, pClass, "Private Members</h2>", false, false, false, 0);

	printHtmlClassMembers(document, pClass, "Static Public Members</h2>", false, false, true, 2);
	printHtmlClassMembers(document, pClass, "Static Protected Members</h2>", false, false, true, 1);
	printHtmlClassMembers(document, pClass, "Static Private Members</h2>", false, false, true, 0);
	*/

	return fragment;

#if 0

#if 0
	{
		bool bAny = false;

		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			if (!pMember->m_typedef)
			{
				if (pMember->m_pType->GetKind() == type_function)
				{
					if (pMember->m_access == 2)
					{
						if (!bAny)
						{
							bAny = true;
							fprintf(outfile, "<h2>Public Methods</h2>");
						}

						printHtml(outfile, pMember);
						fprintf(outfile, "\n");
					}
				}
			}
		}
	}

	{
		bool bAny = false;

		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			if (!pMember->m_typedef)
			{
				if (pMember->m_pType->GetKind() == type_function)
				{
					if (pMember->m_access == 1)
					{
						if (!bAny)
						{
							bAny = true;
							fprintf(outfile, "<h2>Protected Methods</h2>");
						}

						printHtml(outfile, pMember);
						fprintf(outfile, "\n");
					}
				}
			}
		}
	}

	{
		bool bAny = false;

		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			if (!pMember->m_typedef)
			{
				if (pMember->m_pType->GetKind() == type_function)
				{
					if (pMember->m_access == 0)
					{
						if (!bAny)
						{
							bAny = true;
							fprintf(outfile, "<h2>Private Methods</h2>");
						}

						printHtml(outfile, pMember);
						fprintf(outfile, "\n");
					}
				}
			}
		}
	}

	{
		fprintf(outfile, "<h2>Members</h2>");

		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

			if (!pMember->m_typedef)
			{
				if (pMember->m_pType->GetKind() != type_function)
				{
					printHtml(outfile, pMember);
					fprintf(outfile, "\n");
				}
			}

			/*
			print(pMember->m_pType);
			printf(" ");
			printf("%s;", pMember->m_name->c_str());
			*/
		}
	}

	{
		fprintf(outfile, "<h2>Types</h2>");

		for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
		{
			CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];
			if (pMember->m_typedef)
			{
				if (pMember->m_pType->GetKind() == type_class)
				{
					printHtml(outfile, (ClassType*)pMember->m_pType);
				}
				else if (pMember->m_pType->GetKind() == type_typedef)
				{
					printHtml(outfile, (Typedef*)pMember->m_pType);
				}
				else if (pMember->m_pType->GetKind() == type_enum)
				{
					printHtml(outfile, (EnumType*)pMember->m_pType);
				}
				else
				{
					ASSERT(0);
				}
				fprintf(outfile, "\n");
			}

			/*
			print(pMember->m_pType);
			printf(" ");
			printf("%s;", pMember->m_name->c_str());
			*/
		}
	}
#endif

	fprintf(outfile, "}\n");
#endif

	return NULL;
}

class DocumentData : public XDM::IData
{
public:

	DocumentData(XDM::IData* child, StringW* childName)
	{
		m_child = child;
		m_childName = childName;
	}

	virtual XDM::IData* getParent()
	{
		return NULL;
	}

	virtual unsigned int getPosition()
	{
		return ~0;
	}

#if 0
	virtual System::StringW* getName()
	{
		ASSERT(0);
		return NULL;
		//return WSTR("#document");
	}
	virtual System::StringW* getNamespaceURI()
	{
		ASSERT(0);
		return NULL;
	}
#endif

	virtual XDM::IData* getRoot()
	{
		return this;
	}

	virtual unsigned int getAttributeCount()
	{
		return 0;
	}
	virtual System::Variant getAttributeValue(unsigned int index)
	{
		ASSERT(0);
		return Variant();
	}
	virtual System::StringW* getAttributeName(unsigned int index)
	{
		ASSERT(0);
		return 0;
	}

	virtual System::Type* getAttributeType(unsigned int index)
	{
		ASSERT(0);
		return NULL;
	}

	virtual System::Type* getChildType(unsigned int index)
	{
		ASSERT(0);
		return NULL;
	}

	virtual System::StringW* getAttributeNamespaceURI(unsigned int index)
	{
		return 0;
	}
	virtual unsigned int getChildCount()
	{
		return 1;
	}
	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}

	virtual System::StringW* getChildName(unsigned int index)
	{
		return m_childName;
	}

	virtual System::StringW* getChildNamespaceURI(unsigned int index)
	{
		return NULL;
	}
	virtual XDM::IData* getChildElement(unsigned int index)
	{
		ASSERT(index == 0);
		return m_child;
	}
	virtual System::StringW* getChildText(unsigned int index)
	{
		return NULL;
	}

	virtual System::Object* GetObject()
	{
		return NULL;
	}

	XDM::IData* m_child;
	StringW* m_childName;
};

map<Object*, XDM::IData*> objects;

class ObjectData;

class ComplexTypeData  : public XDM::IData
{
public:
	ComplexTypeData(XDM::IData* root, System::Object* object, XDM::IData* parent, unsigned int position);

	virtual XDM::IData* getParent()
	{
		return m_parent;
	}
	virtual unsigned int getPosition()
	{
		return m_position;
	}

	/*
	virtual System::StringW* getName()
	{
		return 0;
	}

	virtual System::StringW* getNamespaceURI()
	{
		return 0;
	}
	*/
	virtual XDM::IData* getRoot()
	{
		return m_root;
	}

	virtual unsigned int getAttributeCount()
	{
		return 0;
	}

	virtual System::Variant getAttributeValue(unsigned int index)
	{
		return 0;
	}
	virtual System::StringW* getAttributeName(unsigned int index)
	{
		return 0;
	}
	virtual System::StringW* getAttributeNamespaceURI(unsigned int index)
	{
		return 0;
	}
	virtual System::Type* getAttributeType(unsigned int index)
	{
		return 0;
	}

	virtual unsigned int getChildCount()
	{
		return 1;
	}
	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}
	virtual System::StringW* getChildName(unsigned int index)
	{
		ASSERT(index == 0);
		return m_object->GetType()->m_name->ToStringW();
	}
	virtual System::StringW* getChildNamespaceURI(unsigned int index)
	{
		ASSERT(index == 0);
		return NULL;
	}
	virtual System::Type* getChildType(unsigned int index)
	{
		return m_object->GetType();
	}
	virtual XDM::IData* getChildElement(unsigned int index);

	virtual System::StringW* getChildText(unsigned int index)
	{
		return 0;
	}

	virtual System::Object* GetObject()
	{
		return m_object;
	}

	XDM::IData* m_root;
	XDM::IData* m_parent;
	unsigned int m_position;
//	Property* m_parentProperty;
	Object* m_object;
//	ObjectData* m_content;
};

class CollectionData : public XDM::IData
{
public:
	CollectionData(XDM::IData* root, ICollection* collection, XDM::IData* parent, unsigned int position)
	{
		m_root = root;
		m_collection = collection;
		m_parent = parent;
		m_position = position;
	//	m_parentProperty = parentProperty;
	}

	virtual XDM::IData* getParent()
	{
		return m_parent;
	}
	virtual unsigned int getPosition()
	{
		return m_position;
	}

	/*
	virtual System::StringW* getName()
	{
		ASSERT(0);
		return 0;
	}

	virtual System::StringW* getNamespaceURI()
	{
		ASSERT(0);
		return 0;
	}
	*/
	virtual XDM::IData* getRoot()
	{
		return m_root;
	}

	virtual unsigned int getAttributeCount()
	{
		return 0;
	}

	virtual System::Variant getAttributeValue(unsigned int index)
	{
		ASSERT(0);
		return 0;
	}
	virtual System::StringW* getAttributeName(unsigned int index)
	{
		ASSERT(0);
		return 0;
	}
	virtual System::StringW* getAttributeNamespaceURI(unsigned int index)
	{
		ASSERT(0);
		return 0;
	}
	virtual System::Type* getAttributeType(unsigned int index)
	{
		ASSERT(0);
		return NULL;
	}

	virtual unsigned int getChildCount()
	{
		return m_collection->GetCount();
	}
	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}
	virtual System::StringW* getChildName(unsigned int index)
	{
		Object* child = m_collection->GetItem(index);
		return child->GetType()->get_Name()->ToStringW();
	}
	virtual System::StringW* getChildNamespaceURI(unsigned int index)
	{
		return NULL;
	}
	virtual System::Type* getChildType(unsigned int index)
	{
		Object* child = m_collection->GetItem(index);
		return child->GetType();
	}
	virtual XDM::IData* getChildElement(unsigned int index);

	virtual System::StringW* getChildText(unsigned int index)
	{
		return 0;
	}

	virtual System::Object* GetObject()
	{
		ASSERT(0);
		return NULL;//m_object;
	}

	XDM::IData* m_root;
	XDM::IData* m_parent;
	unsigned int m_position;
	ICollection* m_collection;
//	Property* m_parentProperty;
};

class ObjectData : public XDM::IData
{
public:

	ObjectData(XDM::IData* root, System::Object* object, XDM::IData* parent, unsigned int position)
	{
		m_root = root;
		m_object = object;
		//m_parentProperty = parentProperty;
		m_parent = parent;
		m_position = position;
	}

	virtual XDM::IData* getParent()
	{
		return m_parent;
	}

	virtual unsigned int getPosition()
	{
		return m_position;
	}

	virtual XDM::IData* getRoot()
	{
		return m_root;
	}

#if 0
	virtual System::StringW* getName()
	{
		ASSERT(0);
		return NULL;
		/*
		ASSERT(m_parentProperty);

		//return m_object->GetType()->m_qname->ToStringW();
		return m_parentProperty->get_PropertyName()->ToStringW();
		*/
	}

	virtual System::StringW* getNamespaceURI()
	{
		ASSERT(0);
		return NULL;
	}
#endif

	virtual unsigned int getAttributeCount()
	{
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			return 0;
		}
		else
		{
			ClassType* pClass = m_object->GetType();

			unsigned int count = 0;

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();
			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (IsSimple(pProperty))
				{
					++count;
				}

				++it;
			}

			return count;
		}
	}

	virtual System::Type* getAttributeType(unsigned int index)
	{
		ASSERT(0);
		return NULL;
	}

	virtual System::Type* getChildType(unsigned int index)
	{
		/*
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			Object* child = collection->GetItem(index);
			return child->GetType();
		}
		else
		*/
		{
			ClassType* pClass = m_object->GetType();

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();

			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					index--;
				}

				if ((int)index == -1)
					break;

				++it;
			}

			long result = pClass->m_pDispatch->Invoke(m_object, (*it).second->get_GetMethod(), NULL, 0);

			ASSERT(result != NULL);	// TODO

			Object* object = (Object*)result;

			return object->GetType();

		//	return (*it).second->get_GetType();
		}
	}

	virtual Variant getAttributeValue(unsigned int index)
	{
		ClassType* pClass = m_object->GetType();

		Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
		Dispatch::propertymap_t::iterator it = properties.begin();

		while (it != properties.end())
		{
			Property* pProperty = (*it).second;

			if (IsSimple(pProperty))
			{
				index--;
			}

			if ((int)index == -1)
				break;

			++it;
		}

		ASSERT(it != properties.end());

		Property* pProperty = (*it).second;

		long result = pClass->m_pDispatch->Invoke(m_object, pProperty->get_GetMethod(), NULL, 0);

		if (pProperty->get_GetType()->get_Kind() == type_enum)
		{
			return Variant((int)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_bool)
		{
			return Variant((bool)(result & 1));
		}
		else if (pProperty->get_GetType()->get_Kind() == type_char ||
					pProperty->get_GetType()->get_Kind() == type_signed_char)
		{
			return Variant((signed char)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_unsigned_char)
		{
			return Variant((unsigned char)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_short_int)
		{
			return Variant((short)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_unsigned_short_int)
		{
			return Variant((unsigned short)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_int)
		{
			return Variant((int)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_unsigned_int)
		{
			return Variant((unsigned int)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_pointer &&
				pProperty->get_GetType()->GetPointerTo() == typeid(StringA).GetType())
		{
			return Variant((StringA*)result);
		}
		else if (pProperty->get_GetType()->get_Kind() == type_pointer &&
				pProperty->get_GetType()->GetPointerTo() == typeid(StringW).GetType())
		{
			return Variant((StringW*)result);
		}
		else
			ASSERT(0);
	}

	virtual System::StringW* getAttributeName(unsigned int index)
	{
		ClassType* pClass = m_object->GetType();

		Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
		Dispatch::propertymap_t::iterator it = properties.begin();

		while (it != properties.end())
		{
			Property* pProperty = (*it).second;

			if (IsSimple(pProperty))
			{
				index--;
			}

			if ((int)index == -1)
				break;

			++it;
		}

		return (*it).second->get_PropertyName()->ToStringW();
	}

	virtual System::StringW* getChildName(unsigned int index)
	{
		/*
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			Object* child = collection->GetItem(index);
			return child->GetType()->get_Name()->ToStringW();
		}
		else
		*/
		{
			ClassType* pClass = m_object->GetType();

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();

			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					index--;
				}

				if ((int)index == -1)
					break;

				++it;
			}

			return (*it).second->get_PropertyName()->ToStringW();
		}
	}

	virtual System::StringW* getAttributeNamespaceURI(unsigned int index)
	{
		return NULL;
	}

	virtual System::StringW* getChildNamespaceURI(unsigned int index)
	{
		return NULL;
	}

	virtual unsigned int getChildCount()
	{
		/*
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			return collection->GetCount();
		}
		else
		*/
		{
			ClassType* pClass = m_object->GetType();

			unsigned int count = 0;

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();
			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					++count;
				}

				++it;
			}

			return count;
		}
	}

	virtual bool IsChildText(unsigned int index)
	{
		return false;
	}

	virtual XDM::IData* getChildElement(unsigned int index)
	{
#if 0
		if (ICollection* collection = dynamic_cast<ICollection*>(m_object))
		{
			Object* child = collection->GetItem(index);
			return new ObjectData(child, NULL/*(*it).second*/, this, index);
		}
		else
#endif
		{
			ClassType* pClass = m_object->GetType();

			Dispatch::propertymap_t& properties = pClass->m_pDispatch->GetProperties();
			Dispatch::propertymap_t::iterator it = properties.begin();

			int i = index;
			while (it != properties.end())
			{
				Property* pProperty = (*it).second;

				if (!IsSimple(pProperty))
				{
					i--;
				}

				if (i == -1)
					break;

				++it;
			}

			ASSERT(it != properties.end());

			long result = pClass->m_pDispatch->Invoke(m_object, (*it).second->get_GetMethod(), NULL, 0);
			if (result != 0)
			{
				Object* object = (Object*)result;

				/*
				map<Object*, XDM::IData*>::iterator oit = objects.find(object);
				if (oit != objects.end())
				{
					return (*oit).second;
				}
				else
					*/
				{
				//	ObjectData* p = new ObjectData(object, (*it).second, this, index);
				//	ObjectData* p = new ObjectData(object, this);
				//	objects.insert(map<Object*, XDM::IData*>::value_type(object, p));

					if (ICollection* collection = dynamic_cast<ICollection*>(object))
					{
						return new CollectionData(m_root, collection, /*(*it).second,*/ this, index);
					}
					else
					{
						return new ComplexTypeData(m_root, object, this, index);
					}

					//return p;
				}
			}
			else
				return NULL;
		}
	}

	virtual System::StringW* getChildText(unsigned int index)
	{
		return NULL;
	}

	static bool IsSimple(Property* pProperty)
	{
		Type* pReturnType = pProperty->get_GetType();

		if (pReturnType->get_Kind() == type_pointer &&

			(pReturnType->GetPointerTo() == typeid(StringA).GetType() ||
			pReturnType->GetPointerTo() == typeid(StringW).GetType()))
		{
			return true;
		}
		else
		{
			switch (pReturnType->get_Kind())
			{
			case type_bool:
			case type_char:
			case type_signed_char:
			case type_unsigned_char:
			case type_int:
			case type_short_int:
			case type_long_int:
			case type_unsigned_int:
			case type_unsigned_short_int:
			case type_unsigned_long_int:

			case type_enum:
				return true;
			}
		}

		return false;
	}

	virtual System::Object* GetObject()
	{
		return m_object;
	}

	XDM::IData* m_root;
	XDM::IData* m_parent;
	unsigned int m_position;
	//Property* m_parentProperty;
	System::Object* m_object;
};

XDM::IData* CollectionData::getChildElement(unsigned int index)
{
	Object* child = m_collection->GetItem(index);
//	return new ComplexTypeData(child, NULL/*m_parentProperty*/, this, index);
	return new ObjectData(m_root, child, this, index);
}

ComplexTypeData::ComplexTypeData(XDM::IData* root, System::Object* object, /*Property* parentProperty,*/ XDM::IData* parent, unsigned int position)
{
	m_root = root;
	m_parent = parent;
	m_position = position;

	m_object = object;

//	m_content = new ObjectData(m_object, this, 0);
}

XDM::IData* ComplexTypeData::getChildElement(unsigned int index)
{
	ASSERT(index == 0);

	return new ObjectData(m_root, m_object, this, 0);
}

Web::Element* ToElement(Web::Document* ownerDocument, XDM::IData* data, int elementpos, int level)
{
	if (level > 10)
		return NULL;

	StringW* name = data->getChildName(elementpos);

	Web::Element* element = ownerDocument->createElement(name);

	XDM::IData* childdata = data->getChildElement(elementpos);
	if (childdata)
	{
		XDM::IData* parent = data;

		/*
		while (parent)
		{
			if (parent->GetObject() == childdata->GetObject())
				break;

			parent = parent->getParent();
		}

		if (parent)
		{
			return NULL;
		}
		*/

		{
			unsigned int nattributes = childdata->getAttributeCount();
			for (int i = 0; i < nattributes; i++)
			{
				StringW* name = childdata->getAttributeName(i);
				ASSERT(name);

				StringW* data = childdata->getAttributeValue(i).ToStringW();
				if (data)
				{
					element->setAttribute(name, data);
				}
			}
		}

		{
			unsigned int nchildren = childdata->getChildCount();
			for (int i = 0; i < nchildren; i++)
			{
			//	StringW* name = childdata->getChildName(i);

				/*
				XDM::IData* parent = data;

				while (parent)
				{
					if (parent->GetObject() == childdata->GetObject())
						break;

					parent = parent->getParent();
				}

				if (parent == NULL)
					*/
				{
					Web::Element* childelement = ToElement(ownerDocument, childdata, i, level+1);
					if (childelement)
					{
						element->appendChild(childelement);
					}
				}
			}
		}
	}

	return element;
}


class test
{
public:
	char k;
	Web::CLDOMDocumentTraversalImpl<test> j;
};

class test3
{
public:
	char k;
	Web::DocumentCSSImpl<test3> j;
};

class test4
{
public:
	char k;
	Web::DocumentEditVALImpl<test4> j;
};

class test5
{
public:
	char k;
	XPath::XPathEvaluator j;
};

//	public IElementParallelTimeContainer,
//	public IDocumentEditVAL,	// ILNodeEditVAL

class test6
{
public:
	char k;
	CNotifyGetImpl<test6> j;
};

class test7
{
public:
	char k;
	CNotifySendImpl<test7> j;
};

struct base
{
};

class empty
{
public:
};

class small
{
public:
	char k;
};

class base2 : public base
{
public:
	Array<int> m_iterators;
	virtual void f3()
	{
	}
};

class base0 : public System::Object
{
public:
	virtual void f2()
	{
	}
};

class base_0
{
	int k;
};

class base_ : public base_0
{
public:
	virtual void f5()
	{
	}
};

class base3 : 
	public Web::Document,
	public Web::EventTarget,
	public Web::DocumentViewImpl<base3>,
	public Web::DocumentEvent,
	public Web::DocumentRangeImpl<base3>,

	public Web::CLDOMDocumentTraversalImpl<base3>//base2
{
public:
	virtual void f()
	{
	}
};

class test2
{
public:
	int x;
	double y;
//	int y;

	virtual void f()
	{
	}
};

class yyy_1 : public empty
{
public:
	//int x;
	//char y;

	virtual void f()
	{
	}
};

class yyy_2 : public yyy_1
{
public:
};

/*template <class T>*/ class /*LXUIEXT*/ CNotifyGetImpl/* :
	public INotifyGet*/
{
public:
	char k;
	/*
	int OnBeforeChange(NotifyType type, System::Object* targetObject, System::Object* immtargetObject, long dispID)
	{
		return S_OK;
	}
	*/

	/*
	int OnChanged(NotifyType type, IUnknown* targetObject, GUID targetObjectIID, DISPID dispID);
	*/

	/*
	int OnChanged(DISPID dispID)
	{
		return S_OK;
	}
	*/
};

class Derived1 : public Object,
	public empty
{
};

class Derived2 : public Object,
	public small
{
};

class Derived3 : public empty
{
public:
	virtual ~Derived3()
	{
	}
};

class Derived4 : public empty, public small
{
virtual void g()
{
}
};

#endif

#define _ATL_PACKING	8

#define offsetofclass(base, derived) \
       ((DWORD)(static_cast<base*>((derived*)_ATL_PACKING))-_ATL_PACKING)

class bigalign
{
	int k;
};

#pragma pack(push, 1)

class s
{
	char x;

	bigalign y;
};

#pragma pack(pop)

int Run()
{
	int size1 = sizeof(s);
	MessageBeep(-1);

#if 0
	{
		int off1 = offsetofclass(empty, Derived1);
		int size1 = sizeof(Derived1);

		int off2 = offsetofclass(small, Derived2);
		int size2 = sizeof(Derived2);

		int off3 = offsetofclass(empty, Derived3);
		int size3 = sizeof(Derived3);

		int off4 = offsetofclass(empty, Derived4);
		int off41 = offsetofclass(small, Derived4);
		int size4 = sizeof(Derived4);

		MessageBeep(-1);
	}

	{
		int size1 = sizeof(Web::PElement);
		int size2 = sizeof(Web::PElementBase);
		int align = __alignof(Web::PElement);

		int size3 = sizeof(Web::ProcessingInstruction);
		int size4 = sizeof(Web::ProcessingInstructionStylesheet);

		MessageBeep(-1);
	}

	{
		int size1 = sizeof(yyy_1);
//		int off2 = offsetof(yyy_2, z);
		MessageBeep(-1);
	}

	{
		int off1 = offsetof(test2, x);
		int off2 = offsetof(test2, y);
		int align = __alignof(test2);

		MessageBeep(-1);
	}
	{
	//	int off = offsetof(base3, m_m.k);

		int off1 = offsetofclass(Web::EventTarget, base3);
		int size1 = sizeof(Web::EventTarget);

		int off2 = offsetofclass(Web::DocumentViewImpl<base3>, base3);
		int size2 = sizeof(Web::DocumentViewImpl<base3>);

		int off3 = offsetofclass(Web::DocumentEvent, base3);
		int size3 = sizeof(Web::DocumentEvent);

		int off4 = offsetofclass(Web::DocumentRangeImpl<base3>, base3);
		int size4 = sizeof(Web::DocumentRangeImpl<base3>);

		int off5 = offsetofclass(Web::CLDOMDocumentTraversalImpl<base3>/*base2*/, base3);
	}

	int align4 = __alignof(Web::HTMLDocument);
	int align5 = __alignof(Web::Document);
	int align6 = __alignof(Web::EventTarget);
	int align7 = __alignof(Web::DocumentViewImpl<Web::HTMLDocument>);
	int align8 = __alignof(Web::DocumentEvent);

	int align0 = __alignof(Web::HTMLDocument);
	int off1 = offsetofclass(Web::DocumentRangeImpl<Web::HTMLDocument>, Web::HTMLDocument);
	int sizeof1 = sizeof(Web::DocumentRangeImpl<Web::HTMLDocument>);
	int align1 = __alignof(Web::DocumentRangeImpl<Web::HTMLDocument>);
	int off2 = offsetofclass(Web::CLDOMDocumentTraversalImpl<Web::HTMLDocument>, Web::HTMLDocument);
	int sizeof3 = sizeof(Web::CLDOMDocumentTraversalImpl<Web::HTMLDocument>);
	int align3 = __alignof(Web::CLDOMDocumentTraversalImpl<Web::HTMLDocument>);

	int off = offsetof(Web::CLDOMDocumentTraversalImpl<Web::HTMLDocument>, m_iterators);
//	{
		test t;
		int offset = offsetof(test, j);
		int size = sizeof(t.j);

		test3 t3;
		int offset3 = offsetof(test3, j);
		int size3 = sizeof(t3.j);

		test4 t4;
		int offset4 = offsetof(test4, j);
		int size4 = sizeof(t4.j);

		test5 t5;
		int offset5 = offsetof(test5, j);
		int size5 = sizeof(t5.j);

		test6 t6;
		int offset6 = offsetof(test6, j);
		int size6 = sizeof(t6.j);

		test7 t7;
		int offset7 = offsetof(test7, j);
		int size7 = sizeof(t.j);
//	}
#endif

#if 0
	if (false)
	{
		FILE* tfile = fopen("C:/mmstudio/Template.html", "r");

		TypeArchive* ar = new TypeArchive(TypeArchive::Mode_Load, new System::IO::FileByteStream(new StringA("C:/test.typeinfo"), System::IO::FileMode_Read));

		int ntypes;
		*ar >> ntypes;

		//doc = new XmlData::Document;

		printf("%d\n", ntypes);

		if (true)
		{
			Array<NamedType*> types;
			types.reserve(ntypes);

			{
				for (int i = 0; i < ntypes; i++)
				{
					NamedType* pType;
					*ar >> pType;

					{
						BufferImp<char> buffer;
						StringBuilderA strbuilder = StringBuilderA(&buffer);
						pType->Write(strbuilder);
						pType->m_qname = buffer.DetachToString();
					}

					types.push_back(pType);
				}
			}

		//sprintf(fullname, , filename->c_str());

			FILE* indexfile = fopen("C:/mmstudio/Documentation/index.html", "w");
			fprintf(indexfile, "<html>\n");
			fprintf(indexfile, "<body>\n");

			int start = 0;
			int end = 1000;
			if (end > ntypes) end = ntypes;

			for (int i = start; i < end; i++)
			{
				NamedType* pType = types[i];

				try
				{
					//if (pType->GetKind() == type_class || pType->GetKind() == type_enum || pType->GetKind() == type_typedef)
					{
						if (pType->m_name)
						{
							/*BufferImp<char> buffer;
							StringBuilderA strbuilder(&buffer);
							Mangler mangler;
							mangler.MangleType(pType, strbuilder);*/
							StringW* filename = GetFilename(pType);//buffer.DetachToString();

							char fullname[600];
							sprintf(fullname, "C:/mmstudio/Documentation/%S", filename->c_str());

							fprintf(indexfile, "<div>");
							fprintf(indexfile, "<a href=\"%S\">%s</a>", filename->c_str(), pType->m_qname->c_str());
							fprintf(indexfile, "</div>");

							Web::HTMLDocument* document = new Web::HTMLDocument;

							document->loadXML(WSTR("<html></html>"));

							if (document->get_documentElement())
							{
								Web::Element* container = document->get_documentElement();
							/*
							FILE* outfile = fopen(fullname, "w");
							if (outfile)
								
								rewind(tfile);

								int c;
								while ((c = fgetc(tfile)) != EOF)
								{
									fputc(c, outfile);
								}
								*/

								/*
								fprintf(outfile, "<html>\n");
								fprintf(outfile, "<link rel=\"stylesheet\" type=\"text/css\" href=\"main.css\">\n");
								*/
							//	fprintf(outfile, "<body>\n");

								Web::DocumentFragment* fragment;

								if (pType->get_Kind() == type_class)
								{
									ClassType* pClass = (ClassType*)pType;

									fragment = printHtml(document, pClass);

								//	fprintf(outfile, ";\n");

									{
										//fprintf(outfile, "<hr/>");
										//

										for (int i = 0; i < pClass->m_pScope->m_orderedDecls.size(); i++)
										{
											CDeclarator* pMember = pClass->m_pScope->m_orderedDecls[i];

											if (!pMember->m_typedef)
											{
												if (pMember->m_pType->get_Kind() == type_function)
												{
													BufferImp<char> buffer;
													StringBuilder<char> strbuilder(&buffer);

													strbuilder << "C:/MMStudio/DocumentationText/";

													MangleName(pClass, pMember, strbuilder);

													strbuilder << ".html";
													StringA* methodfilename = buffer.DetachToString();

													ASSERT(methodfilename->c_str());

													FILE* fp = fopen(methodfilename->c_str(), "r");
													if (fp == NULL)
													{
														fp = fopen(methodfilename->c_str(), "w");
														if (fp)
														{
															fprintf(fp, "<html>\n");
															fprintf(fp, "<body>\n");
															fprintf(fp, "%s\n", pClass->m_qname->c_str(), pMember->m_name->c_str());
															fprintf(fp, "</body>\n");
															fprintf(fp, "</html>\n");

															fclose(fp);
														}
													}
													else
													{
														fclose(fp);

														Web::HTMLDocument* methoddocument = new Web::HTMLDocument;
														methoddocument->load(methodfilename->ToStringW());
													}

													//fprintf(outfile, "<a name=\"%s\">", pMember->m_name->c_str());

													Web::HTMLElement* h3 = (Web::HTMLElement*)document->createElementNS(NULL, WSTR("h3"));
												//	fprintf(outfile, "<h3>");
													h3->appendChild(printHtml(document, pMember));
												//	fprintf(outfile, "\n");
												//	fprintf(outfile, "</h3>");
													//fprintf(outfile, "</a>");
													fragment->appendChild(h3);

													fragment->appendChild(document->createTextNode(WSTR("Some description here, Some description here, Some description here, Some description here, Some description here")));

													/*
													fprintf(outfile, "<div>\n");
													fprintf(outfile, "Some description here, Some description here, Some description here, Some description here, Some description here\n");
													fprintf(outfile, "Some description here, Some description here, Some description here, Some description here, Some description here\n");
													fprintf(outfile, "Some description here, Some description here, Some description here, Some description here, Some description here\n");
													fprintf(outfile, "Some description here, Some description here, Some description here, Some description here, Some description here\n");
													fprintf(outfile, "</div>\n");
													*/
												}
											}
											/*
											print(pMember->m_pType);
											printf(" ");
											printf("%s;", pMember->m_name->c_str());
											*/
										}
									}
								}
								else if (pType->get_Kind() == type_typedef)
								{
									fragment = printHtml(document, (Typedef*)pType);
									//fprintf(outfile, ";\n");
								}
								else if (pType->get_Kind() == type_enum)
								{
									fragment = printHtml(document, (EnumType*)pType);
									//fprintf(outfile, ";\n");
								}
								else
									ASSERT(0);



							//	fprintf(outfile, "</body>\n");
							//	fprintf(outfile, "</html>\n");

							//	fclose(outfile);

								container->appendChild(fragment);

								document->save((new System::StringA(fullname))->ToStringW());
							}
						}
					}
				}
				catch(int)
				{
					ASSERT(0);
					MessageBeep(-1);
					printf("oops\n");
				}
			}

			fprintf(indexfile, "</html>\n");
			fprintf(indexfile, "</body>\n");
			fclose(indexfile);

			exit(0);
		}
	}
#endif

#if WIN32
	if (false)
	{
		MSWindows::AllocConsole();

		HANDLE hErr = MSWindows::GetStdHandle(MSWindows::Std_Error_Handle);
		HANDLE hOut = MSWindows::GetStdHandle(MSWindows::Std_Output_Handle);

		freopen("c:/cpplog.txt", "a", stdout);
		freopen("c:/cpplog.txt", "a", stderr);

	//	freopen("CON:", "a", stdout);
	//	freopen("CON:", "a", stderr);

		printf("Hello\n");
	}
#endif

#if 1
	if (false)
	{
		FileByteStream file(ASTR("C:/test.java"));
		int size = file.GetSize();

		char* buffer = new char[size+1];
		file.Read(buffer, size);
		buffer[size] = 0;

		java::A_Class* p = java::Parse(new StringA(string_copy(buffer, size)));

		MessageBeep(-1);

#if 0
		java::A_ClassBodyDecls* bodydecls = p->bodydecls;
		while (bodydecls)
		{
			if (bodydecls->head)
			{
				if (bodydecls->head->kind == java::A_ClassBodyDecl::A_METHOD)
				{
					TRACE("%s\n", bodydecls->head->pMethod->name);

					java::A_Stms* stms = bodydecls->head->pMethod->body;
					while (stms)
					{
						CTStatement* tstm = java::TransStatement(stms->head);

						tstm = do_stm(tstm);

						T_stmList* stms2 = linearize(tstm);

						java::munch(stms2);

						stms = stms->tail;
					}
				}
			}

			bodydecls = bodydecls->tail;
		}
#endif
	}
#endif

#if AMIGA
	printf("Run\n");
#endif

#if WIN32

//	load_t2();

	InitTypes();
#endif

#if 0
	if (false)
	{
		TypeArchive ar(TypeArchive::Mode_Load, new System::IO::FileByteStream(new StringA("C:/test.typeinfo"), System::IO::FileMode_Read));

		Namespace* pGlobalNamespace;
		ar >> pGlobalNamespace;

		int ntypes;
		ar >> ntypes;

		printf("%d\n", ntypes);

		Array<NamedType*> types;
		types.reserve(ntypes);

		{
			for (int i = 0; i < ntypes; i++)
			{
				NamedType* pType;
				ar >> pType;

				{
					BufferImp<char> buffer;
					StringBuilderA strbuilder = StringBuilderA(&buffer);
					pType->Write(strbuilder);
					pType->m_qname = buffer.DetachToString();
				}

				types.push_back(pType);
			}
		}

		if (true)
		{
			// Namespace/Class Hierarchy

			Web::Document* stylesheet = new Web::GenericDocument;
			stylesheet->set_async(false);
			stylesheet->load(WSTR("C:/mmstudio/NamespaceHierarchy.xsl"));

			XSL::XSLT transformer(stylesheet);

			Web::Element* templateRule = (Web::Element*)stylesheet->get_documentElement()->get_firstChild();

			//CollectionObject<Array<NamedType*>, NamedType>* collection = new CollectionObject<Array<NamedType*>, NamedType>(types);

			DocumentData* documentData = new DocumentData(NULL, WSTR("Root"));
			ObjectData* pData = new ObjectData(documentData, pGlobalNamespace, documentData, 0);
			documentData->m_child = pData;

			Web::Document* resultDocument = new Web::GenericDocument;

			/*Web::DocumentFragment* fragment =*/ transformer.transform(resultDocument, templateRule, pData);

			resultDocument->save(WSTR("C:/mmstudio/Documentation/NamespaceHierarchy.html"));
		}
		else if (false)
		{
			// Class Hierarchy

			Web::Document* stylesheet = new Web::GenericDocument;
			stylesheet->set_async(false);
			stylesheet->load(WSTR("C:/mmstudio/ClassHierarchy.xsl"));

			XSL::XSLT transformer(stylesheet);

			Web::Element* templateRule = (Web::Element*)stylesheet->get_documentElement()->get_firstChild();

			CollectionObject<Array<NamedType*>, NamedType>* collection = new CollectionObject<Array<NamedType*>, NamedType>(types);

			DocumentData* documentData = new DocumentData(NULL, WSTR("Root"));
			CollectionData* pData = new CollectionData(documentData, collection, documentData, 0);
			documentData->m_child = pData;

			Web::Document* resultDocument = new Web::GenericDocument;

			/*Web::DocumentFragment* fragment =*/ transformer.transform(resultDocument, templateRule, pData);

			resultDocument->save(WSTR("C:/mmstudio/Documentation/ClassHierarchy.html"));
		}
		else
		{
			Web::Document* stylesheet = new Web::GenericDocument;
			stylesheet->set_async(false);
			stylesheet->load(WSTR("C:/mmstudio/stylesheet.xsl"));

			XSL::XSLT transformer(stylesheet);

			Web::Element* templateRule = (Web::Element*)stylesheet->get_documentElement()->get_firstChild();

			DocumentData* documentData = new DocumentData(NULL, WSTR("Root"));

			{
				int start = 0;
				int end = 500;
				if (end > ntypes) end = ntypes;

				int count = 0;

				for (int i = start; i < end; i++)
				{
					NamedType* pType = types[i];

					if (	pType->get_Kind() == type_class ||
							pType->get_Kind() == type_enum ||
							pType->get_Kind() == type_typedef)
					{
						NamedType* pClass = (NamedType*)pType;

						StringW* filename = GetFilename(pType);//buffer.DetachToString();

						WCHAR fullname[600];
						swprintf(fullname, L"C:/mmstudio/Documentation/%s", filename->c_str());

						XDM::IData* pData = new ComplexTypeData(documentData/*root*/, pClass, documentData/*parent*/, 0/*position*/);
						documentData->m_child = pData;

						if (false)
						{
							Web::Document* document = new Web::GenericDocument;

							Web::Element* element = ToElement(document, documentData, 0, 0/*level*/);

							document->appendChild(element);

							document->save(WSTR("c:/mmstudio/todoc.xml"));

						}

						Web::Document* resultDocument = new Web::GenericDocument;

						/*Web::DocumentFragment* fragment =*/ transformer.transform(resultDocument, templateRule, pData);

						resultDocument->save(new StringW(fullname));

						count++;
						if (count == 800)
							exit(0);
					}
				}
			}
		}

		exit(0);
	}
#endif

#if WIN32
	MSWindows::HDC hdc = MSWindows::GetDC(NULL);
	pixelsPerInch = MSWindows::GetDeviceCaps(hdc, LOGPIXELSX);
	MSWindows::ReleaseDC(NULL, hdc);
#else
	pixelsPerInch = 96;
#endif

#if 1
	__live_object_ptr<BrowserFrame> wndMain;

	{
		wndMain = new BrowserFrame;
		wndMain->Show();

		/*
		UI::DesktopScreen* pScreen = new UI::DesktopScreen;

	//	BrowserFrame* wndMain = new BrowserFrame;
		UI::WindowBase2* pBase2 = new UI::WindowBase2;

		UI::WindowHost* site = NULL;
		site = pScreen->OpenWindow();
		site->SetClient(pBase2);

		pBase2->set_VisualTree(wndMain);

		site->Show();
		*/
	}
#endif

#if AMIGA
//	return 0;
#endif

	/*
	LDraw::pSystemFonts = new LDraw::FontFamilyCollection("WinHD_C:WINDOWS/FONTS");
	LDraw::pSystemFonts2 = new LDraw::FontFamilyCollection("WinHD_C:WINDOWS/Copy_of_Fonts");

	Web::CHTMLWindow* pBrowser = new Web::CHTMLWindow;
	*/

//	printf("a\n");

	int nRet = 0;
	nRet = messageLoop.Run();

//	checkall();

	return nRet;
}

}	// System

#if WIN32

int APIENTRY wWinMain(MSWindows::HINSTANCE hInstance,
                     MSWindows::HINSTANCE hPrevInstance,
                     LPWSTR     lpCmdLine,
                     int       nCmdShow)
{
	try
	{
		LoadTypes(hInstance);

		LDraw::Init();
		return Run();
	}
	catch(Exception* e)
	{
		MSWindows::MessageBoxW(NULL, e->get_Reason()->c_str(), L"", MB_OK);
		return -1;
	}
}

#elif AMIGA

struct Library* P96Base;


namespace System
{
extern Heap* heap;
}

#include "../LFC/Linker.h"

extern System::Linker* plinker;

int main()
{
	printf("%d\n", plinker);

	ASSERT(pD == NULL);
	pD = new CVR;

	{
		gsymmap_t::iterator it = plinker->m_globsyms.begin();

		while (it != plinker->m_globsyms.end())
		{
			GlobalSymbol* psym = (*it).second;

			if (strstr(psym->m_name->c_str(), "9IAddChild"))
			{
				printf("symbol %s\n", psym->m_name->c_str());
			}

		//	if (psym->m_syms.size())
			{
				if (psym->setResolvedValue)
				{
					pD->m_symbols.insert(multimap<StringA*, ULONG_PTR, Ref_Less<StringA>, __gc_allocator>::value_type(psym->m_name, psym->setResolvedValue));
				}
			}

			++it;
		}
	}

	//printf("addr: %p\n", typeid(IAddChild));

	System::load_t2();

	{
		printf("sizeof(System::EventTargetImpl) = %d\n", sizeof(System::EventTargetImpl));
		printf("Calced: %d\n\n", typeid(System::EventTargetImpl).GetType()->get_sizeof());

		printf("sizeof(Array<list<UI::DependencyObject*> >) = %d\n", sizeof(Array<list<UI::DependencyObject*> >));
		printf("Calced: %d\n\n", typeid(Array<list<UI::DependencyObject*> >).GetType()->get_sizeof());

		printf("sizeof(UI::ExpandableObject) = %d\n", sizeof(UI::ExpandableObject));
		printf("Calced: %d\n\n", typeid(UI::ExpandableObject).GetType()->get_sizeof());

		printf("sizeof(UI::DependencyObject) = %d\n", sizeof(UI::DependencyObject));
		printf("Calced: %d\n\n", typeid(UI::DependencyObject).GetType()->get_sizeof());

		printf("sizeof(UI::Visual) = %d\n", sizeof(UI::Visual));
		printf("Calced: %d\n\n", typeid(UI::Visual).GetType()->get_sizeof());

		printf("sizeof(UI::UIElement) = %d\n", sizeof(UI::UIElement));
		printf("Calced: %d\n\n", typeid(UI::UIElement).GetType()->get_sizeof());

		printf("sizeof(UI::Control) = %d\n", sizeof(UI::Control));
		printf("Calced: %d\n\n", typeid(UI::Control).GetType()->get_sizeof());

		printf("offsetof(UI::Control.m_bFocus) = %d\n", offsetof(UI::Control, m_bFocus));
		printf("Calced: %d\n\n", typeid(UI::Control).GetType()->GetClass()->GetDeclarator(new StringA("m_bFocus"))->m_offset);

		printf("sizeof(UI::Border) = %d\n", sizeof(UI::Border));
		printf("Calced: %d\n\n", typeid(UI::Border).GetType()->get_sizeof());

		printf("sizeof(UI::Canvas) = %d\n", sizeof(UI::Canvas));
		printf("Calced: %d\n\n", typeid(UI::Canvas).GetType()->get_sizeof());

		printf("sizeof(System::ModifierType) = %d\n", sizeof(System::ModifierType));
		printf("Calced: %d\n\n", typeid(System::ModifierType).GetType()->get_sizeof());

		printf("sizeof(System::FunctionParameters) = %d\n", sizeof(System::FunctionParameters));
		printf("Calced: %d\n\n", typeid(System::FunctionParameters).GetType()->get_sizeof());

		printf("sizeof(System::FunctionType) = %d\n", sizeof(System::FunctionType));
		printf("Calced: %d\n\n", typeid(System::FunctionType).GetType()->get_sizeof());

		printf("sizeof(System::NamedType) = %d\n", sizeof(System::NamedType));
		printf("Calced: %d\n\n", typeid(System::NamedType).GetType()->get_sizeof());

		printf("sizeof(System::IClassOrNamespace) = %d\n", sizeof(System::IClassOrNamespace));
		printf("Calced: %d\n\n", typeid(System::IClassOrNamespace).GetType()->get_sizeof());

		printf("sizeof(System::Typedef) = %d\n", sizeof(System::Typedef));
		printf("Calced: %d\n\n", typeid(System::Typedef).GetType()->get_sizeof());

		printf("sizeof(System::ClassType) = %d\n", sizeof(System::ClassType));
		printf("Calced: %d\n\n", typeid(System::ClassType).GetType()->get_sizeof());

		printf("sizeof(System::EnumType) = %d\n", sizeof(System::EnumType));
		printf("Calced: %d\n\n", typeid(System::EnumType).GetType()->get_sizeof());

		printf("sizeof(System::TemplatedClass) = %d\n", sizeof(System::TemplatedClass));
		printf("Calced: %d\n\n", typeid(System::TemplatedClass).GetType()->get_sizeof());

		printf("sizeof(cstr_less) = %d\n", sizeof(cstr_less));
		printf("Calced: %d\n\n", typeid(cstr_less).GetType()->get_sizeof());

		printf("offsetof(System::ClassType.m_bVT) = %d\n", offsetof(System::ClassType, m_bVT));
		printf("Calced: %d\n\n", typeid(System::ClassType).GetType()->GetClass()->GetDeclarator(new StringA("m_bVT"))->m_offset);

		printf("offsetof(System::ClassType.m_sizeof) = %d\n", offsetof(System::ClassType, m_sizeof));
		printf("Calced: %d\n\n", typeid(System::ClassType).GetType()->GetClass()->GetDeclarator(new StringA("m_sizeof"))->m_offset);

		printf("offsetof(System::ClassType.m_rsizeof) = %d\n", offsetof(System::ClassType, m_rsizeof));
		printf("Calced: %d\n\n", typeid(System::ClassType).GetType()->GetClass()->GetDeclarator(new StringA("m_rsizeof"))->m_offset);

		printf("offsetof(System::ClassType.m_virtualSize) = %d\n", offsetof(System::ClassType, m_virtualSize));
		printf("Calced: %d\n\n", typeid(System::ClassType).GetType()->GetClass()->GetDeclarator(new StringA("m_virtualSize"))->m_offset);

		ASSERT(sizeof(XmlData::NodeList) == typeid(XmlData::NodeList).GetType()->get_sizeof());
		ASSERT(sizeof(XmlData::Node) == typeid(XmlData::Node).GetType()->get_sizeof());
		ASSERT(sizeof(XmlData::Attr) == typeid(XmlData::Attr).GetType()->get_sizeof());

		ASSERT(sizeof(LDraw::Font) == typeid(LDraw::Font).GetType()->get_sizeof());
		ASSERT(sizeof(LDraw::Commands) == typeid(LDraw::Commands).GetType()->get_sizeof());
		ASSERT(sizeof(LDraw::GraphicsMetafile) == typeid(LDraw::GraphicsMetafile).GetType()->get_sizeof());

		ASSERT(sizeof(UI::DependencyObject) == typeid(UI::DependencyObject).GetType()->get_sizeof());
		ASSERT(sizeof(UI::Visual) == typeid(UI::Visual).GetType()->get_sizeof());
		ASSERT(sizeof(UI::UIElement) == typeid(UI::UIElement).GetType()->get_sizeof());
		ASSERT(sizeof(UI::Control) == typeid(UI::Control).GetType()->get_sizeof());
		ASSERT(sizeof(UI::TextString) == typeid(UI::TextString).GetType()->get_sizeof());
		ASSERT(sizeof(UI::Button) == typeid(UI::Button).GetType()->get_sizeof());
		ASSERT(sizeof(UI::Border) == typeid(UI::Border).GetType()->get_sizeof());
		ASSERT(sizeof(UI::Canvas) == typeid(UI::Canvas).GetType()->get_sizeof());
		ASSERT(sizeof(UI::TextEdit) == typeid(UI::TextEdit).GetType()->get_sizeof());
		ASSERT(sizeof(UI::FrameWindow) == typeid(UI::FrameWindow).GetType()->get_sizeof());
		ASSERT(sizeof(UI::ChildWindowContainer) == typeid(UI::ChildWindowContainer).GetType()->get_sizeof());
		ASSERT(sizeof(UI::ChildWindow) == typeid(UI::ChildWindow).GetType()->get_sizeof());
		ASSERT(sizeof(UI::CUIFrameImpl) == typeid(UI::CUIFrameImpl).GetType()->get_sizeof());
		ASSERT(sizeof(BrowserFrame) == typeid(BrowserFrame).GetType()->get_sizeof());
		ASSERT(sizeof(ActionScript::StkElt) == typeid(ActionScript::StkElt).GetType()->get_sizeof());

		ASSERT(offsetof(BrowserFrame, m_edit) == typeid(BrowserFrame).GetType()->GetClass()->GetDeclarator(new StringA("m_edit"))->m_offset);
	}
	
	gc();

//	ASSERT(0);

#if 0
		ULONG heapsize = heap->m_next - (heap->m_data);
#else
		ULONG heapsize = heap->m_next - (heap->m_data+heap->m_size);
#endif

	{
		printf("heapsize: %d.%d MB\n", heapsize / (1024*1024), heapsize % (1024*1024));
	}

	printf("Here\n");

	//printf("%s\n", typeid(System::Type).name());
	printf("%s\n", dynamic_cast<NamedType*>(typeid(System::Type).GetType())->m_qname->c_str());

//	return 0;
//	map<DWORD,DWORD> x;
//	x.insert(map<DWORD,DWORD>::value_type(0, 0));

	LDraw::Init();

#if 1
	P96Base = (struct Library*)execOpenLibrary(SysBase, "Picasso96API.library", 2);
	if (P96Base == NULL)
		return -10;

	UI::pUserPort = CreateMsgPort();
#endif

	int nRet = Run();

#if 1
	DeleteMsgPort(UI::pUserPort);

	execCloseLibrary(SysBase, (struct Library*)P96Base);
#endif

//	Delay(50*7);

	return nRet;
}

#endif
