#pragma once

class Renderer;
class SceneBase;

class ObjectBase
{
public:
	ObjectBase(SceneBase* sceneOrNull, int objectType, int x, int y);
	virtual ~ObjectBase();

	virtual void Update(DWORD framesCount) = 0;
	virtual void Render(Renderer* renderer) = 0;

	int GetObjectType() { return m_ObjectType; }

	bool IsRelease() { return m_bRelease; }

protected:
	SceneBase* m_Scene;
	int m_ObjectType;
	int m_X;
	int m_Y;
	bool m_bRelease = false;

private:
};

