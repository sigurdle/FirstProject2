#ifndef __X3DViewer_h__
#define __X3DViewer_h__

namespace System
{

class Viewer;

namespace UI
{
class DeltaMoveButton;
}

namespace x3d
{
	class SceneRenderFilter;
	class COGLSceneRenderer;
}

class X3DViewer : public UI::Control
{
public:
	CTOR X3DViewer();

	Viewer* m_pWindow;

	UI::DeltaMoveButton* m_button[3];

protected:
//	virtual void handleEvent(System::Event* evt);

private:

	long m_xoffset;
	long m_yoffset;
};

class Viewer : public UI::Control, public UI::IMediaControl
{
public:
	CTOR Viewer();

	virtual void Run()
	{
		ASSERT(0);
#if 0
		m_filterGraph->Run();
#endif
	}

	virtual void Stop()
	{
		ASSERT(0);
	}
	virtual void Pause()
	{
		ASSERT(0);
	}

	virtual UI::MEDIACONTROL_STATE GetState()
	{
		return UI::MediaControlState_Stopped;
	}

	MediaShow::FilterGraph* m_filterGraph;
	x3d::SceneRenderFilter* m_pFilter;
	x3d::COGLSceneRenderer* m_pControl;

	void set_Src(System::StringW* url);
};

}

#endif // __X3DViewer_h__
