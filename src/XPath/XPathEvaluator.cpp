#include "stdafx.h"
#include "XPath.h"

#include "XPathEvaluator.h"

#include "XPathExpression.h"
#if 0
#include "XPathNSResolver.h"
#endif

#include "XPath.h"

namespace System
{
namespace XPath
{
extern System::ImmutableString<wchar_t> star_str;

#include "xpath_parse.tab.h"
struct yy_buffer_state;

yy_buffer_state* xpath__scan_string(const char* str);
void xpath__switch_to_buffer(yy_buffer_state*);
void xpath__load_buffer_state();
/*
void cpp_exp_switch_to_buffer(yy_buffer_state*);
int cpp_exp_lex();
*/

char* get_buf_p();

int xpath_parse();

Exp* g_exp;
extern int xpath_char;
}
}

struct yy_buffer_state;

int XPathExt xpath_parse(char* p, char **pp, int* ptoken)
{
	System::XPath::yy_buffer_state* state = System::XPath::xpath__scan_string(p);
	int error = System::XPath::xpath_parse();

	System::XPath::Exp* exp = System::XPath::g_exp;

	int token = System::XPath::xpath_char;
	char* p2 = System::XPath::get_buf_p();

	*pp = p2;
	*ptoken = token;

	return error;
}

int XPathExt xpath_parse(yy_buffer_state* b)
{
	System::XPath::xpath__switch_to_buffer((System::XPath::yy_buffer_state*) b );
	//System::XPath::xpath__load_buffer_state();
	int error = System::XPath::xpath_parse();

	return error;
}

/*
extern "C" LFCEXT long invoke_function(ULONG_PTR func, const void* args, long sz);
extern "C" LFCEXT long invoke_method(ULONG_PTR func, void* _this, const void* args, long sz);
*/

namespace System
{
namespace XPath
{

//Web::NodeList* match(AxisStep* pStep, Web::NodeList* nodeList);

BinopExp::BinopExp(Exp* left, int op, Exp* right)
{
	kind = K_BINOP;
	m_op = op;
	m_left = left;
	m_right = right;
}

UnopExp::UnopExp(Exp* exp, int op)
{
	kind = K_UNOP;
	m_op = op;
	m_exp = exp;
}

PathExp::PathExp(StepList* path)
{
	kind = Exp::K_PATH;
	m_path = path;
}

Exp* NumberExp(double number)
{
	Exp* p = new Exp;
	p->kind = Exp::K_NUMBER;
	p->number = number;
	return p;
}

void evaluate(Exp* exp)
{
	switch (exp->kind)
	{
	case Exp::K_BINOP:
		{
			ASSERT(0);
		}
		break;

	case Exp::K_UNOP:
		{
			ASSERT(0);
		}
		break;
	}
}

#if 0
struct Axis
{
	union
	{
		struct
		{
			Node* cur;
		}
		child;

		struct
		{
			int cur;
		}
		child;

		struct
		{
			Node* cur;
		}
		ancestor;

		struct
		{
			Node* cur;
		}
		ancestor_or_self;
	};
};
#endif

/*
StringW* expandedName(const Node* node)
{
	return node->get_nodeName();
}
*/

XPathExt bool xpath_boolean(ExprResult* obj)
{
	switch (obj->m_kind)
	{
	case ExprResult::K_NODELIST:
		{
			return obj->m_nodeList->m_items.size() > 0;
		}
		break;

	case ExprResult::K_NUMBER:
		{
			return fabs(obj->m_numberValue) >= 0.000000001;
		}
		break;

	case ExprResult::K_BOOL:
		{
			return obj->m_boolValue;
		}
		break;

	case ExprResult::K_STRING:
		{
			return obj->m_stringValue->GetLength() > 0;
		}
		break;

	default:
		ASSERT(0);
		return false;
	}
}

#if 0
void GetAxisNodes(int axis, Web::Node* contextNode, Web::NodeList* nodeList)
{
	switch (axis)
	{
	case AxisStep::K_CHILD:
		{
			for (int i = 0; i < contextNode->get_childNodes()->get_length(); i++)
			{
				nodeList->m_items.Add(contextNode->get_childNodes()->item(i));
			}
		}
		break;

	case AxisStep::K_ATTRIBUTE:
		{
			if (contextNode->get_attributes())
			{
				for (int i = 0; i < contextNode->get_attributes()->get_length(); i++)
				{
					nodeList->m_items.Add(contextNode->get_attributes()->item(i));
				}
			}
		}
		break;

	case AxisStep::K_PARENT:
		{
			if (contextNode->get_parentNode())
			{
				nodeList->m_items.Add(contextNode->get_parentNode());
			}
		}
		break;

	case AxisStep::K_ANCESTOR:
		{
			Node* parentNode = contextNode->get_parentNode();
			while (parentNode)
			{
				nodeList->m_items.Add(parentNode);
				parentNode = parentNode->get_parentNode();
			}
		}
		break;

	case AxisStep::K_ANCESTOR_OR_SELF:
		{
			Node* node = contextNode;
			while (node)
			{
				nodeList->m_items.Add(node);
				node = node->get_parentNode();
			}
		}
		break;

	case AxisStep::K_DESCENDANT:
		{
			for (int i = 0; i < contextNode->get_childNodes()->get_length(); i++)
			{
				Node* node = node->get_childNodes()->item(i);
				nodeList->m_items.Add(node);
				GetAxisNodes(axis, node, nodeList);	// Recurse
			}
		}
		break;

#if 0
	case Step::K_DESCENDANT_OR_SELF:
		{
			for (int i = 0; i < contextNode->get_childNodes->get_length(); i++)
			{
				Node* node = node->get_childNodes()->item(i);
				nodeList->m_items.Add(node);
				GetAxisNodes(axis, node, nodeList);	// Recurse
			}
		}
		break;

	case AxisStep::K_FOLLOWING:
		{
		}
		break;

	case AxisStep::K_FOLLOWING_SIBLING:
		{
		}
		break;

	case AxisStep::K_NAMESPACE:
		{
		}
		break;
#endif

	default:
		ASSERT(0);
	}
}
#endif

bool AxisIterator::AtEnd()
{
	return m_contextPos == m_contextSize;
}

bool AxisIterator::Iterate()
{
	if (m_contextPos < m_contextSize)
	{
		++m_contextPos;
		return true;
	}

	return false;
}

DataItem AxisIterator::GetItem()
{
	if (m_axis == AxisStep::K_ATTRIBUTE)
		return DataItem(m_contextParentItem, (m_contextPos<<1) | 1);
	else
		return DataItem(m_contextParentItem, (m_contextPos<<1));
}

bool TestNodeName(QName* qname, DataItem& item)
{
	if (qname == NULL)	// '*'
		return true;

	if (qname->m_ns != L"*")
	{
		String ns;
		if (item.m_attributeIndex & 1)
			ns = item.m_data->getAttributeNamespaceURI(item.m_attributeIndex>>1);
		else
			ns = item.m_data->getChildNamespaceURI(item.m_attributeIndex>>1);

		if (ns != qname->m_ns)
			return false;
	}

	if (qname->m_local != L"*")
	{
		String local;
		if (item.m_attributeIndex & 1)
			local = item.m_data->getAttributeName(item.m_attributeIndex>>1);
		else
			local = item.m_data->getChildName(item.m_attributeIndex>>1);

		if (*local != *qname->m_local)
			return false;
	}

	return true;
}

bool TestNode(NodeTest* nodeTest, DataItem& item)
{
	if (nodeTest->kind == NodeTest::K_NAMETEST)
	{
		return TestNodeName(nodeTest->m_qname, item);
	}
	else
	{
	//	char buf[600];
	//	sprintf_s(buf, "System::%S", nodeTest->ElementTest.m_typename->m_local->c_str());
		String name = L"System::" + nodeTest->ElementTest.m_typename->m_local;
		NamedType* pType = TypeDatabase::pD->LookupNamedType(name);

		ASSERT(pType->AsClass());

		ASSERT((item.m_attributeIndex & 1) == 0);
		//XDM::IData* data = item.m_data->getChildElement(item.m_attributeIndex>>1);
		Type* pType2 = item.m_data->getChildType(item.m_attributeIndex>>1);

		ASSERT(pType2->AsClass());

		if (pType2->AsClass()->IsDerivedFrom(pType->AsClass()))
			return true;

		//return TestNodeElementAndType(nodeTest, item);
		return false;
	}
}

DataList* match(AxisStep* pStep, AxisIterator& iterator)
{
	DataList* datalist = new DataList;

	while (!iterator.AtEnd())
	{
		DataItem dataitem = iterator.GetItem();

		if (TestNode(pStep->m_nodeTest, dataitem))
		{
			// Filter the nodeList through all the predicates
			ExpList* predList = pStep->m_predicates;
			if (predList)
			{
				while (predList)
				{
					Exp* exp = predList->head;

					ASSERT((dataitem.m_attributeIndex & 1) == 0);
					XDM::IData* contextnode2 = dataitem.m_data->getChildElement(dataitem.m_attributeIndex>>1);

					ExprResult* result = evaluate(exp, contextnode2, dataitem.m_attributeIndex>>1/*iterator.m_contextPos*/, iterator.m_contextSize);
					bool truth = xpath_boolean(result);
					if (!truth)
						break;

					predList = predList->tail;
				}

				if (predList == NULL)
				{
					datalist->m_items.push_back(dataitem);
				}
			}
			else
			{
				datalist->m_items.push_back(dataitem);
			}
		}

		iterator.Iterate();
	}

	return datalist;

#if 0
	if (true)//node->get_nodeType() == axis->nodeType)
	{
		if (true)//expandedName(node) == pStep->nodeTest)
		{
			//NodeList* nodeList;

			// Filter the nodeList through all the predicates
			PredicateList* predList = pStep->predicates;
			while (predList)
			{
				NodeList* nodeList2 = new NodeList;

				// For each node in the nodeset as the contextNode, evaluate the predicate expression
				while (!iterator.AtEnd())
				//for (int i = 0; i < nodeList->get_length(); i++)
				{
					Node* contextNode = nodeList->item(i);

					int contextPosition;
					if (true)	// forward axis
					{
						contextPosition = i+1;
					}
					else	// backward axis
					{
						contextPosition = nodeList->get_length()-i;
					}
					int contextSize = nodeList->get_length();

					ExprResult* r = evaluate(predList->head->exp, contextNode, contextPosition, contextSize);
					if (xpath_boolean(r))
					{
						nodeList2->m_items.Add(contextNode);
					}
				}

				nodeList = nodeList2;

				predList = predList->tail;
			}

			return nodeList;
		}
	}
#endif
}

DataList* select(AxisStep* pStep, XDM::IData* contextNode)
{
	AxisIterator iterator;

	iterator.m_axis = pStep->m_axis;

	if (pStep->m_axis == AxisStep::K_SELF)
	{
		iterator.m_contextParentItem = contextNode->getParent();
		iterator.m_contextPos = contextNode->getPosition();
		iterator.m_contextSize = 1;//contextNode->getAttributeCount();
	}
	else if (pStep->m_axis == AxisStep::K_ATTRIBUTE)
	{
		iterator.m_contextParentItem = contextNode;
		iterator.m_contextPos = 0;
		iterator.m_contextSize = contextNode->getAttributeCount();
	}
	else if (pStep->m_axis == AxisStep::K_CHILD)
	{
		iterator.m_contextParentItem = contextNode;
		iterator.m_contextPos = 0;
		iterator.m_contextSize = contextNode->getChildCount();
	}
	else
		ASSERT(0);

	return match(pStep, iterator);

	/*
	NodeList* nodeList = new NodeList;
	GetAxisNodes(pStep->axis, contextNode, nodeList);

	NodeList* nodeList2 = new NodeList;

	for (int i = 0; i < nodeList->get_length(); i++)
	{
		Node* node = nodeList->item(i);

		if (true)//node->get_nodeType() == axis->nodeType)
		{
			if (true)//expandedName(node) == pStep->nodeTest)
			{
				nodeList2->m_items.Add(node);
			}
		}
	}

	return match(pStep, nodeList2);
	*/
}

ExprResult* select(StepList* steps, XDM::IData* contextNode)
{
	if (steps->head->GetKind() == Step::Axis)
	{
		DataList* nodeList = select(static_cast<AxisStep*>(steps->head), contextNode);

		if (steps->tail == nullptr) return new ExprResult(nodeList);

		// E1/E2

		// E2 is evaluated once for each item in the sequence that results from evaluating E1.

		DataList* nodeList2 = new DataList;

		for (size_t i = 0; i < __min(600, nodeList->m_items.size()); ++i)
		{
			DataItem dataitem = nodeList->m_items[i];

			ASSERT((dataitem.m_attributeIndex & 1) == 0);
			XDM::IData* contextNode2 = dataitem.m_data->getChildElement(dataitem.m_attributeIndex>>1);

			if (contextNode2)	// TODO ??
			{
				DataList* nodeListE2 = select(steps->tail, contextNode2)->m_nodeList;

				for (size_t i = 0; i < nodeListE2->m_items.size(); ++i)
				{
					DataItem dataitemE2 = nodeListE2->m_items[i];

					nodeList2->m_items.push_back(dataitemE2);
				}
			}
		}

		return new ExprResult(nodeList2);
	}
	else
	{
		FilterStep* filterStep = (FilterStep*)steps->head;
		ASSERT(steps->tail == nullptr);	// hmm..

		if (filterStep->m_exp->kind == Exp::K_NUMBER)
		{
			return new ExprResult(filterStep->m_exp->number);
		}
		else if (filterStep->m_exp->kind == Exp::K_FUNCALL)
		{
			FunctionCallExp* funexp = dynamic_cast<FunctionCallExp*>(filterStep->m_exp);

			vector<ExprResult*> arg_results;
			ExpList* args = funexp->m_args;
			while (args)
			{
				Exp* argexp = args->head;
				ExprResult* result = evaluate(argexp, contextNode, contextNode->getPosition(), 1/*TODO ?*/);

				arg_results.push_back(result);

				args = args->tail;
			}

			if (funexp->m_name->m_ns == L"fn")	// TODO expanded qname
			{
				if (funexp->m_name->m_local == L"true")
				{
					// fn:true() as xs:boolean
					return new ExprResult(true);
				}
				else if (funexp->m_name->m_local == L"false")
				{
					// fn:false() as xs:boolean
					return new ExprResult(false);
				}
				else if (funexp->m_name->m_local == L"not")
				{
				// fn:not($arg as item()*) as xs:boolean
					if (arg_results.size() != 1)
					{
						raise(XPathException("INTERNAL error - arg_results.size() != 1"));
					}

					ExprResult* arg = arg_results[0];

					bool boolean = xpath_boolean(arg);

					return new ExprResult( ! boolean);
				}
				else if (funexp->m_name->m_local == L"count")
				{
				// fn:count($arg as item()*) as xs:integer
					if (arg_results.size() != 1)
					{
						raise(XPathException(S("INTERNAL error - arg_results.size() != 1")));
					}

					ExprResult* arg = arg_results[0];

					ASSERT(arg->m_kind == ExprResult::K_NODELIST);

					return new ExprResult((int)arg->m_nodeList->m_items.size());
				}
				else
				{
					raise(XPathException(S("INTERNAL error - unknown function name")));
				}
			}
			else
			{
				auto it = TypeDatabase::pD->m_procs.find(funexp->m_name->m_local);
				if (it != TypeDatabase::pD->m_procs.end())
				{
					FunctionObject* proc = it->second;

					FunctionType* pFunctionType = proc->m_decl->m_pType->AsFunction();

					// TODO
					++it;
					ASSERT(it->first != funexp->m_name->m_local);	// Only one with that name

					uint8 argsdata[256];
					uint8* p = argsdata;

					DataItem itemdata = arg_results[0]->m_nodeList->m_items[0];

					ASSERT((itemdata.m_attributeIndex & 1) == 0);
					XDM::IData* data = itemdata.m_data->getChildElement(itemdata.m_attributeIndex>>1);

					ClassType* totype = pFunctionType->m_parameters[0].m_pType->GetPointerTo()->AsClass();

					Object* object = data->GetObject();
					void* pcast = DynamicCast(object, object->GetType(), totype);
					*(void**)p = (void*)pcast;

					p += sizeof(void*);

					String result = invoke_function_cdecl<String>(proc->m_decl->m_offset, argsdata, p - argsdata);

					return new ExprResult(result);
				}
				else
				{
					ASSERT(0);
					raise(XPathException(S("INTERNAL error - function not found")));
				}
			}
		}
		else if (filterStep->m_exp->kind == Exp::K_CONTEXTITEM)
		{
			//XDM::IData* ctxnode = contextNode->getChildElement(contextPosition);

			DataList* p = new DataList;
			p->m_items.push_back(DataItem(contextNode->getParent(), contextNode->getPosition()<<1));
			return new ExprResult(p);
		}
		else
		{
			ASSERT(0);
			raise(XPathException("INTERNAL error - Unknown expression"));
		}
	}
}

bool evaluateContaining(Step* step, XDM::IData* contextNode)
{
	if (step->GetKind() == Step::Axis)
	{
		AxisStep* axisStep = (AxisStep*)step;

		if (axisStep->m_axis == AxisStep::K_CHILD)
		{
			DataItem item(contextNode->getParent(), contextNode->getPosition()<<1);

			if (!TestNode(axisStep->m_nodeTest, item))
				return false;
		}
		else if (axisStep->m_axis == AxisStep::K_ATTRIBUTE)
		{
			DataItem item(contextNode->getParent(), (contextNode->getPosition()<<1) | 1);

			if (!TestNode(axisStep->m_nodeTest, item))
				return false;
		}
		else	// only child and attribute allowed
			ASSERT(0);

		ExpList* predList = step->m_predicates;

		if (predList)
		{
			while (predList)
			{
				Exp* exp = predList->head;

			//	ASSERT((dataitem.m_attributeIndex & 1) == 0);
				XDM::IData* contextnode2 = contextNode;//dataitem.m_data->getChildElement(dataitem.m_attributeIndex>>1);

				ExprResult* result = evaluate(exp, contextnode2, 0/*iterator.m_contextPos*/, 1/*iterator.m_contextSize*/);
				bool truth = xpath_boolean(result);
				if (!truth)
					break;

				predList = predList->tail;
			}

			if (predList == NULL)
			{
				return true;//datalist->m_items.push_back(dataitem);
			}
		}
		else
			return true;
	}
	else
		ASSERT(0);
	return false;
}

bool evaluateContaining(StepList* steps, XDM::IData* contextNode)
{
	if (steps->tail == NULL)
	{
		bool b = evaluateContaining(steps->head, contextNode);
		return b;
	}

	bool b = evaluateContaining(steps->tail, contextNode);
	if (!b) return b;

	contextNode = contextNode->getParent();

	return evaluateContaining(steps->head, contextNode);
}

bool evaluateContaining(Exp* exp, XDM::IData* contextNode)
{
	// right-to-left

	switch (exp->kind)
	{
	case Exp::K_PATH:
		{
			StepList* steps = ((PathExp*)exp)->m_path;

			return evaluateContaining(steps, contextNode);
		}
		break;

	default:
		ASSERT(0);
	}

	return false;
}

ExprResult* evaluate(Exp* exp, XDM::IData* contextNode, int contextPosition, int contextSize)
{
	switch (exp->kind)
	{
	case Exp::K_INSTANCEOF:
		{
			InstanceOfExp* instanceof = static_cast<InstanceOfExp*>(exp);

			ExprResult* r = evaluate(instanceof->m_exp, contextNode, 0, 0);

			ASSERT(r->m_kind == ExprResult::K_NODELIST);

			bool b = TestNode(instanceof->m_nodeTest, r->m_nodeList->m_items[0]);

			return new ExprResult(b);
		}
		break;

	case Exp::K_CONTEXTITEM:
		{
			ASSERT(0);
		}
		break;

	case Exp::K_PATH:
		{
		//	ExprResult* p = new ExprResult;
		//	p->kind = ExprResult::K_NODELIST;

			StepList* steps = ((PathExp*)exp)->m_path;

			/*
			if (steps->tail && steps->tail->tail)
			{
				MessageBeep(-1);
			}
			*/

			/*p->nodeList =*/ return select(steps, contextNode);

			/*

			if (steps->tail == NULL)	// one step
			{
				p->nodeList = select(steps->head, contextNode);
			}
			else
			{
				// E1/E2

				// E2 is evaluated once for each item in the sequence that results from evaluating E1.

				while (steps)
				{
					p->nodeList = select(steps->head, contextNode);

					for (int i = 0; i < p->nodeList->m_items.size(); i++)
					{
						DataItem dataitem = p->nodeList->m_items[i];

						select(
					}

					steps = steps->tail;
				}
			}
			*/

			//return p;
		}
		break;

	case Exp::K_BINOP:
		{
			BinopExp* binop = (BinopExp*)exp;

			ExprResult* left = evaluate(binop->m_left, contextNode, contextPosition, contextSize);
			ExprResult* right = evaluate(binop->m_right, contextNode, contextPosition, contextSize);

			switch (binop->m_op)
			{
			case '=':
				{
					double left_number;

					if (left->m_kind == ExprResult::K_NODELIST)
					{
						if (left->m_nodeList->m_items.size() == 0)
							return new ExprResult(false);

						ASSERT(left->m_nodeList->m_items.size() == 1);

						ASSERT(left->m_nodeList->m_items[0].m_attributeIndex & 1);
						Variant value = left->m_nodeList->m_items[0].m_data->getAttributeValue(left->m_nodeList->m_items[0].m_attributeIndex>>1);
						left_number = value.ToDouble();
						/*
						if (left_number == 34)
						{
							MessageBeep(-1);
						}
						*/
					}
					else if (left->m_kind == ExprResult::K_INTEGER)
					{
						left_number = left->m_intValue;
					}
					else if (left->m_kind == ExprResult::K_BOOL)
					{
						left_number = left->m_boolValue;
					}
					else
						ASSERT(0);

					double right_number;

					if (right->m_kind == ExprResult::K_NODELIST)
					{
						ASSERT(0);
					}
					else if (right->m_kind == ExprResult::K_INTEGER)
					{
						right_number = right->m_intValue;
					}
					else if (right->m_kind == ExprResult::K_NUMBER)
					{
						right_number = right->m_numberValue;
					}
					else
						ASSERT(0);

					return new ExprResult(left_number == right_number);
				}
				break;

			case '>':
				{
					double left_number = left->m_intValue;
					double right_number = right->m_numberValue;

					return new ExprResult(left_number > right_number);
				}
				break;

			case 'AND':
				{
					ExprResult* p = new ExprResult;
					p->m_kind = ExprResult::K_BOOL;
				}
				break;

			case 'OR':
				{
					ExprResult* p = new ExprResult;
					p->m_kind = ExprResult::K_BOOL;
				}
				break;

			default:
				ASSERT(0);
			}
		}
		break;

	default:
		ASSERT(0);
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CXPathEvaluator

XPathExpression* XPathEvaluator::createExpression(StringIn expression, IXPathNSResolver* resolver)
{
	yy_buffer_state* state = xpath__scan_string(CString(expression).c_str());
//	g_exp = NULL;
	int error = xpath_parse();
	if (error != 0)
	{
		return NULL;
	}

	XPathExpression* exp = new XPathExpression;
	exp->m_exp = g_exp;

	return exp;
#if 0
	if (pVal == NULL) return E_POINTER;

	CComObject<CXPathNSResolver>* nsresolver = (CComObject<CXPathNSResolver>*)resolver;

//	CComQIPtr<IDOMDocument> document;
//	nsresolver->m_nodeResolver->get_ownerDocument(&document);

//	xmlXPathObjectPtr res;
/*
	CComQIPtr<IDOMElement> documentElement;
	document->get_documentElement(&documentElement);
*/
	CComObject<CXPathExpression>* pExpr;
	CComObject<CXPathExpression>::CreateInstance(&pExpr);
	pExpr->AddRef();

	/*
	//if (expr)
	    res = xmlXPathEvalExpression(BAD_CAST expression, ctxt);
	else
		*/
	{
	    /* res = xmlXPathEval(BAD_CAST str, ctxt); */
		//xmlXPathCompExprPtr comp;
		
		pExpr->m_comp = xmlXPathCompile(BAD_CAST (char*)_bstr_t(expression));

#if 0
		if (comp != NULL)
		{
		//	if (tree) 
		//		xmlXPathDebugDumpCompExpr(stdout, comp, 0);
			
			res = xmlXPathCompiledEval(comp, ctxt);
		//	xmlXPathFreeCompExpr(comp);
		}
		else
			res = NULL;
#endif
	}

	*pVal = pExpr;

	return S_OK;
#endif
}

#if 0
STDMETHODIMP CXPathEvaluator::createNSResolver(ILDOMNode* nodeResolver, ILXPathNSResolver** pVal)
{
	CComQIPtr<ILDOMNode> node = nodeResolver;

	CComObject<CXPathNSResolver>* nsresolver;
	CComObject<CXPathNSResolver>::CreateInstance(&nsresolver);
	nsresolver->AddRef();

	nsresolver->m_nodeResolver = nodeResolver;

	*pVal = nsresolver;

	return S_OK;
}

#endif

}	// XPath
}	// System
