#pragma once
#include "pch.h"
#include "D2D1Manager.h"

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
	// �E�B���h�E������������
	HWND InitializeWindow(HINSTANCE hInstance, int nCmdShow, FLOAT width, FLOAT height);

	// �Q�[�����[�v���ɌĂ΂��
	void OnTick();

	// �`����s���O�ɌĂ΂��
	void OnPreRender();

	// �`����s���K�v������ۂɌĂ΂��
	void OnRender();

	// �`����s������ɌĂ΂��
	void OnPostRender();

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	D2D1Manager m_d2d1Manager;

private:
	static TCHAR m_szWindowClass[];
	static TCHAR m_szTitle[];

public:
	// Windows�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// �N���C�A���g�E�B���h�E�̑傫�����w�肵�ăT�C�Y�ύX
	static VOID SetClientSize(HWND hWnd, LONG sx, LONG sy);
};

