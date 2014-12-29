#pragma once
#include "pch.h"

class D2D1Manager
{
public:
	D2D1Manager();
	~D2D1Manager();

	// デバイス非依存のリソースを作成する
	HRESULT CreateDeviceIndependentResources();

	// デバイス依存のリソースを作成する
	HRESULT CreateDeviceResources(HWND hWnd);

	// デバイス依存のリソースを開放する
	void DiscardDeviceResources();

	// リソースをすべて開放する
	void DiscardAllResources();

public:
	// 描画開始
	void BeginDraw();

	// 描画終了
	HRESULT EndDraw();

	//// Direct2DFactoryを取得
	//ID2D1Factory* GetD2D1Factory();

	//// DirectWriteFactoryを取得
	//IDWriteFactory* GetDWriteFactory();

	//// RenderTargetを取得
	//ID2D1HwndRenderTarget* GetRenderTarget();

	// デスクトップDPIを取得
	void GetDesktopDpi(FLOAT *dpiX, FLOAT *dpiY);

	// レンダーターゲットのサイズを取得
	D2D1_SIZE_F GetRenderTargetSize();

	// DirectWriteテキストフォーマットを作成
	HRESULT CreateTextFormat(const TCHAR *fontFamilyName, IDWriteFontCollection *fontCollection,
		DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize, const TCHAR *localeName, IDWriteTextFormat ** textFormat);

	// SolidColorBrushを作成
	HRESULT CreateSolidColorBrush(const D2D1_COLOR_F &colorF, ID2D1SolidColorBrush **ppBrush);

	// テキストを描画
	void DrawText(const TCHAR *text, UINT32 textLength, IDWriteTextFormat *pTextFormat,
		const D2D1_RECT_F &rc, ID2D1Brush *pBrush);

	// 画像ファイルをロード
	HRESULT LoadBitmapFromFile(LPTSTR uri, ID2D1Bitmap **ppBitmap);

	// 画像を描画
	void DrawBitmap(ID2D1Bitmap *pBitmap, const D2D1_RECT_F &destRect,
		FLOAT opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F &srcRect);

private:
	ID2D1Factory* m_pDirect2dFactory;
	IDWriteFactory* m_pDWriteFactory;
	IWICImagingFactory* m_pIWICFactory;

	ID2D1HwndRenderTarget* m_pRenderTarget;

	D2D1_COLOR_F m_backgroundColor;
};

