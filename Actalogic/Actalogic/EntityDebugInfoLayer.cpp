#include "pch.h"
#include "EntityDebugInfoLayer.h"
#include "ActalogicApp.h"

EntityDebugInfoLayer::EntityDebugInfoLayer():
m_pDWTextFormat(nullptr),
m_pTextBrush(nullptr)
{
}


EntityDebugInfoLayer::~EntityDebugInfoLayer()
{
	OnDiscardDeviceResources();
	OnDiscardDeviceIndependentResources();
}

HRESULT EntityDebugInfoLayer::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return pD2D1Manager->GetDWriteFactory()->CreateTextFormat(_T("MS UI Gothic"),
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12.0F,
		_T(""),
		&m_pDWTextFormat);
}

HRESULT EntityDebugInfoLayer::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	return pD2D1Manager->GetRenderTarget()->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pTextBrush);
}

void EntityDebugInfoLayer::OnDiscardDeviceResources()
{
	if (m_pTextBrush != nullptr) { m_pTextBrush->Release(); m_pTextBrush = nullptr; }
}

void EntityDebugInfoLayer::OnDiscardDeviceIndependentResources()
{
	if (m_pDWTextFormat != nullptr) { m_pDWTextFormat->Release(); m_pDWTextFormat = nullptr; }
}

void EntityDebugInfoLayer::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTarget()->GetSize();
	TCHAR c[1024];
	float fps = (m_theApp->m_entityFPS).GetFPS();
	int nc = _stprintf_s(c, 1024, _T("FPS = %.2f"), fps);
	
	pD2D1Manager->GetRenderTarget()->DrawText(c, nc,
		m_pDWTextFormat, D2D1::RectF(0, 0, targetSize.width, targetSize.height), m_pTextBrush);
}

void EntityDebugInfoLayer::SetApp(ActalogicApp *pApp)
{
	m_theApp = pApp;
}