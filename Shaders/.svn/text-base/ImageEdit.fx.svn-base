//float4x4 modelView;				// World * View matrix
//float4x4 projection;			// Projection matrix
float4x4 modelViewProjection;	// World * View * Projection matrix
//float4x4 textureMatrix0;		// : TEXTUREMATRIX;

float4x4 texture0Matrix;		// : TEXTUREMATRIX;
float2 texture1Translate;		// : TEXTUREMATRIX;

struct POS4_T2_T2
{
	float4 Position : SV_Position;   // vertex position
	float2 TextureUV[2] : TEXCOORD0;  // vertex texture coords
};

POS4_T2_T2 SelectionOutlineVS(
				float4 vPos : POSITION,
				float2 vTexCoord0 : TEXCOORD0,
				float2 vTexCoord1 : TEXCOORD1)
{
	POS4_T2_T2 output;

/*
	if (false)
	{
		float4 pos = mul(vPos, modelView);
		pos.x = floor(pos.x) - 0.5;
		pos.y = floor(pos.y) - 0.5;
		output.Position =  mul(pos, projection);
	}
	else
	*/
	{
		output.Position = mul(vPos, modelViewProjection);
	}

/*
	float4 texcoord = float4(vTexCoord0.x, vTexCoord0.y, 0, 1);

//	output.TextureUV = mul(vTexCoord0, textureMatrix0).xy;
	output.TextureUV = mul(texcoord, textureMatrix0).xy;
*/

	output.TextureUV[0] = vTexCoord0;
	output.TextureUV[1] = vTexCoord1 + texture1Translate;

	return output;
}

float3 texelsPerPixel;

SamplerState BorderSampler
{
	Filter = MIN_MAG_MIP_POINT;

	BorderColor = float4(0,0,0,0);
	
	AddressU = BORDER;
	AddressV = BORDER;
};

SamplerState WrapSampler
{
	Filter = MIN_MAG_MIP_POINT;

	AddressU = WRAP;
	AddressV = WRAP;
};

Texture2D texture0;
Texture2D texture1;

float4 SelectionOutlinePS(POS4_T2_T2 In) : SV_Target
{
	float4 pattern = texture1.Sample(WrapSampler, In.TextureUV[1]);

	float2 uv = In.TextureUV[0];

	float4 tex0 = texture0.Sample(BorderSampler, uv);

//	return tex0;

	float4 tex1 = texture0.Sample(BorderSampler, uv+texelsPerPixel.xz);
	float4 tex2 = texture0.Sample(BorderSampler, uv-texelsPerPixel.xz);
	float4 tex3 = texture0.Sample(BorderSampler, uv+texelsPerPixel.zy);
	float4 tex4 = texture0.Sample(BorderSampler, uv-texelsPerPixel.zy);

// Contrast, below 0.5 -> 0, above 0.5 -> 1
	tex0 = round(tex0);
	tex1 = round(tex1);
	tex2 = round(tex2);
	tex3 = round(tex3);
	tex4 = round(tex4);

	float4 color = min(1, tex0 + tex1 + tex2 + tex3 + tex4);

	float4 diff = color-tex0;

//	return pattern;

	if (diff[3] < 0.5)
	{
		discard;
	}

	return pattern;
}

BlendState NoBlending
{
    BlendEnable[0] = FALSE;
};

technique10 RenderSelection
{
	pass P0
	{
		SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	
		SetVertexShader(CompileShader( vs_4_0, SelectionOutlineVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, SelectionOutlinePS()));
	}
}
