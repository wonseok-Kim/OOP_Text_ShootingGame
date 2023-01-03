#include "stdafx.h"
#include "GlobalObjectManager.h"

#include "ObjectBase.h"

GlobalObjectManager::~GlobalObjectManager()
{
	for (ObjectBase* obj : m_ObjectList)
		delete obj;
}

void GlobalObjectManager::Update()
{
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Update();
	}
}

void GlobalObjectManager::Render(Renderer* renderer)
{
	// TODO: Render�� const�� ���� ����?
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render(renderer);
	}
}
