#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// ã•ûŒü‚É‚ ‚éƒZƒ‹‚ÆÚ‘±‚·‚éƒƒCƒ„
class EntityWireUp :
	public EntityActalogicCell
{
public:
	EntityWireUp();
	EntityWireUp(const POINT &pt, bool removable = false);

	virtual ~EntityWireUp();

	void OnPreRender(InputHelper *pInputHelper);
};

