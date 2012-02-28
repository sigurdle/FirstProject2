#if 0
class CSVGLoader
{
protected:
	CComPtr<ISVGDocument> m_svgdoc;
	CComPtr<IPDDocument> m_pddoc;

	ICSSValue* GetCSSValue(ISVGElement* element, BSTR cssname);
	int GetPaint(ISVGElement* element, BSTR cssname, COLORREF& clr, CComPtr<ISVGElement>& urlElement);
	double GetStrokeWidth(ISVGElement* element);
	double GetOpacity(ISVGElement* element);
	double GetStrokeOpacity(ISVGElement* element);
	double GetFillOpacity(ISVGElement* element);

	void SetFrameFill(IPDObjectFrame* pdframe, ISVGElement* element);
	void SetFrameStroke(IPDObjectFrame* pdframe, ISVGElement* element);
	void SetTransform(IPDObject* pdobject, IDOMElement* element);

	void LoadLine(IPDObjectFrame* pdframe, ISVGLineElement* element);
	void LoadCircle(IPDObjectFrame* pdframe, ISVGCircleElement* element);
	void LoadEllipse(IPDObjectFrame* pdframe, ISVGEllipseElement* element);
	void LoadPath(IPDObjectFrame* pdframe, ISVGPathElement* element);
	BOOL LoadUse(IPDObjectSymbolInstance* instance, ISVGUseElement* element);
	void LoadGroup(IPDObjectGroup* pdgroup, IDOMElement* element);

public:
	HRESULT Load(IPDDocument* pddoc, BSTR pathName, IPDObjectGroup* *pVal);
};
#endif