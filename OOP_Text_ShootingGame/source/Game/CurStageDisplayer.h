#pragma once

#include "Engine/ObjectBase.h"
#include "Engine/Renderer.h"
#include "Engine/SceneManager.h"

#include "Resource/ResourceManager.h"

#include "GameDefine.h"
#include "ObjectType.h"
#include "SceneTitle.h"

class CurStageDisplayer : public ObjectBase
{
public:
	CurStageDisplayer(int curStageIdx, bool bStageClear = false)
		: ObjectBase(ObjectType_StageInfo)
		, m_CurStageIdx(curStageIdx)
		, m_bStageClear(bStageClear)
	{
		m_X = 4;
		m_Y = GAME_HEIGHT / 2;

		if (bStageClear)
			m_Length = swprintf_s(m_szToDisplay, _countof(m_szToDisplay), m_ClearFormat);
		else if (curStageIdx == BOSS_STAGE_IDX)
			m_Length = swprintf_s(m_szToDisplay, _countof(m_szToDisplay), m_BossFormat);
		else
			m_Length = swprintf_s(m_szToDisplay, _countof(m_szToDisplay), m_DefaultFormat, curStageIdx + 1);
	}

	virtual void Update() override
	{
		DWORD framesCount = m_Scene->GetFrames();

		if (m_StartFrame == 0)
		{
			m_StartFrame = framesCount;
			return;
		}

		DWORD ElapsedFrames = framesCount - m_StartFrame;

		if (m_CurStageIdx == BOSS_STAGE_IDX && !m_bStageClear)
		{
			if (ElapsedFrames % 25 == 0)
				m_bVisible = !m_bVisible;

			if (ElapsedFrames >= 100)
				Destroy(this);
		}
		else
		{
			m_PrintIdx = ElapsedFrames / 15;
			if (m_PrintIdx > m_Length)
			{
				Destroy(this);
			}
		}
	}

	virtual void Render(Renderer* renderer) override
	{
		if (m_CurStageIdx == BOSS_STAGE_IDX && !m_bStageClear)
		{
			renderer->DrawString(m_X, m_Y, m_szToDisplay);
		}
		else
		{
			int i;
			for (i = 0; i < m_Length; ++i)
			{
				if (i > m_PrintIdx)
					break;

				renderer->Draw(m_X + i, m_Y, m_szToDisplay[i]);
			}
			renderer->Draw(m_X + i, m_Y, L'_');
		}
	}

	virtual void OnDestroy() override
	{
		if (m_bStageClear)
		{
			int stagesCount = ResourceManager::Instance()->GetStagesCount();
			if (m_CurStageIdx + 1 >= stagesCount)
				SceneManager::Instance()->LoadScene(new SceneVictory);
			else
				SceneManager::Instance()->LoadScene(new SceneGame(m_CurStageIdx + 1));			
		}
	}

private:
	const WCHAR* m_DefaultFormat = L"Stage : %02d";

	const WCHAR* m_BossFormat = L"WARNING BOSS";

	const WCHAR* m_ClearFormat = L"STAGE CLEARED!";

	int m_CurStageIdx;
	bool m_bStageClear;

	WCHAR m_szToDisplay[20];
	int m_Length;

	DWORD m_StartFrame = 0;
	int m_PrintIdx = 0;
};