#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// �������ɂ���Z���Ɛڑ����郏�C��
class EntityWireDown :
	public EntityActalogicCell
{
public:
	EntityWireDown();
	EntityWireDown(const POINT &pt, bool removable = false);

	virtual ~EntityWireDown();

	void OnPreRender(InputHelper *pInputHelper);
};

