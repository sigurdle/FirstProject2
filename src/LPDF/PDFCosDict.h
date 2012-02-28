#pragma once

#include "PDFCosObj.h"

namespace System
{
namespace PDF
{

class PDFExt CPDFCosDict : 
	public CPDFCosObj//Impl<IPDFCosDict>
{
public:
	CPDFCosDict()
	{
	}

	class CPDFCosDictEntry
	{
	public:
		System::StringA* m_name;
		CosObject m_value;

		CPDFCosDictEntry()
		{
			//m_value = NULL;
		}
	};

	vector<CPDFCosDictEntry*> m_entries;

	virtual void WriteToStream(std::FILE* fp);
	virtual void ReadFromStream(std::FILE* fp);

// IPDFCosDict
public:
	CPDFCosObj* CosDictGet(System::StringA* name);
	void CosDictPut(System::StringA* name, CPDFCosObj* value);
};

}
}
