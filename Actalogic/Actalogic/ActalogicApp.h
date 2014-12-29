#pragma once
#include "pch.h"
#include "D2D1Manager.h"
#include "EntityFPS.h"
#include "EntityDebugInfoLayer.h"
#include "InputHelper.h"

// Actalogicアプリケーション
// ウィンドウ作成、メッセージループ処理を行います。
class ActalogicApp
{
	friend class EntityDebugInfoLayer;

public:
	ActalogicApp();
	~ActalogicApp();

	// アプリケーションを初期化する
	HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);

	// アプリケーションを実行する
	int Run();

	// アプリケーションを開放する
	void Dispose();

private:
	// ウィンドウを初期化する
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, FLOAT width, FLOAT height);

	// ゲームループ毎に呼ばれる
	void OnTick();

	// 描画を行う前に呼ばれる
	void OnPreRender();

	// 描画を行う必要がある際に呼ばれる
	void OnRender();

	// 描画を行った後に呼ばれる
	void OnPostRender();

	// ウィンドウサイズが変更されたときに呼ばれる
	void OnResize(WORD width, WORD height, BOOL isActive);

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	D2D1Manager m_d2d1Manager;
	BOOL m_isActive;

	EntityFPS m_entityFPS;
	EntityDebugInfoLayer m_entityDebugInfoLayer;

	InputHelper m_inputHelper;

private:
	static TCHAR m_szWindowClass[];
	static TCHAR m_szTitle[];

public:
	// Windowsプロシージャ
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// クライアントウィンドウの大きさを指定してサイズ変更
	static VOID SetClientSize(HWND hWnd, LONG sx, LONG sy);
};

