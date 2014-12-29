#pragma once
#include "pch.h"

class InputHelper
{
public:
	InputHelper();
	~InputHelper();

	void OnTick();

	void SetKeyConfig(tstring key, int nVirtKey);
	bool GetKeyState(const tstring &key);
	
private:
	BYTE *m_pKeyState;
	std::unordered_map<tstring, int> m_keyConfigMap;

public:
	static tstring INPUT_ESCAPE;
};

