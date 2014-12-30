#pragma once
#include "pch.h"
#include "Entity.h"
#include "InputHelper.h"

// FPS‚ÌŒvZ‚ğs‚¤
class EntityFPS :
	public Entity
{
public:
	EntityFPS();
	virtual ~EntityFPS();

	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);
	void OnPreRender(InputHelper *pInputHelper);

private:
	CHRONO_SYSTEM_TIME m_prevTime;
	int m_counter;
	float m_fps;

public:
	float GetFPS();
};

