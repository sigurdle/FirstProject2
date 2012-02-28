#pragma once

#include "resource.h"

//#include "..\CmdHandler.h"
#include "..\UIT\UIT.h"
#include "PageDesignerCP.h"

/////////////////////////////////////////////////////////////////////////////
// CUndoManager
class ATL_NO_VTABLE CUndoManager : 
	public CComObjectRootEx<CComSingleThreadModel>,
//	public CComCoClass<CUndoManager, &CLSID_WEUndoManager>,
//	public IConnectionPointContainerImpl<CUndoManager>,
//	public IDispatchImpl<IWEUndoManager, &IID_IWEUndoManager, &LIBID_WEBEDITORLib>,
	public IOleUndoManager//, &IID_IOleUndoManager>
{
public:
	CUndoManager()
	{
		m_state = 0;
		m_pOpenParent = NULL;
	}

	void FinalRelease()
	{
		ClearUndoList();
		ClearRedoList();
	}

	int m_state;
	CArray<IOleUndoUnit*,IOleUndoUnit*> m_undoList;
	CArray<IOleUndoUnit*,IOleUndoUnit*> m_redoList;

	IOleParentUndoUnit*	m_pOpenParent;

	void ClearUndoList()
	{
		for (int i = 0; i < m_undoList.GetSize(); i++)
		{
			m_undoList[i]->Release();
		}
		m_undoList.RemoveAll();
	}

	void ClearRedoList()
	{
		for (int i = 0; i < m_redoList.GetSize(); i++)
		{
			m_redoList[i]->Release();
		}
		m_redoList.RemoveAll();
	}

//DECLARE_REGISTRY_RESOURCEID(IDR_WEUNDOMANAGER)
DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CUndoManager)
	COM_INTERFACE_ENTRY(IOleUndoManager)
END_COM_MAP()

public:

// IOleUndoManager
	
	STDMETHOD(DiscardFrom)(/* [in] */ IOleUndoUnit __RPC_FAR *pUU)
  	{
		return S_OK;
	}
	
	STDMETHOD(EnumUndoable)(/* [out] */ IEnumOleUndoUnits __RPC_FAR *__RPC_FAR *ppEnum)
  	{
		return S_OK;
	}
	
	STDMETHOD(EnumRedoable)(/* [out] */ IEnumOleUndoUnits __RPC_FAR *__RPC_FAR *ppEnum)
  	{
		return S_OK;
	}

	STDMETHOD(Enable)(/* [in] */ BOOL fEnable)
	{
		return S_OK;
	}

	STDMETHODIMP CUndoManager::Open(/* [in] */ IOleParentUndoUnit __RPC_FAR *pPUU)
	{
		pPUU->AddRef();
		m_pOpenParent = pPUU;

		return S_OK;
	}

	STDMETHODIMP CUndoManager::Close(/* [in] */ IOleParentUndoUnit __RPC_FAR *pPUU, /* [in] */ BOOL fCommit)
	{
		if (pPUU != m_pOpenParent)
			return E_INVALIDARG;

		if (m_pOpenParent)
		{
			m_pOpenParent = NULL;

			if (fCommit)
			{
				Add(pPUU);
			}

			pPUU->Release();
		}

		return S_OK;
	}

	STDMETHODIMP CUndoManager::GetLastUndoDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
	{
		*pBstr = NULL;

		if (m_undoList.GetSize() > 0)
		{
			m_undoList[m_undoList.GetSize()-1]->GetDescription(pBstr);
			return S_OK;
		}

		return E_FAIL;
	}

	STDMETHODIMP CUndoManager::GetLastRedoDescription(/* [out] */ BSTR __RPC_FAR *pBstr)
	{
		*pBstr = NULL;

		if (m_redoList.GetSize() > 0)
		{
			m_redoList[m_redoList.GetSize()-1]->GetDescription(pBstr);
			return S_OK;
		}

		return E_FAIL;
	}

	STDMETHODIMP CUndoManager::GetOpenParentState(/* [out] */ DWORD __RPC_FAR *pdwState)
	{
		if (m_pOpenParent)
		{
			return m_pOpenParent->GetParentState(pdwState);
		}
		else
		{
			return S_FALSE;
		}
	}

	/*
	If the undo manager is in the base state, it should put the new unit on
	the undo stack and discard the entire redo stack. If the undo manager
	is in the undo state, it should put new units on the redo stack.
	If the undo manager is in the redo state, it should put units on the
	undo stack without affecting the redo stack.
	*/

	STDMETHODIMP CUndoManager::Add(/* [in] */ IOleUndoUnit __RPC_FAR *pUU)
	{
		if (m_pOpenParent)
		{
			return m_pOpenParent->Add(pUU);
		}
		else
		{
			pUU->AddRef();
			if (m_state == 0)	// base state
			{
				ClearRedoList();
				m_undoList.Add(pUU);
			}
			else if (m_state == 1)	// undo state
			{
				m_redoList.Add(pUU);
			}
			else if (m_state == 2)	// redo state
			{
				m_undoList.Add(pUU);
			}

			return S_OK;
		}
	}

	STDMETHODIMP CUndoManager::UndoTo(/* [in] */ IOleUndoUnit __RPC_FAR *pUU)
	{
		if (m_undoList.GetSize() > 0)
		{
			int index = m_undoList.GetSize()-1;
			IOleUndoUnit* pUndo = m_undoList[index];

			m_state = 1;	// Undo State

			//CComQIPtr<IOleUndoManager> undomanager;
			//QueryInterface(IID_IOleUndoManager, (void**)&undomanager);

			pUndo->Do(this/*undomanager*/);

			m_undoList.RemoveAt(index);	// Remove it from the undo stack

			m_state = 0;
		}

		return S_OK;
	}

	STDMETHODIMP CUndoManager::RedoTo(/* [in] */ IOleUndoUnit __RPC_FAR *pUU)
	{
		if (m_redoList.GetSize() > 0)
		{
			m_state = 2;	// Redo state

			int index = m_redoList.GetSize()-1;
			IOleUndoUnit* pUndo = m_redoList[index];

			//CComQIPtr<IOleUndoManager> undomanager;
			//QueryInterface(IID_IOleUndoManager, (void**)&undomanager);

			pUndo->Do(this/*undomanager*/);

			m_redoList.RemoveAt(index);	// Remove it from the undo stack

			m_state = 0;
		}

		return S_OK;
	}
};

#if 0
class ATL_NO_VTABLE CPDStoryEnum : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ITextStoryRanges, &IID_ITextStoryRanges/*, &LIBID_tom*/>,	// IDispatch
#endif


class COleServerItem;

class CObjectMap;
class CPDSwatches;
class CPDLayer;
class CPDSpreadDocument;
class CPDSection;
class CPDMatrix;
template<class IBase> class CPDSpreadImpl;

#include "PDDocumentSettingsImpl.h"
#include "PDTextFrameOptionsImpl.h"
#include "PDObjectWithAppearanceAndStrokeFillImpl.h"

class CIPFrame;

class ATL_NO_VTABLE CPDDocument : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CPDDocument, &CLSID_PDDocument>,
	public ProcessTargetCommands,

	public IDispatchImpl<DispIPDDocument, &IID_DispIPDDocument, &LIBID_PAGEDESIGNERLib>,

	public IPDDocument,
	public IDispatchImpl<ITextDocument, &IID_ITextDocument/*, &LIBID_tom*/>,	// IDispatch
	public CProxy_IPDDocumentEvents< CPDDocument >,
	public IConnectionPointContainerImpl<CPDDocument>,

	public CPDDocumentSettingsImpl<CPDDocument>,
	public CPDTextFrameOptionsImpl<CPDDocument>,
	public CPDObjectWithAppearanceAndStrokeFillImpl<CPDDocument>,

	public CNotifyGetImpl<CPDDocument>,
	public CNotifySendImpl<CPDDocument>,

	public IDataObject,

	public IOleObject,
	public IOleDocument,

	public IOleInPlaceObject, // IOleWindow
	public IOleInPlaceActiveObject, // IOleWindow

	public IPersistFile, // IPersist
//	public IPersistStorage, // IPersist

	public IObjectSerializable
{
public:
	CPDDocument()
	{
		m_undoManager = NULL;

		m_layers = NULL;

		m_firstLayer = NULL;
		m_lastLayer = NULL;

		m_firstSpread = NULL;
		m_lastSpread = NULL;

		m_spreads = NULL;
		m_pages = NULL;
		m_masterSpreads = NULL;
		m_masterPages = NULL;
		m_swatches = NULL;
		m_stories = NULL;
		m_images = NULL;
		m_symbols = NULL;

		m_pageWidth = 0;
		m_pageHeight = 0;
		m_facingPages = VARIANT_FALSE;
		m_allowPagesToShuffle = VARIANT_TRUE;

		m_viewDocumentGrid = VARIANT_FALSE;
		m_showHiddenCharacters = VARIANT_FALSE;

		m_nextLayerIndex = 0;
		m_nextMasterPrefix = 0;

		m_distributingStories = 0;

		m_marginTop = 0;
		m_marginBottom = 0;
		m_marginInside = 0;
		m_marginOutside = 0;

		m_columnNumber = 1;
		m_columnGutter = 0;

		m_firstSection = NULL;

		m_showTextThreads = VARIANT_FALSE;

	// Ole
		m_pInPlaceFrame = NULL;
	//	m_pInPlaceView = NULL;

		m_dwRegister = 0L;
	}

	HRESULT FinalConstruct();
	void FinalRelease();

// Need the following because of IPDObjectWithAppearance (TODO, remove)
	double m_scaleX, m_scaleY;
	double m_opacity;
	RectD m_filterRect;
	CComObject<CPDMatrix>* m_matrix;
///////////

	CComObject<CUndoManager>* m_undoManager;

	double m_pageWidth;
	double m_pageHeight;
	VARIANT_BOOL m_facingPages;
	VARIANT_BOOL m_allowPagesToShuffle;
	VARIANT_BOOL m_viewDocumentGrid;
	VARIANT_BOOL m_showHiddenCharacters;

	CComObject<CPDSection>* m_firstSection;

	CComObject<CObjectMap>* m_layers;

	CComObject<CObjectMap>* m_spreads;
	CComObject<CObjectMap>* m_pages;

	CComObject<CObjectMap>* m_masterSpreads;
	CComObject<CObjectMap>* m_masterPages;

	CComObject<CObjectMap>* m_symbols;

	CComObject<CPDSwatches>* m_swatches;

	CComObject<CObjectMap>* m_stories;
	CComObject<CObjectMap>* m_images;

	_bstr_t m_fileTitle;
	_bstr_t m_filePath;

	long m_nextLayerIndex;
	long m_nextMasterPrefix;

	double m_marginTop;
	double m_marginBottom;
	double m_marginInside;
	double m_marginOutside;

	long m_columnNumber;	// Warningm, these two are very similar to TextFrameOptions
	double m_columnGutter;

	VARIANT_BOOL m_showTextThreads;

	CComObject<CPDSpreadDocument>* m_firstSpread;
	CComObject<CPDSpreadDocument>* m_lastSpread;

	CComObject<CPDLayer>* m_firstLayer;
	CComObject<CPDLayer>* m_lastLayer;

	int m_distributingStories;

// IOleDocument
	CComObject<CIPFrame>* m_pInPlaceFrame;

	COleServerItem* m_pOleServerItem;

	CComPtr<IOleClientSite> m_spClientSite;
	CComPtr<IOleAdviseHolder>	m_spOleAdviseHolder;
	DWORD                   m_dwRegister;

	CComPtr<IDataAdviseHolder>	m_spDataAdviseHolder;

//	CComObject<CPDDocumentView>* m_pInPlaceView;

	HRESULT ActivateInPlace();
//

	HRESULT insertSpread(IPDSpread* spread, IPDSpread* before);

	HRESULT insertLayer(IPDLayer* layer, IPDLayer* before);
	HRESULT removeLayer(IPDLayer* layer);

	void ShufflePages(CComObject<CPDSpreadDocument>* pSpread);

	void CreatePages(int npages);
	void CreateSpreadLayerGroups(IPDSpread* spread);

	void InsertLayerGroupOnSpreadList(CObjectMap* spreads, CPDLayer* pLayer);
	void RemoveLayerGroupOnSpreadList(CObjectMap* spreads, IPDLayer* layer);
	void ArrangeLayerGroupOnSpreadList(CObjectMap* spreads, IPDLayer* layer, IPDLayer* before);

	void DistributeStories();

	void OnChangedTextFrameOptions()
	{
		// Do nothnig
	}

DECLARE_PROTECT_FINAL_CONSTRUCT()

DECLARE_REGISTRY_RESOURCEID(IDR_PDDOCUMENT)

BEGIN_COM_MAP(CPDDocument)
	COM_INTERFACE_ENTRY2(IDispatch, DispIPDDocument)
	COM_INTERFACE_ENTRY(IPDDocument)
	COM_INTERFACE_ENTRY(ITextDocument)

	COM_INTERFACE_ENTRY(IPDTextFrameOptions)
	COM_INTERFACE_ENTRY(IPDDocumentSettings)
	COM_INTERFACE_ENTRY(IPDDocumentSettings)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearance)
	COM_INTERFACE_ENTRY(IPDObjectWithAppearanceAndStrokeFill)
	
	COM_INTERFACE_ENTRY(ICommandTarget)
	COM_INTERFACE_ENTRY(INotifyGet)
	COM_INTERFACE_ENTRY(INotifySend)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)

//	COM_INTERFACE_ENTRY2(IPersist, IPersistFile)
	COM_INTERFACE_ENTRY(IPersist)
	COM_INTERFACE_ENTRY(IPersistFile)
//	COM_INTERFACE_ENTRY(IPersistStorage)

	COM_INTERFACE_ENTRY(IDataObject)

	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IOleDocument)

	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)

	COM_INTERFACE_ENTRY(IObjectSerializable)

//	COM_INTERFACE_ENTRY_BREAK(IPersistStorage)
//	COM_INTERFACE_ENTRY_BREAK(IOleInPlaceObject)
//	COM_INTERFACE_ENTRY_BREAK(IOleInPlaceActiveObject)

END_COM_MAP()

BEGIN_CONNECTION_POINT_MAP(CPDDocument)
	CONNECTION_POINT_ENTRY(DIID__IPDDocumentEvents)
END_CONNECTION_POINT_MAP()

DECLARE_CMD_MAP(CPDDocument)

	LRESULT OnFileSave(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileExportSVG(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnFileExportPDF(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDocumentSetup(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnDocumentColorSettings(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditPreferences(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditUndo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditRedo(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnEditUndoUpdate(long iid, IUICmdUpdate* pCmdUI);
	void OnEditRedoUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnLayerNew(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnAllowPagesToShuffle(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnAllowPagesToShuffleUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnViewDocumentGrid(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnViewDocumentGridUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnPagesNewMaster(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnTypeShowHiddenCharacters(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnTypeShowHiddenCharactersUpdate(long iid, IUICmdUpdate* pCmdUI);
	LRESULT OnViewShowTextThreads(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	void OnViewShowTextThreadsUpdate(long iid, IUICmdUpdate* pCmdUI);

// INotifyGet
	STDMETHODIMP OnChanged(NotifyType type, IUnknown* targetObject, IUnknown* immtargetObject, DISPID dispID)
	{
		FireOnChanged(type, targetObject, dispID);
		return S_OK;
	}

// IPDDocument
public:
	STDMETHOD(removeSubObjects)();
	STDMETHOD(get_showTextThreads)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(put_showTextThreads)(/*[in]*/ VARIANT_BOOL newVal);
	STDMETHOD(setColumns)(/*[in]*/ long ncolumns, /*[in]*/ double gutter, /*[in]*/ double width, /*[in]*/ VARIANT_BOOL fixedWidth);
	STDMETHOD(loadImageFromStream)(/*[in]*/ IStream* stream, /*[out,retval]*/ IPDImage* *pVal);
	STDMETHOD(get_lastSpread)(/*[out, retval]*/ IPDSpreadDocument* *pVal);
	STDMETHOD(get_firstSpread)(/*[out, retval]*/ IPDSpreadDocument* *pVal);
	STDMETHOD(getSymbolByName)(/*[in]*/ BSTR name, /*[out,retval]*/ IPDSymbol* *pVal);
	STDMETHOD(appendSymbol)(/*[in]*/ IPDSymbol* symbol);
	STDMETHOD(get_symbols)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(createImage)(/*[in]*/ long width, /*[in]*/ long height, /*[in]*/ DWORD mode, /*[out,retval]*/ IPDImage* *pVal);
	STDMETHOD(removeStory)(/*[in]*/ IPDStory* story);
	STDMETHOD(get_fileTitle)(/*[out, retval]*/ BSTR *pVal);
	STDMETHOD(put_fileTitle)(/*[in]*/ BSTR newVal);
	STDMETHOD(getLayerByUniqId)(/*[in]*/ GUID guid, /*[out,retval]*/ IPDLayer* *pVal);
	STDMETHOD(insertLayerBefore)(/*[in]*/ IPDLayer* layer, /*[in]*/ IPDLayer* before);
	STDMETHOD(deleteLayer)(/*[in]*/ IPDLayer* layer);
	STDMETHOD(createSection)(/*[out,retval]*/ IPDSection* *pVal);
	STDMETHOD(get_firstSection)(/*[out, retval]*/ IPDSection* *pVal);
	STDMETHOD(getStoryById)(/*[in]*/ GUID guid, /*[out,retval]*/ IPDStory* *pVal);
	STDMETHOD(insertPagesAfter)(/*[in]*/ long nPages, /*[in]*/ long nAfterPage);
	STDMETHOD(insertPagesBefore)(/*[in]*/ long nPages, /*[in]*/ long nBeforePage);
	STDMETHOD(createPathText)(/*[out,retval]*/ IPDPathText* *pVal);
	STDMETHOD(appendStory)(/*[in]*/ IPDStory* story);
	STDMETHOD(get_stories)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(createStory)(/*[out,retval]*/ IPDStory* *pVal);
	STDMETHOD(NewWindow)(/*[out,retval]*/ IPDDocumentView* *pVal);
	STDMETHOD(get_swatches)(/*[out, retval]*/ IPDSwatches* *pVal);
	STDMETHOD(get_facingPages)(/*[out, retval]*/ VARIANT_BOOL *pVal);
	STDMETHOD(get_pageHeight)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_pageWidth)(/*[out, retval]*/ double *pVal);
	STDMETHOD(get_pages)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(get_spreads)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(get_filePath)(BSTR *pVal);
	STDMETHOD(put_filePath)(BSTR newVal);
	STDMETHOD(get_undoManager)(IOleUndoManager* *pVal);
	STDMETHOD(ShowViews)();
	STDMETHOD(NewDocument)();
	STDMETHOD(getSpreadByUniqId)(/*[in]*/ GUID guid, /*[out,retval]*/ IPDSpread* *pVal);
	STDMETHOD(getMasterSpreadByName)(/*[in]*/ BSTR prefix, /*[in]*/ BSTR name, /*[out,retval]*/ IPDSpreadMaster* *pVal);
	STDMETHOD(get_masterPages)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(get_masterSpreads)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(createContentText)(/*[out,retval]*/ IPDContentText* *pVal);
	STDMETHOD(loadImage)(/*[in]*/ BSTR pathName, /*[out,retval]*/ IPDImage** pVal);
	STDMETHOD(get_images)(/*[out, retval]*/ IObjectMap* *pVal);
	STDMETHOD(createContentGraphic)(/*[out,retval]*/ IPDContentGraphic* *pVal);
	STDMETHOD(createObjectFrame)(/*[out,retval]*/ IPDObjectFrame* *pVal);
	STDMETHOD(createObjectGroup)(/*[in]*/ GUID guid, /*[out,retval]*/ IPDObjectGroup* *pVal);
	STDMETHOD(get_layers)(/*[out, retval]*/ IObjectMap* *pVal);

// IObjectSerializable
	STDMETHOD(Serialize)(/*[in]*/ IArchive* ar, IArchiveElement* node);
	STDMETHOD(Deserialize)(/*[in]*/ IArchive* ar, IArchiveElement* node, IUnknown* pUnkExtra);
	STDMETHOD(GetClassID)(/*[out,retval]*/ CLSID* pClassID);

// ITextDocument
     virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE GetName( 
         /* [retval][out] */ BSTR __RPC_FAR *pName);
     
     virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE GetSelection( 
         /* [retval][out] */ ITextSelection __RPC_FAR *__RPC_FAR *ppSel);
     
     virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE GetStoryCount( 
         /* [retval][out] */ long __RPC_FAR *pCount);
     
     virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE GetStoryRanges( 
         /* [retval][out] */ ITextStoryRanges __RPC_FAR *__RPC_FAR *ppStories);
     
     virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE GetSaved( 
         /* [retval][out] */ long __RPC_FAR *pValue);
     
     virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE SetSaved( 
         /* [in] */ long Value);
     
     virtual /* [propget][id] */ HRESULT STDMETHODCALLTYPE GetDefaultTabStop( 
         /* [retval][out] */ float __RPC_FAR *pValue);
     
     virtual /* [propput][id] */ HRESULT STDMETHODCALLTYPE SetDefaultTabStop( 
         /* [in] */ float Value);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE New( void);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Open( 
         /* [in] */ VARIANT __RPC_FAR *pVar,
         /* [in] */ long Flags,
         /* [in] */ long CodePage);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Save( 
         /* [in] */ VARIANT __RPC_FAR *pVar,
         /* [in] */ long Flags,
         /* [in] */ long CodePage);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Freeze( 
         /* [retval][out] */ long __RPC_FAR *pCount);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Unfreeze( 
         /* [retval][out] */ long __RPC_FAR *pCount);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE BeginEditCollection( void);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE EndEditCollection( void);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Undo( 
         /* [in] */ long Count,
         /* [retval][out] */ long __RPC_FAR *prop);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Redo( 
         /* [in] */ long Count,
         /* [retval][out] */ long __RPC_FAR *prop);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE Range( 
         /* [in] */ long cp1,
         /* [in] */ long cp2,
         /* [retval][out] */ ITextRange __RPC_FAR *__RPC_FAR *ppRange);
     
     virtual /* [id] */ HRESULT STDMETHODCALLTYPE RangeFromPoint( 
         /* [in] */ long x,
         /* [in] */ long y,
         /* [retval][out] */ ITextRange __RPC_FAR *__RPC_FAR *ppRange);


	//IDataObject methods
	STDMETHODIMP DAdvise(  LPFORMATETC pFormatetc, 
								  DWORD advf,
								  LPADVISESINK pAdvSink, 
								  LPDWORD pdwConnection);
	STDMETHODIMP DUnadvise(DWORD);
	STDMETHODIMP EnumDAdvise(LPENUMSTATDATA*);
	STDMETHODIMP EnumFormatEtc(DWORD, LPENUMFORMATETC*);
	STDMETHODIMP GetCanonicalFormatEtc(LPFORMATETC, LPFORMATETC);
	STDMETHODIMP GetData(LPFORMATETC, LPSTGMEDIUM);
	STDMETHODIMP GetDataHere(LPFORMATETC, LPSTGMEDIUM);
	STDMETHODIMP QueryGetData(LPFORMATETC);
	STDMETHODIMP SetData(LPFORMATETC, LPSTGMEDIUM, BOOL);

// IOleWindow
	STDMETHOD(GetWindow)(HWND __RPC_FAR *phwnd);
	STDMETHOD(ContextSensitiveHelp)(BOOL fEnterMode);

// IOleInPlaceObject
	STDMETHOD(InPlaceDeactivate)(void);
	STDMETHOD(UIDeactivate)(void);
	STDMETHOD(SetObjectRects)(LPCRECT lprcPosRect, LPCRECT lprcClipRect);
	STDMETHOD(ReactivateAndUndo)(void);

// IOleInPlaceActiveObject
	STDMETHODIMP TranslateAccelerator( 
            /* [in] */ LPMSG lpmsg);
	STDMETHODIMP OnFrameWindowActivate( 
            /* [in] */ BOOL fActivate);
	STDMETHODIMP OnDocWindowActivate( 
            /* [in] */ BOOL fActivate);
	STDMETHODIMP ResizeBorder( 
            /* [in] */ LPCRECT prcBorder,
            /* [unique][in] */ IOleInPlaceUIWindow *pUIWindow,
            /* [in] */ BOOL fFrameWindow);
	STDMETHODIMP EnableModeless(/* [in] */ BOOL fEnable);

// IPersist
//	STDMETHOD(GetClassID)(CLSID __RPC_FAR *pClassID);

// IPersistFile/IPersistStream/IPersistStorage
	STDMETHOD(IsDirty)( void);

// IPersistFile
	STDMETHOD(Load)(LPCOLESTR pszFileName, DWORD dwMode);
	STDMETHOD(Save)(LPCOLESTR pszFileName, BOOL fRemember);
	STDMETHOD(SaveCompleted)(LPCOLESTR pszFileName);
	STDMETHOD(GetCurFile)(LPOLESTR __RPC_FAR *ppszFileName);

// IPersistStorage
	STDMETHODIMP InitNew(/* [unique][in] */ IStorage *pStg);
	STDMETHODIMP Load(/* [unique][in] */ IStorage *pStg);
	STDMETHODIMP Save(/* [unique][in] */ IStorage *pStgSave, /* [in] */ BOOL fSameAsLoad);
	STDMETHODIMP SaveCompleted(/* [unique][in] */ IStorage *pStgNew);
	STDMETHODIMP HandsOffStorage( void);

// IOleDocument
	STDMETHOD(CreateView)(IOleInPlaceSite __RPC_FAR *pIPSite, IStream __RPC_FAR *pstm, DWORD dwReserved, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView);		
	STDMETHOD(GetDocMiscStatus)(DWORD __RPC_FAR *pdwStatus);
	STDMETHOD(EnumViews)(IEnumOleDocumentViews __RPC_FAR *__RPC_FAR *ppEnum, IOleDocumentView __RPC_FAR *__RPC_FAR *ppView);
// IOleObject
     virtual HRESULT STDMETHODCALLTYPE SetClientSite( 
         /* [unique][in] */ IOleClientSite __RPC_FAR *pClientSite);
     
     virtual HRESULT STDMETHODCALLTYPE GetClientSite( 
         /* [out] */ IOleClientSite __RPC_FAR *__RPC_FAR *ppClientSite);
     
     virtual HRESULT STDMETHODCALLTYPE SetHostNames( 
         /* [in] */ LPCOLESTR szContainerApp,
         /* [unique][in] */ LPCOLESTR szContainerObj);
     
     virtual HRESULT STDMETHODCALLTYPE Close( 
         /* [in] */ DWORD dwSaveOption);
     
     virtual HRESULT STDMETHODCALLTYPE SetMoniker( 
         /* [in] */ DWORD dwWhichMoniker,
         /* [unique][in] */ IMoniker __RPC_FAR *pmk);
     
     virtual HRESULT STDMETHODCALLTYPE GetMoniker( 
         /* [in] */ DWORD dwAssign,
         /* [in] */ DWORD dwWhichMoniker,
         /* [out] */ IMoniker __RPC_FAR *__RPC_FAR *ppmk);
     
     virtual HRESULT STDMETHODCALLTYPE InitFromData( 
         /* [unique][in] */ IDataObject __RPC_FAR *pDataObject,
         /* [in] */ BOOL fCreation,
         /* [in] */ DWORD dwReserved);
     
     virtual HRESULT STDMETHODCALLTYPE GetClipboardData( 
         /* [in] */ DWORD dwReserved,
         /* [out] */ IDataObject __RPC_FAR *__RPC_FAR *ppDataObject);
     
     virtual HRESULT STDMETHODCALLTYPE DoVerb( 
         /* [in] */ LONG iVerb,
         /* [unique][in] */ LPMSG lpmsg,
         /* [unique][in] */ IOleClientSite __RPC_FAR *pActiveSite,
         /* [in] */ LONG lindex,
         /* [in] */ HWND hwndParent,
         /* [unique][in] */ LPCRECT lprcPosRect);
     
     virtual HRESULT STDMETHODCALLTYPE EnumVerbs( 
         /* [out] */ IEnumOLEVERB __RPC_FAR *__RPC_FAR *ppEnumOleVerb);
     
     virtual HRESULT STDMETHODCALLTYPE Update( void);
     
     virtual HRESULT STDMETHODCALLTYPE IsUpToDate( void);
     
     virtual HRESULT STDMETHODCALLTYPE GetUserClassID( 
         /* [out] */ CLSID __RPC_FAR *pClsid);
     
     virtual HRESULT STDMETHODCALLTYPE GetUserType( 
         /* [in] */ DWORD dwFormOfType,
         /* [out] */ LPOLESTR __RPC_FAR *pszUserType);
     
     virtual HRESULT STDMETHODCALLTYPE SetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [in] */ SIZEL __RPC_FAR *psizel);
     
     virtual HRESULT STDMETHODCALLTYPE GetExtent( 
         /* [in] */ DWORD dwDrawAspect,
         /* [out] */ SIZEL __RPC_FAR *psizel);
     
     virtual HRESULT STDMETHODCALLTYPE Advise( 
         /* [unique][in] */ IAdviseSink __RPC_FAR *pAdvSink,
         /* [out] */ DWORD __RPC_FAR *pdwConnection);
     
     virtual HRESULT STDMETHODCALLTYPE Unadvise( 
         /* [in] */ DWORD dwConnection);
     
     virtual HRESULT STDMETHODCALLTYPE EnumAdvise( 
         /* [out] */ IEnumSTATDATA __RPC_FAR *__RPC_FAR *ppenumAdvise);
     
     virtual HRESULT STDMETHODCALLTYPE GetMiscStatus( 
         /* [in] */ DWORD dwAspect,
         /* [out] */ DWORD __RPC_FAR *pdwStatus);
     
     virtual HRESULT STDMETHODCALLTYPE SetColorScheme( 
         /* [in] */ LOGPALETTE __RPC_FAR *pLogpal);
// IPDObjectWithAppearance
	STDMETHOD(Render2)(/*[in]*/ DWORD dwBitmap, /*[in]*/ DWORD dwGraphics, double scaleX, double scaleY)
	{
		return E_FAIL;
	}
//
};
