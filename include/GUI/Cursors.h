namespace System
{
namespace Gui
{

class GUIEXT Cursors
{
public:

	static Cursor* get_Arrow();
	static Cursor* get_IBeam();
	static Cursor* get_Cross();
	static Cursor* get_Hand();
	static Cursor* get_No();
	static Cursor* get_SizeAll();
	static Cursor* get_SizeNS();
	static Cursor* get_SizeNESW();
	static Cursor* get_SizeNWSE();
	static Cursor* get_SizeWE();
	static Cursor* get_UpArrow();
	static Cursor* get_Wait();
	static Cursor* get_AppStarting();
	static Cursor* get_Help();

private:

	CTOR Cursors();	// Can't construct
};

}	// Gui
}	// System
