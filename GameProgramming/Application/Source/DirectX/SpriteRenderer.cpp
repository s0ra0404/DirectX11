#include "SpriteRenderer.h"

void SpriteRenderer::ChangeMode_2D(Direct3D* d3d)
{
	ID3D11Device* m_device = d3d->m_device.Get();
	ID3D11DeviceContext* m_deviceContext = d3d->m_deviceContext.Get();

	shader.Bind(m_deviceContext);

	// 四角形用 頂点バッファ作成(初回のみ)
	if (m_vbSquare == nullptr)
	{
		D3D11_BUFFER_DESC vbDesc = {};
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	// デバイスにバインドするときの種類(頂点バッファ、インデックスバッファ、定数バッファなど)
		vbDesc.ByteWidth = sizeof(VertexType2D) * 4;	// 作成するバッファのバイトサイズ
		vbDesc.MiscFlags = 0;							// その他のフラグ
		vbDesc.StructureByteStride = 0;					// 構造化バッファの場合、その構造体のサイズ

		vbDesc.Usage = D3D11_USAGE_DYNAMIC;				// 作成するバッファの使用法
		vbDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		m_device->CreateBuffer(&vbDesc, nullptr, &m_vbSquare);
	}

	// 頂点バッファを描画で使えるようにセットする
	UINT stride = sizeof(VertexType2D);
	UINT offset = 0;
	m_deviceContext->IASetVertexBuffers(0, 1, m_vbSquare.GetAddressOf(), &stride, &offset);
	// プロミティブ・トポロジーをセット
	m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// サンプラーステートを作成しセットする
	{
		// 異方性フィルタリング補間、Wrapモード
		D3D11_SAMPLER_DESC desc = {};
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// 線形フィルタリング
		desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		// テクスチャアドレッシングモードをWrapに
		desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;		// テクスチャアドレッシングモードをWrapに
		desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;		// テクスチャアドレッシングモードをWrapに
		desc.MipLODBias = 0;
		desc.MaxAnisotropy = 0;
		desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		desc.BorderColor[0] = desc.BorderColor[1] = desc.BorderColor[2] = desc.BorderColor[3] = 0;
		desc.MinLOD = 0;
		desc.MaxLOD = D3D11_FLOAT32_MAX;

		// ステートオブジェクト作成
		ComPtr<ID3D11SamplerState> state;
		m_device->CreateSamplerState(&desc, &state);

		// 各シェーダーの0番目にセット(実際は必要なシェーダーだけセットしてください)
		m_deviceContext->VSSetSamplers(0, 1, state.GetAddressOf()); // 頂点シェーダーの0番目にセット
		m_deviceContext->PSSetSamplers(0, 1, state.GetAddressOf()); // ピクセルシェーダーの0番目にセット
		m_deviceContext->GSSetSamplers(0, 1, state.GetAddressOf()); // ジオメトリシェーダーの0番目にセット
		m_deviceContext->CSSetSamplers(0, 1, state.GetAddressOf()); // コンピュートシェーダーの0番目にセット
	}
}




void SpriteRenderer::Draw(Direct3D* d3d, const Texture& tex, float x, float y, float w, float h)
{
	ID3D11DeviceContext* m_deviceContext = d3d->m_deviceContext.Get();

	float hW = w * 0.5f;
	float hH = h * 0.5f;

	// 頂点データ作成
	VertexType2D v[4] = {
		{{x - hW, y - hH, 0}, {0, 1}},	// 左下
		{{x - hW, y + hH, 0}, {0, 0}},	// 左上
		{{x + hW, y - hH, 0}, {1, 1}},	// 右下
		{{x + hW, y + hH, 0}, {1, 0}},	// 右上
	};

	// 頂点バッファにデータを書き込む
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED(m_deviceContext->Map(m_vbSquare.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		// データコピー
		memcpy_s(pData.pData, sizeof(v), &v[0], sizeof(v));

		m_deviceContext->Unmap(m_vbSquare.Get(), 0);
	}

	// テクスチャを、スロット0にセット
	m_deviceContext->PSSetShaderResources(0, 1, tex.m_srv.GetAddressOf());

	// デバイスコンテキストくん、上記のセットした内容で描画してください
	m_deviceContext->Draw(4, 0);
}