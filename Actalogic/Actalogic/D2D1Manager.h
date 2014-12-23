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

	// デバイス非依存のリソースを開放する
	void DiscardDeviceResources();

public:
	// 描画開始
	void BeginDraw();

	// 描画終了
	HRESULT EndDraw();

	// デスクトップのDPIを取得
	void GetDesktopDpi(FLOAT *dpiX, FLOAT *dpiY);

private:
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	D2D1_COLOR_F m_backgroundColor;
};

