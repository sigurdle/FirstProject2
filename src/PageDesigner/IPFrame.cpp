#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"
#include "IPFrame.h"

int CALLBACK FontFamExProc(
  ENUMLOGFONTEX *lpelfe,    // pointer to logical-font data
  NEWTEXTMETRICEX *lpntme,  // pointer to physical-font data
  int FontType,             // type of font
  LPARAM lParam);             // application-defined data


int CIPFrame::FinalConstruct()
{
	CComQIPtr<IUIManager> uiManager = this;

// Commands
	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Window and Help", &group);

		AddCommandID(ID_WINDOW_NEW, L"New Window", group, NULL);
		AddCommandID(ID_APP_ABOUT, L"About PageDesigner...", group, NULL);
		//m_AddCommandID(ID_HELP_TOPICS, L"Help Topics...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"File", &group);

		AddCommandID(ID_FILE_NEW, L"New", group, NULL);
		AddCommandID(ID_FILE_OPEN, L"Open...", group, NULL);
		AddCommandID(ID_FILE_SAVE, L"Save", group, NULL);
		AddCommandID(ID_FILE_SAVE_AS, L"Save as...", group, NULL);

		AddCommandID(ID_FILE_PLACE, L"Place...", group, NULL);
		AddCommandID(ID_FILE_DOCUMENTSETUP, L"Document Setup...", group, NULL);

		AddCommandID(ID_FILE_EXPORT_SVG, L"SVG...", group, NULL);
		AddCommandID(ID_FILE_EXPORT_PDF, L"PDF...", group, NULL);

		AddCommandID(ID_FILE_CUSTOMIZE, L"Customize...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Layers", &group);

		AddCommandID(ID_LAYERS_NEWLAYER, L"New Layer...", group, NULL);
		AddCommandID(ID_LAYERS_LAYEROPTIONS, L"Layer Options...", group, NULL);
		AddCommandID(ID_LAYERS_DELETE, L"Delete Layer(s)", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Links", &group);

		AddCommandID(ID_LINKS_PALETTEOPTIONS, L"Palette Options...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Pages", &group);

		AddCommandID(ID_PAGES_INSERTPAGES, L"Insert Pages...", group, NULL);
		AddCommandID(ID_PAGES_NEWMASTER, L"New Master...", group, NULL);

		AddCommandID(ID_PAGES_SECTIONOPTIONS, L"Section Options...", group, NULL);

		AddCommandID(ID_PAGES_KEEPSPREADTOGETHER, L"Keep Spread Together", group, NULL);
		AddCommandID(ID_PAGES_ALLOWPAGESTOSHUFFLE, L"Allow Pages to Shuffle", group, NULL);
		AddCommandID(ID_PAGES_PALETTEOPTIONS, L"Palette Options...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Swatches", &group);

		AddCommandID(ID_SWATCHES_NEWCOLORSWATCH, L"New Color Swatch...", group, NULL);
		AddCommandID(ID_SWATCHES_NEWGRADIENTSWATCH, L"New Gradient Swatch...", group, NULL);
		AddCommandID(ID_SWATCHES_NEWTINTSWATCH, L"New Tint Swatch...", group, NULL);
		AddCommandID(ID_SWATCHES_DELETESWATCH, L"Delete Swatch", group, NULL);
		AddCommandID(ID_SWATCHES_SWATCHOPTIONS, L"Swatch Options...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Transparency", &group);

		AddCommandID(ID_TRANSPARENCY_MAKEOPACITYMASK, L"Make Opacity Mask", group, NULL);
		AddCommandID(ID_TRANSPARENCY_RELEASEOPACITYMASK, L"Release Opacity Mask", group, NULL);
		AddCommandID(ID_TRANSPARENCY_ENABLEOPACITYMASK, L"Enable Opacity Mask", group, NULL);
		AddCommandID(ID_TRANSPARENCY_LINKOPACITYMASK, L"Link Opacity Mask", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Symbols", &group);

		AddCommandID(ID_SYMBOLS_NEWSYMBOL, L"New Symbol...", group, NULL);
		AddCommandID(ID_SYMBOLS_REDEFINESYMBOL, L"Redefine Symbol", group, NULL);
		AddCommandID(ID_SYMBOLS_PLACESYMBOLINSTANCE, L"Place Symbol Instance", group, NULL);
		AddCommandID(ID_SYMBOLS_BREAKLINKTOSYMBOL, L"Break Link to Symbol", group, NULL);
		AddCommandID(ID_SYMBOLS_SYMBOLOPTIONS, L"Symbol Options...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Symbols", &group);

		AddCommandID(ID_COLOR_GRAYSCALE, L"Grayscale", group, NULL);
		AddCommandID(ID_COLOR_RGB, L"RGB", group, NULL);
		AddCommandID(ID_COLOR_HSB, L"HSB", group, NULL);
		AddCommandID(ID_COLOR_ADDTOSWATCHES, L"Add to Swatches", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Tool", &group);

		AddCommandID(ID_TOOL_SELECT, L"Select", group, NULL);
		AddCommandID(ID_TOOL_DIRECT, L"Direct", group, NULL);
		AddCommandID(ID_TOOL_TEXT, L"Text", group, NULL);
		AddCommandID(ID_TOOL_TEXTPATH, L"Text Path", group, NULL);
		AddCommandID(ID_TOOL_RECTANGLE, L"Rectangle", group, NULL);
		AddCommandID(ID_TOOL_RECTANGLEGRAPHIC, L"Rectangle Graphic", group, NULL);
		AddCommandID(ID_TOOL_ELLIPSE, L"Ellipse", group, NULL);
		AddCommandID(ID_TOOL_ELLIPSEGRAPHIC, L"Ellipse Graphic", group, NULL);
		AddCommandID(ID_TOOL_LINE, L"Line", group, NULL);
		AddCommandID(ID_TOOL_PATHPEN, L"Path Pen", group, NULL);
		AddCommandID(ID_TOOL_PATHADDANCHOR, L"Path Add Anchor", group, NULL);
		AddCommandID(ID_TOOL_PATHDELETEANCHOR, L"Path Delete Anchor", group, NULL);
		AddCommandID(ID_TOOL_PATHCORNER, L"Path Corner", group, NULL);
		AddCommandID(ID_TOOL_SCALE, L"Scale", group, NULL);
		AddCommandID(ID_TOOL_ROTATE, L"Rotate", group, NULL);
		AddCommandID(ID_TOOL_FREETRANSFORM, L"Free Transform", group, NULL);
		AddCommandID(ID_TOOL_SYMBOLSPRAYER, L"Symbol Sprayer", group, NULL);
		AddCommandID(ID_TOOL_TWIRL, L"Twirl", group, NULL);
		AddCommandID(ID_TOOL_BULGE, L"Bulge", group, NULL);
		AddCommandID(ID_TOOL_GRADIENT, L"Gradient", group, NULL);
		AddCommandID(ID_TOOL_ZOOM, L"Zoom", group, NULL);
		AddCommandID(ID_TOOL_HAND, L"Hand", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComPtr<ICommandGroup> group;
		CreateCommandGroup(L"Layout", &group);

		AddCommandID(ID_LAYOUT_MARGINSANDCOLUMNS, L"Margins and Columns...", group, NULL);
		AddCommandID(ID_LAYOUT_CREATEGUIDES, L"Create Guides...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComPtr<ICommandGroup> group;
		CreateCommandGroup(L"Text Formatting", &group);

		{
			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_TYPE_FONTFACE, L"Font Face", group, &cmd);
				cmd->put_windowClassname(L"ComboBox");
				cmd->put_windowStyle(CBS_AUTOHSCROLL | CBS_DROPDOWN | CBS_SORT | WS_VSCROLL);
				cmd->put_itemWidth(160);

				HDC	hDC = ::GetDC(NULL);
				LOGFONT	lf = {0};
				lf.lfCharSet = DEFAULT_CHARSET;
				
				int result = EnumFontFamiliesEx(
					hDC,					// handle to device context
					&lf,					// pointer to logical font information
					(FONTENUMPROC)FontFamExProc,    // pointer to callback function
					(LPARAM)cmd.p,						// application-supplied data
					0);					// reserved; must be zero

				::ReleaseDC(NULL, hDC);
			}

			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_CHARACTER_FONTSIZE, L"Font Size", group, &cmd);
				cmd->put_windowClassname(L"ComboBox");
				cmd->put_windowStyle(CBS_AUTOHSCROLL | CBS_DROPDOWN | WS_VSCROLL);
				cmd->put_itemWidth(62);
				cmd->AddString(L"4 pt");
				cmd->AddString(L"6 pt");
				cmd->AddString(L"7 pt");
				cmd->AddString(L"8 pt");
				cmd->AddString(L"9 pt");
				cmd->AddString(L"12 pt");
				cmd->AddString(L"14 pt");
				cmd->AddString(L"18 pt");
				cmd->AddString(L"20 pt");
			}

			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_CHARACTER_LINEHEIGHT, L"Line Height", group, &cmd);
				cmd->put_windowClassname(L"ComboBox");
				cmd->put_windowStyle(CBS_AUTOHSCROLL | CBS_DROPDOWN | WS_VSCROLL);
				cmd->put_itemWidth(62);
				cmd->AddString(L"Auto");
				cmd->AddString(L"6 pt");
				cmd->AddString(L"7 pt");
				cmd->AddString(L"8 pt");
				cmd->AddString(L"9 pt");
				cmd->AddString(L"10 pt");
				cmd->AddString(L"11 pt");
				cmd->AddString(L"12 pt");
				cmd->AddString(L"14 pt");
				cmd->AddString(L"18 pt");
				cmd->AddString(L"21 pt");
				cmd->AddString(L"24 pt");
				cmd->AddString(L"36 pt");
				cmd->AddString(L"48 pt");
				cmd->AddString(L"60 pt");
				cmd->AddString(L"72 pt");
			}
		}

		AddCommandID(ID_CHARACTER_BOLD, L"Bold", group, NULL);
		AddCommandID(ID_CHARACTER_ITALIC, L"Italic", group, NULL);
		AddCommandID(ID_CHARACTER_UNDERLINE, L"Underline", group, NULL);

		AddCommandID(ID_TYPE_CREATEOUTLINES, L"Create Outlines", group, NULL);
		AddCommandID(ID_TYPE_CHARACTER, L"Character...", group, NULL);
		AddCommandID(ID_TYPE_PARAGRAPH, L"Paragraph...", group, NULL);

		AddCommandID(ID_TYPE_SHOWHIDDENCHARACTERS, L"Show Hidden Characters", group, NULL);

		AddCommandID(ID_PARAGRAPH_ALIGNLEFT, L"Align Left", group, NULL);
		AddCommandID(ID_PARAGRAPH_ALIGNCENTER, L"Align Center", group, NULL);
		AddCommandID(ID_PARAGRAPH_ALIGNRIGHT, L"Align Right", group, NULL);
		AddCommandID(ID_PARAGRAPH_JUSTIFYLEFT, L"Justify Left", group, NULL);
		AddCommandID(ID_PARAGRAPH_JUSTIFYCENTER, L"Justify Center", group, NULL);
		AddCommandID(ID_PARAGRAPH_JUSTIFYRIGHT, L"Justify Right", group, NULL);
		AddCommandID(ID_PARAGRAPH_JUSTIFYALL, L"Justify All", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComPtr<ICommandGroup> group;
		CreateCommandGroup(L"Edit", &group);

		AddCommandID(ID_EDIT_UNDO, L"Undo", group, NULL);
		AddCommandID(ID_EDIT_REDO, L"Redo", group, NULL);
		AddCommandID(ID_EDIT_CUT, L"Cut", group, NULL);
		AddCommandID(ID_EDIT_COPY, L"Copy", group, NULL);
		AddCommandID(ID_EDIT_PASTE, L"Paste", group, NULL);
		AddCommandID(ID_EDIT_PASTEINTO, L"Paste Into", group, NULL);
		AddCommandID(ID_EDIT_CLEAR, L"Clear", group, NULL);
//		m_AddCommandID(ID_EDIT_EMPTYCLIPBOARD, L"Empty Clipboard", group, NULL);

		AddCommandID(ID_EDIT_DEFINEPATTERN, L"Define Pattern...", group, NULL);

		AddCommandID(ID_EDIT_DOCUMENTCOLORSETTINGS, L"Document Color Settings...", group, NULL);
		AddCommandID(ID_EDIT_PREFERENCES, L"Preferences...", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"View", &group);

		AddCommandID(ID_VIEW_ZOOMIN, L"Zoom In", group, NULL);
		AddCommandID(ID_VIEW_ZOOMOUT, L"Zoom Out", group, NULL);
		AddCommandID(ID_VIEW_ACTUALSIZE, L"Actual Size", group, NULL);

		AddCommandID(ID_VIEW_RULERS, L"Rulers", group, NULL);
		AddCommandID(ID_VIEW_TRANSPARENCYGRID, L"Transparency Grid", group, NULL);
		AddCommandID(ID_VIEW_BASELINEGRID, L"Baseline Grid", group, NULL);
		AddCommandID(ID_VIEW_DOCUMENTGRID, L"Document Grid", group, NULL);

		AppendCommandGroup(group);
	}

	{
		CComQIPtr<ICommandGroup> group;
		CreateCommandGroup(L"Object", &group);

		AddCommandID(ID_OBJECT_GROUP, L"Group", group, NULL);
		AddCommandID(ID_OBJECT_UNGROUP, L"Ungroup", group, NULL);
		AddCommandID(ID_OBJECT_LOCKPOSITION, L"Lock Position", group, NULL);
		AddCommandID(ID_OBJECT_UNLOCKPOSITION, L"Unlock Position", group, NULL);

		AddCommandID(ID_OBJECT_TEXTFRAMEOPTIONS, L"Text Frame Options...", group, NULL);

		AddCommandID(ID_OBJECT_FITTING_FITCONTENTTOFRAME, L"Fit Content to Frame", group, NULL);
		AddCommandID(ID_OBJECT_FITTING_FITFRAMETOCONTENT, L"Fit Frame to Content", group, NULL);
		AddCommandID(ID_OBJECT_FITTING_CENTERCONTENT, L"Center Content", group, NULL);
		AddCommandID(ID_OBJECT_FITTING_FITCONTENTPROPORTIONALLY, L"Fit Content Proportionally", group, NULL);

		AddCommandID(ID_OBJECT_PATHTYPE_OPTIONS, L"Options...", group, NULL);
		AddCommandID(ID_OBJECT_PATHTYPE_DELETE, L"Delete", group, NULL);

		AddCommandID(ID_OBJECT_CONTENT_GRAPHIC, L"Graphic", group, NULL);
		AddCommandID(ID_OBJECT_CONTENT_TEXT, L"Text", group, NULL);
		AddCommandID(ID_OBJECT_CONTENT_UNASSIGNED, L"Unassigned", group, NULL);

		AddCommandID(ID_OBJECT_RASTERIZE, L"Rasterize...", group, NULL);

		AddCommandID(ID_OBJECT_COMPOUNDPATHS_MAKE, L"Make", group, NULL);
		AddCommandID(ID_OBJECT_COMPOUNDPATHS_RELEASE, L"Release", group, NULL);
		AddCommandID(ID_OBJECT_REVERSEPATH, L"Reverse Path", group, NULL);
		AddCommandID(ID_OBJECT_PATH_ADDANCHORPOINTS, L"Add Anchor Points", group, NULL);

		{
			AddCommandID(ID_TEXTWRAP_NONE, L"None", group, NULL);
			AddCommandID(ID_TEXTWRAP_BBOX, L"Bounding Box", group, NULL);
			AddCommandID(ID_TEXTWRAP_SHAPE, L"Shape", group, NULL);
			AddCommandID(ID_TEXTWRAP_OBJECT, L"Object", group, NULL);
			AddCommandID(ID_TEXTWRAP_COLUMN, L"Column", group, NULL);

			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_TEXTWRAP_TOPOFFSET, L"Top Offset", group, &cmd);
				cmd->put_windowClassname(L"Edit");
				cmd->put_windowStyle(ES_AUTOHSCROLL | WS_BORDER);
				//WS_EX_CLIENTEDGE
				cmd->put_itemWidth(50);
			}
			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_TEXTWRAP_LEFTOFFSET, L"Left Offset", group, &cmd);
				cmd->put_windowClassname(L"Edit");
				cmd->put_windowStyle(ES_AUTOHSCROLL | WS_BORDER);
				cmd->put_itemWidth(50);
			}
			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_TEXTWRAP_BOTTOMOFFSET, L"Bottom Offset", group, &cmd);
				cmd->put_windowClassname(L"Edit");
				cmd->put_windowStyle(ES_AUTOHSCROLL | WS_BORDER);
				cmd->put_itemWidth(50);
			}
			{
				CComPtr<IUICommand> cmd;
				AddCommandID(ID_TEXTWRAP_RIGHTOFFSET, L"Right Offset", group, &cmd);
				cmd->put_windowClassname(L"Edit");
				cmd->put_windowStyle(ES_AUTOHSCROLL | WS_BORDER);
				cmd->put_itemWidth(50);
			}
		}

		AddCommandID(ID_OBJECT_ARRANGE_BRINGTOFRONT, L"Bring to Front", group, NULL);
		AddCommandID(ID_OBJECT_ARRANGE_BRINGFORWARD, L"Bring Forward", group, NULL);
		AddCommandID(ID_OBJECT_ARRANGE_SENDBACKWARD, L"Send Backward", group, NULL);
		AddCommandID(ID_OBJECT_ARRANGE_SENDTOBACK, L"Send to Back", group, NULL);

		AppendCommandGroup(group);
	}

#if 0
// Dialogs
	{
		RegisterDlg(CLSID_PagesDlg, L"Pages", 0, NULL);
		RegisterDlg(CLSID_LayersDlg, L"Layers", 0, NULL);
		RegisterDlg(CLSID_NavigatorDlg, L"Navigator", 0, NULL);
		RegisterDlg(CLSID_SwatchesDlg, L"Swatches", 0, NULL);
		RegisterDlg(CLSID_StrokeDlg, L"Stroke", 0, NULL);
		RegisterDlg(CLSID_ColorDlg, L"Color", 0, NULL);
		RegisterDlg(CLSID_GradientDlg, L"Gradient", 0, NULL);
		RegisterDlg(CLSID_ToolsDlg, L"Tools", 0, NULL);
		RegisterDlg(CLSID_TabsDlg, L"Tabs", 0, NULL);
		RegisterDlg(CLSID_LinksDlg, L"Links", 0, NULL);
		RegisterDlg(CLSID_TransparencyDlg, L"Transparency", 0, NULL);
		RegisterDlg(CLSID_AppearanceDlg, L"Appearance", 0, NULL);
		RegisterDlg(CLSID_FilterGraphDlg, L"Filter Graph", 0, NULL);
		RegisterDlg(CLSID_PluginFiltersDlg, L"Filters", 0, NULL);
		RegisterDlg(CLSID_SymbolsDlg, L"Symbols", 0, NULL);

		RegisterMenuDlg(IDR_TEXTWRAP, L"Text Wrap", 0, NULL);
		RegisterMenuDlg(IDR_PARAGRAPH, L"Paragraph", 0, NULL);
		RegisterMenuDlg(IDR_CHARACTER, L"Character", 0, NULL);
	}
#endif
//

	AddMenuResource(IDR_PAGEDESIGNERFRAME);
	AddMenuResource(IDR_CHARACTER);
	AddMenuResource(IDR_LAYERS);
	AddMenuResource(IDR_PAGES);
	AddMenuResource(IDR_LINKS);
	AddMenuResource(IDR_TRANSPARENCY);
	AddMenuResource(IDR_PARAGRAPH);
	AddMenuResource(IDR_PDDOCUMENTVIEW);
	AddMenuResource(IDR_SWATCHES);
	AddMenuResource(IDR_TEXTWRAP);
	AddMenuResource(IDR_TOOLS);
	AddMenuResource(IDR_SYMBOLS);
	AddMenuResource(IDR_COLOR);

	//Load(L"C:\\MMStudio\\Extras\\PageDesigner\\Debug\\PageDesigner.xml");

	AddToolbarCommands(IDR_MAINFRAME);
	AddToolbarCommands(IDR_TOOLS);
	AddToolbarCommands(IDR_PARAGRAPH);
	AddToolbarCommands(IDR_CHARACTER);
	AddToolbarCommands(IDR_TEXTWRAP);

	return S_OK;
}

#include "PagesDlg.h"
#include "LayersDlg.h"

// virtual
HRESULT CIPFrame::CreateDlg(UINT nID, IUIDlg* *pVal)
{
	*pVal = NULL;

	switch (nID)
	{
	case 1:
		{
			CComObject<CPagesDlg>* p;
			CComObject<CPagesDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
			}
		}
		break;

	case 2:
		{
			CComObject<CLayersDlg>* p;
			CComObject<CLayersDlg>::CreateInstance(&p);
			if (p)
			{
				(*pVal = p)->AddRef();
			}
		}
		break;
		/*
		RegisterDlg(CLSID_NavigatorDlg, L"Navigator", 0, NULL);
		RegisterDlg(CLSID_SwatchesDlg, L"Swatches", 0, NULL);
		RegisterDlg(CLSID_StrokeDlg, L"Stroke", 0, NULL);
		RegisterDlg(CLSID_ColorDlg, L"Color", 0, NULL);
		RegisterDlg(CLSID_GradientDlg, L"Gradient", 0, NULL);
		RegisterDlg(CLSID_ToolsDlg, L"Tools", 0, NULL);
		RegisterDlg(CLSID_TabsDlg, L"Tabs", 0, NULL);
		RegisterDlg(CLSID_LinksDlg, L"Links", 0, NULL);
		RegisterDlg(CLSID_TransparencyDlg, L"Transparency", 0, NULL);
		RegisterDlg(CLSID_AppearanceDlg, L"Appearance", 0, NULL);
		RegisterDlg(CLSID_FilterGraphDlg, L"Filter Graph", 0, NULL);
		RegisterDlg(CLSID_PluginFiltersDlg, L"Filters", 0, NULL);
		RegisterDlg(CLSID_SymbolsDlg, L"Symbols", 0, NULL);

		RegisterMenuDlg(IDR_TEXTWRAP, L"Text Wrap", 0, NULL);
		RegisterMenuDlg(IDR_PARAGRAPH, L"Paragraph", 0, NULL);
		RegisterMenuDlg(IDR_CHARACTER, L"Character", 0, NULL);
		*/
	}

	return S_OK;
}

STDMETHODIMP CIPFrame::OnCmdMsg(long nID, long nCode, IUICmdUpdate * pCmdUI, BOOL * bHandled)
{
	if (bHandled == NULL) return E_POINTER;

	*bHandled = TRUE;

	if (!pCmdUI)
	{
		*bHandled = FALSE;
	}
	else
	{
		*bHandled = FALSE;
	}

	if (*bHandled) return S_OK;

// Try base
	baseClass::OnCmdMsg(nID, nCode, pCmdUI, bHandled);
	if (*bHandled) return S_OK;

// Try App
	CComQIPtr<ICommandTarget> app = gIApp;
	app->OnCmdMsg(nID, nCode, pCmdUI, bHandled);

	return S_OK;
}
