namespace System
{
namespace Expressive
{

interface IParserExtension
{
	virtual void OnExp(Expression* parent, AExpression* field) = 0;
};

class GUIEXT FrameContext : public Object, public IFrameContext
{
public:

	virtual Variant GetVariable(StringIn name) override
	{
		map<String, Variant>::iterator it = m_variables.find(name);
		if (it != m_variables.end())
			return it->second;
		else
			return Variant();
	}

	map<String, Variant> m_variables;
};

class GUIEXT Translator : public Object
{
public:

	CTOR Translator(IParserExtension* extension) : m_extension(extension), m_nerrors(0)
	{
	}

	Expression* TranslateExpression(AExpression* exp, IFrameContext* frame);
	Expression* TranslateExpression(AExpression* exp, ClassType* thisType, IFrameContext* frame, map<String, Expression*>& defs, StringIn defname = nullptr);

	Expression* TranslateDList(ADeclarationList* dlist, IFrameContext* frame);

	static Expression* Translate(ADeclarationList* dlist, IFrameContext* frame = NULL, IParserExtension* ext = nullptr);
	static Expression* Translate(AExpression* exp, IFrameContext* frame = NULL, IParserExtension* ext = nullptr);

	static Object* FromFile(StringIn filename);

	_Ptr<IO::TextWriter> smsg();
	void Error(IO::TextWriter& stream);

	IParserExtension* m_extension;
	uint m_nerrors;
};

}	// Gui
}	// System
