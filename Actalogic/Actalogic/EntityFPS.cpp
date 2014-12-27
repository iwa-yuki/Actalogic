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

HRESULT EntityFPS::OnCreateDeviceIndependentResources()
{
	m_prevTime = std::chrono::system_clock::now();

	return S_OK;
}

void EntityFPS::OnPreRender()
{
	++m_counter;

	CHRONO_SYSTEM_TIME nowTime = std::chrono::system_clock::now();

	auto duration = nowTime - m_prevTime;
	long long duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
	if (duration_ms >= 1000)
	{
		m_fps = ((float)m_counter * 1000.0F) / duration_ms;
		m_counter = 0;
		m_prevTime = nowTime;

#ifdef _DEBUG
		{
			TCHAR c[256];
			_stprintf_s(c, 256, _T("FPS = %f\n"), m_fps);
			OutputDebugString(c);
		}
#endif
	}
}