#pragma once

namespace System
{

class CError : public System::Object
//	public IErrorItem
{
public:

	long GetLine()
	{
		return m_line;
	}
	long GetColumn()
	{
		return m_column;
	}
	long GetOffset()
	{
		return m_offset;
	}
	System::StringW* get_message()
	{
		return m_message;
	}
	System::StringW* get_uri()
	{
		return m_uri;
	}
	long get_severity()
	{
		return m_severity;
	}

public:

	System::StringW* m_message;
	System::StringW* m_uri;
	int m_line;
	int m_column;
	long m_offset;
	Web::DOMErrorSeverity m_severity;
};

class CErrorList// : public System::Object
{
public:
	~CErrorList()
	{
		ClearErrors();
	}

	Array<CError*> m_errors;

	void ClearErrors()
	{
		for (int i = 0; i < m_errors.GetSize(); i++)
		{
			delete m_errors[i];//->Release();
		}

		m_errors.RemoveAll();
	}

	void OffsetErrors(long afterOffset, long offset)
	{
		for (int i = 0; i < m_errors.GetSize(); i++)
		{
			if (m_errors[i]->m_offset >= afterOffset)
				m_errors[i]->m_offset += offset;
		}
	}

	void RemoveErrorsInRange(long startOffset, long endOffset)
	{
		for (int i = m_errors.GetSize()-1; i >= 0; i--)
		{
			if (m_errors[i]->m_offset >= startOffset &&
				m_errors[i]->m_offset <= endOffset)
			{
				delete m_errors[i];//->Release();
				m_errors.RemoveAt(i);
			}
		}
	}

	long GetErrorCount()
	{
		return m_errors.GetSize();
	}

	CError* GetErrorItem(uint index)
	{
		if (index < m_errors.GetSize())
		{
			return m_errors[index];
		}
		else
			return NULL;
	}
};

}
