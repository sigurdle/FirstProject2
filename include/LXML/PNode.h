#ifndef w3c_PNode_h
#define w3c_PNode_h

namespace System
{
namespace Web
{

class ViewCSS;
class CXMLDocumentView;
class CHTMLWindow;
class CHTMContext;
class CHTMRenderContext;
class CHTMFlowContext;
class CHTMCalcContext;
class PElementBase;
class CHTMBlockBox;

class WEBEXT PNode : public Object
{
public:
	CTOR PNode(ChildNode* node);
	virtual ~PNode();

	PNode* GetPrevNode();
	PNode* GetNextNode();
	int GetDOMNodesIndex();	// TODO ?? Remove

	CHTMLWindow* GetWindow();

	virtual void RemovedFromDocument();

	virtual void CalculateDimensions(CHTMCalcContext* pC)
	{
	}

	virtual void DistributeInline(CHTMFlowContext* pParentC, PElementBase* nearestPositioned, PElementBase* stackingContext, double oparentwidth)
	{
	}

	virtual bool GetCursorPosition(int cursorPos, gm::PointD* pos, double* pHeight, gm::matrix3f* pMat3)
	{
		return false;
	}

#if 0	// TODO, have this ??
	virtual void OnInsertedChild(ILDOMNode* node)
	{
	}
#endif

	ChildNode* m_pNode;

	CHTMBlockBox* m_pSharedBox;	// Box shared with other nodes

#if 0
	Web::CLViewCSS* m_pView;
#endif
	CHTMLWindow* m_pWindow;

	PElementBase* m_parent;
	PElementBase* m_rparent;

	CHTMFlowContext* m_pC;

	short m_type;
	short m_selected;	// TODO, am I using this? If I am, put a comment here saying what it's for

	bool m_bArrangeValid;

};

}
}

#endif	// w3c_PNode_h
