#include "pch.h"
#include "EntitySceneCreative.h"
#include "EntitySceneContainer.h"

EntitySceneCreative::EntitySceneCreative() :
m_pContainer(nullptr),
m_pBitmapBackground(nullptr)
{
}

EntitySceneCreative::EntitySceneCreative(EntitySceneContainer *pContainer) :
m_pContainer(pContainer),
m_pBitmapBackground(nullptr)
{
}


EntitySceneCreative::~EntitySceneCreative()
{
	assert(!m_pBitmapBackground);
}

HRESULT EntitySceneCreative::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return S_OK;
}

HRESULT EntitySceneCreative::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	if (m_pBitmapBackground == nullptr)
	{
		hresult = pD2D1Manager->LoadBitmapFromFile(_T("image\\game_back.png"), &m_pBitmapBackground);
	}

	return S_OK;
}

void EntitySceneCreative::OnDiscardDeviceResources()
{
	if (m_pBitmapBackground != nullptr) { m_pBitmapBackground->Release(); m_pBitmapBackground = nullptr; }
}

void EntitySceneCreative::OnDiscardAllResources()
{
	OnDiscardDeviceResources();
}

void EntitySceneCreative::OnPreRender(InputHelper *pInputHelper)
{
	if (pInputHelper->GetKeyState(InputHelper::INPUT_ESCAPE))
	{
		m_pContainer->SetMenu();
	}
}

void EntitySceneCreative::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();

	pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height), 1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height));
}

void EntitySceneCreative::OnPostRender()
{

}
