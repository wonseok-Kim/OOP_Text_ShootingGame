#include "stdafx.h"
#include "Enemy.h"

void Enemy::OnCollision(ObjectBase* other)
{
    if (other->GetObjectType() == ObjectType_Bullet)
    {
        Bullet* b = (Bullet*)other;
        if (b->GetWhoShot() != ObjectType_Player)
            return;

        m_HP--;
        if (m_HP == 0)
            SetRelease();

        b->SetRelease();
    }
}
