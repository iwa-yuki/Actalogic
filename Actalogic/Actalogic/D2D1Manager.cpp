#include "pch.h"
#include "D2D1Manager.h"

D2D1Manager::D2D1Manager():
m_pDirect2dFactory(nullptr),
m_pDWriteFactory(nullptr),
m_pRenderTarget(nullptr),
m_backgroundColor(D2D1::ColorF(D2D1::ColorF::White))
{
}


D2D1Manager::~D2D1Manager()
{
	assert(!m_pDirect2dFactory);
	assert(!m_pDWriteFactory);
	assert(!m_pRenderTarget);
}

HRESULT D2D1Manager::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);
	if (FAILED(hr)) { return hr; }

	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(m_pDWriteFactory), 
		reinterpret_cast<IUnknown **>(&m_pDWriteFactory));
	if (FAILED(hr)) { return hr; }

	return hr;
}

HRESULT D2D1Manager::CreateDeviceResources(HWND hWnd)
{
	HRESULT hresult = S_OK;

	if (!m_pRenderTarget)
	{
		RECT rc;
		GetClientRect(hWnd, &rc);

		D2D1_SIZE_U size = D2D1::SizeU(
			rc.right - rc.left,
			rc.bottom - rc.top
			);

		// Create a Direct2D render target.
		hresult = m_pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, size),
			&m_pRenderTarget
			);
	}

	return hresult;
}

void D2D1Manager::DiscardDeviceResources()
{
	if (m_pRenderTarget != nullptr) { m_pRenderTarget->Release(); m_pRenderTarget = nullptr; }
}

void D2D1Manager::DiscardAllResources()
{
	DiscardDeviceResources();

	if (m_pDirect2dFactory != nullptr) { m_pDirect2dFactory->Release(); m_pDirect2dFactory = nullptr; }
	if (m_pDWriteFactory != nullptr) { m_pDWriteFactory->Release(); m_pDWriteFactory = nullptr; }
}

///////////////////////////////////////////////////////////////////////////////

void D2D1Manager::BeginDraw()
{
	assert(m_pRenderTarget);

	// 描画開始
	m_pRenderTarget->BeginDraw();
	// レンダーターゲットの変換を単位行列に設定
	m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	// レンダーターゲットを背景色でクリア
	m_pRenderTarget->Clear(m_backgroundColor);
}

HRESULT D2D1Manager::EndDraw()
{
	assert(m_pRenderTarget);

	return m_pRenderTarget->EndDraw();
}
//
//ID2D1Factory* D2D1Manager::GetD2D1Factory()
//{
//	assert(m_pDirect2dFactory);
//
//	return m_pDirect2dFactory;
//}
//
//IDWriteFactory* D2D1Manager::GetDWriteFactory()
//{
//	assert(m_pDWriteFactory);
//
//	return m_pDWriteFactory;
//}
//
//ID2D1HwndRenderTarget* D2D1Manager::GetRenderTarget()
//{
//	assert(m_pRenderTarget);
//
//	return m_pRenderTarget;
//}

void D2D1Manager::GetDesktopDpi(FLOAT *dpiX, FLOAT *dpiY)
{
	m_pDirect2dFactory->GetDesktopDpi(dpiX, dpiY);
}

D2D1_SIZE_F D2D1Manager::GetRenderTargetSize()
{
	return m_pRenderTarget->GetSize();
}

HRESULT D2D1Manager::CreateTextFormat(const TCHAR *fontFamilyName, IDWriteFontCollection *fontCollection,
	DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch,
	FLOAT fontSize, const TCHAR *localeName, IDWriteTextFormat ** textFormat)
{
	return m_pDWriteFactory->CreateTextFormat(fontFamilyName,
		fontCollection,
		fontWeight,
		fontStyle,
		fontStretch,
		fontSize,
		localeName,
		textFormat);
}

HRESULT D2D1Manager::CreateSolidColorBrush(const D2D1_COLOR_F &colorF, ID2D1SolidColorBrush **ppBrush)
{
	return m_pRenderTarget->CreateSolidColorBrush(colorF, ppBrush);
}

void D2D1Manager::DrawText(const TCHAR *text,UINT32 textLength ,IDWriteTextFormat *pTextFormat,
	const D2D1_RECT_F &rc, ID2D1Brush *pBrush)
{
	m_pRenderTarget->DrawText(text, textLength, pTextFormat, rc, pBrush);
}