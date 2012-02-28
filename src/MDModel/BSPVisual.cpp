#include "stdafx.h"
#include "BSPModel.h"

namespace System
{

/////////////////////////////////////
// BSPViewer

BSPViewer::BSPViewer()
{
	SetRetainedMode(false);

#if 0
	m_serverState = new LDraw::GLState;
	m_clientState = new LDraw::ClientState;
#endif

//	m_cameraPosition = LDraw::vector3f(400, 800, 300);
//	m_cameraPosition = LDraw::vector3f(0, 800, 0);
	m_camera.m_pos = LDraw::vector3f(0, 0, 0);
	m_camera.m_up = LDraw::vector3f(0, 1, 0);
	m_camera.m_forward = LDraw::vector3f(0, 0, 1);

	m_initialized = false;
}

uint8 palette[256][3];

struct VERTEX
{
	LDraw::vector3f v;
	LDraw::vector3f n;
	LDraw::vector2f tex0;
	LDraw::vector2f tex1;
};

#if 0
TextureManager::TextureManager()
{
	m_width = 0;
	m_height = 0;
}

void TextureManager::AddTexture(uint8* data, int width, int height)
{
	Texture* tex = new Texture;
	tex->m_width = width;
	tex->m_height = height;
	m_textures.push_back(tex);

	m_width += width;
	m_height = std::_MAX(m_height, height);
}
#endif

void BSPViewer::set_Map(BSPFile* bspfile)
{
//	m_filename = filename;
	m_bspfile = bspfile;

	m_textureIndex = new unsigned int[m_bspfile->m_ntexinfos];
}

void BSPViewer::SetOwnerWindow(VisualContentSource* pWindow)
{
	FrameworkElement::SetOwnerWindow(pWindow);
}

void BSPViewer::OnMouseDown(MouseButtonEventArgs* args)
{
	Point mousepos = args->GetPosition(this);
	CaptureMouse();
	if (args->get_LeftButton())
		m_dragging = 1;
	else
		m_dragging = 2;

	m_oldmousepos = mousepos;
}

void BSPViewer::OnMouseUp(MouseButtonEventArgs* args)
{
	Point mousepos = args->GetPosition(this);
	ReleaseMouseCapture();
	m_dragging = 0;
}

void BSPViewer::OnMouseMove(MouseEventArgs* args)
{
	if (m_dragging)
	{
		Point mousepos = args->GetPosition(this);

		if (m_dragging == 1)
		{
			float forward_distance = (mousepos.Y - m_oldmousepos.Y)*1;
			float left_distance = (mousepos.X - m_oldmousepos.X)*1;

			LDraw::vector3f left = LDraw::cross(m_camera.m_up, m_camera.m_forward);

			m_camera.m_pos += m_camera.m_up * forward_distance;
			m_camera.m_pos += left * left_distance;
		}
		else
		{
			//m_cameraPosition[0] += (mousepos.X - m_oldmousepos.X)*1;
			m_camera.m_pos[2] += (mousepos.Y - m_oldmousepos.Y)*1;

//			m_camera.m_forward[0] = (mousepos.Y - m_oldmousepos.Y)*1;

			LDraw::vector3f left = LDraw::cross(m_camera.m_up, m_camera.m_forward);

			LDraw::matrix4f cameramat;

			cameramat[0][0] = left[0];
			cameramat[0][1] = left[1];
			cameramat[0][2] = left[2];

			cameramat[1][0] = m_camera.m_up[0];
			cameramat[1][1] = m_camera.m_up[1];
			cameramat[1][2] = m_camera.m_up[2];

			cameramat[2][0] = m_camera.m_forward[0];
			cameramat[2][1] = m_camera.m_forward[1];
			cameramat[2][2] = m_camera.m_forward[2];

			cameramat[3][0] = 0;
			cameramat[3][1] = 0;
			cameramat[3][2] = 0;
			cameramat[3][3] = 1.0f;

			float angle = (mousepos.X - m_oldmousepos.X)*1;
			cameramat *= LDraw::matrix4f::getRotate(angle, LDraw::vector3f(0, 0, 1));

			m_camera.m_up[0] = cameramat[1][0];
			m_camera.m_up[1] = cameramat[1][1];
			m_camera.m_up[2] = cameramat[1][2];

			m_camera.m_forward[0] = cameramat[2][0];
			m_camera.m_forward[1] = cameramat[2][1];
			m_camera.m_forward[2] = cameramat[2][2];
		}

//		m_cameraPosition[0] += (mousepos.X - m_oldmousepos.X)*0.5;
//		m_cameraPosition[2] += (mousepos.Y - m_oldmousepos.Y)*0.5;

		//TRACE("%f\n", m_cameraPosition[2]);

		m_oldmousepos = mousepos;

		InvalidateRender();
	}
	else
	{
		// TODO Remove
		InvalidateRender();
	}
}

void BSPViewer::RenderFace(LDraw::Graphics3D* p3D, bsp_face* face, int iface)
{
	ASSERT(0);
#if 0

	if (true)
	{
		int nTexture = m_textureIndex[face->texture_info];
		Texture* pTexture = &m_texture[nTexture];
		if (pTexture->m_width == 0) return;
		p3D->BindTexture(GL_TEXTURE_2D, m_textureID[nTexture]);

//		p3D->DrawRangeElements(GL_TRIANGLE_FAN, m_faces[iface].start, m_faces[iface].end, m_nIndices/3, GL_UNSIGNED_INT, NULL);
		p3D->DrawArrays(GL_TRIANGLE_FAN, m_faces[iface].start, face->num_edges);
	}
	else
	{
	bsp_plane* plane = &m_bspfile->m_planes[face->plane];

	int nTexture = m_textureIndex[face->texture_info];
	Texture* pTexture = &m_texture[nTexture];
	if (pTexture->m_width == 0) return;

	p3D->BindTexture(GL_TEXTURE_2D, m_textureID[nTexture]);

	p3D->glBegin(GL_POLYGON);

	LDraw::vector3f normal = plane->normal;
	if (!face->plane_side)
		normal = -normal;

	p3D->glNormal(normal);

	bsp_texinfo* texinfo = &m_bspfile->m_texinfos[face->texture_info];

	for (int i = 0; i < face->num_edges; i++)
	{
		int iedge = face->first_edge + i;

		int32 edgeIndex = m_bspfile->m_faceedges[iedge];
		bool dir;
		if (edgeIndex < 0)
		{
			edgeIndex = -edgeIndex;
			dir = 1;
		}
		else
		{
			dir = 0;
		}

		VERIFY(edgeIndex < m_bspfile->m_nedges);
		bsp_edge* edge = &m_bspfile->m_edges[edgeIndex];

		LDraw::vector3f vertex = m_bspfile->m_vertices[edge->v[dir]];

	//	float u = (LDraw::dot(vertex, texinfo->u_axis) + texinfo->u_offset) / pTexture->width;
	//	float v = (LDraw::dot(vertex, texinfo->v_axis) + texinfo->v_offset) / pTexture->height;

		float s = (LDraw::dot(vertex, texinfo->u_axis) + texinfo->u_offset) / pTexture->m_width;
		float t = (LDraw::dot(vertex, texinfo->v_axis) + texinfo->v_offset) / pTexture->m_height;

		p3D->glTexCoordf(s, t);
		p3D->glVertex(vertex);
	}

	p3D->glEnd();
	}
#endif
}

void ApplyGamma(unsigned char *image, int size, int components, float gamma)
{
   if(!image) return;

   for(int i = 0; i < size / components; i++) 
      {
         float scale = 1.0f, temp = 0.0f;
         float r = 0, g = 0, b = 0;

         // extract the current RGB values
         r = (float)image[0];
         g = (float)image[1];
         b = (float)image[2];

         // Apply gamma.  Divide to keep 0 to 255.
         r *= gamma / 255.0f;
         g *= gamma / 255.0f;
         b *= gamma / 255.0f;

         temp = (1.0f / r);
         if(r > 1.0f && temp < scale) scale = temp;
         temp = (1.0f / g);
         if(g > 1.0f && temp < scale) scale = temp;
         temp = (1.0f / b);
         if(b > 1.0f && temp < scale) scale = temp;

         // Apply scale.
         scale *= 255.0f;		
         r *= scale;
         g *= scale;
         b *= scale;

         image[0] = (unsigned char)r;
         image[1] = (unsigned char)g;
         image[2] = (unsigned char)b;
         image += components;
      }
}

void BSPViewer::RenderFace(LDraw::Graphics3D* p3D, bsp_face_v3* face, int iface)
{
	int nTexture = m_textureIndex[face->texture];
	Texture* pTexture = &m_texture[nTexture];
	if (pTexture->m_width == 0) return;

//	p3D->ActiveTexture(GL_TEXTURE0);
//	p3D->BindTexture(GL_TEXTURE_2D, m_textureID[nTexture]);
//	p3D->ActiveTexture(GL_TEXTURE1);
//	p3D->BindTexture(GL_TEXTURE_2D, m_lightmapID[face->lm_index]);

	p3D->SetTexture(0, m_textureID[nTexture]);
	p3D->SetTexture(1, m_lightmapID[face->lm_index]);

	p3D->SetPrimitiveTopology(GL_TRIANGLE_FAN);
	p3D->Draw(face->vertex, face->n_vertexes);

//	p3D->DrawRangeElements(GL_TRIANGLES, 0, m_nVertices-1, face->n_meshverts, GL_UNSIGNED_INT, (void*)face->meshvert);

//	p3D->DrawRangeElements(GL_TRIANGLES, face->vertex, face->vertex+face->n_vertexes-1, face->n_meshverts, GL_UNSIGNED_INT, (void*)face->meshvert);

	//	p3D->DrawRangeElements(GL_TRIANGLES, m_faces[iface].start, m_faces[iface].end, face->n_meshverts, GL_UNSIGNED_INT, NULL);
//	p3D->DrawArrays(GL_TRIANGLE_FAN, m_faces[iface].start, face->num_edges);
}

void BSPViewer::RenderLeaf(LDraw::Graphics3D* p3D, bsp_leaf* leaf)
{
	/*
	if (true)
	{
		m_leafs[
		p3D->DrawRangeElements(GL_TRIANGLE_FAN, 0, m_bspfile->m_nvertices, m_nIndices/3, GL_UNSIGNED_INT, NULL);
	}
	else
*/
	{
		for (int i = 0; i < leaf->num_leaf_faces; i++)
		{
			int ileafface = leaf->first_leaf_face + i;
			VERIFY(ileafface < m_bspfile->m_nleaffaces);

			uint16 iface = m_bspfile->m_leaffaces[ileafface];
			VERIFY(iface < m_bspfile->m_nfaces);

			bsp_face* face = &m_bspfile->m_faces[iface];

			RenderFace(p3D, face, iface);

			//m_faces
		}
	}
}

void BSPViewer::RenderLeaf(LDraw::Graphics3D* p3D, bsp_leaf_v3* leaf)
{
	/*
	if (true)
	{
		m_leafs[
		p3D->DrawRangeElements(GL_TRIANGLE_FAN, 0, m_bspfile->m_nvertices, m_nIndices/3, GL_UNSIGNED_INT, NULL);
	}
	else
*/
	{
		for (int i = 0; i < leaf->n_leaffaces; i++)
		{
			int ileafface = leaf->leafface + i;
			VERIFY(ileafface < m_bspfile->m_nleaffaces);

			uint32 iface = m_bspfile->m_leaffaces_v3[ileafface];
			VERIFY(iface < m_bspfile->m_nfaces);

			bsp_face_v3* face = &m_bspfile->m_faces_v3[iface];

			RenderFace(p3D, face, iface);

			//m_faces
		}
	}
}

void BSPViewer::RenderNode(LDraw::Graphics3D* p3D, bsp_node* node)
{
	if (false)
	{
		for (int i = 0; i < node->num_faces; i++)
		{
			int iface = node->first_face + i;

			VERIFY(iface < m_bspfile->m_nfaces);
			bsp_face* face = &m_bspfile->m_faces[iface];

			RenderFace(p3D, face, iface);

			//m_faces
		}
	}

	if (node->front_child < 0)
	{
		int leafindex = -(node->front_child+1);
		VERIFY(leafindex < m_bspfile->m_nleaves);
		RenderLeaf(p3D, &m_bspfile->m_leaves[leafindex]);
	}
	else
	{
		RenderNode(p3D, &m_bspfile->m_nodes[node->front_child]);
	}

	if (node->back_child < 0)
	{
		int leafindex = -(node->back_child+1);
		VERIFY(leafindex < m_bspfile->m_nleaves);
		RenderLeaf(p3D, &m_bspfile->m_leaves[leafindex]);
	}
	else
	{
		RenderNode(p3D, &m_bspfile->m_nodes[node->back_child]);
	}
}

void BSPViewer::RenderNode(LDraw::Graphics3D* p3D, bsp_node_v3* node)
{
	if (node->children[0] < 0)
	{
		int leafindex = -(node->children[0]+1);
		VERIFY(leafindex < m_bspfile->m_nleaves);
		RenderLeaf(p3D, &m_bspfile->m_leaves_v3[leafindex]);
	}
	else
	{
		RenderNode(p3D, &m_bspfile->m_nodes_v3[node->children[0]]);
	}

	if (node->children[1] < 0)
	{
		int leafindex = -(node->children[1]+1);
		VERIFY(leafindex < m_bspfile->m_nleaves);
		RenderLeaf(p3D, &m_bspfile->m_leaves_v3[leafindex]);
	}
	else
	{
		RenderNode(p3D, &m_bspfile->m_nodes_v3[node->children[1]]);
	}
}

void BSPViewer::OnRender(Graphics* pGraphics)
{
	int upper_first_frame = 82;
	
	// Adjust
	int skip = 171 - upper_first_frame;

	FrameAnimation lowerAnimation;
	lowerAnimation.m_firstFrame = 186 - skip;
	lowerAnimation.m_frameCount = 17;

	ULONG ms = MSWindows::GetTickCount();
	ms %= 1000*60;

//	double fps = 4;
//	double curtime = (MSWindows::GetTickCount() / 1000.0);
	//curtime *= fps;

	float frame = ms / 1000.0;

	int iframe = (int)frame;
	float tween_factor = frame - iframe;

	//g_nframe = icurtime%26;

//	g_nframe = 

	LDraw::SizeD size = get_ActualSize();

	if (true)
	{
		LDraw::Graphics3D* p3D = GetOwnerWindow()->GetGraphics3D();

		int mode = 2;

		if (!m_initialized)
		{
			m_initialized = true;

			char dir[260];
			strcpy_s(dir, m_bspfile->m_filename);
			char* p = dir + std::strlen(dir)-1;
			while (*p != '\\' && *p != '/')
				p--;

			*p = 0;

			for (int i = 0; i < m_bspfile->m_ntexinfos; i++)
			{
				if (m_bspfile->header().version == 38)
				{
					bsp_texinfo* texinfo = &m_bspfile->m_texinfos[i];

					pair<map<const char*, unsigned int, cstr_less>::iterator, bool> r = m_textureNames.insert(map<const char*, unsigned int, cstr_less>::value_type(texinfo->texture_name, m_textureNames.size()));
					if (r.second)	// inserted
					{
						//r.first->second = -1;
					}
					m_textureIndex[i] = r.first->second;
				}
				else
				{
					bsp_texinfo_v3* texinfo = &m_bspfile->m_texinfos_v3[i];

					pair<map<const char*, unsigned int, cstr_less>::iterator, bool> r = m_textureNames.insert(map<const char*, unsigned int, cstr_less>::value_type(texinfo->name, m_textureNames.size()));
					if (r.second)	// inserted
					{
						//r.first->second = -1;
					}
					m_textureIndex[i] = r.first->second;
				}
			}

		//	TextureManager texman;

			m_texture = new Texture[m_textureNames.size()];

		//	Imaging::BitmapLoader loader;
		//	loader.Load(WSTR("C:\\Documents and Settings\\All Users\\Documents\\My Pictures\\Sample Pictures\\sunset.jpg"));
		//	LDraw::Bitmap* bitmap = loader.GetBitmap();

		//	m_serverState->BindTexture(GL_TEXTURE_2D, m_textureID[0]);
		//	m_serverState->TexImage2D(GL_TEXTURE_2D, bitmap);

			m_textureID = new LDraw::Texture[m_textureNames.size()];
#if 0
			p3D->GenTextures(m_textureNames.size(), m_textureID);
#endif

		#if 1
			int i = 0;
			map<const char*, unsigned int, cstr_less>::iterator it = m_textureNames.begin();
			while (it != m_textureNames.end())
			{
				char fullpath[300];
			//	std::sprintf(fullpath, "%s/../textures/%s.wal", dir, it->first);
				if (m_bspfile->header().version == 38)
				{
					sprintf_s(fullpath, "%s/../textures/%s.tga", dir, it->first);
				}
				else
				{
					sprintf_s(fullpath, "%s/../%s.tga", dir, it->first);
				}

				Imaging::BitmapLoader loader;
				loader.Load(new StringA(string_copy(fullpath)));
				LDraw::Bitmap* pBitmap = loader.GetBitmap();

				if (pBitmap)
				{
					m_texture[i].m_width = pBitmap->GetWidth();
					m_texture[i].m_height = pBitmap->GetHeight();

					m_textureID[i] = p3D->CreateTexture(pBitmap);
#if 0
					p3D->BindTexture(GL_TEXTURE_2D, m_textureID[i]);
				//	p3D->TexImage2D(GL_TEXTURE_2D, 0, 0, m_texture[i].m_width, m_texture[i].m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, rgbdata);
					p3D->TexImage2D(GL_TEXTURE_2D, pBitmap);
#endif

#if 0
				std::FILE* fp = std::fopen(fullpath, "rb");
				if (fp)
				{
					wal_header header;
					std::fread(&header, 1, sizeof(header), fp);

					uint8* data = new uint8[header.width * header.height];

					std::fseek(fp, header.offset[0], SEEK_SET);
					std::fread(data, header.width * header.height, 1, fp);

					m_texture[i].m_width = header.width;
					m_texture[i].m_height = header.height;

					uint8* rgbdata = new uint8[header.width * 3 * header.height];
					for (int y = 0; y < header.height; y++)
					{
						uint8* dst = rgbdata + y*header.width*3;
						uint8* src = data + y*header.width;

						for (int x = 0; x < header.width; x++)
						{
							dst[0] = palette[*src][0];
							dst[1] = palette[*src][1];
							dst[2] = palette[*src][2];
							/*
							dst[0] = x * 255 / header.width;
							dst[1] = y * 255 / header.height;
							dst[2] = 0;
							*/

							dst += 3;
							src++;
						}
					}
					delete[] data;

					std::fclose(fp);

					p3D->BindTexture(GL_TEXTURE_2D, m_textureID[i]);
					p3D->TexImage2D(GL_TEXTURE_2D, 0, 0, m_texture[i].m_width, m_texture[i].m_height, 0, GL_BGR, GL_UNSIGNED_BYTE, rgbdata);

			//		texman.AddTexture(rgbdata, header.width, header.height);
#endif
				}
				else
				{
					m_texture[i].m_width = 0;
					m_texture[i].m_height = 0;
				}

				++it;
				++i;
			}
		#endif

			if (mode == 0)
			{
#if 0
				p3D->GenBuffers(1, &m_vertexBuffer);
				p3D->BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);

				LDraw::vector3f vertices[3] =
				{
					LDraw::vector3f(0, 0, -2),
					LDraw::vector3f(3, 0, -2),
					LDraw::vector3f(3, 3, -2),
				};

				p3D->BufferData(GL_ARRAY_BUFFER, 3*sizeof(LDraw::vector3f), vertices, 0);
				p3D->glVertexPointer(3, GL_FLOAT, 0/*default stride*/, 0);

				unsigned int indicesData[3] =
				{
					0, 1, 2,
				};

				p3D->GenBuffers(1, &m_indicesBuffer);
				p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
				p3D->BufferData(GL_ELEMENT_ARRAY_BUFFER, 3*sizeof(uint), indicesData, 0);
#endif
			}
			else if (mode == 1)	// Draw edges
			{
				ASSERT(0);
#if 0
				p3D->GenBuffers(1, &m_vertexBuffer);
				p3D->BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
				p3D->BufferData(GL_ARRAY_BUFFER, m_bspfile->m_nvertices*sizeof(LDraw::vector3f), m_bspfile->m_vertices, 0);
				p3D->VertexPointer(0, 3, GL_FLOAT, 0/*default stride*/, 0);

				p3D->GenBuffers(1, &m_indicesBuffer);
				p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
				p3D->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_bspfile->m_nedges*sizeof(uint16)*2, m_bspfile->m_edges, 0);
#endif
			}
			else if (mode == 2)	// Filled
			{

				/*
				unsigned int* indicesData = new unsigned int[m_bspfile->m_nedges*2];
				for (int i = 0; i < m_bspfile->m_nedges; i++)
				{
					indicesData[i*2+0] = m_bspfile->m_edges[i].v[0];
					indicesData[i*2+1] = m_bspfile->m_edges[i].v[1];
				}
				*/
				const void* indicesData = m_bspfile->m_edges;

				uint16* indices;
				VERTEX* vertices;

			//	m_lightmapsTextureName
			//	p3D->GenTextures(1, &m_lightmapsTextureName);

				m_nVertices = 0;
				m_nIndices = 0;

				int lightmaps_width = 2048;
				int lightmaps_height = 0;

				if (true)
				{
					if (m_bspfile->header().version == 38)
					{
						indices = new uint16[m_bspfile->m_nfaces*12];
						vertices = new VERTEX[m_bspfile->m_nfaces*12];

						// triangle-fans

						m_faces = new Face[m_bspfile->m_nfaces];

						int row_height = 0;
						int lightmap_offset_x = 0;
						uint8* lightmap_rgb_data = new uint8[2048*1024*3];

						for (int i = 0; i < m_bspfile->m_nfaces; i++)
						{
							bsp_face* face = &m_bspfile->m_faces[i];

							bsp_texinfo* texinfo = &m_bspfile->m_texinfos[face->texture_info];
							int nTexture = m_textureIndex[face->texture_info];
							Texture* pTexture = &m_texture[nTexture];

							bsp_plane* plane = &m_bspfile->m_planes[face->plane];
							LDraw::vector3f normal = plane->normal;
							if (!face->plane_side)
								normal = -normal;

							if (pTexture->m_width)
							{
								float min_u;
								float max_u;
								float min_v;
								float max_v;

								m_faces[i].start = m_nVertices;

								for (int j = 0; j < face->num_edges; j++)
								{
									int index;
									{
									int iedge = face->first_edge + j;

									int32 edgeIndex = m_bspfile->m_faceedges[iedge];
									bool dir;
									if (edgeIndex < 0)
									{
										edgeIndex = -edgeIndex;
										dir = 1;
									}
									else
									{
										dir = 0;
									}

									VERIFY(edgeIndex < m_bspfile->m_nedges);
									bsp_edge* edge = &m_bspfile->m_edges[edgeIndex];
									index = edge->v[dir];
									}

									indices[m_nIndices++] = m_nVertices;
									vertices[m_nVertices+j].v = m_bspfile->m_vertices[index];
									vertices[m_nVertices+j].n = normal;
									float u = (LDraw::dot(vertices[m_nVertices+j].v, texinfo->u_axis) + texinfo->u_offset);
									float v = (LDraw::dot(vertices[m_nVertices+j].v, texinfo->v_axis) + texinfo->v_offset);
									vertices[m_nVertices+j].tex0[0] = u;// / pTexture->m_width;
									vertices[m_nVertices+j].tex0[1] = v;// / pTexture->m_height;

									if (j == 0)
									{
										min_u = u;
										max_u = u;
										min_v = v;
										max_v = v;
									}
									else
									{
										min_u = std::min(u, min_u);
										max_u = std::max(u, max_u);
										min_v = std::min(v, min_v);
										max_v = std::max(v, max_v);
									}
								}

								m_faces[i].lightmap_width  = ceil(max_u / 16) - floor(min_u / 16) + 1;
								m_faces[i].lightmap_height = ceil(max_v / 16) - floor(min_v / 16) + 1;
							//	m_faces[i].lightmap_width  = ((int)(ceil(max_u) - floor(min_u))+15) / 16;// + 1;
							//	m_faces[i].lightmap_height = ((int)(ceil(max_v) - floor(min_v))+15) / 16;// + 1;
							//	ASSERT(m_faces[i].lightmap_width <= 16);
							//	ASSERT(m_faces[i].lightmap_height <= 16);

								int lightmap_offset_y = lightmaps_height;
								if (lightmap_offset_x + m_faces[i].lightmap_width > 2048)
								{
									lightmap_offset_x = 0;
									lightmaps_height += row_height;
									row_height = 0;
								}
								ASSERT(lightmaps_height < 1024);
								row_height = std::max(row_height, m_faces[i].lightmap_height);

								for (int j = 0; j < face->num_edges; j++)
								{
									float u = vertices[m_nVertices+j].tex0[0];
									float v = vertices[m_nVertices+j].tex0[1];

									vertices[m_nVertices+j].tex1[0] = (lightmap_offset_x + ((int)(floor(u)-(int)floor(min_u)) / 16)) / 2047.0;
									vertices[m_nVertices+j].tex1[1] = (lightmap_offset_y + ((int)(floor(v)-(int)floor(min_v)) / 16)) / 1023.0;

									ASSERT(vertices[m_nVertices+j].tex1[0] >= 0 && vertices[m_nVertices+j].tex1[0] <= 1);
									ASSERT(vertices[m_nVertices+j].tex1[1] >= 0 && vertices[m_nVertices+j].tex1[1] <= 1);

									vertices[m_nVertices+j].tex0[0] /= pTexture->m_width;
									vertices[m_nVertices+j].tex0[1] /= pTexture->m_height;
								}

								m_nVertices += face->num_edges;

								ASSERT((face->lightmap_offset % 3) == 0);
								uint8* data = m_bspfile->m_lightmaps + face->lightmap_offset;
								ASSERT(face->lightmap_offset + m_faces[i].lightmap_width*3*m_faces[i].lightmap_height <= m_bspfile->m_lightmapssize);
								for (int y = 0; y < m_faces[i].lightmap_height; y++)
								{
									uint8* src = data + y * m_faces[i].lightmap_width*3;
									uint8* dst = lightmap_rgb_data + lightmap_offset_y * 2048*3 + lightmap_offset_x*3;
									for (int x = 0; x < m_faces[i].lightmap_width; x++)
									{
									//	dst[0] = 255-src[0];
									//	dst[1] = 255-src[1];
									//	dst[2] = 255-src[2];
										dst[0] = src[0];
										dst[1] = src[1];
										dst[2] = src[2];

										src += 3;
										dst += 3;
									}
								}

								lightmap_offset_x += m_faces[i].lightmap_width;
							}
						}

						/*
						p3D->ActiveTexture(GL_TEXTURE1);
						p3D->BindTexture(GL_TEXTURE_2D, m_lightmapsTextureName);
						p3D->TexImage2D(GL_TEXTURE_2D, 0, 0, 2048, 1024, 0, 0, 0, lightmap_rgb_data);
						*/
						m_lightmapsTextureName = p3D->CreateTexture(0, 0, 2048, 1024, 0, 0, 0, lightmap_rgb_data);
					}
					else	// quake 3
					{
						{
							m_lightmapID = new LDraw::Texture[m_bspfile->m_nlightmaps];
							//p3D->GenTextures(m_bspfile->m_nlightmaps, m_lightmapID);

						//	p3D->ActiveTexture(GL_TEXTURE1);
							for (int i = 0; i < m_bspfile->m_nlightmaps; i++)
							{
								ApplyGamma(m_bspfile->m_lightmaps_v3[i].data, 128*128*3, 3, 15);

							//	p3D->BindTexture(GL_TEXTURE_2D, m_lightmapID[i]);
							//	p3D->TexImage2D(GL_TEXTURE_2D, 0, 0, 128, 128, 0, 0, 0, m_bspfile->m_lightmaps_v3[i].data);
								m_lightmapID[i] = p3D->CreateTexture(0, GL_RGB, 128, 128, 0, GL_RGB, GL_UNSIGNED_BYTE, m_bspfile->m_lightmaps_v3[i].data);
							}
						}
						// triangles

						m_faces = new Face[m_bspfile->m_nfaces];

					//	int row_height = 0;
					//	int lightmap_offset_x = 0;
					//	uint8* lightmap_rgb_data = new uint8[2048*1024*3];

						m_nVertices = m_bspfile->m_nvertices;
						vertices = new VERTEX[m_bspfile->m_nvertices];

						m_nIndices = m_bspfile->m_nmeshverts;
						indices = new uint16[m_bspfile->m_nmeshverts];

						VERIFY(m_bspfile->m_nvertices < 65536);

						for (int i = 0; i < m_bspfile->m_nvertices; i++)
						{
							bsp_vertex_v3* v = &m_bspfile->m_vertices_v3[i];

							vertices[i].v = v->position;
							vertices[i].n = v->normal;
							vertices[i].tex0 = v->texcoord[0];
							vertices[i].tex1 = v->texcoord[1];
						}

						for (int i = 0; i < m_bspfile->m_nmeshverts; i++)
						{
							indices[i] = m_bspfile->m_meshverts[i];
						}

#if 0
						for (int i = 0; i < m_bspfile->m_nfaces; i++)
						{
							bsp_face_v3* face = &m_bspfile->m_faces_v3[i];

						//	bsp_texinfo* texinfo = &m_bspfile->m_texinfos[face->texture_info];
						//	int nTexture = m_textureIndex[face->texture_info];
						//	Texture* pTexture = &m_texture[nTexture];

							if (face->type == 1 || face->type == 3)
							{
								/*
								float min_u;
								float max_u;
								float min_v;
								float max_v;

								m_faces[i].start = m_nVertices;

								for (int j = 0; j < face->num_edges; j++)
								{
									int index;
									{
									int iedge = face->first_edge + j;

									int32 edgeIndex = m_bspfile->m_faceedges[iedge];
									bool dir;
									if (edgeIndex < 0)
									{
										edgeIndex = -edgeIndex;
										dir = 1;
									}
									else
									{
										dir = 0;
									}

									VERIFY(edgeIndex < m_bspfile->m_nedges);
									bsp_edge* edge = &m_bspfile->m_edges[edgeIndex];
									index = edge->v[dir];
									}
									*/

									bsp_vertex_v3& v = m_bspfile->m_vertices_v3[index];

									indices[m_nIndices++] = m_nVertices;
									vertices[m_nVertices+j].v = m_bspfile->m_vertices_v3[index];
									vertices[m_nVertices+j].n = normal;
									float u = (LDraw::dot(vertices[m_nVertices+j].v, texinfo->u_axis) + texinfo->u_offset);
									float v = (LDraw::dot(vertices[m_nVertices+j].v, texinfo->v_axis) + texinfo->v_offset);
									vertices[m_nVertices+j].tex0[0] = u;// / pTexture->m_width;
									vertices[m_nVertices+j].tex0[1] = v;// / pTexture->m_height;

								}

								m_nVertices += face->num_edges;
							}
						}
#endif
					}
				}
				else	// triangles
				{
					for (int i = 0; i < m_bspfile->m_nfaces; i++)
					{
						bsp_face* face = &m_bspfile->m_faces[i];

						bsp_texinfo* texinfo = &m_bspfile->m_texinfos[face->texture_info];

						bsp_plane* plane = &m_bspfile->m_planes[face->plane];
						LDraw::vector3f normal = plane->normal;
						if (!face->plane_side)
							normal = -normal;

						int iedge = face->first_edge;

						int32 edgeIndex = m_bspfile->m_faceedges[iedge];
						bool dir;
						if (edgeIndex < 0)
						{
							edgeIndex = -edgeIndex;
							dir = 1;
						}
						else
						{
							dir = 0;
						}

						VERIFY(edgeIndex < m_bspfile->m_nedges);
						bsp_edge* edge = &m_bspfile->m_edges[edgeIndex];

						int index0 = edge->v[dir];

						for (int j = 1; j < face->num_edges-1; j++)
						{
							int index1;
							{
							int iedge = face->first_edge + j;

							int32 edgeIndex = m_bspfile->m_faceedges[iedge];
							bool dir;
							if (edgeIndex < 0)
							{
								edgeIndex = -edgeIndex;
								dir = 1;
							}
							else
							{
								dir = 0;
							}

							VERIFY(edgeIndex < m_bspfile->m_nedges);
							bsp_edge* edge = &m_bspfile->m_edges[edgeIndex];
							index1 = edge->v[dir];
							}

							int index2;
							{
							int iedge = face->first_edge + j+1;

							int32 edgeIndex = m_bspfile->m_faceedges[iedge];
							bool dir;
							if (edgeIndex < 0)
							{
								edgeIndex = -edgeIndex;
								dir = 1;
							}
							else
							{
								dir = 0;
							}

							VERIFY(edgeIndex < m_bspfile->m_nedges);
							bsp_edge* edge = &m_bspfile->m_edges[edgeIndex];
							index2 = edge->v[dir];
							}

							//LDraw::vector3f vertex = m_bspfile->m_vertices[edge->v[dir]];

							indices[m_nIndices++] = m_nVertices;
							vertices[m_nVertices].v = m_bspfile->m_vertices[index0];
							vertices[m_nVertices].n = normal;
							vertices[m_nVertices].tex0[0] = (LDraw::dot(vertices[m_nVertices].v, texinfo->u_axis) + texinfo->u_offset) / 64;
							vertices[m_nVertices].tex0[1] = (LDraw::dot(vertices[m_nVertices].v, texinfo->v_axis) + texinfo->v_offset) / 64;
							m_nVertices++;

							indices[m_nIndices++] = m_nVertices;
							vertices[m_nVertices].v = m_bspfile->m_vertices[index1];
							vertices[m_nVertices].n = normal;
							vertices[m_nVertices].tex0[0] = (LDraw::dot(vertices[m_nVertices].v, texinfo->u_axis) + texinfo->u_offset) / 64;
							vertices[m_nVertices].tex0[1] = (LDraw::dot(vertices[m_nVertices].v, texinfo->v_axis) + texinfo->v_offset) / 64;
							m_nVertices++;

							indices[m_nIndices++] = m_nVertices;
							vertices[m_nVertices].v = m_bspfile->m_vertices[index2];
							vertices[m_nVertices].n = normal;
							vertices[m_nVertices].tex0[0] = (LDraw::dot(vertices[m_nVertices].v, texinfo->u_axis) + texinfo->u_offset) / 64;
							vertices[m_nVertices].tex0[1] = (LDraw::dot(vertices[m_nVertices].v, texinfo->v_axis) + texinfo->v_offset) / 64;
							m_nVertices++;
						}
					}
				}

				if (m_model && false)
				{
					ASSERT(0);
#if 0
					for (int i = 0; i < m_model->m_textures.size(); i++)
					{
						Q3Texture* texture = m_model->m_textures[i];

						p3D->GenTextures(1, &texture->m_id);
						p3D->ActiveTexture(GL_TEXTURE0);
						p3D->BindTexture(GL_TEXTURE_2D, texture->m_id);
						p3D->TexImage2D(GL_TEXTURE_2D, texture->m_bitmap);
					}
#endif
					if (m_model->m_head) m_model->m_head->GenBuffers(p3D);
					if (m_model->m_upper) m_model->m_upper->GenBuffers(p3D);
					if (m_model->m_lower) m_model->m_lower->GenBuffers(p3D);
				}

				if (true)
				{
					LDraw::VertexDeclElement elements[] =
					{
						{"POSITION",	0, 0,		LDraw::DECLTYPE_FLOAT3, 0},
						{"NORMAL",		0, 3*4,	LDraw::DECLTYPE_FLOAT3, 0},
						{"TEXCOORD",	0, 6*4,	LDraw::DECLTYPE_FLOAT2, 0},
						{"TEXCOORD",	0, 8*4,	LDraw::DECLTYPE_FLOAT2, 1},
					};

					m_vertexDeclaration = p3D->CreateVertexDeclaration(elements, 4);

					m_vertexBuffer = p3D->CreateVertexBuffer(m_nVertices*sizeof(VERTEX), vertices, GL_STATIC_DRAW);
	#if 0
					p3D->BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
					p3D->BufferData(GL_ARRAY_BUFFER, m_nVertices*sizeof(VERTEX), vertices, 0);
					p3D->glVertexPointer(3, GL_FLOAT, 0/*default stride*/, 0);
	#endif
				//	p3D->InterleavedData(GL_T2F_T2F_N3F_V3F, 0/*stride*/, vertices, m_nVertices*sizeof(VERTEX));

					m_triangleIndices = p3D->CreateIndexBuffer(GL_UNSIGNED_SHORT, m_nIndices*sizeof(uint16), indices);
					/*
					p3D->GenBuffers(1, &m_triangleIndices);
					p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleIndices);
					p3D->BufferData(GL_ELEMENT_ARRAY_BUFFER, m_nIndices*sizeof(uint16), indices, 0);
					*/
				}
			}
		}

		p3D->SetMatrixMode(GL_PROJECTION);
		p3D->PushMatrix();
		p3D->LoadIdentity();
		p3D->Perspective(45, 1/*size.Width/size.Height*/, 1, 1500.0);

		p3D->SetMatrixMode(GL_MODELVIEW);
		p3D->PushMatrix();
		p3D->LoadIdentity();

	//	p3D->glTranslatef(0, 0, -1200);
		p3D->RotateTransform(-90, 1, 0, 0);	// z is up
	//	p3D->glTranslate(-m_cameraPosition);

		LDraw::vector3f pos = m_camera.m_pos;
		LDraw::vector3f forward = m_camera.m_forward;
		LDraw::vector3f up = m_camera.m_up;

		LDraw::vector3f left;//(1, 0, 0);
		left = LDraw::cross(up, forward);

		LDraw::matrix4f cameramat;

		cameramat[0][0] = left[0];
		cameramat[0][1] = left[1];
		cameramat[0][2] = left[2];

		cameramat[1][0] = up[0];
		cameramat[1][1] = up[1];
		cameramat[1][2] = up[2];

		cameramat[2][0] = forward[0];
		cameramat[2][1] = forward[1];
		cameramat[2][2] = forward[2];

		cameramat[3][0] = pos[0];
		cameramat[3][1] = pos[1];
		cameramat[3][2] = pos[2];
		cameramat[3][3] = 1.0f;

		p3D->MultMatrixf(cameramat.getInverse());

	//	p3D->glTranslate(-m_cameraPosition);
		//p3D->glScalef(0.3, 0.3, 0.3);

		if (mode == 0)	// Points
		{
		//	p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
		//	p3D->BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			p3D->SetPrimitiveTopology(GL_POINTS);
			p3D->Draw(0, m_bspfile->m_nvertices);
		}
		else if (mode == 1)	// Edges
		{
			ASSERT(0);
#if 0
		//	p3D->BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
			p3D->DrawRangeElements(GL_LINES, 0, m_bspfile->m_nvertices, m_bspfile->m_nedges, GL_UNSIGNED_INT, NULL);
		//	p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indicesBuffer);
		//	p3D->DrawArrays(GL_POINTS, 0, m_bspfile->m_nvertices);
#endif
		}
		else if (mode == 2)	// Filled
		{
			// Fog
			if (false)
			{
				p3D->Enable(GL_FOG);
				p3D->Fogf(GL_FOG_MODE, GL_LINEAR);
				p3D->Fogf(GL_FOG_START, 0.5f);
				p3D->Fogf(GL_FOG_END, 100.0f);
			//	float color[4] = {1.0f, 1.0f, 1.0f, 1.0f};
				float color[4] = {0.2f, 0.2f, 0.2f, 0.2f};
				p3D->Fogfv(GL_FOG_COLOR, color);
			}

			if (m_bspfile->header().version == 38)
			{
				ASSERT(0);
#if 0
				p3D->Enable(GL_TEXTURE_2D);
				p3D->Enable(GL_DEPTH_TEST);

				if (true)	// triangle-fans
				{
					p3D->ActiveTexture(GL_TEXTURE1);
					p3D->BindTexture(GL_TEXTURE_2D, m_lightmapsTextureName);
					p3D->Enable(GL_TEXTURE_2D);

					p3D->ActiveTexture(GL_TEXTURE0);
					RenderNode(p3D, &m_bspfile->m_nodes[0]);	// Render root node
				}
				else	// triangles
				{
					p3D->BindTexture(GL_TEXTURE_2D, m_textureID[0]);

				//	p3D->BindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
					p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleIndices);
					p3D->DrawRangeElements(GL_TRIANGLES, 0, m_nVertices, m_nIndices/3, GL_UNSIGNED_INT, NULL);
				}
#endif
			}
			else
			{
				p3D->Enable(GL_DEPTH_TEST);
				p3D->DepthMask(true);
			//	p3D->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				//p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_triangleIndices);

				if (true)
				{
					ASSERT(0);
#if 0
					p3D->ActiveTexture(GL_TEXTURE0);
					p3D->Enable(GL_TEXTURE_2D);

					p3D->ActiveTexture(GL_TEXTURE1);
					p3D->Enable(GL_TEXTURE_2D);

					p3D->SetVertexDeclaration(m_vertexDeclaration);
					p3D->SetStreamSource(0, m_vertexBuffer, 0, sizeof(VERTEX));
					p3D->SetIndices(m_triangleIndices);

					p3D->Enable(GL_CULL_FACE);
					p3D->CullFace(GL_FRONT);

					RenderNode(p3D, &m_bspfile->m_nodes_v3[0]);	// Render root node

					p3D->ActiveTexture(GL_TEXTURE0);
					p3D->Disable(GL_TEXTURE_2D);

					p3D->ActiveTexture(GL_TEXTURE1);
					p3D->Disable(GL_TEXTURE_2D);

					p3D->ActiveTexture(GL_TEXTURE0);

					p3D->Disable(GL_CULL_FACE);
#endif
				}

				p3D->Disable(GL_DEPTH_TEST);
				p3D->DepthMask(false);

				if (false)
				{
				/*
				p3D->ActiveTexture(GL_TEXTURE0);
				p3D->glEnable(GL_TEXTURE_2D);
				p3D->BindTexture(GL_TEXTURE_2D, m_model->m_textureID[0]);
				*/

			//	p3D->ActiveTexture(GL_TEXTURE1);
			//	p3D->glDisable(GL_TEXTURE_2D);

				p3D->Enable(GL_NORMALIZE);

				p3D->Enable(GL_LIGHTING);

				float light_direction[4] = { 0, 0, 1, 0};	// directional
				float color[4] = {1, 1, 1, 1};
				float ambient[4] = {0, 0, 0, 1};
				p3D->Enable(GL_LIGHT0);
				/*
				p3D->glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
				p3D->glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
				p3D->glLightfv(GL_LIGHT0, GL_DIFFUSE, color);
				p3D->glLightfv(GL_LIGHT0, GL_SPECULAR, color);
				*/

				MD3Model::Tag* head_tag_head = m_model->m_head->m_tagNames[&StringA(false, "tag_head")];
				MD3Model::Tag* upper_tag_head = m_model->m_upper->m_tagNames[&StringA(false, "tag_head")];

				MD3Model::Tag* upper_tag_torso = m_model->m_upper->m_tagNames[&StringA(false, "tag_torso")];
				MD3Model::Tag* lower_tag_torso = m_model->m_lower->m_tagNames[&StringA(false, "tag_torso")];

//				int nframe = g_nframe%26;

				p3D->PushMatrix();
				p3D->MultMatrixf(head_tag_head->GetMatrix(0).getInverse());
				p3D->MultMatrixf(upper_tag_head->GetMatrix(0));
				m_model->m_head->Render(p3D, 0);
				p3D->PopMatrix();

				int lower_nframe = lowerAnimation.m_firstFrame + (iframe % lowerAnimation.m_frameCount);

				p3D->PushMatrix();
				p3D->MultMatrixf(lower_tag_torso->GetMatrix(lower_nframe, lower_nframe+1, tween_factor).getInverse());
				p3D->MultMatrixf(upper_tag_torso->GetMatrix(0));
				m_model->m_lower->Render(p3D, lower_nframe, lower_nframe+1, tween_factor);
				p3D->PopMatrix();

			//	p3D->glPushMatrix();
			//	p3D->glMultMatrixf(head_tag_head->GetMatrix());
				m_model->m_upper->Render(p3D, 0);
			//	p3D->glPopMatrix();
				}

			//	p3D->DrawRangeElements(GL_TRIANGLES, 0, m_nVertices, m_nIndices/3, GL_UNSIGNED_INT, NULL);
			}
		}

		p3D->SetMatrixMode(GL_PROJECTION);
		p3D->PopMatrix();

		p3D->SetMatrixMode(GL_MODELVIEW);
		p3D->PopMatrix();
	}
	else
	{
		ASSERT(0);
#if 0
		pGraphics->TranslateTransform(-0.5, -0.5);

		LDraw::Graphics3DImmediate* p3D = new LDraw::Graphics3DImmediate(m_serverState, m_clientState, static_cast<LDraw::GraphicsO*>(pGraphics->m_p));

		p3D->Viewport(0, 0, size.Width, size.Height);
		p3D->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		p3D->MatrixMode(GL_PROJECTION);
		p3D->LoadIdentity();
		p3D->Perspective(45, size.Width/size.Height, 1, 1500.0);

		p3D->MatrixMode(GL_MODELVIEW);
		p3D->LoadIdentity();

		p3D->Enable(GL_TEXTURE_2D);
		p3D->Enable(GL_LIGHTING);
		p3D->Enable(GL_DEPTH_TEST);

		if (true)//headlight)
		{
			float light_direction[4] = { 0, 0, 1, 0};	// directional
			float color[4] = {1, 1, 1, 1};
			float ambient[4] = {0, 0, 0, 1};

			p3D->Enable(GL_LIGHT0/*+xdc.m_nLight*/);

			p3D->Lightfv(GL_LIGHT0/*+xdc.m_nLight*/, GL_POSITION, light_direction);
			p3D->Lightfv(GL_LIGHT0/*+xdc.m_nLight*/, GL_AMBIENT, ambient);
			p3D->Lightfv(GL_LIGHT0/*+xdc.m_nLight*/, GL_DIFFUSE, color);
			p3D->Lightfv(GL_LIGHT0/*+xdc.m_nLight*/, GL_SPECULAR, color);
			
		//	xdc.m_nLight++;
		}

		if (false)
		{
			p3D->BindTexture(GL_TEXTURE_2D, m_textureID[0]);
			p3D->TexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE/*MODULATE*/);
			//p3D->glBegin(GL_POLYGON);
			p3D->glBegin(GL_TRIANGLES);

			p3D->glTexCoordf(0, 0);
			p3D->glColorf(1, 0, 0);
			p3D->glVertexf(0, 0, -8);

			p3D->glTexCoordf(0, 1);
			p3D->glColorf(0, 1, 0);
			p3D->glVertexf(0, -1, -8);

			p3D->glTexCoordf(1, 1);
			p3D->glColorf(0, 0, 1);
			p3D->glVertexf(1, -1, -8);

		//	p3D->glTexCoordf(0, 1);
		//	p3D->glVertexf(-20, 20, -200);

			p3D->glEnd();

			/*
			p3D->glBegin(GL_TRIANGLES);

			p3D->glTexCoordf(0, 0);
			p3D->glVertexf(-1, -1, -8);

			p3D->glTexCoordf(1, 1);
			p3D->glVertexf(1, 1, -8);

			p3D->glTexCoordf(0, 1);
			p3D->glVertexf(-1, 1, -8);

		//	p3D->glTexCoordf(0, 1);
		//	p3D->glVertexf(-20, 20, -200);

			p3D->glEnd();
			*/
		}

		p3D->glRotatef(90, 1, 0, 0);	// z is up
	//	p3D->glTranslate(-m_cameraPosition);

	//	p3D->glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		p3D->glColorf(0.5f, 0.5f, 0.5f);

	#if 0
		RenderNode(p3D, &m_bspfile->m_nodes[0]);	// Render root node
	#endif

		p3D->ReleaseGraphics();
#endif
	}
}
