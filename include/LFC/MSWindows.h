#ifndef __MSWindows_Hwnd_h__
#define __MSWindows_Hwnd_h__

#if _WIN32

#define CALLBACK __stdcall

namespace System
{
namespace MSWindows
{

class LFCEXT Hwnd
{
public:
	inline CTOR Hwnd()
	{
		m_hWnd = NULL;
	}

	inline CTOR Hwnd(HWND hWnd)
	{
		m_hWnd = hWnd;
	}

	inline operator HWND () const
	{
		return m_hWnd;
	}

	LONG_PTR GetWindowLongPtr(int nIndex);
	LONG_PTR SetWindowLong(int nIndex, LONG_PTR dwNewLong);
	BOOL MoveWindow(int x, int y, int nWidth, int nHeight, bool bRepaint = true);
	HWND SetParent(HWND hWndNewParent);
	BOOL SetProp(LPCWSTR lpString, HANDLE hData);
	UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT uElapse);
	LRESULT SendMessage(UINT Msg, WPARAM wParam, LPARAM lParam);
	BOOL PostMessage(UINT Msg, WPARAM wParam, LPARAM lParam);

	HWND m_hWnd;
};

class LFCEXT WindowImpl : public Object//Hwnd
{
public:
	CTOR WindowImpl()
	{
		m_hWnd = NULL;
	}

	HWND m_hWnd;

	virtual ~WindowImpl();

	class Data
	{
	public:
	//	__live_object_ptr<WindowImpl> m_window;
		WindowImpl* m_window;
	};

	LONG_PTR GetWindowLongPtr(int nIndex);
	LONG_PTR SetWindowLongPtr(int nIndex, LONG_PTR dwNewLong);

	BOOL SetProp(LPCWSTR lpString, HANDLE hData);
	UINT_PTR SetTimer(UINT_PTR nIDEvent, UINT uElapse);

	Hwnd Create(Hwnd hWndParent, const gm::RectI& rect, LPCWSTR title, DWORD dwStyle, DWORD dwExStyle = 0, UINT nID = 0);

	virtual bool ProcessWindowMessage(Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult/*, DWORD dwMsgMapID*/ )
	{
		return false;
	}

	virtual LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static inline LRESULT CALLBACK WndProc(Hwnd hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

};

}	// MSWindows
}

#endif

#endif // __MSWindows_Hwnd_h__
