namespace System
{

class LFCEXT ClassType : public NamespaceType
{
public:

	CTOR ClassType();
	~ClassType();

	virtual Type_type get_Kind() const override
	{
		return type_class;
	}

	virtual ClassType* AsClass() override
	{
		return this;
	}

	ClassType* get_InstantiatedFromClass()
	{
		return m_pInstantiatedFromClass;
	}

	ActualTemplateArgs* get_InstantiatedFromParams()
	{
		return m_pInstantiatedFromArgs;
	}

	virtual Class_Type GetSerializableType() const override
	{
		return Class_Class;
	}
	virtual void Load(TypeArchive& ar) override;
	virtual void Store(TypeArchive& ar) const override;

//	CollectionObject<vector<BaseClass*, __gc_allocator>, BaseClass*>* get_BaseClasses();
//	CollectionObject<vector<ClassType*, __gc_allocator>, ClassType*>* get_DerivedClasses();

	List<Object*>& get_Instances()
	{
		return m_instances;
	}

	Vector<BaseClass*, vector<BaseClass*>&>* get_BaseClasses();
	Vector<ClassType*, vector<ClassType*>&>* get_DerivedClasses();

	virtual bool IsOfType(Type* pType) const override;

	bool IsDerivedFrom(ClassType* pClass) const;
	bool IsLeftMostDerivedFrom(ClassType* pClass) const;

	ClassKey GetClassKey() const
	{
		return m_kwType;
	}

	bool HasVirtualTable() const
	{
		return m_bVT;
	}

	bool IsPolymorphic() const
	{
		return m_bVT;
	}

	bool IsPOD() const	// (plain old data)
	{
		return m_isPOD;
	}

	bool IsEmpty() const	// Returns true if the type has no instance data members.
	{
		return m_isEmpty;
	}

	virtual uint get_sizeof(uint sizeofptr = 0) const override
	{
		return m_sizeof;
	}

	int GetOffset(const ClassType* pClass) const;

	bool Equals(const ClassType& other) const;

	virtual String ToString() override;
	virtual IO::TextWriter& Write(IO::TextWriter& stream) const override;
	virtual Type* Clone() const override;

	friend inline TypeArchive& operator >> (TypeArchive& ar, ClassType* & object)
	{
		TypeSerializable* p;
		ar >> p;
		if (p)
		{
			object = dynamic_cast<ClassType*>(p);
			if (object == NULL)
			{
				raise(SystemException(L"Archive"));
			}
		}
		else
			object = nullptr;

		return ar;
	}

	Object* GetUserData(StringIn key) const;
	void SetUserData(StringIn key, Object* data);

	Declarator* GetDeclarator(StringIn name);
	Type* LookupType(StringIn name) const;
	Declarator* GetMemberByOffset(unsigned int offset);

	ClassType* InstantiateTemplate(ActualTemplateArgs* args);

	static ClassType* CreateFromArchive(TypeArchive& ar, uint32 id);

	Declarator* GetOperatorNew();
	Declarator* GetOperatorDelete();

	Declarator* GetDestructor(AccessSpec access = AccessSpec_Private);

	Declarator* GetEmptyConstructor();
	Declarator* GetCopyConstructor();
	Declarator* GetCopyConstructor(Type* fromType);
	Declarator* GetMoveConstructor();
	Declarator* GetMoveConstructor(Type* fromType);
	Declarator* GetCopyOperator();
	Declarator* GetCopyOperator(Type* fromType);
	Declarator* GetMoveOperator();
	Declarator* GetMoveOperator(Type* fromType);

	Declarator* GetConversionOperator(Type* toType);
	Declarator* GetConversionOperatorConst(Type* toType);

	Declarator* GetBracketOperator(Type* pArgType);
	Declarator* GetBracketOperatorConst(Type* pArgType);

	Declarator* GetIncrementOperator();
	Declarator* GetIncrementOperatorConst();
	Declarator* GetDecrementOperator();
	Declarator* GetDecrementOperatorConst();

	Declarator* GetNotOperator();
	Declarator* GetNotOperatorConst();
	Declarator* GetComplementOperator();
	Declarator* GetComplementOperatorConst();

protected:

	Declarator* FindEmptyConstructor();
	Declarator* FindCopyConstructor();
	Declarator* FindMoveConstructor();
	Declarator* FindCopyOperator();
	Declarator* FindMoveOperator();

	Declarator* m_emptyConstructor;
	Declarator* m_copyConstructor;
	Declarator* m_copyOperator;
	Declarator* m_moveOperator;

	Declarator* m_incrementOperator;
	Declarator* m_incrementOperatorConst;
	Declarator* m_decrementOperator;
	Declarator* m_decrementOperatorConst;
	Declarator* m_postIncrementOperator;
	Declarator* m_postIncrementOperatorConst;
	Declarator* m_postDecrementOperator;
	Declarator* m_postDecrementOperatorConst;

	Declarator* m_notOperator;
	Declarator* m_notOperatorConst;

	Declarator* m_complementOperator;
	Declarator* m_complementOperatorConst;

public:

	List<Object*> m_instances;

	map<ClassType*, void*> m_extraInterfaces;

	map<String, ClassType*> m_instantiatedClasses;

	ClassType* m_pInstantiatedFromClass;
	ActualTemplateArgs* m_pInstantiatedFromArgs;
	FormalTemplateArgs* m_pTemplateParams;

	vector<Declarator*> m_forwardDeclarations;

	int m_virtualSize;
	unsigned int m_sizeof;
	unsigned int m_rsizeof;
	unsigned short m_force_alignment;
	unsigned short m_alignment;
	unsigned short m_packing;

//	ClassKey m_kwType : 2;
	ClassKey m_kwType;
	bool m_bVT : 1;
	bool m_def : 1;
	bool m_HasTemplateArgs : 1;
	bool m_isEmpty : 1;
	bool m_isPOD : 1;

	vector<ClassType*> m_derived;
	vector<BaseClass*> m_bases;

//	Type_Info* m_pTypeInfo;

	Object* m_classUserData[4];

	array<AttributeDef> m_attributeDefs;
	array<Object*> m_attributes;

	array<GCMember> m_gcMembers;
	array<GCMember> m_gcInnerMembers;
	array<GCArrayMember> m_gcArrayMembers;
};

LFCEXT vector<BaseClass*>& bases(ClassType* pClass);
LFCEXT vector<ClassType*>& derived(ClassType* pClass);

}	// System
