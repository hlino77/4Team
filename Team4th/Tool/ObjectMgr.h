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
	//HBRUSH	GetBrush(BRUSH_TYPE _eBrush)	{ return m_arrBrush[(UINT)_eBrush]; }
	//HPEN	GetPen(PEN_TYPE _ePen)			{ return m_arrPen[(UINT)_ePen]; }

	void	CreateBrushPen();

private:
	vector<CGameObject*> m_vecObjList[(UINT)OBJID::OBJ_END];

	//HBRUSH		m_arrBrush[(UINT)BRUSH_TYPE::END];
	//HPEN		m_arrPen[(UINT)PEN_TYPE::END];
};

