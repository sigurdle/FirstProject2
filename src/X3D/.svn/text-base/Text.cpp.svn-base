#include "stdafx.h"
#include "X3D2.h"
#include "Text.h"

namespace System
{
namespace x3d
{

X3DFieldDefinition* TextFields[] =
{
	&X3DFieldDefinition("fontStyle", FieldType_SFNode, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("length", FieldType_MFFloat, SAIFieldAccess_inputOutput,-1),
	&X3DFieldDefinition("string", FieldType_MFString, SAIFieldAccess_inputOutput,-1),
	/*
	SFNode   [in,out] fontStyle NULL  [X3FontSyleNode]
	MFFloat  [in,out] length    []    [0,8)
	SFFloat  [in,out] maxExtent 0.0   [0,8)
	SFNode   [in,out] metadata  NULL  [X3DMetadataObject]
	MFString [in,out] string    []
	SFBool   []       solid     FALSE
	*/
};

NodeType Text::s_nodeType(WSTR("Text"), typeid(Text), TextFields, _countof(TextFields));

Text::Text() : X3DGeometryNode(&s_nodeType)
{
	/*
// Cache pointers to relevant fields
	m_fontStyle = static_cast<SFNode*>(getField(WSTR("fontStyle")));
	m_string = static_cast<MFString*>(getField(WSTR("string")));
*/

// Set defaults
}

Text::~Text()
{
}

// virtual
void Text::Draw(X3DDrawContext* pDC, X3DTextureNodeImplImpl* pTextureNode)
{
	MessageBeep(-1);
	//ASSERT(0);
#if 0

	HDC hDC = CreateCompatibleDC(NULL);


	CLFontStyle* fontStyle = static_cast<CLFontStyle*>(m_fontStyle->m_value);
	if (fontStyle)
	{
		HFONT hFont;
		LOGFONT lf = {0};
	//	lf.lfWeight = -2048;	// Truetype em
		lf.lfWeight = -20;	// Truetype em

		if (fontStyle->m_family->m_items.GetSize() > 0)
			strcpy(lf.lfFaceName, fontStyle->m_family->m_items[0]);
		else
			strcpy(lf.lfFaceName, "Arial");

		hFont = CreateFontIndirect(&lf);
		if (hFont)
		{
			HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);

			for (int i = 0; i < m_string->m_items.GetSize(); i++)
			{
				for (int j = 0; j < m_string->m_items[i].length(); j++)
				{
					int gllist = glGenLists(1);

					GLYPHMETRICSFLOAT agmf;

					wglUseFontOutlines(hDC, 
						__toascii((m_string->m_items[i].c_str())[j]),    // Character to generate
						1,                 // Number of characters
						gllist,              // Display-list number
						0.0,               // Deviation
						0.0,               // Extrusion
						WGL_FONT_POLYGONS, // Format
						&agmf);           // Metrics pointer

					glCallList(gllist);

					glDeleteLists(gllist, 1);
				}
			}

			SelectObject(hDC, hOldFont);
			DeleteObject(hFont);
		}
	}
	DeleteDC(hDC);
#endif
}

}	// x3d
}
