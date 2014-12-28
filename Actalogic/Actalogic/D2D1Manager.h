#pragma once
#include "pch.h"

class D2D1Manager
{
public:
	D2D1Manager();
	~D2D1Manager();

	// デバイス非依存のリソースを作成する
	// (開放はこのインスタンスが破棄されるとき自動で行われる)
	HRESULT CreateDeviceIndependentResources();

	// デバイス依存のリソースを作成する
	HRESULT CreateDeviceResources(HWND hWnd);

	// デバイス依存のリソースを開放する
	void DiscardDeviceResources();

public:
	// 描画開始
	void BeginDraw();

	// 描画終了
	HRESULT EndDraw();

	// Direct2DFactoryを取得
	ID2D1Factory* GetD2D1Factory();

	// DirectWriteFactoryを取得
	IDWriteFactory* GetDWriteFactory();

	// RenderTargetを取得
	ID2D1HwndRenderTarget* GetRenderTarget();

private:
	ID2D1Factory* m_pDirect2dFactory;
	IDWriteFactory* m_pDWriteFactory;

	ID2D1HwndRenderTarget* m_pRenderTarget;

	D2D1_COLOR_F m_backgroundColor;
};

