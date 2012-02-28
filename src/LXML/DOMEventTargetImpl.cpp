#include "stdafx.h"
#include "LXML2.h"
#include "DOMEventTargetImpl.h"
#include "Node.h"

#if 0
#include "LSVGShadowableImpl.h"
#endif
//#include "LHTMLWindow.h"
//#include "LBoxWindow.h"
//#include "LXMLDocumentView.h"

//#include "PElement.h"

namespace System
{
namespace Web
{

CLDOMEventTargetImpl::CListener::CListener()
{
	m_listener = NULL;
}

CLDOMEventTargetImpl::CListener::~CListener()
{
}

CLDOMEventTargetImpl::CLDOMEventTargetImpl()
{
}

CLDOMEventTargetImpl::~CLDOMEventTargetImpl()
{
//	ASSERT(m_listeners.GetCount() == 0);
}

EventTarget* CLDOMEventTargetImpl::GetParentEventTarget()
{
	Node* node = dynamic_cast<Node*>(this);
	if (node)
	{
		Node* parentNode = node->get_parentNode();
		EventTarget* eventTarget = dynamic_cast<EventTarget*>(parentNode);
		return eventTarget;
	}
	else
	{
		ASSERT(0);
#if 0
		CComQIPtr<ILSVGElementInstance> svgElementInstance = thisTarget;
		if (svgElementInstance)
		{
			CComPtr<ILSVGElementInstance> parentNode;
			svgElementInstance->get_parentNode(&parentNode);

			if (parentNode)
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = parentNode;
				*pVal = eventTarget.Detach();
			}
			else
			{
				CComPtr<ILSVGUseElement> useElement;
				svgElementInstance->get_correspondingUseElement(&useElement);

				CComQIPtr<ILDOMEventTarget> eventTarget = useElement;
				*pVal = eventTarget.Detach();
			}
		}
#endif
	}

	return NULL;
}

EventTarget::~EventTarget()
{
}

/////////////////////////////////////////////////////////////////////////////
// CLDOMEventTargetImplImpl

void CLDOMEventTargetImpl::addEventListener(StringIn type, Object/*ILDOMEventListener*/ *listener, bool useCapture)
{
	CListener* li = new CListener;
	li->m_listener = listener;
	li->m_type = type;
	li->m_useCapture = useCapture;

	m_listeners.push_back(li);
}

void CLDOMEventTargetImpl::addEventListenerNS(
		StringIn namespaceURI,
		StringIn type,
		Object* listener, 
		bool useCapture, 
		IEventListenerGroup* evtGroup)
{
	//TODO
	ASSERT(namespaceURI == nullptr);
	ASSERT(evtGroup == nullptr);

	addEventListener(type, listener, useCapture);
}

void CLDOMEventTargetImpl::removeEventListener(StringIn type, Object/*ILDOMEventListener*/ *listener, bool useCapture)
{
	ASSERT(0);
#if 0
	UPOSITION pos = m_listeners.GetHeadPosition();
	while (pos)
	{
		UPOSITION pos2 = pos;
		CListener* li = (CListener*)m_listeners.GetNext(pos);

		if ((li->m_listener == listener) &&
			(li->m_useCapture == useCapture) &&
			!tcscmp(li->m_type, type))
		{
			m_listeners.RemoveAt(pos2);
			delete li;
			return S_OK;
		}
	}

	return S_OK;
#endif
}

bool CLDOMEventTargetImpl::willTriggerNS(StringIn namespaceURI, StringIn type)
{
	ASSERT(0);
	return false;
}

bool CLDOMEventTargetImpl::hasEventListenerNS(StringIn namespaceURI, StringIn type)
{
	ASSERT(0);
	return false;
}

void CLDOMEventTargetImpl::capturePhase(Event* evt, bool* pdoDefault)
{
	evt->m_eventPhase = CAPTURING_PHASE;

	list<EventTarget*> ancestors;

	EventTarget* pParent = GetParentEventTarget();

	while (pParent != NULL)
	{
		ancestors.push_front(pParent);
		pParent = pParent->GetParentEventTarget();
	}

	list<EventTarget*>::iterator it = ancestors.begin();
	while (it != ancestors.end())
	{
		EventTarget* pTarget = (*it);//ancestors.GetNext(pos);

		*pdoDefault = pTarget->dispatchEvent2(evt, true);

		++it;
	}

//	ancestors.RemoveAll();
}

void CLDOMEventTargetImpl::bubblePhase(Event *evt, bool* pdoDefault)
{
	bool isPropagationStopped = evt->isPropagationStopped();
	if (isPropagationStopped)
	{
		return;
	}

	evt->m_eventPhase = BUBBLING_PHASE;

	list<EventTarget*> ancestors;

	EventTarget* pParent;
	pParent = GetParentEventTarget();
//	pNode->get_parentNode(&pParent);

	while (pParent != NULL)
	{
		ancestors.push_back(pParent);
		pParent = pParent->GetParentEventTarget();
	}

	list<EventTarget*>::iterator it = ancestors.begin();
	while (it != ancestors.end())
	{
		EventTarget* pTarget = (*it);

		*pdoDefault = pTarget->dispatchEvent2(evt, false);

		if (evt->isPropagationStopped())
		{
			break;
		}
		++it;
	}
}

// virtual
bool CLDOMEventTargetImpl::dispatchEvent2(Event* evt, bool bCapture)
{
#if 0	// Had this
	CComQIPtr<CLSVGShadowableImpl> shadowable = this;//GetUnknown();
	if (shadowable)
	{
		if (shadowable->m_shadowElement)
		{
			if (shadowable->m_elementDef)
			{
				CComQIPtr<ILDOMEventTarget> eventTarget = shadowable->m_elementDef;

			// Return here, not processing listeners on custom element?
				return static_cast<CLDOMEventTargetImplImpl*>(eventTarget.p)->dispatchEvent2(evt, bCapture, doDefault);
			}
		}
	}

	CComQIPtr<ILDOMUIEvent> uiEvt = evt;
	if (uiEvt)
	{
		CComPtr<ILDOMAbstractView> window;
		uiEvt->get_view(&window);
		if (window)	// TODO remove?
		{
			CComPtr<ILPresentation> pres;
			window->GetPresentation(&pres);

			if (CComQIPtr<CLDOMElementImplImpl>(this))
			{
				PElement* pPElement = (PElement*)CComQIPtr<CLDOMElementImplImpl>(this)->CheckNodeOnFrame(static_cast<CXMLDocumentView*>(pres.p));

				if (pPElement)
				{
					if (pPElement->m_bindNode)
					{
						CComQIPtr<ILDOMEventTarget> eventTarget = pPElement->m_behaviors[0]->m_elementDef;
				
					// Return here, not processing listeners on custom element?
						return static_cast<CLDOMEventTargetImplImpl*>(eventTarget.p)->dispatchEvent2(evt, bCapture, doDefault);
					}
				}
			}
		}
	}
#endif

	String eventType = evt->get_type();

	list<CListener*>::iterator pos = m_listeners.begin();
	while (pos != m_listeners.end())
	{
		CListener* li = *pos;

		if (li->m_type == eventType &&
			(bCapture == li->m_useCapture))
		{
			IEventListener* listener = dynamic_cast<IEventListener*>(li->m_listener);
			if (listener)
			{
				listener->handleEvent(evt);
			}
			else
			{
				ASSERT(0);
#if 0
#if _WINDOWS
				CComQIPtr<IDispatch, &IID_IDispatch> displistener = (IUnknown*)li->m_listener;

				if (displistener)
				{
					DISPPARAMS dispparams;
					VARIANTARG varargs[1];
					dispparams.cArgs = 1;
					dispparams.cNamedArgs = 0;
					dispparams.rgvarg = varargs;

					V_VT(&dispparams.rgvarg[0]) = VT_DISPATCH;
					V_DISPATCH(&dispparams.rgvarg[0]) = evt;

					OLECHAR* names[1] =
					{
						OLESTR("handleEvent"),
					};

					DISPID dispid;
					HRESULT hr = displistener->GetIDsOfNames(IID_NULL, names, 1, LOCALE_SYSTEM_DEFAULT, &dispid);
					if (SUCCEEDED(hr))
					{
						hr = displistener->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
							&dispparams, 0, 0, 0);
					}
					else
					{
						dispid = 0;
						hr = displistener->Invoke(dispid, IID_NULL, LOCALE_SYSTEM_DEFAULT, DISPATCH_METHOD,
							&dispparams, 0, 0, 0);
					}
				}
				else
					ASSERT(0);
#endif	// _WINDOWS
#endif
			}
		}

		++pos;
	}

	return true;
}

bool EventTarget::dispatchEvent(Event* evt)
{
	ASSERT(evt != NULL);
	if (evt == NULL) throw std::exception("null pointer");

#if 0
	CComQIPtr<CLDOMEventImplImpl, &IID_IUnknown/*TODO*/> evtImpl = evt;
	if (evtImpl == NULL)
		return E_INVALIDARG;
#endif

	evt->m_target = this;

	bool doDefault = true;

// Capturing
	capturePhase(evt, &doDefault);

// At target phase
	evt->m_eventPhase = AT_TARGET;
	doDefault = dispatchEvent2(evt, false);

// Bubble phase
	if (evt->get_bubbles())
	{
		bubblePhase(evt, &doDefault);
	}

	bool isDefaultPrevented = evt->isDefaultPrevented();
	doDefault = isDefaultPrevented? false: true;

	return doDefault;
}

}
}
