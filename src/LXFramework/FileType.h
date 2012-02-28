#pragma once

class CFileTypeExtension
{
public:
	CFileTypeExtension()
	{
		m_registeredFromRegistry = FALSE;
	}

	CUString m_ext;
	BOOL m_registeredFromRegistry;
};

//typedef CArray<CUString,CUString> CStringList;

class CFileType
{
protected:
	CArray<CFileTypeExtension*, CFileTypeExtension*> m_extensions;

public:
	CUString m_id;
	CUString m_descr;

public:

	CFileType()
	{
		m_registeredFromRegistry = 0;
		m_registered = 0;
	}

	~CFileType()
	{
		for (int i = 0; i < m_extensions.GetSize(); i++)
		{
			delete m_extensions[i];
		}

		m_extensions.RemoveAll();
	}

	void AddFileExtension(LPCTSTR ext)
	{
		CFileTypeExtension* pExt = new CFileTypeExtension();
		pExt->m_ext = ext;
		m_extensions.Add(pExt);
	}

	int GetFileExtensionsCount()
	{
		return m_extensions.GetSize();
	}

	CUString GetFileExtension(int index)
	{
		return m_extensions[index]->m_ext;
	}

	void RemoveFileExtension(int index)
	{
		delete m_extensions[index];
		m_extensions.RemoveAt(index);
	}

	int m_registered;
	int m_registeredFromRegistry;

	int IsFileTypeRegistered();
	void SetFileTypeRegistered(int registered);

	void UpdateFileTypeRegisteredFromRegistry();
	BOOL RegisterFileType();
	void UnRegisterFileType();
//	void GetExtensionStringList(CStringList& extlist);
};

class CFileTypes
{
public:

	CArray<CFileType*,CFileType*> m_fileTypes;

	void UpdateFromRegistry();
	void UpdateToRegistry();
};
