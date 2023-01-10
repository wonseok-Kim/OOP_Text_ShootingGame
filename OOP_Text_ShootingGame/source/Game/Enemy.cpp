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
            Destroy(this, 5);

        Destroy(b);
    }
}

void Enemy::OnDestroy()
{    
    SceneGame* sceneGame = (SceneGame*)m_Scene;
    sceneGame->OnEnemyDie();
}
