#pragma once
#include "pch.h"
#include "D2D1Manager.h"
#include "EntityFPS.h"
#include "EntityDebugInfoLayer.h"
#include "InputHelper.h"

// Actalogic�A�v���P�[�V����
// �E�B���h�E�쐬�A���b�Z�[�W���[�v�������s���܂��B
class ActalogicApp
{
	friend class EntityDebugInfoLayer;

public:
	ActalogicApp();
	~ActalogicApp();

	// �A�v���P�[�V����������������
	HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);

	// �A�v���P�[�V���������s����
	int Run();

	// �A�v���P�[�V�������J������
	void Dispose();

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

	// �E�B���h�E�T�C�Y���ύX���ꂽ�Ƃ��ɌĂ΂��
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
	// Windows�v���V�[�W��
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	// �N���C�A���g�E�B���h�E�̑傫�����w�肵�ăT�C�Y�ύX
	static VOID SetClientSize(HWND hWnd, LONG sx, LONG sy);
};

