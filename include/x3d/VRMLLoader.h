#ifndef x3d_VRMLLoader_h
#define x3d_VRMLLoader_h

namespace System
{
namespace x3d
{

class Lexer
{
public:

	enum Token
	{
		TOKEN_EOF = -1,
		TOKEN_INT,
		TOKEN_FLOAT,
		TOKEN_ID,
		TOKEN_STRING,
		TOKEN_SYMBOL,
	};

	struct lex_val
	{
		union
		{
			int intval;
			double floatval;
			char symbol;
		};

		String string;
	};

	CTOR Lexer();
	virtual ~Lexer();

	virtual void fatalerror(StringIn msg) abstract;

	int lex();

	void adv();
	int Getc();

	int peekc() const throw()
	{
		return m_c;
	}

	long parsenumber();

	Token m_token;
	lex_val m_val;

	_Ptr<IO::Stream> m_stream;
	char* m_buffer;
	uint m_fpos;
	int m_nstacked;

	uint m_line;
	uint m_column;

private:

	bool ceof() const throw()
	{
		return m_c == -1;
	}

	long _getnumber();
	double getfrac();
	int lookexp();

	int m_c;
};

//IO::TextWriter& WriteToStream(IO::TextWriter& stream, Lexer::Token token);

class X3DEXT VRMLLoader : public Object, public Lexer
{
public:
	CTOR VRMLLoader();
	~VRMLLoader();

	static const int X3DPARSER_BASE	= 2000;
	static const int X3DPARSER_UNKNOWNTYPE = X3DPARSER_BASE+1;

	class CRoute : public Object
	{
	public:
		CTOR CRoute()
		{
		}

		String m_sourceNodeNameId;
		String m_destinationNodeNameId;
		String m_sourceField;
		String m_destinationField;
	};

	X3DNode* ReadNode(StringIn ident, X3DLayerNode* ownerLayer);
	void ReadSF(X3DField* field);
	void ReadFieldValue(X3DField* field);

	bool ReadBool();
	int32 ReadInt32();
	float ReadFloat();
	double ReadDouble();
	double ReadTime();
	Vec3f ReadColor();
	Vec4f ReadColorRGBA();

	Vec2f ReadVec2f();
	Vec3f ReadVec3f();
	Vec4f ReadVec4f();

	Vec2d ReadVec2d();
	Vec3d ReadVec3d();
	Vec4d ReadVec4d();

	Rotation ReadRotation();
//	X3DNode* ReadNode();

	SAIProtoDeclaration* LoadExternProtoUrl(StringIn url);

	X3DScene* Load(StringIn url);
	X3DScene* Load(StringIn url, IO::Stream* stream);
	int ParseInto(X3DScene* scene, IO::Stream* stream);

protected:

	int ParseWorld();
	void EatChar(int c);
	void read(char* buffer, size_t count);

	String readidentifier();
	String peekidentifier();
	String readstring();
	long getnumber();
	double getfnumber();

	void ROUTEStatement();

	virtual void fatalerror(StringIn msg) override;
	IO::TextWriter& warning(int code);
	void warning(IO::TextWriter&);

	inline bool eof()
	{
		return m_token == TOKEN_EOF;
	}

	String m_url;
	X3DScene* m_scene;
	vector<CRoute*> m_routes;
};

}	// x3d
}	// System

#endif // VRMLLoader_h
