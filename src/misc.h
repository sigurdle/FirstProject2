#ifndef __MISC_H
#define __MISC_H

#if WIN32

struct IDataObject;

class COleDataObjectWrapper
{
protected:
	IDataObject * m_pDataObject;

public:
	void Attach(IDataObject * dataObject)
	{
		m_pDataObject = dataObject;
	}

#if 0

	HGLOBAL GetGlobalData(UINT nClipboardFormat)
	{
		FORMATETC fetc = {0};
		fetc.cfFormat = nClipboardFormat;
		fetc.tymed = TYMED_HGLOBAL;
		fetc.dwAspect = DVASPECT_CONTENT;
		fetc.lindex = -1;			//	give me all

		STGMEDIUM medium = {0};
		medium.tymed = TYMED_HGLOBAL;

		HRESULT hr = m_pDataObject->GetData(&fetc, &medium);
		if (SUCCEEDED(hr))
		{
			return medium.hGlobal;
		}

		return NULL;
	}

#endif

};
#endif

#endif
