#if 0
class CSVGExport
{
protected:
	CComPtr<ISVGDocument> m_svgdoc;
	CComPtr<ISVGSVGElement> m_svgsvgelement;
	long m_nUriRefs;

	void SaveFilter(IPDAppearance* pdfilter, ISVGFilterElement* filterElement);
	void SaveObjectFilter(IPDObject* pdobject, ISVGFilterElement* *pfilterElement);
	void SetFilterURI(ISVGElement *element, ISVGFilterElement* filterElement);
	void SaveTransform(IPDObject* pdObject, ISVGElement* svgElement);

	void SavePath(IPDPath* pdpath, ISVGPathElement* pathElement, ISVGPathSegList* seglist);
	void SaveObjectFrame(ISVGElement* group, IPDObjectFrame* pdframe);
	void SaveObjectGroup(ISVGElement* group, IPDObjectGroup* pdgroup);

public:
	CSVGExport()
	{
		m_nUriRefs = 0;
	}

	HRESULT Export(BSTR pathName, IPDSpread* spread);
};
#endif