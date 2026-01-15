#pragma once

#include "DirectX.h"

class Texture
{
public:

	// シェーダーリソースビュー(画像データ読み取りハンドル)
	ComPtr<ID3D11ShaderResourceView> m_srv = nullptr;
	// 画像情報
	DirectX::TexMetadata m_info = {};

	// 画像ファイルを読み込む
	bool Load(const std::string& filename);
};