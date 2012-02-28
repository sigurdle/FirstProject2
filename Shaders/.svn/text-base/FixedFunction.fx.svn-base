struct X3DLight
{
	int type;
	float4 diffuseColor;
	float4 specularColor;
	float4 ambientColor;
	float3 position;
	float3 direction;
	float range;
	float falloff;
	float attenuation0;
	float attenuation1;
	float attenuation2;
	float theta;
	float phi;
	bool on;
/*
	float4 ambient;
	float4 diffuseColor;
	float4 specular;
	float4 position;
	float constant_attenuation;
	float linear_attenuation;
	float quadratic_attenuation;
	*/
};

struct X3DMaterial
{
	float4 diffuseColor;
	float4 ambientColor;
	float4 specularColor;
	float4 emissiveColor;
	float power;
};

float4x4 view : VIEW;
float4x4 model : MODEL;
float4x4 modelView : MODELVIEW;
float4x4 modelViewProjection;
float4x4 modelViewIT;
float4 viewPosition;

#define MAX_LIGHTS		256
#define MAX_TEXTURES	16

int fogType;
float fogDistanceSquared;
float4 fogColor;

Texture2D textures[MAX_TEXTURES];

//int addressU;
//int addressV;

SamplerState textureSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Wrap;
    AddressV = Wrap;
};

SamplerState BorderSampler
{
    Filter = MIN_MAG_MIP_LINEAR;
    AddressU = Border;
    AddressV = Border;
};

uniform X3DMaterial material;

uniform X3DLight lights[MAX_LIGHTS];

uniform int ntextures;
uniform int nlights;

Texture2D HeightMapTexture;

struct VS_INPUT
{
	float4 vPos : POSITION;
	float3 vNorm : NORMAL;
};

struct VS_OUTPUT
{
	float4 ObjPos : POSITION;
	float4 ScreenPos : SV_POSITION;
	float3 Norm : NORMAL;
};

struct VS_INPUT_TEX
{
	float4 vPos : POSITION;
	float4 vNorm : NORMAL;
	float2 texCoord[1] : TEXCOORD;
};

struct VS_OUTPUT_TEX
{
	float4 ObjPos : POSITION;
	float4 ScreenPos : SV_POSITION;
	float3 Norm : NORMAL;
	float2 texCoord[1] : TEXCOORD;
};

struct VS_COLORTEX
{
	float4 objPos : POSITION;
	float4 screenPos : SV_POSITION;
	float4 color : COLOR;
	float2 texCoord : TEXCOORD;
};

struct GSPS_INPUT
{
	float4 Pos : SV_Position;
};

struct GSPS_OUTPUT
{
	float4 Pos : SV_Position;
	float3 Norm : NORMAL;
};

[maxvertexcount(3)]
void GSFaceNormal(triangle GSPS_INPUT vinput[3], inout TriangleStream<VS_OUTPUT> OutputStream)
{
    // Calculate the face normal
    float3 faceEdgeA = vinput[1].Pos - vinput[0].Pos;
    float3 faceEdgeB = vinput[2].Pos - vinput[0].Pos;
    float3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));
//    float3 faceNormal = normalize(cross(faceEdgeB, faceEdgeA));

	VS_OUTPUT output;
	output.Norm = faceNormal;

	int i;
	for (i = 0; i < 3; i++)
	{
		output.ScreenPos = vinput[i].Pos;
	
		OutputStream.Append(output);
	}
	
	OutputStream.RestartStrip();
}

[maxvertexcount(9000)]
void GSElevationGrid(triangle GSPS_INPUT vinput[3], inout LineStream<VS_OUTPUT> OutputStream)
{
    // Calculate the face normal
    float3 faceEdgeA = vinput[1].Pos - vinput[0].Pos;
    float3 faceEdgeB = vinput[2].Pos - vinput[0].Pos;
    float3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));
//    float3 faceNormal = normalize(cross(faceEdgeB, faceEdgeA));

	VS_OUTPUT output;
	output.Norm = faceNormal;

	output.ScreenPos = vinput[0].Pos;
	OutputStream.Append(output);

	output.ScreenPos = vinput[0].Pos + float4(faceNormal, 0);
	OutputStream.Append(output);
	
	OutputStream.RestartStrip();
}

[maxvertexcount(3)]
void GSFaceNormalOut(triangle GSPS_INPUT vinput[3], inout LineStream<VS_OUTPUT> OutputStream)
{
    // Calculate the face normal
    float3 faceEdgeA = vinput[1].Pos - vinput[0].Pos;
    float3 faceEdgeB = vinput[2].Pos - vinput[0].Pos;
    float3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));
//    float3 faceNormal = normalize(cross(faceEdgeB, faceEdgeA));

	VS_OUTPUT output;
	output.Norm = faceNormal;

	output.ScreenPos = vinput[0].Pos;
	OutputStream.Append(output);

	output.ScreenPos = vinput[0].Pos + float4(faceNormal, 0);
	OutputStream.Append(output);
	
	OutputStream.RestartStrip();
}

float4 CalcLights(float3 obj_pos, float3 N)
{
	float4 finalColor = float4(0, 0, 0, 1);

	int i;

	for (i = 0; i < nlights; ++i)
	{
	/*
		if (lights[i].type == 0)	// directional
		{
			float3 L = -lights[i].direction.xyz;
		
			float dotNL = max(0.0, dot(N, L));

			float4 diffuse = lights[i].diffuseColor * dotNL * material.diffuseColor;
		//	float4 specular = 0;//lights[i].specularColor * dotNL * material.specularColor;
		
			float4 color = (diffuse);
		
			finalColor += color;
		}
		else if (lights[i].type == 1)	// position
		*/
		{
			float spot = 1;
		
			float3 light_pos = lights[i].position.xyz;
			float3 c0 = lights[i].attenuation0;
			float3 c1 = lights[i].attenuation1;
			float3 c2 = lights[i].attenuation2;
			float3 toLight = light_pos - obj_pos;
			float3 L = normalize(toLight);

			float lightDist = length(toLight);

			float attenuation = 1/max(c0 + c1*lightDist + c2*lightDist*lightDist, 1);
			
			float dotNL = max(0.0, dot(N, L));
			
		//	float4 ambient = 0;
			float4 diffuse = lights[i].diffuseColor * dotNL * material.diffuseColor;
		//	float4 specular = 0;//lights[i].specularColor * dotNL * material.specularColor;
		
			float4 color = attenuation * spot * (/*ambient +*/ diffuse/* + specular*/);
		
			finalColor += color;
		}
	}

	return finalColor;
}

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 obj_pos = mul(input.vPos, modelView);
	float4 screen_pos = mul(input.vPos, modelViewProjection);
	float3 obj_norm = normalize(mul(input.vNorm, (float3x3)modelViewIT));

	output.ObjPos = obj_pos;
	output.ScreenPos = screen_pos;
	output.Norm = obj_norm;

	return output;
}

VS_OUTPUT_TEX VS_TEX(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX output;
	float4 obj_pos = mul(input.vPos, modelView);
	float4 screen_pos = mul(input.vPos, modelViewProjection);
	float3 obj_norm = normalize(mul(input.vNorm, (float3x3)modelViewIT));

	output.ObjPos = obj_pos;
	output.ScreenPos = screen_pos;
	output.Norm = obj_norm;

	int i;
	for (i = 0; i < 1; i++)
	{
		output.texCoord[0] = input.texCoord[0];
	}

	return output;
}

VS_COLORTEX VS_ColorTex(
	float4 vPos : POSITION,
	float4 vColor : COLOR,
	float4 vTexCoord : TEXCOORD
)
{
	VS_COLORTEX output;
	float4 obj_pos = mul(vPos, modelView);
	float4 screen_pos = mul(vPos, modelViewProjection);

	output.objPos = obj_pos;
	output.screenPos = screen_pos;
	output.texCoord = vTexCoord.xy;
	output.color = vColor;

	return output;
}

float4 PS_PhongLight(VS_OUTPUT vs) : SV_Target
{
	float4 color;

	if (fogType == 0)
	{
	//	color = float4(1,1,1,1);
		color = CalcLights(vs.ObjPos, normalize(vs.Norm));
	}
	else if (fogType == 1)
	{
		float distanceSquared = vs.ScreenPos*vs.ScreenPos;
		if (distanceSquared >= fogDistanceSquared)
		{
			color = fogColor;
		}
		else
		{
			color = CalcLights(vs.ObjPos, normalize(vs.Norm));
			
			float dim = (fogDistanceSquared-distanceSquared) / fogDistanceSquared;
			color *= dim;
		}
	}

	return color;
}

float4 PS_PhongLightTex(VS_OUTPUT_TEX vs) : SV_Target
{
	float4 color = float4(1,1,1,1);

	for (int i = 0; i < ntextures; i++)
	{
		color *= textures[0].Sample(textureSampler, vs.texCoord[0]);
	}

	color *= CalcLights(vs.ObjPos, normalize(vs.Norm));

	return color;
}

float4 PS_ColorTex(VS_COLORTEX v) : SV_Target
{
	float4 color = textures[0].Sample(textureSampler, v.texCoord) * v.color;
	return color;
}

float4 SolidPS(VS_OUTPUT vs) : SV_Target
{
	float4 color = float4(1, 0, 0, 1);
	return color;
}

GSPS_OUTPUT VS_HeightMap(
	float4 vPos : POSITION,
	float2 texCoord : TEXCOORD0)
{
	float dx = 1.0f/500;
	float dy = 1.0f/500;

	float p00 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x-dx, texCoord.y-dy), 0).r;
	float p10 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x, texCoord.y-dy), 0).r;
	float p20 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x+dx, texCoord.y-dy), 0).r;

	float p01 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x-dx, texCoord.y), 0).r;
	float p11 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x, texCoord.y), 0).r;
	float p21 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x+dx, texCoord.y), 0).r;

	float p02 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x-dx, texCoord.y+dy), 0).r;
	float p12 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x, texCoord.y+dy), 0).r;
	float p22 = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x+dx, texCoord.y+dy), 0).r;
	
	vPos.y += p11;

	float3 n0 = normalize(cross(p01 - p11, p00 - p11));
	float3 n1 = normalize(cross(p00 - p11, p10 - p11));
	
	float3 n2 = normalize(cross(p10 - p11, p21 - p11));
	float3 n3 = normalize(cross(p21 - p11, p22 - p11));
	float3 n4 = normalize(cross(p22 - p11, p12 - p11));
	float3 n5 = normalize(cross(p12 - p11, p01 - p11));

	float3 norm = (n0+n1+n2+n3+n4+n5) * (1/6);

	GSPS_OUTPUT output;
	output.Pos = mul(vPos, modelViewProjection);
	output.Norm = normalize(mul(norm, (float3x3)modelViewIT));

	return output;

/*
	VS_OUTPUT_TEX output;
	float4 obj_pos = mul(vPos, modelViewProjection);
	float3 N = normalize(mul(input.vNorm, (float3x3)modelViewIT));

	float4 color = CalcLights(obj_pos, N);

	int i;
	for (i = 0; i < 1; i++)
	{
		output.texCoord[0] = input.texCoord[0];
	}

	output.Pos = obj_pos;
	output.Color = color;

	return output;
	*/
}

GSPS_OUTPUT VS_ElevationGrid(
	float4 vPos : POSITION,
	float2 texCoord : TEXCOORD0)
{
	float height = HeightMapTexture.SampleLevel(BorderSampler, texCoord, 0).r;
//	float u = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x + 1/500, texCoord.y), 0).r;
//	float v = HeightMapTexture.SampleLevel(BorderSampler, float2(texCoord.x, texCoord.y + 1/500), 0).r;

	vPos.y = height*2;
//	float3 norm = normalize(float3(height-u, 0.5, height-v));

	GSPS_OUTPUT output;
	output.Pos = mul(vPos, modelViewProjection);
//	output.Norm = normalize(mul(norm, (float3x3)modelViewIT));

	return output;

/*
	VS_OUTPUT_TEX output;
	float4 obj_pos = mul(vPos, modelViewProjection);
	float3 N = normalize(mul(input.vNorm, (float3x3)modelViewIT));

	float4 color = CalcLights(obj_pos, N);

	int i;
	for (i = 0; i < 1; i++)
	{
		output.texCoord[0] = input.texCoord[0];
	}

	output.Pos = obj_pos;
	output.Color = color;

	return output;
	*/
}

technique10 PhongLightTechnique
{
    pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_PhongLight()));
	}
}

technique10 PhongLightTexTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS_TEX()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_PhongLightTex()));
	}
}

technique10 ColorTexTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS_ColorTex()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_ColorTex()));
	}
}

/*
technique10 HeightMapTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS_HeightMap()));
	//	SetGeometryShader(CompileShader(gs_4_0, GSFaceNormal()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
		
	//	SetVertexShader(CompileShader(vs_4_0, VS_HeightMap()));
	//	SetGeometryShader(CompileShader(gs_4_0, GSFaceNormalOut()));
	//	SetPixelShader(CompileShader(ps_4_0, SolidPS()));
	}
}
*/

struct VS_ColorOutput
{
	float4 Position : SV_Position;
	float4 Color : COLOR0;
};

VS_ColorOutput VS_Color(
	float4 vPos : POSITION,
	float4 vColor : COLOR0)
{
	VS_ColorOutput output;

	output.Position = mul(vPos, modelViewProjection);
	output.Color = vColor;

	return output;
}

float4 PS_Color(VS_ColorOutput In) : SV_Target
{
	return In.Color;
}

technique10 SolidColorTechnique
{
	pass P0
	{
	//	SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader(CompileShader( vs_4_0, VS_Color()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, PS_Color()));
	}
}
