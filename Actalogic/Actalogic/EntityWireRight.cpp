#include "pch.h"
#include "EntityWireRight.h"


EntityWireRight::EntityWireRight() :
EntityWireRight({ 0, 0 })
{
}

EntityWireRight::EntityWireRight(const POINT &pt, bool removable) :
EntityActalogicCell(pt, ActalogicCellType::WIRE_RIGHT, removable)
{
}

EntityWireRight::~EntityWireRight()
{
}

void EntityWireRight::OnPreRender(InputHelper *pInputHelper)
{
	EntityActalogicCell::OnPreRender(pInputHelper);

	m_postValue = m_pLinkedCells[ActalogicCellDirection::LEFT] == nullptr ? 0 :
		m_pLinkedCells[ActalogicCellDirection::LEFT]->GetValue();
}
