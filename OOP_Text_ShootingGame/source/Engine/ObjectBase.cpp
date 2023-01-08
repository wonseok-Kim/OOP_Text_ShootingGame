#include "stdafx.h"
#include "ObjectBase.h"

#include "Engine/Sprite.h"

ObjectBase::ObjectBase(SceneBase* sceneOrNull, Sprite* spriteOrNull, int objectType, int x, int y)
    : m_Scene{ sceneOrNull }
    , m_Sprite{ spriteOrNull }
    , m_ObjectType{ objectType }
    , m_X{ x }
    , m_Y{ y }
{

}

ObjectBase::~ObjectBase()
{}

bool ObjectBase::IsCollision(ObjectBase* other)
{
    if (!m_Sprite || !other->m_Sprite)
        return false;

    if (m_Y <= other->m_Y + (other->m_Sprite->Height() - 1))
    {
        if (m_Y + (m_Sprite->Height() - 1) >= other->m_Y)
        {
            if (m_X <= other->m_X + (other->m_Sprite->Width() - 1))
            {
                if (m_X + (m_Sprite->Width() - 1) >= other->m_X)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
