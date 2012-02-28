#include "stdafx.h"
#include "LSVG2.h"
#include "SVGScriptElement.h"

namespace System
{
namespace Web
{

SVGScriptElement::SVGScriptElement(NamedNodeMap* attributes) : SVGElement(new PSVGElement(this), attributes)
{
	SetAllValues(this);	// ??
}

String SVGScriptElement::get_type()
{
	return getAttribute(WSTR("type"));
}

void SVGScriptElement::set_type(StringIn newVal)
{
	setAttribute(WSTR("type"), newVal);
}

bool SVGScriptElement::dispatchEvent2(Event* evt, bool bCapture)
{
	String type = evt->get_type();

	DOMEventPhaseType phase = evt->get_eventPhase();

	if (phase == BUBBLING_PHASE)
	{
		if (type == L"DOMNodeInserted")
		{
			String textContent = get_textContent();

			m_pScript = new ecma::ScriptCode;
			m_pScript->AddText(textContent);

			ExecuteScript();
		}
	}

	if (phase == AT_TARGET)
	{
	// This element is added to the document tree
		if (type == L"DOMNodeInsertedIntoDocument")
		{

			/*
			LoadStyleSheet();

			if (m_styleSheet)
			{
				DocumentStyleImpl* documentStyle = dynamic_cast<DocumentStyleImpl*>(m_ownerDocument);
				if (documentStyle)
				{
					StyleSheetList* styleSheetList = documentStyle->get_styleSheets();

					styleSheetList->append(m_styleSheet);
				}
			}
			*/
		}
	// This element is removed from the document tree
		else if (type == L"DOMNodeRemovedFromDocument")
		{
			ASSERT(0);
		}
	}

	return EventTarget::dispatchEvent2(evt, bCapture);
}

void SVGScriptElement::ExecuteScript()
{
	JSVM::VM vm;
	vm.m_global = NULL;//m_element;

	ASSERT(m_ownerDocument->m_pWindow);
	if (m_ownerDocument->m_pWindow->m_pScriptGlobal == NULL)
	{
		m_ownerDocument->m_pWindow->m_pScriptGlobal = new JSVM::StackFrame;
	}

	JSVM::StackFrame* frame = m_ownerDocument->m_pWindow->m_pScriptGlobal;

	frame->m_pContext = m_pScript->m_as_context;
	frame->m_instructionsData = m_pScript->m_code.begin();
	frame->m_instructionsLength = m_pScript->m_code.size();
//	frame->m_variables[new StringA("this")] = this;
	
//	pFrame->m_return_pc = vm->m_pc;
//	pFrame->m_instructionsData = m_codeData;
//	pFrame->m_instructionsLength = m_codeLength;
//	ctx->m_constantPool = m_ctx->m_constantPool;	// inherited ?
	vm.m_pc = frame->m_instructionsData;
	vm.m_pFrame = frame;

//	vm.m_ctx = frame;
//	vm.pc = frame->m_instructionsData;

	while (vm.next())
		;

//	vm.push(evt);
//	fun->dispatch(&vm, frame, 1);
}

}	// Web
}	// System
