#include "pch.h"
#include "EntityScenePuzzle.h"
#include "EntitySceneContainer.h"
#include "ActalogicCell.h"

EntityScenePuzzle::EntityScenePuzzle() :
EntityScenePuzzle(nullptr)
{
}

EntityScenePuzzle::EntityScenePuzzle(EntitySceneContainer *pContainer) :
m_pContainer(pContainer),
m_pBitmapBackground(nullptr),
m_pSolidBrush(nullptr),
m_currentCursor({ 0, 0 }),
m_keyInputCounter(1),
m_cells(),
m_stackedCell(nullptr)
{
	m_cells.push_back(new ActalogicCell({ 0, 0 }, ActalogicCellType::CELL_BUFFER));
	m_cells.push_back(new ActalogicCell({ 0, 1 }, ActalogicCellType::CELL_NAND));
	m_cells.push_back(new ActalogicCell({ 0, 2 }, ActalogicCellType::CELL_NOR));

	m_cells.push_back(new ActalogicCell({ 0, 3 }, ActalogicCellType::WIRE_UP));
	m_cells.push_back(new ActalogicCell({ 1, 3 }, ActalogicCellType::WIRE_DOWN));
	m_cells.push_back(new ActalogicCell({ 2, 3 }, ActalogicCellType::WIRE_RIGHT));
	m_cells.push_back(new ActalogicCell({ 3, 3 }, ActalogicCellType::WIRE_LEFT));
}


EntityScenePuzzle::~EntityScenePuzzle()
{
	assert(!m_pBitmapBackground);
	assert(!m_pSolidBrush);

	for (ActalogicCell* pCell : m_cells)
	{
		delete pCell;
	}
	m_cells.clear();
}

HRESULT EntityScenePuzzle::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return S_OK;
}

HRESULT EntityScenePuzzle::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	HRESULT hresult = S_OK;

	if (m_pBitmapBackground == nullptr)
	{
		hresult = pD2D1Manager->LoadBitmapFromFile(_T("image\\game_back.png"), &m_pBitmapBackground);
	}
	if (FAILED(hresult)){ return hresult; }

	if (m_pSolidBrush == nullptr)
	{
		hresult = pD2D1Manager->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &m_pSolidBrush);
	}
	if (FAILED(hresult)){ return hresult; }

	return S_OK;
}

void EntityScenePuzzle::OnDiscardDeviceResources()
{
	if (m_pBitmapBackground != nullptr) { m_pBitmapBackground->Release(); m_pBitmapBackground = nullptr; }
	if (m_pSolidBrush != nullptr) { m_pSolidBrush->Release(); m_pSolidBrush = nullptr; }
}

void EntityScenePuzzle::OnDiscardAllResources()
{
	OnDiscardDeviceResources();
}

void EntityScenePuzzle::OnPreRender(InputHelper *pInputHelper)
{
	bool isKeyDown = false;
	if (pInputHelper->GetKeyState(InputHelper::INPUT_ESCAPE))
	{
		m_pContainer->SetMenu();
		isKeyDown = true;
	}

	if (pInputHelper->GetKeyState(InputHelper::INPUT_UP))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.y = m_currentCursor.y > 0 ? m_currentCursor.y - 1 : m_currentCursor.y;
		}
		isKeyDown = true;
	}
	else if (pInputHelper->GetKeyState(InputHelper::INPUT_DOWN))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.y = m_currentCursor.y < 19 ? m_currentCursor.y + 1 : m_currentCursor.y;
		}
		isKeyDown = true;
	}

	if (pInputHelper->GetKeyState(InputHelper::INPUT_LEFT))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.x = m_currentCursor.x > 0 ? m_currentCursor.x - 1 : m_currentCursor.x;
		}
		isKeyDown = true;
	}
	else if (pInputHelper->GetKeyState(InputHelper::INPUT_RIGHT))
	{
		if (m_keyInputCounter == 0 || (m_keyInputCounter >= 24 && m_keyInputCounter % 3 == 0))
		{
			m_currentCursor.x = m_currentCursor.x < 19 ? m_currentCursor.x + 1 : m_currentCursor.x;
		}
		isKeyDown = true;
	}
	if (pInputHelper->GetKeyState(InputHelper::INPUT_SELECT))
	{
		if (m_keyInputCounter == 0)
		{
			ActalogicCell *pTmpCell = nullptr;
			for (ActalogicCell *pCell : m_cells)
			{
				POINT pt = pCell->GetPosition();
				if (pt.x == m_currentCursor.x && pt.y == m_currentCursor.y)
				{
					pTmpCell = pCell;
					break;
				}
			}
			if (pTmpCell != nullptr)
			{
				m_cells.remove(pTmpCell);
				UpdateCellState();
			}
			if (m_stackedCell == nullptr)
			{
				m_stackedCell = pTmpCell;
			}
			else
			{
				m_stackedCell->SetPosition(m_currentCursor);
				m_cells.push_back(m_stackedCell);
				UpdateCellState();
				m_stackedCell = pTmpCell;
			}
		}
		isKeyDown = true;
	}
	
	if (isKeyDown)
	{
		m_keyInputCounter++;
	}
	else
	{
		m_keyInputCounter = 0;
	}
}

void EntityScenePuzzle::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();

	//pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height), 1.0F,
	//	D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height));

	// Œrü‚ð•`‰æ
	m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Gray));
	for (int i = 0; i <= 20; ++i)
	{
		pD2D1Manager->DrawLine(D2D1::Point2F(100.0F, i*30.0F), D2D1::Point2F(targetSize.width - 100.0F, i*30.0F), m_pSolidBrush);
	}
	for (int i = 0; i <= 20; ++i)
	{
		pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + i*30.0F, 0.0F), D2D1::Point2F(100.0F + i*30.0F, targetSize.height), m_pSolidBrush);
	}

	// ƒZƒ‹‚ð•`‰æ
	for (ActalogicCell* pCell : m_cells)
	{
		switch (pCell->GetType())
		{
		case ActalogicCellType::CELL_BUFFER:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Black));
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::CELL_NAND:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Red));
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::CELL_NOR:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::WIRE_UP:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::WIRE_DOWN:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::WIRE_RIGHT:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::WIRE_LEFT:
		{
			POINT pt = pCell->GetPosition();
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			break;
		}
		default:
			break;
		}
	}

	// ƒJ[ƒ\ƒ‹‚ð•`‰æ
	m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
	pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + m_currentCursor.x * 30.0F, m_currentCursor.y*30.0F,
		100.0F + (m_currentCursor.x + 1) * 30.0F, (m_currentCursor.y + 1)*30.0F), m_pSolidBrush, 3.0F);
}

void EntityScenePuzzle::OnPostRender()
{

}

///////////////////////////////////////////////////////////////////////////////

void EntityScenePuzzle::UpdateCellState()
{
	ActalogicCell *pCurrentCell = nullptr;
	{
		for (ActalogicCell *pCell : m_cells)
		{
			POINT pt = pCell->GetPosition();
			if (pt.x == m_currentCursor.x && pt.y == m_currentCursor.y)
			{
				pCurrentCell = pCell;
			}
		}
	}

	if (pCurrentCell == nullptr)
	{
		for (ActalogicCell *pCell : m_cells)
		{
			POINT pt = pCell->GetPosition();
		}
	}
}
