#pragma once
#include "pch.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	HRESULT OnCreateDeviceIndependentResources();
	HRESULT OnCreateDeviceResources();
	void OnDiscardDeviceResources();

	void OnPreRender();
	void OnRender();
	void OnPostRender();
};
