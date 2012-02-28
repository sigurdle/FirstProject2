#include "StdAfx.h"
#include "X3D2.h"
#include "VRMLLoader.h"

#include "X3DScene.h"
#include "Group.h"
#include "Layer.h"
#include "LayerSet.h"

namespace System
{
using namespace IO;

namespace x3d
{

	/*
IO::TextWriter& WriteToStream(IO::TextWriter& writer, Lexer::Token token)
{
	ASSERT(0);
	return writer;
}
*/

ProfileDeclaration ProfileDeclaration::Interchange(L"Interchange");

static int Hex2Number(WCHAR c)
{
	if (c >= L'0' && c <= L'9')
		return c - L'0';
	else if (c >= L'a' && c <= L'f')
		return c - (L'a' - 10);
	else if (c >= L'A' && c <= L'F')
		return c - (L'A' - 10);
	else
		return -1;
}

struct FieldTypeIdent
{
	const WCHAR* fname;
	FieldType ftype;
};

FieldTypeIdent FieldTypeIdents[] =
{
	WSTR("SFBool"), FieldType_SFBool,
	WSTR("MFBool"), FieldType_SFBool,

	WSTR("MFInt32"), FieldType_MFInt32,
	WSTR("SFInt32"), FieldType_SFInt32,

	WSTR("SFFloat"), FieldType_SFFloat,
	WSTR("MFFloat"), FieldType_MFFloat,

	WSTR("SFDouble"), FieldType_SFDouble,
	WSTR("MFDouble"), FieldType_MFDouble,

	WSTR("SFTime"), FieldType_SFTime,
	WSTR("MFTime"), FieldType_MFTime,

	WSTR("SFNode"), FieldType_SFNode,
	WSTR("MFNode"), FieldType_MFNode,

	WSTR("SFVec2f"), FieldType_SFVec2f,
	WSTR("MFVec2f"), FieldType_MFVec2f,

	WSTR("SFVec2d"), FieldType_SFVec2d,
	WSTR("MFVec2d"), FieldType_MFVec2d,

	WSTR("SFVec3f"), FieldType_SFVec3f,
	WSTR("MFVec3f"), FieldType_MFVec3f,

	WSTR("SFVec4f"), FieldType_SFVec4f,
//	WSTR("MFVec4f"), FieldType_SFBool,

	WSTR("SFVec3d"), FieldType_SFVec3d,
	WSTR("MFVec3d"), FieldType_MFVec3d,

	WSTR("MFRotation"), FieldType_MFRotation,
	WSTR("SFRotation"), FieldType_SFRotation,

	WSTR("MFColor"), FieldType_MFColor,
	WSTR("SFColor"), FieldType_SFColor,

	WSTR("MFColorRGBA"), FieldType_MFColorRGBA,
	WSTR("SFColorRGBA"), FieldType_SFColorRGBA,

	WSTR("SFImage"), FieldType_SFImage,
	WSTR("MFImage"), FieldType_MFImage,

	WSTR("SFString"), FieldType_SFString,
	WSTR("MFString"), FieldType_MFString,

	/*
	WSTR("MFColor"),
	WSTR("MFColorRGBA"),
	WSTR("MFDouble"),
	WSTR("MFFloat"),
	WSTR("MFImage"),
	WSTR("MFNode"),
	WSTR("MFRotation"),
	WSTR("MFString"),
	WSTR("MFTime"),
	WSTR("MFVec2d"),
	WSTR("MFVec2f"),
	WSTR("MFVec3d"),
	WSTR("MFVec3f"),
	WSTR("MFURL"),

	WSTR("SFColor"),
	WSTR("SFColorRGBA"),
	WSTR("SFDouble"),
	WSTR("SFFloat"),
	WSTR("SFImage"),
	WSTR("SFNode"),
	WSTR("SFRotation"),
	WSTR("SFString"),
	WSTR("SFTime"),
	WSTR("SFVec2d"),
	WSTR("SFVec2f"),
	WSTR("SFVec3d"),
	WSTR("SFVec3f"),
	WSTR("SFURL"),
	*/
};

#define FieldTypesCount	_countof(FieldTypeIdents)

FieldType GetFieldType(StringIn str)
{
	for (size_t i = 0; i < FieldTypesCount; ++i)
	{
		if (str == FieldTypeIdents[i].fname)
		{
			return FieldTypeIdents[i].ftype;
		}
	}

	return (FieldType)0;
}

static ImmutableString<WCHAR> fieldtype_str[] =
{
	nullptr,

	L"SFBool",
	L"MFBool",

	L"MFInt32",
	L"SFInt32",

	nullptr,
	nullptr,

	L"SFFloat",
	L"MFFloat",

	L"SFDouble",
	L"MFDouble",

	L"SFTime",
	L"MFTime",

	L"SFNode",
	L"MFNode",

	L"SFVec2f",
	L"MFVec2f",

	L"SFVec2d",
	L"MFVec2d",

	L"SFVec3f",
	L"MFVec3f",

	L"SFVec3d",
	L"MFVec3d",

	L"MFRotation",
	L"SFRotation",

	L"MFColor",
	L"SFColor",

	L"MFColorRGBA",
	L"SFColorRGBA",

	L"SFImage",
	L"MFImage",

	L"SFString",
	L"MFString",

	// ??
	L"SFURL",
	L"MFURL",

	L"SFMatrix3f",
	L"MFMatrix3f",

	L"SFMatrix4f",
	L"MFMatrix4f",

	L"SFVec4f",
	L"MFVec4f",

	L"SFVec4d",
	L"MFVec4d",
};

X3DEXT String ToString(FieldType fieldtype)
{
	if (fieldtype >= _countof(fieldtype_str))
	{
		raise(ArgumentOutOfRangeException());
	}

	return &fieldtype_str[fieldtype];
}

/////////////////////////////
//

long Lexer::_getnumber()
{
	long number = 0;

	while (isdigit(m_c))
	{
		char c = m_c;
		adv();
		number = number*10 + (c - '0');
	}

	return number;
}

long Lexer::parsenumber()
{
	long fpos = m_fpos;

// get sign
	int sign = 1;

	if ((m_c == '-') || (m_c == '+'))
	{
		if (m_c == '-') sign = -1;
		adv();
	}

// get number
	long integer = _getnumber();

	if (m_fpos == fpos)
		fatalerror("end of file");

	if (sign == -1) integer = -integer;

	return integer;
}

double Lexer::getfrac()
{
	double dig = 0.1;
	double val = 0;

	//const char* p = *s;

	while (isdigit(m_c))
	{
		char c = m_c;
		val += dig * (c - '0');

		dig = 0.1 * dig;

		adv();
	}

	return val;
}

int Lexer::lookexp()
{
	int c;
	int exp;

	int minus = 0;

	c = m_c;
	if (tolower(c) != 'e')
	{
		return 0;
	}
	adv();

	c = m_c;
	if (c == '-')
	{
		minus = 1;
		adv();
	}
	else if (c == '+')
	{
		adv();
	}
	else
		fatalerror("expected -/+");

	c = m_c;
	if (c >= '0' && c <= '9')
	{
		exp = _getnumber();
	}
	else
	{
		return 0;
		//exp = 0;
		//p--;//myungetc(c);
	}

	if (minus)
		exp = -exp;

	//*s = p;

	return exp;
}

Lexer::Lexer()
{
	m_buffer = new char[64];
	m_fpos = 0;
	m_nstacked = 0;
}

Lexer::~Lexer()
{
	delete[] m_buffer;
}

int Lexer::Getc()
{
	int c = m_c;
	adv();
	return c;
}

int Lexer::lex()
{
	while (m_c == ' ' || m_c == '\t' || m_c == '\n' || m_c == '\r')
	{
		adv();
	}

	while (m_c == '#')	// comment
	{
		adv();

		while (m_c != EOF && m_c != '\n')
		{
			adv();
		}

		while (m_c == ' ' || m_c == '\t' || m_c == '\n' || m_c == '\r')
		{
			adv();
		}
	}

	if (isalpha(m_c) || m_c == '_')
	{
		// TODO

		WCHAR buffer[256];
		int i = 0;
		buffer[i++] = m_c;
		adv();

		while (m_c != EOF)
		{
			if (!(isalnum(m_c) || m_c == '_' || m_c == '-'))
				break;

			buffer[i++] = m_c;
			adv();
		}
		buffer[i] = 0;

		m_val.string = string_copy(buffer);

		m_token = TOKEN_ID;
	}
	else if (isdigit(m_c) || m_c == '-' || m_c == '+'/* || m_c == '.'*/)
	{
		int sign = 1;

		if ((m_c == '-') || (m_c == '+'))
		{
			if (m_c == '-') sign = -1;
			adv();
		}

	// get number
		long integer = _getnumber();

		// get fraction
		double fraction;
		if (m_c == '.')
		{
			adv();
			fraction = getfrac();

		}
		else
		{
			/*
			if (sign == -1) integer = -integer;

			if (m_fpos == fpos)
				throw -1;
			return integer;
			*/
			fraction = 0;
		}

		int exp = 0;
	// get exp
		exp = lookexp();

		/*
		if (exp != 0 && fraction == 0)
		{
			MessageBeep(-1);
		}
		*/

		double value = makeflt(integer, fraction, exp);

		if (exp == 0 && fraction == 0)
		{
			if (sign == -1) integer = -integer;

			m_val.intval = integer;
			m_token = TOKEN_INT;
		}
		else
		{
			if (sign == -1) value = -value;

			m_val.floatval = value;
			m_token = TOKEN_FLOAT;
		}
	}
	else if (m_c == '\"' || m_c == '\'')
	{
		int delimiter = m_c;

		IO::StringWriter str;

		adv();

		while (m_c != EOF)
		{
			if (m_c == delimiter)
				break;

			str << (WCHAR)m_c;
			adv();
		}

		if (m_c != delimiter)
		{
			fatalerror("expected delimiter");
		}

		adv();

		m_val.string = str.str();

		m_token = TOKEN_STRING;
	}
	else
	{
		m_val.symbol = m_c;

		if (m_c == EOF)
			m_token = TOKEN_EOF;
		else
			m_token = TOKEN_SYMBOL;

		adv();
	}

	return m_token;
}

void Lexer::adv()
{
	// TODO, not buffered here
	if (m_nstacked > 0)
	{
		--m_nstacked;
		m_c = m_buffer[(m_fpos++) & 63];
		++m_column;

		if (m_c == '\n')
		{
			++m_line;
			m_column = 0;
		}
		return;
	}

	uint count = MIN(32, 64 - (m_fpos & 63));
	uint nRead = m_stream->Read(m_buffer + (m_fpos & 63), count);
	if (nRead > 0)
	{
		m_nstacked = nRead - 1;
		m_c = m_buffer[(m_fpos++) & 63];
		++m_column;

		if (m_c == '\n')
		{
			++m_line;
			m_column = 0;
		}
	}
	else
		m_c = -1;
}

#if 0
void Lexer::unGetc()
{
	if (m_fpos > 1)
	{
		if (m_c == '\n') --m_line;

		m_nstacked++;
		m_fpos--;
		m_c = m_buffer[(m_fpos-1) & 63];

		/*
		int c = m_buffer[m_fpos];
		if (c == '\n')
		{
			m_line--;
		}
		*/
	}
	else
		ASSERT(0);
}
#endif

///////////////////////////////////////////////////////////////////////
// VRMLLoader

VRMLLoader::VRMLLoader()
{
	m_scene = nullptr;
	m_url = nullptr;
}

VRMLLoader::~VRMLLoader()
{
	for (unsigned int i = 0; i < m_routes.size(); ++i)
	{
		delete m_routes[i];
	}
	m_routes.clear();
}

long VRMLLoader::getnumber()
{
	if (m_token != TOKEN_INT)
		fatalerror("expected number");

	int intval = m_val.intval;
	lex();

	return intval;
}

double VRMLLoader::getfnumber()
{
	if (m_token == TOKEN_FLOAT)
	{
		double floatval = m_val.floatval;
		lex();
		return floatval;
	}
	else if (m_token == TOKEN_INT)
	{
		double floatval = m_val.intval;
		lex();
		return floatval;
	}

	fatalerror("expected number");
	return 0;
}

String VRMLLoader::readidentifier()
{
	if (m_token != TOKEN_ID)
	{
		fatalerror(L"expected identifier");
	}

	String id = m_val.string;
	lex();
	return id;
}

String VRMLLoader::peekidentifier()
{
	if (m_token != TOKEN_ID)
	{
		fatalerror(L"expected identifier");
	}

	String id = m_val.string;
	return id;
}

String VRMLLoader::readstring()
{
	if (m_token != TOKEN_STRING)
	{
		fatalerror(L"expected string");
	}

	String id = m_val.string;
	lex();
	return id;
}

void VRMLLoader::EatChar(int c)
{
	if (m_token != TOKEN_SYMBOL || m_val.symbol != c)
	{
	//	WCHAR msg[256];
		//swprintf_s(msg, L"Expected '%c'", c);
		fatalerror("wrong char");
	}

	lex();
}

void VRMLLoader::read(char* buffer, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		int c = Getc();
		if (c == -1)
		{
			fatalerror("Unexpected EOF");
		}

		buffer[i] = c;
	}
	/*
	ULONG nRead;
	m_stream->Read(buffer, count, &nRead);
	if (nRead != count)
	{
		m_eof = TRUE;
		throw "Unexpected EOF";
	}
	*/
}

void VRMLLoader::ReadFieldValue(X3DField* pField)
{
	ASSERT(pField);

	if (true)	// Inside proto
	{
		//int c = m_c;//Getc();
		if (m_token == TOKEN_ID && m_val.string == L"IS")
		{
		//	adv();
		//	c = m_c;//Getc();
		//	if (c == 'S')
		//	{
				lex();

			//	SkipAtLeastOneSpace();

				pField->m_is = readidentifier();
			//	SkipSpaces();
				return;
		//	}
			/*
			else
			{
				unGetc();
				//unGetc();
			}
			*/
		}
	//	else
	//		unGetc();
	}

	FieldType fieldType = pField->getFieldType();
	X3DField* field = pField;

	if (IsSField(fieldType))
	{
		ReadSF(field);
	}
	else
	{
// If the field has exactly one value, the brackets may be omitted

	// MF
		switch (fieldType)
		{
		case FieldType_MFInt32:
		case FieldType_MFFloat:
		case FieldType_MFDouble:
		case FieldType_MFVec2f:
		case FieldType_MFVec3f:
		case FieldType_MFRotation:
		case FieldType_MFColor:
		case FieldType_MFString:
		case FieldType_MFNode:	// ??
		case FieldType_MFURL:	// ??
			{
				bool bSingleValue;

				//int c = m_c;//Getc();
				if (m_token == TOKEN_SYMBOL && m_val.symbol == '[')
				{
					lex();
					bSingleValue = false;
				}
				else
				{
					bSingleValue = true;
					//unGetc();
				}

				while (!eof())
				{
					// ??
					{
						//int c = m_c;//Getc();
						if (m_token == TOKEN_SYMBOL && m_val.symbol == ',')
						{
							lex();
						}
					//	else
					//		unGetc();
					}

					if (!bSingleValue)
					{
						//int c = m_c;
						
						if (m_token == TOKEN_SYMBOL && m_val.symbol == ']')
						{
							break;
						}
					}

					switch (fieldType)
					{
					case FieldType_MFInt32:
						{
							static_cast<MFInt32*>(field)->m_items.Add(ReadInt32());
						}
						break;

					case FieldType_MFFloat:
						{
							static_cast<MFFloat*>(field)->m_items.Add(ReadFloat());
						}
						break;

					case FieldType_MFDouble:
						{
							static_cast<MFDouble*>(field)->append1Value(ReadDouble());
						}
						break;

					case FieldType_MFVec2f:
						{
							static_cast<MFVec2f*>(field)->append1Value(ReadVec2f());
						}
						break;

					case FieldType_MFVec3f:
						{
							static_cast<MFVec3f*>(field)->append1Value(ReadVec3f());
						}
						break;

					case FieldType_MFRotation:
						{
							static_cast<MFRotation*>(field)->m_items.Add(ReadRotation());
						}
						break;

					case FieldType_MFColor:
						{
							static_cast<MFColor*>(field)->m_items.Add(ReadColor());
						}
						break;

#if 0
					case FieldType_MFURL:
						{
							<CURL>* pSFString;
							<SFString>::CreateInstance(&pSFString);
							if (pSFString == nullptr)
							{
								throw L"Failed to create field";
							}
							pSFString->AddRef();

							try
							{
								ReadSF(pSFString);
								static_cast<CLMFURL*>(field)->m_items.Add(_bstr_t(pSFString->m_value));
							}
							catch (int n)
							{
								pSFString->Release();
								throw n;
							}
						}
						break;
#endif

					case FieldType_MFURL:
						{
							static_cast<MFURL*>(field)->append1Value(readstring());
						}
						break;

					case FieldType_MFString:
						{
							static_cast<MFString*>(field)->append1Value(readstring());
						}
						break;

					case FieldType_MFNode:
						{
							MFNode* mfnode = static_cast<MFNode*>(field);

							String nodeType = readidentifier();
							X3DNode* node = ReadNode(nodeType, mfnode->getOwnerNode()->m_ownerLayer);

							mfnode->m_nLights += node->GetLights();
							//mfnode->m_nViewpoints += pSFNode.m_value->m_nViewpoints;
						//	node->m_ownerLayer = mfnode->getOwnerNode()->m_ownerLayer;
							node->m_parents.Add(mfnode);
							mfnode->m_items.Add(node);
						}
						break;
					}

					if (!bSingleValue)
					{
						//c = m_c;//Getc();
						/*
						if (c != L',')
						{
							unGetc();
							SkipSpaces();
							break;
						}
						*/
						if (m_token == TOKEN_SYMBOL && m_val.symbol == ',')	// comma is optional ??
						{
							lex();
						//	unGetc();
						}
					}

					if (bSingleValue)
						break;
				}
				
				if (!bSingleValue)
				{
					EatChar(']');
				}
			}
			break;

			/*
		case MFFloat:
			{
				EatChar(L'[');

				SkipSpaces();

				while (!eof())
				{
					int c = Getc();
					unGetc();
					if (c == L']')
					{
						break;
					}

					<SFFloat>* pSFFloat;
					<SFFloat>::CreateInstance(&pSFFloat);
					if (pSFFloat == nullptr)
					{
						throw L"Failed to create field";
					}
					pSFFloat->AddRef();

					try
					{
						ReadSF(pSFFloat);
						static_cast<MFFloat*>(field)->m_items.Add(_variant_t(pSFFloat->GetUnknown()));
					}
					catch (WCHAR *p)
					{
						pSFFloat->Release();
						throw p;
					}

					SkipSpaces();
				}
				
				EatChar(L']');

				SkipSpaces();
			}
			break;
			*/

			/*
		case MFString:
			{
				EatChar(L'[');

				SkipSpaces();

				while (!eof())
				{
					int c = Getc();
					unGetc();
					if (c == L']')
					{
						break;
					}

					<SFString>* pSFString;
					<SFString>::CreateInstance(&pSFString);
					if (pSFString == nullptr)
					{
						throw L"Failed to create field";
					}
					pSFString->AddRef();

					try
					{
						ReadSF(pSFString);//->m_v = readstring();
						static_cast<MFString*>(field)->m_items.Add(_variant_t(pSFString->GetUnknown()));
					}
					catch (WCHAR *p)
					{
						pSFString->Release();
						throw p;
					}

					SkipSpaces();
				}
				
				EatChar(L']');

				SkipSpaces();
			}
			break;
			*/

			/*
		case MFNode:
			{
				EatChar(L'[');
				
				SkipSpaces();
				
				while (!eof())
				{
					int c = Getc();
					unGetc();
					if (c == L']')
					{
						break;
					}

					<SFNode>* pSFNode;
					<SFNode>::CreateInstance(&pSFNode);
					if (pSFNode == nullptr)
					{
						throw L"Failed to create field";
					}
					pSFNode->AddRef();

					try
					{
					//	sysstring nodeType = readidentifier();

						ReadSF(pSFNode);//CComPtr<ILSAINode> node = ReadNode(nodeType);	// Recurse
						//pSFNode->m_v = node;

						static_cast<MFNode*>(field)->m_items.Add(_variant_t(pSFNode->GetUnknown()));

						if (pSFNode->m_v)	// TODO
						{
							m_scene->m_timeDependantNodes.Add(pSFNode->m_v);
						}
					}
					catch(WCHAR* p)
					{
						pSFNode->Release();
						throw p;
					}
					
					SkipSpaces();
				}
				
				EatChar(L']');

				SkipSpaces();
			}
			break;
			*/
			
		default:
			fatalerror(WSTR("Unimplemented parsing of field type"));
		}
	}
}

void VRMLLoader::ReadSF(X3DField* field)
{
	FieldType fieldType = field->getFieldType();
	switch (fieldType)
	{
	// SF
	case FieldType_SFBool:
		{
			String str = readidentifier();

			if (str == L"TRUE")
				dynamic_cast<SFBool*>(field)->setValue(true);
			else if (str == L"FALSE")
				dynamic_cast<SFBool*>(field)->setValue(false);
			else
				fatalerror(WSTR("Invalid bool value, should be TRUE or FALSE"));
		}
		break;

	case FieldType_SFInt32:
		{
			long value = getnumber();
			dynamic_cast<SFInt32*>(field)->setValue(value);
		}
		break;

	case FieldType_SFFloat:
		{
			float value = (float)getfnumber();
			dynamic_cast<SFFloat*>(field)->setValue(value);
		}
		break;

	case FieldType_SFDouble:
		{
			double value = getfnumber();
			dynamic_cast<SFDouble*>(field)->setValue(value);
		}
		break;

	case FieldType_SFString:
		{
			String str = readstring();
			dynamic_cast<SFString*>(field)->setValue(str);
		}
		break;

	case FieldType_SFColor:
		{
			/*
			float value[3];

			value[0] = (float)getfnumber();
			value[1] = (float)getfnumber();
			value[2] = (float)getfnumber();
			*/

			dynamic_cast<SFColor*>(field)->setValue(ReadColor());
		}
		break;

	case FieldType_SFTime:
		{
			dynamic_cast<SFTime*>(field)->m_value = getfnumber();
		}
		break;

	case FieldType_SFVec2f:
		{
			dynamic_cast<SFVec2f*>(field)->setValue(ReadVec2f());
		}
		break;

	case FieldType_SFVec3f:
		{
			Vec3f value = ReadVec3f();
			dynamic_cast<SFVec3f*>(field)->setValue(value);
		}
		break;

	case FieldType_SFVec4f:
		{
			dynamic_cast<SFVec4f*>(field)->setValue(ReadVec4f());
		}
		break;

	case FieldType_SFRotation:
		{
			dynamic_cast<SFRotation*>(field)->setValue(ReadRotation());
		}
		break;

	case FieldType_SFNode:
		{
			SFNode* sfnode = static_cast<SFNode*>(field);
			sfnode->setX3DNode(ReadNode(readidentifier(), sfnode->getOwnerNode()->m_ownerLayer));
		}
		break;
/*
	case FieldType_SFVec2d:
		{
			dynamic_cast<SFVec2d*>(field)->setValue(ReadVec2d());
		}
		break;

	case FieldType_SFVec3d:
		{
			dynamic_cast<SFVec3d*>(field)->setValue(ReadVec3d());
		}
		break;

	case FieldType_SFVec4d:
		{
			dynamic_cast<SFVec4d*>(field)->setValue(ReadVec4d());
		}
		break;
*/

#if 0
	case SFImage:
		{
			SFImage* pSFImage = static_cast<SFImage*>(field);

			pSFImage->m_width = getnumber();
			SkipSpaces();

			pSFImage->m_height = getnumber();
			SkipSpaces();

			pSFImage->m_components = getnumber();
			SkipSpaces();

			if (pSFImage->m_width < 0)
				fatalerror(WSTR("Negative image width not allowed");

			if (pSFImage->m_height < 0)
				fatalerror(WSTR("Negative image height not allowed");

			if (!(pSFImage->m_components == 1 ||	// gray
					pSFImage->m_components == 2 ||	// gray+alpha
					pSFImage->m_components == 3 ||	// rgb
					pSFImage->m_components == 4))		// rgb+alpha
			{
				fatalerror(WSTR("Unsupported number of components");
			}

			for (int y = 0; y < static_cast<SFImage*>(field)->m_height; y++)
			{
				for (int x = 0; x < static_cast<SFImage*>(field)->m_width; x++)
				{
					DWORD value;

					int c = Getc();
					if (c == '0')
					{
						c = Getc();
						if (c == 'x')
						{
							while (!eof())
							{
								c = Getc();
								int hex = Hex2Number(c);
								if (hex == -1)
								{
									unGetc();
									break;
								}

								value <<= 4;
								value |= hex;
							}
						}
						else
						{
							value = getnumber();
						}
					}
					else
						value = getnumber();

					SkipSpaces();
				}
			}
		}
		break;
#endif
	default:
		fatalerror(WSTR("Unimplemented parsing of field type"));
	}
}

bool VRMLLoader::ReadBool()
{
	String str = readidentifier();

	if (str == L"TRUE")
		return true;
	else if (str == L"FALSE")
		return false;
	else
	{
		fatalerror(WSTR("Invalid bool value, should be TRUE or FALSE"));
		return false;
	}
}

int32 VRMLLoader::ReadInt32()
{
	return getnumber();
}

float VRMLLoader::ReadFloat()
{
	return (float)getfnumber();
}

double VRMLLoader::ReadDouble()
{
	return getfnumber();
}

double VRMLLoader::ReadTime()
{
	return getfnumber();
}

Vec3f VRMLLoader::ReadColor()
{
	Vec3f value;

	value[0] = (float)getfnumber();
	value[1] = (float)getfnumber();
	value[2] = (float)getfnumber();

	return value;
}

Vec4f VRMLLoader::ReadColorRGBA()
{
	Vec4f value;

	value[0] = (float)getfnumber();
	value[1] = (float)getfnumber();
	value[2] = (float)getfnumber();
	value[4] = (float)getfnumber();

	return value;
}

Vec2f VRMLLoader::ReadVec2f()
{
	Vec2f value;

	value[0] = (float)getfnumber();
	value[1] = (float)getfnumber();

	return value;
}

Vec3f VRMLLoader::ReadVec3f()
{
	float x = (float)getfnumber();
	float y = (float)getfnumber();
	float z = (float)getfnumber();

	return Vec3f(x, y, z);
}

Vec4f VRMLLoader::ReadVec4f()
{
	Vec4f value;

	value[0] = (float)getfnumber();
	value[1] = (float)getfnumber();
	value[2] = (float)getfnumber();
	value[3] = (float)getfnumber();

	return value;
}

Vec2d VRMLLoader::ReadVec2d()
{
	Vec2d value;

	value[0] = getfnumber();
	value[1] = getfnumber();

	return value;
}

Vec3d VRMLLoader::ReadVec3d()
{
	Vec3d value;

	value[0] = getfnumber();
	value[1] = getfnumber();
	value[2] = getfnumber();

	return value;
}

Vec4d VRMLLoader::ReadVec4d()
{
	Vec4d value;

	value[0] = getfnumber();
	value[1] = getfnumber();
	value[2] = getfnumber();
	value[3] = getfnumber();

	return value;
}

Rotation VRMLLoader::ReadRotation()
{
	Vec3f axis = ReadVec3f();
	float angle = (float)getfnumber();

	return Rotation(axis, angle);
}

/*
X3DNode* VRMLLoader::ReadNode()
{
	String nodeType = readidentifier();

	return ReadNode(nodeType);
}
*/

void VRMLLoader::ROUTEStatement()
{
	CRoute* pRoute = new CRoute;

	try
	{
		// nodeNameId . eventOutId TO nodeNameId . eventInId 

		pRoute->m_sourceNodeNameId = readidentifier();
		EatChar('.');
		pRoute->m_sourceField = readidentifier();

		String str = readidentifier();
		if (str != "TO")
			fatalerror(WSTR("Expected 'TO' in 'ROUTE' statement"));

		pRoute->m_destinationNodeNameId = readidentifier();
		EatChar('.');
		pRoute->m_destinationField = readidentifier();

		m_routes.Add(pRoute);
	}
	catch (int n)
	{
		delete pRoute;
		throw n;
	}
}

SAIProtoDeclaration* VRMLLoader::LoadExternProtoUrl(StringIn url)
{
	SAIProtoDeclaration* pProtoDecl = nullptr;
	ASSERT(0);
#if 0

	WCHAR buf[512];
	wcscpy(buf, url);
	WCHAR* p = buf;
	WCHAR* name;
	int i = wcslen(url)-1;
	while (i >= 0)
	{
		if (p[i] == '#')
		{
			name = &p[i+1];
			p[i] = 0;
			break;
		}
		i--;
	}

	CVRMLLoader* loader = new CVRMLLoader;
	//loader.CoCreateInstance(CLSID_VRMLLoader);

	TCHAR result[512];
	DWORD resultLen = sizeof(result);
	InternetCombineUrl(_bstr_t(m_url), _bstr_t(buf), result, &resultLen, 0);

	CLX3DScene* scene = loader->Load(result);

	if (scene)
	{
		CLSAIProtoDeclaration* pProto = scene->FindProto(name);

		scene.Detach();

		if (pProto)
		{
			pProtoDecl = pProto;
		}
		else
		{
			fatalerror(WSTR("Failed to find proto in external file");
		}
	}
#endif

	return pProtoDecl;
}

// TODO rename ReadStatement and don't return a node ?
X3DNode* VRMLLoader::ReadNode(StringIn ident, X3DLayerNode* ownerLayer)
{
	String name;
	String nodeType;

	if (ident == L"nullptr")
	{
		return nullptr;
	}
	else if (ident == L"PROTO" ||
				ident == L"EXTERNPROTO")
	{
		bool bExtern = (ident == L"EXTERNPROTO");

		SAIProtoDeclaration* pProtoDecl = new SAIProtoDeclaration;

		try
		{
			pProtoDecl->m_name = readidentifier();

		// Interface declaration
			EatChar('[');	// ]

			while (!eof())
			{
			//	int c = Getc();
			//	unGetc();
				// [
				if (m_token == TOKEN_SYMBOL && m_val.symbol == L']')
				{
					break;
				}

				String fieldAccessTypeIdent = readidentifier();

				int fieldAccess = -1;
				bool bInitialValue = false;

				if (fieldAccessTypeIdent == "initializeOnly" ||
					fieldAccessTypeIdent == "field")	// VRML97 deprecated
				{
					fieldAccess = SAIFieldAccess_initializeOnly;
					bInitialValue = true;
				}
				else if (fieldAccessTypeIdent == "inputOnly")
				{
					fieldAccess = SAIFieldAccess_inputOnly;
					bInitialValue = true;
				}
				else if (fieldAccessTypeIdent == "eventIn")	// VRML97 deprecated
				{
					fieldAccess = SAIFieldAccess_inputOnly;
					bInitialValue = false;
				}
				else if (fieldAccessTypeIdent == "outputOnly")
				{
					fieldAccess = SAIFieldAccess_outputOnly;
					bInitialValue = false;
				}
				else if (fieldAccessTypeIdent == "eventOut")	// VRML97 deprecated
				{
					fieldAccess = SAIFieldAccess_outputOnly;
					bInitialValue = false;
				}
				else if (fieldAccessTypeIdent == "inputOutput" ||
						fieldAccessTypeIdent == "exposedField")	// VRML97 deprecated
				{
					fieldAccess = SAIFieldAccess_inputOutput;
					bInitialValue = true;
				}

				if (fieldAccess == -1)
				{
					fatalerror("Expected field access type");
				}

				String fieldTypeIdent = readidentifier();

				FieldType ftype = GetFieldType(fieldTypeIdent);

				if (ftype == (FieldType)0)	// couldn't find it
				{
					WCHAR msg[512];
					ASSERT(0);
				//	swprintf_s(msg, L"Unknown field type %s, in proto %s", fieldTypeIdent->c_str(), pProtoDecl->m_name->c_str());
					fatalerror(msg);
				}

				X3DField* pField;
				pField = X3DField::CreateFieldOfType(ftype, nullptr);
				pField->m_fieldName = readidentifier();

			// initial field value (format depends on fieldType)

				pProtoDecl->m_fields.Add(pField);

				if (!bExtern)
				{
					if (bInitialValue)
					{
						ReadFieldValue(pField);
					}
				}
			}

			// [
			EatChar(L']');

			if (bExtern)
			{
				vector<String> urls;
				//int c = Getc();
				if (m_token == TOKEN_SYMBOL && m_val.symbol == '[')
				{
					lex();

					while (!eof())
					{
						//int c = m_c;//Getc();
					//	unGetc();
						if (m_token == TOKEN_SYMBOL && m_val.symbol == ']')
						{
							break;
						}
						String url = readstring();
						urls.Add(url);

					//	int c = Getc();
					//	if (c == 
					}
					EatChar(']');

					pProtoDecl = LoadExternProtoUrl(urls[0]);
				}
				else
				{
					//unGetc();

					String url = readstring();

				//	LoadExternProtoUrl(url);
					pProtoDecl = LoadExternProtoUrl(url);
				}
			}
			else
			{
			// Definition

				EatChar(L'{');	// }

				while (!eof())
				{
				//	int c = Getc();
				//	unGetc();
					// {
					if (m_token == TOKEN_SYMBOL && m_val.symbol == L'}')
					{
						break;
					}
					String ident = readidentifier();

					X3DNode* x3dnode = ReadNode(ident, ownerLayer);
					if (x3dnode)
					{
						ASSERT(x3dnode);

						pProtoDecl->m_nodes.Add(x3dnode);
					}

				}

				// {
				EatChar(L'}');
			}

	//		pProtoDecl->AddRef();
			m_scene->m_protoDeclarations.Add(pProtoDecl);
		}
		catch(int n)
		{
		//	pProtoDecl->Release();
			throw n;
		}

		return nullptr;	// ??
	}
	else if (ident == L"ROUTE")
	{
		ROUTEStatement();

		return nullptr;
	}
	// Node statement
	else if (ident == L"USE")
	{
		// TODO, do this after parsing entire file ??
		String name = readidentifier();

		try
		{
			X3DNode* node = m_scene->getNamedNode(name);

			if (node == nullptr)
			{
				WCHAR msg[512];
				ASSERT(0);
				//swprintf_s(msg, L"Use of undefined def %s", name->c_str());
				fatalerror(msg);
			}

			return node;
		}
		catch (InvalidNodeException* e)
		{
			MessageBeep(-1);
			return nullptr;
		}
	}
	else
	{
		CDef* pDef = nullptr;

		if (ident == L"DEF")
		{
			pDef = new CDef;

			try
			{
				pDef->m_name = readidentifier();

				nodeType = readidentifier();

				m_scene->m_defs.push_back(pDef);
			}
			catch (Exception* e)
			{
				delete pDef;
				e->raiseme();
			}
		}
		else
		{
			nodeType = ident;
		}

		X3DNode* node = nullptr;

		NodeType* pNodeType = NodeType::FindByName(nodeType);
		if (pNodeType == nullptr)
		{
			// Try proto
			SAIProtoDeclaration* protoDecl = m_scene->getProtoDeclaration(nodeType);

			if (protoDecl)
			{
				X3DPrototypeInstance* instance = protoDecl->createInstance();

				node = instance;
			}
			/*
			else	// No normal nodetype and no proto
			{
				WCHAR msg[512];
				ASSERT(0);
			//	swprintf_s(msg, L"Unknown node type %s", nodeType->c_str());
				fatalerror(msg);
			}
			*/
		}
		else
		{
			node = m_scene->CreateNodeOfType(pNodeType);
		}

		X3DLayerNode* layerNode = dynamic_cast<X3DLayerNode*>(node);
		if (layerNode)
		{
			ownerLayer = layerNode;
		}

		if (ownerLayer == nullptr && layerNode == nullptr)
		{
			if (m_scene->m_root == nullptr)
			{
				m_scene->m_root = new Layer;
				m_scene->m_root->m_ownerLayer = m_scene->m_root;	// hm.. ??
				m_scene->m_root->m_scene = m_scene;
				ownerLayer = m_scene->m_root;
			}
		}

		/*
		if (node == nullptr)
		{
			WCHAR msg[512];
			ASSERT(0);
		//	swprintf_s(msg, L"Failed to create node %s", nodeType->c_str());
			fatalerror(msg);
		}
		*/
		if (node)
		{
			node->m_ownerLayer = ownerLayer;
		}
		else
		{
			warning(warning(X3DPARSER_UNKNOWNTYPE) << "Unknown nodeType " << '\'' << nodeType << '\'');
		}

		if (pDef)
		{
			if (node)
			{
				node->m_name = pDef->m_name;
			}
		}

		EatChar('{');	// }

		// body (node fields)
		while (!eof())
		{
			//int c = m_c;//Getc();
			//unGetc();
			// {
			if (m_token == TOKEN_SYMBOL && m_val.symbol == '}')
			{
				break;
			}

			String fieldName = readidentifier();

			if (fieldName == L"ROUTE")
			{
				ROUTEStatement();
			}
			else
			{
#if 0
				IX3DAddField* addFieldNode = dynamic_cast<IX3DAddField*>(node);

				if (addFieldNode != nullptr)
				{
					int fieldAccess = -1;
					bool bInitialValue = false;

					if (fieldName == L"initializeOnly" ||
						fieldName == L"field")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_initializeOnly;
						bInitialValue = true;
					}
					else if (fieldName == L"inputOnly")
					{
						fieldAccess = SAIFieldAccess_inputOnly;
						if (false)	//VRML97
							bInitialValue = true;
						else
							bInitialValue = false;
					}
					else if (fieldName == L"eventIn")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_inputOnly;
						bInitialValue = false;
					}
					else if (fieldName == L"outputOnly")
					{
						fieldAccess = SAIFieldAccess_outputOnly;
						bInitialValue = false;// ???TRUE;
					}
					else if (fieldName == L"eventOut")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_outputOnly;
						bInitialValue = false;
					}
					else if (fieldName == L"inputOutput" ||
							fieldName == L"exposedField")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_inputOutput;
						bInitialValue = true;
					}

					if (fieldAccess != -1)
					{
						String fieldTypeIdent = readidentifier();

						int i;

						for (i = 1; i < FieldTypesCount; i++)
						{
							if (fieldTypeIdent == FieldTypeIdents[i])
							{
								break;
							}
						}

						if (i == FieldTypesCount)	// couldn't find it
						{
							WCHAR msg[512];
							ASSERT(0);
						//	swprintf_s(msg, L"Unknown field type %s", fieldTypeIdent->c_str());
							fatalerror(msg);
						}

						X3DField* pField = CreateFieldOfType((FieldType)i, node);

						try
						{
							//pField->m_fieldType = (FieldType)i;
							pField->m_fieldName = readidentifier();

							if (bInitialValue)
							{
								// initial field value (format depends on fieldType)
								ReadFieldValue(pField);
							}

							addFieldNode->AddField(pField);

							/*
							// TODO, insert sorted
							node->m_fields.push_back(pField);

							if (shaderNode)
							{
								shaderNode->m_addfields.push_back(pField);
							}
							*/
						}
						catch (std::exception& e)
						{
						//	delete pField;
							throw e;
						}

						continue;
					}
				}
#endif

				// Normal field

				/*
				if (!wcscmp(fieldName, L"addChildren"))
				{
					fieldName = L"children";
				}
				*/

				X3DField* pField = nullptr;
				if (node)
				{
					pField = node->getField(fieldName);
				}

				if (pField == nullptr)
				{
					SAIFieldAccess fieldAccess;
					bool bInitialValue = false;
					bool isfield = true;

					if (fieldName == L"initializeOnly" ||
						fieldName == L"field")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_initializeOnly;
						bInitialValue = true;
					}
					else if (fieldName == L"inputOnly")
					{
						fieldAccess = SAIFieldAccess_inputOnly;
					//	if (false)	//VRML97
					//		bInitialValue = true;
					//	else
							bInitialValue = true;
					}
					else if (fieldName == L"eventIn")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_inputOnly;
						bInitialValue = false;
					}
					else if (fieldName == L"outputOnly")
					{
						fieldAccess = SAIFieldAccess_outputOnly;
						bInitialValue = false;
					}
					else if (fieldName == L"eventOut")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_outputOnly;
						bInitialValue = false;
					}
					else if (fieldName == L"inputOutput" ||
							fieldName == L"exposedField")	// VRML97 deprecated
					{
						fieldAccess = SAIFieldAccess_inputOutput;
						bInitialValue = true;
					}
					else
						isfield = false;

					if (isfield)
					{
						IX3DAddField* addfield = dynamic_cast<IX3DAddField*>(node);
						if (addfield == nullptr)
						{
							Console::get_Out() << L"Cannot add custom fields to this node";
						}

						String fieldTypeStr = readidentifier();
						FieldType fieldType = GetFieldType(fieldTypeStr);
						if (fieldType == (FieldType)0)
						{
							fatalerror(L"unknown fieldtype");
						}

						fieldName = readidentifier();

						if (addfield)
						{
							pField = X3DField::CreateFieldOfType(fieldType, node);
							pField->m_fieldName = fieldName;
							pField->m_fieldAccess =  fieldAccess;
							addfield->AddField(pField);

							/*
							if (bInitialValue)
							{
								ReadFieldValue(pField);
							}
							*/
						}
					}
#if 0
					else
					{
						WCHAR msg[512];
						ASSERT(0);
						//swprintf_s(msg, L"Unknown field %s:%s", nodeType->c_str(), fieldName->c_str());
						fatalerror(msg);
					}
#endif
				}

				/*
				if (pField == nullptr)
				{
					raise(Exception(L"field = nullptr"));
				}
				*/
				if (pField)
				{
					ReadFieldValue(pField);
				}
				else
				{
				//	if (m_token == TOKEN_SYMBOL && m_val.symbol == '[')
				//	{
				//	lex();
				//	bSingleValue = false;

					ASSERT(0);
				}

				/*
				if (*pField->m_fieldName == L"children")
				{
					MFNode* mfnode = dynamic_cast<MFNode*>(pField);
					if (mfnode == nullptr)
					{
						THROW(-1);
					}

					unsigned int count = mfnode->get_size();
					for (uint i = 0; i < count; i++)
					{
						X3DNode* child = mfnode->get1Value(i);

						child->m_parents.Add(mfnode);
						node->m_nLidescendantLights += child->m_descendantLights;
					}
				}
				*/

			}
		}

		// {
		EatChar(L'}');

		X3DPrototypeInstance* pInstance = dynamic_cast<X3DPrototypeInstance*>(node);
		if (pInstance)
		{
		//	 pInstance = static_cast<CLX3DPrototypeInstance*>(instance);
			pInstance->ReplaceISFieldsWithInstanceFields(pInstance->m_protoDecl->m_nodes[0], pInstance->m_node);
		}

		if (pDef)
		{
			pDef->m_node = node;
		}

		return node;
	}
}

/*
Stream& WriteToStream(Stream& stream, Lexer::Token token)
{
	switch (token)
	{
	case Lexer::TOKEN_EOF:
		stream << "EOF";
		break;

	case Lexer::TOKEN_INT:
		stream << "INT";
		break;

	case Lexer::TOKEN_FLOAT:
		stream << "FLOAT";
		break;

	case Lexer::TOKEN_ID:
		stream << "ID";
		break;

	case Lexer::TOKEN_STRING:
		stream << "STRING";
		break;

	case Lexer::TOKEN_SYMBOL:
		stream << "SYMBOL";
		break;
	}
	return stream;
}
*/

void VRMLLoader::fatalerror(StringIn msg)
{
	IO::StringWriter str;
	str << m_url << "(" << (m_line+1) << "," << (m_column+1) << ")" << " Error : " << msg;
	str << m_token;

	raise(Exception(str.str()));
}

IO::TextWriter& VRMLLoader::warning(int code)
{
	Console::get_Out() << m_url << "(" << (m_line+1) << "," << (m_column+1) << ")" << " Warning " << code << " : ";
	return Console::get_Out();
}

void VRMLLoader::warning(IO::TextWriter&)
{
	Console::get_Out() << endl;
}

int VRMLLoader::ParseWorld()
{
	//m_fpos = 0;
	m_line = 0;
	m_column = 0;

	adv();

//	try
	{
		char buf[5];
		read(buf, 4);

		bool bVRML = false;

		if (!strncmp(buf, ("#X3D"), 4))
		{
			bVRML = true;
		}
		else
		{
			read(&buf[4], 1);

			if (!strncmp(buf, ("#VRML"), 5))
			{
				bVRML = true;
			}
		}

		if (!bVRML)
		{
			fatalerror(WSTR("Not a VRML/X3D Classic encoded file"));
		}

	//	ASSERT(m_c == ' ');
		adv();
		//EatChar(' ');

		// get version
//		EatChar('V');
		//ASSERT(m_c == 'V');
		adv();
		long major = parsenumber();
		//EatChar('.');
		//ASSERT(m_c == '.');
		adv();
		long minor = parsenumber();

		WCHAR version[16];
		swprintf_s(version, L"%d.%d", major, minor);
		m_scene->m_version = string_copy(version);

		if (major < 2)
			fatalerror(WSTR("Unsupported version"));

		//EatChar(' ');

		lex();

	// get character encoding
		String encoding = peekidentifier();

		// skip spaces
		while (!eof())
		{
			int ch = peekc();
			if (ch != ' ' && ch != '\t') break;

			adv();
		}

		// optional comment
		IO::StringWriter comment;
		while (!eof())
		{
			int ch = peekc();
			if (ch == '\n' || ch == '\r') break;

			comment << (char)ch;
			adv();
		}
		m_scene->m_comment = comment;

		lex();

		while (!eof())
		{
			String ident = readidentifier();

			if (ident == L"PROFILE")
			{
				ProfileDeclaration* profile = nullptr;

				String name = readidentifier();
				if (name.Compare("Interchange") == 0)
				{
					profile = &ProfileDeclaration::Interchange;
				}
				else
					ASSERT(0);
				
				/*
				int c = m_c;//Getc();
				//unGetc();
				if (c == '"')
				{
					readstring();
				}
				else
				{
					readidentifier();
				}
				*/
			}
			else if (ident == L"COMPONENT")
			{
				String componentNameId = readidentifier();
				EatChar(L':');
				int componentSupportLevel = getnumber();
			}
			else if (ident == L"META")
			{
				String key = readstring();
				String value = readstring();

				m_scene->setMetadata(key,value);
			}
			else
			{
				X3DNode* node = ReadNode(ident, nullptr);
				if (node)
				{
					ASSERT(m_scene->m_root != nullptr);
					/*
					if (m_scene->m_root == nullptr)
					{
						m_scene->m_root = new Layer;
						m_scene->m_root->m_ownerLayer = m_scene->m_root;	// hm.. ??
						m_scene->m_root->m_scene = m_scene;
						// Create root group
						//NodeType* pGroupType = FindNodeType(WSTR("Group"));
					//	X3DNode* root = CreateNodeOfType(Group::GetNodeType());//->CreateNode();
					//	m_root = static_cast<Group*>(root);
					}
					*/

					m_scene->m_root->getChildrenField()->m_nLights += node->GetLights();
					node->m_ownerLayer = m_scene->m_root;	// ??
			//		m_scene->m_root->get_children()->m_nViewpoints += node->GetViewports();
					node->m_parents.Add(m_scene->m_root->getChildrenField());
					m_scene->m_root->getChildrenField()->m_items.Add(node);

	#if 0
					if (pSFNode->m_v)	// TODO
					{
						m_scene->m_timeDependantNodes.Add(pSFNode->m_v);
					}
	#endif
				}
			}
		}

		{
			for (uint i = 0; i < m_routes.size(); ++i)
			{
				try
				{
					X3DNode* sourceNode = m_scene->getNamedNode(m_routes[i]->m_sourceNodeNameId);
					if (sourceNode == nullptr)
					{
						WCHAR msg[512];
						ASSERT(0);
						//swprintf_s(msg, L"Use of undefined def %s in ROUTE", m_routes[i]->m_sourceNodeNameId->c_str());
						fatalerror(msg);
					}

					X3DNode* destinationNode = m_scene->getNamedNode(m_routes[i]->m_destinationNodeNameId);
					if (destinationNode == nullptr)
					{
						WCHAR msg[512];
						ASSERT(0);
						//swprintf_s(msg, L"Use of undefined def %s in ROUTE", m_routes[i]->m_destinationNodeNameId->c_str());
						fatalerror(msg);
					}

					m_scene->addRoute(sourceNode, m_routes[i]->m_sourceField, destinationNode, m_routes[i]->m_destinationField);
				}
				catch (InvalidNodeException* e)
				{
					Std::get_Out() << "Use of undefined DEF " << e->m_nodename << " in ROUTE";
				}
			}
		}

		m_scene->m_root->InitStacks();
	}

	return Success;
}

X3DScene* VRMLLoader::Load(StringIn url, IO::Stream* stream)
{
	m_stream = stream;

	X3DScene* pScene = new X3DScene;

	m_scene = pScene;
	m_scene->m_url = m_url;

	ParseWorld();

//	stream->Release();

	return pScene;
}

int VRMLLoader::ParseInto(X3DScene* scene, IO::Stream* stream)
{
	if (scene == nullptr)
	{
		raise(ArgumentNullException());
	}

	m_scene = scene;
	m_stream = stream;
	m_url = scene->getWorldURL();

	return ParseWorld();
}

X3DScene* VRMLLoader::Load(StringIn url)
{
	m_url = url;

	X3DScene* scene = nullptr;

	Net::UrlBinding urlb;
	_Ptr<Stream> fstream = urlb.BindToObject(url, nullptr);

	ubyte buffer[2];
	size_t nRead = fstream->Read(buffer, 2);
	if (nRead < 2)
	{
		return nullptr;
	}

	if (buffer[0] == 0x1f && buffer[1] == 0x8b)	// gzip
	{
		ubyte compression;
		fstream->Read(&compression, 1);
		if (compression != 8)	// Deflate
		{
			return nullptr;
		}

		ubyte flg;
		fstream->Read(&flg, 1);

		uint32 mtime;
		fstream->Read(&mtime, 4);

		ubyte xfl;
		ubyte os;

		fstream->Read(&xfl, 1);
		fstream->Read(&os, 1);

		IO::Inflate inflate(fstream, 8/*info, windowBits-7*/);

		scene = Load(url, &inflate);
	}
	else
	{
		m_nstacked = 2;
		m_buffer[0] = buffer[0];
		m_buffer[1] = buffer[1];

		scene = Load(url, fstream);
	}

	return scene;
}

}	// x3d
}	// System
