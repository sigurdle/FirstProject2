#ifndef __LDOCUMENTASIMPL_H
#define __LDOCUMENTASIMPL_H

namespace System
{
namespace Web
{

template <class T> class DocumentASImpl :
	public IDocumentAS
{
public:
	IASModel* m_activeASModel;

public:
	IASModel* get_activeASModel()
	{
		return m_activeASModel;
	}

	void set_activeASModel(IASModel* newVal)
	{
		if (m_activeASModel != newVal)
		{
			if (static_cast<T*>(this)->m_definedElementTypes)
			{
				static_cast<T*>(this)->m_definedElementTypes = NULL;
			}

			m_activeASModel = newVal;
		}
	}

	void validate()
	{
	}
};

}	// Web
}

#endif	// __LDOCUMENTASIMPL_H
