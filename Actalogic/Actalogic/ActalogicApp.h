#pragma once
#include "pch.h"

class ActalogicApp
{
public:
	ActalogicApp();
	~ActalogicApp();

	// アプリケーションを初期化する
	HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);

	// アプリケーションを実行する
	int Run();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;

private:
	static TCHAR m_szWindowClass[];
	static TCHAR m_szTitle[];

public:
	// Windowsプロシージャ
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// クライアントウィンドウの大きさを指定してサイズ変更
	static VOID SetClientSize(HWND hWnd, LONG sx, LONG sy);
};

