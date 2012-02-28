struct VS_OUTPUT
{
	float4 Position : SV_Position;
	float2 TextureUV : TEXCOORD;
};

float4x4 modelViewProjection : WORLDVIEWPROJECTION;
float3x3 textureMatrix0;/* =
{1, 0, 0,
	0, 1, 0,
	0.5, 9, 1};
	*/
float4x4 colorTransform;
float4 colorTranslate;

/*
float3x2 mat = {1, 0,
	0, 1,
	0, 0};
*/

Texture2D<float4> texture0;

SamplerState borderSampler
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Border;
	AddressV = Border;
};

static const int MaxKernelSize = 32*2+1;

int KernelSize;

VS_OUTPUT GaussianBlurVS(float4 vPos : POSITION, float2 vTexCoord : TEXCOORD)
{
	VS_OUTPUT output;
	output.Position = mul(vPos, modelViewProjection);

	output.TextureUV = mul(float3(vTexCoord, 1), textureMatrix0).xy;
	return output;
}

/*
float2 PixelKernel[g_cKernelSize] =
{
    { -6, 0 },
    { -5, 0 },
    { -4, 0 },
    { -3, 0 },
    { -2, 0 },
    { -1, 0 },
    {  0, 0 },
    {  1, 0 },
    {  2, 0 },
    {  3, 0 },
    {  4, 0 },
    {  5, 0 },
    {  6, 0 },
};

float2 PixelKernel_V[MaxKernelSize] =
{
    { 0, -6 },
    { 0, -5 },
    { 0, -4 },
    { 0, -3 },
    { 0, -2 },
    { 0, -1 },
    { 0,  0 },
    { 0,  1 },
    { 0,  2 },
    { 0,  3 },
    { 0,  4 },
    { 0,  5 },
    { 0,  6 },
};
*/

float2 TexelKernel[MaxKernelSize];
/*
<
    string ConvertPixelsToTexels = "PixelKernel";
>;
*/

float BlurWeights[MaxKernelSize];
/*
static const float BlurWeights[MaxKernelSize] = 
{
    0.002216,
    0.008764,
    0.026995,
    0.064759,
    0.120985,
    0.176033,
    0.199471,
    0.176033,
    0.120985,
    0.064759,
    0.026995,
    0.008764,
    0.002216,
};
*/

float4 GaussianBlurPS(VS_OUTPUT In) : SV_Target
{
	float4 color = 0;

	for (int i = 0; i < KernelSize; i++)
	{
		color += texture0.Sample(borderSampler, In.TextureUV + TexelKernel[i]) * BlurWeights[i];
	}

	color = mul(color, colorTransform) + colorTranslate;

	return color;
}

BlendState NoBlending
{
    BlendEnable[0] = FALSE;
};

BlendState AlphaBlend
{
/*
	BlendEnable[0] = TRUE;
    SrcBlend = SRC_ALPHA;
    DestBlend = ONE;
    BlendOp = ADD;
    SrcBlendAlpha = ZERO;
    DestBlendAlpha = ZERO;
    BlendOpAlpha = ADD;
    RenderTargetWriteMask[0] = 0x0F;
*/

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

technique10 RenderFilterGaussianBlurH
{
	pass P0
	{
		SetBlendState(NoBlending, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader(CompileShader( vs_4_0, GaussianBlurVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, GaussianBlurPS()));
	}
}

technique10 RenderFilterGaussianBlurV
{
	pass P0
	{
		SetBlendState(AlphaBlend, float4(0.0f, 0.0f, 0.0f, 0.0f), 0xFFFFFFFF);

		SetVertexShader(CompileShader(vs_4_0, GaussianBlurVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_4_0, GaussianBlurPS()));
	}
}

/*
technique10 GaussianBlurTechnique
{
	pass P0
	{       
		SetVertexShader(CompileShader( vs_4_0, GaussianBlurVS()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader( ps_4_0, GaussinBlurPS()));
	}
}
*/