#pragma once

class Renderer;
class SceneBase;

class GameBase
{
public:
    GameBase(SceneBase* firstScene, int width = 80, int height = 40);
    virtual ~GameBase();

    void Run();

protected:
    Renderer* m_Renderer;
};

