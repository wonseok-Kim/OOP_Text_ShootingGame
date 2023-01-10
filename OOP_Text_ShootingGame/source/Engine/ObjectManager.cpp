#include "stdafx.h"
#include "ObjectManager.h"

#include "ObjectBase.h"

ObjectManager::~ObjectManager()
{
    for (ObjectBase* obj : m_ObjectList)
    {
        delete obj;
    }
}

void ObjectManager::Update(DWORD frames)
{
    for (ObjectBase* obj : m_ObjectList)
    {
        obj->Update();
    }

    ObjectList::iterator iter1;
    for (iter1 = m_ObjectList.begin(); iter1 != m_ObjectList.end(); ++iter1)
    {
        ObjectList::iterator iter2 = iter1;
        while (true)
        {
            ++iter2;
            if (iter2 == m_ObjectList.end())
                break;

            if (iter1->IsCollision(*iter2))
            {
                iter1->OnCollision(*iter2);
                iter2->OnCollision(*iter1);
            }
        }
    }

    for (iter1 = m_ObjectList.begin(); iter1 != m_ObjectList.end(); )
    {
        if (iter1->m_bRelease)
        {
            DWORD elapsedFrameAfterDestroy = frames - iter1->m_DestroyFrame;
            if (elapsedFrameAfterDestroy >= iter1->m_DestroyDelayFrame)
            {
                iter1->OnDestroy();
                delete (*iter1);
                iter1 = m_ObjectList.erase(iter1);
                continue;
            }
        }
        ++iter1;
    }
}

void ObjectManager::Render(Renderer* renderer)
{
    for (ObjectBase* obj : m_ObjectList)
    {
        if (obj->m_bVisible)
        {
            obj->Render(renderer);
        }
    }
}