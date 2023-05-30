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
#include "Dragoon.h"
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
		AfxMessageBox(L"Zealot Move12 Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Probe/Move12/%d.png", TEX_MULTI, L"Probe", L"Move12", 1)))
	{
		AfxMessageBox(L"Probe Move12 Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Dragoon/Move12/%d.png", TEX_MULTI, L"Dragoon", L"Move12", 10)))
	{
		AfxMessageBox(L"Probe Move12 Create Failed");
		return E_FAIL;
	}
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Unit/protoss/Build/Nexus/0.png", TEX_SINGLE, L"Nexus", L"Nexus")))
	{
		AfxMessageBox(L"Nexus Create Failed");
		return E_FAIL;
	}
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
void CObjectMgr::CreateObject(TCHAR * _pName, D3DXVECTOR3& vPos)
{
	CGameObject* pNewObject = nullptr;
	if (!_tcscmp(_pName, L"Zealot"))				{ pNewObject = new CZealot; }
	else if (!_tcscmp(_pName, L"Probe"))			{ pNewObject = new CProbe; }
	else if (!_tcscmp(_pName, L"Dragoon"))			{ pNewObject = new CDragoon; }
	else if (!_tcscmp(_pName, L"HighTempler"))		{	}
	else if (!_tcscmp(_pName, L"DarkTempler"))		{	}
	else if (!_tcscmp(_pName, L"Nexus"))			{ pNewObject = new CNexus; }
	else if (!_tcscmp(_pName, L"Gateway"))			{	}

	pNewObject->Initialize();
	pNewObject->GetTransform()->Translate(vPos);
	m_vecObjList[(UINT)pNewObject->GetType()].push_back(pNewObject);
}