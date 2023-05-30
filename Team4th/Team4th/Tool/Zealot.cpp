#include "stdafx.h"
#include "Zealot.h"
#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

//
#include "MainFrm.h"
#include "ToolView.h"
#include "Device.h"
#include "TextureMgr.h"

CZealot::CZealot()
{
}

CZealot::CZealot(const CZealot& rhs) : CZealot()
{
	Initialize();
}

CZealot::~CZealot()
{
	Release();
}

void CZealot::Initialize(void)
{
	m_eType = OBJID::OBJ_UNIT_GROUND;
	m_IsDead = false;

	m_dwTime = 0;

#pragma region Data

	m_tData.strName = L"Zealot";
	
	m_tData.iMaxHp = 100;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 60;
	m_tData.iShield = m_tData.iMaxShield;
	m_tData.iAttack = 8;
	m_tData.iDeffnse = 1;
	m_tData.fMovefSpeed = 1.875f;
	m_tData.fAttackSpeed = 22.f;

	m_tData.iFireRange = 0;
	m_tData.iSightRange = 7;
	
	m_tData.iMaxEnergy = 0;
	m_tData.iEnergy = m_tData.iMaxEnergy;

#pragma endregion Data

	m_pTransform = new CTransform;
	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pTransform->Scale(D3DXVECTOR3(32.f, 32.f, 0.f));
	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	// Temp
}

int CZealot::Update(void)
{
	m_pTransform->Update();

	return 0;
}

int CZealot::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	return 0;
}

void CZealot::Render()
{
	m_pGraphics->Render(L"Zealot", L"Move12", 0);
}

void CZealot::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CZealot::OnCollisionEnter(CCollider * _pOther)
{
}

void CZealot::OnCollisionStay(CCollider * _pOther)
{
}

void CZealot::OnCollisionExit(CCollider * _pOther)
{
}

void CZealot::OnCollisionEnter(TILE * _pTIle)
{
}

void CZealot::OnCollisionStay(TILE * _pTIle)
{
}

void CZealot::OnCollisionExit(TILE * _pTIle)
{
}

CGameObject * CZealot::Clone()
{
	CGameObject* pNewObj = new CZealot(*this);
	return pNewObj;
}
