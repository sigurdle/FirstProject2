#ifndef __SOURCEEDITFRAME_H_
#define __SOURCEEDITFRAME_H_

namespace System
{
namespace Debugger
{

class SourceEditFrame : public UI::Control
{
public:
	CTOR SourceEditFrame();

	DebuggerCtx* m_ctx;
	System::StringA* m_filename;
	SourceTextDocument* m_document;
	SourceEdit* m_edit;

	/*
	LRESULT OnViewLineNumbers(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnEditLineWrap(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBuildCompile(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	*/
};

}
}

#endif // __SOURCEEDITFRAME_H_
