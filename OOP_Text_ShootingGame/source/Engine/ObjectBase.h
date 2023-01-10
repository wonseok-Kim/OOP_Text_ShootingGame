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
	static void Destroy(ObjectBase* obj, DWORD framesToDelayDestruction = 0);

	ObjectBase(int objectType);
	virtual ~ObjectBase();

	virtual void Update() = 0;
	virtual void Render(Renderer* renderer) = 0;

	int GetObjectType() { return m_ObjectType; }

	bool IsCollision(ObjectBase* other);
	virtual void OnCollision(ObjectBase* other) {}

	virtual bool IsDestroying() { return m_bRelease; }
	virtual void OnDestroy() {}

protected:
	SceneBase* m_Scene = nullptr;
	Sprite* m_Sprite = nullptr;
	bool m_bVisible = true;
	int m_ObjectType;
	int m_X = 0;
	int m_Y = 0;
	DWORD m_DestroyDelayFrame = 0;
	DWORD m_DestroyFrame = 0;

private:
	bool m_bRelease = false;
};

