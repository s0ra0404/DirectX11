#include "framework.h"
// GameSystemクラスを使えるようにする
#include "GameSystem.h"
// Direct3Dクラスを使えるようにする
#include "Source/DirectX/DirectX.h"

SpriteRenderer spriteRenderer;

// ゲームの初期設定を行う
void GameSystem::Initialize()
{
	m_tex.Load("Resource/Mask_1.png");
}

// このゲームの時間を進める(処理を実行する)
void GameSystem::Execute()
{
    // 画面を青色で塗りつぶす
    float color[4] = { 0.2f, 0.2f, 1.0f, 1.0f };
    D3D.m_deviceContext->ClearRenderTargetView(D3D.m_backBufferView.Get(), color);

	Direct3D d3d = D3D.GetInstance();

		// 三角形の描画
	{
		spriteRenderer.ChangeMode_2D(&d3d);
		spriteRenderer.Draw(&d3d, m_tex, 0, 0, 1, 1);
	}

	// バックバッファの内容を画面に表示
	D3D.m_swapChain->Present(1, 0);
}