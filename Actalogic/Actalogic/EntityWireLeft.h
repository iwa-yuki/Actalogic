#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// 左方向にあるセルと接続するワイヤ
class EntityWireLeft :
	public EntityActalogicCell
{
public:
	EntityWireLeft();
	EntityWireLeft(const POINT &pt, bool removable = false);

	virtual ~EntityWireLeft();

	void OnPreRender(InputHelper *pInputHelper);
};

