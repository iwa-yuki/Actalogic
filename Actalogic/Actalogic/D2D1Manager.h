#pragma once
#include "pch.h"

class D2D1Manager
{
public:
	D2D1Manager();
	~D2D1Manager();

	// Direct2Dを使うための準備を行う
	HRESULT Initialize();
};

