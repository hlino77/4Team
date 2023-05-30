#include "stdafx.h"
#include "ObjectMgr.h"
#include "CollisionMgr.h"
#include "Device.h"
#include "Collider.h"
#include "GameObject.h"
//
#include "TextureMgr.h"
#include "Zealot.h"
#include "Probe.h"
#include "Nexus.h"
#include "Transform.h"

IMPLEMENT_SINGLETON(CObjectMgr)

CObjectMgr::CObjectMgr()
{
	//CreateBrushPen();
}

CObjectMgr::~CObjectMgr()
{
	Release();
}

HRESULT CObjectMgr::Initialize()
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Zealot/Move12/%d.png", TEX_MULTI, L"Zealot", L"Move12", 8)))
	{
		ERR_MSG(L"Zealot Move12 Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Probe/Move12/%d.png", TEX_MULTI, L"Probe", L"Move12", 1)))
	{
		ERR_MSG(L"Probe Move12 Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Build/Nexus/0.png", TEX_SINGLE, L"Nexus", L"Nexus")))
	{
		ERR_MSG(L"Nexus Create Failed");
		return E_FAIL;
	}


	m_Terrain.Initialize();


}

void CObjectMgr::Update()
{
	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
		for (auto& iter = m_vecObjList[i].begin(); iter != m_vecObjList[i].end(); ++iter)
		{
			if (!(*iter)->IsDead())
				(*iter)->Update();
		}
}

void CObjectMgr::LateUpdate()
{
	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
		for (auto& iter : m_vecObjList[i])
			iter->LateUpdate();

	CCollisionMgr::Get_Instance()->LateUpdate();
}

void CObjectMgr::Render()
{
	m_Terrain.Render();

	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
		for (auto& iter : m_vecObjList[i])
			iter->Render();

	CDevice::Get_Instance()->Get_Sprite()->End();
	LPD3DXLINE	pLine = CDevice::Get_Instance()->Get_Line();
	pLine->SetWidth(1.0f);
	pLine->Begin();

	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
		for (auto& iter : m_vecObjList[i])
		{
			if(iter->GetCollider())
				iter->GetCollider()->Render(pLine);
		}

	pLine->End();
}

void CObjectMgr::Release()
{
	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
	{
		for (auto& iter : m_vecObjList[i])
			Safe_Delete(iter);
		m_vecObjList[i].clear();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////
//		// 텍스트가 아니라 각 유닛 이름(+타일)enum class로 만들고 이걸 저장해야 할듯.				//
//		// 생성할 때는 enum 확인해서 enum에 따른 객체 생성 후 push_back							//
//		// ToDo : 고로 아래 텍스트를 포함해 SaveLoad할 데이터 수정 및 다이얼로그와 버튼 추가		//
//////////////////////////////////////////////////////////////////////////////////////////////

//void CObjectMgr::OnSaveData()
//{
//	HANDLE hFile = CreateFile(L"../Data/TempData.dat", GENERIC_WRITE, 0, 0,
//		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
//
//	if (INVALID_HANDLE_VALUE == hFile)
//		return;
//
//	DWORD	dwByte = 0;
//	DWORD	dwStrByte = 0;
//
//	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
//	{
//		for (auto& iter : m_vecObjList[i])
//		{
//			dwStrByte = sizeof(TCHAR) * (iter->GetData().strName.GetLength() + 1);
//	
//			WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
//			WriteFile(hFile, iter->GetData().strName, dwStrByte, &dwByte, nullptr);
//
//			WriteFile(hFile, &(iter->GetTransform()->Position().x), sizeof(float), &dwByte, nullptr);
//			WriteFile(hFile, &(iter->GetTransform()->Position().y), sizeof(float), &dwByte, nullptr);
//		}
//	}
//
//	CloseHandle(hFile);
//}
//
//void CObjectMgr::OnLoadData()
//{
//	HANDLE	hFile = CreateFile(L"../Data/TempData.dat",	GENERIC_READ, 0, 0,	OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
//
//	if (INVALID_HANDLE_VALUE == hFile)	// 파일 개방에 실패했다면
//		return;
//
//	float	vPosX = 0, vPosY = 0;
//	DWORD	dwByte = 0;
//	DWORD	dwStrByte = 0;
//
//	while (true)
//	{
//		// key 값 저장
//		ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
//
//		TCHAR*	pName = new TCHAR[dwStrByte];
//		ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);
//
//		ReadFile(hFile, &vPosX, sizeof(float), &dwByte, nullptr);
//		ReadFile(hFile, &vPosY, sizeof(float), &dwByte, nullptr);
//
//		if (0 == dwByte)
//		{
//			delete[]pName;
//			pName = nullptr;
//			break;
//		}
//
//		if (L"Zealot" == pName)
//		{
//			CGameObject*	pZealot = new CZealot;
//			pZealot->Initialize();
//			pZealot->GetTransform()->Translate(D3DXVECTOR3(vPosX, vPosY, 0.f));
//			
//			m_vecObjList[(UINT)OBJID::OBJ_UNIT_GROUND].push_back(pZealot);
//		}
//		else if (L"Probe" == pName)
//		{
//			CGameObject*	pProbe = new CProbe;
//			pProbe->Initialize();
//			pProbe->GetTransform()->Translate(D3DXVECTOR3(vPosX, vPosY, 0.f));
//			
//			m_vecObjList[(UINT)OBJID::OBJ_UNIT_GROUND].push_back(pProbe);
//		}
//		else if (L"Nexus" == pName)
//		{
//			CGameObject*	pNexus = new CNexus;
//			pNexus->Initialize();
//			pNexus->GetTransform()->Translate(D3DXVECTOR3(vPosX, vPosY, 0.f));
//
//			m_vecObjList[(UINT)OBJID::OBJ_BUILDING].push_back(pNexus);
//		}
//	}
//
//	CloseHandle(hFile);
//}
