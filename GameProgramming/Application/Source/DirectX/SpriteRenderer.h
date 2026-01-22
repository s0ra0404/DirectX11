#include "DirectX.h"

class Texture;

class SpriteRenderer
{
public:
	void ChangeMode_2D(Direct3D* d3d);
	// tex		: テクスチャ
	// x		: x座標
	// y		: y座標
	// w		: 幅
	// h		: 高さ
	void Draw(Direct3D* d3d, const Texture& tex, float x, float y, float w, float h);

private:
	Shader& shader;
	ComPtr<ID3D11Buffer>& m_vbSquare = nullptr;
};