#include "stdafx.h"
#include "LXUI2.h"
#include "Grid.h"

#include <cfloat>

namespace System
{
namespace UI
{

Grid::ColumnDefinition::ColumnDefinition()
{
	m_MinWidth = float_NaN.value;
	m_MaxWidth = float_NaN.value;
}

Grid::RowDefinition::RowDefinition()
{
	m_MinHeight = float_NaN.value;
	m_MaxHeight = float_NaN.value;
}

//

DependencyProperty* Grid::s_ColumnProperty = RegisterProperty(WSTR("Column"), typeid(int), typeid(Grid), IntObject::GetObject(0));
DependencyProperty* Grid::s_RowProperty = RegisterProperty(WSTR("Row"), typeid(int), typeid(Grid), IntObject::GetObject(0));
DependencyProperty* Grid::s_ColumnSpanProperty = RegisterProperty(WSTR("ColumnSpan"), typeid(int), typeid(Grid), IntObject::GetObject(1));
DependencyProperty* Grid::s_RowSpanProperty = RegisterProperty(WSTR("RowSpan"), typeid(int), typeid(Grid), IntObject::GetObject(1));

Grid::Grid()
{
	m_rowDefinitions = new RowDefinitionCollection;
	m_columnDefinitions = new ColumnDefinitionCollection;
}

Grid::RowDefinitionCollection* Grid::get_RowDefinitions()
{
	return m_rowDefinitions;
}

void Grid::set_RowDefinitions(RowDefinitionCollection* rowDefinitions)
{
	m_rowDefinitions = rowDefinitions;
}

Grid::ColumnDefinitionCollection* Grid::get_ColumnDefinitions()
{
	return m_columnDefinitions;
}

void Grid::set_ColumnDefinitions(Grid::ColumnDefinitionCollection* columnDefinitions)
{
	m_columnDefinitions = columnDefinitions;
}

LDraw::SizeD Grid::MeasureOverride(LDraw::SizeD availSize)
{
	uint ncount = get_InternalChildren()->GetCount();//get_rchildList()->get_Size();

	for (uint i = 0; i < ncount; i++)
	{
		UIElement* pChild = get_InternalChildren()->get_Item(i);//(*get_rchildList())[i];
		pChild->Measure(LDraw::SizeD(0,0));
	}

	m_columnWidth.clear();
	m_rowHeight.clear();
	m_columnWidth.reserve(m_columnDefinitions->GetCount());
	m_rowHeight.reserve(m_rowDefinitions->GetCount());

	// Mininum column width / row height based on cells that span only one column
	for (uint i = 0; i < ncount; i++)
	{
		UIElement* pChild = get_InternalChildren()->get_Item(i);

		// TODO remove this
		//pChild->SetRParent(this);

		ASSERT(pChild->GetRParent() == this);

		int col = GetColumn(pChild);
		int row = GetRow(pChild);
		int colspan = GetColumnSpan(pChild);
		int rowspan = GetRowSpan(pChild);

		LDraw::SizeD minSize = pChild->get_DesiredSize();

		if (col >= m_columnWidth.size()) m_columnWidth.resize(col+1);
		if (row >= m_rowHeight.size()) m_rowHeight.resize(row+1);

		m_columnWidth[col] = MAX(m_columnWidth[col], minSize.Width);
		m_rowHeight[row] = MAX(m_rowHeight[row], minSize.Height);
	}

	for (int i = 0; i < m_columnDefinitions->GetCount(); i++)
	{
		ColumnDefinition* coldef = m_columnDefinitions->get_Item(i);

		GridLength* gridLength = coldef->get_Width();
		if (gridLength)
		{
			m_columnWidth[i] = gridLength->m_value;
		}

		double minWidth = coldef->get_MinWidth();
		if (!_isnan(minWidth))
		{
			if (m_columnWidth[i] < minWidth) m_columnWidth[i] = minWidth;
		}

		double maxWidth = coldef->get_MaxWidth();
		if (!_isnan(maxWidth))
		{
			if (m_columnWidth[i] > maxWidth) m_columnWidth[i] = maxWidth;
		}
	}

	for (int i = 0; i < m_rowDefinitions->GetCount(); i++)
	{
		RowDefinition* rowdef = m_rowDefinitions->get_Item(i);

		GridLength* gridLength = rowdef->get_Height();
		if (gridLength)
		{
			m_rowHeight[i] = gridLength->m_value;
		}

		double minHeight = rowdef->get_MinHeight();
		if (!_isnan(minHeight))
		{
			if (m_rowHeight[i] < minHeight) m_rowHeight[i] = minHeight;
		}

		double maxHeight = rowdef->get_MaxHeight();
		if (!_isnan(maxHeight))
		{
			if (m_rowHeight[i] > maxHeight) m_rowHeight[i] = maxHeight;
		}
	}

	LDraw::SizeD desiredSize(0,0);

	for (int i = 0; i < m_columnWidth.size(); i++)
	{
		desiredSize.Width += m_columnWidth[i];
	}

	for (int i = 0; i < m_rowHeight.size(); i++)
	{
		desiredSize.Height += m_rowHeight[i];
	}

	return desiredSize;
}

LDraw::SizeD Grid::ArrangeOverride(LDraw::SizeD finalSize)
{
	LDraw::SizeD minSize(0,0);

	for (int i = 0; i < m_columnWidth.size(); i++)
	{
		minSize.Width += m_columnWidth[i];
	}

	for (int i = 0; i < m_rowHeight.size(); i++)
	{
		minSize.Height += m_rowHeight[i];
	}

	// Distribute left-over space
	for (int i = 0; i < m_columnWidth.size(); i++)
	{
		if (i < m_columnDefinitions->GetCount())
		{
			ColumnDefinition* coldef = m_columnDefinitions->get_Item(i);

			// TODO

			GridLength* gridLength = coldef->get_Width();
			if (gridLength == NULL/* || gridLength->m_unit == Auto*/)
			{
				m_columnWidth[i] += finalSize.Width - minSize.Width;
			}
		}
		else	// missing column definition is like auto
		{
			m_columnWidth[i] += finalSize.Width - minSize.Width;
		}
	}

	// Distribute left-over space
	for (int i = 0; i < m_rowHeight.size(); i++)
	{
		if (i < m_rowDefinitions->GetCount())
		{
			RowDefinition* rowdef = m_rowDefinitions->get_Item(i);

		// TODO

			GridLength* gridLength = rowdef->get_Height();
			if (gridLength == NULL/* || gridLength->m_unit == Auto*/)
			{
				m_rowHeight[i] += finalSize.Height - minSize.Height;
			}
		}
		else	// missing row definition is like auto
		{
			m_rowHeight[i] += finalSize.Height - minSize.Height;
		}
	}

	vector<double> columnLeft;
	vector<double> rowTop;

	columnLeft.resize(m_columnWidth.size());
	rowTop.resize(m_rowHeight.size());

	double left = 0;
	for (int i = 0; i < m_columnWidth.size(); i++)
	{
		columnLeft[i] = left;
		left += m_columnWidth[i];
	}

	double top = 0;
	for (int i = 0; i < m_rowHeight.size(); i++)
	{
		rowTop[i] = top;
		top += m_rowHeight[i];
	}

	uint ncount = get_InternalChildren()->GetCount();
	for (uint i = 0; i < ncount; i++)
	{
		UIElement* pChild = get_InternalChildren()->get_Item(i);

		int ncol = GetColumn(pChild);
		int nrow = GetRow(pChild);
		int colspan = GetColumnSpan(pChild);
		int rowspan = GetRowSpan(pChild);

		/*
		RowDefinition* rowdef = NULL;
		ColumnDefinition* coldef = NULL;

		if (nrow < m_rowDefinitions->GetCount())
			rowdef = m_rowDefinitions->GetItem(nrow);

		if (ncol < m_columnDefinitions->GetCount())
			coldef = m_columnDefinitions->GetItem(ncol);

		GridLength* width = coldef->get_Width();
		double minwidth = coldef->get_MinWidth();
		double maxwidth = coldef->get_MaxWidth();

		GridLength* height = rowdef->get_Height();
		double minheight = rowdef->get_MinHeight();
		double maxheight = rowdef->get_MaxHeight();

		if (_isnan(minheight))
		{
		}

		double x = ncol;
		double y = nrow;

		if (true)
		{
			x = (int)x;
			y = (int)y;
		}

		double abswidth = width->m_value;
		double absheight = height->m_value;
		*/

		double width = 0;
		for (int i = 0; i < colspan; i++) width += m_columnWidth[ncol+i];
		
		double height = 0;
		for (int i = 0; i < rowspan; i++) height += m_rowHeight[nrow+i];

		pChild->Arrange(LDraw::RectD(columnLeft[ncol], rowTop[nrow], width, height));
	}

	return finalSize;
}

template class UIEXT Vector<Grid::RowDefinition*>;
template class UIEXT Vector<Grid::ColumnDefinition*>;

}	// UI
}
