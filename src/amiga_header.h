#ifndef __AMIGA_HEADER_H__
#define __AMIGA_HEADER_H__

#define Point aos_Point
#define Class aos_Class
#define Object aos_Object
#define _Object aos__Object
#define Border intuiBorder
#define Image intuiImage
#define Rectangle gfxRectangle

#define System dosSystem

#include <exec/types.h>
#include <exec/exec.h>
#include <dos/dos.h>
#include <dos/dostags.h>
#include <intuition/intuition.h>
#include <intuition/pointerclass.h>
#include <diskfont/diskfont.h>
#include <devices/keymap.h>
#include <devices/clipboard.h>
#include <libraries/asl.h>
#include <libraries/gadtools.h>
#include <libraries/Picasso96.h>

#include <proto/exec.h>
#include <proto/dos.h>
#include <proto/graphics.h>
#include <proto/diskfont.h>
#include <proto/intuition.h>
#include <proto/layers.h>
#include <proto/asl.h>
#include <proto/gadtools.h>
#include <proto/keymap.h>
#include <proto/Picasso96.h>

/*
#ifdef renameSysBase
#define SysBase renameSysBase
#endif

#ifdef renameDOSBase
#define DOSBase renameDOSBase
#endif
*/

// exec

inline void* execAllocMem(struct ExecBase* SysBase, ULONG size, ULONG flags)
{
	return AllocMem(size, flags);
}
#undef AllocMem

inline void execFreeMem(struct ExecBase* SysBase, void* p, ULONG size)
{
	FreeMem(p, size);
}
#undef FreeMem

inline void* execAllocVec(struct ExecBase* SysBase, ULONG size, ULONG flags)
{
	return AllocVec(size, flags);
}
#undef AllocVec

inline void execFreeVec(struct ExecBase* SysBase, void* p)
{
	FreeVec(p);
}
#undef FreeVec

inline struct Library* execOpenLibrary(struct ExecBase* SysBase, const char* name, int version)
{
	return OpenLibrary(name, version);
}
#undef OpenLibrary

inline void execCloseLibrary(struct ExecBase* SysBase, struct Library* lib)
{
	CloseLibrary(lib);
}
#undef CloseLibrary

inline ULONG execWait(struct ExecBase* SysBase, ULONG mask)
{
	return Wait(mask);
}
#undef Wait

inline void execEnable()
{
	Enable();
}
#undef Enable

inline void execDisable()
{
	Disable();
}
#undef Disable

inline void execInsert(struct List *list, struct Node *node, struct Node *pred)
{
	Insert(list, node, pred);
}
#undef Insert

inline void execRemove(struct Node *node)
{
	Remove(node);
}
#undef Remove

inline void execAddHead(struct List* list, struct Node* node)
{
	AddHead(list, node);
}
#undef AddHead

inline void execAddTail(struct List* list, struct Node* node)
{
	AddTail(list, node);
}
#undef AddTail

// dos

inline BPTR dosOpen(struct DosLibrary* DOSBase, const char* filename, int mode)
{
	return Open(filename, mode);
}
#undef Open

inline int dosClose(struct DosLibrary* DOSBase, BPTR file)
{
	return Close(file);
}
#undef Close

inline int dosRead(struct DosLibrary* DOSBase, BPTR file, void* pv, int size)
{
	return Read(file, pv, size);
}
#undef Read

inline int dosWrite(struct DosLibrary* DOSBase, BPTR file, const void* pv, int size)
{
#ifdef __cplusplus
	return Write(file, const_cast<void*>(pv), size);
#else
	return Write(file, (void*)pv, size);
#endif
}
#undef Write

inline int dosSeek(struct DosLibrary* DOSBase, BPTR file, int offset, int mode)
{
	return Seek(file, offset, mode);
}
#undef Seek

inline BPTR dosLock(struct DosLibrary* DOSBase, STRPTR name, LONG accessMode)
{
	return Lock(name, accessMode);
}
#undef Lock

inline void dosUnLock(struct DosLibrary* DOSBase, BSTR lock)
{
	return UnLock(lock);
}
#undef UnLock

inline BOOL dosExamineFH(struct DosLibrary* DOSBase, BPTR file, struct FileInfoBlock *fib)
{
	return ExamineFH(file, fib);
}
#undef ExamineFH

inline LONG dosFlush(BPTR fh)
{
	return Flush(fh);
}
#undef Flush

/*
inline LONG dosSystem(STRPTR str, struct TagItem * tags)
{
	return System(str, tags);
}
#undef System
*/

// graphics

inline void gfxText(struct RastPort* rp, const char* p, short len)
{
	Text(rp, p, len);
}
#undef Text

inline void gfxMove(struct RastPort* rp, short x, short y)
{
	Move(rp, x, y);
}
#undef Move

inline void gfxDraw(struct RastPort* rp, short x, short y)
{
	Draw(rp, x, y);
}
#undef Draw

inline void gfxDrawEllipse(struct RastPort* rp, short x, short y, short rx, short ry)
{
	DrawEllipse(rp, x, y, rx, ry);
}
#undef DrawEllipse

inline long gfxOrRectRegion(struct Region* rgn, const struct Rectangle* rect)
{
	return OrRectRegion(rgn, rect);
}
#undef OrRectRegion

inline long gfxOrRegionRegion(const struct Region* rgn1, struct Region* rgn2)
{
	return OrRegionRegion(rgn1, rgn2);
}
#undef OrRegionRegion

inline void gfxAndRectRegion(struct Region* rgn, const struct Rectangle* rect)
{
	AndRectRegion(rgn, rect);
}
#undef AndRectRegion

inline long gfxAndRegionRegion(const struct Region* rgn1, struct Region* rgn2)
{
	return AndRegionRegion(rgn1, rgn2);
}
#undef AndRegionRegion

inline long gfxXorRectRegion(struct Region* rgn, const struct Rectangle* rect)
{
	return XorRectRegion(rgn, rect);
}
#undef XorRectRegion

inline long gfxXorRegionRegion(const struct Region* rgn1, struct Region* rgn2)
{
	return XorRegionRegion(rgn1, rgn2);
}
#undef XorRegionRegion

inline void gfxDisposeRegion(struct Region* rgn)
{
	DisposeRegion(rgn);
}
#undef DisposeRegion

inline struct Region* gfxNewRegion()
{
	return NewRegion();
}
#undef NewRegion

inline void gfxClearRegion(struct Region* rgn)
{
	ClearRegion(rgn);
}
#undef ClearRegion

// layer

inline struct Region* layerInstallClipRegion(struct Layer* layer, struct Region* rgn)
{
	return InstallClipRegion(layer, rgn);
}
#undef InstallClipRegion

// diskfont

inline long diskfontAvailFonts(struct AvailFontsHeader* buffer, long bufsize, ULONG flags)
{
	return AvailFonts((char*)buffer, bufsize, flags);
}
#undef AvailFonts

// intuition

inline struct Window* intuiOpenWindow(struct NewWindow* nw)
{
	return OpenWindow(nw);
}
#undef OpenWindow

inline void intuiCloseWindow(struct Window* win)
{
	CloseWindow(win);
}
#undef CloseWindow

inline void intuiMoveWindow(struct Window* win, int dx, int dy)
{
	MoveWindow(win, dx, dy);
}
#undef MoveWindow

inline void intuiWindowToFront(struct Window* win)
{
	WindowToFront(win);
}
#undef WindowToFront

inline void intuiDrawImage(struct RastPort* rp, struct Image* image, short x, short y)
{
	DrawImage(rp, image, x, y);
}
#undef DrawImage

inline void intuiDrawBorder(struct RastPort *rp, struct Border *border, short x, short y)
{
	DrawBorder(rp, border, x, y);
}
#undef DrawBorder

inline ULONG intuiGetAttr( ULONG AttrID, APTR Obj, ULONG * StoragePtr)
{
	return GetAttr(AttrID, Obj, StoragePtr);
}
#undef GetAttr

inline APTR intuiNewObject( struct IClass * cls, const char * clsid, Tag tag1, ...)
{
	return NewObjectA(cls, clsid, (struct TagItem*)&tag1);
}
#undef NewObject

inline APTR intuiNewObjectA( struct IClass * cls, const char * clsid, struct TagItem* taglist)
{
	return NewObjectA(cls, clsid, taglist);
}
#undef NewObjectA

//

#undef Class
#undef Object
#undef _Object
#undef Point
#undef Border
#undef Image
#undef System
#undef Rectangle
#undef VOID

#endif // __AMIGA_HEADER_H__
