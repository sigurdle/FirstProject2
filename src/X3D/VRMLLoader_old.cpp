// VRMLLoader.cpp : Implementation of CVRMLLoader

#include "stdafx.h"
#include "LX3D.h"
#include "VRMLLoader.h"

STDMETHODIMP CVRMLLoader::CInputPin::ReceiveConnection(ILPin* pConnector, LMediaType* pmt)
{
	return S_OK;
}

#include "LX3DScene.h"

#include "LVRMLLoader.h"
#include "3DS.h"
//#import "../LXML/LXML.tlb" raw_interfaces_only, named_guids, no_namespace, exclude("IServiceProvider", "IDispatchEx")

class CX3DXMLParser
{
public:
	HRESULT Parse(ILDOMDocument* document);

	CLX3DScene* m_scene;

	CComPtr<ILX3DNode> ReadNode(ILDOMElement* element, CComBSTR& containerField);
	void ReadChildren(ILDOMElement* element, ILX3DNode* x3dnode);
};

#if 0
struct NodeMap
{
	WCHAR* x3dfield;
	WCHAR* tagName;
};

NodeMap shapenodemappings[] =
{
L"appearance", L"Appearance",
L"geometry", L"Box",
L"geometry", L"Sphere",
L"geometry", L"Cylinder",
NULL
};

WCHAR* GetFieldMap(NodeMap* mappings, WCHAR* name)
{
	int i = 0;
	while (mappings[i].tagName)
	{
		if (!wcscmp(mappings[i].tagName, name))
		{
			return mappings[i].x3dfield;
		}
		i++;
	}
	return NULL;
}
#endif

struct NodeType
{
	WCHAR* name;
	WCHAR* containerField;
	void* mappings;
};

NodeType nodeTypes[] =
{
	L"NavigationInfo", L"children", NULL,
	L"DirectionalLight", L"children", NULL,
	L"Viewpoint", L"children", NULL,
	L"Shape", L"children", NULL,
	L"Appearance", L"appearance", NULL,
	L"Box", L"geometry", NULL,
	L"Sphere", L"geometry", NULL,
	L"Transform", L"children", NULL,
	L"Material", L"material", NULL,
	L"NurbsSurface", L"geometry", NULL,
	L"NurbsCurve", L"geometry", NULL,
	L"IndexedFaceSet", L"geometry", NULL,
	L"IndexedLineSet", L"geometry", NULL,
	L"CoordinateInterpolator", L"children", NULL,
	L"TimeSensor", L"children", NULL,
	L"Background", L"children", NULL,
	L"Collision", L"children", NULL,
	L"HAnimHumanoid", L"children", NULL,
	L"HAnimJoint", L"children", NULL,
	L"HAnimSegment", L"children", NULL,
	L"HAnimSite", L"children", NULL,
	L"WorldInfo", L"children", NULL,
	L"Coordinate", L"coord", NULL,
	L"Inline", L"children", NULL,
	L"Group", L"children", NULL,
	//L"Script", L"children", NULL,
	NULL,
};

NodeType* GetNodeType(WCHAR* name)
{
	int i = 0;
	while (nodeTypes[i].name)
	{
		if (!wcscmp(nodeTypes[i].name, name))
		{
			return &nodeTypes[i];
		}
		i++;
	}
	return NULL;
}

CComPtr<ILX3DNode> CX3DXMLParser::ReadNode(ILDOMElement* element, CComBSTR& containerField)
{
	CComBSTR tagName;
	element->get_tagName(&tagName);

	CComPtr<ILX3DNode> x3dnode;

	CComBSTR use_value;
	element->getAttribute(L"USE", &use_value);
	if (use_value != NULL)
	{
		m_scene->getDEFName(use_value, &x3dnode);
		ATLASSERT(x3dnode);

		element->getAttribute(L"containerField", &containerField);
	}
	else
	{
		CLSAINodeType* pNodeType = m_scene->FindNodeType(tagName);
		if (pNodeType)
		{
			m_scene->CreateNodeOfType(pNodeType, &x3dnode);
		}

		if (x3dnode)
		{
			CComPtr<ILDOMNamedNodeMap> attributes;
			element->get_attributes(&attributes);

			long nattributes;
			attributes->get_length(&nattributes);
			for (int i = 0; i < nattributes; i++)
			{
				CComPtr<ILDOMAttr> attr;
				attributes->item(i, (ILDOMNode**)&attr);

				CComBSTR name;
				attr->get_name(&name);

				CComBSTR bstr_value;
				attr->get_value(&bstr_value);

				if (!wcscmp(name, L"DEF"))
				{
					CDef* pDef = new CDef;
					pDef->m_name = bstr_value;
					pDef->m_node = x3dnode;

					m_scene->m_defs.Add(pDef);
				}
				else if (!wcscmp(name, L"containerField"))
				{
					containerField = bstr_value;
				}
				else
				{
					CComPtr<ILX3DField> x3dfield;
					x3dnode->getField(name, &x3dfield);
					if (x3dfield)
					{
						FieldType fieldType = CComQIPtr<CLX3DFieldImplImpl>(x3dfield)->m_fieldType;//CComQIPtr<CFieldValue>(field)->m_fieldType;

						int sfType;
						if (fieldType >= SFBool)
						{
							sfType = fieldType;
						}
						else
						{
							sfType = fieldType + SFBool;
						}

						WCHAR* p = (BSTR)bstr_value;
						while (iswspace(*p)) p++;

						while (*p)
						{
							switch (sfType)
							{
							case SFBool:
								{
									if (!wcscmp(p, L"true"))
									{
										p += 4;
										CComQIPtr<ILSFBool>(x3dfield)->setValue(VARIANT_TRUE);
									}
									else if (!wcscmp(p, L"false"))
									{
										p += 5;
										CComQIPtr<ILSFBool>(x3dfield)->setValue(VARIANT_FALSE);
									}
									else
										throw -1;
								}
								break;

							case SFTime:
								{
									double value = getfnumber(&p);
									if (p == NULL) throw -1;
									
									if (CComQIPtr<ILSFTime>(x3dfield))
										CComQIPtr<ILSFTime>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFTime>(x3dfield)->append1Value(value);
								}
								break;

							case SFFloat:
								{
									float value = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									
									if (CComQIPtr<ILSFFloat>(x3dfield))
										CComQIPtr<ILSFFloat>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFFloat>(x3dfield)->append1Value(value);
								}
								break;

							case SFInt32:
								{
									long value = getnumber(&p);
									if (p == NULL) throw -1;
									
									if (CComQIPtr<ILSFInt32>(x3dfield))
										CComQIPtr<ILSFInt32>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFInt32>(x3dfield)->append1Value(value);
								}
								break;

							case SFColor:
								{
									float value[3];

									value[0] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;
									
									value[1] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;
									
									value[2] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;

									if (CComQIPtr<ILSFColor>(x3dfield))
										CComQIPtr<ILSFColor>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFColor>(x3dfield)->append1Value(value);

								}
								break;

							case SFVec3f:
								{
									float value[3];

									WCHAR* p2;
									
									p2 = p;
									value[0] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;
									
									p2 = p;
									value[1] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;
									
									p2 = p;
									value[2] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;

									if (CComQIPtr<ILSFVec3f>(x3dfield))
										CComQIPtr<ILSFVec3f>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFVec3f>(x3dfield)->append1Value(value);
								}
								break;

							case SFRotation:
								{
									float value[4];

									value[0] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;
									
									value[1] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;
									
									value[2] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;

									value[3] = (float)getfnumber(&p);
									if (p == NULL) throw -1;
									while (iswspace(*p)) p++;

									if (CComQIPtr<ILSFRotation>(x3dfield))
										CComQIPtr<ILSFRotation>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFRotation>(x3dfield)->append1Value(value);
								}
								break;

							case SFString:
								{
									CWCharString value;

									if (fieldType >= SFBool)
									{
										value = bstr_value;
										p += wcslen(p);
									}
									else
									{
										WCHAR delimiter = *p;

										if (delimiter != '"' && delimiter != '\'')
										{
											long size;
											CComQIPtr<ILMFString>(x3dfield)->get_size(&size);
											if (size == 0)	// A single string is allowed without quotes
											{
												value = bstr_value;
												p += wcslen(p);
											}
											else
											{
												throw -1;
											}
										}
										else
										{
											p++;

											while (*p)
											{
												if (*p == delimiter)
												{
													break;
												}

												value += *p;
												p++;
											}

											if (*p != delimiter)
											{
												throw -1;
											}
											p++;
										}
									}

									if (CComQIPtr<ILSFString>(x3dfield))
										CComQIPtr<ILSFString>(x3dfield)->setValue(value);
									else
										CComQIPtr<ILMFString>(x3dfield)->append1Value(value);
								}
								break;

							default:
								ATLASSERT(0);
							}

							while (iswspace(*p)) p++;

							if (fieldType < SFBool)
							{
								if (*p == ',')
								{
									p++;
								}
								while (iswspace(*p)) p++;
							}
							else
							{
								if (*p != 0)
								{
									throw -1;
								}
								break;
							}
						}
					}
					else
					{
						ATLTRACE("unknown attribute field %S\n", (BSTR)name);
					}
				}
			}

			ReadChildren(element, x3dnode);
		}
	}

	return x3dnode;
}

void CX3DXMLParser::ReadChildren(ILDOMElement* element, ILX3DNode* x3dnode)
{
	CComPtr<ILDOMNode> node;
	element->get_firstChild(&node);
	while (node)
	{
		CComQIPtr<ILDOMElement> element = node;
		if (element)
		{
			CComBSTR tagName;
			element->get_tagName(&tagName);

			if (!wcscmp(tagName, L"ROUTE"))
			{
				CComBSTR fromNode;
				element->getAttribute(L"fromNode", &fromNode);

				CComBSTR fromField;
				element->getAttribute(L"fromField", &fromField);

				CComBSTR toNode;
				element->getAttribute(L"toNode", &toNode);

				CComBSTR toField;
				element->getAttribute(L"toField", &toField);

				CComPtr<ILX3DNode> sourceNode;
				m_scene->getDEFName(fromNode, &sourceNode);

				CComPtr<ILX3DNode> destinationNode;
				m_scene->getDEFName(toNode, &destinationNode);

				m_scene->addRoute(sourceNode, fromField, destinationNode, toField);
			}
			else if (!wcscmp(tagName, L"ExternProtoDeclare"))
			{
				// TODO
			}
			else if (!wcscmp(tagName, L"Script"))
			{
				// TODO
			}
			else if (!wcscmp(tagName, L"ProtoInstance"))
			{
				// TODO
			}
			else
			{
				NodeType* nodeType = GetNodeType(tagName);
				if (nodeType)
				{
					CComBSTR containerField;
					CComPtr<ILX3DNode> x3dchild = ReadNode(element, containerField);

					if (containerField.Length() == 0)
					{
						containerField = nodeType->containerField;
					}

					CComPtr<ILX3DField> x3dfield;
					x3dnode->getField(containerField, &x3dfield);
					if (x3dfield)
					{
						CComQIPtr<ILSFNode> sfnode;
						CComQIPtr<ILMFNode> mfnode;

						if (sfnode = x3dfield)
						{
							sfnode->setValue(x3dchild);
						}
						else if (mfnode = x3dfield)
						{
							mfnode->append1Value(x3dchild);
						}
						else
						{
							ATLASSERT(0);
						}
					}
					else
					{
						ATLASSERT(0);
					}
				}
				else
				{
					ATLASSERT(0);
				}
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		node->get_nextSibling(&nextSibling);
		node = nextSibling;
	}
}

HRESULT CX3DXMLParser::Parse(ILDOMDocument* document)
{
	CComPtr<ILDOMElement> documentElement;
	document->get_documentElement(&documentElement);
	if (documentElement)
	{
		CComBSTR tagName;
		documentElement->get_tagName(&tagName);
		if (!wcscmp(tagName, L"X3D"))
		{
			CComPtr<ILDOMNode> node;
			documentElement->get_firstChild(&node);
			while (node)
			{
				CComQIPtr<ILDOMElement> element = node;
				if (element)
				{
					CComBSTR tagName;
					element->get_tagName(&tagName);
					if (!wcscmp(tagName, L"Scene"))
					{
						ReadChildren(element, m_scene->m_root);
					}
				}

				CComPtr<ILDOMNode> nextSibling;
				node->get_nextSibling(&nextSibling);
				node = nextSibling;
			}

			return S_OK;
		}
	}

	return E_FAIL;
}

STDMETHODIMP CVRMLLoader::Load(BSTR url, ILX3DScene **pVal)
{
	HRESULT hr;

	CComPtr<IBindCtx> bc;
	hr = CreateBindCtx(0/*reserved*/, &bc);
	if (SUCCEEDED(hr))
	{
		CComPtr<IMoniker> moniker;
		hr = CreateURLMoniker(NULL, url, &moniker);
		if (SUCCEEDED(hr))
		{
			CComPtr<IStream> stream;
			hr = moniker->BindToStorage(bc, NULL, IID_IStream, (void**)&stream);
			if (SUCCEEDED(hr))
			{
				BYTE buf[8];
				ULONG nRead;
				stream->Read(buf, 8, &nRead);

				// Seek back to start
				LARGE_INTEGER li;
				li.QuadPart = 0;
				stream->Seek(li, STREAM_SEEK_SET, NULL);

				if ((nRead >= 4 &&
					buf[0] == '#' &&
					buf[1] == 'X' &&
					buf[2] == '3' &&
					buf[3] == 'D') ||

					(nRead >= 5 &&
					buf[0] == '#' &&
					buf[1] == 'V' &&
					buf[2] == 'R' &&
					buf[3] == 'M' &&
					buf[4] == 'L'))
				{
					CComObject<VRMLLoader>* pLoader;
					CComObject<VRMLLoader>::CreateInstance(&pLoader);
					pLoader->AddRef();

					hr = pLoader->Load(url, stream, pVal);

					pLoader->Release();
				}
				else if (nRead >= 2 && *(WORD*)buf == 0x4D4D)	// 3DS
				{
					C3DSLoader* pLoader = new C3DSLoader;

					pLoader->Load(url, stream, pVal);

					delete pLoader;
				}
				else
				{
					CComPtr<ILDOMDocument> document;
					HRESULT hr = document.CoCreateInstance(CLSID_LDOMDocument);
					if (SUCCEEDED(hr))
					{
						VARIANT_BOOL success;
						document->load(_variant_t(stream), &success);

						CX3DXMLParser*  pParser = new CX3DXMLParser;

						CComObject<CLX3DScene>* pScene;
						hr = CComObject<CLX3DScene>::CreateInstance(&pScene);
						if (SUCCEEDED(hr))
						{
							pScene->AddRef();
							pScene->m_url = url;

							pParser->m_scene = pScene;

							pParser->Parse(document);

							*pVal = pScene;
						}
						delete pParser;
					}
				}
			}
		}
	}

	return hr;

#if 0
	CComPtr<ILDOMDocument> doc;
	doc.CoCreateInstance(CLSID_LDOMDocument);

	VARIANT_BOOL success;
	doc->load(_variant_t(pathName), &success);
	if (success)
	{
		MessageBeep(-1);
	}
	else
	{
	}
#endif
	return E_FAIL;
}
