#ifndef __PDFCOSDOC_H_
#define __PDFCOSDOC_H_

namespace System
{
namespace PDF
{

class PDFExt CPDFCosDoc : public System::Object//CPDFCosObj
{
public:
	CPDFCosDoc();

	std::FILE* m_fp;

	ErrorCode Read(System::StringA* filename);
	ErrorCode Save(System::StringA* pathName);

	ErrorCode Create();
	CPDFCosStream* CosNewStream(bool indirect, /*[in]*/ CPDFCosDict* attributesDict);
	CPDFCosObj* GetObjByID(uint32 objNum);
	CPDFCosDict* GetRoot();
	CPDFCosReal* CosNewReal(/*[in]*/ bool indirect, /*[in]*/ double value);
	CPDFCosInteger* CosNewInteger(/*[in]*/ bool indirect, /*[in]*/ long value);
	CPDFCosArray* CosNewArray(/*[in]*/ bool indirect);
	CPDFCosDict* CosNewDict(/*[in]*/ bool indirect);
	CPDFCosName* CosNewName(/*[in]*/ bool indirect, /*[in]*/ System::StringA* name);

	CPDFCosDict* GetCatalog()
	{
		return m_pCatalog;
	}

	CosObject ReadObject(std::FILE* fp);
	CosObject ReadObject2(std::FILE* fp);

	map<ULONG,CPDFCosObj*> m_objectsById;
	map<ULONG,ULONGLONG> m_objectsByIdOffset;

	vector<CPDFCosObj*> m_cosObjects;
	CPDFCosDict* m_pCatalog;
	CPDFCosDict* m_pInfo;
	CPDFCosDict* m_pEncrypt;
	CPDFCosArray* m_pID;
	uint32 m_nextID;
};

}
}

#endif //__PDFCOSDOC_H_
