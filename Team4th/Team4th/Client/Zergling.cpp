#include "stdafx.h"
#include "Zergling.h"
#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

#include "Device.h"
#include "TextureMgr.h"

CZergling::CZergling()
{
}

CZergling::CZergling(const CZergling & rhs)
{
	Initialize();
}


CZergling::~CZergling()
{
	Release();
}

void CZergling::Initialize(void)
{
	m_eType = OBJID::OBJ_UNIT_GROUND;
	m_IsDead = false;

	m_dwTime = 0;

#pragma region Data

	m_tData.strName = L"Zergling";

	m_tData.iMaxHp = 35;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 0;
	m_tData.iShield = m_tData.iMaxShield;
	m_tData.iAttack = 5;
	m_tData.iDeffnse = 0;
	m_tData.fMovefSpeed = 2.612f;
	m_tData.fAttackSpeed = 8.5f;

	m_tData.iFireRange = 0;
	m_tData.iSightRange = 5;

	m_tData.iMaxEnergy = 0;
	m_tData.iEnergy = m_tData.iMaxEnergy;

#pragma endregion Data

	m_pTransform = new CTransform;
	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pTransform->Scale(D3DXVECTOR3(16.f, 16.f, 0.f));
	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	m_eState = UNIT_STATE::IDLE;
	m_vTargetPos = m_pTransform->Position();

	m_tFrame = { 0.f, 7.f };
}

int CZergling::Update(void)
{
	CGroundUnit::Update();

	return 0;
}

int CZergling::LateUpdate(void)
{
	CGroundUnit::LateUpdate();
	m_pCollider->LateUpdate();

	return 0;
}

void CZergling::Render()
{
	m_pGraphics->Render(L"Zergling", L"Move12", m_tFrame.fFrame);
	CGroundUnit::Render();
}

void CZergling::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

CGameObject * CZergling::Clone()
{
	CGameObject* pNewObj = new CZergling(*this);
	return pNewObj;
}
