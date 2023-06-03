#include "stdafx.h"
#include "ObjectMgr.h"
#include "CollisionMgr.h"
#include "KeyMgr.h"
#include "Device.h"
#include "Collider.h"
#include "GameObject.h"
//
#include "TextureMgr.h"
#include "Zealot.h"
#include "Probe.h"
#include "Dragoon.h"
#include "Zergling.h"
#include "Nexus.h"
#include "Gateway.h"
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
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Zealot/Move12/%d.png", TEX_MULTI, L"Zealot", L"Move12", 8)) ||
		FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Probe/Move12/%d.png", TEX_MULTI, L"Probe", L"Move12", 1)) ||
		FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Dragon/Move12/%d.png", TEX_MULTI, L"Dragoon", L"Move12", 10)) ||
		FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Build/Nexus/0.png", TEX_SINGLE, L"Nexus", L"Nexus")) ||
		FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Build/Gateway/0.png", TEX_SINGLE, L"Gateway", L"Gateway")) ||
		FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/zerg/Zergling/Move12/%d.png", TEX_MULTI, L"Zergling", L"Move12", 8)) ||
		FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Terrain/Tile/Tile%d.png", TEX_MULTI, L"Terrain", L"Tile", 36)))
		return E_FAIL;

	if (FAILED(m_Terrain.Initialize()))
		return E_FAIL;

	m_bPath = false;

	return S_OK;
}

void CObjectMgr::Update()
{
	if (CKeyMgr::Get_Instance()->Key_Down('P'))
	{
		m_bPath = !m_bPath;
	}

	for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
		for (auto& iter = m_vecObjList[i].begin(); iter != m_vecObjList[i].end(); ++iter)
		{
			if (!(*iter)->IsDead())
				(*iter)->Update();
		}

	m_Terrain.Update();
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
	m_Terrain.Collider_Render();

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

	CDevice::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
}

void CObjectMgr::CreateObject(TCHAR* _pName, D3DXVECTOR3& vPos)
{
	if (L"" == _pName)
		return;

	CGameObject* pNewObject = nullptr;
	if (!_tcscmp(_pName, L"Zealot")) { pNewObject = new CZealot; }
	else if (!_tcscmp(_pName, L"Probe")) { pNewObject = new CProbe; }
	else if (!_tcscmp(_pName, L"Dragoon")) { pNewObject = new CDragoon; }
	else if (!_tcscmp(_pName, L"HighTempler")) {}
	else if (!_tcscmp(_pName, L"DarkTempler")) {}
	else if (!_tcscmp(_pName, L"Zergling")) { pNewObject = new CZergling; }
	else if (!_tcscmp(_pName, L"Nexus")) { pNewObject = new CNexus; }
	else if (!_tcscmp(_pName, L"Gateway")) { pNewObject = new CGateway; }

	if (!pNewObject)
		return;

	pNewObject->Initialize();
	pNewObject->GetTransform()->Translate(vPos);
	m_vecObjList[(UINT)pNewObject->GetType()].push_back(pNewObject);
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