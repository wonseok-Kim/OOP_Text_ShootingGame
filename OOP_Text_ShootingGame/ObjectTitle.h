#pragma once

#include "ObjectBase.h"
#include "ObjectType.h"
#include "SceneManager.h"

class ObjectTitle : public ObjectBase
{
public:
	enum State
	{
		IDLE = 0,
		KEY_DOWN,
		KEY_UP,
		KEY_PRESSED,
	};

	enum MenuKind
	{
		GAME_START = 0,
		EXIT,
		MAX_MENU
	};

	ObjectTitle()
		:ObjectBase(ObjectType_Title, 0, 0)
	{
	}

	virtual ~ObjectTitle() override
	{
	}

	virtual void Update() override
	{
		switch (m_State)
		{
		case ObjectTitle::IDLE:
			break;

		case ObjectTitle::KEY_DOWN:
			m_CurrentMenu = (m_CurrentMenu + 1) % MAX_MENU;
			break;

		case ObjectTitle::KEY_UP:
			m_CurrentMenu--;
			if (m_CurrentMenu < 0)
				m_CurrentMenu = MAX_MENU - 1;
			break;

		case ObjectTitle::KEY_PRESSED:
			switch (m_CurrentMenu)
			{
			case GAME_START:
				// TODO : Game Scene 넣기
				// SceneManager::Instance().LoadScene();
				break;

			case EXIT:
				// TODO : Game 종료 넣기
				break;

			default:
				Assert(0, "invalid case");
				break;
			}
			break;

		default:
			Assert(0, "invalid case");
			break;
		}

		m_State = IDLE;
	}

	virtual void Render() override
	{

	}

	void SetState(State state) { m_State = state; }

private:
	State m_State = IDLE;
	int m_CurrentMenu = GAME_START;

	// TODO: 변수 이름 바꾸기
	const COORD m_SelectCrd[4] = {
		{8 , 15}, { 8, 29}, {10, 15}, {10, 29}
	};
	const WCHAR* m_TitleScreen[100] = {
		L"***************************************************",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                SHOOTING GAME                    *",
		L"*                                                 *",
		L"*                                                 *",
		L"*               >> GAME START <<                  *",
		L"*                                                 *",
		L"*                     EXIT                        *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*  MOVE : ← → ↑ ↓                                 *",
		L"*  ATTACK, SELECT : SPACE BAR                     *",
		L"*                                                 *",
		L"***************************************************"
	};
};

