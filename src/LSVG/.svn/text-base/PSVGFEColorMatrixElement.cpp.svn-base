#include "stdafx.h"
#include "LSVG2.h"

#include "PSVGFEColorMatrixElement.h"
#include "SVGFEColorMatrixElement.h"

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

namespace System
{
namespace Web
{

PSVGFEColorMatrixElement::PSVGFEColorMatrixElement(SVGFEColorMatrixElement* element) : PSVGFEElement(element)
{
}

//virtual
int PSVGFEColorMatrixElement::GetInCount()
{
	return 1;
}

//virtual
Gui::CEffect* PSVGFEColorMatrixElement::Filter(Gui::RenderContext* renderContext, Gui::CEffect* inEffect[], PSVGFilterElement* pFilterElement, const gm::RectF& uRect, double scaleX, double scaleY)
{
	SVGColorMatrixEffect* pEffect = new SVGColorMatrixEffect;

	pEffect->m_inEffect = inEffect[0];

//	pEffect->m_technique = pO->m_res->m_d3d9_effect->GetTechniqueByName("RenderFilterColorMatrix");
//	ASSERT(pEffect->m_technique);

//	LDraw::ColorMatrixF& cm = pEffect->m_colorMatrix;

	gm::matrix4f cx = pEffect->m_colorTransform;
	gm::vector4f ct = pEffect->m_colorTranslate;
	{
		double s = 0;
		/*
		if (values->m_items.GetSize() == 1)
		{
			s = values->m_items[0]->m_value;

			if (s < 0) s = 0;
			else if (s > 1) s = 1;
		}
		else
		{
			s = 1;
		}
		*/

		cx[0][0] = 0.213+0.787*s;	cx[0][1] = 0.715-0.715*s;	cx[0][2] = 0.072-0.072*s;	cx[0][3] = 0;
		cx[1][0] = 0.213-0.213*s;	cx[1][1] = 0.715+0.285*s;	cx[1][2] = 0.072-0.072*s;	cx[1][3] = 0;
		cx[2][0] = 0.213-0.213*s;	cx[2][1] = 0.715-0.715*s;	cx[2][2] = 0.072+0.928*s;	cx[2][3] = 0;
		cx[3][0] = 0;					cx[3][1] = 0;					cx[3][2] = 0;					cx[3][3] = 1;
		ct[0] = 0;					ct[1] = 0;					ct[2] = 0;					ct[3] = 0;
/*
		cm.m[0][0] = 0.213+0.787*s;	cm.m[1][0] = 0.715-0.715*s;	cm.m[2][0] = 0.072-0.072*s;	cm.m[3][0] = 0;	cm.m[4][0] = 0;
		cm.m[0][1] = 0.213-0.213*s;	cm.m[1][1] = 0.715+0.285*s;	cm.m[2][1] = 0.072-0.072*s;	cm.m[3][1] = 0;	cm.m[4][1] = 0;
		cm.m[0][2] = 0.213-0.213*s;	cm.m[1][2] = 0.715-0.715*s;	cm.m[2][2] = 0.072+0.928*s;	cm.m[3][2] = 0;	cm.m[4][2] = 0;
		cm.m[0][3] = 0;					cm.m[1][3] = 0;					cm.m[2][3] = 0;					cm.m[3][3] = 1;	cm.m[4][3] = 0;
		cm.m[0][4] = 0;					cm.m[1][4] = 0;					cm.m[2][4] = 0;					cm.m[3][4] = 0;	cm.m[4][4] = 1;
*/
		/*
		cm.m[0][0] = 1;	cm.m[1][0] = 0;	cm.m[2][0] = 0;	cm.m[3][0] = 0;	cm.m[4][0] = 0;
		cm.m[0][1] = 0;	cm.m[1][1] = 1;	cm.m[2][1] = 0;	cm.m[3][1] = 0;	cm.m[4][1] = 0;
		cm.m[0][2] = 0;	cm.m[1][2] = 0;	cm.m[2][2] = 1;	cm.m[3][2] = 0;	cm.m[4][2] = 0;
		cm.m[0][3] = 0;	cm.m[1][3] = 0;	cm.m[2][3] = 0;	cm.m[3][3] = 1;	cm.m[4][3] = 0;
		cm.m[0][4] = 0;	cm.m[1][4] = 0;	cm.m[2][4] = 0;	cm.m[3][4] = 0;	cm.m[4][4] = 1;
		*/
	}

	return pEffect;

#if 0
	CLSVGFEColorMatrixElement* psvgElement = static_cast<CLSVGFEColorMatrixElement*>(m_pNode);

	LSVGColorMatrixType type = psvgElement->m_type->m_animated->m_animVal->m_value.m_value;
	CComObject<CLSVGNumberList>* values = psvgElement->m_values->m_animated->m_animVal->m_value.m_object;
	ASSERT(values);

	LDraw::ColorMatrix cm;

	if (type == SVG_FECOLORMATRIX_TYPE_MATRIX)
	{
/*
	For type="matrix", values is a list of 20 matrix values (a00 a01 a02 a03 a04 a10 a11 ... a34), separated by whitespace and/or a comma. For example, the identity matrix could be expressed as: 
	type="matrix" 
	values="1 0 0 0 0  0 1 0 0 0  0 0 1 0 0  0 0 0 1 0"
*/

		if (values->m_items.GetSize() == 20)
		{
			cm.m[0][0] = values->m_items[0]->m_value;
			cm.m[1][0] = values->m_items[1]->m_value;
			cm.m[2][0] = values->m_items[2]->m_value;
			cm.m[3][0] = values->m_items[3]->m_value;
			cm.m[4][0] = values->m_items[4]->m_value;

			cm.m[0][1] = values->m_items[5]->m_value;
			cm.m[1][1] = values->m_items[6]->m_value;
			cm.m[2][1] = values->m_items[7]->m_value;
			cm.m[3][1] = values->m_items[8]->m_value;
			cm.m[4][1] = values->m_items[9]->m_value;

			cm.m[0][2] = values->m_items[10]->m_value;
			cm.m[1][2] = values->m_items[11]->m_value;
			cm.m[2][2] = values->m_items[12]->m_value;
			cm.m[3][2] = values->m_items[13]->m_value;
			cm.m[4][2] = values->m_items[14]->m_value;

			cm.m[0][3] = values->m_items[15]->m_value;
			cm.m[1][3] = values->m_items[16]->m_value;
			cm.m[2][3] = values->m_items[17]->m_value;
			cm.m[3][3] = values->m_items[18]->m_value;
			cm.m[4][3] = values->m_items[19]->m_value;

			cm.m[0][4] = 0;
			cm.m[1][4] = 0;
			cm.m[2][4] = 0;
			cm.m[3][4] = 0;
			cm.m[4][4] = 1;
		}
		else
		{
		// identity
			cm.m[0][0] = 1;	cm.m[1][0] = 0;	cm.m[2][0] = 0;	cm.m[3][0] = 0;	cm.m[4][0] = 0;
			cm.m[0][1] = 0;	cm.m[1][1] = 1;	cm.m[2][1] = 0;	cm.m[3][1] = 0;	cm.m[4][1] = 0;
			cm.m[0][2] = 0;	cm.m[1][2] = 0;	cm.m[2][2] = 1;	cm.m[3][2] = 0;	cm.m[4][2] = 0;
			cm.m[0][3] = 0;	cm.m[1][3] = 0;	cm.m[2][3] = 0;	cm.m[3][3] = 1;	cm.m[4][3] = 0;
			cm.m[0][4] = 0;	cm.m[1][4] = 0;	cm.m[2][4] = 0;	cm.m[3][4] = 0;	cm.m[4][4] = 1;
		}
	}
	else if (type == SVG_FECOLORMATRIX_TYPE_SATURATE)
	{
/*
	For type="saturate", values is a single real number value (0 to 1). A saturate operation is equivalent to the following matrix operation: 
	| R' |     |0.213+0.787s  0.715-0.715s  0.072-0.072s 0  0 |   | R |

	| G' |     |0.213-0.213s  0.715+0.285s  0.072-0.072s 0  0 |   | G |

	| B' |  =  |0.213-0.213s  0.715-0.715s  0.072+0.928s 0  0 | * | B |

	| A' |     |           0            0             0  1  0 |   | A |

	| 1  |     |           0            0             0  0  1 |   | 1 |
*/

		double s;
		if (values->m_items.GetSize() == 1)
		{
			s = values->m_items[0]->m_value;

			if (s < 0) s = 0;
			else if (s > 1) s = 1;
		}
		else
		{
			s = 1;
		}

		cm.m[0][0] = 0.213+0.787*s;	cm.m[1][0] = 0.715-0.715*s;	cm.m[2][0] = 0.072-0.072*s;	cm.m[3][0] = 0;	cm.m[4][0] = 0;
		cm.m[0][1] = 0.213-0.213*s;	cm.m[1][1] = 0.715+0.285*s;	cm.m[2][1] = 0.072-0.072*s;	cm.m[3][1] = 0;	cm.m[4][1] = 0;
		cm.m[0][2] = 0.213-0.213*s;	cm.m[1][2] = 0.715-0.715*s;	cm.m[2][2] = 0.072+0.928*s;	cm.m[3][2] = 0;	cm.m[4][2] = 0;
		cm.m[0][3] = 0;					cm.m[1][3] = 0;					cm.m[2][3] = 0;					cm.m[3][3] = 1;	cm.m[4][3] = 0;
		cm.m[0][4] = 0;					cm.m[1][4] = 0;					cm.m[2][4] = 0;					cm.m[3][4] = 0;	cm.m[4][4] = 1;
	}
	else if (type == SVG_FECOLORMATRIX_TYPE_HUEROTATE)
	{
		double value;
		if (values->m_items.GetSize() == 1)
		{
			value = values->m_items[0]->m_value;
		}
		else
		{
			value = 0;
		}
/*
For type="hueRotate", values is a single one real number value (degrees). A hueRotate operation is equivalent to the following matrix operation: 
| R' |     | a00  a01  a02  0  0 |   | R |

| G' |     | a10  a11  a12  0  0 |   | G |

| B' |  =  | a20  a21  a22  0  0 | * | B |

| A' |     | 0    0    0    1  0 |   | A |

| 1  |     | 0    0    0    0  1 |   | 1 |

where the terms a00, a01, etc. are calculated as follows: 
| a00 a01 a02 |    [+0.213 +0.715 +0.072]
| a10 a11 a12 | =  [+0.213 +0.715 +0.072] +
| a20 a21 a22 |    [+0.213 +0.715 +0.072]

                        [+0.787 -0.715 -0.072]
cos(hueRotate value) *  [-0.213 +0.285 -0.072] +
                        [-0.213 -0.715 +0.928]

                        [-0.213 -0.715+0.928]
sin(hueRotate value) *  [+0.143 +0.140-0.283]
                        [-0.787 +0.715+0.072]

Thus, the upper left term of the hue matrix turns out to be: 
.213 + cos(hueRotate value)*.787 - sin(hueRotate value)*.213
*/

		gmMatrix3 a =

											gmMatrix3(	+0.213, +0.715, +0.072,
												+0.213, +0.715, +0.072,
												+0.213, +0.715, +0.072) +

			cos(gmRadians(value)) * gmMatrix3(	+0.787, -0.715, -0.072,
												-0.213, +0.285, -0.072,
												-0.213, -0.715, +0.928) +

			sin(gmRadians(value)) *	gmMatrix3(	-0.213, -0.715,+0.928,
												+0.143, +0.140,-0.283,
												-0.787, +0.715, +0.072);

		cm.m[0][0] = a[0][0];	cm.m[1][0] = a[0][1];	cm.m[2][0] = a[0][2];	cm.m[3][0] = 0;	cm.m[4][0] = 0;
		cm.m[0][1] = a[1][0];	cm.m[1][1] = a[1][1];	cm.m[2][1] = a[1][2];	cm.m[3][1] = 0;	cm.m[4][1] = 0;
		cm.m[0][2] = a[2][0];	cm.m[1][2] = a[2][1];	cm.m[2][2] = a[2][2];	cm.m[3][2] = 0;	cm.m[4][2] = 0;
		cm.m[0][3] = 0;			cm.m[1][3] = 0;			cm.m[2][3] = 0;			cm.m[3][3] = 1;	cm.m[4][3] = 0;
		cm.m[0][4] = 0;			cm.m[1][4] = 0;			cm.m[2][4] = 0;			cm.m[3][4] = 0;	cm.m[4][4] = 1;
	}
	else if (type == SVG_FECOLORMATRIX_TYPE_LUMINANCETOALPHA)
	{
/*
For type="luminanceToAlpha", values is not applicable. A luminanceToAlpha operation is equivalent to the following matrix operation: 
   | R' |     |      0        0        0  0  0 |   | R |

   | G' |     |      0        0        0  0  0 |   | G |

   | B' |  =  |      0        0        0  0  0 | * | B |

   | A' |     | 0.2125   0.7154   0.0721  0  0 |   | A |

   | 1  |     |      0        0        0  0  1 |   | 1 |
*/

		cm.m[0][0] = 0;		cm.m[1][0] = 0;		cm.m[2][0] = 0;		cm.m[3][0] = 0;	cm.m[4][0] = 0;
		cm.m[0][1] = 0;		cm.m[1][1] = 0;		cm.m[2][1] = 0;		cm.m[3][1] = 0;	cm.m[4][1] = 0;
		cm.m[0][2] = 0;		cm.m[1][2] = 0;		cm.m[2][2] = 0;		cm.m[3][2] = 0;	cm.m[4][2] = 0;
		cm.m[0][3] = 0.2125;	cm.m[1][3] = 0.7154;	cm.m[2][3] = 0.0721;	cm.m[3][3] = 0;	cm.m[4][3] = 0;
		cm.m[0][4] = 0;		cm.m[1][4] = 0;		cm.m[2][4] = 0;		cm.m[3][4] = 0;	cm.m[4][4] = 1;
	}
	else
		ASSERT(0);

	LDraw::ImageAttributes imgAttributes;
	imgAttributes.SetColorMatrix(&cm, LDraw::ColorMatrixFlagsDefault, LDraw::ColorAdjustTypeDefault);

	LDraw::Graphics out(outImage);

	out.SetCompositingMode(LDraw::CompositingModeSourceCopy);

	out.DrawImage(inImage[0]->m_outImage,
			uRect,//LDraw::RectF(0, 0, outImage->GetWidth(), outImage->GetHeight()), // destination rect
			uRect.X, uRect.Y, uRect.Width, uRect.Height,//inImage[0]->m_outImage->GetWidth(), inImage[0]->m_outImage->GetHeight(),
			LDraw::UnitPixel,
			&imgAttributes
			);

	/*
	LDraw::Bitmap* inImage = inPinImage[0];

	double dx = psvgElement->m_dx->m_animated->m_animVal->m_value;
	double dy = psvgElement->m_dy->m_animated->m_animVal->m_value;

	LDraw::Graphics out(outImage);

	out.DrawImage(inImage, (float)dx, (float)dy);
	*/
#endif
	return 0;
}

}	// w3c
}
