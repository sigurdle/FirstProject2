#pragma once

/////////////////////////////////////////////////////////////////////////////
// OLE data (like AUX_DATA)

struct OLE_DATA
{
	// OLE 1.0 clipboard formats
	UINT    cfNative, cfOwnerLink, cfObjectLink;

	// OLE 2.0 clipboard formats
	UINT    cfEmbeddedObject, cfEmbedSource, cfLinkSource;
	UINT    cfObjectDescriptor, cfLinkSourceDescriptor;
	UINT    cfFileName, cfFileNameW;

	//RichEdit formats
	UINT    cfRichTextFormat;
	UINT    cfRichTextAndObjects;

	OLE_DATA();
};

extern OLE_DATA _oleData;
