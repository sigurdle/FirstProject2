namespace System
{
namespace Gui
{

class GUIEXT DependencyClass : public Object
{
public:

	CTOR DependencyClass(const Type_Info& classtype, DependencyClass* baseClass);
	virtual ~DependencyClass();

	ClassType* GetClassType() const throw();

	unsigned int GetLocalPropertiesCount() const throw()
	{
		return m_localPropertyCount;
	}

	DependencyProperty* GetLocalProperty(unsigned int index) throw(ArgumentOutOfRangeException*);
	DependencyProperty* GetLocalProperty(StringIn name) throw();

	DependencyClass* GetBaseClass() const throw();

	static DependencyClass* GetClass(ClassType* pClassType) throw();

	template<class property_type> DependencyProperty* CreateComputedProperty(StringIn name, property_type propertyType, const Expressive::typed_expression<property_type>& exp, PropertyMetadata* metadata = nullptr)
	{
		return new DependencyProperty(this, name, typeid(property_type), exp, metadata);
	}

	static DependencyClass* FindClass(StringIn name) throw();
	static DependencyProperty* FindGlobalProperty(StringIn name) throw();

	typedef map<String, DependencyClass*> Map_t;

	vector<DependencyProperty*> m_localProperties;
	unsigned int m_localPropertyStart;
	unsigned int m_localPropertyCount;
	//int m_computedCount;

protected:

	void RegisterProperty(DependencyProperty* dp);

	friend class DependencyProperty;

	Map_t::iterator Register();
	void Unregister(Map_t::iterator it);

	map<String, DependencyClass*>::iterator m_registered;
	const Type_Info& m_classType;

	static map<String, DependencyClass*>* s_classes;
	static map<String, DependencyProperty*>* s_properties;
};

}	// Gui
}	// System
