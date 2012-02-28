#ifndef Web_CharacterData_h
#define Web_CharacterData_h

namespace System
{
namespace Web
{

class WEBEXT CharacterData : public ChildNode, public EventTarget
{
public:

	CTOR CharacterData(PCharacterData* pNode);

	virtual uint get_length() const;
	virtual String get_data();
	virtual void set_data(StringIn newVal);
	virtual void replaceData(unsigned int offset, unsigned int count, StringIn arg);
	virtual void deleteData(unsigned int offset, unsigned int count);
	virtual void insertData(unsigned int offset, StringIn arg);
	virtual void appendData(StringIn arg);
	virtual String substringData(unsigned int offset, unsigned int count) const;

	virtual String get_textContent() override;

protected:

	friend class Attr;
	friend class Document;
	friend class XMLParser;

	String m_data;
};

}	// Web
}	// System

#endif	// Web_CharacterData_h
