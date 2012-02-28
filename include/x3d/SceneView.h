namespace System
{
namespace x3d
{

class X3DEXT SceneVisual3D: public Gui::FrameworkElement
{
public:

	CTOR SceneVisual3D();
	CTOR SceneVisual3D(X3DScene* scene);

	virtual void Render(Gui::ManagedRenderContext renderContext) override;

	void InitStacks();

	X3DScene* get_Scene();
	void set_Scene(X3DScene* scene);

	float getCurrentFrameRate()
	{
		return m_fps;
	}

	virtual void OnMouseMove(Gui::MouseEventArgs* args) override;
	virtual void OnMouseLeftButtonDown(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseLeftButtonUp(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseRightButtonDown(Gui::MouseButtonEventArgs* args) override;
	virtual void OnMouseRightButtonUp(Gui::MouseButtonEventArgs* args) override;

	virtual void OnComputedPropertyValueChanged(Gui::PropertyValue* pProperty, bool handled) override;

	virtual D3DXMATRIX GetViewMatrix();

	static Gui::DependencyClass* get_Class();
	static Gui::DependencyClass* pClass;
	typedef SceneVisual3D thisClass;
	typedef Gui::FrameworkElement baseClass;

	DEPENDENCY_PROPERTY(ICamera*, Camera)
	DEPENDENCY_PROPERTY(bool, MultiSample)
	DEPENDENCY_PROPERTY(X3DNodeSelection*, Selection)

	uint64 m_lasttickcount;
	float m_fps;
	Gui::Timeline* m_timeline;
	Gui::Media3D::Lines2 m_origoAxis;

protected:

	virtual void OnSetRoot(Gui::IRootVisual* root) override;

	void OnSelectionChanged(X3DNodeSelection* selection);
	void OnTick(double tim);
	void OnSceneInvalidate(X3DScene* scene);

	X3DScene* m_scene;
	Vec2f m_startmousepos;
	Vec2f m_oldmousepos;
	int m_mousedown;

private:

	CTOR SceneVisual3D(const SceneVisual3D&);	// non-copyable
};

}	// x3d
}	// System
