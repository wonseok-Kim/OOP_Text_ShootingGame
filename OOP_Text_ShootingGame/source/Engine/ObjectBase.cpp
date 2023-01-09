#include "stdafx.h"
#include "ObjectBase.h"

#include "Engine/Sprite.h"

ObjectBase::ObjectBase(int objectType)
    : m_ObjectType{ objectType }
{ }

ObjectBase::~ObjectBase()
{}

bool ObjectBase::IsCollision(ObjectBase* other)
{
    if (!m_Sprite || !other->m_Sprite)
        return false;

    int myLeft = m_X;
    int myRight = m_X + m_Sprite->Width() - 1;
    int myTop = m_Y;
    int myBottom = m_Y - m_Sprite->Height() + 1;

    int youLeft = other->m_X;
    int youRight = other->m_X + other->m_Sprite->Width() - 1;
    int youTop = other->m_Y;
    int youBottom = other->m_Y - other->m_Sprite->Height() + 1;

    if (myLeft <= youRight)
    {
        if (myRight >= youLeft)
        {
            if (myTop <= youBottom)
            {
                if (myBottom >= youTop)
                {
                    return true;
                }
            }
        }
    }

    return false;
}
