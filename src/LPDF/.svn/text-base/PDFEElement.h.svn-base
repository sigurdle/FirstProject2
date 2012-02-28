#pragma once

#include "PDFObject.h"

namespace System
{
namespace PDF
{

class CPDFEMatrix;
class CPDFEGraphicState;

class PDFExt CPDFEElement : public CPDFObject
{
public:
	CPDFEElement();
	~CPDFEElement();

	CPDFEMatrix* m_matrix;
	CPDFEGraphicState* m_gstate;

	virtual void WriteToStream(std::FILE* fp) = 0;

	virtual PDFEType GetType() const = 0;

public:

	void SetMatrix(CPDFEMatrix* matrix);
	void SetGState(CPDFEGraphicState* gstate);
	CPDFEGraphicState* GetGState();
};

#if 0
template <class IBase> class IPDFEElementImpl :
	public IPDFObjectImpl<IBase>,
	public CPDFEElement
{
public:
	STDMETHODIMP SetMatrix(IPDFEMatrix* matrix)
	{
		return CPDFEElement::SetMatrix(matrix);
	}
	STDMETHOD(SetGState)(/*[in]*/ IPDFEGraphicState* gstate)
	{
		return CPDFEElement::SetGState(gstate);
	}
	STDMETHOD(GetGState)(/*[in,out]*/ IPDFEGraphicState* *gstate)
	{
		return CPDFEElement::GetGState(gstate);
	}
};
#endif

}
}
