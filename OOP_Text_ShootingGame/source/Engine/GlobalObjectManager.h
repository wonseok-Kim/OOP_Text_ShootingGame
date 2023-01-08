#pragma once

//class GlobalObjectManager
//{
//public:
//	static GlobalObjectManager* Instance()
//	{
//		static GlobalObjectManager inst;
//		return &inst;
//	}
//
//	~GlobalObjectManager();
//
//	void Update();
//	void Render(Renderer* renderer);
//
//private:
//	GlobalObjectManager() = default;
//
//private:
//	ObjectList m_ObjectList;
//};

#include "ObjectManager.h"

class GlobalObjectManager : public ObjectManager
{
public:
    static GlobalObjectManager* Instance()
    {
        static GlobalObjectManager inst;
        return &inst;
    }

    ~GlobalObjectManager() = default;

private:
    GlobalObjectManager() = default;
};
