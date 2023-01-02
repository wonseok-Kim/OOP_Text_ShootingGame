#pragma once

#include "ObjectBase.h"
#include "ObjectType.h"
#include "ResourceManager.h"

class Sprite;

class Player : public ObjectBase
{
public:
	Player(int x, int y)
		:ObjectBase(ObjectType_Player, x, y)
	{ 
		m_Sprite = ResourceManager::Instance().GetSprite(SpriteKind_Player);
		if (!m_Sprite)
		{
			// TODO: 예외 처리
			PrintError("sprite doesn't exists");
		}
	}

	virtual ~Player() override = default;

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;

private:
	Sprite* m_Sprite;
};

