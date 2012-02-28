// DOK5Loader.cpp : Implementation of CDOK5Loader
#include "stdafx.h"
#include "LCinema4D.h"
#include "DOK5Loader.h"

/////////////////////////////////////////////////////////////////////////////
// CDOK5Loader

long CDOK5Loader::LoadObject(IStream* pStream, ILMFNode* children)
{
	//CI3DComp* pComp = (CI3DComp*)topLayer->GetLayerComp();

	CHUNKHDR ck;

// Object ident, always first
	if (ReadChunkHeader(pStream, &ck) != 0) return 1;

	CComPtr<ILX3DNode> node;// = (CI3DLayer*)sBasic->CreateCmdTarget("3DLAYER");
	//ASSERT(pLayer);
	//if (!pLayer) return 1;

	char name[1024] = {0};
	long hierarchy;
	float posi[3];
	float rota[3];
	float scale[3];

	switch (ck.type)
	{
	case 5100:	// Polygon
		{
#if 0
			pLayer->SetType(OBJT_POLYGON);
			pLayer->AddLayerParams();
#endif
			m_scene->createNode(L"IndexedFaceSet", &node);

			CComPtr<ILCoordinate> coordinateNode;
			m_scene->createNode(L"Coordinate", (ILX3DNode**)&coordinateNode);

			CComPtr<ILSFNode> coordField;
			node->getField(L"coord", (ILX3DField**)&coordField);
			coordField->setValue(coordinateNode);
// Empty
		}
		break;

	case 5106: // SphereObject
		{
			MessageBeep(-1);
#if 0
			float radius;
			LONG v;
			pStream->Read(&v, 4);
			*((DWORD*)&radius) = ENDIANLONG(v);

			pLayer->SetType(OBJT_POLYGON);
			pLayer->AddLayerParams();
			pLayer->Sphere(radius, 32);
#endif
		}
		break;

	case 5101:	// Spline object
		{
//			AfxMessageBox("Spline object");
			MessageBeep(-1);
#if 0
			pLayer->SetType(OBJT_SPLINE);
#endif
		}
		break;

	case 5103:// CameraObject
		{
			m_scene->createNode(L"Viewpoint", &node);

#if 0
			pLayer->SetType(OBJT_CAMERA);
			pLayer->AddLayerParams();
#endif

			float reserved[3];
			float focal_length;

			ReadFLOAT(pStream, &focal_length);
			ReadFLOAT(pStream, reserved);
			ReadVECTOR(pStream, reserved);

			long type_of_perspective;
			pStream->Read(&type_of_perspective, 4);
			type_of_perspective = ENDIANLONG(type_of_perspective);

		//	float FL = 36;
		//	float FOV = 2 * atan2 (36, FL);
		//	char msg[256];
		//	sprintf(msg, "%f", FOV);
		//	AfxMessageBox(msg);

		//	sprintf(msg, "Type of Perspective %d", type_of_perspective);
		//	AfxMessageBox(msg);

/*
REAL reserved
VECTOR reserved
LONG type_of_perspective
REAL depth_of_field_front
REAL depth_of_field _back
REAL depth_of_field_sharpness
REAL depth_of_field_type
*/
		}
		break;

	case 5102:	// LightObject
		{
			MessageBeep(-1);
#if 0
			pLayer->SetType(OBJT_LIGHT);
			pLayer->AddLayerParams();
			LoadLight(pStream, pLayer);
#endif
		}
		break;

	case 5107:	// EnvironmentObject
		{
			MessageBeep(-1);

#if 0
			AfxMessageBox("Environment object");

			pLayer->SetType(OBJT_ENVIRONMENT);
			pLayer->AddLayerParams();

			float ambient_color[3];
			float fog_color[3];
			float ambient_intensity;
			float fog_intensity;
			float fog_distance;

			ReadVECTOR(pStream, ambient_color);
			ReadVECTOR(pStream, fog_color);
			ReadFLOAT(pStream, &ambient_intensity);
			ReadFLOAT(pStream, &fog_intensity);
			ReadFLOAT(pStream, &fog_distance);

			pStream->Seek(4*5+1, CIStream::cur);
/*
REAL sun_latitude
LONG sun_hour
LONG sun_day
LONG sun_month
LONG sun_minutes
BOOL sun_shadow
*/
			BYTE fog_active;
			BYTE sun_active;
			pStream->Read(&fog_active, 1);
			pStream->Read(&sun_active, 1);

			pLayer->FindParam('ambc', 'env ')->SetParamTags((PARAM_COLOR_Value), RGB(ambient_color[0]*255,ambient_color[1]*255,ambient_color[2]*255), (TAG_DONE));
			pLayer->FindParam('ambb', 'env ')->SetParamTags((PARAM_SLIDER_Value), (long)(ambient_intensity*100)>>16, (TAG_DONE));

			pLayer->FindParam('fogc', 'env ')->SetParamTags((PARAM_COLOR_Value), RGB(fog_color[0]*255,fog_color[1]*255,fog_color[2]*255), (TAG_DONE));
			pLayer->FindParam('fogi', 'env ')->SetParamTags((PARAM_SLIDER_Value), (long)(fog_intensity*100)>>16, (TAG_DONE));
		//	fog_distance	// TODO
			pLayer->FindParam('foga', 'env ')->SetParamTags((PARAM_CHECKBOX_Value), fog_active, (TAG_DONE));
#endif
		}
		break;

//#define ENDIANFLOAT(f)		((float)(ENDIANLONG((DWORD)(vf))))

	case 5110:	// Particle Emitter
		{
			MessageBeep(-1);
#if 0
		//	AfxMessageBox("Particle Emitter");
			pLayer->SetType(OBJT_PARTICLE_EMITTER);
			pLayer->AddLayerParams();

			long editor_number;
			long render_number;
			float reserved;
			float v_start;
			float v_variance;
			TIME life_time;
			float life_time_variance;
			float size;
			float size_variance;
			float rotation;
			float rotation_variance;
			BYTE tangential;
			LONG emitter_type;
			float x_length;
			float y_length;
			float horizontal;
			float vertical;

			pStream->Read(&editor_number, 4); editor_number = ENDIANLONG(editor_number);
			pStream->Read(&render_number, 4); render_number = ENDIANLONG(render_number);
			ReadFLOAT(pStream, &reserved);
			ReadFLOAT(pStream, &v_start);
			ReadFLOAT(pStream, &v_variance);
			ReadTIME(pStream, &life_time);
			ReadFLOAT(pStream, &life_time_variance);
			ReadFLOAT(pStream, &size);				// End Scaling
			ReadFLOAT(pStream, &size_variance);
			ReadFLOAT(pStream, &rotation);
			ReadFLOAT(pStream, &rotation_variance);
			pStream->Read(&tangential, 1);
			pStream->Read(&emitter_type, 4); emitter_type = ENDIANLONG(emitter_type);
			ReadFLOAT(pStream, &x_length);
			ReadFLOAT(pStream, &y_length);
			ReadFLOAT(pStream, &horizontal);
			ReadFLOAT(pStream, &vertical);

			double lifetimesecs = life_time.nominator / life_time.denominator;
			long	lifetimeframes = lifetimesecs * topLayer->GetLayerComp()->GetFrameRate();

			pLayer->FindParam('brat', 'emit')->SetParamTags((PARAM_SLIDER_Value), render_number<<16, (TAG_DONE));
			pLayer->FindParam('lftm', 'emit')->SetParamTags((PARAM_SLIDER_Value), lifetimeframes<<16, (TAG_DONE));
			pLayer->FindParam('sped', 'emit')->SetParamTags((PARAM_SLIDER_Value), (long)(reserved*65536.0), (TAG_DONE));

			pLayer->FindParam('hori', 'emit')->SetParamTags((PARAM_ANGLE_Value), (long)(horizontal*65536.0), (TAG_DONE));
			pLayer->FindParam('vert', 'emit')->SetParamTags((PARAM_ANGLE_Value), (long)(vertical*65536.0), (TAG_DONE));
#endif
		}
		break;
/*
	case 5117: // ExtrudeObject
		{
			AfxMessageBox("Extrude object");
			pLayer->AddLayerParams();
		}
		break;

	case 5122: // BézierObject
		{
			AfxMessageBox("Bezier object");
			pLayer->AddLayerParams();
		}
		break;
*/
	case 5125: // BoneObject
		{
			MessageBeep(-1);

#if 0
			pLayer->SetType(OBJT_BONE);
			pLayer->AddLayerParams();

#if 0
			LONG bone_type;
			r->ReadF(r->file, &bone_type, 4);
			pLayer->bone_type = ENDIANLONG(bone_type);

			BYTE limit_range;
			r->ReadF(r->file, &limit_range, 1);
			pLayer->limit_range = limit_range;

			BYTE scale_strength;
			r->ReadF(r->file, &scale_strength, 1);
			pLayer->scale_strength = scale_strength;

			ReadFLOAT(r, &pLayer->minradius);
			ReadFLOAT(r, &pLayer->maxradius);
			ReadFLOAT(r, &pLayer->strength);
			ReadFLOAT(r, &pLayer->bone_length);
			ReadFLOAT(r, &pLayer->fix_bone_length);
			ReadFLOAT(r, &pLayer->fix_pos);
			ReadFLOAT(r, &pLayer->fix_scal);
			ReadFLOAT(r, &pLayer->fix_rot);
#endif
#endif
		}
		break;

	default:
			MessageBeep(-1);
#if 0
		pLayer->SetType(OBJT_POLYGON);
		pLayer->AddLayerParams();
#endif
	}

	LeaveChunk(pStream, &ck);

// Object data chunk (always second)
	if (ReadChunkHeader(pStream, &ck) != 0) return 1;

	{
		ATLASSERT(ck.type == 5021);

		long bits;

		Read(pStream, &hierarchy, 4);
		Read(pStream, &bits, 4);
		hierarchy = ENDIANLONG(hierarchy);
		bits = ENDIANLONG(bits);

		Seek(pStream, 4*12, STREAM_SEEK_CUR);	// MATRIX m

		ReadVECTOR(pStream, posi);	// pos
		ReadVECTOR(pStream, scale);	// scale
		ReadVECTOR(pStream, rota);	// rot

		if (posi[0] != 0 || posi[1] != 0 || posi[2] != 0 ||
			scale[0] != 1 || scale[1] != 1 || scale[2] != 1)
		{
			CComPtr<ILTransform> transform;
			m_scene->createNode(L"Transform", (ILX3DNode**)&transform);

			CComPtr<ILSFVec3f> translationField;
			transform->getField(L"translation", (ILX3DField**)&translationField);
			translationField->setValue(posi);

			CComPtr<ILSFVec3f> scaleField;
			transform->getField(L"scale", (ILX3DField**)&scaleField);
			scaleField->setValue(scale);

			children->append1Value(transform);

			CComPtr<ILMFNode> children2;
			transform->getField(L"children", (ILX3DField**)&children2);
			children = children2;
		}

		if (rota[0] != 0)
		{
			CComPtr<ILTransform> transform;
			m_scene->createNode(L"Transform", (ILX3DNode**)&transform);

			float rotation[4] = {1, 0, 0, rota[0]};

			CComPtr<ILSFRotation> rotationField;
			transform->getField(L"rotation", (ILX3DField**)&rotationField);
			rotationField->setValue(rotation);

			children->append1Value(transform);

			CComPtr<ILMFNode> children2;
			transform->getField(L"children", (ILX3DField**)&children2);
			children = children2;
		}

		if (rota[1] != 0)
		{
			CComPtr<ILTransform> transform;
			m_scene->createNode(L"Transform", (ILX3DNode**)&transform);

			float rotation[4] = {0, 1, 0, rota[1]};

			CComPtr<ILSFRotation> rotationField;
			transform->getField(L"rotation", (ILX3DField**)&rotationField);
			rotationField->setValue(rotation);

			children->append1Value(transform);

			CComPtr<ILMFNode> children2;
			transform->getField(L"children", (ILX3DField**)&children2);
			children = children2;
		}

		if (rota[2] != 0)
		{
			CComPtr<ILTransform> transform;
			m_scene->createNode(L"Transform", (ILX3DNode**)&transform);

			float rotation[4] = {0, 0, 1, rota[2]};

			CComPtr<ILSFRotation> rotationField;
			transform->getField(L"rotation", (ILX3DField**)&rotationField);
			rotationField->setValue(rotation);

			children->append1Value(transform);

			CComPtr<ILMFNode> children2;
			transform->getField(L"children", (ILX3DField**)&children2);
			children = children2;
		}

	// radian -> degrees
#if 0
		rota[0] *= 180/M_PI;
		rota[1] *= 180/M_PI;
		rota[2] *= 180/M_PI;
#endif

		WORD len;
		Read(pStream, &len, 2);
		len = ENDIANWORD(len);
		Read(pStream, name, len);

		LeaveChunk(pStream, &ck);
	}

#if 0	// Have this
	int offset = hierarchy - m_level;
	CI3DLayer* parentRef = NULL;

	if (!m_prevLayer)	// First layer we're adding
	{
		parentRef = topLayer;
		ATLASSERT(parentRef);
	}
	else
	{
		if (offset == 0)	// Same parent as previous layer
		{
			parentRef = (CI3DLayer*)m_prevLayer->GetParentObject();
			ASSERT(parentRef);
		}
		else if (offset == 1)	// Previous layer is parent
		{
			parentRef = m_prevLayer;
			ASSERT(parentRef);
		}
		else if (offset < 0)	// Back up
		{
			int i = -offset +1;
			parentRef = m_prevLayer;

			while (i--)
			{
				parentRef = (CI3DLayer*)parentRef->GetParentObject();
			}

			ATLASSERT(parentRef);
		}
	}

	ATLASSERT(parentRef);
	if (!parentRef) return -1;

	pLayer->SetName(name);

	parentRef->InsertObject(pLayer, NULL);
#endif
	children->append1Value(node);

//	TRACE("%s\n", pLayer->m_name);

/*
	C3DLayer layerRef = NULL;
		filterrec->layer->AddLayerTags(parentRef, NULL, 'SLER', 'OB3D', NULL,
		(LAYER_UserData),	pModel,
		(LAYER_Name),		name,
		(TAG_DONE));
	if (!layerRef) return NULL;
*/
	/*
	pLayer->FindParam('posi', 0)->SetParamTags(
		(PARAM_VECTOR_Value), posi,
		(TAG_DONE));

	pLayer->FindParam('rota', 0)->SetParamTags(
		(PARAM_VECTOR_Value), rota,
		(TAG_DONE));

	pLayer->FindParam('scle', 0)->SetParamTags(
		(PARAM_VECTOR_Value), scale,
		(TAG_DONE));
		*/

	m_prevLayer = node;
	m_level = hierarchy;

	do
	{
		if (ReadChunkHeader(pStream, &ck) != 0) return 1;

		switch (ck.type)
		{
		case 5613: // Display Tag
			{
			//	LONG reserved // should be set to zero
			//	LONG reserved // should be set to zero
				Seek(pStream, 8, STREAM_SEEK_CUR);

				LONG object;
				Read(pStream, &object, 4);
				object = ENDIANLONG(object);

				Seek(pStream, 11, STREAM_SEEK_CUR);
			/*
				BYTE ray_hide
				BYTE backcull
				BYTE normals
				BYTE back_picture
				BYTE axes
				BYTE show_path
				BYTE animation_effects
				BYTE shade_xy
				BYTE shade_xz
				BYTE shade_zy
				BYTE shade_3d
			*/

				if (ck.level >= 1)
				{
					BYTE edithide;
					Read(pStream, &edithide, 1);
#if 0
					pLayer->SetEditHide(edithide);
#endif
				}

				if (ck.level >= 2)
				{
				//	BYTE textures
				}
			}
			break;

		case 5600: // Point Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

				if (node)
				{
					CComPtr<ILSFNode> coordField;
					node->getField(L"coord", (ILX3DField**)&coordField);

					CComPtr<ILCoordinate> coord;
					coordField->getValue((ILX3DNode**)&coord);

					CComPtr<ILMFVec3f> pointField;
					coord->getField(L"point", (ILX3DField**)&pointField);

				//	char msg[512];
				//	sprintf(msg, "pt: %s - %d", name, number);
				//	AfxMessageBox(msg);

					LONG (*v)[3] = (LONG (*)[3])malloc(number*12);
					if (v)
					{
	#if 0
						evec3* data = pLayer->SetVertexDataSize(number);
	#endif

						Read(pStream, v, number*12);

						for (int i = 0; i < number; i++)
						{
							float vf[3];
							*((DWORD*)&vf[0]) = ENDIANLONG(v[i][0]);
							*((DWORD*)&vf[1]) = ENDIANLONG(v[i][1]);
							*((DWORD*)&vf[2]) = ENDIANLONG(v[i][2]);

							pointField->append1Value(vf);
	#if 0
							data[i].v[0] = vf[0];
							data[i].v[1] = vf[1];
							data[i].v[2] = vf[2];
	#endif
						}

						free(v);
					}
				}
			}
			break;

		case 5618:	// UV
			{
				//	Afx
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				BYTE x_cyclic;
				BYTE y_cyclic;

				Read(pStream, &number, 4); number = ENDIANLONG(number);
				Read(pStream, &reserved, 4);
				Read(pStream, &x_cyclic, 1);
				Read(pStream, &y_cyclic, 1);

			//	char msg[512];
			//	sprintf(msg, "uv: %s - %d", name, number);
			//	AfxMessageBox(msg);

				for (int i = 0; i < number; i++)
				{
					float u,v;
					ReadFLOAT(pStream, &u);
					ReadFLOAT(pStream, &v);
				}
			}
			break;

		case 5638:	// UVW Tag
			{
				ATLASSERT(0);
#if 0
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				BYTE x_cyclic;
				BYTE y_cyclic;

			//	pStream->Read(&number, 4); number = ENDIANLONG(number);
			//	pStream->Read(&reserved, 4);
			//	pStream->Read(&x_cyclic, 1);
			//	pStream->Read(&y_cyclic, 1);

				char msg[512];
				sprintf(msg, "uvw: %s - %d", name, number);
				MessageBox(NULL, msg, "", MB_OK);

				for (int i = 0; i < number; i++)
				{
					float uvw[3];
					ReadVECTOR(pStream, uvw);
				}
#endif
			}
			break;

		case 5653: // Triangle32 Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

				for (int i = 0; i < number; i++)
				{
#if 0
					int* data = pLayer->AddPoly(3);
#endif

					long v[3];
					Read(pStream, v, 12);
					v[0] = ENDIANLONG(v[0]);
					v[1] = ENDIANLONG(v[1]);
					v[2] = ENDIANLONG(v[2]);

#if 0
					data[0] = v[0];
					data[1] = v[1];
					data[2] = v[2];
#endif
				}
			}
			break;

		case 5601: //Triangle16 Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

				WORD (*v)[3] = (WORD (*)[3])malloc(number*6);
				if (v)
				{
					Read(pStream, v, number*6);

					for (int i = 0; i < number; i++)
					{
#if 0
						int* data = pLayer->AddPoly(3);
#endif

						v[i][0] = ENDIANWORD(v[i][0]);
						v[i][1] = ENDIANWORD(v[i][1]);
						v[i][2] = ENDIANWORD(v[i][2]);
#if 0
						data[0] = v[i][0];
						data[1] = v[i][1];
						data[2] = v[i][2];
#endif
					}

					free(v);
				}
			}
			break;

		case 5654: //Quadrangle32 Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

				for (int i = 0; i < number; i++)
				{
#if 0
					int* data = pLayer->AddPoly(4);
#endif

					long v[4];
					Read(pStream, v, 16);
#if 0
					data[0] = ENDIANLONG(v[0]);
					data[1] = ENDIANLONG(v[1]);
					data[2] = ENDIANLONG(v[2]);
					data[3] = ENDIANLONG(v[3]);
#endif
				}
			}
			break;

		case 5602: // Quadrangle16 Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

				CComPtr<ILMFInt32> coordIndex;
				node->getField(L"coordIndex", (ILX3DField**)&coordIndex);

				for (int i = 0; i < number; i++)
				{
#if 0
					int* data = pLayer->AddPoly(4);
#endif

					WORD v[4];
					Read(pStream, v, 8);

					coordIndex->append1Value(ENDIANWORD(v[0]));
					coordIndex->append1Value(ENDIANWORD(v[1]));
					coordIndex->append1Value(ENDIANWORD(v[2]));
					coordIndex->append1Value(ENDIANWORD(v[3]));
					coordIndex->append1Value(-1);
#if 0
					data[0] = ENDIANWORD(v[0]);
					data[1] = ENDIANWORD(v[1]);
					data[2] = ENDIANWORD(v[2]);
					data[3] = ENDIANWORD(v[3]);
#endif
				}
			}
			break;

		case 5655: // Edge32 Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

#if 0
				e-dge* data = pLayer->SetEdgeDataSize(number);
#endif

				for (int i = 0; i < number; i++)
				{
					DWORD	v[2];
					Read(pStream, v, 8);
#if 0
					data[i].v[0] = ENDIANLONG(v[0]);
					data[i].v[1] = ENDIANLONG(v[1]);
#endif
				}
			}
			break;

		case 5603: // Edge16 Tag
			{
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				Read(pStream, &number, 4);
				Read(pStream, &reserved, 4);
				number = ENDIANLONG(number);

#if 0
				pLayer->SetEdgeDataSize(number);
				edge* data = pLayer->GetEdgeData();
#endif

				for (int i = 0; i < number; i++)
				{
					WORD	v[2];
					Read(pStream, v, 4);
#if 0
					data[i].v[0] = ENDIANWORD(v[0]);
					data[i].v[1] = ENDIANWORD(v[1]);
#endif
				}
			}
			break;

		case 5617: // Hermite Tag
			{
#if 0
	//			AfxMessageBox("Hermite");
				LONG number; // number of elements
				LONG reserved; // should be set to zero
				r->ReadF(r->file, &number, 4);
				r->ReadF(r->file, &reserved, 4);
				number = ENDIANLONG(number);

				pLayer->hermiteArray.SetSize(number);

				for (int i = 0; i < number; i++)
				{
					float vf[3];

					ReadVECTOR(r, vf); // the left tangent
					pLayer->hermiteArray[i].left[0] = vf[0];
					pLayer->hermiteArray[i].left[1] = vf[1];
					pLayer->hermiteArray[i].left[2] = vf[2];

					ReadVECTOR(r, vf); // the right tangent
					pLayer->hermiteArray[i].right[0] = vf[0];
					pLayer->hermiteArray[i].right[1] = vf[1];
					pLayer->hermiteArray[i].right[2] = vf[2];
				}
#endif
			}
			break;

		case 5614: // Kinematic Tag
			{
			//	AfxMessageBox("Kinematic");
			}
			break;

		case 5616: // Texture Tag
			{
				long reserved;
				float pos[3];
				float scale[3];
				float rot[3];
				float offset_x;
				float offset_y_old;
				float length_x;
				float length_y;
				BYTE tile;
				BYTE seamless;
				BYTE additive;
				LONG mapping;
				LONG material_number; // 0 = no material, 1 = first material in file, 2 = second etc.

				Read(pStream, &reserved, 4);
				Read(pStream, &reserved, 4);

				ReadVECTOR(pStream, pos);
				ReadVECTOR(pStream, scale);
				ReadVECTOR(pStream, rot);

				ReadFLOAT(pStream, &offset_x);
				ReadFLOAT(pStream, &offset_y_old);
				ReadFLOAT(pStream, &length_x);
				ReadFLOAT(pStream, &length_y);
				Read(pStream, &tile, 1);
				Read(pStream, &seamless, 1);
				Read(pStream, &additive, 1);
				Read(pStream, &mapping, 4);
				Read(pStream, &material_number, 4);
				material_number = ENDIANLONG(material_number);

#if 0
				pLayer->AddTextureParams();

				if (material_number > 0)
				{
					pLayer->FindParam('mat ', 'txtr')->SetParamTags(PARAM_LAYER_Value,
						pComp->FindNthMaterial(material_number-1),
						(TAG_DONE));
				}
#endif
/*
27
LONG reserved // should be set to zero
LONG reserved // should be set to zero
VECTOR pos
VECTOR scale
VECTOR rot
REAL offset_x
REAL offset_y_old
REAL length_x
REAL length_y
BOOL tile
BOOL seamless
BOOL additive
LONG mapping
LONG material_number // 0 = no material, 1 = first material in file, 2 = second etc.
Level 1
MATRIX compensation
Level 2
LONG side
Level 3
REAL offset_y
*/			}
			break;

		case 5657: // WWW Tag
			{
			//	LONG reserved0; // should be set to zero
			//	LONG reserved1; // should be set to zero
				Seek(pStream, 8, STREAM_SEEK_CUR);

				WORD len;
				char text[4096];

				Read(pStream, &len, 2);
				Read(pStream, text, ENDIANWORD(len));
#if 0
				pLayer->SetUrl(text);
#endif

				Read(pStream, &len, 2);
				Read(pStream, text, ENDIANWORD(len));
#if 0
				pLayer->SetDescr(text);
#endif
			}
			break;

		case 5500:	// TRACK chunk (we skip this now, and read it later)
			{
#if 0	// TODO Have this
				TRACK* track = (TRACK*)malloc(sizeof(TRACK));
				track->next = NULL;

				if (m_prevTrack)
					m_prevTrack->next = track;
				else
					m_trackList = track;

				track->fileOffset = GetPos(pStream);
				track->layerRef = pLayer;

				m_prevTrack = track;
#endif
			}
			break;
		}

		LeaveChunk(pStream, &ck);
	}
	while (ck.type != 0);	// while no END Chunk

	return 0;
}

long CDOK5Loader::Load(IStream* pStream, ILMFNode* children)
{
	CHUNKHDR ck;

	ATLASSERT(children);

// Skip header
	Seek(pStream, 16, STREAM_SEEK_SET);

//	m_prevLayer = NULL;
	m_level = 0;

//	m_trackList = NULL;
//	m_prevTrack = NULL;

	do
	{
		if (ReadChunkHeader(pStream, &ck) != 0) return 1;

		switch (ck.type)
		{
#if 0	// Have this
		case 5703:	// MATERIAL
			{
				LoadMaterial(pStream, parentRef);
			}
			break;
#endif

		case 5020:	// OBJECT
			{
				long err = LoadObject(pStream, children);
				if (err != 0) return 0;
			}
			break;

		case 2000: // DOCUMENT
			{

			}
			break;

		default:
			{
			//	CString msg;
			//	msg.Format("un: %d", ck.type);
			//	AfxMessageBox(msg);
			}
			break;
		}

		LeaveChunk(pStream, &ck);
	}
	while (ck.type != 0);	// while no END Chunk

#if 0
	TRACK* track = m_trackList;

	while (track)
	{
		Seek(pStream, track->fileOffset, CIStream::beg);

		LoadTrack(pStream, track->layerRef, parentRef);

		TRACK* ftrack = track;
		track = track->next;
		free(ftrack);
	}
#endif

	return 0;
}

// ILX3DLoader
STDMETHODIMP CDOK5Loader::Load(/*[in]*/ IStream* stream, /*[in]*/ ILX3DScene* scene, /*[in]*/ ILMFNode* children)
{
	m_scene = scene;
	return Load(stream, children);
}
