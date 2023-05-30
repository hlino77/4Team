#pragma once
#include "Include.h"

#include "ToolView.h"
#include "MainFrm.h"

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

	vector<TILE*>&	m_vecTile = 
		dynamic_cast<CToolView*>(dynamic_cast<CMainFrame*>(AfxGetMainWnd())->m_MainSplitter.GetPane(0, 1))->m_pTerrain->Get_TileList();

	bool IsCollision(CCollider* _pLeft, CCollider* _pRight);
	bool IsTileCollision(CCollider* _pLeft, TILE* _pRight);
	void CheckCollisionByType(OBJID _eTypeLeft, OBJID _eTypeRight);
};

