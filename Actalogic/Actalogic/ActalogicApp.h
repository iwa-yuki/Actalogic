#pragma once
#include "pch.h"

class ActalogicApp
{
public:
	ActalogicApp();
	~ActalogicApp();

	// �A�v���P�[�V����������������
	HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);

	// �A�v���P�[�V���������s����
	int Run();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

private:
	static TCHAR m_szWindowClass[];
	static TCHAR m_szTitle[];

public:
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
};

