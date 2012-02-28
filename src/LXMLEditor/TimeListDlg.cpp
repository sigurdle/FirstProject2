#include "stdafx.h"
#include "LXMLEditor2.h"
#include "TimeListDlg.h"

namespace System
{
namespace LXmlEdit
{
long CTimeListDlg::OnInitDialog()
{
#if 0
	SetWindowText(m_title);
#endif
	unsigned int length = m_timeList->get_length();
	for (unsigned int i = 0; i < length; i++)
	{
		Web::SMILTime* time = m_timeList->item(i);
	}

	return 1;  // Let the system set the focus
}

}
}
