#include "pch.h"
#include "EntitySceneMenu.h"
#include "ActalogicApp.h"

EntitySceneMenu::EntitySceneMenu() :
m_pBitmapBackground(nullptr),
m_cursor(0),
m_keyInputCounter(0),
m_pTheApp(nullptr)
{
}

EntitySceneMenu::EntitySceneMenu(ActalogicApp *pApp) :
m_pBitmapBackground(nullptr),
m_cursor(0),
m_keyInputCounter(0),
m_pTheApp(pApp)
{
}


EntitySceneMenu::~EntitySceneMenu()
{
	assert(!m_pBitmapBackground);
}

HRESULT EntitySceneMenu::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return S_OK;
}

HRESULT EntitySceneMenu::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	if (m_pBitmapBackground == nullptr)
	{
		hresult = pD2D1Manager->LoadBitmapFromFile(_T("image\\menu_back.png"), &m_pBitmapBackground);
	}

	return S_OK;
}

void EntitySceneMenu::OnDiscardDeviceResources()
{
	if (m_pBitmapBackground != nullptr) { m_pBitmapBackground->Release(); m_pBitmapBackground = nullptr; }
}

void EntitySceneMenu::OnDiscardAllResources()
{
	OnDiscardDeviceResources();
}

void EntitySceneMenu::OnPreRender(InputHelper *pInputHelper)
{
	if (pInputHelper->GetKeyState(InputHelper::INPUT_DOWN))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 40 && m_keyInputCounter % 5 == 0))
		{
			m_cursor = (m_cursor + 1) % 4;
		}
		m_keyInputCounter++;
	}
	else if (pInputHelper->GetKeyState(InputHelper::INPUT_UP))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 40 && m_keyInputCounter % 5 == 0))
		{
			m_cursor = (m_cursor + 3) % 4;
		}
		m_keyInputCounter++;
	}
	else if (pInputHelper->GetKeyState(InputHelper::INPUT_SELECT))
	{
		if (m_cursor == 3) // EXIT
		{
			m_pTheApp->Exit();
		}
	}
	else
	{
		m_keyInputCounter = 0;
	}
}

void EntitySceneMenu::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();

	pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height), 1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height));

	pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(160.0F, 195.0F + 75.0F*m_cursor, 160.0F + 44.0F, 195.0F + 75.0F*m_cursor + 44.0F), 1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, targetSize.height, 44.0F, targetSize.height + 44.0F));
}

void EntitySceneMenu::OnPostRender()
{

}
