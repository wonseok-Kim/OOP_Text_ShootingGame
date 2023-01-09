#include "stdafx.h"
#include "SceneBase.h"

#include "ObjectBase.h"

void SceneBase::AddObject(ObjectBase* obj)
{
	obj->m_Scene = this;
	m_ObjectManager.AddObject(obj);
}
