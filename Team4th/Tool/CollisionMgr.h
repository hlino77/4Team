#pragma once
#include "Include.h"

union COLLIDER_ID
{
	struct
	{
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};

class CCollider;
class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)

private:
	CCollisionMgr();
	~CCollisionMgr();

public:
	void LateUpdate();

public:
	map<ULONGLONG, bool>& GetMapColInfo() { return m_mapColInfo; }
	void SetMapColInfo(ULONGLONG ID, bool bCollision) { m_mapColInfo[ID] = bCollision; }

	void CheckGroup(OBJID _eLeft, OBJID _eRight);
	void Reset();

private:
	map<ULONGLONG, bool> m_mapColInfo;
	UINT	m_arrCheck[(UINT)OBJID::OBJ_END];

	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);
	void CheckCollisionByType(OBJID _eTypeLeft, OBJID _eTypeRight);
};

