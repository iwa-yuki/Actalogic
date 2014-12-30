#include "pch.h"
#include "InputHelper.h"

tstring InputHelper::INPUT_ESCAPE = _T("escape");
tstring InputHelper::INPUT_SELECT = _T("select");
tstring InputHelper::INPUT_UP = _T("up");
tstring InputHelper::INPUT_DOWN = _T("down");
tstring InputHelper::INPUT_RIGHT = _T("right");
tstring InputHelper::INPUT_LEFT = _T("left");

InputHelper::InputHelper()
{
	m_pKeyState = new BYTE[256];

	SetKeyConfig(INPUT_ESCAPE, VK_ESCAPE);
	SetKeyConfig(INPUT_SELECT, 'Z');
	SetKeyConfig(INPUT_UP, VK_UP);
	SetKeyConfig(INPUT_DOWN, VK_DOWN);
	SetKeyConfig(INPUT_RIGHT, VK_RIGHT);
	SetKeyConfig(INPUT_LEFT, VK_LEFT);
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