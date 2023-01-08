#include "stdafx.h"
#include "Player.h"

#include "Engine/Renderer.h"
#include "Engine/SceneBase.h"

#include "Bullet.h"
#include "GameDefine.h"
#include "ResourceManager.h"

void Player::Update(DWORD framesCount)
{
    if (framesCount % 2 == 0)
    {
        if (m_State & PlayerState::MOVE_UP)
            m_Y--;
        if (m_State & PlayerState::MOVE_DOWN)
            m_Y++;
        if (m_State & PlayerState::MOVE_RIGHT)
            m_X++;
        if (m_State & PlayerState::MOVE_LEFT)
            m_X--;

        m_Y = min(GAME_HEIGHT - 1, max(0, m_Y));
        m_X = min(GAME_WIDTH - m_Sprite->Width(), max(0, m_X));

        if (m_State & PlayerState::ATTACK)
        {
            Sprite* sprite = ResourceManager::Instance()->GetSprite(L"Resources/Sprite/default_bullet.sp");
            m_Scene->AddObject(new Bullet(m_Scene, m_X, m_Y, sprite, { (short)0, (short)1 }));
        }

        m_State = 0u;
    }
}

void Player::Render(Renderer* renderer)
{
    renderer->DrawSprite(m_X, m_Y, m_Sprite);
}

void Player::OnCollision(ObjectBase* other)
{
    if (other->GetObjectType() == ObjectType_Bullet)
    {
        Bullet* b = (Bullet*)other;
        if (b->GetWhoShot() != ObjectType_Enemy)
            return;
    }

}
