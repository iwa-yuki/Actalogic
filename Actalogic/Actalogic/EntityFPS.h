#pragma once
#include "pch.h"
#include "Entity.h"

class EntityFPS :
	public Entity
{
public:
	EntityFPS();
	virtual ~EntityFPS();

	HRESULT OnCreateDeviceIndependentResources();
	void OnPreRender();

private:
	CHRONO_SYSTEM_TIME m_prevTime;
	int m_counter;
	float m_fps;
};

