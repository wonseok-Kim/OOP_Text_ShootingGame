#include "stdafx.h"
#include "SceneBase.h"

#include "ObjectBase.h"

SceneBase::~SceneBase()
{
	for (ObjectBase* obj : m_ObjectList)
		delete obj;
}
