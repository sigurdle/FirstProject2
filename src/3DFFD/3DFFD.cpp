// 3DFFD.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include <math.h>

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}


MMBasicSuite* sBasic;


class CFFD : public CI3DEffectImpl
{
protected:

	CIParam* paramID[4];

public:
	IMETHOD long OnAddParams(CI3DLayer* pLayer);
	IMETHOD long Transform(CI3DLayer* pLayer, vec3* vertex, DWORD size);
};

#if 0
typedef _VOLUMECTRLPTS
{
}
VOLUMECTRLPTS;
#endif

#include <assert.h>

void EvalVolume(float P[4][4][4][3], float u, float v, float w, float Ret[])
{
	assert(P != NULL);
	assert(u >= 0.0f && u <= 1.0f);
	assert(v >= 0.0f && v <= 1.0f);

	float BU[4], BV[4], BW[4];

	Ret[0] = Ret[1] = Ret[2] = 0;
//	CVector3D Ret(0);

	BU[0] = (1.0f - u) * (1.0f - u) * (1.0f - u);
	BU[1] = 3.0f * u * (1 - u) * (1.0f - u); 
	BU[2] = 3.0f * u * u * (1.0f - u); 
	BU[3] = u * u * u; 

	BV[0] = (1.0f - v) * (1.0f - v) * (1.0f - v);
	BV[1] = 3.0f * v * (1 - v) * (1.0f - v); 
	BV[2] = 3.0f * v * v * (1.0f - v); 
	BV[3] = v * v * v; 

	BW[0] = (1.0f - w) * (1.0f - w) * (1.0f - w);
	BW[1] = 3.0f * w * (1 - w) * (1.0f - w); 
	BW[2] = 3.0f * w * w * (1.0f - w); 
	BW[3] = w * w * w; 

	for (int i = 0; i < 4; i++)
	{	
		for (int j = 0; j < 4; j++)
		{	
			for (int k = 0; k < 4; k++)
			{ 	
				Ret[0] += P[i][j][k][0] * (BU[i] * BV[j] * BW[k]);
				Ret[1] += P[i][j][k][1] * (BU[i] * BV[j] * BW[k]);
				Ret[2] += P[i][j][k][2] * (BU[i] * BV[j] * BW[k]);
			}
		}
	}

//	return Ret;	
}

void GetBoundingBox(vec3* vertexArray, DWORD size, vec3 bounds[2])
{
  int i;
  double maxx, minx, maxy, miny, maxz, minz;

//	ASSERT(vertexArray.GetSize() > 0);

  /* get the max/mins */
  maxx = minx = vertexArray[0].v[0];
  maxy = miny = vertexArray[0].v[1];
  maxz = minz = vertexArray[0].v[2];

  for (i = 1; i < size; i++)
  {
	 vec3& vertex = vertexArray[i];

    if (maxx < vertex.v[0]) maxx = vertex.v[0];
    if (minx > vertex.v[0]) minx = vertex.v[0];

    if (maxy < vertex.v[1]) maxy = vertex.v[1];
    if (miny > vertex.v[1]) miny = vertex.v[1];

    if (maxz < vertex.v[2]) maxz = vertex.v[2];
    if (minz > vertex.v[2]) minz = vertex.v[2];
  }

  bounds[0].v[0] = minx;
  bounds[0].v[1] = miny;
  bounds[0].v[2] = minz;

  bounds[1].v[0] = maxx;
  bounds[1].v[1] = maxy;
  bounds[1].v[2] = maxz;
}


long CFFD::Transform(CI3DLayer* pLayer, vec3* vertex, DWORD size)
{
//	float sizef[3];
//	long strength;
//	paramID[0]->GetParamTags((PARAM_VECTOR_Value), sizef, (TAG_DONE));

	float center[3] = {0, 0, 0};

	CILayer* pLT = pLayer;
	do
	{
		float posi[3];
		pLT->FindParam('posi', 0)->GetParamTags((PARAM_VECTOR_Value), posi, (TAG_DONE));
		pLT = pLT->GetParentObject();

		center[0] += posi[0];
		center[1] += posi[1];
		center[2] += posi[2];
	}
	while (pLT);

	float P[4][4][4][3];

	{
		evec3* vecs = pLayer->GetVertexData();

		int i = 0;
		for (int x = 0; x < 4; x++)
		{
			for (int y = 0; y < 4; y++)
			{
				for (int z = 0; z < 4; z++)
				{
					P[z][x][y][0] = vecs[i].v[0];
					P[z][x][y][1] = vecs[i].v[1];
					P[z][x][y][2] = vecs[i].v[2];

					i++;
				}
			}
		}
	}

	vec3	bounds[2];
	GetBoundingBox(vertex, size, bounds);

	float maxx =  bounds[1].v[0] -  bounds[0].v[0];
	float maxy =  bounds[1].v[1] -  bounds[0].v[1];
	float maxz =  bounds[1].v[2] -  bounds[0].v[2];

	for (DWORD i = 0; i < size; i++)
	{
		double x = vertex[i].v[0];// - center[0];
		double y = vertex[i].v[1];// - center[1];
		double z = vertex[i].v[2];// - center[2];

		float u = (x - bounds[0].v[0]) / maxx;
		float v = (y - bounds[0].v[1]) / maxy;
		float w = (z - bounds[0].v[2]) / maxz;

		float Ret[3];
		EvalVolume(P, u, v, w, Ret);

		vertex[i].v[0] = Ret[0] /*- bounds[0].v[0]*/ + center[0];
		vertex[i].v[1] = Ret[1] /*- bounds[0].v[1]*/ + center[1];
		vertex[i].v[2] = Ret[2] /*- bounds[0].v[2]*/ + center[2];
	}

	return 0;
}

#include <stdio.h>

long CFFD::OnAddParams(CI3DLayer* pLayer)
{
// Grid Subdivisions

	int subx = 4;
	int suby = 4;
	int subz = 4;

// Set vertices & edges

	int ng = (subx)*(suby)*(subz);

	int nedges = (subx)*(suby)*(subz)*3 - subx*suby - subx*subz - suby*subz;

	evec3* vertex = pLayer->SetVertexDataSize(subx*suby*subz);
	edge* edg = pLayer->SetEdgeDataSize(nedges);

	double mx = (subx-1)/2.0;
	double my = (suby-1)/2.0;
	double mz = (subz-1)/2.0;

#define EDGE(v0, v1) \
	do { \
	edg[e].v[0] = v0; \
	edg[e].v[1] = v1; \
	e++; } while(0);
	
	int e = 0;
	int pnt = 0;
	
	for (int z = 0; z < subz; z++)
	{
		for (int y = 0; y < suby; y++)
		{
			for (int x = 0; x < subx; x++)
			{
				vertex[pnt].v[0] = x - mx;
				vertex[pnt].v[1] = y - my;
				vertex[pnt].v[2] = z - mz;
				
				if (x < subx-1) EDGE(pnt, pnt+1);
				if (y < suby-1) EDGE(pnt, pnt+subx);
				if (z < subz-1) EDGE(pnt, pnt+subx*suby);
				
				pnt++;
			}
		}
	}

	pLayer->Scale(150);

	CIParam* id;

	float sizef[3] = {200, 200, 200};

	id = paramID[0] = pLayer->AddParamTags(PARAM_VECTOR, -1,
		(PARAM_Name),					"Size",
		(PARAM_UniqID),				'size',
		(PARAM_VECTOR_Value),		sizef,
		(TAG_DONE));
	if (!id) return 1;

	id = paramID[1] = pLayer->AddParamTags(PARAM_SLIDER, -1,
		(PARAM_Name),					"Strength",
		(PARAM_UniqID),				'strn',
		(PARAM_SLIDER_Value),		500<<16,
		(PARAM_SLIDER_MinValue),   1<<16,
		(PARAM_SLIDER_MaxValue),	1000<<16,
		(PARAM_SLIDER_MaxUIValue),	800<<16,
		(PARAM_SLIDER_Precision),	1,
		(TAG_DONE));
	if (!id) return 1;

	return 0;
}

// Called at program startup
long Startup(MMMessageData* msg)
{
	sBasic->MMRegisterClass(msg->self,
		"I3DFFD", IID_3DEFFECT,
		NULL,
		NULL);

	return 0;
}


long SetupClass(MMClassMessage* msg)
{
	if (!strcmp(msg->classname, "I3DFFD"))
	{
		*msg->object = new CFFD;
	}

	return 0;
}

extern "C" __declspec(dllexport)
LONG
EntryPoint(char* caller, char* selector, MMMessageData* msg)
{
	long result = 0;

	sBasic = msg->basic;
//	thisPlugin = msg->self;

	if (!strcmp(selector, kMMStartup))
	{
		result = Startup(msg);
	}
	else if (!strcmp(selector, "SetupClass"))
	{
		result = SetupClass((MMClassMessage*)msg);
	}
	else if (!strcmp(selector, "SetdownClass"))
	{
	//	result = SetdownClass((MMAdapterMessage*)msg);
	}

	return result;
}
