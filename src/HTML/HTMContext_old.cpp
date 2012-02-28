#if 0
void CHTMContext::PlaceInlineBox(CHTMPElement* pElement, CHTMBoxItem* pBox)
{
	ATLASSERT(m_pBlockBox);

	int boxwidth = pBox->m_outerRect.Width;
	int boxheight = pBox->m_outerRect.Height;

	if (pBox->m_type == 1 && !wcscmp(((CHTMBox*)pBox)->m_pElement->m_float, L"left"))
	{
		CHTMBox* pFloatBox = (CHTMBox*)pBox;

		CHTMPElement* pPElement = pFloatBox->m_pElement;
		pBox->m_parentBox = m_pBlockBox;

	// Move to right of previous left floating box
	// If there's not enough room there, move down below previous
	// left floating box
		if ((m_pPrevLeftFloatBox == NULL) ||
			(m_linepos.x/*m_pPrevLeftFloatBox->m_outerRect.right*/ + pFloatBox->m_outerRect.Width < m_pBlockBox->m_innerRect.Width))
		{
			pFloatBox->m_outerRect.Offset(m_linepos.x, 0);

		// Move below current line
			if (m_pCurLineBox)
			{
			// TODO, what if this line changes height later on?
				pFloatBox->m_outerRect.Offset(0, m_pCurLineBox->m_innerRect.GetBottom());
			}
		}
		else
	// Move down below previous left floating box
		{
			pFloatBox->m_outerRect.Offset(
				0, m_pPrevLeftFloatBox->m_outerRect.GetBottom());
		}

	// New line boxes created from now on, start at the right/top edge of
	// this floating box
		m_linepos.x = pFloatBox->m_outerRect.GetRight();
		m_linepos.y = pFloatBox->m_outerRect.Y;

		m_floatBottom = pFloatBox->m_outerRect.GetBottom();

		m_pPrevLeftFloatBox = pFloatBox;
	}
	else
	{
	// Reached right border, wrap to next line (create new line box)
		if ((m_linepos.x + m_curpos.x + boxwidth) > m_pBlockBox->m_innerRect.Width)
		{
			if (m_pCurLineBox) m_pCurLineBox->Adjust();
			m_pCurLineBox = NULL;
			m_pCurInlineBox = NULL;

			if (m_linepos.y >= m_floatBottom)
			{
				// We've gone below the float, so reset the left edge to 0
				m_linepos.x = 0;
			}

			m_curpos.x = 0;
			m_curpos.y = 0;

		// If there still is no room on the line, begin new line
		// below any floats
			if ((m_linepos.x + m_curpos.x + boxwidth) > m_pBlockBox->m_innerRect.Width)
			{
				m_linepos.y = max(m_linepos.y, m_floatBottom);
				// We've gone below the float, so reset the left edge to 0
				m_linepos.x = 0;
			}
		}

		if (!m_pCurLineBox)
		{
			m_pCurLineBox = new CHTMLineBox;

			m_pCurLineBox->m_outerRect.X = m_linepos.x;
			m_pCurLineBox->m_outerRect.Y = m_linepos.y;
			m_pCurLineBox->m_outerRect.Width = m_pBlockBox->m_innerRect.Width-m_linepos.x;

			m_pCurLineBox->m_innerRect.X = 0;
			m_pCurLineBox->m_innerRect.Y = 0;
			m_pCurLineBox->m_innerRect.Width = m_pCurLineBox->m_outerRect.Width;

			m_pBlockBox->AddChildBox(m_pCurLineBox);
		}

		if (!m_pCurInlineBox)
		{
			m_pCurInlineBox = new CHTMInlineBox;
			m_pCurInlineBox->m_pElement = pElement;

			m_pCurInlineBox->m_outerRect.X = m_curpos.x - m_pCurLineBox->m_outerRect.X;
			m_pCurInlineBox->m_outerRect.Y = 0;

			m_pCurInlineBox->m_innerRect.X = 0;
			m_pCurInlineBox->m_innerRect.Y = 0;

			m_pCurLineBox->AddChildBox(m_pCurInlineBox);

			/*
			if (m_pCurInlineBox->m_pElement->getCSSLineHeight())
			{
			}
			*/
		}

		pBox->m_outerRect.X = m_curpos.x - m_pCurInlineBox->m_outerRect.X-m_pCurLineBox->m_outerRect.X;
		pBox->m_outerRect.Y = 0;

		m_curpos.x += boxwidth;

		if (m_curpos.x > maxx) maxx = m_curpos.x;

	// Adjust inline box
		m_pCurInlineBox->m_innerRect.Width = pBox->m_outerRect.GetRight();
		m_pCurInlineBox->m_outerRect.Width = m_pCurInlineBox->m_innerRect.Width;

		if (pBox->m_outerRect.Height > m_pCurInlineBox->m_innerRect.Height)
		{
			double lineheight = m_pCurInlineBox->m_pElement->m_lineHeight;

			if (lineheight != 0)
				m_pCurInlineBox->m_innerRect.Height = lineheight;
			else
				m_pCurInlineBox->m_innerRect.Height = pBox->m_outerRect.Height;

			m_pCurInlineBox->m_outerRect.Height = m_pCurInlineBox->m_innerRect.Height;
		}

	// Adjust line box
		if (m_pCurInlineBox->m_outerRect.Height > m_pCurLineBox->m_innerRect.Height)
		{
			double blocklineheight = m_pBlockBox->m_pElement->getCSSLineHeight();

			m_pCurLineBox->m_innerRect.Height = max(m_pCurInlineBox->m_outerRect.Height, blocklineheight);
			m_pCurLineBox->m_outerRect.Height = m_pCurLineBox->m_innerRect.Height;

			m_linepos.y = max(m_linepos.y, m_pCurLineBox->m_outerRect.GetBottom());
		}

	// Add the boxitem to the inlinebox
		m_pCurInlineBox->AddChildBox(pBox);
	}
}

#endif