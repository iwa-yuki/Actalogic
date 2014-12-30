#pragma once
#include "pch.h"
#include "Entity.h"
#include "InputHelper.h"

class EntitySceneContainer;

class EntitySceneMenu :
	public Entity
{
public:
	EntitySceneMenu();
	EntitySceneMenu(EntitySceneContainer *pContainer);
	virtual ~EntitySceneMenu();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardAllResources();

	void OnPreRender(InputHelper *pInputHelper);
	void OnRender(D2D1Manager *pD2D1Manager);
	void OnPostRender();

private:
	EntitySceneContainer *m_pContainer;
	ID2D1Bitmap *m_pBitmapBackground;
	int m_cursor;
	int m_keyInputCounter;
};

