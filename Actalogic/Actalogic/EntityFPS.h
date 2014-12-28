#pragma once
#include "pch.h"
#include "Entity.h"

// FPSの計算を行う
class EntityFPS :
	public Entity
{
public:
	EntityFPS();
	virtual ~EntityFPS();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	void OnPreRender();

private:
	CHRONO_SYSTEM_TIME m_prevTime;
	int m_counter;
	float m_fps;

public:
	float GetFPS();
};

