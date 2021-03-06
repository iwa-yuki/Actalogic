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

class EntityActalogicCell : Entity
{
public:
	EntityActalogicCell();
	EntityActalogicCell(const POINT &pt,
		ActalogicCellType type = ActalogicCellType::CELL_BUFFER,
		bool removable = false);
	virtual ~EntityActalogicCell();

	virtual void OnPreRender(InputHelper *pInputHelper);
	virtual void OnPostRender();

	ActalogicCellType GetType();
	POINT GetPosition();
	void SetPosition(const POINT &pt);
	void SetLink(ActalogicCellDirection dir, EntityActalogicCell *pCell);
	void ClearLink(ActalogicCellDirection dir);
	int GetDistanceToLink(ActalogicCellDirection dir);
	bool IsRemovable();
	int GetValue(int index = 0);

protected:
	ActalogicCellType m_type;
	POINT m_position;
	bool m_isRemovable;

	int m_currentValue;
	int m_postValue;
	std::deque<int> m_prevValue;

	int m_count;

	EntityActalogicCell* m_pLinkedCells[4];
};

