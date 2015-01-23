#include "pch.h"
#include "EntityWireLeft.h"


EntityWireLeft::EntityWireLeft() :
EntityWireLeft({ 0, 0 })
{
}

EntityWireLeft::EntityWireLeft(const POINT &pt, bool removable) :
EntityActalogicCell(pt, ActalogicCellType::WIRE_LEFT, removable)
{
}

EntityWireLeft::~EntityWireLeft()
{
}

void EntityWireLeft::OnPreRender(InputHelper *pInputHelper)
{
	EntityActalogicCell::OnPreRender(pInputHelper);

	m_postValue = m_pLinkedCells[ActalogicCellDirection::RIGHT] == nullptr ? 0 :
		m_pLinkedCells[ActalogicCellDirection::RIGHT]->GetValue();
}
