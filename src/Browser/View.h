#ifndef __View_h__
#define __View_h__

/*
#ifndef _FILETIME_
typedef struct _FILETIME {
    DWORD dwLowDateTime;
    DWORD dwHighDateTime;
} FILETIME, *PFILETIME, *LPFILETIME;
#define _FILETIME_
#endif
*/

namespace System
{

class DirectoryObject;

class PropertiesTable;

class IDocument
{
public:
	virtual void Open(PropertiesTable* table, UI::TreeItem* item) = 0;
};

class FileObject : public System::Object, public IDocument
{
public:
	CTOR FileObject();

	System::StringA* get_Name();
	void set_Name(System::StringA* name);
	LONGLONG get_Size();
//	DirectoryObject* get_Children();	// This is a view, the viewable object doesn't make any assumptions about its views

	WIN_FILETIME get_CreationTime();
	WIN_FILETIME get_LastAccessTime();
	WIN_FILETIME get_LastWriteTime();

	//DirectoryObject* m_children;
	System::StringA* m_Name;
	System::StringA* m_Fullname;
	LONGLONG m_Size;
	WIN_FILETIME m_CreationTime;
	WIN_FILETIME m_LastAccessTime;
	WIN_FILETIME m_LastWriteTime;
	ULONG m_FileAttributes;

	void Open(PropertiesTable* table, UI::TreeItem* item);

	vector<IViewOf*> m_views;
};

class DirectoryObject : public System::Object, public ICollection<FileObject*>, public IViewOf
{
public:

	const Type_Info& GetItemType() const
	{
		return typeid(FileObject);
	}

	System::Object* get_Viewable()
	{
		return NULL;
	}

	void set_Viewable(System::Object* pObject)
	{
		SetDir(static_cast<FileObject*>(pObject));
	}

	void SetDir(FileObject* pFile);

	System::StringA* m_dirName;
	vector<FileObject*> m_files;

	/*
	const Type_Info& GetType() const
	{
		return typeid(FileObject);
	}
	*/

	unsigned int GetCount();
	System::Object* GetItem(unsigned int index);
};

class NotifyCollectionChangedEventArgs : public EventArgs
{
public:

};

interface INotityCollectionChanged
{
	virtual signal2<Object*, NotifyCollectionChangedEventArgs*>& get_CollectionChanged() = 0;
};

template<class TYPE> class ObservableCollection : public Object, public INotityCollectionChanged
{
public:

	virtual void Add(TYPE item)
	{
		m_items.push_back(item);
		CollectionChanged(this, new NotifyCollectionChangedEventArgs());
	}

	virtual unsigned int get_Count()
	{
		return m_items.size();
	}

	virtual TYPE get_Item(unsigned int index)
	{
		return m_items[index];
	}

	virtual signal2<Object*, NotifyCollectionChangedEventArgs*>& get_CollectionChanged()
	{
		return CollectionChanged;
	}

private:

	vector<TYPE> m_items;
	signal2<Object*, NotifyCollectionChangedEventArgs*> CollectionChanged;
};

namespace ImageEdit
{

class Mask;
class Element;
class Group;
class PathShape;
class BitmapEditor;

struct StrokeSample
{
	LDraw::PointD pos;
	double angle;
	double arclength;
	int segment;
};

class Path : public Object
{
public:

	class BezierPoint : public Object
	{
	public:

		CTOR BezierPoint()
		{
		}

		CTOR BezierPoint(LDraw::PointD p0, LDraw::PointD p1, LDraw::PointD p2)
		{
			m_points[0] = (p0);
			m_points[1] = (p1);
			m_points[2] = (p2);
		}

		BezierPoint Transform(const LDraw::matrix3f& transform)
		{
			return BezierPoint(
				transform.transform(m_points[0]),
				transform.transform(m_points[1]),
				transform.transform(m_points[2]));
		}

		LDraw::PointD m_points[3];
	};

	class SubPath : public Object
	{
	public:
		CTOR SubPath();

		int DrawVertices(LDraw::GraphicsI* device, LDraw::BufferData* bufferData);
		void DrawVertices(LDraw::DrawLineStripCommand* pCmd, const LDraw::matrix3f& transform);

		void Stroke(function1<StrokeSample>& callback);

		void Reverse();
		void SetEllipse(double x, double y, double width, double height);
		void SetRectangle(double x, double y, double width, double height);

		bool get_IsClosed() const
		{
			return m_closed;
		}

		void set_IsClosed(bool isClosed);

		vector<BezierPoint*, __gc_allocator> m_data;
		bool m_closed;
	};

	CTOR Path();

	void AddEllipse(double x, double y, double width, double height);
	void AddRectangle(double x, double y, double width, double height);
	void DrawOutline(LDraw::GraphicsI* device, LDraw::BufferData* bufferData, LDraw::Commands* pCommands, LDraw::Brush* brush, const LDraw::matrix3f& transform);
	void DrawFilled(LDraw::GraphicsI* device, LDraw::BufferData* bufferData, LDraw::Commands* pCommands, LDraw::Brush* brush);
	void Stroke(function1<StrokeSample>& callback);

	vector<SubPath*, __gc_allocator> m_subPath;
	uint m_refcount;
};

class PaintBrush : public Object
{
public:
	LDraw::Bitmap* m_bitmap;

	void SetCircular();
};

class PaintToolSettings
{
public:
	PaintBrush* m_brush;

	double m_spacing;
};

class RenderTo
{
public:
	CTOR RenderTo()
	{
		m_offscreenBitmap[0] = NULL;
		m_offscreenBitmap[1] = NULL;
	}

	int Render(LDraw::GraphicsO* pO, ObservableCollection<Element*>* layers);

	LDraw::Bitmap* m_offscreenBitmap[2];
//	IDirect3DSurface9* m_offscreenSurface[2];

	int m_width;
	int m_height;
};

class Element : public Object, public INotifyPropertyChanged
{
public:
	CTOR Element(ImageDocument* document);

	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics) = 0;
	virtual LDraw::Bitmap* get_Bitmap() = 0;

	double get_Opacity();
	void set_Opacity(double opacity);

	virtual Element* Clone() = 0;

	virtual StringPtr get_Name()
	{
		return m_name;
	}

	virtual signal2<Object*, StringW*>& get_PropertyChanged()
	{
		return PropertyChanged;
	}

	LDraw::Color get_DisplayColor();

	uint AddRef()
	{
		++m_refcount;
		return m_refcount;
	}

	uint Release()
	{
		--m_refcount;
		return m_refcount;
	}

public:

	signal2<Object*, StringW*> PropertyChanged;

	ImageDocument* m_document;
	Group* m_parent;
	Mask* m_mask;

	StringPtr m_name;
	LDraw::matrix3f m_transform;

	LDraw::RectD m_bounds;

	double m_opacity;
	uint32 m_blendMode;
	bool m_visible;
	bool m_boundsValid;

	uint m_refcount;
};

class Adjustment : public Object, public INotifyPropertyChanged
{
public:

	virtual signal2<Object*, StringW*>& get_PropertyChanged()
	{
		return PropertyChanged;
	}

	signal2<Object*, StringW*> PropertyChanged;
};

/*
class HistogramView : public FrameworkElement
{
public:

	void 

	LDraw::Bitmap* get_Bitmap();
	void set_Bitmap(LDraw::Bitmap* bitmap);

	static DependencyProperty* s_BitmapProperty;
};
*/

class BrightnessContrastAdjustment : public Adjustment
{
public:

	CTOR BrightnessContrastAdjustment();

	double get_Brightness();
	void set_Brightness(double brightness);

	double get_Contrast();
	void set_Contrast(double contrast);

	double m_brightness;
	double m_contrast;
};

class LevelsAdjustment : public Adjustment
{
public:

	// 0=rgb, 1=r, 2=g, 3=g, 

	float gamma[5];
	float inputblack[5];
	float inputwhite[5];
	float outputblack[5];
	float outputwhite[5];
};

class Gradient : public Object
{
public:
};

class Mask : public Object
{
};

class GradientMask : public Mask
{
public:
};

class ElementMask : public Mask
{
public:

	CTOR ElementMask();
	CTOR ElementMask(Element* element);

	Element* m_element;
};

class AdjustmentLayer : public Element
{
public:
	CTOR AdjustmentLayer(ImageDocument* document);

	virtual Element* Clone();

	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
	virtual LDraw::Bitmap* get_Bitmap();

	Adjustment* get_Adjustment();

	void OnAdjustmentPropertyChanged(Object* sender, StringW* propertyName);

	Adjustment* m_adjustment;
};

/*
class Shape : public Object
{
public:
	virtual void Render(UI::Graphics* pGraphics) = 0;
};

class RectangleShape : public Shape
{
public:
};

class EllipseShape : public Shape
{
};
*/


class Shape : public Element
{
public:

	virtual LDraw::Bitmap* get_Bitmap()
	{
		return NULL;
	}

protected:
	CTOR Shape(ImageDocument* document);
};

class PathShape : public Shape
{
public:

	CTOR PathShape(ImageDocument* document);

	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
//	virtual void Render(UI::Graphics* pGraphics);

	virtual PathShape* Clone();

	void DrawBrush(UI::Graphics* pGraphics, StrokeSample sample);

	virtual void CalculateBounds();

	PaintBrush* m_paintBrush;

	Path* m_path;
};

class Group : public Element
{
public:

	CTOR Group(ImageDocument* document);

	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
	virtual Group* Clone();

	virtual LDraw::Bitmap* get_Bitmap();

	ObservableCollection<Element*>* m_subObjects;

//	RenderTo m_renderTo;
	LDraw::Bitmap* m_offscreenBitmap;
//	IDirect3DSurface9* m_offscreenSurface;
};

class Layer : public Group
{
public:

	CTOR Layer(ImageDocument* document);

	virtual Layer* Clone();
	virtual LDraw::Bitmap* get_ThumbnailBitmap() = 0;

	LDraw::Color m_color;
};

/*
class GroupLayer : public Layer
{
public:

	virtual void Render(IDirect3DSurface9* renderTarget, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
	virtual LDraw::Bitmap* get_ThumbnailBitmap();
};
*/

/*
class ShapesLayer : public Layer
{
public:
	CTOR ShapesLayer();

	virtual void Render(IDirect3DSurface9* renderTarget, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
	virtual LDraw::Bitmap* get_Bitmap();
	virtual LDraw::Bitmap* get_ThumbnailBitmap();

	LDraw::Bitmap* m_bitmap;

	vector<Shape*> m_shapes;
};
*/

class Video : public Object
{
public:
};

class BitmapLayer : public Layer
{
public:

	CTOR BitmapLayer(ImageDocument* document);

	virtual BitmapLayer* Clone();
	virtual int Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics);
	virtual LDraw::Bitmap* get_ThumbnailBitmap();

	virtual LDraw::Bitmap* get_Bitmap()
	{
		return m_bitmap;
	}

	void CreateA8R8G8B8(int width, int height);
	void CreateA8(int width, int height);
	void CreateR16F(int width, int height);

	UI::Histogram* get_Histogram();

public:

	UI::Histogram* m_histogram;

	LDraw::Bitmap* m_bitmap;
	Video* m_video;

	float m_x;
	float m_y;

	/*
	PaintBrush* m_paintBrush;
	vector<LDraw::PointF> m_points;
	*/
};

class Selected : public Object
{
public:

	CTOR Selected(Element* element)
	{
		m_element = element;
	}

	Element* m_element;
};

class PathSelected : public Selected
{
public:
	CTOR PathSelected(PathShape* path);

	int Draw(LDraw::GraphicsI* device, LDraw::BufferData* bufferData, LDraw::Commands* pCommands, LDraw::Brush* brush);

	class SubPath
	{
	public:
		vector<int> m_selectedPoints;
		vector<bool> m_isSelected;
	};

	vector<SubPath*> m_subPath;

	inline PathShape* GetPath()
	{
		return static_cast<PathShape*>(m_element);
	}
};

class SelectedItems : public Object
{
public:

	Selected* m_target;
	vector<Selected*> m_items;
};

class ImageDocument : public Object
{
public:
	CTOR ImageDocument();

	void OnLayerPropertyChanged(Object* sender, StringW* propertyName);

	StringW* get_FilePath()
	{
		return m_filepath;
	}

	static ImageDocument* FromBitmap(LDraw::Bitmap* bitmap);

	ObservableCollection<Element*>* m_layers;

//	Layer* m_selection;
	Group* m_selection;

	LDraw::SizeD m_size;

	StringW* m_filepath;

	list<BitmapEditor*> m_views;

	SelectedItems* m_selected;
};

class BitmapEditor : public UI::FrameworkElement
{
public:

	CTOR BitmapEditor();

	void OnTimer(UINT);

	virtual void OnRender(UI::Graphics* pGraphics);
	virtual LDraw::SizeD MeasureOverride(LDraw::SizeD availSize);

	virtual void OnMouseDown(UI::MouseButtonEventArgs* args);
	virtual void OnMouseUp(UI::MouseButtonEventArgs* args);
	virtual void OnMouseMove(UI::MouseEventArgs* args);

	void OnLayerAddLayer(Object* sender, UI::ExecutedRoutedEventArgs* args);
	void OnCanLayerAddLayer(Object* sender, UI::CanExecuteRoutedEventArgs* args);

	void OnLayerAddLayerMask(Object* sender, UI::ExecutedRoutedEventArgs* args);
	void OnCanLayerAddLayerMask(Object* sender, UI::CanExecuteRoutedEventArgs* args);

	void OnFramePropertyChanged(Object* sender, StringW* propertyName);

public:

	SelectedItems* m_selected;

	BrowserFrame* m_frame;

	ImageDocument* m_document;
	Layer* m_activeLayer;

	LDraw::Bitmap* m_checkboardBitmap;

	RenderTo m_renderTo;

	int m_marchingOffset;

	bool m_showLayerEdges;

	int m_dragging;
};

}

class EditView : public UI::Control, public IViewOf
{
public:
	CTOR EditView(System::Property* pProperty, System::Object* itemVisual);

	System::Object* get_Viewable()
	{
		return NULL;
	}

	void set_Viewable(System::Object* pViewable)
	{
	}

	UI::TextEdit* m_edit;

	System::Property* m_pProperty;
	System::Object* m_itemVisual;

//	void handleEvent(System::Event* evt);
};

class EnumView : public UI::Control, public IViewOf
{
public:
	CTOR EnumView(System::Property* pProperty, System::Object* itemVisual);

	System::Object* get_Viewable()
	{
		return NULL;
	}

	void set_Viewable(System::Object* pViewable)
	{
	}

protected:

//	virtual void handleEvent(System::Event* evt);

public:
	UI::MenuItem* m_menu;

	System::Property* m_pProperty;
	System::Object* m_itemVisual;
};

}

#if 0//WIN32

#ifdef __LERSTAD__
//#import "../../Win32/bin/Debug/LXImageEditor.typeinfo"
#else
#include "../LXImageEditor/LXImageEditor.h"

namespace System
{

class ToolListener// : public System::IEventListener
{
public:
	CTOR ToolListener()
	{
		m_doc = NULL;
		m_tool = NULL;
	}

	ImageEdit::CImageDocument *m_doc;
	ImageEdit::IImageTool *m_tool;

	//void handleEvent(System::Event* evt);
};

}

#endif

#endif

namespace System
{

class MetafileVisual : public UI::UIElement
{
public:
	CTOR MetafileVisual()
	{
		m_commands = NULL;
	}

	LDraw::Commands* m_commands;

	LDraw::RectD m_originalRect;

	void OnRender(UI::Graphics* pGraphics);
};

class EditLines : public UI::Control
{
public:
	CTOR EditLines();

	int m_dragging;

	vector<LDraw::PointF> m_points;

//	Bezier m_bezierA;
//	Bezier m_bezierB;

	/*
	class Stroke
	{
	public:
		std::vector<LDraw::PointF> m_points;
		LDraw::Color m_color;
	};
	*/

	//LDraw::PointD m_startpoint;

	//std::vector<Stroke*> m_strokes;
	UI::FrameworkElement* m_pCurStroke;
	LDraw::PointD m_startpoint;
	LDraw::PointD m_oldpoint;
	UI::Canvas* m_pCanvas;

//	void handleEvent(System::Event* evt);

#if 1
	virtual void OnRender(UI::Graphics* pGraphics);
#endif
};

class Display : public UI::Control
{
public:

	UI::TreeControl* m_tree;
	UI::UIElement* root;

	/*
	int get_test()
	{
		return 0;
	}
	void put_test(int x)
	{
	}
	*/


	CTOR Display(UI::UIElement* visual);

//	virtual LDraw::SizeD OnMeasure(LDraw::SizeD availSize);

	class Item : public System::Object//, public System::IEventListener
	{
	public:
		CTOR Item(Display* root)
		{
			m_root = root;
			m_treeItem = NULL;
			m_Visual = NULL;
			m_eventCtl = new UI::TextString(WSTR(""));
		}

		Display* m_root;

		UI::TreeItem* m_treeItem;
		UI::UIElement* m_Visual;

		UI::TextString* m_eventCtl;

		//void handleEvent(System::Event* evt);
	};

	void BuildChildren(UI::TreeControl* tree, UI::UIElement* visual, UI::ITreeParent* parent);

	Item* m_item;

//	virtual void handleEvent(System::Event* evt);
};

namespace UI
{
	/*
	class MutationEvent : public Event
	{
	public:
		UIElement* m_element;
	};
	*/
}

}

#endif // __View_h__
