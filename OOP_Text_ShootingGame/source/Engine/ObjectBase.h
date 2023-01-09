#pragma once

#include "ObjectManager.h"
#include "SceneBase.h"

class Renderer;
class SceneBase;
class Sprite;

class ObjectBase
{
	friend class ObjectManager;
	friend void SceneBase::AddObject(ObjectBase* obj);
public:
	ObjectBase(int objectType);
	virtual ~ObjectBase();

	virtual void Update() = 0;
	virtual void Render(Renderer* renderer) = 0;

	int GetObjectType() { return m_ObjectType; }

	void SetRelease() { m_bRelease = true; }
	bool IsRelease() { return m_bRelease; }
	bool IsCollision(ObjectBase* other);

	virtual void OnCollision(ObjectBase* other) {}


protected:
	SceneBase* m_Scene = nullptr;
	Sprite* m_Sprite = nullptr;
	int m_ObjectType;
	int m_X = 0;
	int m_Y = 0;
	bool m_bRelease = false;

private:
};

