#include "stdafx.h"
#include "Input.h"

void Input::Handle()
{
	for (int i = 0; i < 256; ++i)
	{
		m_NewKeyState[i] = GetAsyncKeyState(i);

		m_Keys[i].pressed = false;
		m_Keys[i].released = false;

		if (m_NewKeyState[i] != m_OldKeyState[i])
		{
			if (m_NewKeyState[i] & 0x8001)
			{
				m_Keys[i].pressed = !m_Keys[i].held;
				m_Keys[i].held = true;
			}
			else
			{
				m_Keys[i].released = true;
				m_Keys[i].held = false;
			}
		}

		m_OldKeyState[i] = m_NewKeyState[i];
	}
}
