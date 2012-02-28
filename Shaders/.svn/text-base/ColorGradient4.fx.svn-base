struct VS_TextureOutput
{
	float4 Position : SV_Position;
	float2 TexCoord : TEXCOORD0;
};

float4x4 modelViewProjection;

#define MAXPOINTS	32

float2 pointPos[MAXPOINTS];
float4 pointColor[MAXPOINTS];

int npoints;

VS_TextureOutput VS_Texture(
	float4 vPos : POSITION,
	float2 vTexCoord : TEXCOORD0)
{
	VS_TextureOutput output;

	output.Position = mul(vPos, modelViewProjection);
	output.TexCoord = vTexCoord;

    return output;
}

float4 PS_Texture(VS_TextureOutput In) : SV_Target
{
	float4 color(0,0,0,0);

	int i;
	for (i = 0; i < 4; ++i)
	{	
		float2 delta = In.TexCoord - pointPos[i];
		float2 delta2 = delta*delta;
		color += (1-(delta2.x + delta2.y))*pointColor[i];
	}

	return color;
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
		SetPixelShader(CompileShader( ps_4_0, PS_Texture()));
	}
}
