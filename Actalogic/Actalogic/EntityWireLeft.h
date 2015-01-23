#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// ¶•ûŒü‚É‚ ‚éƒZƒ‹‚ÆÚ‘±‚·‚éƒƒCƒ„
class EntityWireLeft :
	public EntityActalogicCell
{
public:
	EntityWireLeft();
	EntityWireLeft(const POINT &pt, bool removable = false);

	virtual ~EntityWireLeft();

	void OnPreRender(InputHelper *pInputHelper);
};

