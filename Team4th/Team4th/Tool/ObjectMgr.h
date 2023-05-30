#pragma once
#include "Include.h"

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

	void		CreateObject(TCHAR*	_pName, D3DXVECTOR3& vPos);

private:
	vector<CGameObject*> m_vecObjList[(UINT)OBJID::OBJ_END];
};

