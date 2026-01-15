#include "framework.h"

#include <locale.h>

#include "Texture.h"
#include "Direct3D.h"
#include <memory>


bool Texture::Load(const std::string& filename)
{
	// マルチバイト文字列からワイド文字列へ変換
	setlocale(LC_CTYPE, "jpn");
	wchar_t wFilename[256];
	size_t ret;
	mbstowcs_s(&ret, wFilename, filename.c_str(), 256);

	// WIC画像を読み込む
	auto image = std::make_unique<DirectX::ScratchImage>();
	if (FAILED(DirectX::LoadFromWICFile(wFilename, DirectX::WIC_FLAGS_NONE, &m_info, *image)))
	{
		// 失敗
		m_info = {};
		return false;
	}

	// ミップマップの生成
	if (m_info.mipLevels == 1)
	{
		auto mipChain = std::make_unique<DirectX::ScratchImage>();
		if (SUCCEEDED(DirectX::GenerateMipMaps(image->GetImages(), image->GetImageCount(), image->GetMetadata(), DirectX::TEX_FILTER_DEFAULT, 0, *mipChain)))
		{
			image = std::move(mipChain);
		}
	}

	// リソースとシェーダーリソースビューを作成
	if (FAILED(DirectX::CreateShaderResourceView(D3D.m_device.Get(), image->GetImages(), image->GetImageCount(), m_info, &m_srv)))
	{
		// 失敗
		m_info = {};
		return false;
	}

	// 成功！
	return true;
}