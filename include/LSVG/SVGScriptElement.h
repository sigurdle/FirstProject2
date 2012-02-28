#ifndef Web_SVGScriptElement_h
#define Web_SVGScriptElement_h

namespace System
{
namespace Web
{

class SVGEXT SVGScriptElement : 

	public SVGElement,
//	public SVGURIReferenceImpl<SVGScriptElement>,
//	public ElementEditASImpl<SVGScriptElement>,
	public ElementEditVALImpl<SVGScriptElement>

//	protected CNotifyGetImpl<SVGScriptElement>,
//	protected CNotifySendImpl<SVGScriptElement>
{
public:
	CTOR SVGScriptElement(NamedNodeMap* attributes);

	String get_type();
	void set_type(StringIn newVal);

	ecma::ScriptCode* m_pScript;

protected:

	virtual bool dispatchEvent2(Event* evt, bool bCapture);

	void ExecuteScript();
};

}	// Web
}

#endif // Web_SVGScriptElement_h
