#pragma once
#include "pch.h"

class D2D1Manager
{
public:
	D2D1Manager();
	~D2D1Manager();

	// �f�o�C�X��ˑ��̃��\�[�X���쐬����
	HRESULT CreateDeviceIndependentResources();

	// �f�o�C�X�ˑ��̃��\�[�X���쐬����
	HRESULT CreateDeviceResources(HWND hWnd);

	// �f�o�C�X�ˑ��̃��\�[�X���J������
	void DiscardDeviceResources();

	// ���\�[�X�����ׂĊJ������
	void DiscardAllResources();

public:
	// �`��J�n
	void BeginDraw();

	// �`��I��
	HRESULT EndDraw();

	// �f�X�N�g�b�vDPI���擾
	void GetDesktopDpi(FLOAT *dpiX, FLOAT *dpiY);

	// �����_�[�^�[�Q�b�g�̃T�C�Y���擾
	D2D1_SIZE_F GetRenderTargetSize();

	// DirectWrite�e�L�X�g�t�H�[�}�b�g���쐬
	HRESULT CreateTextFormat(const TCHAR *fontFamilyName, IDWriteFontCollection *fontCollection,
		DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch,
		FLOAT fontSize, const TCHAR *localeName, IDWriteTextFormat ** textFormat);

	// SolidColorBrush���쐬
	HRESULT CreateSolidColorBrush(const D2D1_COLOR_F &colorF, ID2D1SolidColorBrush **ppBrush);

	// PathGeometry���쐬
	HRESULT CreatePathGeometry(ID2D1PathGeometry **ppGeometry);

	// �e�L�X�g��`��
	void DrawText(const TCHAR *text, UINT32 textLength, IDWriteTextFormat *pTextFormat,
		const D2D1_RECT_F &rc, ID2D1Brush *pBrush);

	// �摜�t�@�C�������[�h
	HRESULT LoadBitmapFromFile(LPTSTR uri, ID2D1Bitmap **ppBitmap);

	// �摜��`��
	void DrawBitmap(ID2D1Bitmap *pBitmap, const D2D1_RECT_F &destRect,
		FLOAT opacity, D2D1_BITMAP_INTERPOLATION_MODE interpolationMode, const D2D1_RECT_F &srcRect);

	// ������`��
	void DrawLine(D2D1_POINT_2F point0, D2D1_POINT_2F point1, ID2D1Brush *pBrush, FLOAT width = 1.0F);

	// ��`��`��
	void DrawRectangle(const D2D1_RECT_F &rc, ID2D1Brush *pBrush, FLOAT width = 1.0F);

private:
	ID2D1Factory* m_pDirect2dFactory;
	IDWriteFactory* m_pDWriteFactory;
	IWICImagingFactory* m_pIWICFactory;

	ID2D1HwndRenderTarget* m_pRenderTarget;

	D2D1_COLOR_F m_backgroundColor;
};

