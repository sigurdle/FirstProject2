#pragma once

#include "PElement.h"

class CPMathMLElementImpl : public CPElement
{
public:
	CPMathMLElementImpl()
	{
	}

	~CPMathMLElementImpl()
	{
	}

	virtual void BuildChildren();
};

class CPMathMLElement :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CPMathMLElementImpl
{
public:
	CPMathMLElement()
	{
	}

BEGIN_COM_MAP(CPMathMLElement)
	COM_INTERFACE_ENTRY(ILViewNode)
END_COM_MAP()
};
