#pragma once
#include "pch.h"
#include "Entity.h"
#include "EntityActalogicCell.h"

class EntitySceneContainer;

class EntityScenePuzzle :
	public Entity
{
public:
	EntityScenePuzzle();
	EntityScenePuzzle(EntitySceneContainer *pContainer);
	virtual ~EntityScenePuzzle();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);
	void OnDiscardDeviceResources();
	void OnDiscardAllResources();

	void OnPreRender(InputHelper *pInputHelper);
	void OnRender(D2D1Manager *pD2D1Manager);
	void OnPostRender();

	ActalogicCell* GetCurrentCell();

private:
	EntitySceneContainer *m_pContainer;
	ID2D1Bitmap *m_pBitmapBackground;
	ID2D1SolidColorBrush *m_pSolidBrush;
	POINT m_currentCursor;
	int m_keyInputCounter;

	std::list<ActalogicCell*> m_cells;
	ActalogicCell* m_stackedCell;

private:
	void UpdateCellState();
	bool CanLink(ActalogicCell *pCell1, ActalogicCell *pCell2);
};

