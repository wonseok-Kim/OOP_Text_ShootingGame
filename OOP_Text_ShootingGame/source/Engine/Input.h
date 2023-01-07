#pragma once

struct KeyState
{
	bool pressed;
	bool released;
	bool held;
};

class Input
{
public:
	static Input* Instance()
	{
		static Input inst;
		return &inst;
	}

	~Input() = default;

	void Handle()
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

	KeyState GetKey(int vKeyCode) 
	{ 
		Assert(vKeyCode >= 0 && vKeyCode < 256, L"vKeyCode ¹üÀ§ ¹þ¾î³²");

		return m_Keys[vKeyCode]; 
	}

private:
	Input() = default;

private:	
	KeyState m_Keys[256]{ 0, };
	short m_OldKeyState[256]{ 0, };
	short m_NewKeyState[256]{ 0, };
};