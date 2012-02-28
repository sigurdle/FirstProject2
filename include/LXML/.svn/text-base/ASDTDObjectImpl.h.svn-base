#ifndef __ASDTDOBJECTIMPL_H
#define __ASDTDOBJECTIMPL_H

namespace System
{
namespace Web
{

class ASDTDModel;

class CASDTDObject : public System::Object//IASObject
{
public:
	class CUserData
	{
	public:
		String m_key;
		Object* m_data;
		IASUserDataHandler* m_handler;
	};

	ASDTDModel* m_ownerASModel;

	vector<CUserData*> m_userdataList;

	IASModel* get_ownerASModel();

	ErrorCode setUserData(StringIn key, /*[in]*/ Object* data, /*[in]*/ IASUserDataHandler* handler, /*[out,retval]*/ System::Object* *pVal)
	{
		for (unsigned int i = 0; i < m_userdataList.GetSize(); i++)
		{
			if (key == m_userdataList[i]->m_key)
			{
				if (pVal)
				{
					*pVal = m_userdataList[i]->m_data;
				//	(*pVal)->AddRef();
				}

				if (data)
				{
					m_userdataList[i]->m_data = data;
					m_userdataList[i]->m_handler = handler;
				}
				else
				{
					delete m_userdataList[i];
					m_userdataList.RemoveAt(i);
				}

				return Success;
			}
		}

		if (data)
		{
			CUserData* pData = new CUserData;
			pData->m_key = key;
			pData->m_data = data;
			pData->m_handler = handler;

			m_userdataList.Add(pData);
		}

		if (pVal)
		{
			*pVal = NULL;
		}

		return Success;
	}
	System::Object* getUserData(System::StringW* key)
	{
		for (unsigned int i = 0; i < m_userdataList.GetSize(); i++)
		{
			if (*key == *m_userdataList[i]->m_key)
			{
				return m_userdataList[i]->m_data;
			//	(*pVal)->AddRef();
			}
		}

		return NULL;
	}

	ErrorCode GetElement(/*[out,retval]*/ Element* *pVal)
	{
		return Success;
	}
	ErrorCode SetElement(/*[in]*/ Element* newVal)
	{
		return Success;
	}
};

}	// Web
}

#endif
