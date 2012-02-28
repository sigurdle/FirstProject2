#include "stdafx.h"
#include "GUI2.h"

namespace System
{
namespace Gui
{

Object* IDataObjectPtr::GetData(UINT nFormat)
{
	FORMATETC fetc;
	fetc.cfFormat = nFormat;
	fetc.ptd = NULL;
	fetc.tymed = TYMED_HGLOBAL;
	fetc.dwAspect = DVASPECT_CONTENT;
	fetc.lindex = -1;

	STGMEDIUM stgm = {0};
	stgm.tymed = TYMED_HGLOBAL;  
	HRESULT hr = m_p->GetData(&fetc, &stgm);
	if (FAILED(hr))
	{
		return nullptr;
	}

	Object* ret = nullptr;

	if (stgm.tymed == TYMED_HGLOBAL)
	{
		if (nFormat == CF_TEXT)
		{
			String str;
			char* p = (char*)GlobalLock(stgm.hGlobal);
			if (p)
			{
				str = p;
				GlobalUnlock(stgm.hGlobal);
			}

			ret = str.Detach();
		}
		else if (nFormat == CF_UNICODETEXT)
		{
			String str;
			WCHAR* p = (WCHAR*)GlobalLock(stgm.hGlobal);
			if (p)
			{
				str = p;
				GlobalUnlock(stgm.hGlobal);
			}

			ret = str.Detach();
		}
		else if (nFormat == CF_HDROP/* || nFormat == CF_PRINTERS*/)
		{
			DROPFILES* dropfiles = (DROPFILES*)GlobalLock(stgm.hGlobal);
			if (dropfiles)
			{
				List<String>* l = new List<String>;

				if (dropfiles->fWide)
				{
					WCHAR* p = (WCHAR*)((byte*)dropfiles + dropfiles->pFiles);

					while (*p)
					{
						size_t len = wcslen(p);
						l->Add(p);

						p += len+1;
					}
				}
				else
				{
					char* p = (char*)dropfiles + dropfiles->pFiles;

					while (*p)
					{
						size_t len = strlen(p);
						l->Add(p);

						p += len+1;
					}
				}

				GlobalUnlock(stgm.hGlobal);

				ret = l;
			}
		}
		else if (nFormat == CF_DIBV5)
		{
		}
	}
	else if (stgm.tymed == TYMED_ENHMF)
	{
		if (nFormat == CF_ENHMETAFILE)
		{
			HENHMETAFILE hEnhMeta = stgm.hEnhMetaFile;
		}
	}

	if (stgm.pUnkForRelease)
		stgm.pUnkForRelease->Release();
	else
		ReleaseStgMedium(&stgm);

	return ret;
}

Object* IDataObjectPtr::GetData(StringIn format)
{
	UINT nFormat = DataFormats::GetDataFormat(format).get_Id();

	return GetData(nFormat);
}

Object* IDataObjectPtr::GetData(Type* format)
{
	if (format == typeid(String))
	{
		return GetData(CF_UNICODETEXT);
	}

	return nullptr;
}

bool IDataObjectPtr::GetDataPresent(UINT nFormat)
{
	FORMATETC fetc;
	fetc.cfFormat = nFormat;
	fetc.ptd = nullptr;
	fetc.tymed =
		TYMED_HGLOBAL |
		TYMED_ENHMF |
		TYMED_ISTREAM |
		TYMED_ISTORAGE;

	fetc.dwAspect = DVASPECT_CONTENT;
	fetc.lindex = -1;

	return m_p->QueryGetData(&fetc) == S_OK;
}

bool IDataObjectPtr::GetDataPresent(StringIn format)
{
	UINT nFormat = DataFormats::GetDataFormat(format).get_Id();
	return GetDataPresent(nFormat);
}

bool IDataObjectPtr::GetDataPresent(Type* format)
{
	return false;
}

void IDataObjectPtr::SetData(UINT nFormat, Object* data)
{
	ASSERT(0);
}

void IDataObjectPtr::SetData(StringIn format, Object* data)
{
	UINT nFormat = DataFormats::GetDataFormat(format).get_Id();
	SetData(nFormat, data);
}

void IDataObjectPtr::SetData(Type* format, Object* data)
{
	ASSERT(0);
}

vector<String> IDataObjectPtr::GetFormats()
{
	vector<String> formats;

	ComPtr<IEnumFORMATETC> enumfmt;
	m_p->EnumFormatEtc(DATADIR_GET, &enumfmt);

	FORMATETC fetc;
	DWORD fetched;
	while ((enumfmt->Next(1, &fetc, &fetched) == S_OK) && fetched)
	{
		formats.push_back(DataFormats::GetDataFormatString(fetc.cfFormat));
	}

	return formats;
}

bool IDataObjectPtr::ContainsFileDropList()
{
	return GetDataPresent(CF_HDROP);
}

List<String>* IDataObjectPtr::GetFileDropList()
{
	return dynamic_cast<List<String>*>(GetData(CF_HDROP));
}

}	// Gui
}	// System
