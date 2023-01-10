#pragma once

class ResourceLoader
{
public:
    static bool Load();

private:
    static bool LoadSprite();
    static bool LoadShotInfo();
    static bool LoadPattern();
    static bool LoadItem();
    static bool LoadStage();
};

