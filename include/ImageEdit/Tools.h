namespace System
{
namespace ImageEdit
{

class IMAGEEDITEXT Tools
{
public:

	static HandTool* get_Hand()
	{
		static HandTool tool;
		return &tool;
	}

	static PaintBrushTool* get_Paintbrush()
	{
		static PaintBrushTool tool;
		return &tool;
	}

	static PencilTool* get_Pencil()
	{
		static PencilTool tool;
		return &tool;
	}

	static TransformTool* get_Transform()
	{
		static TransformTool tool;
		return &tool;
	}

	static RectangleTool* get_Rectangle()
	{
		static RectangleTool tool;
		return &tool;
	}

	static RoundedRectangleTool* get_RoundedRectangle()
	{
		static RoundedRectangleTool tool;
		return &tool;
	}

	static EllipseTool* get_Ellipse()
	{
		static EllipseTool tool;
		return &tool;
	}

	static RectangularSelectionTool* get_RectSelect()
	{
		static RectangularSelectionTool tool;
		return &tool;
	}

	/*
	static RectangularSelectionTool* get_EllipseSelect()
	{
		static EllipticalSelectionTool tool;
		return &tool;
	}
	*/

private:

	CTOR Tools();
};

}	// ImageEdit
}	// System
