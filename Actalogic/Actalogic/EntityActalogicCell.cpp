#include "pch.h"
#include "EntityActalogicCell.h"

ActalogicCell::ActalogicCell() : 
ActalogicCell({ 0, 0 })
{
}

ActalogicCell::ActalogicCell(const POINT &pt,
	ActalogicCellType type, bool removable) :
m_type(type),
m_position(pt),
m_isRemovable(removable)
{
	m_pLinkedCells[ActalogicCellDirection::RIGHT] = nullptr;
	m_pLinkedCells[ActalogicCellDirection::DOWN] = nullptr;
	m_pLinkedCells[ActalogicCellDirection::LEFT] = nullptr;
	m_pLinkedCells[ActalogicCellDirection::UP] = nullptr;
}

ActalogicCell::~ActalogicCell()
{
}


ActalogicCellType ActalogicCell::GetType()
{
	return m_type;
}

POINT ActalogicCell::GetPosition()
{
	return m_position;
}

void ActalogicCell::SetPosition(const POINT &pt)
{
	m_position = pt;
}

void ActalogicCell::SetLink(ActalogicCellDirection dir, ActalogicCell *pCell)
{
	if (pCell == nullptr)
	{
		ClearLink(dir);
		return;
	}

	switch (dir)
	{
	case ActalogicCellDirection::RIGHT:
		assert(pCell->GetPosition().y == m_position.y && pCell->GetPosition().x > m_position.x);
		m_pLinkedCells[dir] = pCell;
		break;
	case ActalogicCellDirection::DOWN:
		assert(pCell->GetPosition().x == m_position.x && pCell->GetPosition().y > m_position.y);
		m_pLinkedCells[dir] = pCell;
		break;
	case ActalogicCellDirection::LEFT:
		assert(pCell->GetPosition().y == m_position.y && pCell->GetPosition().x < m_position.x);
		m_pLinkedCells[dir] = pCell;
		break;
	case ActalogicCellDirection::UP:
		assert(pCell->GetPosition().x == m_position.x && pCell->GetPosition().y < m_position.y);
		m_pLinkedCells[dir] = pCell;
		break;
	default:
		assert(false);
		break;
	}
}

void ActalogicCell::ClearLink(ActalogicCellDirection dir)
{
	m_pLinkedCells[dir] = nullptr;
}

int ActalogicCell::GetDistanceToLink(ActalogicCellDirection dir)
{
	if (m_pLinkedCells[dir] == nullptr)
	{
		return 0;
	}

	switch (dir)
	{
	case ActalogicCellDirection::RIGHT:
		return (m_pLinkedCells[ActalogicCellDirection::RIGHT])->GetPosition().x - m_position.x;
		break;
	case ActalogicCellDirection::DOWN:
		return (m_pLinkedCells[ActalogicCellDirection::DOWN])->GetPosition().y - m_position.y;
		break;
	case ActalogicCellDirection::LEFT:
		return m_position.x - (m_pLinkedCells[ActalogicCellDirection::LEFT])->GetPosition().x;
		break;
	case ActalogicCellDirection::UP:
		return m_position.y - (m_pLinkedCells[ActalogicCellDirection::UP])->GetPosition().y;
		break;
	default:
		assert(false);
		break;
	}

	return 0;
}

bool ActalogicCell::IsRemovable()
{
	return m_isRemovable;
}

