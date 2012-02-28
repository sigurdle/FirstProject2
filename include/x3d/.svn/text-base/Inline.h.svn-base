#ifndef x3d_Inline_h
#define x3d_Inline_h

namespace System
{
namespace x3d
{

class X3DEXT Inline :
	public X3DChildNode,
	public X3DUrlObject,
	public X3DBoundedObject,
	public RenderImplImpl
{
public:
	CTOR Inline();
	CTOR Inline(StringIn url);

	~Inline();

	virtual void Draw(X3DDrawContext* pDC);
	virtual void DrawOverlay(X3DDrawContext* pDC);

	virtual MFURL* get_urlField()
	{
		ASSERT(0);
		return NULL;
		//return m_url;
	}

	virtual SFVec3f* get_bboxCenterField()
	{
		ASSERT(0);
		return NULL;
	}
	virtual SFVec3f* get_bboxSizeField()
	{
		ASSERT(0);
		return NULL;
	}

	static NodeType* nodeType;
	static NodeType* GetNodeType();

protected:

	static DWORD WINAPI _LoadThread(void* lParam);

	DWORD LoadThread();

	HANDLE m_hLoadThread;
	DWORD m_dwLoadThreadId;
	CriticalSection m_critSec;

	MFNode* m_children;	// Not a field

	Gui::Media3D::Visual3D* m_visual3D;	// TODO

private:

	SFBool* m_load;
	MFString* m_url;
};

}	// x3d
}	// System

#endif // x3d_Inline_h
