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

	void Handle();

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