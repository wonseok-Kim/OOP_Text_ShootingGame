#pragma once

#include "ObjectList.h"

class SceneBase
{
public:
	SceneBase() = default;
	virtual ~SceneBase() = default;

	virtual void Update() = 0;
	virtual void Render() = 0;

protected:
	ObjectList m_ObjectList;
};

