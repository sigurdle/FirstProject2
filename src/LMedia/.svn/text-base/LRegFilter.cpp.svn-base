#include "stdafx.h"

#include "LMediaImpl.h"
#include "LRegFilter.h"
#include "LFilterGraph.h"

using namespace System;

#if AMIGA || __APPLE__
#define _wtoi64 atoi//_atoi64
#endif

/*
StringW stripspaces(const WCHAR* s)
{
	StringW str;
	while (*s)
	{
		if (!iswspace(*s))
			str += *s;
		s++;
	}

	return str;
}
*/

namespace System
{

XmlData::Element* GetElementByTagNameNS(XmlData::Element* parent, StringIn ns, StringIn tagName, bool bDeep = true);

XmlData::Element* GetElementByTagNameNS(XmlData::Element* parent, StringIn ns, StringIn tagName, bool bDeep/* = TRUE*/)
{
	XmlData::Node* child = parent->get_firstChild();

	while (child != NULL)
	{
		XmlData::Element* element = dynamic_cast<XmlData::Element*>(child);
		if (element)
		{
			String ens = element->get_namespaceURI();

			if (ens == ns)
			{
				String etagName = element->get_localName();
				if (etagName == NULL)
				{
					etagName = element->get_tagName();
				}

				if (etagName == tagName)
				{
					return element;
				}
			}

		// Recurse
			if (bDeep)
			{
				XmlData::Element* element2 = GetElementByTagNameNS(element, ns, tagName, true);
				if (element2 != NULL)
					return element2;
			}
		}

		child = child->get_nextSibling();
	}

	return NULL;
}

// This version assumes c is a legal hex digit
int Hex2Number(int c)
{
	ASSERT(isxdigit(c));

	if (c <= '9')
		return c - '0';
	else if (c <= 'F')
		return 10 + c - 'A';
	else
		return 10 + c - 'a';
}

void HexStringToBytes(const WCHAR* str, uint8* buf, int length)
{
	for (int i = 0; i < length; i++)
	{
		int l = Hex2Number(str[i*2+0]);
		int h = Hex2Number(str[i*2+1]);

		buf[i] = (l<<4) | h;
	}
}

namespace MediaShow
{

CDispLRegFilter::CDispLRegFilter()
{
}

String CDispLRegFilter::get_Name() const
{
	return m_Name;
}

ErrorCode CDispLRegFilter::BuildRegFilter(XmlData::Element* element)
{
	m_Name = element->getAttribute(WSTR("name"));
	m_Src = element->getAttribute(WSTR("src"));

	XmlData::Node* node = element->get_firstChild();
	while (node)
	{
		XmlData::Element* element = dynamic_cast<XmlData::Element*>(node);
		if (element)
		{
			String tagName = element->get_tagName();

			if (tagName == L"inputpin" ||
				tagName == L"outputpin")
			{
				CLRegPin* pRegPin = new CLRegPin;

				if (tagName == L"inputpin")
				{
					pRegPin->m_dir = PINDIR_INPUT;
				}
				else// if (!wcscmp(tagName, L"outputpin"))
				{
					pRegPin->m_dir = PINDIR_OUTPUT;
				}

				String minOccurs = element->getAttribute(WSTR("minOccurs"));
				String maxOccurs = element->getAttribute(WSTR("maxOccurs"));

				pRegPin->m_name = element->getAttribute(WSTR("name"));

				XmlData::Element* mediaTypes = GetElementByTagNameNS(element, NULL, WSTR("mediatypes"), false);
				if (mediaTypes)
				{
					XmlData::Node* node = mediaTypes->get_firstChild();
					while (node)
					{
						XmlData::Element* element = dynamic_cast<XmlData::Element*>(node);
						if (element)
						{
							String tagName = element->get_tagName();
							if (tagName == "mediatype")
							{
								CLRegMediaType* pRegMediaType = new CLRegMediaType;

								String majortype = element->getAttribute(WSTR("majortype"));
								if (majortype.Compare(WSTR("stream")) == 0)
								{
									pRegMediaType->m_majortype = LMEDIATYPE_Stream;

									XmlData::Element* streamcontent = GetElementByTagNameNS(element, NULL, WSTR("streamcontent"), false);
									if (streamcontent)
									{
										XmlData::Node* node = streamcontent->get_firstChild();
										while (node)
										{
											XmlData::Element* element = dynamic_cast<XmlData::Element*>(node);
											if (element)
											{
												String tagName = element->get_tagName();

												if (tagName == "match")
												{
													CMatch match;

													XmlData::Node* node = element->get_firstChild();
													while (node)
													{
														XmlData::Element* element = dynamic_cast<XmlData::Element*>(node);
														if (element)
														{
															String tagName = element->get_tagName();

															if (tagName == "pattern")
															{
																String value = element->getAttribute(WSTR("value"));
																if (value != NULL)
																{
																	BytePattern pattern;
																	
																	String offset = element->getAttribute(WSTR("offset"));
																	if (offset != NULL)
																		//pattern.m_offset = _wtoi64(offset.c_str());
																		pattern.m_offset = str2int(CString(offset));
																	else
																		pattern.m_offset = 0;

																	String v = stripspaces(value);
																	pattern.m_length = v.GetLength()/2;
																	pattern.m_value = new uint8[pattern.m_length];

																	HexStringToBytes(CStringw(v), pattern.m_value, pattern.m_length);

																	pattern.m_mask = new uint8[pattern.m_length];

																	String mask = element->getAttribute(WSTR("mask"));

																	int masklen;
																	if (mask != NULL)
																	{
																		v = stripspaces(mask);
																		masklen = MIN(v.GetLength()/2, pattern.m_length);
																		HexStringToBytes(CStringw(v), pattern.m_mask, masklen);
																	}
																	else
																		masklen = 0;

																	while (masklen < pattern.m_length)	// Fill rest with 0xFF
																	{
																		pattern.m_mask[masklen++] = 0xFF;
																	}

																	match.m_patterns.Add(pattern);
																}
															}
														}

														node = node->get_nextSibling();
													}

													pRegMediaType->m_streamcontent.m_matches.Add(match);
												}
											}

											node = node->get_nextSibling();
										}
									}
								}
								else if (majortype.Compare(WSTR("video")) == 0)
								{
									pRegMediaType->m_majortype = LMEDIATYPE_Video;
								}
								else if (majortype.Compare(WSTR("audio")) == 0)
								{
									pRegMediaType->m_majortype = LMEDIATYPE_Audio;
								}
								else if (majortype.Compare(WSTR("scene")) == 0)
								{
									pRegMediaType->m_majortype = LMEDIATYPE_Scene;
								}
								else
								{
									// TODO
									ASSERT(0);
								}

								pRegPin->m_mediaTypes.Add(pRegMediaType);
							}
						}

						node = node->get_nextSibling();
					}
				}

				m_RegPins.Add(pRegPin);
			}
		}

		node = node->get_nextSibling();
	}

	return 0;
}

}	// MediaShow
}
