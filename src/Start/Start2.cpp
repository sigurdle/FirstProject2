///////////////////////////////////////
// SelectionTool

SelectionTool::SelectionTool()
{
}

void SelectionTool::OnTimer(BitmapEditor* view)
{
	m_marchingOffset++;
	view->Invalidate();

}

///////////////////////////////////////

LDraw::Bitmap* s_Texture = CreateCheckboardBitmap(12, 12, LDraw::Color(0,0,0), LDraw::Color(255,255,255));

RectangularSelectionTool::RectangularSelectionTool()
{
}

void RectangularSelectionTool::OnRender(BitmapEditor* view, UI::Graphics* pGraphics)
{
	if (m_dragging)
	{
		LDraw::DrawLineStripCommand* pCmd = new LDraw::DrawLineStripCommand;
	//	pCmd->m_brush = new LDraw::SolidBrush(LDraw::Color(255, 255, 255));
		pCmd->m_brush = new LDraw::TextureBrush(s_Texture);
		pCmd->m_vertexBuffer = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexBuffer;
		pCmd->m_vertexOffsetInBytes = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexOffsetInBytes;
		pCmd->m_count = 5;

		LDraw::RectD bounds(m_startpos, m_oldpos);
		const LDraw::matrix3f& transform = LDraw::matrix3f::getIdentity();//element->m_transform;

		LDraw::vector2f pts[4] =
		{
			transform.transform(LDraw::vector2f(bounds.X, bounds.Y)),
			transform.transform(LDraw::vector2f(bounds.X+bounds.Width, bounds.Y)),
			transform.transform(LDraw::vector2f(bounds.X+bounds.Width, bounds.Y+bounds.Height)),
			transform.transform(LDraw::vector2f(bounds.X, bounds.Y+bounds.Height)),
		};

		LDraw::vector2f texIncrement(m_marchingOffset, 0/*m_marchingOffset*/);

		unsigned int verticesSizeInBytes = sizeof(LDraw::VERTEX_XYZ_T2)*5;
		LDraw::VERTEX_XYZ_T2 vertices[5] =
		{
			pts[0], pts[0]+texIncrement,
			pts[1], pts[1]+texIncrement,
			pts[2], pts[2]+texIncrement,
			pts[3], pts[3]+texIncrement,
			pts[0], pts[0]+texIncrement,

			/*
			pts[0], LDraw::matrix3f::getRotate(45).transform(pts[0]+texIncrement),
			pts[1], LDraw::matrix3f::getRotate(45).transform(pts[1]+texIncrement),
			pts[2], LDraw::matrix3f::getRotate(45).transform(pts[2]+texIncrement),
			pts[3], LDraw::matrix3f::getRotate(45).transform(pts[3]+texIncrement),
			pts[0], LDraw::matrix3f::getRotate(45).transform(pts[0]+texIncrement),
			*/
		};
		pGraphics->m_pO->m_device->VertexBufferSubData(dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexBuffer, dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexOffsetInBytes, verticesSizeInBytes, vertices);

		dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexOffsetInBytes += verticesSizeInBytes;

		dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands->AddCommand(pCmd);
	}
}

void RectangularSelectionTool::OnMouseDown(BitmapEditor* view, LDraw::PointD pos)
{
	if (!m_dragging)
	{
		view->CaptureMouse();

		m_dragging = 1;
		m_startpos = pos;
	}
}

void RectangularSelectionTool::OnMouseUp(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		view->ReleaseMouseCapture();
		m_dragging = 0;

		PathShape* pShape = new PathShape(view->m_document);
		pShape->m_path = new Path;

		pShape->m_path->AddEllipse(m_startpos.X, m_startpos.Y, pos.X-m_startpos.X, pos.Y-m_startpos.Y);
		pShape->CalculateBounds();	// TODO not here

		if (view->m_selected == NULL)
		{
			view->m_selected = new SelectedItems;
		}

		PathSelected* pathSelected = new PathSelected(pShape);
		pathSelected->m_subPath[0]->m_selectedPoints.push_back(0);
		pathSelected->m_subPath[0]->m_isSelected[0] = true;

		view->m_selected->m_target = pathSelected;
		view->m_selected->m_items.clear();
		view->m_selected->m_items.push_back(pathSelected);

		if (true)
		{
			if (view->m_document->m_selection == NULL)
			{
				view->m_document->m_selection = new Group(view->m_document);
			}
			else
			{
				if (view->m_document->m_selection->m_refcount > 1)
				{
					view->m_document->m_selection = view->m_document->m_selection->Clone();
				}
			}

			view->m_document->m_selection->m_subObjects->Add(pShape);
		}
		else
		{
			view->m_document->m_layers->Add(pShape);
		}
		view->Invalidate();
	}
}

void RectangularSelectionTool::OnMouseMove(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		m_oldpos = pos;
		view->Invalidate();
	}
}

/////////////////////////////////////

Path::Path()
{
	m_refcount = 0;
}

Path::SubPath::SubPath()
{
}

void Path::SubPath::SetEllipse(double x, double y, double width, double height)
{
	LDraw::PointD pts[13];
	LDraw::SetPointsEllipse(x, y, width, height, pts);

	m_data.reserve(4);
	m_data.clear();

	m_data.push_back(new BezierPoint(pts[11], pts[0], pts[1]));
	m_data.push_back(new BezierPoint(pts[2], pts[3], pts[4]));
	m_data.push_back(new BezierPoint(pts[5], pts[6], pts[7]));
	m_data.push_back(new BezierPoint(pts[8], pts[9], pts[10]));

	m_closed = true;
}

void Path::SubPath::SetRectangle(double x, double y, double width, double height)
{
	m_data.reserve(4);
	m_data.clear();

	m_data.push_back(new BezierPoint(LDraw::PointD(x,y), LDraw::PointD(x,y), LDraw::PointD(x,y)));
	m_data.push_back(new BezierPoint(LDraw::PointD(x+width,y), LDraw::PointD(x+width,y), LDraw::PointD(x+width,y)));
	m_data.push_back(new BezierPoint(LDraw::PointD(x+width,y+height), LDraw::PointD(x+width,y+height), LDraw::PointD(x+width,y+height)));
	m_data.push_back(new BezierPoint(LDraw::PointD(x,y+height), LDraw::PointD(x,y+height), LDraw::PointD(x,y+height)));

	m_closed = true;
}

void Path::AddEllipse(double x, double y, double width, double height)
{
	SubPath* subPath = new SubPath;
	subPath->SetEllipse(x, y, width, height);

	m_subPath.push_back(subPath);
}

void Path::AddRectangle(double x, double y, double width, double height)
{
	SubPath* subPath = new SubPath;
	subPath->SetRectangle(x, y, width, height);

	m_subPath.push_back(subPath);
}

void Path::Stroke(function1<StrokeSample>& callback)
{
	for (int i = 0; i < m_subPath.size(); i++)
	{
		m_subPath[i]->Stroke(callback);
	}
}

void Path::SubPath::Stroke(function1<StrokeSample>& callback)
{
	int nsteps = 26;

	int nvertices = 0;
	for (int i = 0; i < m_data.size()-1; i++)
	{
		BezierPoint* p0 = m_data[i];
		BezierPoint* p1 = m_data[i+1];

		LDraw::CubicBezierEvaluator<double> evaluator(p0->m_points[1], p0->m_points[2], p1->m_points[0], p1->m_points[1]);

		for (int j = 0; j < nsteps; j++)
		{
			double t = (double)j/nsteps;

			StrokeSample sample;
			sample.pos = evaluator.evaluate(t);
			sample.angle = evaluator.GetAngleAt(t);

			callback(sample);
		}
	}

	if (m_closed)
	{
		BezierPoint* p0 = m_data[m_data.size()-1];
		BezierPoint* p1 = m_data[0];

		LDraw::CubicBezierEvaluator<double> evaluator(p0->m_points[1], p0->m_points[2], p1->m_points[0], p1->m_points[1]);

		for (int j = 0; j < nsteps; j++)
		{
			double t = (double)j/nsteps;

			StrokeSample sample;
			sample.pos = evaluator.evaluate(t);
			sample.angle = evaluator.GetAngleAt(t);

			callback(sample);
		}
	}
}

int Path::SubPath::DrawVertices(LDraw::GraphicsI* device, LDraw::BufferData* bufferData)
{
	int nsteps = 14;

	int nvertices = 0;
	for (int i = 0; i < m_data.size()-1; i++)
	{
		BezierPoint* p0 = m_data[i];
		BezierPoint* p1 = m_data[i+1];

		LDraw::CubicBezierEvaluator<double> evaluator(p0->m_points[1], p0->m_points[2], p1->m_points[0], p1->m_points[1]);

		for (int j = 0; j < nsteps; j++)
		{
			double t = (double)j/nsteps;
			LDraw::PointD point = evaluator.evaluate(t);

			unsigned int verticesSizeInBytes = sizeof(LDraw::VERTEX_XYZ);
			LDraw::VERTEX_XYZ vertex = {LDraw::vector3f(point.X, point.Y, 0)};
			device->VertexBufferSubData(bufferData->m_vertexBuffer, bufferData->m_vertexOffsetInBytes, verticesSizeInBytes, &vertex);

			bufferData->m_vertexOffsetInBytes += verticesSizeInBytes;

			++nvertices;
		}
	}

	if (m_closed)
	{
		BezierPoint* p0 = m_data[m_data.size()-1];
		BezierPoint* p1 = m_data[0];

		LDraw::CubicBezierEvaluator<double> evaluator(p0->m_points[1], p0->m_points[2], p1->m_points[0], p1->m_points[1]);

		for (int j = 0; j <= nsteps; j++)
		{
			double t = (double)j/nsteps;
			LDraw::PointD point = evaluator.evaluate(t);

			unsigned int verticesSizeInBytes = sizeof(LDraw::VERTEX_XYZ);
			LDraw::VERTEX_XYZ vertex = {LDraw::vector3f(point.X, point.Y, 0)};
			device->VertexBufferSubData(bufferData->m_vertexBuffer, bufferData->m_vertexOffsetInBytes, verticesSizeInBytes, &vertex);

			bufferData->m_vertexOffsetInBytes += verticesSizeInBytes;

			++nvertices;
		}
	}

	return nvertices;
}

void Path::SubPath::DrawVertices(LDraw::DrawLineStripCommand* pCmd, const LDraw::matrix3f& transform)
{
	int nsteps = 14;

	int nvertices = 0;
	for (int i = 0; i < m_data.size()-1; i++)
	{
		BezierPoint p0 = m_data[i]->Transform(transform);
		BezierPoint p1 = m_data[i+1]->Transform(transform);

		LDraw::CubicBezierEvaluator<double> evaluator(p0.m_points[1], p0.m_points[2], p1.m_points[0], p1.m_points[1]);

		for (int j = 0; j < nsteps; j++)
		{
			double t = (double)j/nsteps;
			LDraw::PointD point = evaluator.evaluate(t);

			pCmd->m_points.push_back(LDraw::vector2f(point.X, point.Y));
		}
	}

	if (m_closed)
	{
		BezierPoint p0 = m_data[m_data.size()-1]->Transform(transform);
		BezierPoint p1 = m_data[0]->Transform(transform);

		LDraw::CubicBezierEvaluator<double> evaluator(p0.m_points[1], p0.m_points[2], p1.m_points[0], p1.m_points[1]);

		for (int j = 0; j <= nsteps; j++)
		{
			double t = (double)j/nsteps;
			LDraw::PointD point = evaluator.evaluate(t);

			pCmd->m_points.push_back(LDraw::vector2f(point.X, point.Y));
		}
	}
}

PathSelected::PathSelected(PathShape* path) : Selected(path)
{
	if (path == NULL) throw new ArgumentNullException();

	for (int i = 0; i < path->m_path->m_subPath.size(); i++)
	{
		SubPath* subPath = new SubPath;
		subPath->m_isSelected.resize(path->m_path->m_subPath[i]->m_data.size());
		m_subPath.push_back(subPath);
	}
}

int PathSelected::Draw(LDraw::GraphicsI* device, LDraw::BufferData* bufferData, LDraw::Commands* pCommands, LDraw::Brush* brush)
{
	LDraw::DrawLinesCommand* pCmd = new LDraw::DrawLinesCommand;
	pCmd->m_brush = brush;
	pCmd->m_vertexBuffer = bufferData->m_vertexBuffer;
	pCmd->m_vertexOffsetInBytes = bufferData->m_vertexOffsetInBytes;

	int nvertices = 0;

	for (int i = 0; i < m_subPath.size(); i++)
	{
		SubPath* subPath = m_subPath[i];
		for (int i = 0; i < subPath->m_selectedPoints.size(); i++)
		{
			int n = subPath->m_selectedPoints[i];
			const Path::BezierPoint p = GetPath()->m_path->m_subPath[i]->m_data[n]->Transform(m_element->m_transform);

			if (true)
			{
				unsigned int verticesSizeInBytes = sizeof(LDraw::VERTEX_XYZ)*2;
				LDraw::VERTEX_XYZ vertices[2] =
				{
					LDraw::vector3f(p.m_points[1].X, p.m_points[1].Y, 0),
					LDraw::vector3f(p.m_points[0].X, p.m_points[0].Y, 0)
				};
				device->VertexBufferSubData(bufferData->m_vertexBuffer, bufferData->m_vertexOffsetInBytes, verticesSizeInBytes, vertices);

				bufferData->m_vertexOffsetInBytes += verticesSizeInBytes;

				nvertices += 2;
			}

			if (true)
			{
				unsigned int verticesSizeInBytes = sizeof(LDraw::VERTEX_XYZ)*2;
				LDraw::VERTEX_XYZ vertices[2] =
				{
					LDraw::vector3f(p.m_points[1].X, p.m_points[1].Y, 0),
					LDraw::vector3f(p.m_points[2].X, p.m_points[2].Y, 0)
				};
				device->VertexBufferSubData(bufferData->m_vertexBuffer, bufferData->m_vertexOffsetInBytes, verticesSizeInBytes, vertices);

				bufferData->m_vertexOffsetInBytes += verticesSizeInBytes;

				nvertices += 2;
			}
		}
	}

	if (nvertices)
	{
		pCmd->m_count = nvertices;
		pCommands->AddCommand(pCmd);
	}

	return nvertices;
}

void Path::DrawOutline(LDraw::GraphicsI* device, LDraw::BufferData* bufferData, LDraw::Commands* pCommands, LDraw::Brush* brush, const LDraw::matrix3f& transform)
{
	for (int i = 0; i < m_subPath.size(); i++)
	{
		LDraw::DrawLineStripCommand* pCmd = new LDraw::DrawLineStripCommand;
		pCmd->m_brush = brush;
		pCmd->m_vertexBuffer = bufferData->m_vertexBuffer;
		pCmd->m_vertexOffsetInBytes = bufferData->m_vertexOffsetInBytes;

		pCmd->m_antialias = true;
		pCmd->m_color = ((LDraw::SolidBrush*)brush)->GetColor();
		pCmd->m_width = 1;
		m_subPath[i]->DrawVertices(pCmd, transform);
	//	pCmd->m_count = m_subPath[i]->DrawVertices(device, bufferData);

		pCommands->AddCommand(pCmd);
	}
}

void Path::DrawFilled(LDraw::GraphicsI* device, LDraw::BufferData* bufferData, LDraw::Commands* pCommands, LDraw::Brush* brush)
{
	/*
	for (int i = 0; i < m_subPath.size(); i++)
	{
		DrawTriangleFan*
	}
	*/
}

////////////////////////////////
// ShapeTool

ShapeTool::ShapeTool()
{
}

void ShapeTool::OnMouseDown(BitmapEditor* view, LDraw::PointD pos)
{
	if (!m_dragging)
	{
		view->CaptureMouse();
		m_dragging = 1;
		m_startpos = pos;
	}
}

void ShapeTool::OnMouseUp(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		view->ReleaseMouseCapture();
		m_dragging = 0;

		PathShape* pShape = new PathShape(view->m_document);
		pShape->m_path = new Path;

		pShape->m_mask = new ElementMask(view->m_document->m_selection);

		pShape->m_path->AddEllipse(m_startpos.X, m_startpos.Y, pos.X-m_startpos.X, pos.Y-m_startpos.Y);
		pShape->CalculateBounds();	// TODO not here

		if (view->m_selected == NULL)
		{
			view->m_selected = new SelectedItems;
		}

		PathSelected* pathSelected = new PathSelected(pShape);
		pathSelected->m_subPath[0]->m_selectedPoints.push_back(0);
		pathSelected->m_subPath[0]->m_isSelected[0] = true;

		view->m_selected->m_target = pathSelected;
		view->m_selected->m_items.clear();
		view->m_selected->m_items.push_back(pathSelected);

		if (false)
		{
			if (view->m_document->m_selection == NULL)
			{
				view->m_document->m_selection = new Group(view->m_document);
			}
			view->m_document->m_selection->m_subObjects->Add(pShape);
		}
		else
		{
			view->m_document->m_layers->Add(pShape);
		}
		view->Invalidate();

	}
}

void ShapeTool::OnMouseMove(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		view->Invalidate();
	}
}

////////////////////////////////

LineTool::LineTool()
{
}

////////////////////////////////

RectangleTool::RectangleTool()
{
}

////////////////////////////////

RoundedRectangleTool::RoundedRectangleTool()
{
}

///////////////////////////////
// EllipseTool

EllipseTool::EllipseTool()
{
}

///////////////////////////////
// PenTool

PenTool::PenTool()
{
}

void PenTool::OnMouseDown(BitmapEditor* view, LDraw::PointD pos)
{
	if (!m_dragging)
	{
		if (view->m_selected)
		{
			m_dragging = 1;
			view->CaptureMouse();

			m_startpos = pos;
			m_oldpos = pos;
		}
	}
}

void PenTool::OnMouseUp(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		m_dragging = 0;
		view->ReleaseMouseCapture();
	}
}

void PenTool::OnMouseMove(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		LDraw::PointD deltapos = pos - m_oldpos;

		for (int i = 0; i < view->m_selected->m_items.size(); i++)
		{
			PathSelected* selected = dynamic_cast<PathSelected*>(view->m_selected->m_items[i]);

			for (int nsubPath = 0; nsubPath < selected->m_subPath.size(); nsubPath++)
			{
				for (int j = 0; j < selected->m_subPath[nsubPath]->m_selectedPoints.size(); j++)
				{
					int n = selected->m_subPath[nsubPath]->m_selectedPoints[j];
					selected->GetPath()->m_path->m_subPath[nsubPath]->m_data[n]->m_points[0] += deltapos;
					selected->GetPath()->m_path->m_subPath[nsubPath]->m_data[n]->m_points[1] += deltapos;
					selected->GetPath()->m_path->m_subPath[nsubPath]->m_data[n]->m_points[2] += deltapos;
				}
			}

			selected->m_element->m_boundsValid = false;
			selected->GetPath()->CalculateBounds();	// TODO, not here
		}

		m_oldpos = pos;

		view->Invalidate();
	}
}

///////////////////////////////////////
// Shape

Shape::Shape(ImageDocument* document) : Element(document)
{
}

///////////////////////////////////////
// PathShape

PathShape::PathShape(ImageDocument* document) : Shape(document)
{
	m_paintBrush = new PaintBrush;
	m_paintBrush->SetCircular();

	m_opacity = 1.0;
}

PathShape* PathShape::Clone()
{
	ASSERT(0);
	return NULL;
}

void PathShape::CalculateBounds()
{
	LDraw::BBoxD bbox;

	for (int i = 0; i < m_path->m_subPath.size(); i++)
	{
		Path::SubPath* subPath = m_path->m_subPath[i];

		for (int j = 0; j < subPath->m_data.size()-1; j++)
		{
			const Path::BezierPoint* p0 = subPath->m_data[j];
			const Path::BezierPoint* p1 = subPath->m_data[j+1];

			double mx[4] =
			{
				99999, 99999,
				-99999, -99999
			};

			LDraw::CalcCurveBBox(
				p0->m_points[1].X, p0->m_points[1].Y,
				p0->m_points[2].X, p0->m_points[2].Y,
				p1->m_points[0].X, p1->m_points[0].Y,
				p1->m_points[1].X, p1->m_points[1].Y, mx);

			if (i == 0 && j == 0)
			{
				bbox.left = mx[0];
				bbox.top = mx[1];
				bbox.right = mx[2];
				bbox.bottom = mx[3];
			}
			else
			{
				bbox.left = std::min(bbox.left, mx[0]);
				bbox.top = std::min(bbox.top, mx[1]);
				bbox.right = std::max(bbox.right,  mx[2]);
				bbox.bottom = std::max(bbox.bottom, mx[3]);
			}
		}
	}

	m_bounds.X = bbox.left;
	m_bounds.Y = bbox.top;
	m_bounds.Width = bbox.GetWidth();
	m_bounds.Height = bbox.GetHeight();
}

void PathShape::DrawBrush(UI::Graphics* pGraphics, StrokeSample sample)
{
	float width = 20;
	float height = 20;

	if (false)
	{
		pGraphics->DrawImage(
			m_paintBrush->m_bitmap,
			LDraw::RectF(sample.pos.X - width/2-4, sample.pos.Y - height/2-4, width+8, height+8),
			-4, -4, m_paintBrush->m_bitmap->GetWidth()+8, m_paintBrush->m_bitmap->GetHeight()+8);
	}
	else
	{
		BrushCommand* pCmd = new BrushCommand;

		//LDraw::Bitmap* bitmap = m_document->m_selection->m_offscreenBitmap;

		pCmd->m_bitmap = m_paintBrush->m_bitmap;
		pCmd->m_destRect = LDraw::RectF(sample.pos.X - width/2-4, sample.pos.Y - height/2-4, width+8, height+8);
		pCmd->m_srcX = -4;
		pCmd->m_srcY = -4;
		pCmd->m_srcWidth = m_paintBrush->m_bitmap->GetWidth()+8;
		pCmd->m_srcHeight = m_paintBrush->m_bitmap->GetHeight()+8;

		if (m_mask)
		{
			LDraw::Bitmap* maskBitmap = ((ElementMask*)m_mask)->m_element->get_Bitmap();

			pCmd->m_mask = maskBitmap;
			pCmd->m_maskSrcX = pCmd->m_destRect.X;
			pCmd->m_maskSrcY = pCmd->m_destRect.Y;
			pCmd->m_maskSrcWidth = pCmd->m_destRect.Width;//m_paintBrush->m_bitmap->GetWidth();
			pCmd->m_maskSrcHeight = pCmd->m_destRect.Height;//m_paintBrush->m_bitmap->GetHeight();
		}

		dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands->AddCommand(pCmd);
	}
}

//void PathShape::Render(UI::Graphics* pGraphics)
int PathShape::Render(IDirect3DSurface9* renderTarget, IDirect3DSurface9* renderTarget2, LDraw::Bitmap* targetBitmap, LDraw::Bitmap* targetBitmap2, UI::Graphics* pGraphics)
{
	if (m_path)
	{
		m_path->Stroke(bind2st_of_3(mem_fun2(&PathShape::DrawBrush), this, pGraphics));

	}

	return 0;
}


///////////////////////////////////////
// ImageTool

void ImageTool::OnRender(BitmapEditor* view, UI::Graphics* pGraphics)
{
}

///////////////////////////////////////
// TransformTool

TransformTool::TransformTool()
{
}

void TransformTool::OnRender(BitmapEditor* view, UI::Graphics* pGraphics)
{
	if (view->m_selected)
	{
		for (int i = 0; i < view->m_selected->m_items.size(); i++)
		{
			PathSelected* selected = dynamic_cast<PathSelected*>(view->m_selected->m_items[i]);

			Element* element = selected->m_element;

			LDraw::SolidBrush* brush = new LDraw::SolidBrush(LDraw::Color(80, 160, 240));

			LDraw::DrawLineStripCommand* pCmd = new LDraw::DrawLineStripCommand;
			pCmd->m_brush = brush;
			pCmd->m_vertexBuffer = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexBuffer;
			pCmd->m_vertexOffsetInBytes = dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexOffsetInBytes;
			pCmd->m_count = 5;

			LDraw::RectD bounds = element->m_bounds;
			const LDraw::matrix3f& transform = element->m_transform;

			LDraw::vector2f pts[8] =
			{
				transform.transform(LDraw::vector2f(bounds.X, bounds.Y)),
				transform.transform(LDraw::vector2f(bounds.X+bounds.Width/2, bounds.Y)),
				transform.transform(LDraw::vector2f(bounds.X+bounds.Width, bounds.Y)),
				transform.transform(LDraw::vector2f(bounds.X+bounds.Width, bounds.Y+bounds.Height/2)),
				transform.transform(LDraw::vector2f(bounds.X+bounds.Width, bounds.Y+bounds.Height)),
				transform.transform(LDraw::vector2f(bounds.X+bounds.Width/2, bounds.Y+bounds.Height)),
				transform.transform(LDraw::vector2f(bounds.X, bounds.Y+bounds.Height)),
				transform.transform(LDraw::vector2f(bounds.X, bounds.Y+bounds.Height/2)),
			};

			unsigned int verticesSizeInBytes = sizeof(LDraw::VERTEX_XYZ)*5;
			LDraw::VERTEX_XYZ vertices[5] =
			{
				pts[0],
				pts[2],
				pts[4],
				pts[6],
				pts[0],
			};
			pGraphics->m_pO->m_device->VertexBufferSubData(dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexBuffer, dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexOffsetInBytes, verticesSizeInBytes, vertices);

			dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_bufferData->m_vertexOffsetInBytes += verticesSizeInBytes;

		//	pCmd->m_count = m_subPath[i]->DrawVertices(device, bufferData);

			dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands->AddCommand(pCmd);

			for (int i = 0; i < 8; i++)
			{
				pGraphics->FillRectangle(brush, pts[i][0]-2, pts[i][1]-2, 4, 4);
			}
		}
	}
}

void TransformTool::OnMouseDown(BitmapEditor* view, LDraw::PointD pos)
{
	if (!m_dragging)
	{
		m_dragging = 1;
		view->CaptureMouse();

		PathSelected* selected = dynamic_cast<PathSelected*>(view->m_selected->m_target);

		Element* element = selected->m_element;

		LDraw::RectD bounds = element->m_bounds;

		LDraw::PointD pts[8] =
		{
			LDraw::PointD(bounds.X, bounds.Y),
			LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y),
			LDraw::PointD(bounds.X+bounds.Width, bounds.Y),
			LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height/2),
			LDraw::PointD(bounds.X+bounds.Width, bounds.Y+bounds.Height),
			LDraw::PointD(bounds.X+bounds.Width/2, bounds.Y+bounds.Height),
			LDraw::PointD(bounds.X, bounds.Y+bounds.Height),
			LDraw::PointD(bounds.X, bounds.Y+bounds.Height/2),
		};

		LDraw::PointD xpts[8];
		for (int npt = 0; npt < 8; npt++)
		{
			xpts[npt] = element->m_transform.transform(pts[npt]);//.matrixTransform(viewMatrix);

		//	xpts[npt] = pts[npt];//.matrixTransform(viewMatrix);
			//m_matrix->transformPoint(&pts[npt], &xpts[npt]);
			//xpts[npt] = pts[npt];
		}

		for (int i = 0; i < 8; i++)
		{
			if ((fabs(/*d*/pos.X-xpts[i].X) <= 6) && (fabs(/*d*/pos.Y-xpts[i].Y) <= 6))
			{
				m_offset.X = (pos.X-xpts[i].X);//*magnify;
				m_offset.Y = (pos.Y-xpts[i].Y);//*magnify;

				m_hit = i+2;
				break;
			}
		}

#if 0
		if (m_hit == 0)
		{
			/*
			CComPtr<ILSVGMatrix> imatrix;
			m_matrix->inverse(&imatrix);
			*/

			LDraw::PointD xpt = pos;//wpt;///*dpt*/wpt.matrixTransform(imatrix);
			//imatrix->transformPoint((PointD*)&dpt, &xpt);

			if (xpt.X > bounds.X && xpt.Y > bounds.Y &&
				xpt.X < bounds.X+bounds.Width && xpt.Y < bounds.Y+bounds.Height)
			{
				m_hit = 1;	// Inside
			}
			else	// Outside (Rotate)
			{
				m_pivot.X = bounds.X + bounds.Width/2;	// Center
				m_pivot.Y = bounds.Y + bounds.Height/2;

				m_hit = 0;
			}
		}
#endif
		m_startTransform = selected->GetPath()->m_transform;
		m_startpos = pos;
	}
}

void TransformTool::OnMouseUp(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		m_dragging = 0;
		view->ReleaseMouseCapture();
	}
}

void TransformTool::OnMouseMove(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		PathSelected* selected = dynamic_cast<PathSelected*>(view->m_selected->m_target);

		LDraw::RectD bounds = selected->m_element->m_bounds;

		LDraw::matrix3f mat;

		LDraw::matrix3f istartTransform = m_startTransform.getInverse();

		if (m_hit >= 2)	// Scale
		{
			double cx, cy;
			double sx, sy;

			if (m_hit == 2)	// top-left
			{
				cx = bounds.X + bounds.Width;
				cy = bounds.Y + bounds.Height;
			}
			else if (m_hit == 3)
			{
				cx = bounds.X + bounds.Width/2;
				cy = bounds.Y + bounds.Height;
			}
			else if (m_hit == 4)
			{
				cx = bounds.X;
				cy = bounds.Y + bounds.Height;
			}
			else if (m_hit == 5)
			{
				cx = bounds.X;
				cy = bounds.Y + bounds.Height/2;
			}
			else if (m_hit == 6)
			{
				cx = bounds.X;
				cy = bounds.Y;
			}
			else if (m_hit == 7)
			{
				cx = bounds.X + bounds.Width/2;
				cy = bounds.Y;
			}
			else if (m_hit == 8)
			{
				cx = bounds.X + bounds.Width;
				cy = bounds.Y;
			}
			else if (m_hit == 9)
			{
				cx = bounds.X + bounds.Width;
				cy = bounds.Y + bounds.Height/2;
			}

			// TODO Snap to guides

			// Transform these into local coordinates

			LDraw::PointD pivot = istartTransform.transform(m_startpos - m_offset);
			//LDraw::PointD offset = istartTransform.transform(m_offset);
			pos = istartTransform.transform(pos);

			if (m_hit == 2 || m_hit == 4 || m_hit == 6 || m_hit == 8)
			{
				sx = (/*w*/pos.X - cx)/(/*w*/pivot.X - cx);
				sy = (/*w*/pos.Y - cy)/(/*w*/pivot.Y - cy);
			}
			else if (m_hit == 3 || m_hit == 7)
			{
				sx = 1;
				sy = (/*w*/pos.Y - cy)/(/*w*/pivot.Y - cy);
			}
			else if (m_hit == 5 || m_hit == 9)
			{
				sx = (/*w*/pos.X - cx)/(/*w*/pivot.X - cx);
				sy = 1;
			}

			mat =
				LDraw::matrix3f::getTranslate(-cx, -cy) *
				LDraw::matrix3f::getScale(sx, sy) *
				LDraw::matrix3f::getTranslate(cx, cy);
		}

		selected->GetPath()->m_transform = mat * m_startTransform;

		view->Invalidate();

#if 0
					else if (m_hit >= 2)	// Scale
					{
						double cx = 0;
						double cy = 0;
						double sx;
						double sy;

						RectD bounds = m_objectsBoundingBox;

						if (mouse->nFlags & MK_ALT)
						{
							cy = bounds.Y + bounds.Height/2;
							cx = bounds.X + bounds.Width/2;
						}
						else
						{
							if (m_hit == 2)	// top-left
							{
								cx = bounds.X + bounds.Width;
								cy = bounds.Y + bounds.Height;
							}
							else if (m_hit == 3)
							{
								cx = bounds.X + bounds.Width/2;
								cy = bounds.Y + bounds.Height;
							}
							else if (m_hit == 4)
							{
								cx = bounds.X;
								cy = bounds.Y + bounds.Height;
							}
							else if (m_hit == 5)
							{
								cx = bounds.X;
								cy = bounds.Y + bounds.Height/2;
							}
							else if (m_hit == 6)
							{
								cx = bounds.X;
								cy = bounds.Y;
							}
							else if (m_hit == 7)
							{
								cx = bounds.X + bounds.Width/2;
								cy = bounds.Y;
							}
							else if (m_hit == 8)
							{
								cx = bounds.X+bounds.Width;
								cy = bounds.Y;
							}
							else if (m_hit == 9)
							{
								cx = bounds.X+bounds.Width;
								cy = bounds.Y + bounds.Height/2;
							}
						}

						CComPtr<ILSVGMatrix> mat0;

						if (mouse->nFlags & MK_CONTROL &&
							(m_hit == 3 || m_hit == 7 || m_hit == 5 || m_hit == 9))
						{
							if (m_hit == 3 || m_hit == 7)	// Skew Y
							{
								double angle = 90 - GetLineAngle(/*w*/pt.X, /*w*/startpt.Y, cx, cy) * (180/M_PI);

								CComPtr<ILSVGMatrix> mat3;
								svgsvgElement->createSVGMatrix(&mat3);

								CComPtr<ILSVGMatrix> mat2;
								mat3->translate(0, -cy, &mat2);

								CComQIPtr<ILSVGMatrix> mat1;
								mat2->skewY(angle, &mat1);

								mat1->translate(0, cy, &mat0);
							}
							else	// SkewX
							{
								double angle = GetLineAngle(/*w*/startpt.X, /*w*/pt.Y, cx, cy) * (180/M_PI);

								CComPtr<ILSVGMatrix> mat3;
								svgsvgElement->createSVGMatrix(&mat3);

								CComPtr<ILSVGMatrix> mat2;
								mat3->translate(-cx, 0, &mat2);

								CComQIPtr<ILSVGMatrix> mat1;
								mat2->skewX(angle, &mat1);

								mat1->translate(cx, 0, &mat0);
							}
						}
						else
						{
							svgsvgElement->createSVGMatrix(&mat0);
						}

	#if 0
						// Snap to guides
						{
							CComPtr<IObjectMap> layergroups;
							m_activeSpread->get_layergroups(&layergroups);

							long nlayergroups;
							layergroups->get_length(&nlayergroups);

							for (long nlayergroup = 0; nlayergroup < nlayergroups; nlayergroup++)
							{
								CComPtr<IPDObjectLayerGroup> layergroup;
								layergroups->item(nlayergroup, (IUnknown**)&layergroup);

								CComPtr<IPDGuides> guides;
								layergroup->get_guides(&guides);

								long nguides;
								guides->get_length(&nguides);

								for (long i = 0; i < nguides; i++)
								{
									CComPtr<IPDGuide> guide;
									guides->item(i, &guide);

									long direction;
									guide->get_direction(&direction);

									double position;
									guide->get_position(&position);

									if (direction == 0)
									{
										if (fabs((wpt.y/*+m_offsetPt.y*/)-position) < 8)
										{
											wpt.y = position;//+m_offsetPt.y;
										}
									}
									else
									{
										if (fabs((wpt.x/*+m_offsetPt.x*/)-position) < 8)
										{
											wpt.x = position;//+m_offsetPt.x;
										}
									}
								}
							}
						}
	#endif

						if (m_hit == 2 || m_hit == 4 || m_hit == 6 || m_hit == 8)
						{
							sx = (/*w*/pt.X - cx)/(/*w*/startpt.X-m_offsetPt.X - cx);
							sy = (/*w*/pt.Y - cy)/(/*w*/startpt.Y-m_offsetPt.Y - cy);
						}
						else if (m_hit == 3 || m_hit == 7)
						{
							sx = 1;
							sy = (/*w*/pt.Y - cy)/(/*w*/startpt.Y-m_offsetPt.Y - cy);
						}
						else if (m_hit == 5 || m_hit == 9)
						{
							sx = (/*w*/pt.X - cx)/(/*w*/startpt.X-m_offsetPt.X - cx);
							sy = 1;
						}

						CComPtr<ILSVGMatrix> mat1;
						mat0->translate(-cx, -cy, &mat1);

						CComQIPtr<ILSVGMatrix> mat2;
						mat1->scaleNonUniform(sx, sy, &mat2);

						mat2->translate(cx, cy, &xMat);
					}
#endif
	}
}

///////////////////////////////////////
// MoveTool

MoveTool::MoveTool()
{
}

void MoveTool::OnMouseDown(BitmapEditor* view, LDraw::PointD pos)
{
	if (!m_dragging)
	{
		if (view->m_selected)
		{
			m_startpos = pos;

			m_startTransform.resize(view->m_selected->m_items.size());

			for (int i = 0; i < view->m_selected->m_items.size(); i++)
			{
				m_startTransform[i] = view->m_selected->m_items[i]->m_element->m_transform;
			}

			m_dragging = 1;
			view->CaptureMouse();
		}
	}
}

void MoveTool::OnMouseUp(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		m_dragging = 0;
		view->ReleaseMouseCapture();
	}
}

void MoveTool::OnMouseMove(BitmapEditor* view, LDraw::PointD pos)
{
	if (m_dragging)
	{
		float deltaX = pos.X - m_startpos.X;
		float deltaY = pos.Y - m_startpos.Y;

		for (int i = 0; i < view->m_selected->m_items.size(); i++)
		{
			view->m_selected->m_items[i]->m_element->m_transform = m_startTransform[i] * LDraw::matrix3f::getTranslate(deltaX, deltaY);
		}

		view->Invalidate();
	}
}

///////////////////////////////////////
// BitmapEditor

BitmapEditor::BitmapEditor()
{
	m_checkboardBitmap = CreateCheckboardBitmap(32, 32, LDraw::Color(190, 190, 190), LDraw::Color(255, 255, 255));

	UI::SetTimer(100, bind1st_of_2(mem_fun(&BitmapEditor::OnTimer), this));
}

void BitmapEditor::OnTimer(UINT)
{
	m_frame->get_ActiveTool()->OnTimer(this);

	if (m_document->m_selection)
	{
		++m_marchingOffset;
		Invalidate();
	}
}

void BitmapEditor::OnFramePropertyChanged(Object* sender, StringW* propertyName)
{
	Invalidate();
}

int RenderTo::Render(LDraw::GraphicsO* pO, ObservableCollection<Element*>* layers)
{
	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pO->m_device);
	ASSERT(pD3D9);

	IDirect3DSurface9* offscreenSurface[2];

	if (m_offscreenBitmap[0] == NULL)
	{
		m_offscreenBitmap[0] = new LDraw::Bitmap(m_width, m_height, m_width*4, LDraw::PixelFormat_t::RGBAP_32, NULL);
		m_offscreenBitmap[0]->m_d3dDevice = pD3D9->m_d3dDevice;
		m_offscreenBitmap[0]->m_d3dDevice->CreateTexture(m_offscreenBitmap[0]->GetWidth(), m_offscreenBitmap[0]->GetHeight(), 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_offscreenBitmap[0]->m_texture.u.d3d, NULL);
		m_offscreenBitmap[0]->m_d3dTexture = m_offscreenBitmap[0]->m_texture.u.d3d;
	}
	else
	{
		m_offscreenBitmap[0]->m_d3dTexture->AddRef();
	}

	m_offscreenBitmap[1] = NULL;

	if (m_offscreenBitmap[1] == NULL/* || m_offscreenBitmap[1]->GetWidth() != m_width || m_offscreenBitmap[1]->GetHeight() != m_height*/)
	{
		m_offscreenBitmap[1] = new LDraw::Bitmap(m_width, m_height, m_width*4, LDraw::PixelFormat_t::RGBAP_32, NULL);
		m_offscreenBitmap[1]->m_d3dDevice = pD3D9->m_d3dDevice;
		m_offscreenBitmap[1]->m_d3dDevice->CreateTexture(m_offscreenBitmap[1]->GetWidth(), m_offscreenBitmap[1]->GetHeight(), 1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &m_offscreenBitmap[1]->m_texture.u.d3d, NULL);
		m_offscreenBitmap[1]->m_d3dTexture = m_offscreenBitmap[1]->m_texture.u.d3d;
	}
	else
	{
		m_offscreenBitmap[1]->m_d3dTexture->AddRef();
	}

	offscreenSurface[0] = NULL;
	m_offscreenBitmap[0]->m_d3dTexture->GetSurfaceLevel(0, &offscreenSurface[0]);

	offscreenSurface[1] = NULL;
	m_offscreenBitmap[1]->m_d3dTexture->GetSurfaceLevel(0, &offscreenSurface[1]);

	IDirect3DSurface9* pOldRenderTarget;
	pD3D9->m_d3dDevice->GetRenderTarget(0, &pOldRenderTarget);

	pD3D9->m_d3dDevice->SetRenderTarget(0, offscreenSurface[0]);
	pD3D9->m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0x00000000, 0, 0);

	LDraw::Commands* commands = new LDraw::Commands;
	LDraw::GraphicsMetafile* pMetafile = new LDraw::GraphicsMetafile(pO->m_device, pO->m_bufferData, commands);
	UI::Graphics graphics(pMetafile);

	int m_scaledWidth = m_offscreenBitmap[0]->GetWidth();
	int m_scaledHeight = m_offscreenBitmap[0]->GetHeight();

	pD3D9->SetMatrixMode(GL_PROJECTION);
	pD3D9->PushMatrix();
	pD3D9->SetTransform(LDraw::matrix4f::getOrtho(0, m_scaledWidth, m_scaledHeight, 0, -1/*zNear*/, 1/*zFar*/));

	pD3D9->SetMatrixMode(GL_MODELVIEW);
	pD3D9->PushMatrix();
	pD3D9->IdentityTransform();

	graphics.PushTransform();
//	pO->SetTransform(LDraw::Matrix3f::GetIdentity());
//	pO->SetTransform(LDraw::Matrix3f::GetTranslate(-m_expandedBBox.X, -m_expandedBBox.Y));

	int noff = 0;
	int nlayers = layers->get_Count();
	for (int i = 0; i < nlayers; i++)
	{
		Element* element = layers->get_Item(i);
		if (element->m_visible)
		{
		//	layer->Render(m_offscreenSurface[0], m_offscreenBitmap[0], &graphics);
		//	noff ^= 1;
		//	noff = 1;

			graphics.PushTransform();
			graphics.MultiplyTransform(new LDraw::Matrix3f(element->m_transform));

			int change = element->Render(offscreenSurface[noff], offscreenSurface[noff^1], m_offscreenBitmap[noff], m_offscreenBitmap[noff^1], &graphics);
			noff ^= change;
		//	noff ^= 1;

			graphics.PopTransform();
		}
	}

	pD3D9->m_d3dDevice->BeginScene();
	pO->RenderCommands(commands);
	pD3D9->m_d3dDevice->EndScene();

	pO->PopTransform();

	pD3D9->SetMatrixMode(GL_PROJECTION);
	pD3D9->PopMatrix();
	pD3D9->SetMatrixMode(GL_MODELVIEW);
	pD3D9->PopMatrix();

	pD3D9->m_d3dDevice->SetRenderTarget(0, pOldRenderTarget);

	offscreenSurface[0]->Release();
	offscreenSurface[1]->Release();

//	m_offscreenBitmap[0]->m_d3dTexture->Release();
	m_offscreenBitmap[1]->m_d3dTexture->Release();

	return noff;
}

void BitmapEditor::OnRender(UI::Graphics* pGraphics)
{
	LDraw::Direct3D9_I* pD3D9 = dynamic_cast<LDraw::Direct3D9_I*>(pGraphics->m_p->m_device);
	ASSERT(pD3D9);

//	LDraw::SmoothingMode oldSmoothingMode = pGraphics->GetSmoothingMode();
//	pGraphics->SetSmoothingMode(LDraw::SmoothingModeHighQuality);

	m_renderTo.m_width = ceil(m_document->m_size.Width);
	m_renderTo.m_height = ceil(m_document->m_size.Height);

//	m_selectionRender.m_width = ceil(m_document->m_size.Width);
//	m_selectionRender.m_height = ceil(m_document->m_size.Height);

#if 0
	if (m_renderTarget == NULL)
	{
		D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONE;
	//	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_4_SAMPLES;
	//	D3DMULTISAMPLE_TYPE MultiSample = D3DMULTISAMPLE_NONMASKABLE;
		int quality = 0;

		/*
		if (MultiSample == D3DMULTISAMPLE_NONE)	// Create texture directly as RenderTarget
		{
			m_renderTargetSurface = pTextureSurface;
		}
		else	 // Create multisample RenderTarget
		*/
		{
			hr = pD3D9->m_d3dDevice->CreateRenderTarget(m_scaledWidth, m_scaledHeight, D3DFMT_A8R8G8B8, MultiSample, quality, false/*lockable*/, &m_multiSampleSurface, NULL);
			ASSERT(m_multiSampleSurface);

			m_renderTargetSurface = m_multiSampleSurface;
		}
	}
#endif

	{
		LDraw::SizeD size = m_document->m_size;//get_ActualSize();

		if (m_checkboardBitmap)
		{
			pGraphics->FillRectangle(new LDraw::TextureBrush(m_checkboardBitmap, LDraw::WrapModeTile), LDraw::RectF(0, 0, size.Width, size.Height));
		//	pGraphics->FillRectangle(LDraw::TextureBrush(m_checkboardBitmap, LDraw::RectF(0, 0, size.Width, size.Height), 0, 0, size.Width, size.Height, LDraw::WrapModeTile);

		//	pGraphics->DrawImage(m_checkboardBitmap, LDraw::RectF(0, 0, size.Width, size.Height), 0, 0, size.Width, size.Height, LDraw::WrapModeTile);
		//	pGraphics->DrawImage(m_checkboardBitmap, LDraw::RectF(0, 0, size.Width, size.Height), 0, 0, 32, 32, LDraw::WrapModeTile);
		//	pGraphics->DrawImage(m_checkboardBitmap, LDraw::RectF(0, 0, 32, 32), 0, 0, 32, 32, LDraw::WrapModeTile);
		}

		int noff = m_renderTo.Render(pGraphics->m_pO, m_document->m_layers);

		pGraphics->DrawImage(m_renderTo.m_offscreenBitmap[noff], LDraw::RectF(0, 0, m_renderTo.m_offscreenBitmap[0]->GetWidth(), m_renderTo.m_offscreenBitmap[0]->GetHeight()), 0, 0, m_renderTo.m_offscreenBitmap[0]->GetWidth(), m_renderTo.m_offscreenBitmap[0]->GetHeight());

		if (m_document->m_selection)
		{
			RenderTo renderTo;
			renderTo.m_width = m_renderTo.m_width;
			renderTo.m_height = m_renderTo.m_height;

			renderTo.m_offscreenBitmap[0] = m_document->m_selection->m_offscreenBitmap;
			renderTo.m_offscreenBitmap[1] = NULL;

			int noff = renderTo.Render(pGraphics->m_pO, m_document->m_selection->m_subObjects);

			m_document->m_selection->m_offscreenBitmap = renderTo.m_offscreenBitmap[noff];

			/*
			if (false)
			{
			pGraphics->DrawImage(m_selectionRender.m_offscreenBitmap[noff], LDraw::RectF(0, 0, m_selectionRender.m_offscreenBitmap[0]->GetWidth(), m_renderTo.m_offscreenBitmap[0]->GetHeight()), 0, 0, m_renderTo.m_offscreenBitmap[0]->GetWidth(), m_selectionRender.m_offscreenBitmap[0]->GetHeight());
			}
			else
			*/
			{
			BlendCommand2* pCmd = new BlendCommand2;

			LDraw::Bitmap* bitmap = m_document->m_selection->m_offscreenBitmap;

			pCmd->m_bitmap = bitmap;
			pCmd->m_pattern = s_Texture;
		//	pCmd->m_destRect = LDraw::RectF(0, 0, (float)m_bitmap->GetWidth(), (float)m_bitmap->GetHeight());
			pCmd->m_destRect = LDraw::RectF(0, 0, (float)bitmap->GetWidth(), (float)bitmap->GetHeight());
			pCmd->m_srcX = 0;
			pCmd->m_srcY = 0;
			pCmd->m_srcWidth = bitmap->GetWidth();
			pCmd->m_srcHeight = bitmap->GetHeight();

			pCmd->m_patternSrcX = m_marchingOffset;

			dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands->AddCommand(pCmd);
			}
		}

		if (m_selected)
		{
			/*
			for (int i = 0; i < m_document->m_selection->m_shapes.size(); i++)
			{
				Shape* shape = m_document->m_selection->m_shapes[i];

				dynamic_cast<PathShape*>(shape)->m_path->Draw(
					pGraphics->m_pO->m_device,
					pGraphics->m_pO->m_bufferData,
					dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands,
					new LDraw::SolidBrush(LDraw::Color(80, 160, 240)));
			}
			*/
		}

		if (m_selected)
		{
			if (m_selected->m_target)
			{
				Shape* shape = dynamic_cast<PathSelected*>(m_selected->m_target)->GetPath();

				dynamic_cast<PathShape*>(shape)->m_path->DrawOutline(
					pGraphics->m_pO->m_device,
					pGraphics->m_pO->m_bufferData,
					dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands,
					new LDraw::SolidBrush(LDraw::Color(80, 160, 240)), shape->m_transform);

				dynamic_cast<PathSelected*>(m_selected->m_target)->Draw(
					pGraphics->m_pO->m_device,
					pGraphics->m_pO->m_bufferData,
					dynamic_cast<LDraw::GraphicsMetafile*>(pGraphics->m_p)->m_pCommands,
					new LDraw::SolidBrush(LDraw::Color(80, 160, 240)));
			}
		}

		if (m_frame->m_activeTool)
		{
			m_frame->m_activeTool->OnRender(this, pGraphics);
		}

		/*
		LDraw::TextureBrush brush(&m_bitmap, LDraw::WrapModeTile, LDraw::RectF(0, 0, 100, 100));
		brush.TranslateTransform(50, 50);

		pGraphics->FillRectangle(&brush, 50, 50, m_computedSize.Width-40, m_computedSize.Height-40);
		*/

	//	LDraw::Font font(L"Arial", 20);

	//	pGraphics->DrawString("ABC", &font, LDraw::PointF(10, 10), &LDraw::SolidBrush(LDraw::Color(0,0,0)));
	//	pGraphics->FillRectangle(&LDraw::SolidBrush(LDraw::Color(0,0,0)), 20, 20, 100, 100);
	}

//	pGraphics->SetSmoothingMode(oldSmoothingMode);
}

LDraw::SizeD BitmapEditor::MeasureOverride(LDraw::SizeD availSize)
{
	return m_document->m_size;
}

void BitmapEditor::OnMouseDown(UI::MouseButtonEventArgs* args)
{
	Point mousepos = args->GetPosition(this);

	if (m_frame->m_activeTool)
	{
		m_frame->m_activeTool->OnMouseDown(this, mousepos);
	}

//	m_dragging = 1;
}

void BitmapEditor::OnMouseUp(UI::MouseButtonEventArgs* args)
{
	Point mousepos = args->GetPosition(this);

	if (m_frame->m_activeTool)
	{
		m_frame->m_activeTool->OnMouseUp(this, mousepos);
	}

	//m_dragging = 0;
}

void BitmapEditor::OnMouseMove(UI::MouseEventArgs* args)
{
	Point mousepos = args->GetPosition(this);

	if (m_frame->m_activeTool)
	{
		m_frame->m_activeTool->OnMouseMove(this, mousepos);
	}

	/*
	if (m_dragging)
	{
		BitmapLayer* layer = dynamic_cast<BitmapLayer*>(m_activeLayer);

		layer->m_points.push_back(LDraw::PointF(mousepos.X, mousepos.Y));

		InvalidateRender();
	}
	*/
}

void BitmapEditor::OnLayerAddLayer(Object* sender, UI::ExecutedRoutedEventArgs* args)
{
	MessageBeep(-1);
}

void BitmapEditor::OnCanLayerAddLayer(Object* sender, UI::CanExecuteRoutedEventArgs* args)
{
}

void BitmapEditor::OnLayerAddLayerMask(Object* sender, UI::ExecutedRoutedEventArgs* args)
{
	MessageBeep(-1);
}

void BitmapEditor::OnCanLayerAddLayerMask(Object* sender, UI::CanExecuteRoutedEventArgs* args)
{
}

}
