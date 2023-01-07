#include "stdafx.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase(SceneBase* sceneOrNull, int objectType, int x, int y)
	: m_Scene{ sceneOrNull }
	, m_ObjectType{ objectType }
	, m_X{ x }
	, m_Y{ y }
{ 

}

ObjectBase::~ObjectBase()
{
}
