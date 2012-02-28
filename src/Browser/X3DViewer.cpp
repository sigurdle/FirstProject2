#include "stdafx.h"
#include "Browser.h"
#include "X3DViewer.h"

/*
#include "../LX3D/LX3D.h"
#include "../LX3D/LX3DScene.h"
#include "../LX3D/LVRMLLoader.h"
#include "../LX3D/OGLSceneRenderer.h"

#include "../LX3D/SceneRenderFilter.h"
*/

namespace System
{
using namespace UI;

X3DViewer::X3DViewer()
{
	/*
	CLVRMLLoader* pLoader = new CLVRMLLoader;

	CLX3DScene* pScene = pLoader->Load(WSTR("C:/Files/VRML/RedSphereBlueBox.wrl"));
	*/
//	pScene = pLoader->Load(WSTR("C:/Files/VRML/z_wing.wrl"));

//	CLXUIBorder* pBorder = new CLXUIBorder;
//	pBorder->put_BorderThickness(new CLXUIThickness(new Length(3, Length::UnitAbsolute), new Length(3, Length::UnitAbsolute), new Length(3, Length::UnitAbsolute), new Length(3, Length::UnitAbsolute)));

	DockPanel* pPanel = new DockPanel;
	{
		m_button[0] = new DeltaMoveButton;
		m_button[0]->set_VisualTree(new TextString(WSTR("Examine")));
		pPanel->AddChild(m_button[0]);
	}
	{
		m_button[1] = new DeltaMoveButton;
		m_button[1]->set_VisualTree(new TextString(WSTR("Slide")));
		pPanel->AddChild(m_button[1]);
	}
	{
		m_button[2] = new DeltaMoveButton;
		m_button[2]->set_VisualTree(new TextString(WSTR("Walk")));
		pPanel->AddChild(m_button[2]);
	}

	{
		m_pWindow = new Viewer;
	//	m_pWindow->SetScene(pScene);

		DockPanel::SetDock(m_pWindow, DockPanel::Fill);
		pPanel->AddChild(m_pWindow);
	}

	set_VisualTree(pPanel);
}

#if 0
void X3DViewer::handleEvent(System::Event* evt)
{
	StringW* type = evt->get_type();

	EventPhaseType phase = evt->get_eventPhase();
	if (phase != System::CAPTURING_PHASE)
	{
		if (*type == L"mousedown")
		{
			evt->stopPropagation();

			m_xoffset = 0;
			m_yoffset = 0;
			m_pWindow->m_pControl->BeginMove();
		}
		else if (*type == L"deltaChange")
		{
			evt->stopPropagation();

			DeltaChangeEvent* deltaEvt = dynamic_cast<DeltaChangeEvent*>(evt);

			m_xoffset += deltaEvt->deltaX;
			m_yoffset += deltaEvt->deltaY;

			if (evt->get_target() == m_button[0])
			{
				m_pWindow->m_pControl->Move(3/*m_dragging*/, LDraw::PointI(m_xoffset, m_yoffset));
			}
			else if (evt->get_target() == m_button[1])
			{
				m_pWindow->m_pControl->Move(1/*m_dragging*/, LDraw::PointI(m_xoffset, m_yoffset));
			}
			else if (evt->get_target() == m_button[2])
			{
				m_pWindow->m_pControl->Move(2/*m_dragging*/, LDraw::PointI(m_xoffset, m_yoffset));
			}
		}
	}
}
#endif

Viewer::Viewer()
{
	m_pControl = new x3d::COGLSceneRenderer;

	set_VisualTree(m_pControl);
}

void Viewer::set_Src(StringW* url)
{
#if 1
	m_filterGraph = new MediaShow::FilterGraph;

	m_pFilter = new x3d::SceneRenderFilter;
	m_pFilter->m_Control = m_pControl;
//	m_pFilter->m_pControl = this;
//	pFilter->m_pBitmap = this;
	m_filterGraph->AddFilter(m_pFilter);

//	pFilterGraph->LoadURL(L"C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\Sunset.pcx");
	m_filterGraph->LoadURL(url);
#endif
}

}
