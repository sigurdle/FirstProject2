#include "stdafx.h"
#include "LXUI2.h"
#include "Visual.h"
//#include "WindowBase.h"

#include "ActionScript.h"

namespace System
{
using namespace ActionScripting;

namespace UI
{

DependencyProperty* Visual::s_EdgeModeProperty = RegisterProperty(WSTR("EdgeMode"), typeid(EdgeMode), typeid(Visual), IntObject::GetObject(EdgeMode_Unspecified), PropertyMetaData(None));

void VisualRenderCommand::Render(LDraw::GraphicsO* pGraphics)
{
	ASSERT(0);
#if 0
	UI::Graphics* graphics = new UI::Graphics(pGraphics);
//	graphics->m_invalidRegion = pGraphics->m_invalidRegion;
	m_pVisual->_OnRender2(graphics);
#endif
//	graphics->m_invalidRegion = NULL;
}

////////////////////////////////
// Visual

extern DepState* depstate;

Visual::Visual()
{
	m_bClip = true;
	m_bRetained = true;
	m_bRenderValid = false;

	m_bRegionValid = true;	// TODO, should be false
	m_bDrawsOutsideOpaqueRegion = true;

	m_pDrawCommands = NULL;

	m_Name = NULL;

	m_pScript = NULL;

	m_computedLeft = 0;
	m_computedTop = 0;

	m_depCookies.resize(depstate->gindex);//g_dependencyProperties.size());
}

Visual* Visual::GetRParent()
{
	return m_rparent;
}

void Visual::SetRParent(Visual* newVal)
{
#if 0
	ASSERT(m_rparent == NULL);
	if (m_rparent != NULL)
		THROW(-1);
#endif

	m_rparent = newVal;

	/*

  // TODO, not fully tested

	if (m_rparent)
		SetOwnerWindow(m_rparent->get_OwnerWindow());
	else
		SetOwnerWindow(NULL);
		*/
}

void Visual::AddVisualChild(Visual* visual)
{
	visual->SetRParent(this);
	visual->SetOwnerWindow(GetOwnerWindow());
}

void Visual::RemoveVisualChild(Visual* visual)
{
	if (visual->GetRParent() != this)
	{
		ASSERT(0);
		throw new Exception(WSTR("RemoveVisualChild: visual was not a child"));
	}

	visual->SetRParent(NULL);
	visual->SetOwnerWindow(NULL);
}

bool Visual::IsAncestorOf(DependencyObject* descendant)
{
	if (this == descendant) return false;

	Visual* v = dynamic_cast<Visual*>(descendant);	// TODO ??

	while (v)
	{
		v = v->GetRParent();
		if (this == v) return true;
	}

	return false;
}

Visual* Visual::FindVisualChildByName(StringW* name)
{
	ASSERT(0);
	return NULL;
}

unsigned int Visual::get_VisualChildrenCount()
{
	return 0;
}

Visual* Visual::GetVisualChild(unsigned int index)
{
	throw std::exception("index out of bounds");
	return NULL;
}

DependencyObject* Visual::get_VisualParent()
{
	return m_VisualParent;
}

double Visual::get_VisualOpacity()
{
	return 1.0;
}

Script* Visual::get_Script()
{
	return m_pScript;
}

void Visual::set_Script(Script* p)
{
	m_pScript = p;
}

StringW* Visual::get_Name() const
{
	return m_Name;
}

void Visual::set_Name(StringW* name)
{
//	printf("Visual::set_Name()\n");
	//fflush(stdout);
	m_Name = name;

//	StringA* str = m_Name->ToStringA();

	//printf("%s, done\n", str.c_str());
}

LDraw::SizeD Visual::get_ActualSize() const
{
	return m_computedSize;
}

EdgeMode Visual::get_EdgeMode()
{
	return (EdgeMode)static_cast<IntObject*>(GetValue(get_EdgeModeProperty()))->GetValue();
}

void Visual::set_EdgeMode(EdgeMode edgeMode)
{
	SetValue(get_EdgeModeProperty(), IntObject::GetObject(edgeMode));
}

Graphics* Visual::OpenDrawingContext(LDraw::GraphicsO* pGraphicsO)
{
	Graphics* pGraphics = new Graphics(new LDraw::GraphicsMetafile(pGraphicsO->m_device, pGraphicsO->m_bufferData, new LDraw::Commands));

	return pGraphics;
}

void Visual::CloseDrawingContext(Graphics* context)
{
	m_crit.Lock();

	if (dynamic_cast<UIElement*>(this))
	{
		m_pDrawCommands = new LDraw::Commands;

		{
			LDraw::SetClipRegionCommand* pCmd = new LDraw::SetClipRegionCommand(dynamic_cast<UIElement*>(this)->m_visibleRegion, LDraw::CombineModeIntersect);
		//	pCmd->m_pNext = dynamic_cast<LDraw::GraphicsMetafile*>(context->m_p)->m_pCommands->GetTail()->m_pNext;
			m_pDrawCommands->AddCommand(pCmd);
		}

		{
			LDraw::RenderCommandsCommand* pCmd = new LDraw::RenderCommandsCommand(dynamic_cast<LDraw::GraphicsMetafile*>(context->m_p)->m_pCommands);
			m_pDrawCommands->AddCommand(pCmd);
		}

		//pGraphics->IntersectClip(m_visibleRegion);
	}
	else
	{
		m_pDrawCommands = dynamic_cast<LDraw::GraphicsMetafile*>(context->m_p)->m_pCommands;
	}

	//m_bRenderValid = true;

	m_crit.Unlock();

	if (dynamic_cast<UIElement*>(this))
	{
		dynamic_cast<UIElement*>(this)->InvalidateRender();
	}

	// TODO, "invalidate" for a screen update
}

void Visual::SetRetainedMode(bool bRetained)
{
	m_bRetained = bRetained;
}

bool Visual::GetClipMode() const
{
	return m_bClip;
}

void Visual::SetClipMode(bool bClip)
{
	m_bClip = bClip;
}

void Visual::InvalidateRender()
{
	m_bRenderValid = false;

	if (true)
	{
		/*
		Visual* p = GetRParent();
		while (p)
		{
			p->m_bRenderValid = false;
			p = p->GetRParent();
		}
		*/

		if (GetOwnerWindow())
		{
			if (!m_bRedraw)
			{
#ifdef _DEBUG
				// Assert that we're not in the list

				Visual* pVisual = GetOwnerWindow()->m_redrawList;
				while (pVisual)
				{
					ASSERT(pVisual != this);
					pVisual = pVisual->m_redrawNext;
				}
#endif

				m_bRedraw = true;
				m_redrawNext = GetOwnerWindow()->m_redrawList;
				GetOwnerWindow()->m_redrawList = this;
			}
			else
			{
#ifdef _DEBUG

				// Assert that we're in the list

				Visual* pVisual = GetOwnerWindow()->m_redrawList;
				while (pVisual)
				{
					if (pVisual == this)
						break;

					pVisual = pVisual->m_redrawNext;
				}
				ASSERT(pVisual != NULL);
#endif
			}

			/*
			Visual* p = GetOwnerWindow()->get_VisualTree();

			if (!p->m_bRedraw)
			{
				p->m_bRedraw = true;
				p->m_redrawNext = GetOwnerWindow()->m_pSite->m_redrawList;
				GetOwnerWindow()->m_pSite->m_redrawList = p;
			}
			*/

			GetOwnerWindow()->m_pSite->InvalidateRegion(m_visibleRegion);
		}
		return;
	}

	Visual* p = GetRParent();
	while (p)
	{
		p->m_bRenderValid = false;
		/*
		if (p->m_Filter)
		{
			UIElement* v = p->m_Filter;
			while (v != p)
			{
				v->m_bRenderValid = false;
				v = v->GetRParent();
			}

		//	p->m_Filter->m_bRenderValid = false;
		}
		*/
		p = p->GetRParent();
	}

	if (GetOwnerWindow())
	{
		Visual* p = this;
		while (p)
		{
			if (!p->m_bDrawsOutsideOpaqueRegion)
			{
				break;
			}

			p = p->GetRParent();
		}

		if (p == NULL)
		{
			return;	// Means that the window hasn't been laid out yet
		}

		ASSERT(p);

		// If the element isn't already set to redraw, add it to a redraw list
		if (!p->m_bRedraw)
		{
			// If there's already a parent that's in the renderlist, don't add us as well
			Visual* p2 = p->GetRParent();
			while (p2)
			{
				if (p2->m_bRedraw) break;
				p2 = p2->GetRParent();
			}

			if (p2 == NULL)
			{
				p->m_bRedraw = true;

#ifdef _DEBUG
				{
					// Verify that it's not already in the list
					Visual* redrawList = GetOwnerWindow()->m_redrawList;
					Visual* p2 = redrawList;
					while (p2)
					{
						if (p == p2)
							break;
						p2 = p2->m_redrawNext;
					}

					ASSERT(p2 == NULL);
				}
#endif

				p->m_redrawNext = GetOwnerWindow()->m_redrawList;
				GetOwnerWindow()->m_redrawList = p;
			}
		}
		else
		{
#ifdef _DEBUG
			// Verify that it's in the list
			Visual* redrawList = GetOwnerWindow()->m_redrawList;
			Visual* p2 = redrawList;
			while (p2)
			{
				if (p == p2)
					break;
				p2 = p2->m_redrawNext;
			}

			ASSERT(p2 != NULL);
#endif
		}

		GetOwnerWindow()->m_pSite->InvalidateRegion(m_visibleRegion);
	}
	else
	{
	//	ASSERT(0);
#if 0
		WindowBase* pWindow = dynamic_cast<WindowBase*>(this);
		if (pWindow)
		{
			if (pWindow->m_pSite)
			{
				pWindow->m_bRedraw = true;
				pWindow->m_pSite->m_redrawList = pWindow;
				pWindow->m_pSite->InvalidateRegion(m_visibleRegion);
			}
		}
#endif
	}

	//InvalidateRender(m_expandedBBox);
}

void Visual::InvalidateRender(const LDraw::RectD &area)
{
	InvalidateRender();
#if 0

	m_bRenderValid = false;
	if (m_Filter)
	{
		UIElement* v = m_Filter;
		while (v != this)
		{
			v->m_bRenderValid = false;
			v = v->GetRParent();
		}
	}
	/*
	if (get_OwnerWindow())
	{
		get_OwnerWindow()->InvalidateRegion(&m_visibleRegion);
	}
	*/
	UIElement* p = dynamic_cast<UIElement*>(GetRParent());
	while (p)
	{
		p->m_bRenderValid = false;
		if (p->m_Filter)
		{
			UIElement* v = p->m_Filter;
			while (v != p)
			{
				v->m_bRenderValid = false;
				v = v->GetRParent();
			}

		//	p->m_Filter->m_bRenderValid = false;
		}
		p = p->GetRParent();
	}

	RenderChanged(area);
//	InvalidateRect(LDraw::RectD(0, 0, m_computedSize.Width, m_computedSize.Height));
#endif
}

void Visual::_OnRender(Graphics* pGraphics)
{
#if 0//AMIGA

		pGraphics->PushTransform();
		pGraphics->PushClip();

		_OnRender2(pGraphics);

		pGraphics->PopTransform();
		pGraphics->PopClip();

		return;

#endif
	//if (m_bRetained)
	{
		m_crit.Lock();

		if (!m_bRenderValid)
		{
			LDraw::GraphicsO* pGraphicsO = pGraphics->m_pO;
		//	VERIFY(pGraphicsO);

			if (m_pDrawCommands == NULL)
			{
				m_pDrawCommands = new LDraw::Commands;
			}
			else
			{
				m_pDrawCommands->Clear();
			}

			LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(pGraphicsO->m_device, pGraphicsO->m_bufferData, m_pDrawCommands);

#if 0
			LDraw::RectF clip = pGraphics->m_clip2;
			LDraw::GetTransformRectBoundingBox(pGraphics->GetTransform()->GetInverse(), clip, &clip);
			pMetafile->m_clip = new LDraw::Region(LDraw::Rect(clip.X, clip.Y, ceil(clip.Width), ceil(clip.Height)));
#endif

			LDraw::SizeD actualSize = get_ActualSize();

			if (actualSize.Width > 0 && actualSize.Height > 0)
			{
				if (m_bRetained)
				{
					Graphics* graphics = new Graphics(pMetafile);
					graphics->m_pO = pGraphics->m_pO;
				//	pMetafile->m_smoothingMode = pGraphics->GetSmoothingMode();
#if 0
					graphics->m_clip2 = clip;
					graphics->m_invalidRegion = pGraphics->m_invalidRegion;
#endif

					graphics->PushTransform();
					graphics->PushClip();

					_OnRender2(graphics);

					graphics->PopTransform();
					graphics->PopClip();

#if 0
					graphics->m_invalidRegion = NULL;
#endif
				}
				else
				{
					VisualRenderCommand* pCmd = new VisualRenderCommand;
					pCmd->m_pVisual = this;
					m_pDrawCommands->AddCommand(pCmd);
				}

			}

			m_bRenderValid = true;
		}

		m_crit.Unlock();

		if (pGraphics->m_p)
		{
			ASSERT(pGraphics->m_p);
			pGraphics->RenderCommands(m_pDrawCommands);
		}
	}
	/*
	else
	{
		_OnRender2(pGraphics);
	}
	*/
}

// virtual
void Visual::Render(Graphics* pGraphics)
{
	pGraphics->PushTransform();
//	LDraw::Matrix oldTransform = pGraphics->GetTransform();
	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();

	pGraphics->MultiplyTransform(m_transformMatrix);

#if 0
	if (m_LayoutTransform)
	{
		__release<LDraw::Matrix3f> layoutTransform = m_LayoutTransform->get_Value();

		LDraw::SizeD size = get_ActualSize();
		LDraw::RectD rc(0, 0, size.Width, size.Height);
		LDraw::RectD rect;
		LDraw::GetTransformRectBoundingBox(layoutTransform, rc, &rect);

		layoutTransform->Translate(-rect.X, -rect.Y, LDraw::MatrixOrderAppend);

		pGraphics->MultiplyTransform(layoutTransform);
	}
#endif

	EdgeMode edgeMode = get_EdgeMode();
	if (edgeMode != EdgeMode_Unspecified)
	{
		pGraphics->SetSmoothingMode(edgeMode == EdgeMode_AntiAliased? LDraw::SmoothingModeAntiAlias: LDraw::SmoothingModeNone);
	}

//	HRGN hRgn = ExtCreateRegion(NULL, 0, NULL);
//	HRGN hRgn = CreateRectRgn(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.GetRight(), m_expandedBBox.GetBottom());

#if 0//AMIGA

	LDraw::RectF oldclip = pGraphics->m_clip2;
	LDraw::RectF rect(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height);

	pGraphics->m_clip2 = LDraw::RectF::Intersect(pGraphics->m_clip2, rect, pGraphics->m_clip2);

	if (!pGraphics->m_clip2.IsEmpty())
	{
		_OnRender(pGraphics);
	}

	pGraphics->m_clip2 = oldclip;

#else

#if 0
	LDraw::RectF clip;
	pGraphics->GetClipBounds(&clip);

	LDraw::RectD xrect = m_expandedBBox;
	//GetTransformRectBoundingBox(pGraphics->m_transform, m_expandedBBox, &xrect);

	if (xrect.IntersectsWith(clip))
	{
#endif

#if 0
	LDraw::Rect invalidBounds;
	pGraphics->m_invalidRegion->GetRegionRect(&invalidBounds);
	ASSERT(!invalidBounds.IsEmpty());
#endif

//	LDraw::Rect elementBounds;
//	m_visibleWithChildrenRegion->GetRegionRect(&elementBounds);
	
//	if (!elementBounds.IsEmpty() && invalidBounds.IntersectsWith(elementBounds))
	{

	//	LDraw::Region oldClip;
	//	pGraphics->GetClip(&oldClip);
		pGraphics->PushClip();
		if (true)//m_bClip)
		{
#if 0
#if 1//AMIGA

			LDraw::Region* rgn = m_visibleRegion->GetIntersection(pGraphics->m_invalidRegion);

		//	if (dynamic_cast<UIElement*>(this))
			{
				pGraphics->IntersectClip(rgn/*dynamic_cast<UIElement*>(this)->m_visibleRegion*/);
			}
#else
			LDraw::Rect rect(m_expandedBBox.X, m_expandedBBox.Y, m_expandedBBox.Width, m_expandedBBox.Height);
			pGraphics->IntersectClip(rect);
#endif
#endif
		}

//		gmVector2 xpt = pGraphics->m_transform.transform(gmVector2(rect.X, rect.Y));

//		LDraw::RectD rect;
//		LDraw::RectD::Intersect(rect, m_expandedBBox, pGraphics->m_clip.m_clipBounds._RectD());

	// Clip away children
#if 0
		HRGN hRgn = CreateRectRgn(pGraphics->m_clip.m_clipBounds.X, pGraphics->m_clip.m_clipBounds.Y, pGraphics->m_clip.m_clipBounds.GetRight(), pGraphics->m_clip.m_clipBounds.GetBottom());

		// Clip away children
		{
			int size = get_rchildList().size();

			LDraw::RectF clip;
			pGraphics->GetClipBounds(&clip);

			for (int i = 0; i < size; i++)
			{
				UIElement* pElement = get_rchildList()[i];
				if (pElement->get_Visibility() == Visible)
				{
					if (clip.IntersectsWith(pElement->m_expandedBBoxParent))
					{
					//GetTransformRectBoundingBox(m_transform.inverse(), m_clip.m_clipBounds, bounds);

						pElement->Clip(pGraphics, hRgn);
					}
				}
			}
		}

		// Intersect with parent
		if (pGraphics->m_clip.m_hRgn)
		{
			RECT rect;
			GetRgnBox(pGraphics->m_clip.m_hRgn, &rect);
			CombineRgn(hRgn, hRgn, pGraphics->m_clip.m_hRgn, RGN_AND);

			GetRgnBox(pGraphics->m_clip.m_hRgn, &rect);
		}
#endif
	//	pGraphics->m_clip.m_hRgn = hRgn;

		if (m_Filter)		// ??
		{
			m_Filter->Render(pGraphics);
		}
		else
		{
			//LDraw::BBox rect;
		//	if (!pGraphics->IsClipEmpty())
			{
				_OnRender(pGraphics);
			}
		}

//		DeleteObject(hRgn);

	//	pGraphics->SetClip(&oldClip);
		pGraphics->PopClip();

	}
#endif

	pGraphics->SetSmoothingMode(oldSmoothingMode);
//	pGraphics->SetTransform(oldTransform);
	pGraphics->PopTransform();
}

#if 0
void Visual::dispatchEvent2(System::Event* evt, bool bCapture, bool *doDefault)
{
	if (m_pScript && m_pScript->m_root)
	{
		if (!bCapture)
		{
			map<StringA*, StkElt, Ref_Less<StringA>, System::__gc_allocator>::iterator it = m_pScript->m_root->m_variables.find(evt->get_type()->ToStringA());
			if (it != m_pScript->m_root->m_variables.end())
			{
				ActionScripting::StkElt & elt = (*it).second;
				if (elt.m_variant.kind == VARKIND_OBJECT)
				{
					ActionScripting::ActionScriptFunction* fun = dynamic_cast<ActionScripting::ActionScriptFunction*>(elt.m_variant.m_pObject);
					if (fun)
					{
						ActionScripting::VM vm;
						vm.m_global = this;

						ActionScripting::StackFrame* frame = new ActionScripting::StackFrame;
						
						/*
						frame->m_pContext = m_pScript->m_as_context;
						frame->m_instructionsData = fun->m_codeData;
						frame->m_instructionsLength = fun->m_codeLength;
						frame->m_variables[new StringA("this")] = this;
						

						vm.m_ctx = frame;
						vm.pc = frame->m_instructionsData;

						while (vm.next())
							;
							*/
						vm.push(evt);
						fun->dispatch(&vm, frame, 1);
					}
				}
			}
		}
	}

	handleEvent(evt);
	EventTargetImpl::dispatchEvent2(evt, bCapture, doDefault);
}
#endif

#if 0
// Overridables
void Visual::handleEvent(System::Event* evt)
{
}
#endif

}	// UI
}
