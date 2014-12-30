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
	assert(!m_pDWTextFormat);
	assert(!m_pTextBrush);
}

HRESULT EntityDebugInfoLayer::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return pD2D1Manager->CreateTextFormat(_T("MS UI Gothic"),
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
	HRESULT hresult = S_OK;
	if (!m_pTextBrush)
	{
		hresult = pD2D1Manager->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pTextBrush);
	}
	return hresult;
}

void EntityDebugInfoLayer::OnDiscardDeviceResources()
{
	if (m_pTextBrush != nullptr) { m_pTextBrush->Release(); m_pTextBrush = nullptr; }
}

void EntityDebugInfoLayer::OnDiscardAllResources()
{
	OnDiscardDeviceResources();

	if (m_pDWTextFormat != nullptr) { m_pDWTextFormat->Release(); m_pDWTextFormat = nullptr; }
}

void EntityDebugInfoLayer::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();
	TCHAR c[1024];
	float fps = (m_theApp->m_entityFPS).GetFPS();
	int keyEscape = (m_theApp->m_inputHelper).GetKeyState(InputHelper::INPUT_ESCAPE) ? 1 : 0;
	int keySelect = (m_theApp->m_inputHelper).GetKeyState(InputHelper::INPUT_SELECT) ? 1 : 0;
	int keyUp = (m_theApp->m_inputHelper).GetKeyState(InputHelper::INPUT_UP) ? 1 : 0;
	int keyDown = (m_theApp->m_inputHelper).GetKeyState(InputHelper::INPUT_DOWN) ? 1 : 0;
	int keyRight = (m_theApp->m_inputHelper).GetKeyState(InputHelper::INPUT_RIGHT) ? 1 : 0;
	int keyLeft = (m_theApp->m_inputHelper).GetKeyState(InputHelper::INPUT_LEFT) ? 1 : 0;

	int nc = _stprintf_s(c, 1024, _T("FPS = %.2f\nKey.escape = %d, Key.select = %d, Key.up = %d, Key.down = %d, Key.right = %d, Key.left = %d"), fps, keyEscape, keySelect, keyUp, keyDown, keyRight, keyLeft);
	
	pD2D1Manager->DrawText(c, nc,
		m_pDWTextFormat, D2D1::RectF(0, 0, targetSize.width, targetSize.height), m_pTextBrush);
}

void EntityDebugInfoLayer::SetApp(ActalogicApp *pApp)
{
	m_theApp = pApp;
}