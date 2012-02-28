namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT ImageDocument : public Object
{
public:
	CTOR ImageDocument();

	//void OnLayerPropertyChanged(Object* sender, StringW* propertyName);

	String get_FilePath()
	{
		return m_filepath;
	}

	static ImageDocument* FromBitmap(Graphics::Bitmap* bitmap);

	List<Element*>* m_layers;

//	Layer* m_selection;
	Group* m_selection;

	gm::SizeF m_size;

	String m_filepath;

	list<BitmapEditor*> m_views;

	SelectedItems* m_selected;
};

}
}
