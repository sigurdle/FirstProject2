namespace System
{
namespace Gui
{

class GUIEXT Application : public Object
{
public:

	static Application* get_Current();

	Window* get_MainWindow();
	void set_MainWindow(Window* window);

	/*
	virtual bool DdeExecute(StringIn command)
	{
		return false;
	}
	*/

	Event1<StringIn>& get_DdeExecute()
	{
		return DdeExecute;
	}

	Event1<StringIn> DdeExecute;

	static Application* s_Current;

	// DDE
	static DdeInstance* g_ddeInst;
#ifndef __LERSTAD__
	static HSZ dde_service_name;
	static HSZ dde_system;
	static HDDEDATA CALLBACK DdeCallback( 
		UINT uType,       // transaction type 
		UINT uFmt,        // clipboard data format 
		HCONV hconv,      // handle to conversation 
		HSZ hsz1,         // handle to string 
		HSZ hsz2,         // handle to string 
		HDDEDATA hdata,   // handle to global memory object 
		DWORD dwData1,    // transaction-specific data 
		DWORD dwData2    // transaction-specific data 
	);
#endif

private:

	Window* m_mainWindow;
	list<Window*> m_windows;
};

}	// Gui
}	// System
