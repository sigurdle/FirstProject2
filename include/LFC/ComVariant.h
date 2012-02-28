namespace System
{

class LFCEXT ComVariant : public VARIANT
{
public:

	CTOR ComVariant() throw()
	{
		this->vt = VT_EMPTY;
	}

	CTOR ComVariant(decltype(nullptr)) throw()
	{
		this->vt = VT_NULL;
	}

#ifndef __LERSTAD__

	CTOR ComVariant(const VARIANT& other)
	{
		ThrowHr(::VariantCopy(this, &other));
	}

	CTOR ComVariant(bool value) throw()
	{
		this->vt = VT_BOOL;
		this->boolVal = value? VARIANT_TRUE: VARIANT_FALSE;
	}

	CTOR ComVariant(char value) throw()
	{
		this->vt = VT_I1;
		this->cVal = value;
	}

	CTOR ComVariant(signed char value) throw()
	{
		this->vt = VT_I1;
		this->cVal = value;
	}

	CTOR ComVariant(unsigned char value) throw()
	{
		this->vt = VT_UI1;
		this->bVal = value;
	}

	CTOR ComVariant(short value) throw()
	{
		this->vt = VT_I2;
		this->iVal = value;
	}

	CTOR ComVariant(unsigned short value) throw()
	{
		this->vt = VT_UI2;
		this->uiVal = value;
	}

	CTOR ComVariant(int value) throw()
	{
		this->vt = VT_I4;
		this->intVal = value;
	}

	CTOR ComVariant(int value, VARTYPE vartype)
	{
		if (vartype == VT_INT || vartype == VT_I4)
		{
			this->vt = vartype;
			this->intVal = value;
		}
		else
		{
			vt = VT_ERROR;
			scode = E_INVALIDARG;
			raise(ArgumentException());
		}
	}

	CTOR ComVariant(unsigned int value) throw()
	{
		this->vt = VT_UI4;
		this->uintVal = value;
	}

	CTOR ComVariant(unsigned int value, VARTYPE vartype)
	{
		if (vartype == VT_UINT || vartype == VT_UI4)
		{
			this->vt = vartype;
			this->uintVal = value;
		}
		else
		{
			vt = VT_ERROR;
			scode = E_INVALIDARG;
			raise(ArgumentException());
		}
	}

	CTOR ComVariant(long long value) throw()
	{
		this->vt = VT_I8;
		this->llVal = value;
	}

	CTOR ComVariant(unsigned long long value) throw()
	{
		this->vt = VT_UI8;
		this->ullVal = value;
	}

	CTOR ComVariant(float value) throw()
	{
		this->vt = VT_R4;
		this->fltVal = value;
	}

	CTOR ComVariant(double value) throw()
	{
		this->vt = VT_R8;
		this->dblVal = value;
	}

	CTOR ComVariant(double value, VARTYPE vartype)
	{
		if (vartype == VT_R8 || vartype == VT_DATE)
		{
			this->vt = vartype;
			this->dblVal = value;
		}
		else
		{
			vt = VT_ERROR;
			scode = E_INVALIDARG;

			raise(ArgumentException());
		}
	}

#ifndef __LERSTAD__

	CTOR ComVariant(CY value)
	{
		this->vt = VT_CY;
		this->cyVal = value;
	}

	CTOR ComVariant(const DECIMAL& value)
	{
		this->decVal = value;	// NOTE: must set this first, look into VARIANT struct to see why...
		this->vt = VT_DECIMAL;
	}

#endif

	CTOR ComVariant(const SYSTEMTIME* systime)
	{
		this->vt = VT_DATE;
		BOOL success = SystemTimeToVariantTime((SYSTEMTIME*)systime, &this->dblVal);

		if (!success)
		{
			vt = VT_ERROR;
			scode = E_INVALIDARG;

			raise(ArgumentException("arg"));
		}
	}

	CTOR ComVariant(IUnknown* p)
	{
		this->vt = VT_UNKNOWN;
		this->punkVal = p;
		if (p) p->AddRef();
	}

	CTOR ComVariant(IDispatch* p)
	{
		this->vt = VT_DISPATCH;
		this->pdispVal = p;
		if (p) p->AddRef();
	}

	CTOR ComVariant(ComBSTR&& str)
	{
		this->vt = VT_BSTR;
		this->bstrVal = str.Detach();
	}

	CTOR ComVariant(ComVariant&& other)
	{
		memcpy(this, &other, sizeof(VARIANT));
		other.vt = VT_EMPTY;		// reset other
	}

#ifndef __LERSTAD__

	template<class T>
	CTOR ComVariant(ComPtr<T>&& other)
	{
		this->vt = VT_UNKNOWN;
		this->punkVal = other.Detach();
	}

	// TODO T base of IDispatch
	CTOR ComVariant(ComPtr<IDispatch>&& other)
	{
		this->vt = VT_DISPATCH;
		this->pdispVal = other.Detach();
	}

	ComVariant& operator = (ComBSTR&& str)
	{
		ThrowHr(::VariantClear(this));

		this->vt = VT_BSTR;
		this->bstrVal = str.Detach();

		return *this;
	}

	ComVariant& operator = (ComVariant&& other)
	{
		if (this != &other)
		{
			ThrowHr(::VariantClear(this));
			memcpy(this, &other, sizeof(VARIANT));
			other.vt = VT_EMPTY;
		}
		return *this;
	}

#endif

	~ComVariant()
	{
		::VariantClear(this);
	}

	void CopyTo(VARIANT* v) const
	{
		ThrowHr(::VariantCopy(v, this));
	}

	void Attach(const VARIANT& other)
	{
		ASSERT(this != &other);

		ThrowHr(::VariantClear(this));
		memcpy(this, &other, sizeof(VARIANT));
	}

	VARIANT Detach() throw()
	{
		VARIANT v;
		memcpy(&v, this, sizeof(VARIANT));

		this->vt = VT_EMPTY;
		return v;
	}

	// comparison

	bool operator == (decltype(nullptr)) const throw()
	{
		if (this->vt == VT_NULL) return true;
		if (this->vt == VT_EMPTY) return true;

		if (this->vt == VT_UNKNOWN ||
			this->vt == VT_DISPATCH ||
			this->vt == VT_BSTR)
		{
			return this->punkVal == nullptr;
		}

		return false;
	}

	bool operator != (decltype(nullptr)) const throw()
	{
		return !operator==(nullptr);
	}

	bool operator == (const ComVariant& other) const
	{
		HRESULT hr = ::VarCmp((VARIANT*)this, (VARIANT*)&other, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_EQ;
	}

	bool operator != (const ComVariant& other) const
	{
		HRESULT hr = ::VarCmp((VARIANT*)this, (VARIANT*)&other, LOCALE_USER_DEFAULT, 0);
		return hr != VARCMP_EQ;
	}

	bool operator < (const ComVariant& other) const
	{
		HRESULT hr = ::VarCmp((VARIANT*)this, (VARIANT*)&other, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_LT;
	}

	bool operator > (const ComVariant& other) const
	{
		HRESULT hr = ::VarCmp((VARIANT*)this, (VARIANT*)&other, LOCALE_USER_DEFAULT, 0);
		return hr == VARCMP_GT;
	}

	int CompareNoCase(const ComVariant& other) const
	{
		HRESULT hr = ::VarCmp((VARIANT*)this, (VARIANT*)&other, LOCALE_USER_DEFAULT, NORM_IGNORECASE);
		ASSERT(hr != VARCMP_NULL);	// TODO
		return hr - 1;
	}

	// conversion

	operator bool () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_BOOL));
		return !!result.boolVal;
	}

	operator char () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_I1));
		return result.cVal;
	}

	operator signed char () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_I1));
		return result.cVal;
	}

	operator unsigned char () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_UI1));
		return result.bVal;
	}

	operator short () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_I2));
		return result.iVal;
	}

	operator unsigned short () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_UI2));
		return result.uiVal;
	}

	operator int () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_I4));
		return result.intVal;
	}

	operator unsigned int () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_UI4));
		return result.uintVal;
	}

	operator long long () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_I8));
		return result.llVal;
	}

	operator unsigned long long () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_UI8));
		return result.ullVal;
	}

	operator float () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_R4));
		return result.fltVal;
	}

	operator double () const
	{
		VARIANT result;
		ThrowHr(::VariantChangeType(&result, this, 0, VT_R8));
		return result.dblVal;
	}

	operator ComBSTR () const
	{
		if (this->vt == VT_BSTR)
		{
			return ComBSTR(this->bstrVal);
		}
		else
		{
			VARIANT result;
			ThrowHr(::VariantChangeType(&result, this, 0, VT_BSTR));

			ComBSTR str;
			str.Attach(result.bstrVal);
			return str;
		}
	}

	operator SYSTEMTIME () const
	{
		if (this->vt == VT_DATE)
		{
			SYSTEMTIME systime;
			BOOL success = VariantTimeToSystemTime(this->dblVal, &systime);
			return systime;
		}

		raise(SystemException("vt != VT_DATE"));
	}

	// math

	ComVariant operator - () const
	{
		ComVariant result;
		ThrowHr(::VarNeg((VARIANT*)this, &result));
		return result;
	}

	ComVariant operator ! () const
	{
		ComVariant result;
		ThrowHr(::VarNot((VARIANT*)this, &result));
		return result;
	}

	ComVariant Abs() const
	{
		ComVariant result;
		ThrowHr(::VarAbs((VARIANT*)this, &result));
		return result;
	}

	ComVariant operator + (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarAdd((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator - (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarSub((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator * (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarMul((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator / (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarDiv((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator % (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarMod((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator & (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarAnd((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator | (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarOr((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	ComVariant operator ^ (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarXor((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}

	/*
	ComVariant operator += (const ComVariant& other) const
	{
		ComVariant result;
		ThrowHr(::VarAdd((VARIANT*)this, (VARIANT*)&other, &result));
		return result;
	}
	*/
#endif
};

#if 0

class LFCEXT PropVariant : public PROPVARIANT
{
public:

	CTOR PropVariant(const FILETIME& ft)
	{
		this->vt = VT_FILETIME;
		this->filetime = ft;
	}

	PropVariant& operator = (const FILETIME& rhs)
	{
		VariantClear((VARIANT*)this);
		this->vt = VT_FILETIME;
		this->filetime = rhs;
		return *this;
	}

	operator FILETIME () const
	{
		if (this->vt == VT_FILETIME)
		{
			return this->filetime;
		}

		raise(SystemException("vt != VT_FILETIME"));
	}

};
#endif

}	// System
