#pragma once

#include "Engine/SceneBase.h"

class Renderer;

class SceneTitle : public SceneBase
{
	enum
	{
		GAME_START,
		GAME_EXIT,
		MAX_MENU,
	};

public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;

private:
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

