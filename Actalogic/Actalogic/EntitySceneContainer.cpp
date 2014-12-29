#include "pch.h"
#include "EntitySceneContainer.h"


enum EntityScene : long
{
	MENU,
};

///////////////////////////////////////////////////////////////////////////////

EntitySceneContainer::EntitySceneContainer() :
m_scene(EntityScene::MENU),
m_entityMenu()
{
}


EntitySceneContainer::~EntitySceneContainer()
{
}


HRESULT EntitySceneContainer::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	hresult = m_entityMenu.OnCreateDeviceIndependentResources(pD2D1Manager);

	return hresult;
}

HRESULT EntitySceneContainer::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	hresult = m_entityMenu.OnCreateDeviceResources(pD2D1Manager);

	return hresult;
}

void EntitySceneContainer::OnDiscardDeviceResources()
{
	m_entityMenu.OnDiscardDeviceResources();
}

void EntitySceneContainer::OnDiscardAllResources()
{
	m_entityMenu.OnDiscardAllResources();
}

void EntitySceneContainer::OnPreRender()
{
	switch (m_scene)
	{
	case EntityScene::MENU:
		m_entityMenu.OnPreRender();
		break;
	default:
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
	default:
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
	default:
		break;
	}
}

///////////////////////////////////////////////////////////////////////////////
