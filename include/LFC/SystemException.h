namespace System
{

class LFCEXT SystemException : public Exception
{
public:
	CTOR SystemException(StringIn reason, Exception* innerException = nullptr, HRESULT hr = E_FAIL) : Exception(reason, innerException, hr)
	{
	}

	// copy constructor
	CTOR SystemException(const SystemException& e) : Exception(e)
	{
	}
};

}	// System
