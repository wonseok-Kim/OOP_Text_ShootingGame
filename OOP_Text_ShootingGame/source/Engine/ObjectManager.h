#pragma once

#include "ObjectList.h"

class Renderer;

class ObjectManager
{
public:
    ObjectManager() = default;
    ~ObjectManager();

    void Update();
    void Render(Renderer* renderer);

    void AddObject(ObjectBase* obj) { m_ObjectList.push_back(obj); }

private:
    ObjectList m_ObjectList;
};
