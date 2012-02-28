#pragma once

namespace System
{

class CError;

template <class T> class CDOMErrorHandlerImpl :
public Web::IDOMErrorHandler//, &IID_IDOMErrorHandler, &LIBID_SVGLib>
{
public:

	long m_addOffset;

	CDOMErrorHandlerImpl()
	{
		m_addOffset = 0;
	}

// IDOMErrorHandler
	ErrorCode handleError(Web::IDOMError *error, bool* pVal)
	{
		ASSERT(0);
#if 0

		CError* pError = new CError;
		if (pError)
		{
//			pError->AddRef();

			error->get_severity(&pError->m_severity);
			pError->m_message = error->get_message();

			Web::ILDOMLocator* location;
			error->get_location(&location);

			pError->m_uri = location->get_uri();

			location->get_offset(&pError->m_offset);
			pError->m_offset += m_addOffset;

			// TODO, this aren't used here ?
			location->get_lineNumber(&pError->m_line);
			location->get_columnNumber(&pError->m_column);

			(static_cast<T*>(this))->m_errors.Add(pError);
		}

		*pVal = true;	// Continue if possible
#endif
		return Success;
	}
};

}
