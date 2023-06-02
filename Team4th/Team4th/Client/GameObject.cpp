#include "stdafx.h"
#include "GameObject.h"
#include "TimeMgr.h"

CGameObject::CGameObject():m_IsDead(false)
{
}

CGameObject::~CGameObject()
{
}

void CGameObject::Move_Frame(void)
{
	m_tFrame.fFrame += m_tFrame.fMax * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_tFrame.fFrame >= m_tFrame.fMax)
		m_tFrame.fFrame = 0.f;
}