// no B declared here
class X;
template<class T> class Y
{
public:
class Z; // forward declaration of member class
void f() {
X* a1; // declare pointer to X
T* a2; // declare pointer to T
Y* a3; // declare pointer to Y<T>
Z* a4; // declare pointer to Z
typedef typename T::A TA;
TA* a5; // declare pointer to T’s A
typename T::A* a6; // declare pointer to T’s A
T::Q+ a7; // T::A is not a type name:
// multiply T::A by a7; ill-formed,
// no visible declaration of a7
B* a8; // B is not a type name:
// multiply B by a8; ill-formed,
// no visible declarations of B and a8
}
};

/*
extern int k;

static int k;
*/

#if AMIGA
#include <exec/exec.h>
#include <dos/dos.h>
#include <exec/libraries.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/intuition.h>

extern "C"
{
struct ExecBase* SysBase;
struct IntuitionBase* IntuitionBase;
struct DosLibrary* DOSBase;
}

extern "C" int first();

extern "C" void _first()
{
	struct Window *mywin;
	struct MsgPort* userport;

	userport = (*mywin).UserPort;
	//WaitPort(userport);

//	first();
}
#if 0

extern "C" int first()
{
	SysBase = *((struct ExecBase**)4);
	IntuitionBase = (struct IntuitionBase*)OpenLibrary("intuition.library", 37);
	DOSBase = (struct DosLibrary*)OpenLibrary("dos.library", 37);

	struct NewWindow nw = {0};

	nw.TopEdge = 0;
	nw.LeftEdge = 0;
	nw.Width = 100;
	nw.Height = 100;
	nw.Flags = WFLG_DRAGBAR;
	nw.Type = WBENCHSCREEN;

	struct Window* win = OpenWindow(&nw);
	if (win == NULL)
	{
		Write(Output(), (void* const)"Failed\n", 7);
		return 0;
	}

	Delay(50*4);

	CloseWindow(win);

	//DisplayBeep(NULL);
	return 0;
}
#endif

#endif
