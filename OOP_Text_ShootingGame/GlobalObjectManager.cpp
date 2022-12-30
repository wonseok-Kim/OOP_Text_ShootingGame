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
	// TODO: Render는 const가 맞을 지도?
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render();
	}
}
