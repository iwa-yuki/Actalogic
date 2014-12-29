#pragma once
#include "pch.h"
#include "Entity.h"
#include "EntitySceneMenu.h"

enum EntityScene : long;

class EntitySceneContainer :
	public Entity
{
public:
	EntitySceneContainer();
	virtual ~EntitySceneContainer();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardAllResources();

	void OnPreRender();
	void OnRender(D2D1Manager *pD2D1Manager);
	void OnPostRender();

private:
	EntityScene m_scene;

	EntitySceneMenu m_entityMenu;
};
