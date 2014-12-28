#pragma once
#include "pch.h"
#include "Entity.h"

class ActalogicApp;

class EntityDebugInfoLayer :
	public Entity
{
public:
	EntityDebugInfoLayer();
	virtual ~EntityDebugInfoLayer();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardDeviceIndependentResources();

	void OnRender(D2D1Manager *pD2D1Manager);
private:
	IDWriteTextFormat *m_pDWTextFormat;
	ID2D1SolidColorBrush *m_pTextBrush;

	ActalogicApp *m_theApp;

public:
	void SetApp(ActalogicApp *pApp);
};

