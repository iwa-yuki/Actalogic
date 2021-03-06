#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// 右方向にあるセルと接続するワイヤ
class EntityWireRight :
	public EntityActalogicCell
{
public:
	EntityWireRight();
	EntityWireRight(const POINT &pt, bool removable = false);

	virtual ~EntityWireRight();

	void OnPreRender(InputHelper *pInputHelper);
};

