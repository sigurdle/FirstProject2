struct VS_TextureOutput
{
	float4 Position : SV_Position;
	float2 TextureUV[2] : TEXCOORD0;
};

float4x4 modelView : MODELVIEW;
float4x4 modelViewProjection;

float4x4 colorTransform;
float4 colorTranslate;

float4 colorMultiply;

Texture2D texture0;
Texture2D texture1;

float4x4 textureMatrix0;
float4x4 textureMatrix1;

SamplerState TextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	//BorderColor = 0;
	AddressU = Border;
	AddressV = Border;
};

SamplerState MaskTextureSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	//BorderColor = 0;
	AddressU = Clamp;
	AddressV = Clamp;
};

VS_TextureOutput VS_Texture(
	float4 vPos : POSITION,
	float2 vTexCoord0 : TEXCOORD0
)
{
	VS_TextureOutput output;

	output.Position = mul(vPos, modelViewProjection);
	output.TextureUV[0] = vTexCoord0;
	output.TextureUV[1] = mul(float3(vTexCoord0, 1), (float3x3)textureMatrix1).xy;

    return output;
}

float4 PS_Texture(VS_TextureOutput In) : SV_Target
{
	float4 color = texture0.Sample(TextureSampler, In.TextureUV[0]) * colorMultiply + colorTranslate;
	return color;
}

float4 PS_TextureMask(VS_TextureOutput In) : SV_Target
{
	float4 color = texture0.Sample(TextureSampler, In.TextureUV[0]) * colorMultiply + colorTranslate;
	float4 mask = texture1.Sample(MaskTextureSampler, In.TextureUV[1]);

	/*
//	float2 scale = float2(1.0/400.0, 1.0/400.0);

	float2 screenpos = In.Position.xy;
	float2 maskpos = mul(In.TextureUV[1], screenpos);
	In.TextureUV[1]

	float4 mask = texture1.Sample(TextureSampler, maskpos);
	*/

	return color * mask;
}

/*
float4 PS_TextureColorTransform(VS_TextureOutput In) : SV_Target
{
	float4 color = texture0.Sample(TextureSampler, In.TextureUV);
	color = mul(color, colorTransform) + colorTranslate;
	return color;
}
*/

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

	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ONE;
	BlendOpAlpha = ADD;

	SrcBlendAlpha = ZERO;
	DestBlendAlpha = ONE;
	BlendOpAlpha = ADD;

/*
	SrcBlendAlpha = ONE;
	DestBlendAlpha = ZERO;
	BlendOpAlpha = ADD;
*/
	RenderTargetWriteMask[0] = 0x0F;
};

technique10 RenderTexture
{
	pass P0
	{
		SetBlendState(AlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);
	
		SetVertexShader(CompileShader( vs_4_0, VS_Texture()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, PS_TextureMask()));
	}
}

/*
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
*/