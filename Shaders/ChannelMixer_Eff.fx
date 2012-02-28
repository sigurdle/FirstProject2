float red[3];
float green[3];
float blue[3];
bool monochrome;

float4 PS_Texture(VS_TextureOutput In) : SV_Target
{
	float3 color = texture0.Sample(TextureSampler, In.TextureUV);

	if (monochrome)
	{
		float gray = color.r * red[0] + color.g * green[0] + color.b * blue[0];

		return float3(gray, gray, gray);
	}
	else
	{
		float3 color2;
		color2.r = color.r * red[0] + color.g * green[0] + color.b * blue[0];
		color2.g = color.r * red[1] + color.g * green[1] + color.b * blue[1];
		color2.b = color.r * red[2] + color.g * green[2] + color.b * blue[2];

		return color2;
	}
}
