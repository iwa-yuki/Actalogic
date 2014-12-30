#pragma once
#include "pch.h"
#include "D2D1Manager.h"
#include "InputHelper.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	// �f�o�C�X��ˑ����\�[�X�̏�����
	HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);

	// �f�o�C�X�ˑ������[�X�̏�����
	HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);

	// �f�o�C�X�ˑ����\�[�X�̊J��
	void OnDiscardDeviceResources();

	// ���ׂẴ��\�[�X�̊J��
	void OnDiscardAllResources();


	// �����_�����O�O����
	void OnPreRender(InputHelper *pInputHelper);

	// �����_�����O����
	void OnRender(D2D1Manager *pD2D1Manager);

	// �����_�����O�㏈��
	void OnPostRender();
};
