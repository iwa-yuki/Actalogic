#pragma once
#include "pch.h"

class D2D1Manager
{
public:
	D2D1Manager();
	~D2D1Manager();

	// �f�o�C�X��ˑ��̃��\�[�X���쐬����
	// (�J���͂��̃C���X�^���X���j�������Ƃ������ōs����)
	HRESULT CreateDeviceIndependentResources();

	// �f�o�C�X�ˑ��̃��\�[�X���쐬����
	HRESULT CreateDeviceResources(HWND hWnd);

	// �f�o�C�X�ˑ��̃��\�[�X���J������
	void DiscardDeviceResources();

public:
	// �`��J�n
	void BeginDraw();

	// �`��I��
	HRESULT EndDraw();

	// Direct2DFactory���擾
	ID2D1Factory* GetD2D1Factory();

	// DirectWriteFactory���擾
	IDWriteFactory* GetDWriteFactory();

	// RenderTarget���擾
	ID2D1HwndRenderTarget* GetRenderTarget();

private:
	ID2D1Factory* m_pDirect2dFactory;
	IDWriteFactory* m_pDWriteFactory;

	ID2D1HwndRenderTarget* m_pRenderTarget;

	D2D1_COLOR_F m_backgroundColor;
};

