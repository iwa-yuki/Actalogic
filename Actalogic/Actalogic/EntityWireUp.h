#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// 上方向にあるセルと接続するワイヤ
class EntityWireUp :
	public EntityActalogicCell
{
public:
	EntityWireUp();
	EntityWireUp(const POINT &pt, bool removable = false);

	virtual ~EntityWireUp();

	void OnPreRender(InputHelper *pInputHelper);
};

