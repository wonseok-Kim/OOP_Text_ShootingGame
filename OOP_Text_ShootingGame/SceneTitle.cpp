#include "stdafx.h"
#include "SceneTitle.h"

#include "ObjectTitle.h"
#include "ObjectBase.h"

SceneTitle::SceneTitle()
	: SceneBase()
{
	m_Title = new ObjectTitle();
	m_ObjectList.push_back(m_Title);
}

SceneTitle::~SceneTitle()
{
	for (ObjectBase* obj : m_ObjectList)
	{
		delete obj;
	}
}

void SceneTitle::Update()
{	
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8001) ||
		(GetAsyncKeyState(VK_DOWN) & 0x8001))
	{
		m_Title->SetState(ObjectTitle::KEY_DOWN);
	}
	if ((GetAsyncKeyState(VK_LEFT) & 0x8001) ||
		(GetAsyncKeyState(VK_UP) & 0x8001))
	{
		m_Title->SetState(ObjectTitle::KEY_UP);
	}
	if ((GetAsyncKeyState(VK_SPACE) & 0x8001))
	{
		m_Title->SetState(ObjectTitle::KEY_PRESSED);
	}

	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Update();
	}
}

void SceneTitle::Render()
{
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render();
	}
}
