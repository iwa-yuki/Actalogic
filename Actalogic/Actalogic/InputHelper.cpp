#include "pch.h"
#include "InputHelper.h"

tstring InputHelper::INPUT_ESCAPE = _T("escape");

InputHelper::InputHelper()
{
	m_pKeyState = new BYTE[256];

	SetKeyConfig(INPUT_ESCAPE, VK_ESCAPE);
}


InputHelper::~InputHelper()
{
	delete[] m_pKeyState;
}

void InputHelper::OnTick()
{
	GetKeyboardState(m_pKeyState);
}

void InputHelper::SetKeyConfig(tstring key, int nVirtKey)
{
	m_keyConfigMap.emplace(key, nVirtKey);
}

bool InputHelper::GetKeyState(const tstring &key)
{
	if (m_keyConfigMap.count(key))
	{
		int nVirtKey = m_keyConfigMap[key];

		return (m_pKeyState[nVirtKey] & 0x80) == 0x80;
	}

	return false;
}