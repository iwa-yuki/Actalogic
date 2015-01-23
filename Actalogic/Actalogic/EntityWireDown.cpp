#include "pch.h"
#include "EntityWireDown.h"


EntityWireDown::EntityWireDown() :
EntityWireDown({ 0, 0 })
{
}

EntityWireDown::EntityWireDown(const POINT &pt, bool removable) :
EntityActalogicCell(pt, ActalogicCellType::WIRE_DOWN, removable)
{
}

EntityWireDown::~EntityWireDown()
{
}

void EntityWireDown::OnPreRender(InputHelper *pInputHelper)
{
	EntityActalogicCell::OnPreRender(pInputHelper);

	m_postValue = m_pLinkedCells[ActalogicCellDirection::UP] == nullptr ? 0 :
		m_pLinkedCells[ActalogicCellDirection::UP]->GetValue();
}
