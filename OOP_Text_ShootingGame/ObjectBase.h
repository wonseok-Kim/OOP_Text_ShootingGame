#pragma once

class ObjectBase
{
public:
	ObjectBase(int objectType, int x, int y);
	virtual ~ObjectBase();

	virtual void Update() = 0;
	virtual void Render() = 0;

	int GetObjectType() { return m_ObjectType; }

protected:
	int m_ObjectType;
	int m_X;
	int m_Y;

private:
};

