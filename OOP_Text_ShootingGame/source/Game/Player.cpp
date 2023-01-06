#include "stdafx.h"
#include "Player.h"

#include "Engine/Renderer.h"

#include "GameDefine.h"

void Player::Update(DWORD framesCount)
{
	if (m_KeyState.up)
		m_Y--;
	if (m_KeyState.down)
		m_Y++;
	if (m_KeyState.right)
		m_X++;
	if (m_KeyState.left)
		m_X--;

	m_Y = min(GAME_HEIGHT - 1, max(0, m_Y));
	m_X = min(GAME_WIDTH - m_Sprite->Width(), max(0, m_X));

	memset(&m_KeyState, 0, sizeof(m_KeyState));
}

void Player::Render(Renderer* renderer)
{
	renderer->DrawSprite(m_X, m_Y, m_Sprite);
}
