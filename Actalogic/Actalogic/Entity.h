#pragma once
#include "pch.h"
#include "D2D1Manager.h"
#include "InputHelper.h"

class Entity
{
public:
	Entity();
	virtual ~Entity();

	// デバイス非依存リソースの初期化
	virtual HRESULT OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager);

	// デバイス依存リロースの初期化
	virtual HRESULT OnCreateDeviceResources(D2D1Manager *pD2D1Manager);

	// デバイス依存リソースの開放
	virtual void OnDiscardDeviceResources();

	// すべてのリソースの開放
	virtual void OnDiscardAllResources();


	// レンダリング前処理
	virtual void OnPreRender(InputHelper *pInputHelper);

	// レンダリング処理
	virtual void OnRender(D2D1Manager *pD2D1Manager);

	// レンダリング後処理
	virtual void OnPostRender();
};
