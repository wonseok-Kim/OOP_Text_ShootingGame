#pragma once

class Renderer;
class SceneBase;
class Sprite;

class ObjectBase
{
public:
	ObjectBase(SceneBase* sceneOrNull, Sprite* spriteOrNull, int objectType, int x, int y);
	virtual ~ObjectBase();

	virtual void Update(DWORD framesCount) = 0;
	virtual void Render(Renderer* renderer) = 0;

	int GetObjectType() { return m_ObjectType; }

	void SetRelease() { m_bRelease = true; }
	bool IsRelease() { return m_bRelease; }
	bool IsCollision(ObjectBase* other);

	virtual void OnCollision(ObjectBase* other) {}

protected:
	SceneBase* m_Scene;
	Sprite* m_Sprite;
	int m_ObjectType;
	int m_X;
	int m_Y;
	bool m_bRelease = false;

private:
};

