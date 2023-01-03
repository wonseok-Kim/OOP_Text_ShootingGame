#pragma once

#include "ObjectBase.h"
#include "ObjectType.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "SceneGame.h"

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
				SceneManager::Instance().LoadScene(new SceneGame());
				break;

			case EXIT:
				// TODO : Game 종료 넣기
				break;

			default:
				Assert(0, L"invalid case");
				break;
			}
			break;

		default:
			Assert(0, L"invalid case");
			break;
		}

		m_State = IDLE;
	}

	virtual void Render(Renderer* renderer) override
	{
		for (int i = 0; i < 19; ++i)
			renderer->DrawString(0, i, s_TitleScreen[i]);

		if (m_CurrentMenu == MenuKind::GAME_START)
		{
			renderer->Draw(m_SelectCrd[0].X, m_SelectCrd[0].Y, L'>');
			renderer->Draw(m_SelectCrd[0].X + 1, m_SelectCrd[0].Y, L'>');
			renderer->Draw(m_SelectCrd[1].X, m_SelectCrd[1].Y, L'<');
			renderer->Draw(m_SelectCrd[1].X + 1, m_SelectCrd[1].Y, L'<');
		}
		else if (m_CurrentMenu == MenuKind::EXIT)
		{
			renderer->Draw(m_SelectCrd[2].X, m_SelectCrd[2].Y, L'>');
			renderer->Draw(m_SelectCrd[2].X + 1, m_SelectCrd[2].Y, L'>');
			renderer->Draw(m_SelectCrd[3].X, m_SelectCrd[3].Y, L'<');
			renderer->Draw(m_SelectCrd[3].X + 1, m_SelectCrd[3].Y, L'<');
		}
	}

	void SetState(State state) { m_State = state; }

private:
	State m_State = IDLE;
	int m_CurrentMenu = GAME_START;

	// TODO: 변수 이름 바꾸기
	const COORD m_SelectCrd[4] = {
		{16, 8}, { 30, 8}, {16, 10}, {30, 10}	
	};

	WCHAR s_TitleScreen[19][52] = {
		L"***************************************************",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                SHOOTING GAME                    *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                  GAME START                     *",
		L"*                                                 *",
		L"*                     EXIT                        *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*  MOVE : Arrow Keys                              *",
		L"*  ATTACK, SELECT : SPACE BAR                     *",
		L"*                                                 *",
		L"***************************************************"
	};
};

