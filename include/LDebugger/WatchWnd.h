#ifndef Debugger_WatchWnd_h
#define Debugger_WatchWnd_h

namespace System
{
namespace Debugger
{

struct ExpResult
{
	long size;

	union
	{
		long int32;
		short int16;
		char int8;
		uint8* buf;
	}
	value;
};

class WatchItem
{
public:
	CTOR WatchItem()
	{
		m_texp = NULL;
		m_bExpanded = false;
	}

	System::StringA* m_name;
	Tr_Exp* m_texp;
	vector<WatchItem*> m_subItems;
	long value;
	bool m_bExpanded;
};

class WatchExpression : public UI::Control
{
public:
	CTOR WatchExpression(System::StringA* str);

	//WatchExpression& operator = (System::StringA* str);

	friend class WatchWnd;

	UI::TextEdit* m_edit;
	UI::TextString* m_result;

protected:
//	std::string m_str;
	cpp::ast::A_Exp* m_exp;
//	Tr_Exp* m_texp;
//	long m_value;

	WatchItem m_item;

//	ExpValue* m_value;

//	cpp::CDeclarator* m_pDeclarator;
};

class WatchWnd :
	public UI::Control
	//public UI::DockPanel
{
public:
	CTOR WatchWnd();

	void Update();
	void UpdateItem(WatchItem* pItem);
	void UpdateWatchExpression(WatchExpression* pItem, PlatformProcess hProcess);

	void ExpandClass(WatchItem* pItem, System::Type* pType, T_Exp* exp);
	void Expand(WatchItem* pItem);
	void OnExpand(WatchItem* pItem);
	int DrawItem(UI::Graphics* pGraphics, int x, int y, WatchItem* pItem, PlatformProcess hProcess);

	//virtual void OnRender(UI::Graphics* pGraphics);
//	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);
//	virtual void OnArrange(LDraw::SizeD finalSize);

	void AddWatchExpression(WatchExpression* exp);

	void set_Context(DebuggerCtx* ctx);

public:

//	DebuggerFrame* m_pFrame;
	DebuggerCtx* m_ctx;
	UI::TreeControl* m_tree;

	int m_index;
#if 0//
	CEdit m_edit;
#endif

protected:

	vector<WatchExpression*, __gc_allocator> m_watchList;

//	LRESULT OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
};

}
}

#endif // Debugger_WatchWnd_h
