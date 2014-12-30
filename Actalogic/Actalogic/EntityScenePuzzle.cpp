#include "pch.h"
#include "EntityScenePuzzle.h"
#include "EntitySceneContainer.h"

EntityScenePuzzle::EntityScenePuzzle() :
m_pContainer(nullptr),
m_pBitmapBackground(nullptr)
{
}

EntityScenePuzzle::EntityScenePuzzle(EntitySceneContainer *pContainer) :
m_pContainer(pContainer),
m_pBitmapBackground(nullptr)
{
}


EntityScenePuzzle::~EntityScenePuzzle()
{
	assert(!m_pBitmapBackground);
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

	return S_OK;
}

void EntityScenePuzzle::OnDiscardDeviceResources()
{
	if (m_pBitmapBackground != nullptr) { m_pBitmapBackground->Release(); m_pBitmapBackground = nullptr; }
}

void EntityScenePuzzle::OnDiscardAllResources()
{
	OnDiscardDeviceResources();
}

void EntityScenePuzzle::OnPreRender(InputHelper *pInputHelper)
{
	if (pInputHelper->GetKeyState(InputHelper::INPUT_ESCAPE))
	{
		m_pContainer->SetMenu();
	}
}

void EntityScenePuzzle::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();

	pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height), 1.0F,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height));
}

void EntityScenePuzzle::OnPostRender()
{

}
