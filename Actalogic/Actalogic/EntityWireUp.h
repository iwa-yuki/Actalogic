#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// ������ɂ���Z���Ɛڑ����郏�C��
class EntityWireUp :
	public EntityActalogicCell
{
public:
	EntityWireUp();
	EntityWireUp(const POINT &pt, bool removable = false);

	virtual ~EntityWireUp();

	void OnPreRender(InputHelper *pInputHelper);
};

