#include "pch.h"
#include "Entity.h"


Entity::Entity()
{
}


Entity::~Entity()
{
	OnDiscardDeviceResources();
}

HRESULT Entity::OnCreateDeviceIndependentResources()
{
	return S_OK;
}

HRESULT Entity::OnCreateDeviceResources()
{
	return S_OK;
}

void Entity::OnDiscardDeviceResources()
{

}

void Entity::OnPreRender()
{

}

void Entity::OnRender()
{

}

void Entity::OnPostRender()
{

}
