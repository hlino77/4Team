#include "stdafx.h"
#include "ObjectMgr.h"
#include "CollisionMgr.h"
#include "Device.h"
#include "Collider.h"
#include "GameObject.h"
//
#include "TextureMgr.h"
#include "Zealot.h"
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
	}	// Áú·µ ÀÓ½Ã
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

//void CObjectMgr::CreateBrushPen()
//{
//	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
//	m_arrBrush[(UINT)BRUSH_TYPE::SOLID] = (HBRUSH)GetStockObject(DC_BRUSH);
//
//	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
//	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
//}
