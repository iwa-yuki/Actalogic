#include "pch.h"
#include "D2D1Manager.h"

D2D1Manager::D2D1Manager():
m_pDirect2dFactory(NULL),
m_pRenderTarget(NULL),
m_backgroundColor(D2D1::ColorF(D2D1::ColorF::White))
{
}


D2D1Manager::~D2D1Manager()
{
	DiscardDeviceResources();

	if (m_pDirect2dFactory != NULL) { m_pDirect2dFactory->Release(); m_pDirect2dFactory = NULL; }
}

HRESULT D2D1Manager::CreateDeviceIndependentResources()
{
	HRESULT hr = S_OK;

	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pDirect2dFactory);

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
	if (m_pRenderTarget != NULL) { m_pRenderTarget->Release(); m_pRenderTarget = NULL; }
}

///////////////////////////////////////////////////////////////////////////////

void D2D1Manager::BeginDraw()
{
	if (m_pRenderTarget)
	{
		// 描画開始
		m_pRenderTarget->BeginDraw();
		// レンダーターゲットの変換を単位行列に設定
		m_pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		// レンダーターゲットを背景色でクリア
		m_pRenderTarget->Clear(m_backgroundColor);
	}
}

HRESULT D2D1Manager::EndDraw()
{
	if (m_pRenderTarget)
	{
		return m_pRenderTarget->EndDraw();
	}

	return E_FAIL;
}

void D2D1Manager::GetDesktopDpi(FLOAT *dpiX, FLOAT *dpiY)
{
	assert(m_pDirect2dFactory != NULL);
	m_pDirect2dFactory->GetDesktopDpi(dpiX, dpiY);
}