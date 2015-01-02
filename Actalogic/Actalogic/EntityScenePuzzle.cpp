#include "pch.h"
#include "EntityScenePuzzle.h"
#include "EntitySceneContainer.h"

EntityScenePuzzle::EntityScenePuzzle() :
m_pContainer(nullptr),
m_pBitmapBackground(nullptr),
m_pSolidBrush(nullptr),
m_currentCursor({0, 0}),
m_keyInputCounter(0)
{
}

EntityScenePuzzle::EntityScenePuzzle(EntitySceneContainer *pContainer) :
m_pContainer(pContainer),
m_pBitmapBackground(nullptr),
m_pSolidBrush(nullptr),
m_currentCursor({ 0, 0 }),
m_keyInputCounter(0)
{
}


EntityScenePuzzle::~EntityScenePuzzle()
{
	assert(!m_pBitmapBackground);
	assert(!m_pSolidBrush);
}

HRESULT EntityScenePuzzle::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return S_OK;
}

HRESULT EntityScenePuzzle::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	if (m_pBitmapBackground == nullptr)
	{
		hresult = pD2D1Manager->LoadBitmapFromFile(_T("image\\game_back.png"), &m_pBitmapBackground);
	}
	if (FAILED(hresult)){ return hresult; }

	if (m_pSolidBrush == nullptr)
	{
		hresult = pD2D1Manager->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pSolidBrush);
	}

	return S_OK;
}

void EntityScenePuzzle::OnDiscardDeviceResources()
{
	if (m_pBitmapBackground != nullptr) { m_pBitmapBackground->Release(); m_pBitmapBackground = nullptr; }
	if (m_pSolidBrush != nullptr) { m_pSolidBrush->Release(); m_pSolidBrush = nullptr; }
}

void EntityScenePuzzle::OnDiscardAllResources()
{
	OnDiscardDeviceResources();
}

void EntityScenePuzzle::OnPreRender(InputHelper *pInputHelper)
{
	bool isKeyDown = false;
	if (pInputHelper->GetKeyState(InputHelper::INPUT_ESCAPE))
	{
		m_pContainer->SetMenu();
		isKeyDown = true;
	}

	if (pInputHelper->GetKeyState(InputHelper::INPUT_UP))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.y = m_currentCursor.y > 0 ? m_currentCursor.y - 1 : m_currentCursor.y;
		}
		isKeyDown = true;
	}
	else if (pInputHelper->GetKeyState(InputHelper::INPUT_DOWN))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.y = m_currentCursor.y < 19 ? m_currentCursor.y + 1 : m_currentCursor.y;
		}
		isKeyDown = true;
	}

	if (pInputHelper->GetKeyState(InputHelper::INPUT_LEFT))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.x = m_currentCursor.x > 0 ? m_currentCursor.x - 1 : m_currentCursor.x;
		}
		isKeyDown = true;
	}
	else if (pInputHelper->GetKeyState(InputHelper::INPUT_RIGHT))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.x = m_currentCursor.x < 19 ? m_currentCursor.x + 1 : m_currentCursor.x;
		}
		isKeyDown = true;
	}
	
	if (isKeyDown)
	{
		m_keyInputCounter++;
	}
	else
	{
		m_keyInputCounter = 0;
	}
}

void EntityScenePuzzle::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();

	pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height), 1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height));

	// Œrü‚ð•`‰æ
	m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
	for (int i = 0; i <= 20; ++i)
	{
		pD2D1Manager->DrawLine(D2D1::Point2F(100.0F, i*30.0F), D2D1::Point2F(targetSize.width - 100.0F, i*30.0F), m_pSolidBrush);
	}
	for (int i = 0; i <= 20; ++i)
	{
		pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + i*30.0F, 0.0F), D2D1::Point2F(100.0F + i*30.0F, targetSize.height), m_pSolidBrush);
	}

	// ƒJ[ƒ\ƒ‹‚ð•`‰æ
	m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
	pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + m_currentCursor.x * 30.0F, m_currentCursor.y*30.0F, 100.0F + (m_currentCursor.x + 1) * 30.0F, (m_currentCursor.y + 1)*30.0F), m_pSolidBrush, 3.0F);
}

void EntityScenePuzzle::OnPostRender()
{

}
