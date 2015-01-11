#pragma once
#include "pch.h"
#include "Entity.h"
#include "EntitySceneMenu.h"
#include "EntityScenePuzzle.h"
#include "EntitySceneCreative.h"
#include "InputHelper.h"

enum EntityScene : long
{
	MENU,
	PUZZLE,
	CREATIVE,
	CONFIG,
};

class ActalogicApp;

class EntitySceneContainer :
	public Entity
{
	friend class EntityDebugInfoLayer;

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

	void SetMenu();
	void SetPuzzle();
	void SetCreative();
	void SetConfig();
	void SetExit();

private:
	ActalogicApp *m_pTheApp;
	EntityScene m_scene;

	EntitySceneMenu m_entityMenu;
	EntityScenePuzzle m_entityPuzzle;
	EntitySceneCreative m_entityCreative;
};
