#include "stdafx.h"
#include "EventMgr.h"
#include "ObjectMgr.h"
#include "GameScene.h"
#include "GameObject.h"

IMPLEMENT_SINGLETON(CEventMgr)

CEventMgr::CEventMgr()
{
}

CEventMgr::~CEventMgr()
{
}

void CEventMgr::Update()
{
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		// 여기에서 삭제 해주고, GameScene에서는 벡터 원소만 날려 줌.
		/*if (OBJ_TYPE::MONSTER == m_vecDead[i]->GetType())
		{
		CManagers_SG::instance().Pool()->ReturnPool(m_vecDead[i]);
		}*/

		Safe_Delete(m_vecDead[i]);
	}
	m_vecDead.clear();

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Execute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void CEventMgr::CreateObject(CGameObject * _pObj, OBJID _eGroup)
{
	tagEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	AddEvent(evn);
}

void CEventMgr::DeleteObject(CGameObject * _pObj)
{
	tagEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	AddEvent(evn);
}

void CEventMgr::Execute(const tagEvent & _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		CGameObject* pNewObject = (CGameObject*)_eve.lParam;
		OBJID eType = (OBJID)_eve.wParam;

		CObjectMgr::Get_Instance()->GetObjList(eType).push_back(pNewObject);
	}
	break;

	case EVENT_TYPE::DELETE_OBJECT:
	{
		CGameObject*	pDeadObject = (CGameObject*)_eve.lParam;
		pDeadObject->SetDead(true);
		m_vecDead.push_back(pDeadObject);
	}
	break;
	case EVENT_TYPE::SCENE_CHANGE:
		//
		break;
	}
}
