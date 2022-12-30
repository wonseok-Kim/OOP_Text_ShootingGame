#pragma once
#include "SceneBase.h"

class ObjectTitle;

class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle() override;

	virtual void Update() override;
	virtual void Render() override;

private:
	ObjectTitle* m_Title;
};

