#pragma once

#include "Direct3D.h"
#include <string.h>

class Shader
{
public:

	// シェーダのコンパイル
	bool Load(ID3D11Device* device,
        const std::wstring& path,
        const std::string& vsEntry,
        const std::string& psEntry);

	// デバイスコンテキストにセット
    void Bind(ID3D11DeviceContext* context);

private:
	// 2D描画用のシェーダー
	ComPtr<ID3D11VertexShader> m_spriteVS = nullptr;	      // 頂点シェーダー
	ComPtr<ID3D11PixelShader>  m_spritePS = nullptr;	      // ピクセルシェーダー
	ComPtr<ID3D11InputLayout>  m_spriteInputLayout = nullptr; // 入力レイアウト
};

