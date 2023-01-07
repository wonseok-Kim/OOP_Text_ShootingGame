#pragma once

#include "ObjectList.h"

class Renderer;

class GlobalObjectManager
{
public:
	static GlobalObjectManager* Instance()
	{
		static GlobalObjectManager inst;
		return &inst;
	}

	~GlobalObjectManager();

	void Update();
	void Render(Renderer* renderer);

private:
	GlobalObjectManager() = default;

private:
	ObjectList m_ObjectList;
};

