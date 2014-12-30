#pragma once
#include "pch.h"
#include "Entity.h"
#include "InputHelper.h"

class ActalogicApp;

class EntitySceneMenu :
	public Entity
{
public:
	EntitySceneMenu();
	EntitySceneMenu(ActalogicApp *pApp);
	virtual ~EntitySceneMenu();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardAllResources();

	void OnPreRender(InputHelper *pInputHelper);
	void OnRender(D2D1Manager *pD2D1Manager);
	void OnPostRender();

private:
	ActalogicApp *m_pTheApp;
	ID2D1Bitmap *m_pBitmapBackground;
	int m_cursor;
	int m_keyInputCounter;
};

