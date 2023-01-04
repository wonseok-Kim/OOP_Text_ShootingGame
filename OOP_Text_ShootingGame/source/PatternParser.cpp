#include "stdafx.h"
#include "PatternParser.h"

#include "ResourceManager.h"

bool PatternParser::Run()
{
	int* pCount = &(ResourceManager::Instance().m_PatternListsCount);

	while (*m_Current != '\0')
	{
		PatternList* pPatternList = &(ResourceManager::Instance().m_PatternLists[*pCount]);
		WCHAR** pPatternFilename = &(ResourceManager::Instance().m_PatternFilenames[*pCount]);

		size_t size = wcslen(m_Filename) + 1;
		(*pPatternFilename) = new WCHAR[size];
		wcscpy_s(*pPatternFilename, size, m_Filename);

		int count;
		GetNumberLiteral(&count);

		for (int i = 0; i < count; ++i)
		{
			SubString block;
			if (!GetBlock(&block))
				return false;

			Pattern* p = new Pattern;
			ParsePattern(block, p);
			pPatternList->push_back(p);
		}

		++(*pCount);
	}

	return true;
}

bool PatternParser::ParsePattern(SubString texts, Pattern* out_Pattern)
{
	const char* identifiers[6] = { "duration", "moveTo", "moveInterval", "shotInfo", "shotInterval", "shotChance" };
	size_t identifiersLength = sizeof(identifiers) / sizeof(char*);

	m_Current = texts.begin;

	while (true)
	{
		SkipWhiteSpace();
		if (m_Current == texts.end)
			break;

		SubString key;
		GetIdentifier(&key);

		SkipWhiteSpace();
		if (GetCharType(*m_Current) != CharType::Colon)
			return false;
		++m_Current;

		int i;
		for (i = 0; i < identifiersLength; ++i)
			if (key.equal(identifiers[i]))
				break;

		ShotInfo* pShotInfo;
		WCHAR path[MAX_PATH];
		int temp;
		switch (i)
		{
		case 0:
			if (!GetNumberLiteral(&out_Pattern->duration))
				return false;
			break;

		case 1:
			if (!GetCoord(&out_Pattern->moveTo))
				return false;
			break;

		case 2:
			if (!GetNumberLiteral(&temp))
				return false;

			out_Pattern->moveInterval = (DWORD)temp;
			break;

		case 3:
			if (!GetStringLiteral(path, MAX_PATH))
				return false;

			pShotInfo = ResourceManager::Instance().GetShotInfo(path);
			if (!pShotInfo)
				return false;

			out_Pattern->shotInfo = pShotInfo;
			break;

		case 4:
			if (GetNumberLiteral(&temp))
				return false;

			out_Pattern->shotInterval = (DWORD)temp;
			break;

		case 5:
			if (GetNumberLiteral(&out_Pattern->shotChance))
				return false;
			break;

		default:
			Assert(0, L"Invalid case");
			return false;
		}
	}

	return true;
}
