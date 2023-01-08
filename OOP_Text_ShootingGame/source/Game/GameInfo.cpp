#include "stdafx.h"
#include "GameInfo.h"

#include "Engine/Renderer.h"

void GameInfo::Update(DWORD framesCount)
{
}

void GameInfo::Render(Renderer* renderer)
{
    renderer->DrawString(m_X, m_Y, m_szInfo);
}
