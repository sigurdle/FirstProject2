#include "stdafx.h"
#include "LSVG.h"

namespace System
{
namespace Web
{

Gui::DependencyClass* SVGVisual::get_Class()
{
	static Gui::DependencyClass depclass(typeid(SVGVisual), Gui::FrameworkElement::get_Class());

	/*
	static Gui::DependencyProperty* properties[] =
	{
	};
	*/

	return &depclass;
}

Gui::DependencyClass* SVGVisual::pClass(get_Class());

//list<SVGVisual*> arrangeList;

SVGVisual::SVGVisual() : Gui::FrameworkElement(get_Class())
{
}

void SVGVisual::Load(StringIn url)
{
	Web::CHTMLWindow* svgwindow;

	svgwindow = new Web::CHTMLWindow;
	svgwindow->m_ownerVisual = this;

	Web::SVGDocument* svgdocument = new Web::SVGDocument();
	svgdocument->m_pWindow = svgwindow;

	svgdocument->load(url);

	Web::SVGSVGElement* svgelement = dynamic_cast<Web::SVGSVGElement*>(svgdocument->get_documentElement());
	if (svgelement == NULL)
	{
		raise(Exception("no svg element"));
	}
	Web::PSVGSVGElement* psvgelement = dynamic_cast<Web::PSVGSVGElement*>(svgelement->m_pNode);

	svgwindow->m_htmTree = psvgelement;

	/*
	for (int i = 0; i < svgelement->get_childNodes()->get_length(); i++)
	{
		w3c::Node* child = svgelement->get_childNodes()->item(i);
		psvgelement->m_rchildList.push_back(child->m_pNode);
	}
	*/

	psvgelement->GetCSSPropertiesAndChildren();
//	psvgelement->BuildRenderableChildren();
	psvgelement->SetViewportElement(NULL);
	psvgelement->CalculateBoundsAndChildren();

	this->m_window = svgwindow;
	this->m_document = svgdocument;
	this->m_svgelement = svgelement;
	this->m_psvgelement = psvgelement;
}

void SVGVisual::SetDocument(Web::SVGDocument* svgdocument)
{
	CHTMLWindow* svgwindow;

	svgwindow = new CHTMLWindow;
	svgwindow->m_ownerVisual = this;
	svgdocument->m_pWindow = svgwindow;

//	svgdocument->load(WSTR("../../../TestFiles/image.svg"));
//	svgdocument->load(WSTR("D:/Users/Sigurd/Documents/VSProjects/MMStudio/TestFiles/image.svg"));

	Web::SVGSVGElement* svgelement = dynamic_cast<SVGSVGElement*>(svgdocument->get_documentElement());
	Web::PSVGSVGElement* psvgelement = dynamic_cast<PSVGSVGElement*>(svgelement->m_pNode);

	svgwindow->m_htmTree = psvgelement;

	/*
	for (int i = 0; i < svgelement->get_childNodes()->get_length(); i++)
	{
		w3c::Node* child = svgelement->get_childNodes()->item(i);
		psvgelement->m_rchildList.push_back(child->m_pNode);
	}
	*/

	psvgelement->GetCSSPropertiesAndChildren();
//	psvgelement->BuildRenderableChildren();
	psvgelement->CalculateBoundsAndChildren();

	this->m_window = svgwindow;
	this->m_document = svgdocument;
	this->m_svgelement = svgelement;
	this->m_psvgelement = psvgelement;

//		window->set_Content(svgVisual);
}

void SVGVisual::Render(Gui::ManagedRenderContext renderContext)
{
	CHTMRenderContext ctx;
	ctx.m_renderContext = renderContext.m_p;
	m_psvgelement->Render(&ctx, renderContext.m_p, 1.0, 1.0);
}

void SVGVisual::DoLayout()
{
	gm::SizeD finalSize(get_ActualWidth(), get_ActualHeight());
	m_window->ArrangeOverride(finalSize);
}

void SVGVisual::DoLayoutSize(gm::SizeF size)
{
	m_psvgelement->m_boundsValid = false;
	m_psvgelement->CalculateBoundsAndChildren();

//	m_window->ArrangeOverride(size);
}

void SVGVisual::OnLeftMouseButtonDown(Gui::MouseButtonEventArgs* args)
{
	Gui::Point mousepos = args->GetPosition(this);

	PSVGElement* pElement;
	pElement = m_psvgelement->HitTestElement(gm::Matrix3d::GetIdentity(), gm::PointD(mousepos.X, mousepos.Y));

	if (pElement)
	{
		EventTarget* target = dynamic_cast<EventTarget*>(pElement->m_pNode);
		EventTarget* relatedTarget = dynamic_cast<EventTarget*>(m_psvgelement->m_pNode);

		gm::PointF screenpt;
		gm::PointF clientpt = mousepos;
		UINT nFlags = 0;
		bool m_bAlt = false;
		int iButton = 0;

		//IDocumentEvent* documentEvent = dynamic_cast<IDocumentEvent*>(m_document);

		MouseEvent* mouseevt = static_cast<MouseEvent*>(m_document->createEvent(WSTR("MouseEvents")));
		mouseevt->initMouseEvent(L"mousedown",
			true,	// bubbles
			true,	// cancelable
			m_window,	// viewArg
			0,		// detail
			screenpt.X, screenpt.Y,	// screen
			clientpt.X, clientpt.Y, // client,
			(nFlags & MK_CONTROL)? true: false,
			(nFlags & MK_SHIFT)? true: false,
			(m_bAlt)? true: false,
			0,	// meta
			iButton,
			relatedTarget
			);

		bool doDefault = target->dispatchEvent(mouseevt);
		if (doDefault)
		{
		}
	}
}

}	// Web
}	// System
