#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// �������ɂ���Z���Ɛڑ����郏�C��
class EntityWireLeft :
	public EntityActalogicCell
{
public:
	EntityWireLeft();
	EntityWireLeft(const POINT &pt, bool removable = false);

	virtual ~EntityWireLeft();

	void OnPreRender(InputHelper *pInputHelper);
};

