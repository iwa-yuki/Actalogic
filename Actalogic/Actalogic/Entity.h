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
	virtual HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);

	// �f�o�C�X�ˑ������[�X�̏�����
	virtual HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);

	// �f�o�C�X�ˑ����\�[�X�̊J��
	virtual void OnDiscardDeviceResources();

	// ���ׂẴ��\�[�X�̊J��
	virtual void OnDiscardAllResources();


	// �����_�����O�O����
	virtual void OnPreRender(InputHelper *pInputHelper);

	// �����_�����O����
	virtual void OnRender(D2D1Manager *pD2D1Manager);

	// �����_�����O�㏈��
	virtual void OnPostRender();
};
