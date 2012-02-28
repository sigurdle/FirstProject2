// Simple3DEditorView.h : interface of the CSimple3DEditorView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMPLE3DEDITORVIEW_H__59C66E8D_3792_4348_98D2_1486BAFAF25A__INCLUDED_)
#define AFX_SIMPLE3DEDITORVIEW_H__59C66E8D_3792_4348_98D2_1486BAFAF25A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CSimple3DEditorView : public CWindowImpl<CSimple3DEditorView>
{
public:
	DECLARE_WND_CLASS(NULL)

	BOOL PreTranslateMessage(MSG* pMsg)
	{
		pMsg;
		return FALSE;
	}

	BEGIN_MSG_MAP(CSimple3DEditorView)
		MESSAGE_HANDLER(WM_PAINT, OnPaint)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)

	END_MSG_MAP()


	CEdit m_edit;

	std::vector<gmVector3> m_vertices;

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
	//	m_edit.Create(m_hWnd, CRect(200, 200, 400, 400), NULL, WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_BORDER);

		for (int i = 0; i < 60; i++)
		{
			float x = cos(gmRadians(i*360/60))*10;
			float y = 0.1;
			float z = sin(gmRadians(i*360/60))*8;

			m_vertices.push_back(gmVector3(x, y, z));
		}

		return 0;
	}

	LRESULT OnPaint(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CPaintDC dc(m_hWnd);

		CRect rect;
		GetClientRect(&rect);

		double zf = 20;

		for (int i = 0; i < m_vertices.size(); i++)
		{
			int x = (m_vertices[i][0]*zf) + rect.Width()/2;
			int y = (m_vertices[i][2]*zf) + rect.Height()/2;

			dc.FillSolidRect(x-2, y-2, 4, 4, RGB(200, 100, 50));

			if (i == 0)
				dc.MoveTo(x, y);
			else
				dc.LineTo(x, y);
		}

#if 0
		double radius = 0.5;

		int cx = 0;
		int cy = 0;

		double PI = 3.14;

		int r = 60;

		int j = 0;
		int k = 0;
		double h = 0;

		CString str;

		while (k <= r)
		{
			int k0 = k;

			if (j == 0)
			{
				j++;
				k += 1;
			}
			else if (j == 1)
			{
				h = 0.1;
				j++;
			}
			else if (j == 2)
			{
				j++;
				k += 1;
			}
			else if (j == 3)
			{
				h = 0;
				j = 0;
			}

			double f = k * 2*PI / r;

			double x = cos(f)*(radius+h) + cx;
			double y = sin(f)*(radius+h) + cy;

			if (y <= 0)
			{
				printf("");
			}

			if (k0 == 0)
				dc.MoveTo(x, y);
			else
				dc.LineTo(x, y);

			char buf[256];
			sprintf(buf, "%g %g ", x, y);
			str += buf;
		}

		m_edit.SetWindowText(str);
#endif
		return 0;
	}
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SIMPLE3DEDITORVIEW_H__59C66E8D_3792_4348_98D2_1486BAFAF25A__INCLUDED_)
