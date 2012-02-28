#ifndef ActionScriptFunction_h
#define ActionScriptFunction_h

namespace System
{
namespace ActionScripting
{

class ActionScript2Ext ActionScriptFunction : public Function
{
public:

	CTOR ActionScriptFunction();
//	CTOR ActionScriptFunction(ecma::Script* script);

	virtual size_t get_NumArgs() override;
	virtual String ToString() override;
	virtual void dispatch(VM* vm, StackFrame* ctx, uint numargs) override;

	String m_name;
	String m_codeAsText;
	uint8* m_codeData;
	ULONG m_codeLength;
	ActionContext* m_pContext;
	vector<String> m_args;
};

ActionScript2Ext void Disasm(ActionScriptFunction* function);

}	// ActionScripting
}

#endif // ActionScriptFunction_h
