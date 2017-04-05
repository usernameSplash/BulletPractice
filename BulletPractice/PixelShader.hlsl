struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float2 tex: TEXCOORD0;
};

Texture2D image;
SamplerState state;

float4 main(PixelShaderInput input) : SV_TARGET
{
	float4 t = image.Sample(state, input.tex);
	clip(t.w - 0.05f);
	return t;
}