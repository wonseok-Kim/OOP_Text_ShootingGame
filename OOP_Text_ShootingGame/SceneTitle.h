#pragma once
#include "SceneBase.h"

class ObjectTitle;
class Renderer;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Update() override;
	virtual void Render(Renderer* renderer) override;

private:
	ObjectTitle* m_Title;
};

