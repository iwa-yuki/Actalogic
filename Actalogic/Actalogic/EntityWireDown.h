#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// 下方向にあるセルと接続するワイヤ
class EntityWireDown :
	public EntityActalogicCell
{
public:
	EntityWireDown();
	EntityWireDown(const POINT &pt, bool removable = false);

	virtual ~EntityWireDown();

	void OnPreRender(InputHelper *pInputHelper);
};

