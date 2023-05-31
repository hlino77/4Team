#include "stdafx.h"
#include "SceneMgr.h"
#include "GameScene.h"
#include "CameraMgr.h"

IMPLEMENT_SINGLETON(CSceneMgr)

CSceneMgr::CSceneMgr()
	:m_pScene(nullptr)
{
}

CSceneMgr::~CSceneMgr()
{
	Release();
}

void CSceneMgr::Initialize(CScene* _pScene)
{
	m_pScene = _pScene;
	m_pScene->Ready_Scene();
}

void CSceneMgr::Update()
{
	m_pScene->Update_Scene();
	CCameraMgr::Get_Instance()->Update();
}

void CSceneMgr::LateUpdate()
{
	m_pScene->Late_Update_Scene();
	CCameraMgr::Get_Instance()->LateUpdate();
}

void CSceneMgr::Render()
{
	m_pScene->Render_Scene();
}

void CSceneMgr::Release()
{
	Safe_Delete<CScene*>(m_pScene);
}
