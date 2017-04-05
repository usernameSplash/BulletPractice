cbuffer MatrixBuffer
{
	float4x4 worldOrthoMatrix;
}

struct VerTexShaderInput
{
	float4 position : POSITION;
	float2 tex: TEXCOORD0;
};

struct PixelShaderInput
{
	float4 position : SV_POSITION;
	float2 tex: TEXCOORD0;
};


PixelShaderInput main(VerTexShaderInput input)
{
	PixelShaderInput output;

	output.position = mul(input.position, worldOrthoMatrix);
	output.tex = input.tex;

	return output;

}