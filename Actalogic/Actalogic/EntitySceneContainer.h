#pragma once
#include "pch.h"
#include "Entity.h"
#include "EntitySceneMenu.h"
#include "InputHelper.h"

enum EntityScene : long;
class ActalogicApp;

class EntitySceneContainer :
	public Entity
{
public:
	EntitySceneContainer();
	EntitySceneContainer(ActalogicApp *pApp);
	virtual ~EntitySceneContainer();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardAllResources();

	void OnPreRender(InputHelper *pInputHelper);
	void OnRender(D2D1Manager *pD2D1Manager);
	void OnPostRender();

private:
	ActalogicApp *m_pTheApp;
	EntityScene m_scene;

	EntitySceneMenu m_entityMenu;
};
