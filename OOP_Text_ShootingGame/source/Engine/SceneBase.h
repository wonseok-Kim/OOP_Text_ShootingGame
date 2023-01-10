#pragma once

#include "ObjectManager.h"
#include "SceneManager.h"

class ObjectBase;
class Renderer;

class SceneBase
{
	friend class SceneManager;

public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

	virtual void Update() = 0;
	virtual void Render(Renderer* renderer) = 0;

	virtual bool OnInit() { return true; }

	DWORD GetFrames() { return m_FramesCount; }

	void AddObject(ObjectBase* obj);

protected:
private:
	DWORD m_FramesCount = 0;
	ObjectManager m_ObjectManager;
};

