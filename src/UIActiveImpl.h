#if 0
#pragma once

#include "UIActive.h"

class CUIEventHandlerImpl :
	public IUIEventHandler
{
public:
	STDMETHOD(handleActivateObjectEvent)(IUnknown* object, long* cookie)
	{
		*cookie = 0;
		return S_OK;
	}

	STDMETHOD(handleDeactivateObjectEvent)(IUnknown* object, long cookie, BOOL* bAllow)
	{
		return S_OK;
	}
};

class CUIActiveManagerImpl :
	public IUIActiveManager
{
public:
	class CUIEHandler;

	class CActiveObjectHandler
	{
	public:
		CUIEHandler* m_pHandler;
		long m_cookie;
	};

	class CActiveObject
	{
	public:
		CActiveObject* m_parent;
		CArray<CActiveObject*,CActiveObject*> m_childObjects;

		int m_nActived;
		CComPtr<IUnknown> m_p;
		CArray<CActiveObjectHandler*,CActiveObjectHandler*> m_handlers;

		CActiveObject()
		{
			m_nActived = 0;
			m_parent = NULL;
		}
	};

	class CUIEHandler
	{
	public:
		CComPtr<IUIEventHandler> m_handler;

		void NotifyEventHandlerActivatedObject(CActiveObject* pObject)
		{
			long cookie = 0;
			m_handler->handleActivateObjectEvent(pObject->m_p, &cookie);
			if (cookie != 0)
			{
				CActiveObjectHandler* pHandler = new CActiveObjectHandler;
				pHandler->m_pHandler = this;
				pHandler->m_cookie = cookie;

				pObject->m_handlers.Add(pHandler);
			}
		}

		/*
		void NotifyEventHandlerDeactivatedObject(CActiveObject* pObject)
		{
			m_handler->handleDeactivateObjectEvent(pObject->m_p, pObject->m_cookie);
		}
		*/
	};

	CArray<CActiveObject*,CActiveObject*> m_activeObjects;
	CArray<CUIEHandler*, CUIEHandler*> m_handlers;

	CActiveObject* GetActiveObject(IUnknown* object)
	{
		for (int i = 0; i < m_activeObjects.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_activeObjects[i]->m_p, object))
			{
				return m_activeObjects[i];
			}
		}

		return NULL;
	}

	int GetActiveObjectIndex(IUnknown* object)
	{
		for (int i = 0; i < m_activeObjects.GetSize(); i++)
		{
			if (IsUnknownEqualUnknown(m_activeObjects[i]->m_p, object))
			{
				return i;//m_activeObjects[i];
			}
		}

		return -1;
	}

	CUIEHandler* GetUIHandler(IUIEventHandler* handler)
	{
		for (int i = 0; i < m_handlers.GetSize(); i++)
		{
			if (m_handlers[i]->m_handler == handler)
			{
				return m_handlers[i];
			}
		}

		return NULL;
	}

	STDMETHOD(IsObjectActive)(IUnknown* object)
	{
		CActiveObject* pObject = GetActiveObject(object);
		if (pObject)
			return S_OK;
		else
			return S_FALSE;
	}

	STDMETHOD(GetActiveObjects)(IID itype, IUnknown** pobjects, long size, long* count)
	{
		if (pobjects == NULL)
		{
			if (count == NULL) return E_POINTER;

			*count = 0;

			for (int i = 0; i < m_activeObjects.GetSize(); i++)
			{
				IUnknown* p;
				m_activeObjects[i]->m_p->QueryInterface(itype, (void**)&p);
				if (p)
				{
					*count++;
					p->Release();
				}
			}
		}
		else
		{
			int n = 0;
			for (int i = 0; i < m_activeObjects.GetSize(); i++)
			{
				CComPtr<IUnknown> p;
				m_activeObjects[i]->m_p->QueryInterface(itype, (void**)&p);
				if (p)
				{
					(*pobjects = p)->AddRef();
					pobjects++;

					n++;
					if (n == size)
						break;
				}
			}

			if (count) *count = n;
		}
		return S_OK;
	}

	STDMETHODIMP ActivateObject(IUnknown* activatedBy, IUnknown *object)
	{
		CActiveObject* pObject = GetActiveObject(object);
		if (!pObject)
		{
			CActiveObject* pParent = NULL;
			if (activatedBy)
			{
				pParent = GetActiveObject(activatedBy);
				ATLASSERT(pParent);
			}

			pObject = new CActiveObject;
			pObject->m_p = object;

			pObject->m_parent = pParent;
			if (pParent) pParent->m_childObjects.Add(pObject);

			m_activeObjects.Add(pObject);

			CComQIPtr<IUIActivatable> a = object;
			if (a)
			{
				a->OnActivate(this);
			}
		}

		pObject->m_nActived++;

	// Notify all event handlers
		for (int i = 0; i < m_handlers.GetSize(); i++)
		{
			m_handlers[i]->NotifyEventHandlerActivatedObject(pObject);
		}
/*		else
			ATLASSERT(0);
*/
		//static_cast<T*>(this)->Fire_ActivatedObject(object);

		return S_OK;
	}

	STDMETHODIMP DeactivateObject(IUnknown *object)
	{
		int objectIndex = GetActiveObjectIndex(object);
		ATLASSERT(objectIndex >= 0);
		CActiveObject* pObject = m_activeObjects[objectIndex];
		//ATLASSERT(pObject);

		pObject->m_nActived--;
		if (pObject->m_nActived == 0)
		{
			CComQIPtr<IUIActivatable> a = object;
			if (a)
			{
				a->OnDeactivate(this);
			}

			BOOL bDeactivate = TRUE;

			for (int nh = 0; nh < pObject->m_handlers.GetSize(); nh++)
			{
				BOOL bAllow = TRUE;

				pObject->m_handlers[nh]->m_pHandler->m_handler->handleDeactivateObjectEvent(
					object, pObject->m_handlers[nh]->m_cookie, &bAllow);

				if (bAllow == FALSE)
					bDeactivate = FALSE;
			}

			if (bDeactivate)
			{
				// Deactivate all children (recursively)
				//for (int i = pObject->m_childObjects.GetSize()-1; i >= 0; i--)
				while (pObject->m_childObjects.GetSize() > 0)
				{
					DeactivateObject(pObject->m_childObjects[pObject->m_childObjects.GetSize()-1]->m_p);
				}

				if (pObject->m_parent)
				{
					for (int i = 0; i < pObject->m_parent->m_childObjects.GetSize(); i++)
					{
						if (pObject->m_parent->m_childObjects[i] == pObject)
						{
							pObject->m_parent->m_childObjects.RemoveAt(i);
							break;
						}
					}
					//ATLASSERT(i < pObject->m_parent->m_childObjects.GetSize());
				}
				delete pObject;
				m_activeObjects.RemoveAt(objectIndex);
			}
		}

		return S_OK;
	}

	STDMETHOD(AddEventHandler)(IUIEventHandler* handler)
	{
		CUIEHandler* pHandler = GetUIHandler(handler);
		ATLASSERT(pHandler == NULL);
		if (pHandler == NULL)
		{
			pHandler = new CUIEHandler;
			pHandler->m_handler = handler;
			m_handlers.Add(pHandler);

			for (int i = 0; i < m_activeObjects.GetSize(); i++)
			{
				CActiveObject* pObject = m_activeObjects[i];
				pHandler->NotifyEventHandlerActivatedObject(pObject);
			}

			return S_OK;
		}

		return E_FAIL;
	}

	STDMETHOD(RemoveEventHandler)(IUIEventHandler* handler)
	{
		for (int k = 0; k < m_handlers.GetSize(); k++)
		{
			if (m_handlers[k]->m_handler == handler)
			{
				for (int i = 0; i < m_activeObjects.GetSize(); i++)
				{
					CActiveObject* pObject = m_activeObjects[i];

					for (int j = 0; j < pObject->m_handlers.GetSize(); j++)
					{
						if (pObject->m_handlers[j]->m_pHandler == m_handlers[k])
						{
							BOOL bAllow = TRUE;
							handler->handleDeactivateObjectEvent(pObject->m_p, pObject->m_handlers[j]->m_cookie, &bAllow);

							delete pObject->m_handlers[j];
							pObject->m_handlers.RemoveAt(j);
							break;
						}
					}
				}

				delete m_handlers[k];
				m_handlers.RemoveAt(k);
				return S_OK;
			}
		}

		ATLASSERT(0);
		return S_OK;
	}
};

#endif