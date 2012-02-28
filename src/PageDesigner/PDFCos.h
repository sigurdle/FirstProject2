#pragma once

class CPDFCosObject
{
public:
	CPDFCosDoc* m_pCosDoc;
	long m_id;
	DWORD m_offset;

public:
	CPDFCosObject()
	{
		m_pCosDoc = NULL;
		m_id = 0L;
	}

	virtual ~CPDFCosObject()
	{
	}

	DWORD GetID()
	{
		return m_id;
	}

	virtual void WriteToStream(FILE* fp) = 0;
};

class CPDFCosDictEntry
{
public:
	CUString m_name;
	CPDFCosObject* m_value;
};

class CPDFCosDict : public CPDFCosObject
{
public:
	CArray<CPDFCosDictEntry*,CPDFCosDictEntry*> m_entries;

	void CosDictPut(LPCTSTR name, CPDFCosObject* value)
	{
		CPDFCosDictEntry* pEntry = new CPDFCosDictEntry;
		pEntry->m_name = name;
		pEntry->m_value = value;
		
		m_entries.Add(pEntry);
	}

	CPDFCosObject* CosDictGet(TCHAR* name)
	{
		for (int i = 0; i < m_entries.GetSize(); i++)
		{
			if (!strcmp(m_entries[i]->m_name, name))
			{
				return m_entries[i]->m_value;
			}
		}

		return NULL;
	}

	// hmm.. same as above :)
	CPDFCosObject* FindObjectByName(LPCTSTR name)
	{
		for (int i = 0; i < m_entries.GetSize(); i++)
		{
			if (!strcmp(m_entries[i]->m_name, name))
			{
				return m_entries[i]->m_value;
			}
		}

		return NULL;
	}

	virtual void WriteToStream(FILE* fp)
	{
		if (m_id)
		{
			m_offset = ftell(fp);

			fprintf(fp, "%ld 0 obj\r\n", m_id);
		}

		fprintf(fp, "<<\r\n");

		for (int i = 0; i < m_entries.GetSize(); i++)
		{
			fprintf(fp, "/%s ", m_entries[i]->m_name);

			if (m_entries[i]->m_value->m_id)	// Write reference
			{
				fprintf(fp, "%ld 0 R", m_entries[i]->m_value->m_id);
			}
			else
			{
				m_entries[i]->m_value->WriteToStream(fp);
			}

			fprintf(fp, "\r\n");
		}

		fprintf(fp, ">>\r\n");

		if (m_id)
		{
			fprintf(fp, "endobj\r\n");
		}
	}
};

class CPDFCosArray : public CPDFCosObject
{
public:
	CArray<CPDFCosObject*,CPDFCosObject*> m_items;

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "[\r\n");

		for (int i = 0; i < m_items.GetSize(); i++)
		{
			if (m_items[i]->m_id)	// Write reference
			{
				fprintf(fp, "%ld 0 R", m_items[i]->m_id);
			}
			else
			{
				m_items[i]->WriteToStream(fp);
			}

			fprintf(fp, "\r\n");
		}

		fprintf(fp, "]");
	}
};

class CPDFCosString : public CPDFCosObject
{
public:
	char* m_str;
	int m_nBytes;

	CPDFCosString()
	{
		m_str = NULL;
		m_nBytes = NULL;
	}

	~CPDFCosString()
	{
		if (m_str)
		{
			delete m_str;
			m_str = NULL;
			m_nBytes = 0L;
		}
	}

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "(%*.*s)", m_nBytes, m_nBytes, m_str);
	}
};

class CPDFCosName : public CPDFCosObject
{
public:
	CUString m_name;

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "/%s", (LPCTSTR)m_name);
	}
};

class CPDFCosInteger : public CPDFCosObject
{
public:
	long m_value;

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "%ld", m_value);
	}
};

class CPDFCosReal : public CPDFCosObject
{
public:
	double m_value;

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "%g", m_value);
	}
};

class CPDFCosBoolean : public CPDFCosObject
{
public:
	bool m_value;

	virtual void WriteToStream(FILE* fp)
	{
		fprintf(fp, "%s", (m_value)? "true": "false");
	}
};

class CPDFCosStream : public CPDFCosObject
{
public:
	CPDFCosDict* m_attributesDict;
	CUString m_filename;

	CPDFCosStream()
	{
		m_attributesDict = NULL;
	}

	~CPDFCosStream()
	{
		if (m_attributesDict)
		{
			delete m_attributesDict;
			m_attributesDict = NULL;
		}

		if (m_filename.GetLength())
		{
			if (!DeleteFile(m_filename))
			{
				ATLASSERT(0);
			}
		}
	}

	CUString m_fmode;

	FILE* OpenFStream(LPCTSTR mode);
	void CloseFStream(FILE* fp);

	CPDFCosDict* CosStreamDict()
	{
		return m_attributesDict;
	}

	virtual void WriteToStream(FILE* fp)
	{
		ATLASSERT(m_id);	// must be indirect
		ATLASSERT(m_attributesDict);

		if (m_id)
		{
			m_offset = ftell(fp);

			fprintf(fp, "%ld 0 obj\r\n", m_id);
		}

		m_attributesDict->WriteToStream(fp);

		fprintf(fp, "stream\r\n");

		if (m_filename.GetLength())
		{
			FILE* srcfp = fopen(m_filename, "rb");
			if (srcfp)
			{
				fseek(srcfp, 0, SEEK_END);
				DWORD size = ftell(srcfp);
				fseek(srcfp, 0, SEEK_SET);

				BYTE buf[1024];

				long n = 0;
				while (n < size)
				{
					long nread = 1024;
					if (n+nread > size) nread = size-n;

					fread(buf, nread, 1, srcfp);
					fwrite(buf, nread, 1, fp);

					n += nread;
				}

				fclose(srcfp);
			}
		}

		fprintf(fp, "\r\nendstream\r\n");

		if (m_id)
		{
			fprintf(fp, "endobj\r\n");
		}
	}
};

class CPDFCosDoc
{
public:
	long m_nextID;
	CArray<CPDFCosObject*,CPDFCosObject*> m_cosObjects;
	CPDFCosDict* m_pCatalog;
	CPDFCosDict* m_pInfo;

	CPDFCosDoc()
	{
		m_nextID = 0;
		m_pCatalog = NULL;
		m_pInfo = NULL;
	}

	~CPDFCosDoc()
	{
		for (int i = 0; i < m_cosObjects.GetSize(); i++)
		{
			delete m_cosObjects[i];
		}
		m_cosObjects.RemoveAll();
	}

	CPDFCosStream* CosNewStream(bool indirect, CPDFCosDict* attributesDict)
	{
		if (!indirect)
			return NULL;	// must be true

		if (attributesDict == NULL)
		{
			attributesDict = CosNewDict(false);
		}
		else
		{
			if (attributesDict->m_id)
				return NULL;	// must be direct
		}

		CPDFCosStream* pCosStream = new CPDFCosStream;
		pCosStream->m_pCosDoc = this;
		pCosStream->m_id = ++m_nextID;
		pCosStream->m_attributesDict = attributesDict;

		return pCosStream;
	}

	CPDFCosString* CosNewString(bool indirect, const char* str, int nBytes)
	{
		CPDFCosString* pCosString = new CPDFCosString;
		if (indirect) pCosString->m_id = ++m_nextID;
		pCosString->m_pCosDoc = this;

		pCosString->m_str = (char*)malloc(nBytes);
		if (pCosString->m_str)
		{
			memcpy(pCosString->m_str, str, nBytes);
			pCosString->m_nBytes = nBytes;
		}

		return pCosString;
	}

	CPDFCosName* CosNewName(bool indirect, LPCTSTR name)
	{
		CPDFCosName* pCosName = new CPDFCosName;
		pCosName->m_pCosDoc = this;
		if (indirect) pCosName->m_id = ++m_nextID;

		pCosName->m_name = name;

		return pCosName;
	}

	CPDFCosInteger* CosNewInteger(bool indirect, long value)
	{
		CPDFCosInteger* pCosInteger = new CPDFCosInteger;
		pCosInteger->m_pCosDoc = this;
		if (indirect) pCosInteger->m_id = ++m_nextID;

		pCosInteger->m_value = value;

		return pCosInteger;
	}

	CPDFCosReal* CosNewReal(bool indirect, double value)
	{
		CPDFCosReal* pCosReal = new CPDFCosReal;
		pCosReal->m_pCosDoc = this;
		if (indirect) pCosReal->m_id = ++m_nextID;

		pCosReal->m_value = value;

		return pCosReal;
	}

	CPDFCosBoolean* CosNewBoolean(bool indirect, bool value)
	{
		CPDFCosBoolean* pCosBoolean = new CPDFCosBoolean;
		pCosBoolean->m_pCosDoc = this;
		if (indirect) pCosBoolean->m_id = ++m_nextID;

		pCosBoolean->m_value = value;

		return pCosBoolean;
	}

	CPDFCosArray* CosNewArray(bool indirect)
	{
		CPDFCosArray* pCosArray = new CPDFCosArray;
		pCosArray->m_pCosDoc = this;
		if (indirect) pCosArray->m_id = ++m_nextID;

		return pCosArray;
	}

	CPDFCosDict* CosNewDict(bool indirect)
	{
		CPDFCosDict* pCosDict = new CPDFCosDict;
		pCosDict->m_pCosDoc = this;
		if (indirect) pCosDict->m_id = ++m_nextID;

		return pCosDict;
	}

	STDMETHODIMP GetRoot(CPDFCosDict* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pCatalog;
		return S_OK;
	}

	STDMETHODIMP GetInfoDict(CPDFCosDict* *pVal)
	{
		if (pVal == NULL) return E_POINTER;
		*pVal = m_pInfo;
		return S_OK;
	}

	STDMETHODIMP Save(TCHAR* pathName);
};
