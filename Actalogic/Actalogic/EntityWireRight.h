#pragma once
#include "pch.h"
#include "EntityActalogicCell.h"

// ‰E•ûŒü‚É‚ ‚éƒZƒ‹‚ÆÚ‘±‚·‚éƒƒCƒ„
class EntityWireRight :
	public EntityActalogicCell
{
public:
	EntityWireRight();
	EntityWireRight(const POINT &pt, bool removable = false);

	virtual ~EntityWireRight();

	void OnPreRender(InputHelper *pInputHelper);
};

