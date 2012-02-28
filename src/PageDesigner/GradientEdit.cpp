// GradientEdit.cpp : Implementation of CGradientEdit

#include "stdafx.h"
#include "PageDesigner.h"
#include "PageDesigner2.h"

#include "GradientEdit.h"

void CreateGradient(CArray<Gdiplus::REAL, Gdiplus::REAL>& offsets, CArray<Gdiplus::Color,Gdiplus::Color&>& colors, IPDGradient* gradient)
{
	CComPtr<IObjectMap> stops;
	gradient->get_stops(&stops);

	long nstops;
	stops->get_length(&nstops);

	if (nstops >= 1)
	{
		CComPtr<IPDGradientStop> stop;
		stops->item(0, (IUnknown**)&stop);

		double last_offset;
		stop->get_offset(&last_offset);

		double last_middle;
		stop->get_middle(&last_middle);

		CComPtr<IPDColor> color;
		stop->getFinalColor(&color);

		double dred; color->getChannel(0, &dred);
		double dgreen; color->getChannel(1, &dgreen);
		double dblue; color->getChannel(2, &dblue);

		int last_red = dred;
		int last_green = dgreen;
		int last_blue = dblue;

		if (last_offset > 0)
		{
			colors.Add(Gdiplus::Color(255, last_red, last_green, last_blue));
			offsets.Add(0);
		}

		for (int i = 1; i < nstops; i++)
		{
			CComPtr<IPDGradientStop> stop1;
			stops->item(i, (IUnknown**)&stop1);

			double offset1;
			stop1->get_offset(&offset1);

			double middle1;
			stop1->get_middle(&middle1);

			CComPtr<IPDColor> color1;
			stop1->getFinalColor(&color1);

			double dred1; color1->getChannel(0, &dred1);
			double dgreen1; color1->getChannel(1, &dgreen1);
			double dblue1; color1->getChannel(2, &dblue1);

			int red1 = dred1;
			int green1 = dgreen1;
			int blue1 = dblue1;

			int mred = last_red + (red1-last_red)/2;
			int mgreen = last_green + (green1-last_green)/2;
			int mblue = last_blue + (blue1-last_blue)/2;
			double moffset = last_offset + (offset1-last_offset)*last_middle;

			colors.Add(Gdiplus::Color(255, last_red, last_green, last_blue));
			offsets.Add(last_offset);

			colors.Add(Gdiplus::Color(255, mred, mgreen, mblue));
			offsets.Add(moffset);

			last_red = red1;
			last_green = green1;
			last_blue = blue1;
			last_offset = offset1;
			last_middle = middle1;
		}

		colors.Add(Gdiplus::Color(255, last_red, last_green, last_blue));
		offsets.Add(last_offset);

	// Finish of to 100%
		if (last_offset < 1)
		{
			colors.Add(Gdiplus::Color(255, last_red, last_green, last_blue));
			offsets.Add(1);
		}
	}

//	grad->SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());
}

/////////////////////////////////////////////////////////////////////////////
// CGradientEdit

void CGradientEdit::FinalRelease()
{
	if (m_gradient)
	{
		CComQIPtr<INotifySend> cp = m_gradient;
		cp->Unadvise(this);

		m_gradient.Release();
	}
}

HRESULT CGradientEdit::OnDraw(ATL_DRAWINFO& di)
{
	HDC hDC = di.hdcDraw;
	CRect& rc = *(CRect*)di.prcBounds;

	FillSolidRect(hDC, &rc, m_clrBackColor);

	if (m_gradient)
	{
		Gdiplus::Graphics graphics(hDC);

		CArray<Gdiplus::REAL, Gdiplus::REAL> offsets;
		CArray<Gdiplus::Color,Gdiplus::Color&> colors;

		CreateGradient(offsets, colors, m_gradient);

		Gdiplus::LinearGradientBrush grad(
				Gdiplus::Point(4, 0), Gdiplus::Point(rc.right-4, 0),
				Gdiplus::Color(0,0,0,0), Gdiplus::Color(0,0,0,0));
		grad.SetInterpolationColors(colors.GetData(), offsets.GetData(), colors.GetSize());

		graphics.FillRectangle(&grad, 4, 8, rc.Width()-8, rc.bottom-16-8);

	// Draw knobs
		CComPtr<IObjectMap> stops;
		m_gradient->get_stops(&stops);

		long nstops;
		stops->get_length(&nstops);

		for (int i = 0; i < nstops; i++)
		{
			CComPtr<IPDGradientStop> stop;
			stops->item(i, (IUnknown**)&stop);

			Gdiplus::Pen blackpen(Gdiplus::Color(0, 0, 0), 1);

			double offset;
			stop->get_offset(&offset);

			double middle;
			stop->get_middle(&middle);

			if (i < nstops-1)
			{
				CComPtr<IPDGradientStop> stop1;
				stops->item(i+1, (IUnknown**)&stop1);

				double offset1;
				stop1->get_offset(&offset1);

				int x = 4 + (rc.Width()-8)*(offset + (offset1-offset)*middle);

				graphics.DrawLine(&blackpen, x-4, 4, x, 0);
				graphics.DrawLine(&blackpen, x, 0, x+4, 4);
				graphics.DrawLine(&blackpen, x+4, 4, x, 8);
				graphics.DrawLine(&blackpen, x, 8, x-4, 4);
			}

			CComPtr<IPDColor> color;
			//stop->get_color(&color);
			stop->getFinalColor(&color);

			double red; color->getChannel(0, &red);
			double green; color->getChannel(1, &green);
			double blue; color->getChannel(2, &blue);

			int x = 4 + offset * (rc.Width()-8);

			Gdiplus::Rect knobrc(x-4, rc.bottom-12, 8, 10);

			Gdiplus::SolidBrush brush(Gdiplus::Color(red, green, blue));

			graphics.FillRectangle(&brush, knobrc);
			graphics.DrawRectangle(&blackpen, knobrc);

			Gdiplus::SolidBrush blackbrush(Gdiplus::Color(0, 0, 0));
			Gdiplus::Point pts[] =
			{
				Gdiplus::Point(x-4, rc.bottom-12),
				Gdiplus::Point(x, rc.bottom-16),
				Gdiplus::Point(x+4, rc.bottom-12),
			};

			if (stop == m_stop)
			{
				graphics.FillPolygon(&blackbrush, pts, 3);
			}
			else
			{
				graphics.DrawPolygon(&blackpen, pts, 3);
			}
			/*
			graphics.DrawLine(&pen, x-4, rc.bottom-12, x, rc.bottom-16);
			graphics.DrawLine(&pen, x, rc.bottom-16, x+4, rc.bottom-12);
			*/
		}
	}

	return S_OK;
}

LRESULT CGradientEdit::OnLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_gradient)
	{
		m_stop.Release();

		CComPtr<IObjectMap> stops;
		m_gradient->get_stops(&stops);

		long nstops;
		stops->get_length(&nstops);

		if (point.y < 8)
		{
			for (int i = 0; i < nstops; i++)
			{
				CComPtr<IPDGradientStop> stop;
				stops->item(i, (IUnknown**)&stop);

				double offset;
				stop->get_offset(&offset);

				double middle;
				stop->get_middle(&middle);

				if (i < nstops-1)
				{
					CComPtr<IPDGradientStop> stop1;
					stops->item(i+1, (IUnknown**)&stop1);

					double offset1;
					stop1->get_offset(&offset1);

					int x = 4 + (client.Width()-8)*(offset + (offset1-offset)*middle);

					if (abs(point.x-x) < 4)
					{
						m_stop = stop;
						break;
					}
				}
			}

			if (m_stop)
			{
				m_dragging = 2;
			}
		}
		else
		{
			for (int i = 0; i < nstops; i++)
			{
				CComPtr<IPDGradientStop> stop;
				stops->item(i, (IUnknown**)&stop);

				double offset;
				stop->get_offset(&offset);

				double middle;
				stop->get_middle(&middle);

				int x = 4 + offset * (client.Width()-8);

				if (abs(point.x-x) < 4)
				{
					m_stop = stop;
					break;
				}
			}

			if (m_stop == NULL)
			{
				m_gradient->createStop(&m_stop);
				m_stop->setColorRGB(255, 0, 0);

				double offset = (double)(point.x-4)/(client.Width()-8);

				if (offset < 0) offset = 0;
				else if (offset > 1) offset = 1;

				m_stop->put_offset(offset);
				m_gradient->append(m_stop);
			}

			if (m_stop)
			{
				Fire_ClickStop(m_stop);

				m_dragging = 1;
			}
		}

		Invalidate();

		if (m_dragging)
		{
			SetCapture();
		}
	}
	else
	{
		Fire_ClickOnEmpty();
	}

	return 0;
}

LRESULT CGradientEdit::OnLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if (m_dragging)
	{
		ReleaseCapture();
		m_dragging = 0;

	//	m_stop.Release();
	}

	return 0;
}

LRESULT CGradientEdit::OnMouseMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT point;
	point.x = (short)LOWORD(lParam);
	point.y = (short)HIWORD(lParam);

	CRect client;
	GetClientRect(&client);

	if (m_dragging)
	{
		if (m_dragging == 1)
		{
			double offset = (double)(point.x-4)/(client.Width()-8);

			if (offset < 0) offset = 0;
			else if (offset > 1) offset = 1;

			m_stop->put_offset(offset);
		}
		else if (m_dragging == 2)
		{
			CComPtr<IPDGradientStop> stop1;
			m_stop->get_nextSibling(&stop1);

			double offset;
			double offset1;

			m_stop->get_offset(&offset);
			stop1->get_offset(&offset1);

			double middle;

			double off = (double)(point.x-4)/(client.Width()-8);

			middle = (off - offset) / (offset1-offset);

			if (middle < 0.13) middle = 0.13;
			else if (middle > 0.87) middle = 0.87;

			m_stop->put_middle(middle);
		}

	//	Invalidate();
	}

	return 0;
}

STDMETHODIMP CGradientEdit::get_gradient(IPDGradient **pVal)
{
	if (pVal == NULL) return E_POINTER;
	*pVal = m_gradient;
	if (*pVal) (*pVal)->AddRef();
	return S_OK;
}

STDMETHODIMP CGradientEdit::put_gradient(IPDGradient *newVal)
{
	if (m_gradient)
	{
		CComQIPtr<INotifySend> cp = m_gradient;
		cp->Unadvise(this);
	}

	m_gradient = newVal;

	if (m_gradient)
	{
		CComQIPtr<INotifySend> cp = m_gradient;
		DWORD cookie;
		cp->Advise(this, &cookie);
	}

	Invalidate();

	return S_OK;
}
