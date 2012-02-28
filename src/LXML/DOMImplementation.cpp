#include "stdafx.h"
#include "LXML2.h"
#include "DOMImplementation.h"
#include "DOMBuilder.h"

typedef System::Object* (*CreateObjectFN)(const WCHAR* name);

#define OLESTR(x)	L##x

namespace System
{

namespace Web
{

//ILDOMImplementation* g_implementation;

struct Feature
{
	ImmutableString<WCHAR> feature;
	ImmutableString<WCHAR> version;
};

static Feature features[] =
{
	WSTR("core"), WSTR("1.0"),
	WSTR("core"), WSTR("2.0"),
	WSTR("core"), WSTR("3.0"),

	WSTR("xml"), WSTR("1.0"),
	WSTR("xml"), WSTR("2.0"),
	WSTR("xml"), WSTR("3.0"),

	WSTR("views"), WSTR("2.0"),

	WSTR("range"), WSTR("2.0"),

	WSTR("traversal"), WSTR("2.0"),

	WSTR("stylesheets"), WSTR("2.0"),

	WSTR("css"), WSTR("2.0"),

	WSTR("events"), WSTR("2.0"),
//	WSTR("events"), WSTR("3.0"),

	WSTR("uievents"), WSTR("2.0"),
	WSTR("uievents"), WSTR("3.0"),

	WSTR("mouseevents"), WSTR("2.0"),
	WSTR("mouseevents"), WSTR("3.0"),

	WSTR("mutationevents"), WSTR("2.0"),
	WSTR("mutationevents"), WSTR("3.0"),

	WSTR("textevents"), WSTR("3.0"),
	WSTR("keyboardevents"), WSTR("3.0"),
};

/////////////////////////////////////////////////////////////////////////////
// DOMImplementation

DOMImplementation* DOMImplementation::s_DOMImplementation;

DOMImplementation::DOMImplementation()
{
#if WIN32
	{
		HINSTANCE hInstance = LoadLibraryW(L"LHTML.dll");
		if (hInstance)
		{
			CreateObjectFN fn = (CreateObjectFN)GetProcAddress(hInstance, "CreateObject");

			IXMLImplementation* impl = dynamic_cast<IXMLImplementation*>(fn(OLESTR("HTMLImplementation")));

			m_implList.Add(impl);
		}
	}

	if (true)
	{
		HINSTANCE hInstance = LoadLibraryW(L"LSVG.dll");
		if (hInstance)
		{
			CreateObjectFN fn = (CreateObjectFN)GetProcAddress(hInstance, "CreateObject");

			IXMLImplementation* impl = dynamic_cast<IXMLImplementation*>(fn(OLESTR("SVGImplementation")));

			m_implList.Add(impl);
		}
	}

#else

	Module* pModule = FindModule("LHTML.dll");
	if (pModule)
	{
		CreateObjectFN fn = (CreateObjectFN)pModule->GetProc("CreateObject");
		IXMLImplementation* impl = dynamic_cast<IXMLImplementation*>(fn("HTMLImplementation"));

		m_implList.Add(impl);
	}

#endif
}

DOMImplementation::~DOMImplementation()
{
}

// static
DOMImplementation* DOMImplementation::get_DOMImplementation()
{
	if (s_DOMImplementation == NULL)
	{
		s_DOMImplementation = new DOMImplementation;
	}

	return s_DOMImplementation;
}

#if 0
int CLDOMImplementation::FinalConstruct()
{
#if 0	// TODO
	g_preferences.LoadIfNotLoaded();
#endif

#if _WINDOWS
	// Add-ins
	{
		CComPtr<ICatInformation> catinfo;
		HRESULT hr = S_OK;
 
		hr = CoCreateInstance(CLSID_StdComponentCategoriesMgr,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_ICatInformation,
			(LPVOID*)&catinfo);

		if (SUCCEEDED(hr))
		{
			CRegKey clsidkey;
			clsidkey.Open(HKEY_CLASSES_ROOT, "CLSID");

			CATID impl[1];
			impl[0] = CATID_LXMLPlugin;

			CComPtr<IEnumCLSID> enumClsid;
			catinfo->EnumClassesOfCategories(1, impl, 0, NULL, &enumClsid);

			CLSID clsid;
			ULONG fetched;
			while ((enumClsid->Next(1, &clsid, &fetched) == S_OK) && (fetched == 1))
			{
				/*
				LPOLESTR clsidstr;
				StringFromCLSID(clsid, &clsidstr);

				CRegKey key;
				key.Open(clsidkey, _bstr_t(clsidstr));

				CoTaskMemFree(clsidstr);
				*/

				CComPtr<IUnknown> unk;
				unk.CoCreateInstance(clsid);

				CComQIPtr<ILXMLImplementation> impl = unk;

				if (impl)
				{
					m_implList.Add(impl.Detach());
				}
			}
		}
	}
#endif // _WINDOWS

//		g_implementation = this;
	return 0;
}

void CLDOMImplementation::FinalRelease()
{
//		g_implementation = NULL;
}
#endif

bool DOMImplementation::hasFeature(StringIn feature, StringIn version)
{
	if (feature == nullptr) raise(ArgumentNullException());

	size_t count = _countof(features);
	for (size_t i = 0; i < count; ++i)
	{
		if (feature.CompareNoCase(&features[i].feature) == 0 &&
			(version.IsEmpty() || version.CompareNoCase(&features[i].version) == 0))
		{
			return true;
		}

		++i;
	}

	return false;
}

ILSParser* DOMImplementation::createLSParser(short mode, StringIn schemaType)
{
	ASSERT(0);
	/*
	CComObject<CLLSParser>* pBuilder;
	CComObject<CLLSParser>::CreateInstance(&pBuilder);
	if (pBuilder)
	{
		(*pVal = pBuilder)->AddRef();
	}
	else
		*pVal = NULL;
		*/

	return NULL;
}

DocumentType* DOMImplementation::createDocumentType(StringIn qualifiedName, StringIn publicId, StringIn systemId)
{
	DocumentType* pDocType = new DocumentType;
	pDocType->m_name = qualifiedName;
	pDocType->m_publicId = publicId;
	pDocType->m_systemId = systemId;

	return pDocType;
}

Document* DOMImplementation::createDocument(StringIn namespaceURI, StringIn qualifiedName, DocumentType *doctype)
{
	ASSERT(0);
	return NULL;
}

}	// Web
}
