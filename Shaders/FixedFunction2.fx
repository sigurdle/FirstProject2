struct GSPS_INPUT
{
	float4 Pos : SV_Position;
	float2 TexCoord : TEXCOORD0;
};

struct GSPS_OUTPUT
{
	float4 Pos : SV_Position;
	float3 Norm : NORMAL;
	float2 TexCoord : TEXCOORD0;
};

[maxvertexcount(3)]
void GS(triangle GSPS_INPUT vinput[3], inout TriangleStream<GSPS_OUTPUT> OutputStream)
{
    // Calculate the face normal
    float3 faceEdgeA = vinput[1].Pos - vinput[0].Pos;
    float3 faceEdgeB = vinput[2].Pos - vinput[0].Pos;
    float3 faceNormal = normalize(cross(faceEdgeA, faceEdgeB));

	GSPS_OUTPUT output;
	output.Norm = faceNormal;

	int i;
	for (i = 0; i < 3; i++)
	{
		output.Pos = vinput[i].Pos;
		output.TexCoord = vinput[i].TexCoord;
	
		OutputStream.Append(output);
	}
	
	OutputStream.RestartStrip();
}

struct X3DLight
{
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
	int type;
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

float4x4 modelView : MODELVIEW;
float4x4 modelViewIT;
float4x4 modelViewProjection;

#define MAX_LIGHTS		256
#define MAX_TEXTURES	16

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
	float4 Pos : POSITION;
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
	float4 Pos : SV_POSITION;
	float3 Norm : NORMAL;
	float4 Color : COLOR;
	float2 texCoord[1] : TEXCOORD;
};

float4 CalcLights(float3 obj_pos, float3 N)
{
	float4 finalColor = float4(0, 0, 0, 1);

	int i;

	for (i = 0; i < nlights; i++)
	{
		float3 light_pos = lights[i].position.xyz;
		
		float3 L = normalize(light_pos - obj_pos);

		float dotNL = max(0.0, dot(N, L));
		
	//	float4 ambient = 0;
		float4 diffuse = lights[i].diffuseColor * dotNL * material.diffuseColor;
	//	float4 specular = 0;//lights[i].specularColor * dotNL * material.specularColor;
	
		float4 color = (/*ambient +*/ diffuse/* + specular*/);
	
		finalColor += color;
	}

	return finalColor;
}

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	float4 obj_pos = mul(input.vPos, modelViewProjection);
	float3 obj_norm = normalize(mul(input.vNorm, (float3x3)modelViewIT));

	output.Pos = obj_pos;
	output.ScreenPos = obj_pos;
	output.Norm = obj_norm;

	return output;
}

float4 PS(VS_OUTPUT vs) : SV_Target
{
	float4 color = CalcLights(vs.Pos, normalize(vs.Norm));
	return color;
}

VS_OUTPUT_TEX VS_TEX(VS_INPUT_TEX input)
{
	VS_OUTPUT_TEX output;
	float4 obj_pos = mul(input.vPos, modelViewProjection);
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
}

GSPS_INPUT VS_HeightMap(
	float4 vPos : POSITION,
	float2 texCoord : TEXCOORD0)
{
	float height = HeightMapTexture.Sample(BorderSampler, texCoord);

	GSPS_INPUT output;
	output.Pos = mul(vPos, modelViewProjection);
	output.TexCoord = texCoord;
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

float4 PS_TEX(VS_OUTPUT_TEX vs) : SV_Target
{
	float color = vs.Color;

	for (int i = 0; i < ntextures; i++)
	{
		color *= textures[0].Sample(textureSampler, vs.texCoord[0]);
	}

	return color;
}

// Technique Definition
technique10 Render
{
    pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS()));
	}
}

technique10 RenderTex
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS_TEX()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, PS_TEX()));
	}
}

technique10 HeightMapTechnique
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_4_0, VS_HeightMap()));
		SetGeometryShader(CompileShader(vs_4_0, GS()));
		SetPixelShader(CompileShader(ps_4_0, PS_TEX()));
	}
}
