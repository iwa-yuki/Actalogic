#include "pch.h"
#include "EntityFPS.h"


EntityFPS::EntityFPS():
m_prevTime(),
m_counter(0),
m_fps(0.0F)
{
}


EntityFPS::~EntityFPS()
{
}

HRESULT EntityFPS::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	m_prevTime = std::chrono::system_clock::now();

	return S_OK;
}

void EntityFPS::OnPreRender(InputHelper *pInputHelper)
{
	++m_counter;

	CHRONO_SYSTEM_TIME nowTime = std::chrono::system_clock::now();

	auto duration = nowTime - m_prevTime;
	long long duration_us = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
	if (duration_us >= std::chrono::microseconds::period::den)
	{
		m_fps = ((float)m_counter * std::chrono::microseconds::period::den) / duration_us;
		m_counter = 0;
		m_prevTime = nowTime;

#ifdef _NO_USE
		{
			TCHAR c[256];
			_stprintf_s(c, 256, _T("FPS = %f\n"), m_fps);
			OutputDebugString(c);
		}
#endif
	}
}

float EntityFPS::GetFPS()
{
	return m_fps;
}
