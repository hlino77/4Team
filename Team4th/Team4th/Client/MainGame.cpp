#include "stdafx.h"
#include "MainGame.h"
#include "Device.h"

#include "SceneMgr.h"
#include "ObjectMgr.h"
#include "TimeMgr.h"

#include "EventMgr.h"

#include "GameScene.h"

#include "CameraMgr.h"
#include "GameObject.h"
#include "MyMouse.h"


CMainGame::CMainGame()
	: m_pGraphicDev(CDevice::Get_Instance())
{
	ZeroMemory(m_szFPS, sizeof(TCHAR) * MIN_STR);
	m_iFps = 0;
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize(void)
{
	if (FAILED(m_pGraphicDev->Initialize()))
	{
		ERR_MSG(L"Client Device Create Failed");
		return E_FAIL;
	}

	CTimeMgr::Get_Instance()->Initialize();

	CScene*	pGameScene = new CGameScene;
	CSceneMgr::Get_Instance()->Initialize(pGameScene);

	CObjectMgr::Get_Instance()->Initialize();
	CCameraMgr::Get_Instance()->Initialize();
	

	CGameObject* pMouse = new CMyMouse;
	pMouse->Initialize();
	CObjectMgr::Get_Instance()->GetObjList(pMouse->GetType()).push_back(pMouse);

	ShowCursor(false);

	/*
	#ifdef _DEBUG

	if (::AllocConsole() == TRUE)
	{
	FILE* nfp[3];
	freopen_s(nfp + 0, "CONOUT$", "rb", stdin);
	freopen_s(nfp + 1, "CONOUT$", "wb", stdout);
	freopen_s(nfp + 2, "CONOUT$", "wb", stderr);
	std::ios::sync_with_stdio();
	}

	#endif // _DEBUG*/


	return S_OK;
}

void CMainGame::Update(void)
{
	CTimeMgr::Get_Instance()->Update();
	CSceneMgr::Get_Instance()->Update_SceneMgr();
	CObjectMgr::Get_Instance()->Update();
	CCameraMgr::Get_Instance()->Update();
	
}

void CMainGame::Late_Update(void)
{
	CSceneMgr::Get_Instance()->Late_Update_SceneMgr();
	CObjectMgr::Get_Instance()->LateUpdate();
	CCameraMgr::Get_Instance()->LateUpdate();
}

void CMainGame::Render(void)
{
	//++m_iFps;

	m_pGraphicDev->Render_Begin();

	CSceneMgr::Get_Instance()->Render_SceneMgr();

	CObjectMgr::Get_Instance()->Render();

	m_pGraphicDev->Render_End();
}

void CMainGame::Release(void)
{
#ifdef _DEBUG

	//FreeConsole();

#endif // _DEBUG

	CTimeMgr::Get_Instance()->Destroy_Instance();
	CTextureMgr::Get_Instance()->Destroy_Instance();
	CSceneMgr::Get_Instance()->Destroy_Instance();
	m_pGraphicDev->Destroy_Instance();
}

