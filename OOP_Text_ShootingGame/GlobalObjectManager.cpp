#include "stdafx.h"
#include "GlobalObjectManager.h"

#include "ObjectBase.h"

void GlobalObjectManager::Update()
{
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Update();
	}
}

void GlobalObjectManager::Render()
{
	// TODO: Render�� const�� ���� ����?
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render();
	}
}
