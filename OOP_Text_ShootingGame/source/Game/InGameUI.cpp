#include "stdafx.h"
#include "InGameUI.h"

#include "Engine/Renderer.h"

void InGameUI::Render(Renderer* renderer)
{
    renderer->DrawString(m_X, m_Y, m_szUI);
}
