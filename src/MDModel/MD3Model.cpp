#include "stdafx.h"
#include "BSPModel.h"

namespace System
{

int MD3Model::Load(IO::Stream* stream)
{
	int32 ident = ReadInt32(stream);
	if (ident != 0x33504449/*IDP3*/) return -1;

	int32 version = ReadInt32(stream);

	stream->Read(m_name, 64);

	uint32 flags = ReadInt32(stream);
	uint32 numframes = ReadInt32(stream);
	uint32 numtags = ReadInt32(stream);
	uint32 numsurfaces = ReadInt32(stream);
	uint32 numskins = ReadInt32(stream);
	uint32 offset_frames = ReadInt32(stream);
	uint32 offset_tags = ReadInt32(stream);
	uint32 offset_surfaces = ReadInt32(stream);
	uint32 offset_eof = ReadInt32(stream);

	// Read these in the order they appear in the stream
	uint32 offsets[3];
	offsets[0] = offset_frames;
	offsets[1] = offset_tags;
	offsets[2] = offset_surfaces;

	std::sort(offsets, offsets+3);

	if (numframes == 0)
	{
		raise(Exception("No frames"));
	}

	for (int i = 0; i < 3; i++)
	{
		if (offsets[i] == offset_frames)
		{
			stream->Seek(offset_frames, IO::SeekOrigin::STREAM_SEEK_SET);

			m_frames.reserve(numframes);
			for (unsigned int i = 0; i < numframes; i++)
			{
				Frame* frame = new Frame;

				frame->m_minBounds = ReadVector(stream);
				frame->m_maxBounds = ReadVector(stream);
				frame->m_localOrigin = ReadVector(stream);
				frame->m_radius = ReadFloat(stream);
				stream->Read(frame->m_name, 16);

				m_frames.push_back(frame);
			}
		}
		else if (offsets[i] == offset_tags)
		{
			stream->Seek(offset_tags, IO::SeekOrigin::STREAM_SEEK_SET);

			m_tags.reserve(numtags);

			// tags for first frame
			for (unsigned int i = 0; i < numtags; i++)
			{
				Tag* tag = new Tag;
				stream->Read(tag->m_name, 64);

				tag->m_frames = new Tag::Frame[numframes];

				tag->m_frames[0].m_origin = ReadVector(stream);
				tag->m_frames[0].m_axis[0] = ReadVector(stream);
				tag->m_frames[0].m_axis[1] = ReadVector(stream);
				tag->m_frames[0].m_axis[2] = ReadVector(stream);

				StringA* tagname = new StringA(string_copy(tag->m_name));

				m_tags.push_back(tag);
				m_tagNames[tagname] = tag;
			}

			// then the tags for the rest of the frames
			for (unsigned int nframe = 1; nframe < numframes; nframe++)
			{
				for (unsigned int i = 0; i < numtags; i++)
				{
					char name[64];
					stream->Read(name, 64);
					Tag* tag = m_tagNames.find(&StringA(false, name))->second;
					if (tag == NULL)
					{
						raise(Exception("Tag name not found while reading the rest of the frames"));
					}

					tag->m_frames[nframe].m_origin = ReadVector(stream);
					tag->m_frames[nframe].m_axis[0] = ReadVector(stream);
					tag->m_frames[nframe].m_axis[1] = ReadVector(stream);
					tag->m_frames[nframe].m_axis[2] = ReadVector(stream);
				}
			}
		}
		else if (offsets[i] == offset_surfaces)
		{
			stream->Seek(offset_surfaces, IO::SeekOrigin::STREAM_SEEK_SET);

			m_surfaces.reserve(numsurfaces);
			for (unsigned int i = 0; i < numsurfaces; i++)
			{
				Surface* surface = new Surface;
				ReadSurface(stream, surface);
				m_surfaces.push_back(surface);

				m_surfaceNames[new StringA(string_copy(surface->m_name))] = surface;
			}
		}
	}

	return 0;
}

int MD3Model::LoadSkin(IO::ISequentialByteStream* stream, Q3Model* model, ZIP::Archive* archive)
{
	while (1)
	{
		char line[512];
		if (ReadLine(stream, line) == -1)
			break;

		if (*line)
		{
			char* mesh = line;
			char* path = line;
			while (*path != ',') path++;

			*path = 0;
			path++;
			char* p = path;
			while (*p)
			{
				if (*p == '\\') *p = '/';
				++p;
			}

			if (*path)
			{
				Surface* surface = m_surfaceNames[&StringA(true, mesh)];
				VERIFY(surface);

				pair<map<StringA*, unsigned int, Ref_Less<StringA> >::iterator, bool> r = model->m_textureNames.insert(map<StringA*, unsigned int, Ref_Less<StringA> >::value_type(new StringA(string_copy(path)), 0));
				if (r.second)	// inserted
				{
					Q3Texture* texture = new Q3Texture;
					r.first->second = model->m_textures.size();
					model->m_textures.push_back(texture);

					Imaging::BitmapLoader bmloader;
					_Ptr<IO::Stream> fp = archive->FindFile(r.first->first)->GetStream();
					texture->m_bitmap = bmloader.Load(fp);
					ASSERT(texture->m_bitmap);
				}
				//m_textureIndex[i] = r.first->second;

				surface->m_texture = model->m_textures[r.first->second];
			}
		}
	}

	return 0;
}

void MD3Model::ReadSurface(IO::ISequentialByteStream* stream, Surface* surface)
{
	uint32 surface_offset = stream->Seek(0, IO::SeekOrigin::STREAM_SEEK_CUR);

	int32 ident = ReadInt32(stream);
	stream->Read(surface->m_name, 64);
	uint32 flags = ReadInt32(stream);
	uint32 numframes = ReadInt32(stream);
	//if (numframes != global_numframes) throw std::exception("Surface numframes doesn't match model numframes");
	surface->m_nframes = numframes;

	uint32 numshaders = ReadInt32(stream);
	surface->m_nvertices = ReadInt32(stream);
	surface->m_ntriangles = ReadInt32(stream);
	uint32 offset_triangles = ReadInt32(stream);
	uint32 offset_shaders = ReadInt32(stream);
	uint32 offset_st = ReadInt32(stream);
	uint32 offset_verts = ReadInt32(stream);
	uint32 offset_end = ReadInt32(stream);

	// Read these in the order they appear in the stream
	uint32 offsets[4];
	offsets[0] = offset_triangles;
	offsets[1] = offset_shaders;
	offsets[2] = offset_st;
	offsets[3] = offset_verts;

	std::sort(offsets, offsets+4);

	surface->m_texcoords = new LDraw::vector2f[surface->m_nvertices];
	surface->m_vertices = new Vertex[surface->m_nvertices * surface->m_nframes];
	surface->m_triangleIndices16 = new uint16[surface->m_ntriangles*3];

	for (int i = 0; i < 4; i++)
	{
		if (offsets[i] == offset_shaders)
		{
			stream->Seek(surface_offset + offset_shaders, IO::SeekOrigin::STREAM_SEEK_SET);

			surface->m_shaders.reserve(numshaders);

			for (int i = 0; i < numshaders; i++)
			{
				Shader* shader = new Shader;

				stream->Read(shader->m_name, 64);
				shader->m_id = ReadInt32(stream);

				surface->m_shaders.push_back(shader);
			}
		}
		else if (offsets[i] == offset_st)
		{
			stream->Seek(surface_offset + offset_st, IO::STREAM_SEEK_SET);
			for (int i = 0; i < surface->m_nvertices; i++)
			{
				surface->m_texcoords[i][0] = ReadFloat(stream);
				surface->m_texcoords[i][1] = 1-ReadFloat(stream);
			}
		}
		else if (offsets[i] == offset_triangles)
		{
			stream->Seek(surface_offset + offset_triangles, IO::STREAM_SEEK_SET);
			for (int i = 0; i < surface->m_ntriangles*3; i++)
			{
				int32 index = ReadInt32(stream);
				VERIFY(index < 65536);
				surface->m_triangleIndices16[i] = index;
			}
		}
		else if (offsets[i] == offset_verts)
		{
			stream->Seek(surface_offset + offset_verts, IO::STREAM_SEEK_SET);
			for (int i = 0; i < surface->m_nvertices * surface->m_nframes; i++)
			{
				ReadVertex(stream, &surface->m_vertices[i]);
			}
		}
	}

	stream->Seek(surface_offset + offset_end, IO::STREAM_SEEK_SET);
}

void MD3Model::ReadVertex(IO::ISequentialByteStream* stream, Vertex* vertex)
{
	int16 x = ReadInt16(stream);
	int16 y = ReadInt16(stream);
	int16 z = ReadInt16(stream);
	uint16 n = ReadInt16(stream);

	vertex->position[0] = x / 64.0;
	vertex->position[1] = y / 64.0;
	vertex->position[2] = z / 64.0;

	float longitude = (n>>8) * (2*M_PI) / 255;
	float latitude = (n & 0xFF) * (2*M_PI) / 255;

	vertex->normal[0] = cos(latitude) * sin(longitude);
	vertex->normal[1] = sin(latitude) * sin(longitude);
	vertex->normal[2] = cos(longitude);
}

void MD3Model::Render(LDraw::Graphics3D* p3D, int frame0)
{
	ASSERT(0);
#if 0

	p3D->SetVertexBlend(0);

	for (int i = 0; i < m_surfaces.size(); i++)
	{
		MD3Model::Surface* surface = m_surfaces[i];

		if (surface->m_texture)
		{
			p3D->ActiveTexture(GL_TEXTURE0);
			p3D->Enable(GL_TEXTURE_2D);
			p3D->BindTexture(GL_TEXTURE_2D, surface->m_texture->m_id);
		}

		p3D->BindVertexDeclaration(surface->m_vertexDeclaration);

		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_verticesName);
		p3D->InterleavedArrays(GL_N3F_V3F, sizeof(Vertex), (void*)(sizeof(Vertex)*frame0*surface->m_nvertices));
	//	p3D->InterleavedArrays(GL_N1_3F_V1_3F, sizeof(Vertex), (void*)(sizeof(Vertex)*frame1*surface->m_nvertices));

		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_texcoordsName);
		p3D->ActiveTexture(GL_TEXTURE0);
		p3D->TexCoordPointer(2, GL_FLOAT, sizeof(LDraw::vector2f), NULL);

		p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, surface->m_indicesName);
		p3D->DrawRangeElements(GL_TRIANGLES, 0, surface->m_nvertices-1, surface->m_ntriangles*3, GL_UNSIGNED_INT, 0);
	//	p3D->DrawRangeElements(GL_POINTS, 0, surface->m_nvertices-1, surface->m_ntriangles*3, GL_UNSIGNED_INT, 0);
	//	p3D->DrawArrays(GL_POINTS, 0, surface->m_nvertices);
	}
#endif
}

void MD3Model::Render(LDraw::Graphics3D* p3D, int frame0, int frame1, float tween_factor)
{
	ASSERT(0);
#if 0

	p3D->SetVertexBlend(1);
	p3D->SetTweenFactor(tween_factor);

	for (int i = 0; i < m_surfaces.size(); i++)
	{
		MD3Model::Surface* surface = m_surfaces[i];

		if (surface->m_texture)
		{
			p3D->ActiveTexture(GL_TEXTURE0);
			p3D->Enable(GL_TEXTURE_2D);
			p3D->BindTexture(GL_TEXTURE_2D, surface->m_texture->m_id);
		}

		p3D->BindVertexDeclaration(surface->m_vertexDeclaration);

		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_verticesName);
		p3D->InterleavedArrays(GL_N3F_V3F, sizeof(Vertex), (void*)(sizeof(Vertex)*frame0*surface->m_nvertices));
		p3D->InterleavedArrays(GL_N1_3F_V1_3F, sizeof(Vertex), (void*)(sizeof(Vertex)*frame1*surface->m_nvertices));

		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_texcoordsName);
		p3D->ActiveTexture(GL_TEXTURE0);
		p3D->TexCoordPointer(2, GL_FLOAT, sizeof(LDraw::vector2f), NULL);

		p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, surface->m_indicesName);
		p3D->DrawRangeElements(GL_TRIANGLES, 0, surface->m_nvertices-1, surface->m_ntriangles*3, GL_UNSIGNED_INT, 0);
	//	p3D->DrawRangeElements(GL_POINTS, 0, surface->m_nvertices-1, surface->m_ntriangles*3, GL_UNSIGNED_INT, 0);
	//	p3D->DrawArrays(GL_POINTS, 0, surface->m_nvertices);
	}
#endif
}

void MD3Model::GenBuffers(LDraw::Graphics3D* p3D)
{
	ASSERT(0);
#if 0
	for (int i = 0; i < m_surfaces.size(); i++)
	{
		MD3Model::Surface* surface = m_surfaces[i];

		p3D->GenBuffers(1, &surface->m_verticesName);
		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_verticesName);
	//	p3D->InterleavedData(GL_N3F_V3F, 0/*stride*/, surface->m_vertices, surface->m_nvertices*surface->m_nframes*sizeof(MD3Model::Vertex));
		p3D->BufferData(GL_ARRAY_BUFFER, surface->m_nvertices*surface->m_nframes*sizeof(Vertex), surface->m_vertices, 0);

		p3D->GenBuffers(1, &surface->m_texcoordsName);
	//	p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_texcoordsName);
	//	p3D->BufferData(GL_ARRAY_BUFFER, surface->m_ntriangles*3*sizeof(uint16), surface->m_triangleIndices16, 0);
	//	p3D->InterleavedData(GL_T2F, 0/*stride*/, surface->m_texcoords, surface->m_nvertices*sizeof(LDraw::vector2f));
	//	p3D->BufferData(GL_ELEMENT_ARRAY_BUFFER, surface->m_ntriangles*3*sizeof(uint16), surface->m_triangleIndices16, 0);
		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_texcoordsName);
		p3D->BufferData(GL_ARRAY_BUFFER, surface->m_nvertices*sizeof(LDraw::vector2f), surface->m_texcoords, 0);

		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_verticesName);
		p3D->InterleavedArrays(GL_N3F_V3F, sizeof(Vertex), NULL);//surface->m_verticesName);

		p3D->BindBuffer(GL_ARRAY_BUFFER, surface->m_texcoordsName);
		p3D->ActiveTexture(GL_TEXTURE0);
		p3D->TexCoordPointer(2, GL_FLOAT, sizeof(LDraw::vector2f), NULL);

		surface->m_vertexDeclaration = p3D->GenVertexDeclaration();

		p3D->GenBuffers(1, &surface->m_indicesName);
		p3D->BindBuffer(GL_ELEMENT_ARRAY_BUFFER, surface->m_indicesName);
		p3D->BufferData(GL_ELEMENT_ARRAY_BUFFER, surface->m_ntriangles*3*sizeof(uint16), surface->m_triangleIndices16, 0);
	}
#endif
}

}
