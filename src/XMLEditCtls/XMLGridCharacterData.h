#ifndef XmlGrid_GridCharacterData_h
#define XmlGrid_GridCharacterData_h

#include "XMLGridNode.h"

namespace System
{

class XMLGRIDEXT CGridCharacterData :
	public CGridNode,
	public System::ITextData,
	public System::IEventListener
{
public:
	CGridCharacterData(LXmlEdit::Node* node);

	LXmlEdit::CharacterData* m_charData;
	UI::TextEdit* m_edit;

	System::StringW* GetValue();
//	virtual void Size(HDC hDC, int width);

	virtual void handleEvent(System::Event* evt);

//	virtual void OnRender2(LDraw::Graphics* pGraphics);
//	virtual void CalculateBoundsAndChildren(LDraw::SizeD availSize);

	virtual void Draw(MSWindows::HDC hDC, bool bSelected);
	virtual int Click(MSWindows::HDC hDC, LDraw::PointI point, UINT nFlags, bool bDblClk, CGridItem* *pVal);
	virtual void EndEdit(/*CXMLGridCtl* pUI*/);
	virtual void OnEditChange(MSWindows::HDC hDC, CGridItem* m_pTree);

	virtual int HitTest(LDraw::PointI point, UINT nFlags, CGridItem* *pVal);

	virtual void BuildXML(System::StringBuilderW& stream);
	virtual void BuildXML(System::IO::ISequentialByteStream* stream);

	virtual unsigned int GetLen()
	{
		return m_charData->get_length();
	}
	virtual WCHAR* GetData()
	{
		return const_cast<WCHAR*>(m_charData->get_data()->c_str());
	}
	virtual void SetData(const WCHAR* data, unsigned int len)
	{
		m_charData->set_data(new System::StringW(string_copy(data, len)));
	}
	virtual void InsertText(unsigned int offset, const WCHAR* data, unsigned int len)
	{
		m_charData->insertData(offset, new System::StringW(string_copy(data, len)));
	}
	virtual void AppendText(const WCHAR* data, unsigned int len)
	{
		ASSERT(0);
		//m_charData->insertData(offset, new System::StringW(data, len));
	}
	virtual void DeleteText(unsigned int offset, unsigned int len)
	{
		m_charData->deleteData(offset, len);
	}
	virtual void ReplaceText(unsigned int offset, unsigned int deletelen, const WCHAR* data)
	{
		ASSERT(0);
	}
};

}

#endif // XmlGrid_GridCharacterData_h
