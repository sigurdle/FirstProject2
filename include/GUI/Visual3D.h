namespace System
{
namespace Gui
{
namespace Media3D
{

class GUIEXT Visual3D : public Object3D
{
protected:

	CTOR Visual3D(DependencyClass* depClass);

public:

	virtual void Render(ManagedRenderContext renderContext) abstract;

	virtual void SetLight(ImmediateRenderContext* renderContext)
	{
	}

	virtual void OnSetRoot(IRootVisual* root);

	virtual size_t GetChildrenCount() throw ();
//	virtual void AddChild(Visual3D* obj) throw (ArgumentNullException*);
	virtual Visual3D* GetChild(size_t index) throw (ArgumentOutOfRangeException*);

	virtual void OnComputedPropertyValueChanged(PropertyValue* pPropertyVal, bool handled) override;

	DEPENDENCY_PROPERTY(Transform3D*, Transform)

	DEPENDENCY_CLASS_ABSTRACT(Visual3D, Object3D)
};

}	// Media3D
}	// Gui
}	// System
