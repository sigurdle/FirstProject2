#include "stdafx.h"
#include "X3D2.h"
#include "Inline.h"

#include "VRMLLoader.h"

namespace System
{

GUIEXT map<String, Object*> g_files;

namespace x3d
{

NodeType* Inline::nodeType(GetNodeType());

NodeType* Inline::GetNodeType()
{
	static X3DFieldDefinition load("load", FieldType_SFBool, SAIFieldAccess_inputOutput, offsetof(Inline, m_load));
	static X3DFieldDefinition url("url", FieldType_MFString, SAIFieldAccess_inputOutput, offsetof(Inline, m_url));

	static X3DFieldDefinition* fields[] =
	{
		&load,
		&url,
	};

	static NodeType nodeType("Inline", typeid(Inline), fields, _countof(fields), X3DChildNode::GetNodeType());
	return &nodeType;
}

Inline::Inline() : X3DChildNode(GetNodeType())
{
	m_hLoadThread = NULL;
	m_children = NULL;

//	m_children = static_cast<MFNode*>(GetField(L"children"));
}

Inline::Inline(StringIn url) : X3DChildNode(GetNodeType()),
	m_url(new MFString(NULL, this, url))
{
	m_hLoadThread = NULL;
	m_children = NULL;

//	m_children = static_cast<MFNode*>(GetField(L"children"));
}

Inline::~Inline()
{
}

DWORD WINAPI Inline::_LoadThread(void* lParam)
{
	Inline* pThis = (Inline*)lParam;
	return pThis->LoadThread();
}

DWORD Inline::LoadThread()
{
//	MFNode* children = new MFNode;
//	children->AddRef();

	ASSERT(0);
#if 0

	if (m_url->get_size() > 0)
	{
		StringW* url = m_url->get1Value(0);

		WCHAR buf[512];
		wcscpy_s(buf, m_scene->getWorldURL()->c_str());

		WCHAR* p = buf + m_scene->getWorldURL().GetLength();
		while (p[-1] != '\\' && p[-1] != '/')
		{
			p--;
		}
		*p = 0;

		wcscat_s(buf, url->c_str());

		VRMLLoader* loader = new VRMLLoader;
		//loader->AddRef();

		Scene* scene = loader->Load(new StringW(string_copy(buf)));

		//loader->Release();

		if (scene)
		{
			Scene* pScene = scene;

			for (unsigned int i = 0; i < pScene->m_root->get_children()->m_items.size(); i++)
			{
				children->m_items.push_back(pScene->m_root->get_children()->m_items[i]);
			}
		}

	//	scene.Detach();
	}
#endif

	return 0;
}

// virtual
void Inline::Draw(X3DDrawContext* pDC)
{
	{
		CriticalSectionLock lock(m_critSec);

		if (m_children == NULL)
		{
			if (true)
			{
				Object* file = g_files[m_url->get1Value(0)];
				Gui::Media3D::Visual3D* visual3D = dynamic_cast<Gui::Media3D::Visual3D*>(file);
				if (visual3D)
				{
					m_visual3D = visual3D;
					MFNode* children = new MFNode(this);
				//	children->append1Value();
					m_children = children;
				}
			}
			else
			{
				if (m_hLoadThread == NULL)
				{
					m_hLoadThread = ::CreateThread(NULL, 0, _LoadThread, this, 0, &m_dwLoadThreadId);
				}
			}
		}
	}

	int nLight = pDC->m_renderContext->m_nLight;

	if (m_visual3D)
	{
		m_visual3D->Render(pDC->m_renderContext);
	}
	else
	{
		for (uint i = 0; i < m_children->m_items.GetSize(); ++i)
		{
			if (m_children->m_items[i])
			{
				RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
				if (render)
				{
					render->PreDraw(pDC);
				}
			}
		}

		for (uint i = 0; i < m_children->m_items.GetSize(); ++i)
		{
			if (m_children->m_items[i])
			{
				RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(m_children->m_items[i]->GetNode());
				if (render)
				{
					render->Draw(pDC);
				}
			}
		}

		for (int i = pDC->m_renderContext->m_nLight; i >= nLight; --i)
		{
		//	pDC->m_pGraphics3D->Disable(GL_LIGHT0+i);
		}
	}

	pDC->m_renderContext->m_nLight = nLight;
}

void Inline::DrawOverlay(X3DDrawContext* pDC)
{
	if (m_children)
	{
		int nLight = pDC->m_renderContext->m_nLight;

		for (unsigned i = 0; i < m_children->m_items.GetSize(); i++)
		{
			X3DNode* node = m_children->m_items[i];

			if (node)
			{
				RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
				if (render)
				{
					render->PreDraw(pDC);
				}
			}
		}

		for (unsigned i = 0; i < m_children->m_items.GetSize(); i++)
		{
			X3DNode* node = m_children->m_items[i];

			if (node)
			{
				RenderImplImpl* render = dynamic_cast<RenderImplImpl*>(node->GetNode());
				if (render)
				{
					render->DrawOverlay(pDC);
				}
			}
		}

		for (int i = pDC->m_renderContext->m_nLight; i >= nLight; i--)
		{
	//		pDC->m_pGraphics3D->Disable(GL_LIGHT0+i);
		}
		pDC->m_renderContext->m_nLight = nLight;
	}
}

}	// x3d
}	// System
