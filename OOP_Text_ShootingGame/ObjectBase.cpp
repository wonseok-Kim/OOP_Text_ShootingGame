#include "stdafx.h"
#include "ObjectBase.h"

ObjectBase::ObjectBase(int objectType, int x, int y)
	: m_ObjectType{ objectType }
	, m_X{ x }
	, m_Y{ y }
{ 

}

ObjectBase::~ObjectBase()
{
}
