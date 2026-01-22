#include "Shader.h"
#include <vector>

bool Shader::Load(ID3D11Device* device,
	const std::wstring& path,
	const std::string& vsEntry,
	const std::string& psEntry)
{
	//=====================================================
	// シェーダーの作成
	//=====================================================

	// 頂点シェーダーを読み込み＆コンパイル
	ComPtr<ID3DBlob> compiledVS;
	if (FAILED(D3DCompileFromFile(path.c_str(), nullptr, nullptr, vsEntry.c_str(), "vs_5_0", 0, 0, &compiledVS, nullptr)))
	{
		return false;
	}
	// ピクセルシェーダーを読み込み＆コンパイル
	ComPtr<ID3DBlob> compiledPS;
	if (FAILED(D3DCompileFromFile(path.c_str(), nullptr, nullptr, psEntry.c_str(), "ps_5_0", 0, 0, &compiledPS, nullptr)))
	{
		return false;
	}


	// 頂点シェーダー作成
	if (FAILED(device->CreateVertexShader(compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), nullptr, &m_spriteVS)))
	{
		return false;
	}
	// ピクセルシェーダー作成
	if (FAILED(device->CreatePixelShader(compiledPS->GetBufferPointer(), compiledPS->GetBufferSize(), nullptr, &m_spritePS)))
	{
		return false;
	}

	// １頂点の詳細な情報
	std::vector<D3D11_INPUT_ELEMENT_DESC> layout = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,		0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0,  12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	// 頂点インプットレイアウト作成
	if (FAILED(device->CreateInputLayout(&layout[0], layout.size(), compiledVS->GetBufferPointer(), compiledVS->GetBufferSize(), &m_spriteInputLayout)))
	{
		return false;
	}

	return true;
}

void Shader::Bind(ID3D11DeviceContext* deviceContext)
{
	// 2D用頂点シェーダーセット
	deviceContext->VSSetShader(m_spriteVS.Get(), 0, 0);
	// 2D用ピクセルシェーダーセット
	deviceContext->PSSetShader(m_spritePS.Get(), 0, 0);
	// 入力レイアウトセット
	deviceContext->IASetInputLayout(m_spriteInputLayout.Get());
}
