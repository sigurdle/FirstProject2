struct VS_TextureOutput
{
	float4 Position : SV_Position;
	float2 TextureUV : TEXCOORD0;
};

struct VS_ColorOutput
{
	float4 Position : SV_Position;
	float4 Color : COLOR0;
};

float4x4 modelView : MODELVIEW;
float4x4 modelViewProjection;

float4x4 colorTransform;
float4 colorTranslate;

float4 colorMultiply;

Texture2D<float4> textureC;

Texture2D<float4> texture0;
float4x4 textureMatrix0;

SamplerState TextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	//BorderColor = 0;
	AddressU = Border;
	AddressV = Border;
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

VS_TextureOutput VS_Texture(
	float4 vPos : POSITION,
	float2 vTexCoord0 : TEXCOORD0)
{
	VS_TextureOutput output;

//	float4 pos = mul(vPos, modelView);
//	float4 pos = mul(vPos, modelViewProjection);

	//float4 texcoord = float4(vTexCoord0.x, vTexCoord0.y, 0, 0);

	output.Position = mul(vPos, modelViewProjection);
	output.TextureUV = mul(vTexCoord0, (float3x3)textureMatrix0).xy;
//	output.TextureUV = vTexCoord0;//, (float3x3)textureMatrix0).xy;

    return output;
}

float4 PS_Texture(VS_TextureOutput In) : SV_Target
{
	return texture0.Sample(TextureSampler, In.TextureUV) * colorMultiply + colorTranslate;
}

float4 PS_TextureColorTransform(VS_TextureOutput In) : SV_Target
{
	float4 color = texture0.Sample(TextureSampler, In.TextureUV);
	color = mul(color, colorTransform) + colorTranslate;
	return color;
}

float4 PS_Normal(VS_TextureOutput In) : SV_Target
{
/*
Er, Eg, Eb    - Element color value
Ea            - Element alpha value
Cr, Cg, Cb    - Canvas color value (before blending)
Ca            - Canvas alpha value (before blending)
Cr', Cg', Cb' - Canvas color value (after blending)
Ca'           - Canvas alpha value (after blending)
Ca' = 1 - (1 - Ea) * (1 - Ca)
Cr' = (1 - Ea) * Cr + Er
Cg' = (1 - Ea) * Cg + Eg
Cb' = (1 - Ea) * Cb + Eb
*/
	float2 screenpos = In.Position.xy;

	float4 C = textureC.Sample(TextureSampler, screenpos);
	float4 E = texture0.Sample(TextureSampler, In.TextureUV);
//	E = mul(E, colorTransform) + colorTranslate;

	float inv_Ea = 1 - E.a;

	float Ca_ = 1 - inv_Ea * (1 - C.a);
	float Cr_ = inv_Ea * C.r + E.r;
	float Cg_ = inv_Ea * C.g + E.g;
	float Cb_ = inv_Ea * C.b + E.b;

	return float4(Cr_, Cg_, Cb_, Ca_);
}

BlendState NoBlending
{
    BlendEnable[0] = FALSE;
};

BlendState AlphaBlend
{
/*
Er, Eg, Eb    - Element color value
Ea            - Element alpha value
Cr, Cg, Cb    - Canvas color value (before blending)
Ca            - Canvas alpha value (before blending)
Cr', Cg', Cb' - Canvas color value (after blending)
Ca'           - Canvas alpha value (after blending)
Ca' = 1 - (1 - Ea) * (1 - Ca)
Cr' = (1 - Ea) * Cr + Er
Cg' = (1 - Ea) * Cg + Eg
Cb' = (1 - Ea) * Cb + Eb
*/

	BlendEnable[0] = TRUE;

	SrcBlend = SRC_ALPHA;
	DestBlend = INV_SRC_ALPHA;
	BlendOp = ADD;

	SrcBlendAlpha = ONE;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;

	RenderTargetWriteMask[0] = 0x0F;
};

technique10 RenderTexture
{
	pass P0
	{
		SetBlendState(AlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	
		SetVertexShader(CompileShader( vs_4_0, VS_Texture()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, PS_Normal()));
	}
}

technique10 RenderTextureColorTransform
{
	pass P0
	{
		SetBlendState(AlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	
		SetVertexShader(CompileShader( vs_4_0, VS_Texture()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, PS_TextureColorTransform()));
	}
}

technique10 SolidColorTechnique
{
	pass P0
	{
		SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	
		SetVertexShader(CompileShader( vs_4_0, VS_Color()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, PS_Color()));
	}
}
