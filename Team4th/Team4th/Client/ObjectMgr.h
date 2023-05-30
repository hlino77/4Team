#pragma once
#include "Include.h"
#include "Terrain.h"

class CGameObject;
class CObjectMgr
{
	DECLARE_SINGLETON(CObjectMgr)

private:
	CObjectMgr();
	~CObjectMgr();

public:
	HRESULT		Initialize();
	void		Update();
	void		LateUpdate();
	void		Render();
	void		Release();

	vector<CGameObject*>&	GetObjList(OBJID _eType)	{ return m_vecObjList[(UINT)_eType]; }

	// 임시 저장 불러오기
	/*void OnSaveData();
	void OnLoadData();*/

private:
	vector<CGameObject*> m_vecObjList[(UINT)OBJID::OBJ_END];

	CTerrain			 m_Terrain;
};

