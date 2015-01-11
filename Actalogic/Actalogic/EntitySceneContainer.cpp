#include "pch.h"
#include "EntitySceneContainer.h"
#include "ActalogicApp.h"

///////////////////////////////////////////////////////////////////////////////

EntitySceneContainer::EntitySceneContainer() :
m_scene(EntityScene::MENU),
m_entityMenu(this),
m_entityPuzzle(this),
m_entityCreative(this),
m_pTheApp(nullptr)
{
}

EntitySceneContainer::EntitySceneContainer(ActalogicApp *pApp) :
m_scene(EntityScene::MENU),
m_entityMenu(this),
m_entityPuzzle(this),
m_entityCreative(this),
m_pTheApp(pApp)
{
}


EntitySceneContainer::~EntitySceneContainer()
{
}


HRESULT EntitySceneContainer::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	hresult = m_entityMenu.OnCreateDeviceIndependentResources(pD2D1Manager);
	if (FAILED(hresult)){ return hresult; }

	hresult = m_entityPuzzle.OnCreateDeviceIndependentResources(pD2D1Manager);
	if (FAILED(hresult)){ return hresult; }

	hresult = m_entityCreative.OnCreateDeviceIndependentResources(pD2D1Manager);

	return hresult;
}

HRESULT EntitySceneContainer::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	hresult = m_entityMenu.OnCreateDeviceResources(pD2D1Manager);
	if (FAILED(hresult)){ return hresult; }

	hresult = m_entityPuzzle.OnCreateDeviceResources(pD2D1Manager);
	if (FAILED(hresult)){ return hresult; }

	hresult = m_entityCreative.OnCreateDeviceResources(pD2D1Manager);

	return hresult;
}

void EntitySceneContainer::OnDiscardDeviceResources()
{
	m_entityMenu.OnDiscardDeviceResources();
	m_entityPuzzle.OnDiscardDeviceResources();
	m_entityCreative.OnDiscardDeviceResources();
}

void EntitySceneContainer::OnDiscardAllResources()
{
	m_entityMenu.OnDiscardAllResources();
	m_entityPuzzle.OnDiscardAllResources();
	m_entityCreative.OnDiscardAllResources();
}

void EntitySceneContainer::OnPreRender(InputHelper *pInputHelper)
{
	switch (m_scene)
	{
	case EntityScene::MENU:
		m_entityMenu.OnPreRender(pInputHelper);
		break;
	case EntityScene::PUZZLE:
		m_entityPuzzle.OnPreRender(pInputHelper);
		break;
	case EntityScene::CREATIVE:
		m_entityCreative.OnPreRender(pInputHelper);
		break;
	default:
		assert(false);
		break;
	}
}

void EntitySceneContainer::OnRender(D2D1Manager *pD2D1Manager)
{
	switch (m_scene)
	{
	case EntityScene::MENU:
		m_entityMenu.OnRender(pD2D1Manager);
		break;
	case EntityScene::PUZZLE:
		m_entityPuzzle.OnRender(pD2D1Manager);
		break;
	case EntityScene::CREATIVE:
		m_entityCreative.OnRender(pD2D1Manager);
		break;
	default:
		assert(false);
		break;
	}
}

void EntitySceneContainer::OnPostRender()
{
	switch (m_scene)
	{
	case EntityScene::MENU:
		m_entityMenu.OnPostRender();
		break;
	case EntityScene::PUZZLE:
		m_entityPuzzle.OnPostRender();
		break;
	case EntityScene::CREATIVE:
		m_entityCreative.OnPostRender();
		break;
	default:
		assert(false);
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////

void EntitySceneContainer::SetMenu()
{
	m_scene = EntityScene::MENU;
}

void EntitySceneContainer::SetPuzzle()
{
	m_scene = EntityScene::PUZZLE;
}

void EntitySceneContainer::SetCreative()
{
	m_scene = EntityScene::CREATIVE;
}

void EntitySceneContainer::SetConfig()
{
	m_scene = EntityScene::CONFIG;
}

void EntitySceneContainer::SetExit()
{
	m_pTheApp->Exit();
}
