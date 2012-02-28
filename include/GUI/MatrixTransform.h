namespace System
{
namespace Gui
{

class GUIEXT MatrixTransform : public Transform
{
public:

	CTOR MatrixTransform();
	CTOR MatrixTransform(const gm::matrix3f& matrix);

	virtual gm::matrix3f get_Matrix()
	{
		return m_matrix;
	}

//	DEPENDENCY_CLASS(MatrixTransform, Transform)
	static DependencyClass* get_Class();
	static DependencyClass* pClass;

	gm::matrix3f m_matrix;
};

}	// Gui
}	// System
