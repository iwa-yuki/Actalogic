#include "pch.h"
#include "D2D1Manager.h"

D2D1Manager::D2D1Manager():
m_pDirect2dFactory(nullptr),
m_pDWriteFactory(nullptr),
m_pIWICFactory(nullptr),
m_pRenderTarget(nullptr),
m_backgroundColor(D2D1::ColorF(D2D1::ColorF::White))
{
}


D2D1Manager::~D2D1Manager()
{
	assert(!m_pDirect2dFactory);
	assert(!m_pDWriteFactory);
	assert(!m_pIWICFactory);
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

	hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory, (LPVOID*)&m_pIWICFactory);
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
	if (m_pIWICFactory != nullptr) { m_pIWICFactory->Release(); m_pIWICFactory = nullptr; }
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

HRESULT D2D1Manager::CreatePathGeometry(ID2D1PathGeometry **ppGeometry)
{
	return m_pDirect2dFactory->CreatePathGeometry(ppGeometry);
}

void D2D1Manager::DrawText(const TCHAR *text,UINT32 textLength ,IDWriteTextFormat *pTextFormat,
	const D2D1_RECT_F &rc, ID2D1Brush *pBrush)
{
	m_pRenderTarget->DrawText(text, textLength, pTextFormat, rc, pBrush);
}

HRESULT D2D1Manager::LoadBitmapFromFile(LPTSTR uri, ID2D1Bitmap **ppBitmap)
{
	IWICBitmapDecoder *pDecoder = nullptr;
	IWICBitmapFrameDecode *pSource = nullptr;
	IWICStream *pStream = nullptr;
	IWICFormatConverter *pConverter = nullptr;
	IWICBitmapScaler *pScaler = nullptr;

	HRESULT hr = m_pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
		);

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
			);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
			);
	}

	if (pDecoder != nullptr){ pDecoder->Release(); }
	if (pSource != nullptr){ pSource->Release(); }
	if (pStream != nullptr){ pStream->Release(); }
	if (pConverter != nullptr){ pConverter->Release(); }
	if (pScaler != nullptr){ pScaler->Release(); }

	return hr;
}

void D2D1Manager::DrawBitmap(ID2D1Bitmap *pBitmap, const D2D1_RECT_F &destRect,
	FLOAT opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F &srcRect)
{
	m_pRenderTarget->DrawBitmap(pBitmap, destRect, opacity, interpolationMode, srcRect);
}


void D2D1Manager::DrawLine(D2D1_POINT_2F point0, D2D1_POINT_2F point1, ID2D1Brush *pBrush, FLOAT width)
{
	m_pRenderTarget->DrawLine(point0, point1, pBrush, width);
}

void D2D1Manager::DrawRectangle(const D2D1_RECT_F &rc, ID2D1Brush *pBrush, FLOAT width)
{
	m_pRenderTarget->DrawRectangle(rc, pBrush, width);
}

