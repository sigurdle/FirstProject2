#include "stdafx.h"
#include "LXUI2.h"
#include "TextDocument.h"

//#include <functional>

namespace System
{

TextData::TextData()
{
	m_data = NULL;
	m_len = 0;
	m_alloclen = 0;
}

TextData::TextData(StringW* str)
{
	m_textAsString = str;
//	m_data = str->begin();
	m_len = str->Length();
	m_alloclen = 0;
}

TextData::~TextData()
{
	delete m_data;
}

void TextData::SetTextAsString(StringW* str)
{
	m_textAsString = str;
//	m_data = str->begin();
	m_len = str->Length();
	m_alloclen = 0;

	InsertedText(0);
}

void TextData::ReadFromStream(IO::ISequentialByteStream* stream)
{
	unsigned int size = stream->GetSize();
	m_alloclen = AllocLen(size);
	m_data = new WCHAR[m_alloclen];

	char buffer[512];
	unsigned int offset = 0;

	while (1)
	{
		ULONG nRead = stream->Read(buffer, 512);
		for (int i = 0; i < nRead; i++)
		{
			if (buffer[i] != '\r')
			{
				m_data[offset++] = buffer[i];
			}
		}

		if (nRead < 512) break;
	}
	m_len = offset;

/*

		WCHAR* newdata = (WCHAR*)new WCHAR[newalloclen];//*sizeof(WCHAR));
		memcpy(newdata, m_data, m_len*sizeof(WCHAR));

		for (int i = 0; i < nRead; i++)
		{
			if (buffer[i] == '\r')
			{
				i++;

			}
		}
		
	*/
	
//	BuildLineOffsets();
}

unsigned int TextData::GetLen()
{
	return m_len;
}

WCHAR* TextData::GetData()
{
	if (m_data)
		return m_data;
	else if (m_textAsString)
		return m_textAsString->begin();

	return NULL;
}

unsigned int TextData::AllocLen(unsigned int len)
{
	if (len <= 8)
	{
		return 8;
	}
	else if (len <= 16)
	{
		return 16;
	}
	else if (len <= 32)
	{
		return 32;
	}
	else if (len <= 64)
	{
		return 64;
	}
	else if (len <= 128)
	{
		return 128;
	}
	else if (len <= 256)
	{
		return 256;
	}
	else
	{
		return (len+511) & ~511;
	}
}

void TextData::SetData(const WCHAR* data, unsigned int len)
{
	if (len > m_alloclen)
	{
		m_alloclen = AllocLen(len);
		m_data = (WCHAR*)new WCHAR[m_alloclen];//)*sizeof(WCHAR));
	}

	m_len = len;

	if (data)
	{
		std::memcpy(m_data, data, len*sizeof(WCHAR));
	}

//	BuildLineOffsets();

	ASSERT(0);
#if 0
	TextDataEvent* evt = new TextDataEvent;
	evt->m_offset = -1;
	evt->m_len = -1;
	evt->InitEvent(WSTR("TextChanged"), false, false);
	dispatchEvent(evt);
#endif
}

void TextData::CopyStringOnWrite()
{
	if (m_textAsString)
	{
		int alloclen = AllocLen(m_textAsString->Length());

		m_data = (WCHAR*)new WCHAR[alloclen];
		std::memcpy(m_data, m_textAsString->begin(), alloclen*sizeof(WCHAR));

		m_textAsString = NULL;
	}
}

void TextData::InsertText(unsigned int offset, const WCHAR* data, unsigned int len)
{
	CopyStringOnWrite();

	unsigned int newlen = m_len+len;
	if (newlen <= m_alloclen)
	{
		std::memmove(m_data+offset+len, m_data+offset, (m_len - offset)*sizeof(WCHAR));
		std::memcpy(m_data+offset, data, len*sizeof(WCHAR));
	}
	else
	{
		unsigned int newalloclen = AllocLen(newlen);

		WCHAR* newdata = (WCHAR*)new WCHAR[newalloclen];//*sizeof(WCHAR));
		std::memcpy(newdata, m_data, offset*sizeof(WCHAR));
		std::memcpy(newdata+offset, data, len*sizeof(WCHAR));
		std::memcpy(newdata+offset+len, m_data+offset, (m_len-offset)*sizeof(WCHAR));
		delete m_data;
		m_alloclen = newalloclen;
		m_data = newdata;
	}
	m_len = newlen;

//	BuildLineOffsets();	// TODO

	InsertedText(offset);

#if 0
	TextDataEvent* evt = new TextDataEvent;
	evt->m_offset = offset;
	evt->m_len = len;
	evt->InitEvent(WSTR("TextInserted"), false, false);
	dispatchEvent(evt);
#endif
}

void TextData::DeleteText(unsigned int offset, unsigned int len)
{
	if (len > m_len)
		THROW(-1);

	CopyStringOnWrite();

	unsigned int newlen = m_len - len;
	unsigned int newalloclen = AllocLen(newlen);

	if (newalloclen < m_alloclen)
	{
		WCHAR* newdata = (WCHAR*)new WCHAR[newalloclen];//*sizeof(WCHAR));
		std::memcpy(newdata, m_data, offset*sizeof(WCHAR));
		std::memcpy(newdata+offset, m_data+offset+len, (m_len-len-offset)*sizeof(WCHAR));
		delete m_data;
		m_data = newdata;
		m_alloclen = newalloclen;
	}
	else
	{
		std::memmove(m_data+offset, m_data+offset+len, (m_len-len-offset)*sizeof(WCHAR));
	}

	m_len = newlen;

	ASSERT(0);
#if 0
	TextDataEvent* evt = new TextDataEvent;
	evt->m_offset = offset;
	evt->m_len = len;
	evt->InitEvent(WSTR("TextDeleted"), false, false);
	dispatchEvent(evt);
#endif
}

void TextData::ReplaceText(unsigned int offset, unsigned int deletelen, const WCHAR* data)
{
	ASSERT(0);
}

void TextData::AppendText(const WCHAR* data, unsigned int len)
{
	InsertText(m_len, data, len);
	/*
	int newlen = m_len+len;
	if (newlen <= m_alloclen)
	{
		memmove(m_data+offset+len, m_data+offset, (m_len - offset)*sizeof(WCHAR));
		memcpy(m_data+offset, data, len*sizeof(WCHAR));
	}
	else
	{
		int newalloclen = AllocLen(newlen);

		WCHAR* newdata = (WCHAR*)new WCHAR[newalloclen];//*sizeof(WCHAR));
		memcpy(newdata, m_data, offset*sizeof(WCHAR));
		memcpy(newdata+offset, data, len*sizeof(WCHAR));
		memcpy(newdata+offset+len, m_data+offset, (m_len-offset)*sizeof(WCHAR));
		delete m_data;
		m_alloclen = newalloclen;
		m_data = newdata;
	}
	m_len = newlen;

	TextDataEvent* evt = new TextDataEvent;
	evt->m_offset = offset;
	evt->m_len = len;
	evt->InitEvent(WSTR("TextInserted"), false, false);
	dispatchEvent(evt);
	*/
}

StringW* TextData::GetTextAsString()
{
	if (m_textAsString == NULL)
	{
		m_textAsString = new StringW(string_copy(GetData(), GetLen()));
	}

	return m_textAsString;
}

TextLines::TextLines(ITextData* textdata)
{
	m_textData = textdata;

	m_textData->get_InsertedText().connect(bind1st_of_2(mem_fun(&TextLines::OnInsertedText), this));

	BuildLineOffsets();
}

void TextLines::OnInsertedText(int offset)
{
	BuildLineOffsets();
	InsertedText(offset);
}

void TextLines::set_TextData(ITextData* textdata)
{
	if (m_textData)
	{
		VERIFY(0);
	}

	m_textData = textdata;
	m_textData->get_InsertedText().connect(bind1st_of_2(mem_fun(&TextLines::OnInsertedText), this));

	BuildLineOffsets();
}

void TextLines::SetTextAsString(StringW* str)
{
	m_textData->SetTextAsString(str);
	//BuildLineOffsets();	// ??
}

void TextLines::BuildLineOffsets()
{
	/*
	for (int i = 0; i < m_lines.GetSize(); i++)
	{
		delete m_rlines[i];
	}
	*/
	m_lines.RemoveAll();

	const WCHAR* data = m_textData->GetData();
	uint length = m_textData->GetLen();

	uint offset = 0;

	Line* pLine;

	pLine = new Line;
	m_lines.Add(pLine);

	pLine->m_offset = 0;

	int len = 0;

	while (offset < length)
	{
		int startoffset = offset;

		// Run until newline
		while (offset < length)
		{
			if (*data == '\n') break;
			offset++;
			data++;
		}

		len += offset-startoffset;

		if (offset < length)
		{
			ASSERT(*data == '\n');

			pLine->m_lineLength = len;
			pLine->m_lineLengthR = len+1;
			len = 0;

		// Start new line

			pLine = new Line;
			m_lines.Add(pLine);
			
			pLine->m_offset = ++offset;

			data++;
		}
	}

	pLine->m_lineLength = len;
	pLine->m_lineLengthR = len;

//	m_nDispLines.resize(m_rlinesArr.size());
}

}	// System
