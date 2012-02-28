#include "stdafx.h"
#include "XSLT.h"

namespace System
{
namespace XSLT
{

static ImmutableString<WCHAR> xsl_namespaceURI(L"http://www.w3.org/1999/XSL/Transform");

Web::Element* cloneElement(Web::Document* resultDocument, Web::Element* element)
{
	String namespaceURI = element->get_namespaceURI();
	String localName = element->get_localName();

	Web::Element* newElement = (Web::Element*)resultDocument->createElementNS(namespaceURI, localName);
	if (newElement)
	{
		// Clone attributes
		Web::NamedNodeMap* attributes = element->get_attributes();
		Web::NamedNodeMap* newAttributes = newElement->get_attributes();

		unsigned int nattrs = attributes->get_length();

		for (unsigned int i = 0; i < nattrs; ++i)
		{
			Web::Attr* attr = (Web::Attr*)attributes->item(i);

			String namespaceURI = attr->get_namespaceURI();
			String localName = attr->get_localName();

			String value = attr->get_value();

			// TODO
			// attribute value template

			Web::Attr* newAttr = (Web::Attr*)resultDocument->createAttributeNS(namespaceURI, localName);
			newAttr->set_value(value);

			newAttributes->setNamedItem(newAttr);
		}
	}

	return newElement;
}

Document::Document(Web::Document* xsltDocument)
{
	m_xsltDocument = xsltDocument;

	Web::Element* element = m_xsltDocument->get_documentElement();

	Web::Node* child = element->get_firstChild();

	while (child)
	{
		if (child->get_nodeType() == Web::NODE_ELEMENT)
		{
			Web::Element* childelement = static_cast<Web::Element*>(child);

			String namespaceURI = childelement->get_namespaceURI();
			if (namespaceURI == String(&xsl_namespaceURI))
			{
				String localName = childelement->get_localName();
				if (localName == L"template")
				{
					String match = childelement->getAttribute(L"match");
					if (match != L"/")
					{
						Template* pTemplate = new Template;
						pTemplate->m_element = childelement;

						XPath::XPathEvaluator xpatheval;
						pTemplate->m_matchExp = xpatheval.createExpression(match, NULL);

						m_templates.push_back(pTemplate);
					}
				}
			}
		}

		child = child->get_nextSibling();
	}
}

Web::Element* Document::evaluateLiteral(Web::Document* resultDocument, Web::Element* literalElement, XDM::IData* contextNode)
{
	Web::Element* resultElement = cloneElement(resultDocument, literalElement);

	/*
	Web::Node* childnode = literalElement->get_firstChild();
	while (childnode)
	{
		if (childnode->get_nodeType() == Web::LNODE_ELEMENT)
		{
			Web::Element* childelement = static_cast<Web::Element*>(childnode);

			StringW* namespaceURI = childelement->get_namespaceURI();
			if (*namespaceURI == *xsl_namespaceURI)	// xsl namespace
			{
			}
		}

		childnode = childnode->get_nextSibling();
	}
	*/

	Sequence* seq = evaluate(resultDocument, literalElement, contextNode);

	for (uint i = 0; i < seq->m_items.size(); ++i)
	{
		SequenceItem* item = seq->m_items[i];
		if (item->m_node->get_nodeType() == Web::NODE_ATTRIBUTE)
		{
			resultElement->setAttributeNodeNS((Web::Attr*)item->m_node);
		}
		else if (item->m_node->get_nodeType() == Web::NODE_COMMENT)
		{
			resultElement->appendChild(item->m_node);
		}
		else if (item->m_node->get_nodeType() == Web::NODE_TEXT)
		{
			resultElement->appendChild(item->m_node);
		}
		else if (item->m_node->get_nodeType() == Web::NODE_ELEMENT)
		{
			resultElement->appendChild(item->m_node);
		}
		else
			ASSERT(0);
	}

	return resultElement;
}

String Document::SimpleContent(Web::Document* resultDocument, Web::Element* childelement, XDM::IData* contextNode)
{
	String select = childelement->getAttribute(L"select");
	Web::Node* firstChild = childelement->get_firstChild();

	String stringValue = NULL;

	if (select != NULL || firstChild != NULL)
	{
		Sequence* seq;

		if (select != NULL)
		{
		// [ERR XTSE0840] It is a static error if the select attribute of the xsl:attribute element is present unless the element has empty content.
			// TODO, do this earlier
			if (firstChild != NULL)
				THROW(-1);

			XPath::XPathEvaluator xpatheval;
			XPath::XPathExpression* xpathExp = xpatheval.createExpression(select, NULL);

			XPath::XPathResult* xpathResult = xpathExp->evaluate(contextNode, XPath::ANY_TYPE, NULL);

			seq = new Sequence;
			if (xpathResult->m_result->m_kind == XPath::ExprResult::K_NODELIST)
			{
				for (unsigned int i = 0; i < xpathResult->m_result->m_nodeList->m_items.size(); ++i)
				{
					XPath::DataItem dataitem = xpathResult->m_result->m_nodeList->m_items[i];
					ASSERT((dataitem.m_attributeIndex & 1) == 1);

					Variant value = dataitem.m_data->getAttributeValue(dataitem.m_attributeIndex>>1);
					String textvalue = value.ToString();

					if (textvalue)
					{
						Web::Text* node = resultDocument->createTextNode(textvalue);

						seq->m_items.push_back(new SequenceItem(node));
					}
				}
			}
			else if (xpathResult->m_result->m_kind == XPath::ExprResult::K_STRING)
			{
				Web::Text* node = resultDocument->createTextNode(xpathResult->m_result->m_stringValue);

				seq->m_items.push_back(new SequenceItem(node));
			}
			else if (xpathResult->m_result->m_kind == XPath::ExprResult::K_BOOL)
			{
				//???

				Web::Text* node = resultDocument->createTextNode(L"true");

				seq->m_items.push_back(new SequenceItem(node));
			}
			else
				ASSERT(0);
		}
		else
		{
			// sequence constructor
			seq = evaluate(resultDocument, childelement, contextNode);
		}

		// Constructing simple content

	//	BufferImp<WCHAR> buffer;
	//	StringBuilderW stream(&buffer);
	//	String stringValue;

		for (size_t i = 0; i < seq->m_items.size(); ++i)
		{
			SequenceItem* item = seq->m_items[i];

			if (item->m_node)
			{
				if (item->m_node->get_nodeType() == Web::NODE_TEXT)
				{
					stringValue += item->m_node->get_textContent();
				}
				else
					ASSERT(0);
			}
			else
			{
				ASSERT(0);
				/*
				StringW* str;

				if (item->m_dataitem.m_attributeIndex & 1)
					str = item->m_dataitem.m_data->getAttributeValue(item->m_dataitem.m_attributeIndex>>1);
				else
					ASSERT(0);

				stream << *str;
				*/
			}
		}

		//stringValue = buffer.DetachToString();
	}
	else
	{
	// If neither is present, the value of the new attribute node will be a zero-length string
	//	static ImmutableString<WCHAR> str(L"");
		stringValue = L"";
	}

	return stringValue;
}

// Evaluate sequence constructor
Sequence* Document::evaluate(Web::Document* resultDocument, Web::Element* templateRule, XDM::IData* contextNode)
{
	Sequence* resultseq = new Sequence;

	uint nchild = 0;
	Web::Node* childnode = templateRule->get_firstChild();
	while (childnode)
	{
		if (childnode->get_nodeType() == Web::NODE_TEXT)
		{
			Web::Node* node2 = childnode->cloneNodeExport(resultDocument, true);

			resultseq->m_items.push_back(new SequenceItem(node2));
		}
		else if (childnode->get_nodeType() == Web::NODE_ELEMENT)
		{
			Web::Element* childelement = static_cast<Web::Element*>(childnode);

			String namespaceURI = childelement->get_namespaceURI();
			if (namespaceURI == String(&xsl_namespaceURI))
			{
				String localName = childelement->get_localName();
				if (localName == L"call-template")
				{
					String name = childelement->getAttribute(L"name");
					if (name == NULL)
					{
						THROW(-1);
					}

					size_t j;
					for (j = 0; j < m_templates.size(); ++j)
					{
						Template* pTemplate = m_templates[j];

						String name2 = pTemplate->m_element->getAttribute(L"name");
						if (name2)
						{
							if (name2 == name)
							{
								break;
							}
						}
					}

					ASSERT(j < m_templates.size());
					Template* pTemplate = m_templates[j];

					Sequence* tseq = evaluate(resultDocument, pTemplate->m_element, contextNode);
					for (size_t i = 0; i < tseq->m_items.size(); ++i)
					{
						resultseq->m_items.push_back(tseq->m_items[i]);
					}
				}
				else if (localName == L"apply-templates")
				{
					String select = childelement->getAttribute(L"select");
					if (select == NULL)
					{
						static ImmutableString<WCHAR> str(L"child::node()");
						select = &str;//WSTR("child::node()");	// Default if there is no select attribute
					}

					XPath::XPathEvaluator xpatheval;
					XPath::XPathExpression* xpathExp = xpatheval.createExpression(select, NULL);

					XPath::XPathResult* xpathResult = xpathExp->evaluate(contextNode, XPath::ANY_TYPE, NULL);

					if (xpathResult->m_result->m_kind == XPath::ExprResult::K_NODELIST)
					{
						// Each node in the input sequence is processed by finding a template rule whose pattern matches that node

						for (size_t i = 0; i < xpathResult->m_result->m_nodeList->m_items.size(); ++i)
						{
							XPath::DataItem dataitem = xpathResult->m_result->m_nodeList->m_items[i];

							ASSERT((dataitem.m_attributeIndex & 1) == 0);
							XDM::IData* ctxnode = dataitem.m_data->getChildElement(dataitem.m_attributeIndex>>1);

							if (ctxnode)
							{
								size_t j;
								for (j = 0; j < m_templates.size(); ++j)
								{
									Template* pTemplate = m_templates[j];

									if (pTemplate->m_matchExp->evaluateContaining(ctxnode))
									{
										break;
									}
								//	Web::XPathResult* xpathResult = pTemplate->m_matchExp->evaluate(ctxnode, Web::ANY_TYPE, NULL);
								}

								if (j == m_templates.size())
								{
									Std::Out << ctxnode->GetObject()->GetType()->get_QName();

									size_t j;
									for (j = 0; j < m_templates.size(); j++)
									{
										Template* pTemplate = m_templates[j];

										if (pTemplate->m_matchExp->evaluateContaining(ctxnode))
										{
											break;
										}
									//	Web::XPathResult* xpathResult = pTemplate->m_matchExp->evaluate(ctxnode, Web::ANY_TYPE, NULL);
									}
								}

								Template* pTemplate = m_templates[j];

								Sequence* tseq = evaluate(resultDocument, pTemplate->m_element, ctxnode);
								for (size_t i = 0; i < tseq->m_items.size(); ++i)
								{
									resultseq->m_items.push_back(tseq->m_items[i]);
								}
							}
						}
					}
					else
					{
						ASSERT(0);
						THROW(-1);
					}
				}
				else if (localName == L"if")
				{
					String test = childelement->getAttribute(L"test");
					if (test == NULL)
						THROW(-1);

					XPath::XPathEvaluator xpatheval;
					XPath::XPathExpression* xpathExp = xpatheval.createExpression(test, NULL);

					XPath::XPathResult* xpathResult = xpathExp->evaluate(contextNode, XPath::ANY_TYPE, NULL);

					bool truth = XPath::xpath_boolean(xpathResult->m_result);

					if (truth)
					{
						Sequence* tseq = evaluate(resultDocument, childelement, contextNode);

						for (size_t i = 0; i < tseq->m_items.size(); ++i)
						{
							resultseq->m_items.push_back(tseq->m_items[i]);
						}
					}
				}
				else if (localName == L"for-each")
				{
					String select = childelement->getAttribute(L"select");
					if (select == NULL)
						THROW(-1);

					XPath::XPathEvaluator xpatheval;
					XPath::XPathExpression* xpathExp = xpatheval.createExpression(select, NULL);

					XPath::XPathResult* xpathResult = xpathExp->evaluate(contextNode, XPath::ANY_TYPE, NULL);

/*
The xsl:for-each instruction contains a sequence constructor. The sequence constructor is evaluated once for each item in the sorted sequence, with the focus set as follows:

The context item is the item being processed. If this is a node, it will also be the context node. If it is not a node, there will be no context node: that is, any attempt to reference the context node will result in a non-recoverable dynamic error.

The context position is the position of this item in the sorted sequence.

The context size is the size of the sorted sequence (which is the same as the size of the input sequence).


*/
					for (size_t i = 0; i < xpathResult->m_result->m_nodeList->m_items.size(); ++i)
					{
						XPath::DataItem dataitem = xpathResult->m_result->m_nodeList->m_items[i];

						ASSERT((dataitem.m_attributeIndex & 1) == 0);
						XDM::IData* ctxnode = dataitem.m_data->getChildElement(dataitem.m_attributeIndex>>1);
						Sequence* tseq = evaluate(resultDocument, childelement, ctxnode);

						for (size_t j = 0; j < tseq->m_items.size(); j++)
						{
							resultseq->m_items.push_back(tseq->m_items[j]);
						}
					}
				}
				else if (localName == L"attribute")
				{
					String name = childelement->getAttribute(L"name");
					if (name == NULL)	// name is required
						THROW(-1);

					String namespaceURI = childelement->getAttribute(L"namespace");

				// [ERR XTDE0855] In the case of an xsl:attribute instruction with no namespace attribute, it is a non-recoverable dynamic error if the effective value of the name attribute is the string xmlns.

					if (namespaceURI == NULL)
					{
						if (name == L"xmlns")
							THROW(-1);
					}

				// TODO
				// The name attribute is interpreted as an attribute value template, whose effective value must be a lexical QName.
					String qname = name;

				// [ERR XTDE0850] It is a non-recoverable dynamic error if the effective value of the name attribute is not a lexical QName.

				// [ERR XTDE0860] In the case of an xsl:attribute instruction with no namespace attribute, it is a non-recoverable dynamic error if the effective value of the name attribute is a lexical QName whose prefix is not declared in an in-scope namespace declaration for the xsl:attribute instruction.

					String effectiveValue = SimpleContent(resultDocument, childelement, contextNode);

					Web::Attr* attr = resultDocument->createAttributeNS(namespaceURI, qname);
					attr->set_value(effectiveValue);

					resultseq->m_items.push_back(new SequenceItem(attr));
				}
				else if (localName == L"value-of")
				{
					String textContent = SimpleContent(resultDocument, childelement, contextNode);

					Web::Text* text = resultDocument->createTextNode(textContent);

					resultseq->m_items.push_back(new SequenceItem(text));
				}
				else if (localName == L"comment")
				{
					String textContent = SimpleContent(resultDocument, childelement, contextNode);

					Web::Comment* comment = resultDocument->createComment(textContent);

					resultseq->m_items.push_back(new SequenceItem(comment));
				}
				else if (localName == L"processing-instruction")
				{
					ASSERT(0);

					String target = NULL;
					String data = NULL;

					Web::ProcessingInstruction* pi = resultDocument->createProcessingInstruction(target, data);
				}
				else if (localName == L"text")
				{
					/*
						<xsl:text
						  [disable-output-escaping]? = "yes" | "no">
						  <!-- Content: #PCDATA -->
						</xsl:text>
					*/
					String textContent = childelement->get_textContent();

					Web::Text* text = resultDocument->createTextNode(textContent);
					resultseq->m_items.push_back(new SequenceItem(text));
				}
				else
					ASSERT(0);
			}
			else	// Literal
			{
				Web::Element* element = evaluateLiteral(resultDocument, childelement, contextNode);

			//	fragment->appendChild(element);
				resultseq->m_items.push_back(new SequenceItem(element));
			}
		}
		else
			ASSERT(0);

		childnode = childnode->get_nextSibling();
		++nchild;
	}

	return resultseq;
}

Web::DocumentFragment* Document::transform(Web::Document* resultDocument, Web::Element* templateRule, XDM::IData* contextNode)
{
	Sequence* seq = evaluate(resultDocument, templateRule, contextNode);

	for (size_t i = 0; i < seq->m_items.size(); ++i)
	{
		SequenceItem* item = seq->m_items[i];

		resultDocument->appendChild(item->m_node);
	}

	return NULL;
}

}	// XSLT
}	// System
