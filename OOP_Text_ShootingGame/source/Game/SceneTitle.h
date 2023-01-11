#pragma once

#include "Engine/SceneBase.h"

class Renderer;

class SceneTitle : public SceneBase
{
	enum
	{
		GAME_START = 0,
		GAME_EXIT,
		MAX_MENU,
	};

public:
	SceneTitle() = default;
	virtual ~SceneTitle() override = default;

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;

private:
	int m_CurrentMenu = GAME_START;

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

class SceneDefeat : public SceneBase
{
	enum
	{
		GAME_RETRY = 0,
		GAME_EXIT,
		MAX_MENU,
	};

public:
	SceneDefeat(int curStageIdx)
		:m_CurStageIdx{ curStageIdx }
	{}
	virtual ~SceneDefeat() override = default;

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;

private:
	int m_CurrentMenu = GAME_RETRY;
	int m_CurStageIdx;

	const COORD m_SelectCrd[4] = {
		{16, 8}, { 30, 8}, {16, 10}, {30, 10}
	};

	WCHAR s_RetryScreen[19][52] = {
		L"***************************************************",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                   You Died                      *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                    RETRY                        *",
		L"*                                                 *",
		L"*                    EXIT                         *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"***************************************************"
	};
};

class SceneVictory : public SceneBase
{
	enum
	{
		GAME_TITLE = 0,
		GAME_EXIT,
		MAX_MENU,
	};

public:
	SceneVictory() = default;
	virtual ~SceneVictory() override = default;

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;

private:
	int m_CurrentMenu = GAME_TITLE;

	const COORD m_SelectCrd[4] = {
		{16, 8}, { 30, 8}, {16, 10}, {30, 10}
	};

	WCHAR s_VictoryScreen[19][52] = {
		L"***************************************************",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                   Victory                       *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                  Go To Main                     *",
		L"*                                                 *",
		L"*                    EXIT                         *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"*                                                 *",
		L"***************************************************"
	};
};