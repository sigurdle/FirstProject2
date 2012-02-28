// LX3DViewer.cpp : Implementation of CLX3DViewer

#include "stdafx.h"
#include "LX3D.h"
#include "LX3DViewer.h"

/////////////////////////////////////////////////////////////////////////////
// CLX3DViewer

int CLX3DViewer::FinalConstruct()
{
#if 0
	m_hDC = CreateCompatibleDC(NULL);
	if (m_hDC == NULL)
		return E_FAIL;
#endif

	return 0;
}

void CLX3DViewer::FinalRelease()
{
#if 0
	if (m_hDC)
	{
		DeleteDC(m_hDC);
		m_hDC = NULL;
	}
#endif
}

DWORD WINAPI StartProc(LPVOID lpParam)
{
	CLX3DViewer* pDocument = (CLX3DViewer*)lpParam;

	MSG msg;
	do
	{
		BOOL bAdvance = FALSE;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) && (msg.message == WM_USER+100))
		{
			bAdvance = TRUE;
			ATLASSERT(msg.hwnd == NULL);
		}

		if (bAdvance)
		{
#if 0
			pDocument->AdvancePlay();
#endif
			pDocument->PostMessage(WM_USER+100, 0, 0);
		}
	}
	while (msg.message != WM_QUIT);

	return 0;
}

DWORD oldTime = 0;

void CALLBACK VideoPlayTimeProc(
  UINT uID,     
  UINT uMsg,  
  DWORD dwUser,
  DWORD dw1,
  DWORD dw2
)
{
	CLX3DViewer* pDoc = (CLX3DViewer*)dwUser;

	/*
	if (!audioClock)
	{
		pDoc->m_currentTime += 1 / pDoc->m_frameRate;
	}
	*/

	pDoc->m_currentVideoTime += 1 / pDoc->m_frameRate;

	::PostThreadMessage(pDoc->m_threadID, WM_USER+100, 0, 0);
}

HRESULT CLX3DViewer::StartPlay()
{
// Timer
	//m_totalIntendedTime = 0;

//	m_currentAudioTime = 0;
	m_currentVideoTime = 0;

	LONG uDelay = (LONG)(1000/m_frameRate);

#if 0
	if (FALSE)
	{
		CComQIPtr<IDirectSoundNotify8, &IID_IDirectSoundNotify> notify8;// = m_dsBuffer8;
		m_dsBuffer8->QueryInterface(IID_IDirectSoundNotify8, (void**)&notify8);

		m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThread = CreateThread(NULL, 0, StartProc, (LPVOID)this, 0, &m_threadID);

		currentVideoTime = 0;
		currentAudioTime = 0;

		dwOffset = 0;
		DSBPOSITIONNOTIFY ps[2];
		ps[0].dwOffset = 0;
		ps[0].hEventNotify = m_hEvent;
		ps[1].dwOffset = 2*m_wf.nAvgBytesPerSec;
		ps[1].hEventNotify = m_hEvent;

		notify8->SetNotificationPositions(2, ps);

		//DWORD nSamples = m_wf.nSamplesPerSec*2;
		DWORD dwbuffer;
		if (SUCCEEDED(m_dsBuffer8->Lock(0, 2 * m_wf.nAvgBytesPerSec, (void**)&m_wavbuffer, &dwbuffer, NULL, NULL, 0)))
		{
			CComPtr<ILDOMElement> documentElement;
			m_document->get_documentElement(&documentElement);

			RenderAllAudio(documentElement, 0, 2, 0);

			m_dsBuffer8->Unlock(m_wavbuffer, dwbuffer, NULL, 0);
		}
	}
#endif

	ATLASSERT(m_nTimerID == 0);
//	m_timerID = m_cwnd.SetTimer(1, uDelay);

	/*
	CComPtr<ILDOMElement> documentElement;
	m_document->get_documentElement(&documentElement);
	if (documentElement)
	{
		Run(documentElement);
	}
	*/

	m_hThread = CreateThread(NULL, 0, StartProc, (LPVOID)this, 0, &m_threadID);

	m_nTimerID = timeSetEvent(uDelay, 0, VideoPlayTimeProc, (DWORD)this, TIME_PERIODIC);

#if 0
	if (FALSE)
	{
		m_dsBuffer8->Play(0, 0, DSBPLAY_LOOPING);
	}
#endif

	return S_OK;
}

LRESULT CLX3DViewer::OnAdvance(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	//AdvancePlay();
	//UpdateAllViews();
	//MessageBeep(-1);
#if 0	// TODO, have something like this

	for (int i = 0; i < m_scene->m_nodes.GetSize(); i++)
	{
		CComQIPtr<CLX3DNodeImplImpl> node(m_scene->m_nodes[i]);

		CComQIPtr<ILX3DTimeDependentNode> timeDependant = node;
		if (timeDependant)
		{
			node->DoTime(m_currentVideoTime);
		}
	}
#endif

	FireViewChange();

#if 0	// TODO, have something like this
	DWORD currentTime = GetTickCount();

	m_currentSpeed = 1000.0/(currentTime-oldTime);
	oldTime = currentTime;
#endif

	return 0;
}

LRESULT CLX3DViewer::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_basicVideo)
	{
		m_basicVideo->set_WindowStyle(WS_CHILD | WS_VISIBLE);
		m_basicVideo->set_Owner((ULONG_PTR)m_hWnd);
	}

	return 0;
}

LRESULT CLX3DViewer::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CLX3DViewer::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CRect client;
	GetClientRect(&client);

	m_slider.SetRect(CRect(0, client.bottom-16, client.right, client.bottom));

	CRect videoRect;
	videoRect.SetRect(0, 0, client.right, client.bottom-16);

	if (m_basicVideo)
	{
		m_basicVideo->SetRect(videoRect);
	}

	return 0;
}

LRESULT CLX3DViewer::OnTimer(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	UINT wTimerID = (UINT)wParam;	// timer identifier 

	if (wTimerID == m_nRunTimer)
	{
		CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
		LONGLONG currentPosition;
		seeking->GetCurrentPosition(&currentPosition);
		m_currentPosition = currentPosition / 100000.0;

		m_slider.SetPos(m_currentPosition);
		InvalidateRect(&m_slider.GetRect());
		UpdateWindow();
	}

	return 0;
}

HRESULT CLX3DViewer::OnPostVerbInPlaceActivate()
{
	if (m_filterGraph)
	{
		m_filterGraph->Run();

	// Timer for updating slider position (update every 0.1 seconds)
	//	m_nRunTimer = SetTimer(1, 100);
	}

#if 0
	StartPlay();
#endif
	return 0;
}

#if 0
STDMETHODIMP CMoviePlayerFilter::CInputPin::Receive(ILMediaSample *pSample)
{
	EnterCriticalSection(&m_pLock);
	/*

	while (1)
	{
		EnterCriticalSection(&m_pFilter->m_pLock);
		if (m_pFilter->m_state == LState_Running)
			break;
		LeaveCriticalSection(&m_pFilter->m_pLock);
	}
	LeaveCriticalSection(&m_pFilter->m_pLock);

	*/

//	MessageBeep(-1);

	double timeStart;
	double timeEnd;
	pSample->GetTime(&timeStart, &timeEnd);

	CComQIPtr<ILBIFSSample> bifsSample = pSample;

	CComPtr<IUnknown> unk;
	bifsSample->GetScene(&unk);
	CComQIPtr<ILX3DScene> scene = unk;

	m_pFilter->m_pMoviePlayer->m_scene = static_cast<CComObject<CLSAIScene>*>(scene.p);

	if (m_pFilter->m_viewpointStack.GetSize() == 0)
	{
		MessageBeep(-1);
		m_pFilter->InitStacks();
	}

// BIFS samples are not double buffered, so we do de this differently than when displaying double buffered video

	PostMessage(m_pFilter->m_pMoviePlayer->m_hWnd, WM_USER+100, 0, 0);	// Display the sample

// Wait for the duration of the sample
	HANDLE hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_pFilter->m_clock->AdviseTime(m_pFilter->m_tStart/*baseTime*/, timeEnd/*streamTime*/, hEvent, NULL);
	WaitForSingleObject(hEvent, INFINITE);

	CloseHandle(hEvent);

	//m_pSample = static_cast<CVideoSample*>(pSample);

	LeaveCriticalSection(&m_pLock);

	return S_OK;
}
#endif

/////////////////////////////////////////////////////////////////////////////////
// CLX3DViewer

#if 0
HRESULT CLX3DViewer::OnDraw(ATL_DRAWINFO& di)
{
	CRect& rc = *(CRect*)di.prcBounds;
	CDCHandle dc(di.hdcDraw);

	{
		{
			CUString str = "left/right/up/down";
			dc.TextOut(0, 0, str, str.GetLength());
		}
		{
			CUString str = "left/right/forward/backward";
			dc.TextOut(125, 0, str, str.GetLength());
		}
		{
			CUString str = "rotate";
			dc.TextOut(315, 0, str, str.GetLength());
		}

		/*
		CUString str;
		str.Format("%g", m_currentSpeed);
		TextOut(hdc, 0, 0, str, str.GetLength());
		*/
	}

	{
		m_slider.Draw(dc);
	}

	return 1;	// ??
	return S_OK;
}
#endif

LRESULT CLX3DViewer::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_slider.GetRect().PtInRect(point))
	{
		int drag = m_slider.OnLButtonDown(point);
		if (drag)
		{
			m_dragging = 1;
			SetCapture();
			InvalidateRect(&m_slider.GetRect());

			if (drag == 2)
			{
				double position = m_slider.GetPos();

				CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
				seeking->Seek(position);
			}
		}
	}

#if 0
	if (!m_dragging)
	{
		SetCapture();

		if (point.x < 125)
			m_dragging = 1;
		else if (point.x < 315)
			m_dragging = 2;
		else if (point.x < 400)
			m_dragging = 3;

		if (m_dragging)
		{
			m_startpoint = point;

			CLViewpoint* pViewpoint = static_cast<CLViewpoint*>(m_viewpointStack[0]);

			CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
			CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

			m_initialPosition = position->m_value;
			m_initialOrientation = orientation->m_value;
		}
	}
#endif

	return 0;
}

LRESULT CLX3DViewer::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging)
	{
		ReleaseCapture();

		if (m_dragging == 1)
		{
			m_slider.OnLButtonUp(point);
		}

		m_dragging = 0;
	}

	return 0;
}

/*
http://www.web3d.org/specifications/ISO-IEC-19775/Part01/components/pointingsensor.html#TouchSensor

... These events are generated only when the pointing device has moved and changed
`over' state. Events are not generated if the geometry itself is animating and moving
underneath the pointing device.
*/

LRESULT CLX3DViewer::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	if (m_dragging == 1)
	{
		m_slider.OnMouseMove(point);
		UpdateWindow();

		double position = m_slider.GetPos();

		CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
		seeking->Seek(position);
	}

#if 0
	if (m_dragging)
	{
		CPoint offset = point - m_startpoint;

		if (m_dragging == 1)	// change XY position
		{
			CLViewpoint* pViewpoint = static_cast<CLViewpoint*>(m_viewpointStack[0]);

			CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
			CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

			double moveY = (double)-offset.y/20;
			double moveX = (double)offset.x/20;

			gmMatrix4 repos = gmMatrix4::identity();

			repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v);
			repos *= gmMatrix4::translate(moveX, moveY, 0);
			repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v).inverse();

			position->m_value = repos.transform(m_initialPosition);

			FireViewChange();
		}
		else if (m_dragging == 2) // change XZ position
		{
			CLViewpoint* pViewpoint = static_cast<CLViewpoint*>(m_viewpointStack[0]);

			CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
			CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

			double moveX = (double)offset.x/20;
			double moveZ = (double)offset.y/20;

			gmMatrix4 repos = gmMatrix4::identity();

			repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v);
			repos *= gmMatrix4::translate(moveX, 0, moveZ);
			repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v).inverse();

			position->m_value = repos.transform(m_initialPosition);

			FireViewChange();
		}
		else if (m_dragging == 3)
		{
			double r = 600;	// 360

			double rotateY = (double)offset.x*360/r;
			double rotateX = (double)offset.y*360/r;

			CLViewpoint* pViewpoint = static_cast<CLViewpoint*>(m_viewpointStack[0]);

			CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
			CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

			// Orientation
			if (rotateY != 0 || rotateX != 0)
			{
				/*
				float x = m_initialOrientation.m_v[0];
				float y = m_initialOrientation.m_v[1];
				float z = m_initialOrientation.m_v[2];
				float angle = m_initialOrientation.m_a;
				*/

				Quat4d q = m_initialOrientation.AxisAngleToQuaternion(/*x, y, z, angle*/);

				q.CombineQuaternion(/*x, y, z, angle,*/ 0, gmRadians(rotateY), gmRadians(rotateX));

				orientation->m_value = q.QuaternionToAxisAngle();//Quat4d(x, y, z, angle));

				/*
				orientation->m_value.m_v[0] = x;
				orientation->m_value.m_v[1] = y;
				orientation->m_value.m_v[2] = z;
				orientation->m_value.m_a = angle;
				*/

				orientation->m_value.m_v.normalize();
			}

			// Position
			{
				// Rotate position around centerOfRotation
				gmMatrix4 repos = gmMatrix4::identity();

				repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v);
				repos *= gmMatrix4::rotate(rotateY, gmVector3(0,1,0));
				repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v).inverse();

				position->m_value = repos.transform(m_initialPosition);
			}

			// Position
			{
				// Rotate position around centerOfRotation
				gmMatrix4 repos = gmMatrix4::identity();

				repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v);
				repos *= gmMatrix4::rotate(rotateX, gmVector3(1,0,0));
				repos *= gmMatrix4::rotate(rotateY, gmVector3(0,1,0));
				repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v).inverse();

				position->m_value = repos.transform(m_initialPosition);
			}

			FireViewChange();
		}
	}
	else
	{
		CRect client;
		GetClientRect(&client);
		int w = client.right;
		int h = client.bottom;
	//	wglMakeCurrent(hdc, m_hrc);

		double winx = point.x;
		double winy = client.bottom-point.y-1;

		GLint viewport[4] = { 0, 0, w, h };

		GLuint selectBuf[512];

		glSelectBuffer(512, selectBuf);
		glRenderMode(GL_SELECT);
		glInitNames();
		glPushName(0);

		{
			CLViewpoint* pViewpoint = NULL;

			if (m_viewpointStack.GetSize() > 0)
			{
				pViewpoint = static_cast<CLViewpoint*>(m_viewpointStack[0]);
			}
			else
			{
				// hmm...
			}

			//	glViewport(m_viewR[view].left, m_viewR[view].top, w, h);

			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPickMatrix(winx, winy, 3, 3, viewport);
	//		glLoadMatrixd(projm);
		//
			double fov;
			if (pViewpoint)
			{
				CLSFFloat* fieldOfView = static_cast<CLSFFloat*>(pViewpoint->m_fieldOfView);
				fov = fieldOfView->m_value;
			}
			else
			{
				fov = M_PI/4;
			}

			gluPerspective(gmDegrees(fov), (GLfloat)w / (GLfloat)h, 1.0, 10000.0);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			//glLoadMatrixf((float*)modelm);

			CX3DDrawContext xdc;

#if 0
			// NavigationInfo
			{
				BOOL headlight;

				if (m_navigationinfoStack.GetSize() > 0)
				{
					CLNavigationInfo* pNavigationInfo = static_cast<CLNavigationInfo*>(m_navigationinfoStack[0]);

					headlight = static_cast<CLSFBool*>(pNavigationInfo->m_headlight)->m_v;
				}
				else
				{
					// Default values
					headlight = TRUE;
				}

				glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

				if (TRUE)//TRUE/*bAnyLights*/)
				{
				}

				if (headlight)
				{
					GLfloat light_direction[4] = { 0, 0, 1, 0};	// directional
					GLfloat color[4] = {1, 1, 1, 1};
					GLfloat ambient[4] = {0, 0, 0, 1};

					glEnable(GL_LIGHT0+xdc.m_nLight);
					glLightfv(GL_LIGHT0+xdc.m_nLight, GL_POSITION, light_direction);
					glLightfv(GL_LIGHT0+xdc.m_nLight, GL_AMBIENT, ambient);
					glLightfv(GL_LIGHT0+xdc.m_nLight, GL_DIFFUSE, color);
					glLightfv(GL_LIGHT0+xdc.m_nLight, GL_SPECULAR , color);

					xdc.m_nLight++;
				}
			}
#endif

			if (pViewpoint)
			{
				CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
				CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);
				gmVector3t<float> norientation = orientation->m_value.m_v;
				norientation.normalize();

				glRotate(gmDegrees(orientation->m_value.m_a), -norientation);
				glTranslate(-position->m_value);
			}
			else
			{
				// TODO
				glTranslatef(0, 0, -180);
			}

			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

			if (m_scene)
			{
				CComQIPtr<CLRenderImplImpl> render = static_cast<CLSAIScene*>(m_scene)->m_root;
				if (render)
				{
					render->Draw(&xdc);
				}
			}

			glFlush();
		}

		GLint hits = glRenderMode(GL_RENDER);

		if (hits > 0)
		{
			MessageBeep(-1);
			GLuint* ptr = selectBuf;

			GLuint names = *ptr++;
			float z1 = *ptr++ / 0x7fffffff;
			float z2 = *ptr++ / 0x7fffffff;

			double winz = z2;

			double modelMatrix[16];
			double projMatrix[16];

			glGetDoublev(GL_MODELVIEW_MATRIX, modelMatrix);
			glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);

			double objx, objy, objz;
			gluUnProject(winx, winy, winz, modelMatrix, projMatrix, viewport, &objx, &objy, &objz);

			for (int n = 0; n < names; n++)
			{
			}
		}
	}
#endif

	return 0;
}

LRESULT CLX3DViewer::OnKeyDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	int nVirtKey = (int) wParam;    // virtual-key code 
	int lKeyData = lParam;          // key data 

	m_nKeyRepeat++;
	int repeatCount = m_nKeyRepeat;//lKeyData & 0xffff;

	LONG bCtrl = (GetAsyncKeyState(VK_CONTROL) & (1<<15));
	LONG bShift = (GetAsyncKeyState(VK_SHIFT) & (1<<15));

	double moveX = 0;
	double moveZ = 0;

	double rotateX = 0;
	double rotateY = 0;
	double rotateZ = 0;

	double rotate = 0.4 + 0.2*(repeatCount-1);
	if (rotate > 2) rotate = 2;

	BOOL bRunning = bShift;
	double speed = bRunning? 4: 2;

	switch (nVirtKey)
	{
	case VK_UP:
		{
			if (bCtrl)
			{
				rotateX = -rotate;
			}
			else
			{
				moveZ -= speed;
			}
		}
		break;

	case VK_DOWN:
		{
			if (bCtrl)
			{
				rotateX = rotate;
			}
			else
			{
				moveZ += speed;
			}
		}
		break;

	case VK_LEFT:
		{
			if (bCtrl)
			{
				moveX -= speed;
			}
			else
			{
				rotateY = rotate;
			}
		}
		break;

	case VK_RIGHT:
		{
			if (bCtrl)
			{
				moveX += speed;
			}
			else
			{
				rotateY = -rotate;
			}
		}
		break;
	}

	CLViewpoint* pViewpoint = static_cast<CLViewpoint*>(m_viewpointStack[0]);

	CLSFRotation* orientation = static_cast<CLSFRotation*>(pViewpoint->m_orientation);
	CLSFVec3f* position = static_cast<CLSFVec3f*>(pViewpoint->m_position);

	// Orientation
	if (rotateY != 0 || rotateX != 0 || rotateZ != 0)
	{
		/*
		float x = orientation->m_value.m_v[0];
		float y = orientation->m_value.m_v[1];
		float z = orientation->m_value.m_v[2];
		float angle = orientation->m_value.m_a;
		*/

		Quat4d q = orientation->m_value.AxisAngleToQuaternion();//x, y, z, angle);

		q.CombineQuaternion(/*x, y, z, angle,*/ gmRadians(rotateZ), gmRadians(rotateY), gmRadians(rotateX));

		orientation->m_value = q.QuaternionToAxisAngle();//x, y, z, angle);

		/*
		orientation->m_value.m_v[0] = x;
		orientation->m_value.m_v[1] = y;
		orientation->m_value.m_v[2] = z;
		orientation->m_value.m_a = angle;
		*/

		orientation->m_value.m_v.normalize();
	}

	// Position
	{
		gmMatrix4 repos = gmMatrix4::identity();

		repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v);
		repos *= gmMatrix4::translate(moveX, 0, moveZ);
		repos *= gmMatrix4::rotate(gmDegrees(orientation->m_value.m_a), -orientation->m_value.m_v).inverse();

		position->m_value = repos.transform(position->m_value);
	}

	FireViewChange();
#endif

	return 0;
}

LRESULT CLX3DViewer::OnKeyUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
#if 0
	m_nKeyRepeat = 0;
#endif
	return 0;
}

LRESULT CLX3DViewer::OnContextMenu(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	CPoint point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CMenu menu;
	menu.LoadMenu(MAKEINTRESOURCE(IDR_BROWSER));

	::TrackPopupMenu(menu.GetSubMenu(0), TPM_LEFTALIGN | TPM_TOPALIGN, point.x, point.y, 0/*reserved*/, m_hWnd, NULL);

	return 0;
}

LRESULT CLX3DViewer::OnEraseBkgnd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return TRUE;
}

LRESULT CLX3DViewer::OnBrowserDisplaySmooth(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	m_display = 0;
	FireViewChange();
#endif
	return 0;
}

LRESULT CLX3DViewer::OnBrowserDisplayFlat(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	m_display = 1;
	FireViewChange();
#endif
	return 0;
}

LRESULT CLX3DViewer::OnBrowserDisplayWireframe(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	m_display = 2;
	FireViewChange();
#endif
	return 0;
}

LRESULT CLX3DViewer::OnBrowserDisplayPoints(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	m_display = 3;
	FireViewChange();
#endif
	return 0;
}

LRESULT CLX3DViewer::OnBrowserHeadlight(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
#if 0
	if (m_navigationinfoStack.GetSize() > 0)
	{
		CLNavigationInfo* pNavigationInfo = static_cast<CLNavigationInfo*>(m_navigationinfoStack[0]);

		CLSFBool* pHeadlight = static_cast<CLSFBool*>(pNavigationInfo->m_headlight);

		// Toggle headlight
		if (pHeadlight->m_value)
			pHeadlight->m_value = false;
		else
			pHeadlight->m_value = true;

		FireViewChange();
	}
#endif
	return 0;
}

STDMETHODIMP CLX3DViewer::get_src(/*[out, retval]*/ BSTR *pVal)
{
	return m_src.CopyTo(pVal);
}

STDMETHODIMP CLX3DViewer::put_src(/*[in]*/ BSTR newVal)
{
	HRESULT hr;

	m_src = newVal;

	CComPtr<IServiceProvider> sp;
	hr = m_spClientSite->QueryInterface(IID_IServiceProvider, (void**)&sp);
	if (SUCCEEDED(hr))
	{
		CComPtr<IBindHost> bindHost;
		hr = sp->QueryService(SID_SBindHost, &bindHost);
		if (SUCCEEDED(hr))
		{
			CComPtr<IMoniker> imkName;

			CComPtr<IBindCtx> ctx;
			hr = CreateBindCtx(0/*reserved*/, &ctx);
			if (SUCCEEDED(hr))
			{
				hr = bindHost->CreateMoniker(m_src, NULL, &imkName, 0);
				if (SUCCEEDED(hr))
				{
					hr = m_filterGraph.CoCreateInstance(CLSID_LFilterGraph);
					if (SUCCEEDED(hr))
					{
						hr = m_filterGraph->AddSourceFilterForMoniker(imkName, ctx, L"", NULL);

						if (SUCCEEDED(hr))
						{
							CComQIPtr<ILMediaSeeking> seeking = m_filterGraph;
							LONGLONG duration;
							seeking->GetDuration(&duration);
							m_duration = duration / 100000.0;

							if (m_duration > 0)
							{
								m_slider.Enable(TRUE);
								m_slider.SetMaxPos(m_duration);
							}
							else
							{
								m_slider.Enable(FALSE);
							}

						// find the renderer filter
							CComPtr<ILBasicVideo> basicVideo;
							m_filterGraph->QueryFilterInterface(IID_ILBasicVideo, (IUnknown**)&basicVideo);
							if (basicVideo)
							{
								m_basicVideo = basicVideo;
							}
						}
					}
				}
			}
		}
	}

	return hr;

#if 0
#if 0
	m_viewpointStack.RemoveAll();
	m_navigationinfoStack.RemoveAll();
#endif

	if (m_scene)
	{
		m_scene->Release();
		m_scene = NULL;
	}

	CComBSTR m_src = newVal;

	CComQIPtr<IServiceProvider> sp = m_spClientSite;
	if (sp)
	{
		CComPtr<IMoniker> imkName;

		CComPtr<IBindHost> bindHost;
		if (SUCCEEDED(sp->QueryService(SID_SBindHost, &bindHost)))
		{
			bindHost->CreateMoniker(m_src, NULL, &imkName, 0);
		}
		else
		{
			CreateURLMoniker(NULL, m_src, &imkName);
		}

		if (imkName)
		{
			CComPtr<IBindCtx> bctx;
			if (SUCCEEDED(CreateBindCtx(0/*reserved*/, &bctx)))
			{
				CComPtr<IStream> stream;
				imkName->BindToStorage(bctx, NULL, IID_IStream, (void**)&stream);
				if (stream)
				{
					LPOLESTR szDisplayName;
					imkName->GetDisplayName(bctx, NULL, &szDisplayName);
					_bstr_t url = szDisplayName;
					CoTaskMemFree(szDisplayName);

					LPTSTR ext = PathFindExtension(url);
					if (ext && !strcmp(ext, ".mp4"))
					{
						m_file.CoCreateInstance(L"LMPEG4.MP4File");
						if (m_file)
						{
							//CComPtr<ILX3DScene> scene;

							CComPtr<IUnknown> unk;
							m_file->OpenStream(stream);
							
							//m_scene = static_cast<CComObject<CLSAIScene>*>(scene.p);
							//scene.Detach();

							CComQIPtr<ILBaseFilter> baseFilter = m_file;
							if (baseFilter)
							{
								CComPtr<ILPin> outputpin;
								baseFilter->GetPin(0, &outputpin);

								CComObject<CMoviePlayerFilter>::CreateInstance(&m_pFilter);
								m_pFilter->AddRef();
								m_pFilter->m_pMoviePlayer = this;

								// TODO, don't have it like this
								CComPtr<ILReferenceClock> clock;
								clock.CoCreateInstance(L"LMedia.LSystemClock");
								m_pFilter->m_clock = clock.Detach();
								m_pFilter->m_tStart = 0;

								outputpin->Connect(m_pFilter->m_pInput, NULL/*pMediaType*/);

								if (TRUE)
								{
									baseFilter->Run(0);
								}
							}
							else
							{
								::MessageBox(NULL, "Error opening file", "LViewer", MB_OK);
							}
						}
					}
					else
					{
						CComObject<CLSAIScene>::CreateInstance(&m_scene);
						if (m_scene)
						{
							m_scene->AddRef();

							m_scene->m_url = (BSTR)url;
							CoTaskMemFree(szDisplayName);

							m_scene->readStream(stream);

#if 0
							InitStacks();
#endif
						}
					}
				}
			}
		}
	}
#endif

	return S_OK;
}

// ILSAIBrowser

STDMETHODIMP CLX3DViewer::createX3DFromStream(IStream* stream, /*[out,retval]*/ ILX3DScene* *pVal)
{
	ATLASSERT(0);
	return E_NOTIMPL;
#if 0
	ATLASSERT(stream != NULL);
	ATLASSERT(pVal != NULL);
	if (stream == NULL) return E_INVALIDARG;
	if (pVal == NULL) return E_POINTER;

	*pVal = NULL;
	HRESULT hr = E_FAIL;	// Assume error

	CComObject<CLX3DScene>* pScene;
	CComObject<CLX3DScene>::CreateInstance(&pScene);
	if (pScene)
	{
		pScene->AddRef();

		hr = pScene->readStream(stream);

		if (SUCCEEDED(hr))
		{
			*pVal = pScene;
			(*pVal)->AddRef();
		}

		pScene->Release();
	}

	return hr;
#endif
}

STDMETHODIMP CLX3DViewer::getCurrentSpeed(/*[out,retval]*/ double *pVal)
{
	ATLASSERT(0);
	return E_NOTIMPL;
}

STDMETHODIMP CLX3DViewer::replaceWorld(ILX3DScene *scene)
{
	ATLASSERT(0);
	return E_NOTIMPL;
#if 0
	m_viewpointStack.RemoveAll();
	m_navigationinfoStack.RemoveAll();

	if (m_scene)
	{
		m_scene->Release();
		m_scene = NULL;
	}

	m_scene = static_cast<CComObject<CLSAIScene>*>(scene);

	if (m_scene)
	{
		InitStacks();
	}

	FireViewChange();
#endif

	return S_OK;
}
