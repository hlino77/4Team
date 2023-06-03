#include "stdafx.h"
#include "GameScene.h"
#include "TextureMgr.h"
#include "ObjectMgr.h"
#include "CollisionMgr.h"
#include "GameMgr.h"
#include "Controller.h"

CGameScene::CGameScene()
{
}

CGameScene::~CGameScene()
{
	Release_Scene();
}

HRESULT CGameScene::Ready_Scene()
{
	if(FAILED(CObjectMgr::Get_Instance()->Initialize()))
		return E_FAIL;

	CGameMgr::Get_Instance()->Initialize();

	if (FAILED(LoadUnitData()))
		return E_FAIL;

	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_UNIT_GROUND, OBJID::OBJ_MOUSE);
	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_BUILDING, OBJID::OBJ_MOUSE);
	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_UNIT_GROUND, OBJID::OBJ_UNIT_GROUND);
	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_UNIT_GROUND, OBJID::OBJ_TILE);

	return S_OK;
}

void CGameScene::Update_Scene()
{
	CGameMgr::Get_Instance()->Update();
	CObjectMgr::Get_Instance()->Update();
}

void CGameScene::Late_Update_Scene()
{
	CObjectMgr::Get_Instance()->LateUpdate();
}

void CGameScene::Render_Scene()
{
	CObjectMgr::Get_Instance()->Render();
	CGameMgr::Get_Instance()->Get_Controller()->Render();
}

void CGameScene::Release_Scene()
{
	CObjectMgr::Get_Instance()->Release();
}

HRESULT CGameScene::LoadUnitData()
{
	CObjectMgr::Get_Instance()->Release();
	HANDLE hFile = CreateFile(L"../Data/TempData.dat", GENERIC_READ,
		0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
	{
		MessageBox(g_hWnd, _T("Load File"), L"Fail", MB_OK);
		return E_FAIL;
	}

	DWORD	dwByte = 0;
	DWORD	dwStrByte = 0;
	float fX, fY;

	while (true)
	{
		// key 값 저장
		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

		TCHAR*	pName = new TCHAR[dwStrByte];

		ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);


		// value값 저장
		ReadFile(hFile, &fX, sizeof(float), &dwByte, nullptr);
		ReadFile(hFile, &fY, sizeof(float), &dwByte, nullptr);


		if (0 == dwByte)
		{
			delete[]pName;
			pName = nullptr;
			break;
		}

		//if문추가
		if (L"" == pName)
			continue;
		CObjectMgr::Get_Instance()->CreateObject(pName, D3DXVECTOR3(fX, fY, 0.f));

		delete[]pName;
		pName = nullptr;
	}

	CloseHandle(hFile);
}
