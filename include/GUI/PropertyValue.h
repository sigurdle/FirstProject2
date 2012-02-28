namespace System
{
namespace Gui
{

// 1 input, 0 or more outputs
class GUIEXT PropertyValue : public Object, public IBinding, public IObjectChangedNotify
{
public:

	CTOR PropertyValue(DependencyObject* owner, DependencyProperty* dp);

	virtual Type* GetOutputType() override;	// IBinding
	virtual Variant GetOutput(IBinding* caller) override;	// IBinding
	virtual int SetOutput(IBinding* caller, const Variant& value) override;	// IBinding
	virtual int SetInput(IBinding* caller, const Variant& value) override;	// IBinding
	virtual void* Connect(IInputBinding* binding) override;	// IBinding

	virtual void OnObjectChanged(Object*) override;	// IObjectChangedNotify

	operator Expressive::Expression* ()
	{
		return new BindingExpression(this);
	}

	void SetInputBinding(IBinding* inBinding);

	DependencyProperty* GetPropertyDefinition()
	{
		return m_dp;
	}

	DependencyObject* GetOwner()
	{
		return m_owner;
	}

	void SetLocalValue(const Variant& value);
	Variant GetLocalValue();

	Variant GetComputedValue();

	void UpdateValue(const Variant& value);

	void OnComputedValueChanged();
	void OnComputedValueChanging(const Variant& oldValue, const Variant& newValue);

	int SendComputedValueDownStreamExcept(IBinding* exceptThis);

	inline int SendComputedValueDownStream()
	{
		return SendComputedValueDownStreamExcept(nullptr);
	}

	DependencyObject* m_owner;
	DependencyProperty* m_dp;

	Variant m_computedValue;
	Variant m_localValue;

	IBinding* m_inBinding;
	void* m_inBindingPtr;
	list<IInputBinding*> m_outBindings;

	bool m_valueChanged;
};

}	// Gui
}	// System
