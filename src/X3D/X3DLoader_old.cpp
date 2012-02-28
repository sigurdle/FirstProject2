// LX3DViewer.cpp : Implementation of CLX3DViewer

#include "stdafx.h"
#include "LX3D.h"
#include "LX3DViewer.h"

#include "LX3DScene.h"

#include "../LXML/LDOMDocumentImpl.h"
#include "../LXML/LDOMElementImpl.h"

//#import "../LXML/LXML.tlb" no_namespace, raw_interfaces_only, named_guids
//#import "../LXML/LXML.tlb" raw_interfaces_only, named_guids, no_namespace exclude("IServiceProvider", "IDispatchEx")

#if 0

ILDOMElement* FindByTagName(ILDOMElement* parent, BSTR tagName, BOOL bDeep = TRUE);

ILDOMElement* FindByTagName(ILDOMElement* parent, BSTR tagName, BOOL bDeep/* = TRUE*/)
{
	CComPtr<ILDOMNode> child;
	parent->get_firstChild(&child);

	while (child != NULL)
	{
		LDOMNodeType nodeType;
		child->get_nodeType(&nodeType);

		if (nodeType == LNODE_ELEMENT)
		{
			CComQIPtr<ILDOMElement> element = child;
			BSTR etagName;
			element->get_tagName(&etagName);
			_bstr_t ttagName = _bstr_t(etagName, false);

			if (!wcscmp(ttagName, tagName))
			{
				return element;
			}

		// Recurse
			if (bDeep)
			{
				CComQIPtr<ILDOMElement> element2 = FindByTagName(element, tagName);
				if (element2 != NULL)
					return element2;
			}
		}

		CComPtr<ILDOMNode> nextSibling;
		child->get_nextSibling(&nextSibling);
		child = nextSibling;
	}

	return NULL;
}
#endif

class CLX3DLoader
{
public:
	CLX3DScene* m_scene;

	CLX3DNode* BuildScene(LXML::Element* element);
};

CLX3DNode* CLX3DLoader::BuildScene(LXML::Element* element)
{
	sysstring tagName = element->get_tagName();

	CLSAINodeType* pNodeType = m_scene->FindNodeType(tagName);
	ATLASSERT(pNodeType);

	CLX3DNode* node = m_scene->CreateNodeOfType(pNodeType);

#if 0
	if (!wcscmp(tagName, L"DirectionalLight"))
	{
		CComObject<CLDirectionalLight>* x3dnode;
		CComObject<CLDirectionalLight>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Appearance"))
	{
		CComObject<CLAppearance>* x3dnode;
		CComObject<CLAppearance>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		// Recurse children
		CComPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;
			if (element)
			{
				CComPtr<ILX3DNode> node = BuildScene(element);

				if (x3dnode->m_material == NULL)	// Use the first material node found
				{
					CComQIPtr<ILX3DMaterialNode> materialNode = node;
					if (materialNode)
					{
						x3dnode->m_material = materialNode;
					}
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Material"))
	{
		CComObject<CLMaterial>* x3dnode;
		CComObject<CLMaterial>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		{
			CComBSTR bstr;
			element->getAttribute(L"diffuseColor", &bstr);

			if (bstr != NULL)
			{
				WCHAR* p = bstr;

				while (iswspace(*p)) p++;
				x3dnode->m_diffuseColor[0] = getfnumber(&p);
				if (p == NULL) ATLASSERT(0);

				while (iswspace(*p)) p++;
				x3dnode->m_diffuseColor[1] = getfnumber(&p);
				if (p == NULL) ATLASSERT(0);

				while (iswspace(*p)) p++;
				x3dnode->m_diffuseColor[2] = getfnumber(&p);
				if (p == NULL) ATLASSERT(0);

				while (iswspace(*p)) p++;
				ATLASSERT(*p == 0);
			}
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Coordinate"))
	{
		CComObject<CLCoordinate>* x3dnode;
		CComObject<CLCoordinate>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		{
			CComBSTR bstr;
			element->getAttribute(L"point", &bstr);

			if (bstr != NULL)
			{
				WCHAR* p = bstr;

				while (1)
				{
					gmVector3 point;

					while (iswspace(*p)) p++;
					point[0] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					point[1] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					point[2] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					x3dnode->m_point.Add(point);

					while (iswspace(*p)) p++;

					if (*p == 0)
						break;

					if (*p == ',')
					{
						p++;
					}
					else
						ATLASSERT(0);
				}
			}
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Color"))
	{
		CComObject<CLColor>* x3dnode;
		CComObject<CLColor>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		{
			CComBSTR bstr;
			element->getAttribute(L"color", &bstr);

			if (bstr != NULL)
			{
				WCHAR* p = bstr;

				while (1)
				{
					gmVector3 color;

					while (iswspace(*p)) p++;
					color[0] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					color[1] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					color[2] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					x3dnode->m_color.Add(color);

					while (iswspace(*p)) p++;

					if (*p == 0)
						break;

					if (*p == ',')
					{
						p++;
					}
					else
						ATLASSERT(0);
				}
			}
		}

		return x3dnode;
	}
//
	else if (!wcscmp(tagName, L"Box"))
	{
		CComObject<CLBox>* x3dnode;
		CComObject<CLBox>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Sphere"))
	{
		CComObject<CLSphere>* x3dnode;
		CComObject<CLSphere>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		CComBSTR bstr;
		element->getAttribute(L"radius", &bstr);
		if (bstr != NULL)
		{
			x3dnode->m_radius = getfnumber(bstr);
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Cone"))
	{
		CComObject<CLCone>* x3dnode;
		CComObject<CLCone>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		{
			CComBSTR bstr;
			element->getAttribute(L"bottomRadius", &bstr);
			if (bstr != NULL)
			{
				x3dnode->m_bottomRadius = getfnumber(bstr);
			}
		}

		{
			CComBSTR bstr;
			element->getAttribute(L"height", &bstr);
			if (bstr != NULL)
			{
				x3dnode->m_height = getfnumber(bstr);
			}
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Cylinder"))
	{
		CComObject<CLCylinder>* x3dnode;
		CComObject<CLCylinder>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		{
			CComBSTR bstr;
			element->getAttribute(L"radius", &bstr);
			if (bstr != NULL)
			{
				x3dnode->m_radius = getfnumber(bstr);
			}
		}

		{
			CComBSTR bstr;
			element->getAttribute(L"height", &bstr);
			if (bstr != NULL)
			{
				x3dnode->m_height = getfnumber(bstr);
			}
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"TriangleSet"))
	{
		CComObject<CLTriangleSet>* x3dnode;
		CComObject<CLTriangleSet>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		// Recurse children
		CComPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;
			if (element)
			{
				CComPtr<ILX3DNode> node = BuildScene(element);

				if (x3dnode->m_coord == NULL)	// Use the first coord node found
				{
					CComQIPtr<ILX3DCoordinateNode> coordinateNode = node;
					if (coordinateNode)
					{
						x3dnode->m_coord = coordinateNode;
					}
				}

				if (x3dnode->m_color == NULL)	// Use the first color node found
				{
					CComQIPtr<ILX3DColorNode> colorNode = node;
					if (colorNode)
					{
						x3dnode->m_color = colorNode;
					}
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		return x3dnode;
	}

//
	else if (!wcscmp(tagName, L"Shape"))
	{
		CComObject<CLShape>* x3dnode;
		CComObject<CLShape>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		// Recurse children
		CComPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;
			if (element)
			{
				CComPtr<ILX3DNode> node = BuildScene(element);

				if (x3dnode->m_geometry == NULL)	// Use the first geometry node found
				{
					CComQIPtr<ILX3DGeometryNode> geometryNode = node;
					if (geometryNode)
					{
						x3dnode->m_geometry = geometryNode;
					}
				}

				if (x3dnode->m_appearance == NULL)	// Use the first appearance node
				{
					CComQIPtr<ILX3DAppearanceNode> appearanceNode = node;
					if (appearanceNode)
					{
						x3dnode->m_appearance = appearanceNode;
					}
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		return x3dnode;
	}
	else if (!wcscmp(tagName, L"Transform") ||
				!wcscmp(tagName, L"Scene"))	// hm..
	{
		CComObject<CLTransform>* x3dnode;
		CComObject<CLTransform>::CreateInstance(&x3dnode);
		x3dnode->AddRef();

		if (!wcscmp(tagName, L"Transform"))
		{
			{
				CComBSTR bstr;
				element->getAttribute(L"translation", &bstr);

				if (bstr != NULL)
				{
					WCHAR* p = bstr;

					while (iswspace(*p)) p++;
					x3dnode->m_T[0] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					x3dnode->m_T[1] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					x3dnode->m_T[2] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					ATLASSERT(*p == 0);
				}
			}

			{
				CComBSTR bstr;
				element->getAttribute(L"rotation", &bstr);
				if (bstr != NULL)
				{
					WCHAR* p = bstr;

				// rotation axis
					while (iswspace(*p)) p++;
					x3dnode->m_R.m_v[0] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					x3dnode->m_R.m_v[1] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					x3dnode->m_R.m_v[2] = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

				// rotation angle
					while (iswspace(*p)) p++;
					x3dnode->m_R.m_angle = getfnumber(&p);
					if (p == NULL) ATLASSERT(0);

					while (iswspace(*p)) p++;
					ATLASSERT(*p == 0);
				}
			}
		}

		// Recurse children
		CComPtr<ILDOMNode> node;
		element->get_firstChild(&node);
		while (node)
		{
			CComQIPtr<ILDOMElement> element = node;
			if (element)
			{
				CComPtr<ILX3DNode> node = BuildScene(element);

				CComQIPtr<ILX3DChildNode> childNode = node;
				if (childNode)
				{
					x3dnode->m_children.Add(childNode);
				}
			}

			CComPtr<ILDOMNode> nextSibling;
			node->get_nextSibling(&nextSibling);
			node = nextSibling;
		}

		return x3dnode;
	}
	else
	{
		// TODO something to implement
	//	ATLASSERT(0);
	}
#endif

	return NULL;
}
