#include "pch.h"
#include "EntitySceneMenu.h"


EntitySceneMenu::EntitySceneMenu():
m_pBitmapBackground(nullptr)
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

void EntitySceneMenu::OnPreRender()
{

}

void EntitySceneMenu::OnRender(D2D1Manager *pD2D1Manager)
{
	pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, 640.0F, 480.0F), 1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, 640.0F, 480.0F));
}

void EntitySceneMenu::OnPostRender()
{

}
