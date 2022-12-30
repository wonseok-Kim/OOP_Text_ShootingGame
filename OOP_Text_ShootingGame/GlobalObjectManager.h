#pragma once

#include "ObjectList.h"

class GlobalObjectManager
{
public:
	static GlobalObjectManager& Instance()
	{
		static GlobalObjectManager inst;
		return inst;
	}

	~GlobalObjectManager()
	{
		for (ObjectBase* obj : m_ObjectList)
			delete obj;
	}

	void Update();
	void Render();

private:
	GlobalObjectManager() = default;

private:
	ObjectList m_ObjectList;
};

