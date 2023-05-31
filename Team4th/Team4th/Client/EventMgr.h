#pragma once
#include "Include.h"

struct tagEvent
{
	EVENT_TYPE	eEvent;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class CGameObject;
class CEventMgr
{
	DECLARE_SINGLETON(CEventMgr)

private:
	CEventMgr();
	~CEventMgr();

public:
	void Update();

	void AddEvent(const tagEvent& _eve) { m_vecEvent.push_back(_eve); }

	void CreateObject(CGameObject* _pObj, OBJID _eGroup);
	void DeleteObject(CGameObject* _pObj);

private:
	void Execute(const tagEvent& _eve);

private:
	vector<tagEvent> m_vecEvent;
	vector<CGameObject*> m_vecCreate;
	vector<CGameObject*> m_vecDead;
};

