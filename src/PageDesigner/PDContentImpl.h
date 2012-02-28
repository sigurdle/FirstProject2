#if 0
#pragma once

//class CPDObjectGroup;
class CPDObjectShape;

class ATL_NO_VTABLE CPDContent
{
public:
	virtual void Render(Gdiplus::Graphics* graphics);
	virtual void DistributeText(Gdiplus::Graphics* graphics, Gdiplus::Region* region) = 0;
};

template <class T> class ATL_NO_VTABLE CPDContentImpl :
	public CPDContent,
	public T
{
public:
	CPDContentImpl()
	{
		m_pDocument = NULL;
		m_frame = NULL;
	}

	GUID m_uniqID;
	CPDDocument* m_pDocument;

	CPDObjectShape* m_frame;

public:
};
#endif