#pragma once

#include "Engine/ObjectBase.h"

#include "Resource/Infos.h"

#include "ObjectType.h"

class Renderer;

class Enemy : public ObjectBase
{
public:
    Enemy(EnemyInfo* pInfo)
        :ObjectBase(ObjectType_Enemy)
    {
        m_Sprite = pInfo->sprite;
        m_X = pInfo->startCoord.X;
        m_Y = pInfo->startCoord.Y;

        m_EnemyInfo = pInfo;
        m_CurPatternIter = pInfo->pPatternList->begin();
        m_CurPattern = *m_CurPatternIter;
        m_HP = pInfo->hp;
    }

    virtual ~Enemy() override = default;

    virtual void Update() override;
    virtual void Render(Renderer* renderer);

    virtual void OnCollision(ObjectBase* other) override;
    virtual void OnDestroy() override;

private:
    EnemyInfo* m_EnemyInfo;
    PatternList::iterator m_CurPatternIter;
    Pattern* m_CurPattern;
    int m_Duration = 0;
    int m_HP;
};

