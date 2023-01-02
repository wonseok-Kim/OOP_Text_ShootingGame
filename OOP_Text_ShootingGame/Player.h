#pragma once

#include "ObjectBase.h"
#include "ObjectType.h"
#include "ResourceManager.h"

class Sprite;

typedef union
{
	struct
	{
		bool up;
		bool down;
		bool left;
		bool right;
		bool attack;
	};
	bool keys[5];
} PlayerKeyState;

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

	PlayerKeyState& SetState() { return m_KeyState; }

private:
	Sprite* m_Sprite;
	PlayerKeyState m_KeyState{};
};

