// ElementEventsDlg.cpp : Implementation of CElementEventsDlg
#include "stdafx.h"
#include "LXMLEditor.h"
#include "LXMLEditor2.h"
#include "ElementEventsDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CElementEventsDlg

#if 0

class CActiveXEvent : public CItem
{
public:
	CActiveXEvent()
	{
		m_type = SO_EVENT;
	}

	int m_memberid;
};

void BuildEvents(IUnknown* unk, CArray<CActiveXEvent*,CActiveXEvent*>& events)
{
	CComQIPtr<IConnectionPointContainer> connectionPtContainer = unk;
	if (connectionPtContainer)
	{
		CArray<IConnectionPoint*,IConnectionPoint*> connectionPoints;

		CComQIPtr<IEnumConnectionPoints> enumcpts;
		connectionPtContainer->EnumConnectionPoints(&enumcpts);
		if (enumcpts)
		{
		// Retrieve all connection points of object
			while (1)
			{
				IConnectionPoint* connectionpt;
				ULONG retrieved;

				enumcpts->Next(1, &connectionpt, &retrieved);
				if (retrieved == 0) break;

				connectionPoints.Add(connectionpt);
			}
		}

		CComQIPtr<IProvideClassInfo2> classinfo = unk;

		if (classinfo)
		{
			//classinfo->GetGUID(GUIDKIND_DEFAULT_SOURCE_DISP_IID
			ITypeInfo* pTInfo;
			HRESULT hr = classinfo->GetClassInfo(&pTInfo);

		// Needed to retrieve custom properties
			ITypeInfo2* pTInfo2;
			pTInfo->QueryInterface(IID_ITypeInfo2, (void**)&pTInfo2);
			if (pTInfo2) pTInfo2->Release();

			TYPEATTR* pType;
			pTInfo->GetTypeAttr(&pType);

			for (int i = 0; i < pType->cImplTypes; i++)
			{
				HREFTYPE pRefType = NULL;
				if (SUCCEEDED(pTInfo->GetRefTypeOfImplType(i, &pRefType)))
				{
					ITypeInfo* pTIInfo;
					pTInfo->GetRefTypeInfo(pRefType, &pTIInfo);

					TYPEATTR* pType;
					pTIInfo->GetTypeAttr(&pType);

					IConnectionPoint* connpt;
					connectionPtContainer->FindConnectionPoint(pType->guid, &connpt);
					if (connpt)
					{
					//	IID iid;
					//	connectionPoints[i]->GetConnectionInterface(&iid);

						/*
						CActiveXDispEvent* dispevent = new CActiveXDispEvent;
						dispevent->m_iid = pType->guid;
						connectionPoints[i]->Advise(dispevent, &dispevent->m_dwCookie);
						dispEvents.Add(dispevent);
						*/

						for (int i = 0; i < pType->cFuncs; i++)
						{
							FUNCDESC* pFuncDesc = NULL;
							if (SUCCEEDED(pTIInfo->GetFuncDesc(i, &pFuncDesc)))
							{
								BSTR bname;
								UINT pcNames;
								pTIInfo->GetNames(pFuncDesc->memid, &bname, 1, &pcNames);

								CActiveXEvent* event = new CActiveXEvent;
								event->m_name = bname;
								event->m_memberid = pFuncDesc->memid;

								events.Add(event);

								pTInfo->ReleaseFuncDesc(pFuncDesc);
							}
						}
					}

					pTIInfo->Release();
				}
			}

			pTInfo->Release();
		}

	/*
		for (int i = 0; i < connectionPoints.GetSize(); i++)
		{
			IID iid;
			connectionPoints[i]->GetConnectionInterface(&iid);

			CActiveXDispEvent* dispevent = new CActiveXDispEvent;
			dispevent->m_iid = iid;
			connectionPoints[i]->Advise(dispevent, &dispevent->m_dwCookie);

			m_pControl->m_dispEvents.Add(dispevent);
		}
	*/

	// Release connection points
		/*
		for (i = 0; i < connectionPoints.GetSize(); i++)
		{
			connectionPoints[i]->Release();
		}
		connectionPoints.RemoveAll();
		*/
	}
}

#endif