#pragma once
#include "pch.h"
#include "Entity.h"

enum ActalogicCellType : int
{
	CELL_BUFFER,
	CELL_NOR,
	CELL_NAND,
	CELL_INPUT,
	CELL_OUTPUT,
	WIRE_UP,
	WIRE_DOWN,
	WIRE_RIGHT,
	WIRE_LEFT,
};

enum ActalogicCellDirection : int
{
	RIGHT = 0,
	DOWN = 1,
	LEFT = 2,
	UP = 3,
};

class ActalogicCell : Entity
{
public:
	ActalogicCell();
	ActalogicCell(const POINT &pt,
		ActalogicCellType type = ActalogicCellType::CELL_BUFFER,
		bool removable = false);
	virtual ~ActalogicCell();

	ActalogicCellType GetType();
	POINT GetPosition();
	void SetPosition(const POINT &pt);
	void SetLink(ActalogicCellDirection dir, ActalogicCell *pCell);
	void ClearLink(ActalogicCellDirection dir);
	int GetDistanceToLink(ActalogicCellDirection dir);
	bool IsRemovable();

private:
	ActalogicCellType m_type;
	POINT m_position;
	bool m_isRemovable;

	ActalogicCell* m_pLinkedCells[4];
};

