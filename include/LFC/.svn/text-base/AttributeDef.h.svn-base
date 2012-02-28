namespace System
{

class LFCEXT AttributeDef
{
public:

	union Arg
	{
		bool boolVal;
		int8 int8Val;
		int16 int16Val;
		int32 int32Val;
		int64 int64Val;
		float floatVal;
		double doubleVal;
		StringA* astrVal;
		StringW* wstrVal;
	};

	void Store(TypeArchive& ar) const;
	void Load(TypeArchive& ar);

	ClassType* m_pClass;
//	Declarator* m_pMethod;
	unsigned short m_method;
	unsigned short m_nargs;
	Arg* m_args;
};

}	// System
