#include "pch.h"
#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
}

HRESULT Entity::OnCreateDeviceIndependentResources(D2D1Manager *pD2D1Manager)
{
	return S_OK;
}

HRESULT Entity::OnCreateDeviceResources(D2D1Manager *pD2D1Manager)
{
	return S_OK;
}

void Entity::OnDiscardDeviceResources()
{

}

void Entity::OnDiscardAllResources()
{
	OnDiscardDeviceResources();
}

void Entity::OnPreRender(InputHelper *pInputHelper)
{

}

void Entity::OnRender(D2D1Manager *pD2D1Manager)
{

}

void Entity::OnPostRender()
{

}