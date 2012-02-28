#if 0
class CHTMPSpan : public CHTMPElement
{
public:
	CTOR CHTMPSpan()
	{
	}

	virtual void BuildTree(CHTMFrame* pFrame, ILDOMElement* pNode);
	virtual void Draw(CHTMRenderContext* pC);
	virtual void CalculateDimensions(CHTMCalcContext* pC);
};
#endif