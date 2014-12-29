#pragma once
#include "pch.h"
#include "Entity.h"
class EntitySceneMenu :
	public Entity
{
public:
	EntitySceneMenu();
	virtual ~EntitySceneMenu();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardAllResources();

	void OnPreRender();
	void OnRender(D2D1Manager *pD2D1Manager);
	void OnPostRender();

private:
	ID2D1Bitmap *m_pBitmapBackground;
};

