#include "stdafx.h"
#include "Player.h"

#include "Renderer.h"

void Player::Update()
{

}

void Player::Render(Renderer* renderer)
{
	renderer->drawSprite(m_X, m_Y, m_Sprite);
}
