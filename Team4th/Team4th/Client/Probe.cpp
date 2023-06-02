#include "stdafx.h"
#include "Probe.h"
#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

CProbe::CProbe()
{
}

CProbe::CProbe(const CProbe & rhs)
{
	Initialize();
}

CProbe::~CProbe()
{
	Release();
}

void CProbe::Initialize(void)
{
	m_eType = OBJID::OBJ_UNIT_GROUND;
	m_IsDead = false;

	m_dwTime = 0;

#pragma region Data

	m_tData.strName = L"Probe";

	m_tData.iMaxHp = 20;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 20;
	m_tData.iShield = m_tData.iMaxShield;
	m_tData.iAttack = 5;
	m_tData.iDeffnse = 0;
	m_tData.fMovefSpeed = 2.344f;
	m_tData.fAttackSpeed = 22.f;

	m_tData.iFireRange = 1;
	m_tData.iSightRange = 8;

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

	m_eState = UNIT_STATE::IDLE;
	m_vTargetPos = m_pTransform->Position();

	m_tFrame = {0.f, 0.f};
}

int CProbe::Update(void)
{
	CGroundUnit::Update();

	return 0;
}

int CProbe::LateUpdate(void)
{
	CGroundUnit::LateUpdate();
	m_pCollider->LateUpdate();

	return 0;
}

void CProbe::Render()
{
	m_pGraphics->Render(L"Probe", L"Move12", m_tFrame.fFrame);
	CGroundUnit::Render();
}

void CProbe::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

CGameObject * CProbe::Clone()
{
	CGameObject* pNewObj = new CProbe(*this);
	return pNewObj;
}
