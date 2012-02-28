#include "stdafx.h"
#include "LMediaImpl.h"
#include "LFilterGraph.h"
#include "SystemClock.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>
/*
#if WIN32

extern "C"
{
_CRTIMP void   __cdecl _makepath(char *, const char *, const char *, const char *,
        const char *);
}

#endif
*/

#if AMIGA
#include "../amiga_header.h"
#endif

using namespace System;

//extern LFCEXT std::map<StringA,Module*> _Modules;
LFCEXT Module* FindModule(StringA* name);

namespace System
{

//LFCEXT void LoadTypes(MSWindows::HINSTANCE hModule);

namespace MediaShow
{

typedef Object* (*CreateObjectFN)(const WCHAR* name);

IBaseFilter* LoadFilter(CDispLRegFilter* pRegFilter)
{
	IBaseFilter* filter = NULL;

	size_t nsep = pRegFilter->m_Src.find('#');
	if (nsep == String::npos)
	{
		return NULL;
	}

//	StringW* dllname = pRegFilter->m_Src->LeftOf(nsep);//new StringW(true, pRegFilter->m_Src->begin(), nsep/*sep - pRegFilter->m_Src->c_str()*/);
	String::_SubString classname = pRegFilter->m_Src.RightOf(nsep+1);

	if (nsep > 511)
	{
		return NULL;
	}

#if WIN32

//	HMODULE hLib = LoadLibrary("C:/mmstudio/extras/lpcx/debug/lpcx.dll");
	//StringA* dllname = dllname->ToStringA();
	WCHAR buffer[512];
	wcsncpy_s(buffer, CStringw(pRegFilter->m_Src), nsep);
	buffer[nsep] = 0;
	HMODULE hLib = LoadLibraryW(buffer);//dllname->c_str()/*A->c_str()*//*"C:/mmstudio/extras/iff/debug/iff.dll"*/);
	if (hLib)
	{
	//	LoadTypes(hLib);	// TODO, remove

		CreateObjectFN fn = (CreateObjectFN)GetProcAddress(hLib, "CreateObject");
		if (fn)
		{
			ASSERT(0);
#if 0
			Object* obj = fn(CString(classname));
			filter = dynamic_cast<IBaseFilter*>(obj);
#endif
		}
	}

#elif AMIGA

	Module* pModule = FindModule(dllname->ToStringA());
	if (pModule)
	{
		printf("Located module %s\n", dllname->c_str());

		CreateObjectFN fn = (CreateObjectFN)pModule->GetProc(new StringA("CreateObject"));
		if (fn)
		{
			Object* obj = fn(classname);

			filter = dynamic_cast<IBaseFilter*>(obj);
		}
	}
	else
		printf("Failed to locate module %s\n", dllname->c_str());

	// TODO
//	Object* obj = CreateObject(classname);
//	filter = dynamic_cast<IBaseFilter*>(obj);

#else
	// TODO
	filter = NULL;
#endif

	return filter;
}

RegFilters::RegFilters()
{
	return;
#if WIN32
	WCHAR* dirName = L"C:/MMStudio/src/bin/LMediaFilters";
#else
	char* dirName = "WinHD_C:/MMStudio/src/bin/LMediaFilters";
#endif

#if WIN32
	WCHAR searchPath[512];
	_wmakepath_s(searchPath, NULL, dirName, L"*", NULL);

//	sprintf(searchPath, "%s/*", directoryName);
	WIN32_FIND_DATAW wfd;
	HANDLE hFindFile = FindFirstFileW(searchPath, &wfd);
	if (hFindFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				// Maybe recurse ??
			}
			else
			{
				int len = wcslen(wfd.cFileName);
				if (len >= 4 && !_wcsicmp(wfd.cFileName+len-4, L".xml"))
				{
					WCHAR fullpath[512];
					swprintf_s(fullpath, L"%s/%s", dirName, wfd.cFileName);

					CDispLRegFilter* p = new CDispLRegFilter;
					if (p)
					{
						XmlData::Document* document = new XmlData::Document;
						if (document)
						{
							bool success = document->load(fullpath);

							XmlData::Element* documentElement = document->get_documentElement();

							if (documentElement)
							{
								p->BuildRegFilter(documentElement);
							}
						}

					//	p->m_pFilterGraph = this;

						m_RegFilters.Add(p);
					}

				}
			}
		}
		while (FindNextFileW(hFindFile, &wfd));

		FindClose(hFindFile);
	}
#else

	struct FileInfoBlock* fib = (struct FileInfoBlock*)AllocDosObject(DOS_FIB, NULL);
	BPTR lock;

	if (fib != NULL)
	{
		lock = dosLock(DOSBase, const_cast<char*>(dirName), ACCESS_READ);
		if (lock != NULL)
		{
			Examine(lock, fib);

			char* fullpath = new char[1024];

			while (ExNext(lock, fib) != 0)
			{
				if (fib->fib_DirEntryType > 0)	// directory
				{
					// Maybe recurse ???
				}
				else
				{
					int len = strlen(fib->fib_FileName);

					strcpy(fullpath, dirName);
					AddPart(fullpath, fib->fib_FileName, 1024);

					CDispLRegFilter* p = new CDispLRegFilter;
					if (p)
					{
						XmlData::Document* document = new XmlData::Document;
						if (document)
						{
							bool success = document->load(new StringA(fullpath));

							XmlData::Element* documentElement = document->get_documentElement();

							if (documentElement)
							{
								p->BuildRegFilter(documentElement);
							}
						}

						m_RegFilters.Add(p);
					}
				}
			}

			delete[] fullpath;

			if (IoErr() != ERROR_NO_MORE_ENTRIES)
			{
				//MessageBox(NULL, "dos Error", "", MB_OK);
			}
			dosUnLock(DOSBase, lock);
		}

		FreeDosObject(DOS_FIB, fib);
	}
#endif

#if 0
	CRegKey filterCatKey;
	filterCatKey.Open(HKEY_CURRENT_USER, "Software\\Lerstad\\LMedia");
	if (filterCatKey)
	{
		TCHAR name[512];
		DWORD cbname = 512;
		DWORD n = 0;
		while (::RegEnumKeyEx(filterCatKey, n, name, &cbname, NULL, NULL, NULL, NULL) != ERROR_NO_MORE_ITEMS)
		{
			CLSID clsid;
			if (SUCCEEDED(CLSIDFromString(_bstr_t(name), &clsid)))
			{
				CDispLRegFilter* p = new CDispLRegFilter;
				//CComObject<CDispLRegFilter>::CreateInstance(&p);
				if (p)
				{
					CRegKey filterKey;
					filterKey.Open(filterCatKey, name);

					TCHAR value[4096];
					DWORD cb = 4096;
					filterKey.QueryValue(value, NULL, &cb);

					LXML::CLDOMDocument* document = new LXML::CLDOMDocument;
				//	document.CoCreateInstance(CLSID_LDOMDocument);
					if (document)
					{
						bool success = document->loadXML(A2W(value));

						LXML::Element* documentElement = document->get_documentElement();

						if (documentElement)
						{
							p->BuildRegFilter(documentElement);
						}
					}

			//		p->AddRef();
					p->m_pFilterGraph = this;
				//	p->m_Name = L"LMedia.URLSource";
					p->m_clsid = clsid;

					m_RegFilters.push_back(p);
				}
			}

			cbname = 512;
			n++;
		}
	}
#endif
}

RegFilters g_RegFilters;

/////////////////////////////////////////////////////////////////////////////
// FilterGraph

FilterGraph::FilterGraph()// : m_cwnd("static", this, 1)
{
#if WIN32
	m_wnd = new Wnd;
	m_wnd->m_graph = this;
	m_wnd->Create(NULL, gm::Recti(), NULL, WS_POPUP);
#endif

//		m_streams = NULL;
	//m_RegFilters = NULL;

//	m_currentPosition = 0;

	m_hThread = NULL;
	m_threadId = 0;

	m_Filters = new CDispLCollection;

	m_state = State_Stopped;

//	m_RegFilters = new CDispLCollection;

}

FilterGraph::~FilterGraph()
{
#if WIN32
	/*
	if (m_hWnd)
	{
		::DestroyWindow(m_hWnd);
	}
	*/
	delete m_wnd;
#endif

	delete m_Filters;
}

HANDLE FilterGraph::GetEventHandle() const
{
	return m_hEvent;
}

#if 0
int FilterGraph::FinalConstruct()
{
	ErrorCode hr;


	/*
	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"LMedia.URLSource";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"LMedia.ByteArray";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"IFF.IFFDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"SunAU.AUDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"GIF.GIFDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

		{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"GIF.GIFEncoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"TIFF.TIFFDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"PCX.PCXDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"VOC.VOCDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"JPEG.JPEGDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"PNG.PNGDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"MPEG.MPEGDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"LMPEGVideo.LMPEGVideoDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"LMPEG4.MP4File";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"LMPEGAudio.LMPEGAudioDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"SVGM.SVGMDecoder";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}

	{
		CComObject<CDispLRegFilter>* p;
		CComObject<CDispLRegFilter>::CreateInstance(&p);
		p->AddRef();
		p->m_pFilterGraph = this;
		p->m_Name = L"LQuant.LQuantizer";
		CLSIDFromString(p->m_Name, &p->m_clsid);
		m_RegFilters->m_items.Add(p);
	}
	*/

	return 0;
}

void FilterGraph::FinalRelease()
{
	if (m_streams)
	{
		m_streams->Release();
		m_streams = NULL;
	}
}
#endif

#if 0
ErrorCode FilterGraph::AddFilter(ILBaseFilter *pFilter, DispILFilter* *pVal)
{
#if 0
	CComObject<CDispLFilter>* pDispFilter;
	CComObject<CDispLFilter>::CreateInstance(&pDispFilter);
	if (pDispFilter)
	{
		pDispFilter->AddRef();

		pDispFilter->m_pFilterGraph = this;
		pDispFilter->m_p = pFilter;
#endif
		m_Filters->m_items.push_back(pFilter);

		pFilter->SetFilterGraph(this, NULL);

		pFilter->SetSyncSource(m_clock);

#if 0
		if (pVal)
		{
			*pVal = pDispFilter;
			(*pVal)->AddRef();
		}
	}
#endif

	return S_OK;
}
#endif

void FilterGraph::AddFilter(IBaseFilter *pFilter)
{
	/*
	IRefCounted* pref = dynamic_cast<IRefCounted*>(pFilter);
	if (pref) pref->AddRef();
	*/

	m_Filters->m_items.Add(pFilter);

	pFilter->SetFilterGraph(this, nullptr);

	pFilter->SetSyncSource(m_clock);
}

void FilterGraph::RemoveFilter(IBaseFilter *pFilter)
{
	for (int i = 0; i <	m_Filters->m_items.GetSize(); i++)
	{
		//DispILFilter> p = m_Filters->m_items[i];
		//ASSERT(p);
		IBaseFilter* pFilter = m_Filters->m_items[i];
		//if (static_cast<CDispLFilter*>(p.p)->m_p == pFilter)
		{
			pFilter->SetFilterGraph(nullptr, nullptr);

			//m_Filters->m_items[i]->Release();
			m_Filters->m_items.RemoveAt(i);//erase(m_Filters->m_items.begin()+i);

			return;
		}
	}

	ASSERT(0);
}

ErrorCode FilterGraph::ConnectDirect(IPin *ppinOut, IPin *ppinIn, MediaType* pMediaType)
{
	if (ppinOut == NULL) return Error_InvalidArgument;
	if (ppinIn == NULL) return Error_InvalidArgument;

	return ppinOut->Connect(ppinIn, pMediaType);
}

void FilterGraph::LoadURL(StringW* url)
{
//	USES_CONVERSION;

	ErrorCode hr;

	CURLSource* pSourceFilter = new CURLSource;
	//CComObject<CURLSource>::CreateInstance(&pSourceFilter);

	pSourceFilter->SetURL(url);

	/*
	CComPtr<IStream> stream;
	hr = pMoniker->BindToStorage(pCtx, NULL, IID_IStream, (void**)&stream);
	if (SUCCEEDED(hr))
	{
	*/
		AddFilter(pSourceFilter);

#if 0
		ASSERT(0);
		pSourceFilter->LoadFromStream(stream);
#endif

		////////

		RenderGraph();

		// Try to find a filter that implements a reference clock
		IReferenceClock* clock = NULL;

#if 1
		{
			for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
			{
				IBaseFilter* pFilter = m_Filters->m_items[i];

				clock = dynamic_cast<IReferenceClock*>(pFilter);
				if (clock)
					break;
			}
		}
#endif
#if 0
	//	QueryFilterInterface(__uuidof(ILReferenceClock), (IUnknown**)&clock);
		QueryFilterInterface(typeid(ILReferenceClock), (IUnknown**)&clock);
#endif

		if (clock == NULL)
		{
		//	clock.CoCreateInstance(CLSID_LSystemClock);	// Create a default reference clock
			clock = new SystemClock;
		}
		m_clock = clock;

		for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
		//	CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];
			IBaseFilter* mediaFilter = m_Filters->m_items[i];

			//CComQIPtr<ILMediaFilter> mediaFilter = pFilter->m_p;
			//if (mediaFilter)
			{
				mediaFilter->SetSyncSource(m_clock);
			}
		}

#if 0
	/*
	CComPtr<ILBaseFilter> sourceFilter;
	sourceFilter.CoCreateInstance(L"LMedia.URLSource");

	AddFilter(sourceFilter);

	hr = CComQIPtr<IURLSource>(sourceFilter)->SetURL(url);
	*/



	CComPtr<IBindCtx> bc;
	hr = CreateBindCtx(0/*reserved*/, &bc);
	if (SUCCEEDED(hr))
	{
		CComPtr<IMoniker> moniker;
		hr = CreateURLMoniker(NULL, url.c_str(), &moniker);
		if (SUCCEEDED(hr))
		{
			AddSourceFilterForMoniker(moniker, bc, NULL, NULL);
		}
	}
#endif
}

bool Match(IByteData* stream, BytePattern& pattern)
{
//	LARGE_INTEGER li;
//	li.QuadPart = pattern.m_offset;

	LONGLONG offset;

	if (pattern.m_offset >= 0)
	{
		offset = pattern.m_offset;
//		stream->Seek(li, STREAM_SEEK_SET, NULL);
	}
	else
	{
		offset = stream->GetSize() + pattern.m_offset;
//		stream->Seek(li, STREAM_SEEK_END, NULL);
	}

	uint8* buf = new uint8[pattern.m_length];

	ULONG nRead = stream->Read(buf, offset, pattern.m_length);
	if (nRead != pattern.m_length)
	{
		delete [] buf;
		return false;
	}

	int n;
	for (n = 0; n < pattern.m_length; n++)
	{
		if (!((buf[n] & pattern.m_mask[n]) == pattern.m_value[n]))
		{
			break;
		}
	}

	delete [] buf;

	if (n < pattern.m_length)
		return false;

	return true;
}

bool Match(IByteData* stream, CMatch& match)
{
	// All must match (AND)
	for (int i = 0; i < match.m_patterns.GetSize(); i++)
	{
		BytePattern& pattern = match.m_patterns[i];

		bool bMatch = Match(stream, pattern);
		if (!bMatch)
			return false;
	}

	return true;
}

bool Match(IByteData* stream, CStreamContent& content)
{
	// Any of these must match (OR)
	for (int i = 0; i < content.m_matches.GetSize(); i++)
	{
		CMatch& match = content.m_matches[i];
		if (Match(stream, match))
			return true;
	}

	return false;
}

/*
The Connect method connects the two pins, using intermediates if necessary.
*/
ErrorCode FilterGraph::Connect(IPin *ppinOut, IPin *ppinIn)
{
	// First try direct connection
	ErrorCode hr = ConnectDirect(ppinOut, ppinIn, NULL);
	if (hr >= 0) return hr;

	return hr;

	IByteData* byteStream = dynamic_cast<IByteData*>(ppinOut);
	if (ppinOut)
	{
		for (int i = 0; i < g_RegFilters.m_RegFilters.GetSize(); i++)
		{
			CDispLRegFilter* pRegFilter = g_RegFilters.m_RegFilters[i];

			for (int j = 0; j < pRegFilter->m_RegPins.GetSize(); j++)
			{
				CLRegPin* pRegPin = pRegFilter->m_RegPins[j];
				if (pRegPin->m_dir == PINDIR_INPUT)
				{
				}
			}
		}
	}
	else
	{
	}

	return Success;
}

ErrorCode FilterGraph::RenderGraph()
{
//	printf("FilterGraph::RenderGraph()\n");

	// Traverse all filters looking for output pins that aren't connected to anything
	{
		for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
			//CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];
			IBaseFilter* pFilter = m_Filters->m_items[i];

			IBaseFilter* baseFilter = pFilter;//->m_p;
			if (baseFilter)
			{
				RenderAllOutputs(baseFilter);
			}
		}
	}

	return Success;
}

ErrorCode FilterGraph::RenderAllOutputs(IBaseFilter* baseFilter)
{
	IEnumPins* enumPins = baseFilter->EnumPins();
	if (enumPins)
	{
		IPin* outpin;
		while (enumPins->Next(1, &outpin) == 1)
		{
			PIN_DIRECTION dir = outpin->QueryDirection();
			if (dir == PINDIR_OUTPUT)
			{
				IPin* connectedTo = outpin->ConnectedTo();
				if (connectedTo == NULL)
				{
					Render(outpin);
					/*
					CLMediaType mt;
				//	CComPtr<ILMediaType> mediaType;
					outpin->ConnectionMediaType(&mt);

					//mediaType->GetType(&mt);
					if (mt->majortype == LMEDIATYPE_Video)
					{
						// Connect Video renderer
						CComPtr<ILBaseFilter> filter;
						filter.CoCreateInstance(CLSID_LVideoRenderer);

						ILPin* inpin;
						filter->GetPin(0, &inpin);

						AddFilter(filter);
						ConnectDirect(outpin, inpin, NULL);
					}
					else if (mt->majortype == LMEDIATYPE_Audio)
					{
					// Connect Audio renderer
						CComPtr<ILBaseFilter> filter;
						filter.CoCreateInstance(CLSID_LDSoundRender);

						ILPin* inpin;
						filter->GetPin(0, &inpin);

						AddFilter(filter);
						ConnectDirect(outpin, inpin, NULL);
					}
					*/
				}
			}
			outpin = NULL;//.Release();
		}
	}

	return Success;
}

/*
The Render method builds a filter graph that renders the data from a specified output pin. 

This operation is recursive
*/
ErrorCode FilterGraph::Render(IPin *ppinOut)
{
//	printf("FilterGraph::Render()\n");

	ErrorCode hr = Error;

	IStreamBuilder* streamBuilder = dynamic_cast<IStreamBuilder*>(ppinOut);
	if (streamBuilder)
	{
		// The pin will take care of building itself
		hr = streamBuilder->Render(ppinOut, this);
	}
	else
	{
		IEnumMediaTypes* enumMediaTypes = ppinOut->EnumMediaTypes();

		int i;

	// Try filters in the graph with unconnected input pins
		for (i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
		//	CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];
			IBaseFilter* baseFilter = m_Filters->m_items[i];

			//CComQIPtr<ILBaseFilter> baseFilter = pFilter->m_p;
			//if (baseFilter)
			{
				IEnumPins* enumPins = baseFilter->EnumPins();
				if (enumPins)
				{
					IPin* ppinIn;
					while (enumPins->Next(1, &ppinIn) == 1)
					{
						PIN_DIRECTION dir = ppinIn->QueryDirection();
						if (dir == PINDIR_INPUT)
						{
							IPin* connectedTo = ppinIn->ConnectedTo();
							if (connectedTo == NULL)
							{
								ErrorCode hr = Connect(ppinOut, ppinIn);
								if (hr >= 0)
								{
									return hr;
								}
							}
						}
						ppinIn = NULL;//.Release();
					}
				}
			}
		}

	// Look up filters in the registry
		for (i = 0; i < g_RegFilters.m_RegFilters.GetSize(); i++)
		{
			CDispLRegFilter* pRegFilter = g_RegFilters.m_RegFilters[i];

			for (int npin = 0; npin < pRegFilter->m_RegPins.GetSize(); npin++)
			{
				CLRegPin* pRegPin = pRegFilter->m_RegPins[npin];

				if (pRegPin->m_dir == PINDIR_INPUT)
				{
					for (int nmt = 0; nmt < pRegPin->m_mediaTypes.GetSize(); nmt++)
					{
						if (pRegPin->m_mediaTypes[nmt]->m_majortype == LMEDIATYPE_Stream)
						{
							IByteData* byteStream = dynamic_cast<IByteData*>(ppinOut);
							if (byteStream)
							{
								bool bMatch = Match(byteStream, pRegPin->m_mediaTypes[nmt]->m_streamcontent);

								/*
								// Reset stream position
								LARGE_INTEGER li;
								li.QuadPart = 0;
								byteStream->Seek(li, STREAM_SEEK_SET, NULL);
								*/

								if (bMatch)
								{
									IBaseFilter* filter = LoadFilter(pRegFilter);

									//ASSERT(0);
									//filter.CoCreateInstance(pRegFilter->m_clsid);
									if (filter)
									{
										AddFilter(filter);

										IPin* pPin = filter->FindPin(pRegPin->m_name);
										if (pPin)
										{
											ErrorCode hr = Connect(ppinOut, pPin);
											if (hr >= 0)
											{
												// Recurse and render all the outputs of this filter
												hr = RenderAllOutputs(filter);
												return hr;
											}
										}

										// Back up
										RemoveFilter(filter);
										//ASSERT(SUCCEEDED(hr));
									}
								}
							}
						}
						else //if (pRegPin->m_mediaTypes[nmt]->m_majortype == LMEDIATYPE_Stream)
						{
							enumMediaTypes->Reset();

							MediaType* mediaType;
							while (enumMediaTypes->Next(1, &mediaType) == 1)
							{
							//	ASSERT(mediaType.m_pmt);

//								IMPLEMENT_DYNAMIC
								if (pRegPin->m_mediaTypes[nmt]->m_majortype == mediaType->GetMajorType())
								{
									/*
									typedef (*CTOR)();

									CTOR m_pfnCreateObject;
									m_pfnCreateObject = ILBaseFilter::SetFilterGraph;
									*/
									

									IBaseFilter* filter = LoadFilter(pRegFilter);
#if 0
								//	ASSERT(0);

									const OLECHAR* sep = wcschr(pRegFilter->m_Src.c_str(), '#');
									sysstring dllname = sysstring(pRegFilter->m_Src.c_str(), sep - pRegFilter->m_Src.c_str());
									const OLECHAR* classname = sep+1;

								//	HMODULE hLib = LoadLibrary("C:/mmstudio/extras/lpcx/debug/lpcx.dll");
									HMODULE hLib = LoadLibrary(ConvertS2A(dllname).c_str()/*"C:/mmstudio/extras/iff/debug/iff.dll"*/);
									if (hLib)
									{
										typedef Object* (*CreateObjectFN)(const wchar_t* name);
										CreateObjectFN fn = (CreateObjectFN)GetProcAddress(hLib, "CreateObject");
										if (fn)
										{
											Object* obj = fn(classname/*L"Test"*/);

											filter = dynamic_cast<ILBaseFilter*>(obj);
										}
									}
#endif

									//filter.CoCreateInstance(pRegFilter->m_clsid);
									if (filter)
									{
										AddFilter(filter);

										IPin* pPin = filter->FindPin(pRegPin->m_name);
										if (pPin)
										{
											ErrorCode hr = Connect(ppinOut, pPin);
											if (hr >= 0)
											{
												// Recurse and render all the outputs of this filter
												hr = RenderAllOutputs(filter);
												return hr;
											}
										}

										// Back up
										RemoveFilter(filter);
										//ASSERT(SUCCEEDED(hr));
									}
								}

//								mediaType.Delete();
							}
						}
					}
				}
			}
		}
	}

	return hr;
}

#if 0
ErrorCode FilterGraph::AddSourceFilterForMoniker(IMoniker *pMoniker, IBindCtx *pCtx, LPCWSTR lpcwstrFilterName, ILBaseFilter* *ppFilter)
{
//	ASSERT(ppFilter != NULL);
//	if (ppFilter == NULL) return E_POINTER;

	ErrorCode hr = S_OK;

	CURLSource* pSourceFilter = new CURLSource;
	//CComObject<CURLSource>::CreateInstance(&pSourceFilter);

	CComPtr<IStream> stream;
	hr = pMoniker->BindToStorage(pCtx, NULL, IID_IStream, (void**)&stream);
	if (SUCCEEDED(hr))
	{
		AddFilter(pSourceFilter);

		ASSERT(0);
#if 0
		pSourceFilter->LoadFromStream(stream);
#endif

		////////

		RenderGraph();

		// Try to find a filter that implements a reference clock
		ILReferenceClock* clock = NULL;
#if 0
	//	QueryFilterInterface(__uuidof(ILReferenceClock), (IUnknown**)&clock);
		QueryFilterInterface(typeid(ILReferenceClock), (IUnknown**)&clock);
#endif

		if (clock == NULL)
		{
		//	clock.CoCreateInstance(CLSID_LSystemClock);	// Create a default reference clock
			clock = new CLSystemClock;
		}
		m_clock = clock;

		for (int i = 0; i < m_Filters->m_items.size(); i++)
		{
		//	CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];
			ILBaseFilter* mediaFilter = m_Filters->m_items[i];

			//CComQIPtr<ILMediaFilter> mediaFilter = pFilter->m_p;
			//if (mediaFilter)
			{
				mediaFilter->SetSyncSource(m_clock);
			}
		}

#if 0
		// Traverse all filters looking for output pins that aren't connected to anything
		{
			for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
			{
				CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];

				CComQIPtr<ILBaseFilter> baseFilter = pFilter->m_p;
				if (baseFilter)
				{
					long npins;
					baseFilter->GetPinCount(&npins);
					for (int npin = 0; npin < npins; npin++)
					{
						ILPin* outpin;
						baseFilter->GetPin(npin, &outpin);

						LPIN_DIRECTION dir;
						outpin->QueryDirection(&dir);
						if (dir == LPINDIR_OUTPUT)
						{
							ILPin* connectedTo;
							outpin->ConnectedTo(&connectedTo);
							if (connectedTo == NULL)
							{
								CLMediaType mt;
							//	CComPtr<ILMediaType> mediaType;
								outpin->ConnectionMediaType(&mt);

								//mediaType->GetType(&mt);
								if (mt->majortype == LMEDIATYPE_Video)
								{
									// Connect Video renderer
									CComPtr<ILBaseFilter> filter;
									filter.CoCreateInstance(CLSID_LVideoRenderer);

									ILPin* inpin;
									filter->GetPin(0, &inpin);

									AddFilter(filter);
									ConnectDirect(outpin, inpin, NULL);
								}
								else if (mt->majortype == LMEDIATYPE_Audio)
								{
								// Connect Audio renderer
									ILBaseFilter* filter = new CLDSoundRender;
								//	filter.CoCreateInstance(CLSID_LDSoundRender);

									ILPin* inpin;
									filter->GetPin(0, &inpin);

									AddFilter(filter);
									ConnectDirect(outpin, inpin, NULL);
								}
							}
						}
					}
				}
			}
		}
#endif

//		*ppFilter = pSourceFilter;
//		(*ppFilter)->AddRef();

	}

	return hr;
}
#endif

#if 0
STDMETHODIMP FilterGraph::get_Streams(/*out,retval*/DispILStreams* *pVal)
{
	if (pVal == NULL) return E_POINTER;

	if (m_streams == NULL)
	{
		CComObject<CLStreams>::CreateInstance(&m_streams);
		m_streams->AddRef();

	// Build streams

	/*
	TODO
	To determine the number of streams, the Filter Graph Manager counts the number of filters that support seeking (through IMediaSeeking or IMediaPosition) and have a rendered input pin, which is defined as an input pin with no corresponding outputs. The Filter Graph Manager determines whether a pin is rendered in one of two ways: 

	The pin's IPin::QueryInternalConnections method returns zero in the nPin parameter.  
	The filter exposes the IAMFilterMiscFlags interface and returns the AM_FILTER_MISC_FLAGS_IS_RENDERER flag. 

	*/
#if 0
		for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
			CDispLFilter* pFilter = (CDispLFilter*)(DispILFilter*)m_Filters->m_items[i];

			long npins;
			pFilter->m_p->GetPinCount(&npins);

			for (int i = 0; i < npins; i++)
			{
				ILPin* pin;
				pFilter->m_p->GetPin(i, &pin);

				LPIN_DIRECTION dir;
				pin->QueryDirection(&dir);
				if (dir == LPINDIR_OUTPUT)
				{
					ILPin* connectedTo;
					pin->ConnectedTo(&connectedTo);

					if (connectedTo == NULL)
					{
						CComObject<CLStream>* pStream;
						CComObject<CLStream>::CreateInstance(&pStream);
						pStream->AddRef();

						pStream->m_pin = pin;

						m_streams->m_items.Add(pStream);
					}
				}
			}
		}
#endif
	}

	*pVal = m_streams;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}
#endif

#if 0
STDMETHODIMP FilterGraph::get_Filters(/*[out,retval]*/ IDispatch* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_Filters;
	(*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP FilterGraph::get_RegFilters(/*[out,retval]*/ IDispatch* *pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_RegFilters;
	(*pVal)->AddRef();
	return S_OK;
}
#endif

// untested
Object* FilterGraph::QueryFilterInterface(const Type_Info& riid)
{
	for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
	{
		IBaseFilter* pFilter = m_Filters->m_items[i];

#if WIN32
		// TODO, this must be wrong
		Object* obj = (Object*)__RTDynamicCast(pFilter, 0/*unknown*/, (void*)&typeid(pFilter), (void*)&riid, 0/*unknown*/);
#else
		Object* obj = NULL;
		ASSERT(0);
#endif
		if (obj)
		{
			return obj;
		}
	}

	return NULL;
}

// IMediaSeeking
ErrorCode FilterGraph::GetCurrentPosition(TimeUnit unit, LONGLONG* pVal)
{
//	LONGLONG t;
//	m_clock->GetTime(&t);

//	*pVal = t - m_tStart;

	for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
	{
		IBaseFilter* pFilter = m_Filters->m_items[i];

		IMediaSeeking* seeking = dynamic_cast<IMediaSeeking*>(pFilter);
		if (seeking)
		{
			return seeking->GetCurrentPosition(unit, pVal);
			// Return on first found????
		}
	}

	return Error_Failed;
}

ErrorCode FilterGraph::Seek(TimeUnit unit, LONGLONG t)
{
	for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
	{
	//	CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];
		IBaseFilter* pFilter = m_Filters->m_items[i];

		IMediaSeeking* seeking = dynamic_cast<IMediaSeeking*>(pFilter);//->m_p;
		if (seeking)
		{
			seeking->Seek(unit, t);
		}
	}

	return Success;
}

ErrorCode FilterGraph::GetDuration(TimeUnit unit, LONGLONG* pVal)
{
//	if (pVal == NULL) return E_POINTER;

	LONGLONG duration = 0;

	for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
	{
		IBaseFilter* pFilter = m_Filters->m_items[i];

		IMediaSeeking* seeking = dynamic_cast<IMediaSeeking*>(pFilter);//->m_p;
		if (seeking)
		{
			LONGLONG dur;
			seeking->GetDuration(unit, &dur);
			duration = MAX(duration, dur);
		}
	}

	*pVal = duration;
	return Success;
}

#if AMIGA
#define WINAPI
#endif

ULONG WINAPI ThreadStartProc(LPVOID lpParameter)
{
	FilterGraph* pGraph = (FilterGraph*)lpParameter;

	return pGraph->OnRun();
}

long FilterGraph::OnRun()
{
//	CoInitializeEx(NULL, COINIT_MULTITHREADED);

#if 0
	pGraph->m_cwnd.Create(NULL, CRect(0,0,0,0), NULL, WS_POPUP);
	ASSERT(pGraph->m_cwnd.m_hWnd);
	if (pGraph->m_cwnd.m_hWnd == NULL)
		return E_FAIL;
#endif

#if 0
	{
		for (int i = 0; i < m_Filters->m_items.size(); i++)
		{
			IBaseFilter* pFilter = m_Filters->m_items[i];

			IDirectSound* lds = dynamic_cast<IDirectSound*>(pFilter);//->m_p;
			if (lds)
			{
				lds->SetWindow(m_hWnd);
			}
		}
	}
#endif

	// First pause it
	m_state = State_Paused;

	{
		for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
			IBaseFilter* pFilter = m_Filters->m_items[i];

			pFilter->Pause();
		}
	}

	// Then run it
	LONGLONG tStart;
	m_clock->GetTime(&tStart);
	m_tStart = tStart;

	{
		for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
			IBaseFilter* pFilter = m_Filters->m_items[i];

			pFilter->Run(tStart);
		}
	}

	m_state = State_Running;

#if WIN32
	MSG msg;
	while (GetMessageA(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);

		if (msg.message == WM_USER+101 && msg.wParam == 2)
		{
			m_state = State_Paused;

			for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
			{
				IBaseFilter* pFilter = m_Filters->m_items[i];

				pFilter->Pause();
			}
		}
		else if (msg.message == WM_USER+101 && msg.wParam == 3)
		{
			m_state = State_Running;

		//	m_clock->GetTime(&tStart);
		//	m_tStart = tStart;

			for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
			{
				IBaseFilter* pFilter = m_Filters->m_items[i];

				pFilter->Run(m_tStart);
			}
		}
	}

#elif AMIGA

	m_pMsgPort = CreateMsgPort();

	//while (1)
	{
		execWait(SysBase, 1 << m_pMsgPort->mp_SigBit);

		Message* pMsg;
		while (pMsg = GetMsg(m_pMsgPort))
		{
			ReplyMsg(pMsg);
		}
	}

	//printf("End of FilterGraph Message loop\n");

#endif

//	goto loop;

	{
		m_state = State_Stopped;

		for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
		{
			IBaseFilter* pFilter = m_Filters->m_items[i];

			IMediaFilter* mediaFilter = pFilter;
			mediaFilter->Stop();
		}

#if 0
		if (m_cwnd)
		{
			m_cwnd.DestroyWindow();
		}
#endif
	}

//	CoUninitialize();

#if WIN32
	SetEvent(m_hEvent);
#endif

	return 0;
}

void FilterGraph::Run()
{

//	ThreadStartProc(this);

	if (m_state == State_Paused)
	{
#if WIN32
		PostThreadMessageA(m_threadId, WM_USER+101, 3, 0);
#else
		ASSERT(0);
#endif
	}
	else
	{
	#if WIN32
		m_hEvent = CreateEventA(NULL, true, false, NULL);
		if (m_hEvent == INVALID_HANDLE_VALUE)
			THROW(-1);

		m_hThread = ::CreateThread(NULL, 0L, ThreadStartProc, (LPVOID)this, 0, &m_threadId);
	#else

		CreateThread(ThreadStartProc, (void*)this);

	#endif
	}
//	WaitForSingleObject(m_hThread, INFINITE);

//	Sleep(10*1000);

}

void FilterGraph::Pause()
{
#if WIN32
	PostThreadMessageA(m_threadId, WM_USER+101, 2, 0);
#else
	ASSERT(0);
#endif
}

FILTER_STATE FilterGraph::GetState()
{
	// TODO, critical section

	return m_state;
}

void FilterGraph::Notify(IBaseFilter* pFilter, long nEvent)
{
#if WIN32
	if (nEvent == 0)
	{
		PostThreadMessageA(m_threadId, WM_QUIT, 0, 0);
	//	m_cwnd.PostMessage(WM_QUIT, 0, 0);
	}
#elif AMIGA

	/*
	MsgPort* pReplyPort = CreateMsgPort();

	Message* pMsg = (Message*)AllocMem(sizeof(Message), MEMF_PUBLIC);
	pMsg->mn_Node.ln_Type = NT_MESSAGE;
	pMsg->mn_Length = sizeof(Message);
	pMsg->mn_ReplyPort = pReplyPort;

	PutMsg(m_pMsgPort, pMsg);
	WaitPort(pReplyPort);
	GetMsg(m_pMsgPort);

	FreeMem(pMsg, sizeof(Message));
	DeleteMsgPort(pReplyPort);
	*/

	//printf("FilterGraph::Notify\n");

#endif
}

long FilterGraph::WaitForCompletion(long msTimeout)
{
#if WIN32
	ULONG waitRet = WaitForSingleObject(m_hEvent, msTimeout);
	ASSERT(waitRet != WAIT_FAILED);
#endif

	return 0;
}

void FilterGraph::Stop()
{
#if 0
	if (m_cwnd)
#endif

#if WIN32
	if (m_hThread)
	{
		//m_cwnd.PostMessage(WM_QUIT, 0, 0);
		PostThreadMessageA(m_threadId, WM_QUIT, 0, 0);
		WaitForSingleObject(m_hThread, INFINITE);
		m_hThread = NULL;
		m_threadId = 0;
	}

	if (m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	}
#endif

#if 0
	for (int i = 0; i < m_Filters->m_items.GetSize(); i++)
	{
		CDispLFilter* pFilter = (CDispLFilter*)m_Filters->m_items[i];

		CComQIPtr<ILMediaFilter> mediaFilter = pFilter->m_p;
		if (mediaFilter)
		{
			mediaFilter->Stop();
		}
	}

	if (m_cwnd)
	{
		m_cwnd.DestroyWindow();
	}
#endif

}

ErrorCode FilterGraph::get_frameRate(double *pVal) const
{
	// TODO: Add your implementation code here

	return Success;
}

ErrorCode FilterGraph::set_frameRate(double newVal)
{
	// TODO: Add your implementation code here

	return Success;
}

}
}
