#include "stdafx.h"
#include "SceneTitle.h"

#include "Input.h"
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
	Input& input = Input::Instance();

	if (input.GetKey(VK_RIGHT).released ||
		input.GetKey(VK_UP).released)
	{
		m_Title->SetState(ObjectTitle::KEY_DOWN);
	}
	if (input.GetKey(VK_LEFT).released ||
		input.GetKey(VK_DOWN).released)
	{
		m_Title->SetState(ObjectTitle::KEY_UP);
	}
	if (input.GetKey(VK_SPACE).released)
	{
		m_Title->SetState(ObjectTitle::KEY_PRESSED);
	}

	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Update();
	}
}

void SceneTitle::Render(Renderer* renderer)
{
	for (ObjectBase* obj : m_ObjectList)
	{
		obj->Render(renderer);
	}
}
