#pragma once

namespace System
{
namespace PDF
{

class PDFExt CPDFCosObj : public System::Object
{
    public:

	CPDFCosObj()
	{
		m_id = 0L;
		m_offset = 0L;

		m_pCosDoc = NULL;
	}

	virtual uint32 GetID();
        
   virtual CPDFCosDoc * GetDoc();     

	virtual void WriteToStream(std::FILE* fp) = 0;
	virtual void ReadFromStream(std::FILE* fp)	/* TODO = 0 */
	{
	}

public:

	uint32 m_id;
	uint32 m_genNum;
	uint32 m_offset;
	CPDFCosDoc* m_pCosDoc;
};

class PDFExt CosObject
{
public:
	CosObject()
	{
		m_pObj = NULL;
	}

	CPDFCosDoc* m_pCosDoc;

	CosObject(CPDFCosObj* pObj)
	{
		m_pObj = pObj;
	}

	uint32 m_R;
	uint32 m_gen;
	CPDFCosObj* m_pObj;

	operator CPDFCosObj* ();
};

#if 0
class CPDFCosObj
{
public:
	DWORD m_id;
	DWORD m_offset;
	IPDFCosDoc* m_pCosDoc;

	CPDFCosObj()
	{
		m_id = 0;
		m_genNum = 0;
		m_offset = 0L;

		m_pCosDoc = NULL;
	}

	virtual void WriteToStream(FILE* fp) = 0;
	virtual void ReadFromStream(FILE* fp)	/* TODO = 0 */
	{
	}

public:
	HRESULT GetID(DWORD* pVal);
	HRESULT GetDoc(IPDFCosDoc* *pVal);
};
#endif

#if 0
template <class IBase> class IPDFCosObjImpl :
	public IBase
{
public:
	STDMETHODIMP GetID(DWORD* pVal)
	{
		return CPDFCosObj::GetID(pVal);
	}
	STDMETHODIMP GetDoc(CPDFCosDoc* *pVal)
	{
		return CPDFCosObj::GetDoc(pVal);
	}
};

#endif

}
}
