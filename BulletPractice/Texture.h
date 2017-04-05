#pragma once
#include <D3D11.h>
#include <D3DX11.h>

class Texture
{
public:
	Texture(ID3D11Device* device, LPCWSTR imagePath);
	~Texture();

	void bind(ID3D11DeviceContext* deviceContext);
private:
	ID3D11ShaderResourceView* m_Texture;
	ID3D11SamplerState* m_State;
};
