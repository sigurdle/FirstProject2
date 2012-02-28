#ifndef __BrowserFrame_h__
#define __BrowserFrame_h__

struct IWiaDevMgr;
struct IWiaDevMgr2;

namespace System
{

namespace ImageEdit
{
class BitmapEditor;
class ImageDocument;

class WIADevice : public Object
{
public:

	CTOR WIADevice(WCHAR* deviceID) : m_deviceID(deviceID)
	{
	}

	WCHAR* m_deviceID;
};

interface IBitmapTransferCallback
{
	virtual void OnTransferBitmap(LDraw::Bitmap* bitmap) = 0;
	virtual void OnTransferDone() = 0;
};

class ImageTool : public Object
{
public:
	virtual void OnMouseDown(BitmapEditor* view, LDraw::PointD pos) = 0;
	virtual void OnMouseUp(BitmapEditor* view, LDraw::PointD pos) = 0;
	virtual void OnMouseMove(BitmapEditor* view, LDraw::PointD pos) = 0;
	virtual void OnRender(BitmapEditor* view, UI::Graphics* pGraphics);

	virtual void OnTimer(BitmapEditor* view)
	{
	}
};

class MoveTool : public ImageTool
{
public:
	CTOR MoveTool();

	virtual void OnMouseDown(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseUp(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseMove(BitmapEditor* view, LDraw::PointD pos);

	vector<LDraw::matrix3f, __gc_allocator> m_startTransform;

	LDraw::PointD m_startpos;
	LDraw::PointD m_oldpos;

	int m_dragging;
};

class TransformTool : public ImageTool
{
public:
	CTOR TransformTool();

	virtual void OnMouseDown(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseUp(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseMove(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnRender(BitmapEditor* view, UI::Graphics* pGraphics);

	LDraw::matrix3f m_startTransform;

	LDraw::PointD m_startpos;
	LDraw::PointD m_oldpos;
	LDraw::PointD m_pivot;
	LDraw::PointD m_offset;

	int m_hit;

	int m_dragging;
};

class PenTool : public ImageTool
{
public:

	CTOR PenTool();

	virtual void OnMouseDown(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseUp(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseMove(BitmapEditor* view, LDraw::PointD pos);

	LDraw::PointD m_startpos;
	LDraw::PointD m_oldpos;

	int m_dragging;
};

class ShapeTool : public ImageTool
{
public:
	virtual void OnMouseDown(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseUp(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseMove(BitmapEditor* view, LDraw::PointD pos);

	LDraw::PointD m_startpos;
	LDraw::PointD m_oldpos;

	int m_dragging;

protected:

	CTOR ShapeTool();
};

class EllipseTool : public ShapeTool
{
public:
	CTOR EllipseTool();
};

class RectangleTool : public ShapeTool
{
public:
	CTOR RectangleTool();
};

class RoundedRectangleTool : public ShapeTool
{
public:
	CTOR RoundedRectangleTool();
};

class LineTool : public ShapeTool
{
public:
	CTOR LineTool();
};

class SelectionTool : public ImageTool
{
public:
	CTOR SelectionTool();

	virtual void OnTimer(BitmapEditor* view);

	int m_marchingOffset;
};

class RectangularSelectionTool : public SelectionTool
{
public:
	CTOR RectangularSelectionTool();

	virtual void OnMouseDown(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseUp(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnMouseMove(BitmapEditor* view, LDraw::PointD pos);
	virtual void OnRender(BitmapEditor* view, UI::Graphics* pGraphics);

	LDraw::PointD m_startpos;
	LDraw::PointD m_oldpos;

	int m_dragging;
};

}

class SpreadSheetControl;

class TestDraw : public UI::Control
{
public:
	CTOR TestDraw();

	LDraw::Brush* m_brush;

	vector<LDraw::PointI> m_points;
	vector<LDraw::PointI> m_points2;

	bool m_dragging;

	void OnRender(UI::Graphics* pGraphics);

//	void handleEvent(System::Event* evt);
};

class BrowserFrame :
	public UI::CLXUIWindow,
	public ImageEdit::IBitmapTransferCallback,
	public INotifyPropertyChanged
{
public:
	CTOR BrowserFrame();

	void ShowImageDocument(ImageEdit::ImageDocument* document);

	void EnumWIADevices(UI::MenuItem* menuitem);

	void OnFileOpen(Object* sender, UI::ExecutedRoutedEventArgs* args);
	void OnCanFileOpen(Object* sender, UI::CanExecuteRoutedEventArgs* args);

	void OnSetTool(Object* sender, UI::ExecutedRoutedEventArgs* args);
	void OnCanSetTool(Object* sender, UI::CanExecuteRoutedEventArgs* args);

	void OnImportFromWIA(Object* sender, UI::ExecutedRoutedEventArgs* args);

	/*
	void OnMouseDown(Event* evt)
	{
		MessageBeep(-1);
	};
	*/

//	virtual void handleEvent(System::Event* evt);

	virtual void OnTransferBitmap(LDraw::Bitmap* bitmap);
	virtual void OnTransferDone();

	ImageEdit::ImageTool* get_ActiveTool()
	{
		return m_activeTool;
	}

	void set_ActiveTool(ImageEdit::ImageTool* activeTool);

	virtual signal2<Object*, StringW*>& get_PropertyChanged()
	{
		return PropertyChanged;
	}

	signal2<Object*, StringW*> PropertyChanged;

public:

	UI::ChildWindowContainer* m_pWindowContainer;

	UI::TextEdit* m_edit;
	SpreadSheetControl* m_spreadSheetCtl;

	ImageEdit::ImageDocument* m_imageDocument;

	ImageEdit::ImageTool* m_activeTool;

	IWiaDevMgr* m_pWiaDevMgr;
	IWiaDevMgr2* m_pWiaDevMgr2;

	static UI::RoutedUICommand* s_SetToolCommand;
	static UI::RoutedUICommand* s_ImportFromWIACommand;
	static UI::RoutedUICommand* s_LayerAddMaskCommand;
};

}

#endif // __BROWSERFRAME_H_
