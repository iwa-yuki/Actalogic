#pragma once
#include "pch.h"
#include "Entity.h"

class EntitySceneContainer;

class EntitySceneCreative :
	public Entity
{
public:
	EntitySceneCreative();
	EntitySceneCreative(EntitySceneContainer *pContainer);
	virtual ~EntitySceneCreative();

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
};

