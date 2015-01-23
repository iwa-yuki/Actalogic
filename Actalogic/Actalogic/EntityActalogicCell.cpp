#include "pch.h"
#include "EntityActalogicCell.h"

EntityActalogicCell::EntityActalogicCell() :
EntityActalogicCell({ 0, 0 })
{
}

EntityActalogicCell::EntityActalogicCell(const POINT &pt,
	ActalogicCellType type, bool removable) :
m_type(type),
m_position(pt),
m_isRemovable(removable),
m_count(0)
{
	m_pLinkedCells[ActalogicCellDirection::RIGHT] = nullptr;
	m_pLinkedCells[ActalogicCellDirection::DOWN] = nullptr;
	m_pLinkedCells[ActalogicCellDirection::LEFT] = nullptr;
	m_pLinkedCells[ActalogicCellDirection::UP] = nullptr;

	m_prevValue.assign(16, 0);
}

EntityActalogicCell::~EntityActalogicCell()
{
}

void EntityActalogicCell::OnPreRender(InputHelper *pInputHelper)
{
	switch (m_type)
	{
	case CELL_BUFFER:
	{
		int val = 0;
		int pos = 0;
		int neg = 0;
		if (m_pLinkedCells[ActalogicCellDirection::DOWN] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::DOWN]->GetType() == ActalogicCellType::WIRE_UP)
		{
			val = m_pLinkedCells[ActalogicCellDirection::DOWN]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::DOWN));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::UP] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::UP]->GetType() == ActalogicCellType::WIRE_DOWN)
		{
			val = m_pLinkedCells[ActalogicCellDirection::UP]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::UP));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::RIGHT] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetType() == ActalogicCellType::WIRE_LEFT)
		{
			val = m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::RIGHT));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::LEFT] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::LEFT]->GetType() == ActalogicCellType::WIRE_RIGHT)
		{
			val = m_pLinkedCells[ActalogicCellDirection::LEFT]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::LEFT));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}

		if (pos > 0 && neg == 0)
		{
			m_postValue = 1;
		}
		else if (pos == 0 && neg > 0)
		{
			m_postValue = -1;
		}
		else
		{
			m_postValue = 0;
		}
		break;
	}
	case CELL_NOR:
	{
		int val = 0;
		int pos = 0;
		int neg = 0;
		if (m_pLinkedCells[ActalogicCellDirection::DOWN] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::DOWN]->GetType() == ActalogicCellType::WIRE_UP)
		{
			val = m_pLinkedCells[ActalogicCellDirection::DOWN]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::DOWN));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::UP] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::UP]->GetType() == ActalogicCellType::WIRE_DOWN)
		{
			val = m_pLinkedCells[ActalogicCellDirection::UP]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::UP));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::RIGHT] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetType() == ActalogicCellType::WIRE_LEFT)
		{
			val = m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::RIGHT));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::LEFT] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::LEFT]->GetType() == ActalogicCellType::WIRE_RIGHT)
		{
			val = m_pLinkedCells[ActalogicCellDirection::LEFT]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::LEFT));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}

		if (pos == 0 && neg > 0)
		{
			m_postValue = 1;
		}
		else if (pos == 0 && neg == 0)
		{
			m_postValue = 0;
		}
		else
		{
			m_postValue = -1;
		}
		break;
	}
	case CELL_NAND:
	{
		int val = 0;
		int pos = 0;
		int neg = 0;
		if (m_pLinkedCells[ActalogicCellDirection::DOWN] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::DOWN]->GetType() == ActalogicCellType::WIRE_UP)
		{
			val = m_pLinkedCells[ActalogicCellDirection::DOWN]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::DOWN));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::UP] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::UP]->GetType() == ActalogicCellType::WIRE_DOWN)
		{
			val = m_pLinkedCells[ActalogicCellDirection::UP]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::UP));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::RIGHT] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetType() == ActalogicCellType::WIRE_LEFT)
		{
			val = m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::RIGHT));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}
		if (m_pLinkedCells[ActalogicCellDirection::LEFT] != nullptr
			&& m_pLinkedCells[ActalogicCellDirection::LEFT]->GetType() == ActalogicCellType::WIRE_RIGHT)
		{
			val = m_pLinkedCells[ActalogicCellDirection::LEFT]->GetValue(
				GetDistanceToLink(ActalogicCellDirection::LEFT));
			if (val > 0){ ++pos; }
			else if (val < 0){ ++neg; }
		}

		if (pos > 0 && neg == 0)
		{
			m_postValue = -1;
		}
		else if (pos == 0 && neg == 0)
		{
			m_postValue = 0;
		}
		else
		{
			m_postValue = 1;
		}
		break;
	}
	case CELL_INPUT:
		m_postValue = (m_count / 60) % 2 == 1 ? 1 : -1;
		break;
	case CELL_OUTPUT:
		break;
	case WIRE_UP:
		m_postValue = m_pLinkedCells[ActalogicCellDirection::DOWN] == nullptr ? 0 :
			m_pLinkedCells[ActalogicCellDirection::DOWN]->GetValue();
		break;
	case WIRE_DOWN:
		m_postValue = m_pLinkedCells[ActalogicCellDirection::UP] == nullptr ? 0 :
			m_pLinkedCells[ActalogicCellDirection::UP]->GetValue();
		break;
	case WIRE_RIGHT:
		m_postValue = m_pLinkedCells[ActalogicCellDirection::LEFT] == nullptr ? 0 :
			m_pLinkedCells[ActalogicCellDirection::LEFT]->GetValue();
		break;
	case WIRE_LEFT:
		m_postValue = m_pLinkedCells[ActalogicCellDirection::RIGHT] == nullptr ? 0 :
			m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetValue();
		break;
	default:
		assert(false);
		break;
	}
	++m_count;
}

void EntityActalogicCell::OnPostRender()
{
	m_prevValue.push_front(m_currentValue);
	while (m_prevValue.size() > 16)
	{
		m_prevValue.pop_back();
	}
	m_currentValue = m_postValue;
}


ActalogicCellType EntityActalogicCell::GetType()
{
	return m_type;
}

POINT EntityActalogicCell::GetPosition()
{
	return m_position;
}

void EntityActalogicCell::SetPosition(const POINT &pt)
{
	m_position = pt;
}

void EntityActalogicCell::SetLink(ActalogicCellDirection dir, EntityActalogicCell *pCell)
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

void EntityActalogicCell::ClearLink(ActalogicCellDirection dir)
{
	m_pLinkedCells[dir] = nullptr;
}

int EntityActalogicCell::GetDistanceToLink(ActalogicCellDirection dir)
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

bool EntityActalogicCell::IsRemovable()
{
	return m_isRemovable;
}

int EntityActalogicCell::GetValue(int index)
{
	if (index == 0)
	{
		return m_currentValue;
	}
	return m_prevValue.at(index - 1);
}
