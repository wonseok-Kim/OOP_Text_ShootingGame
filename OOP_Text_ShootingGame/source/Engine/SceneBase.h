#pragma once

#include "ObjectManager.h"

class Renderer;

class SceneBase
{
public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

	virtual void Update() = 0;
	virtual void Render(Renderer* renderer) = 0;

	void AddObject(ObjectBase* obj) { m_ObjectManager.AddObject(obj); }

protected:
	ObjectManager m_ObjectManager;
	DWORD m_FramesCount = 0;
};

