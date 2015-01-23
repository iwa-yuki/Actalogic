#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// ‰º•ûŒü‚É‚ ‚éƒZƒ‹‚ÆÚ‘±‚·‚éƒƒCƒ„
class EntityWireDown :
	public EntityActalogicCell
{
public:
	EntityWireDown();
	EntityWireDown(const POINT &pt, bool removable = false);

	virtual ~EntityWireDown();

	void OnPreRender(InputHelper *pInputHelper);
};

