#include "pch.h"
#include "EntityScenePuzzle.h"
#include "EntitySceneContainer.h"
#include "EntityActalogicCell.h"

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
	for (int i = 0; i < 2; ++i)
	{
		m_cells.push_back(new EntityActalogicCell({ i, 0 }, ActalogicCellType::CELL_BUFFER, true));
		m_cells.push_back(new EntityActalogicCell({ i, 1 }, ActalogicCellType::CELL_NAND, true));
		m_cells.push_back(new EntityActalogicCell({ i, 2 }, ActalogicCellType::CELL_NOR, true));
		m_cells.push_back(new EntityActalogicCell({ i, 3 }, ActalogicCellType::CELL_INPUT, true));
		m_cells.push_back(new EntityActalogicCell({ i, 4 }, ActalogicCellType::CELL_OUTPUT, true));

		m_cells.push_back(new EntityActalogicCell({ i, 5 }, ActalogicCellType::WIRE_UP, true));
		m_cells.push_back(new EntityActalogicCell({ i, 6 }, ActalogicCellType::WIRE_DOWN, true));
		m_cells.push_back(new EntityActalogicCell({ i, 7 }, ActalogicCellType::WIRE_RIGHT, true));
		m_cells.push_back(new EntityActalogicCell({ i, 8 }, ActalogicCellType::WIRE_LEFT, true));
	}
}


EntityScenePuzzle::~EntityScenePuzzle()
{
	assert(!m_pBitmapBackground);
	assert(!m_pSolidBrush);

	for (EntityActalogicCell* pCell : m_cells)
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

	// メニューへ戻る
	if (pInputHelper->GetKeyState(InputHelper::INPUT_ESCAPE))
	{
		m_pContainer->SetMenu();
		isKeyDown = true;
	}

	// カーソル移動
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

	// 選択
	if (pInputHelper->GetKeyState(InputHelper::INPUT_SELECT))
	{
		if (m_keyInputCounter == 0)
		{
			// カーソル位置にセルがあるか検索
			EntityActalogicCell *pTmpCell = GetCurrentCell();

			// 移動可能なセルの場合、カーソル位置のセルを削除
			if (pTmpCell != nullptr && pTmpCell->IsRemovable())
			{
				m_cells.remove(pTmpCell);
				UpdateCellState();
				pTmpCell->ClearLink(ActalogicCellDirection::DOWN);
				pTmpCell->ClearLink(ActalogicCellDirection::UP);
				pTmpCell->ClearLink(ActalogicCellDirection::RIGHT);
				pTmpCell->ClearLink(ActalogicCellDirection::LEFT);
			}

			if ((pTmpCell == nullptr) || (pTmpCell != nullptr && pTmpCell->IsRemovable()))
			{
				// m_stackedCellにセルが保存されていたらカーソル位置のセルと入れ替える
				if (m_stackedCell != nullptr)
				{
					m_stackedCell->SetPosition(m_currentCursor);
					m_cells.push_back(m_stackedCell);
					UpdateCellState();
				}
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

	// セルの前処理
	for (EntityActalogicCell* pCell : m_cells)
	{
		pCell->OnPreRender(pInputHelper);
	}
	if (m_stackedCell != nullptr)
	{
		m_stackedCell->OnPreRender(pInputHelper);
	}
}

void EntityScenePuzzle::OnRender(D2D1Manager *pD2D1Manager)
{
	D2D1_SIZE_F targetSize = pD2D1Manager->GetRenderTargetSize();

	//pD2D1Manager->DrawBitmap(m_pBitmapBackground, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height), 1.0F,
	//	D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0.0F, 0.0F, targetSize.width, targetSize.height));

	// 罫線を描画
	m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::LightGray));
	for (int i = 0; i <= 20; ++i)
	{
		pD2D1Manager->DrawLine(D2D1::Point2F(100.0F, i*30.0F), D2D1::Point2F(targetSize.width - 100.0F, i*30.0F), m_pSolidBrush);
	}
	for (int i = 0; i <= 20; ++i)
	{
		pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + i*30.0F, 0.0F), D2D1::Point2F(100.0F + i*30.0F, targetSize.height), m_pSolidBrush);
	}

	// セル・リンクを描画
	for (EntityActalogicCell* pCell : m_cells)
	{
		POINT pt = pCell->GetPosition();
		if (!pCell->IsRemovable())
		{
			m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Gainsboro));
			pD2D1Manager->FillRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 1.0F, pt.y*30.0F + 1.0F,
				100.0F + (pt.x + 1) * 30.0F - 1.0F, (pt.y + 1)*30.0F - 1.0F), m_pSolidBrush);
		}
		// セルを描画
		switch (pCell->GetType())
		{
		case ActalogicCellType::CELL_BUFFER:
		{
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			break;
		}
		case ActalogicCellType::CELL_NAND:
		{
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), 2.0F, 2.0F), m_pSolidBrush, 3.0F);
			break;
		}
		case ActalogicCellType::CELL_NOR:
		{
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 6.0F, pt.y*30.0F + 15.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 24.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 6.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 24.0F), m_pSolidBrush, 3.0F);
			break;
		}
		case ActalogicCellType::CELL_INPUT:
		{
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 6.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 24.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 24.0F, pt.y*30.0F + 15.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 24.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 24.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 6.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 6.0F, pt.y*30.0F + 15.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 6.0F), m_pSolidBrush, 3.0F);
			break;
		}
		case ActalogicCellType::CELL_OUTPUT:
		{
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F,
				100.0F + (pt.x + 1) * 30.0F - 2.0F, (pt.y + 1)*30.0F - 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 6.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 24.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 24.0F, pt.y*30.0F + 15.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 24.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 24.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 6.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 3.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 6.0F, pt.y*30.0F + 15.0F),
				D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 6.0F), m_pSolidBrush, 3.0F);
			break;
		}
		case ActalogicCellType::WIRE_UP:
		{
			int linkToUp = pCell->GetDistanceToLink(ActalogicCellDirection::UP);
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			for (int i = 1; i <= linkToUp; ++i)
			{
				int prevValue = pCell->GetValue(i);
				if (prevValue > 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
				}
				else if (prevValue < 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				}
				else
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
				}
				if (i == linkToUp)
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F - (i - 1)*30.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 30.0F - i*30.0F), m_pSolidBrush, 2.0F);
				}
				else
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F - (i - 1)*30.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F - i*30.0F), m_pSolidBrush, 2.0F);
				}
			}
			break;
		}
		case ActalogicCellType::WIRE_DOWN:
		{
			int linkToDown = pCell->GetDistanceToLink(ActalogicCellDirection::DOWN);
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			for (int i = 1; i <= linkToDown; ++i)
			{
				int prevValue = pCell->GetValue(i);
				if (prevValue > 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
				}
				else if (prevValue < 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				}
				else
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
				}
				if (i == linkToDown)
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F + (i - 1)*30.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + i*30.0F), m_pSolidBrush, 2.0F);
				}
				else
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F + (i - 1)*30.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F + i*30.0F), m_pSolidBrush, 2.0F);
				}
			}
			break;
		}
		case ActalogicCellType::WIRE_RIGHT:
		{
			int linkToRight = pCell->GetDistanceToLink(ActalogicCellDirection::RIGHT);
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 2.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			for (int i = 1; i <= linkToRight; ++i)
			{
				int prevValue = pCell->GetValue(i);
				if (prevValue > 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
				}
				else if (prevValue < 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				}
				else
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
				}
				if (i == linkToRight)
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F + (i - 1)*30.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + i*30.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 2.0F);
				}
				else
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F + (i - 1)*30.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F + i*30.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 2.0F);
				}
			}
			//if (linkToRight > 0)
			//{
			//	pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + linkToRight*30.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 2.0F);
			//}
			break;
		}
		case ActalogicCellType::WIRE_LEFT:
		{
			int linkToLeft = pCell->GetDistanceToLink(ActalogicCellDirection::LEFT);
			if (pCell->GetValue() > 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
			}
			else if (pCell->GetValue() < 0)
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
			}
			else
			{
				m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
			}
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 2.0F), m_pSolidBrush, 2.0F);
			pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 28.0F, pt.y*30.0F + 28.0F), m_pSolidBrush, 2.0F);
			for (int i = 1; i <= linkToLeft; ++i)
			{
				int prevValue = pCell->GetValue(i);
				if (prevValue > 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Orange));
				}
				else if (prevValue < 0)
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Blue));
				}
				else
				{
					m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::DarkGray));
				}
				if (i == linkToLeft)
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F - (i - 1)*30.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 30.0F - i*30.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 2.0F);
				}
				else
				{
					pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F - (i - 1)*30.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F - i*30.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 2.0F);
				}
			}
			//if (linkToLeft > 0)
			//{
			//	pD2D1Manager->DrawLine(D2D1::Point2F(100.0F + pt.x * 30.0F + 15.0F, pt.y*30.0F + 15.0F), D2D1::Point2F(100.0F + pt.x * 30.0F + 30.0F - linkToLeft*30.0F, pt.y*30.0F + 15.0F), m_pSolidBrush, 2.0F);
			//}
			break;
		}
		default:
			break;
		}
	}

	// カーソルを描画
	m_pSolidBrush->SetColor(D2D1::ColorF(D2D1::ColorF::Green));
	pD2D1Manager->DrawRectangle(D2D1::RectF(100.0F + m_currentCursor.x * 30.0F, m_currentCursor.y*30.0F,
		100.0F + (m_currentCursor.x + 1) * 30.0F, (m_currentCursor.y + 1)*30.0F), m_pSolidBrush, 3.0F);
}

void EntityScenePuzzle::OnPostRender()
{
	// セルの後処理
	for (EntityActalogicCell* pCell : m_cells)
	{
		pCell->OnPostRender();
	}
	if (m_stackedCell != nullptr)
	{
		m_stackedCell->OnPostRender();
	}
}

EntityActalogicCell* EntityScenePuzzle::GetCurrentCell()
{
	EntityActalogicCell *pTmpCell = nullptr;
	for (EntityActalogicCell *pCell : m_cells)
	{
		POINT pt = pCell->GetPosition();
		if (pt.x == m_currentCursor.x && pt.y == m_currentCursor.y)
		{
			pTmpCell = pCell;
			break;
		}
	}

	return pTmpCell;
}

///////////////////////////////////////////////////////////////////////////////

void EntityScenePuzzle::UpdateCellState()
{
	// カーソル位置および十字方向にもっとも近いセルを検索
	EntityActalogicCell *pCurrentCell = nullptr;
	EntityActalogicCell *pRightCell = nullptr;
	EntityActalogicCell *pLeftCell = nullptr;
	EntityActalogicCell *pUpCell = nullptr;
	EntityActalogicCell *pDownCell = nullptr;
	{
		for (EntityActalogicCell *pCell : m_cells)
		{
			POINT pt = pCell->GetPosition();
			if (pt.x == m_currentCursor.x)
			{
				if (pt.y == m_currentCursor.y)
				{
					// カーソル位置のセル
					pCurrentCell = pCell;
				}
				else if (pt.y > m_currentCursor.y)
				{
					// 下方向のセル
					if (pDownCell == nullptr)
					{
						pDownCell = pCell;
					}
					else if (pDownCell->GetPosition().y > pt.y)
					{
						pDownCell = pCell;
					}
				}
				else
				{
					// 上方向のセル
					if (pUpCell == nullptr)
					{
						pUpCell = pCell;
					}
					else if (pUpCell->GetPosition().y < pt.y)
					{
						pUpCell = pCell;
					}
				}
			}
			else if (pt.y == m_currentCursor.y)
			{
				if (pt.x == m_currentCursor.x)
				{
					assert(false);
				}
				else if (pt.x > m_currentCursor.x)
				{
					// 右方向のセル
					if (pRightCell == nullptr)
					{
						pRightCell = pCell;
					}
					else if (pRightCell->GetPosition().x > pt.x)
					{
						pRightCell = pCell;
					}
				}
				else
				{
					// 左方向のセル
					if (pLeftCell == nullptr)
					{
						pLeftCell = pCell;
					}
					else if (pLeftCell->GetPosition().x < pt.x)
					{
						pLeftCell = pCell;
					}
				}
			}
		}
	}

	//相互リンク生成
	if (pCurrentCell != nullptr)
	{
		if (pRightCell != nullptr)
		{
			if (CanLink(pCurrentCell, pRightCell))
			{
				pCurrentCell->SetLink(ActalogicCellDirection::RIGHT, pRightCell);
				pRightCell->SetLink(ActalogicCellDirection::LEFT, pCurrentCell);
			}
			else
			{
				pCurrentCell->ClearLink(ActalogicCellDirection::RIGHT);
				pRightCell->ClearLink(ActalogicCellDirection::LEFT);
			}
		}
		else
		{
			pCurrentCell->ClearLink(ActalogicCellDirection::RIGHT);
		}

		if (pLeftCell != nullptr)
		{
			if (CanLink(pCurrentCell, pLeftCell))
			{
				pCurrentCell->SetLink(ActalogicCellDirection::LEFT, pLeftCell);
				pLeftCell->SetLink(ActalogicCellDirection::RIGHT, pCurrentCell);
			}
			else
			{
				pCurrentCell->ClearLink(ActalogicCellDirection::LEFT);
				pLeftCell->ClearLink(ActalogicCellDirection::RIGHT);
			}
		}
		else
		{
			pCurrentCell->ClearLink(ActalogicCellDirection::LEFT);
		}

		if (pUpCell != nullptr)
		{
			if (CanLink(pCurrentCell, pUpCell))
			{
				pCurrentCell->SetLink(ActalogicCellDirection::UP, pUpCell);
				pUpCell->SetLink(ActalogicCellDirection::DOWN, pCurrentCell);
			}
			else
			{
				pCurrentCell->ClearLink(ActalogicCellDirection::UP);
				pUpCell->ClearLink(ActalogicCellDirection::DOWN);
			}
		}
		else
		{
			pCurrentCell->ClearLink(ActalogicCellDirection::UP);
		}

		if (pDownCell != nullptr)
		{
			if (CanLink(pCurrentCell, pDownCell))
			{
				pCurrentCell->SetLink(ActalogicCellDirection::DOWN, pDownCell);
				pDownCell->SetLink(ActalogicCellDirection::UP, pCurrentCell);
			}
			else
			{
				pCurrentCell->ClearLink(ActalogicCellDirection::DOWN);
				pDownCell->ClearLink(ActalogicCellDirection::UP);
			}
		}
		else
		{
			pCurrentCell->ClearLink(ActalogicCellDirection::DOWN);
		}
	}
	else
	{
		if (pRightCell != nullptr)
		{
			if (pLeftCell != nullptr)
			{
				if (CanLink(pRightCell, pLeftCell))
				{
					pRightCell->SetLink(ActalogicCellDirection::LEFT, pLeftCell);
					pLeftCell->SetLink(ActalogicCellDirection::RIGHT, pRightCell);
				}
				else
				{
					pRightCell->ClearLink(ActalogicCellDirection::LEFT);
					pLeftCell->ClearLink(ActalogicCellDirection::RIGHT);
				}
			}
			else
			{
				pRightCell->ClearLink(ActalogicCellDirection::LEFT);
			}
		}
		else
		{
			if (pLeftCell != nullptr)
			{
				pLeftCell->ClearLink(ActalogicCellDirection::RIGHT);
			}
		}

		if (pUpCell != nullptr)
		{
			if (pDownCell != nullptr)
			{
				if (CanLink(pUpCell, pDownCell))
				{
					pUpCell->SetLink(ActalogicCellDirection::DOWN, pDownCell);
					pDownCell->SetLink(ActalogicCellDirection::UP, pUpCell);
				}
				else
				{
					pUpCell->ClearLink(ActalogicCellDirection::DOWN);
					pDownCell->ClearLink(ActalogicCellDirection::UP);
				}
			}
			else
			{
				pUpCell->ClearLink(ActalogicCellDirection::DOWN);
			}
		}
		else
		{
			if (pDownCell != nullptr)
			{
				pDownCell->ClearLink(ActalogicCellDirection::UP);
			}
		}
	}
}

bool EntityScenePuzzle::CanLink(EntityActalogicCell *pCell1, EntityActalogicCell *pCell2)
{
	if (pCell1 == nullptr || pCell2 == nullptr)
	{
		return false;
	}

	POINT pt1 = pCell1->GetPosition();
	POINT pt2 = pCell2->GetPosition();
	ActalogicCellType type1 = pCell1->GetType();
	ActalogicCellType type2 = pCell2->GetType();

	if (type1 == ActalogicCellType::WIRE_UP)
	{
		if ((pt1.x == pt2.x) && (pt1.y == pt2.y - 1 || (pt1.y > pt2.y && pt1.y < pt2.y + 16)))
		{
			if (type2 == ActalogicCellType::CELL_BUFFER ||
				type2 == ActalogicCellType::CELL_NAND ||
				type2 == ActalogicCellType::CELL_NOR ||
				type2 == ActalogicCellType::CELL_INPUT ||
				type2 == ActalogicCellType::CELL_OUTPUT)
			{
				return true;
			}
		}
	}
	else if (type1 == ActalogicCellType::WIRE_DOWN)
	{
		if ((pt1.x == pt2.x) && (pt1.y == pt2.y + 1 || (pt1.y < pt2.y && pt1.y > pt2.y - 16)))
		{
			if (type2 == ActalogicCellType::CELL_BUFFER ||
				type2 == ActalogicCellType::CELL_NAND ||
				type2 == ActalogicCellType::CELL_NOR ||
				type2 == ActalogicCellType::CELL_INPUT ||
				type2 == ActalogicCellType::CELL_OUTPUT)
			{
				return true;
			}
		}
	}
	else if (type1 == ActalogicCellType::WIRE_LEFT)
	{
		if ((pt1.y == pt2.y) && (pt1.x == pt2.x - 1 || (pt1.x > pt2.x && pt1.x < pt2.x + 16)))
		{
			if (type2 == ActalogicCellType::CELL_BUFFER ||
				type2 == ActalogicCellType::CELL_NAND ||
				type2 == ActalogicCellType::CELL_NOR ||
				type2 == ActalogicCellType::CELL_INPUT ||
				type2 == ActalogicCellType::CELL_OUTPUT)
			{
				return true;
			}
		}
	}
	else if (type1 == ActalogicCellType::WIRE_RIGHT)
	{
		if ((pt1.y == pt2.y) && (pt1.x == pt2.x + 1 || (pt1.x < pt2.x && pt1.x > pt2.x - 16)))
		{
			if (type2 == ActalogicCellType::CELL_BUFFER ||
				type2 == ActalogicCellType::CELL_NAND ||
				type2 == ActalogicCellType::CELL_NOR ||
				type2 == ActalogicCellType::CELL_INPUT ||
				type2 == ActalogicCellType::CELL_OUTPUT)
			{
				return true;
			}
		}
	}
	else
	{
		if (type2 == ActalogicCellType::WIRE_UP)
		{
			if ((pt1.x == pt2.x) && (pt1.y == pt2.y + 1 || (pt1.y < pt2.y && pt1.y > pt2.y -16)))
			{
				return true;
			}
		}
		else if (type2 == ActalogicCellType::WIRE_DOWN)
		{
			if ((pt1.x == pt2.x) && (pt1.y == pt2.y - 1 || (pt1.y > pt2.y && pt1.y < pt2.y +16)))
			{
				return true;
			}
		}
		else if (type2 == ActalogicCellType::WIRE_LEFT)
		{
			if ((pt1.y == pt2.y) && (pt1.x == pt2.x + 1 || (pt1.x < pt2.x && pt1.x > pt2.x -16)))
			{
				return true;
			}
		}
		else if (type2 == ActalogicCellType::WIRE_RIGHT)
		{
			if ((pt1.y == pt2.y) && (pt1.x == pt2.x - 1 || (pt1.x > pt2.x && pt1.x < pt2.x +16)))
			{
				return true;
			}
		}
	}

	return false;
}