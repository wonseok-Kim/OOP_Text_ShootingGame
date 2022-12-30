#pragma once

class SceneBase;

class GameBase
{
public:
	GameBase(SceneBase* firstScene);
	virtual ~GameBase();

	void Run();
};

