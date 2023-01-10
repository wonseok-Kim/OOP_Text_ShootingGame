#include "stdafx.h"
#include "Player.h"

#include "Engine/Renderer.h"
#include "Engine/SceneBase.h"

#include "Bullet.h"
#include "GameDefine.h"
#include "GameInfo.h"
#include "ResourceManager.h"

//Player::Player(SceneBase* scene, PlayerInfo* pInfo)
//    :ObjectBase(scene, pInfo->sprite, ObjectType_Player, pInfo->startCoord.X, pInfo->startCoord.Y)
//{
//    m_ShotInfo = ResourceManager::Instance()->GetShotInfo(L"Resources/ShotInfo/player_shot.txt");
//    assert(m_ShotInfo);
//}

Player::Player(PlayerInfo* pInfo)
    :ObjectBase(ObjectType_Player)
{
    m_Sprite = pInfo->sprite;
    m_X = pInfo->startCoord.X;
    m_Y = pInfo->startCoord.Y;
    m_ShotInfo = ResourceManager::Instance()->GetShotInfo(L"Resources/ShotInfo/player_shot.txt");
    assert(m_ShotInfo);
}

void Player::Update()
{
    DWORD framesCount = m_Scene->GetFrames();

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
            for (int i = 0; i < m_ShotInfo->shotCount; ++i)
            {
                //m_Scene->AddObject(new Bullet(m_Scene,
                //    m_X + m_ShotInfo->startCoord[i].X,
                //    m_Y + m_ShotInfo->startCoord[i].Y,
                //    m_ShotInfo->sprite, m_ShotInfo->dir[i], ObjectType_Player));

                m_Scene->AddObject(new Bullet(
                    m_X + m_ShotInfo->startCoord[i].X,
                    m_Y + m_ShotInfo->startCoord[i].Y,
                    m_ShotInfo->sprite, m_ShotInfo->dir[i], ObjectType_Player));
            }
        }

        m_State = 0u;
    }

    if (m_bInvicible)
    {
        DWORD elapsedFrame = framesCount - m_HittedFrame;
        if (elapsedFrame >= m_InvicibleFrames)
        {
            m_bInvicible = false;
            m_bVisible = true;
        }
        else
        {
            if (elapsedFrame % 15 == 0)
            {
                m_bVisible = !m_bVisible;
            }
        }
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
        if (m_bInvicible)
            return;

        Bullet* b = (Bullet*)other;
        if (b->GetWhoShot() != ObjectType_Enemy)
            return;

        m_HP--;
        m_bInvicible = true;
        m_bVisible = false;
        m_HittedFrame = m_Scene->GetFrames();
        if (m_HP == 0)
        {
            if (m_Life > 0)
            {
                m_HP = 3;
                m_Life--;
            }
            else
            {
                // TODO: 플레이어 뒤짐처리
            }
        }

        Destroy(b);

        if (m_GameInfo)
            m_GameInfo->OnUpdate(m_Life, m_HP);
    }
}
