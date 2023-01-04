#pragma once

#include "ObjectList.h"

class Renderer;

class SceneBase
{
public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

	virtual void Update() = 0;
	virtual void Render(Renderer* renderer) = 0;

protected:
	ObjectList m_ObjectList;
};

