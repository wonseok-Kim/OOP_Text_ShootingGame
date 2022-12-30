#pragma once

class Renderer
{
public:
	Renderer(int width, int height)
		: m_Width{ width }
		, m_Height{ height }
	{
		m_pScreenBuffer = new WCHAR[(width + 1) * (height + 1)];

		//memset
	}

	~Renderer()
	{
		delete[] m_pScreenBuffer;
	}

	void Render()
	{
		//sputwchar()
	}

	void ClearScreen()
	{
		system("cls");
	}

	void ClearBuffer()
	{
		for (int y = 1; y <= m_Height; ++y)
		{
			for (int x = 1; x <= m_Width; ++x)
			{
				int idx = x + y * m_Width;
				m_pScreenBuffer[idx] = L' ';
			}
		}
	}

private:
	WCHAR* m_pScreenBuffer;
	int m_Width;
	int m_Height;
};

