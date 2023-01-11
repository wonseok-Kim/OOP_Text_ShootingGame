#include "stdafx.h"
#include "Bullet.h"

#include "Engine/Renderer.h"

#include "Enemy.h"
#include "Player.h"

void Bullet::Update()
{
    DWORD framesCount = m_Scene->GetFrames();

    if (framesCount % 3 == 0)
    {
        m_X += m_Dir.X;
        m_Y += m_Dir.Y;

        if (m_X < 0 || m_X > GAME_WIDTH - 1)
            Destroy(this);
        if (m_Y < 0 || m_Y > GAME_HEIGHT - 1)
            Destroy(this);
    }
}

void Bullet::Render(Renderer* renderer)
{
    renderer->DrawSprite(m_X, m_Y, m_Sprite);
}
