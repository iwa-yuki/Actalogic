#include "pch.h"
#include "EntitySceneContainer.h"
#include "ActalogicApp.h"


enum EntityScene : long
{
	MENU,
	PUZZLE,
};

///////////////////////////////////////////////////////////////////////////////

EntitySceneContainer::EntitySceneContainer() :
m_scene(EntityScene::MENU),
m_entityMenu(this),
m_entityPuzzle(this),
m_pTheApp(nullptr)
{
}

EntitySceneContainer::EntitySceneContainer(ActalogicApp *pApp) :
m_scene(EntityScene::MENU),
m_entityMenu(this),
m_entityPuzzle(this),
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

	return hresult;
}

HRESULT EntitySceneContainer::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	hresult = m_entityMenu.OnCreateDeviceResources(pD2D1Manager);
	if (FAILED(hresult)){ return hresult; }

	hresult = m_entityPuzzle.OnCreateDeviceResources(pD2D1Manager);

	return hresult;
}

void EntitySceneContainer::OnDiscardDeviceResources()
{
	m_entityMenu.OnDiscardDeviceResources();
	m_entityPuzzle.OnDiscardDeviceResources();
}

void EntitySceneContainer::OnDiscardAllResources()
{
	m_entityMenu.OnDiscardAllResources();
	m_entityPuzzle.OnDiscardAllResources();
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
}

void EntitySceneContainer::SetConfig()
{
}

void EntitySceneContainer::SetExit()
{
	m_pTheApp->Exit();
}
