#include "pch.h"
#include "EntityWireUp.h"


EntityWireUp::EntityWireUp() :
EntityWireUp({ 0, 0 })
{
}

EntityWireUp::EntityWireUp(const POINT &pt, bool removable) :
EntityActalogicCell(pt, ActalogicCellType::WIRE_UP, removable)
{
}

EntityWireUp::~EntityWireUp()
{
}

void EntityWireUp::OnPreRender(InputHelper *pInputHelper)
{
	EntityActalogicCell::OnPreRender(pInputHelper);

	m_postValue = m_pLinkedCells[ActalogicCellDirection::DOWN] == nullptr ? 0 :
		m_pLinkedCells[ActalogicCellDirection::DOWN]->GetValue();
}
