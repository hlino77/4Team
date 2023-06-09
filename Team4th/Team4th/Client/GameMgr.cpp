#include "stdafx.h"
#include "GameMgr.h"
#include "Controller.h"

IMPLEMENT_SINGLETON(CGameMgr)

CGameMgr::CGameMgr()
{
}

CGameMgr::~CGameMgr()
{
}

void CGameMgr::Initialize(void)
{
	m_pController = new CController;
	m_pController->Initialize();
}

void CGameMgr::Update(void)
{
	m_pController->Update();
}

void CGameMgr::LateUpdate(void)
{
}

void CGameMgr::Release(void)
{
}


