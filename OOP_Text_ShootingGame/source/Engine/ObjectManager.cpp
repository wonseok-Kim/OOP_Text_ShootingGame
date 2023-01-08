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

void ObjectManager::Update(DWORD framesCount)
{
    for (ObjectBase* obj : m_ObjectList)
    {
        obj->Update(framesCount);
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
		if (iter1->IsRelease())
		{
			delete (*iter1);
 			iter1 = m_ObjectList.erase(iter1);
		}
		else
			++iter1;
	}
}

void ObjectManager::Render(Renderer* renderer)
{
	for (ObjectBase* obj : m_ObjectList)
		obj->Render(renderer);
}