#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// �E�����ɂ���Z���Ɛڑ����郏�C��
class EntityWireRight :
	public EntityActalogicCell
{
public:
	EntityWireRight();
	EntityWireRight(const POINT &pt, bool removable = false);

	virtual ~EntityWireRight();

	void OnPreRender(InputHelper *pInputHelper);
};

