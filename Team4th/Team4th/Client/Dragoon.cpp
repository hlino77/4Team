#include "stdafx.h"
#include "Dragoon.h"
#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

#include "Device.h"
#include "TextureMgr.h"

CDragoon::CDragoon()
{
}

CDragoon::CDragoon(const CDragoon & rhs)
{
	Initialize();
}

CDragoon::~CDragoon()
{
	Release();
}

void CDragoon::Initialize(void)
{
	m_eType = OBJID::OBJ_UNIT_GROUND;
	m_IsDead = false;

	m_dwTime = 0;

#pragma region Data

	m_tData.strName = L"Dragoon";

	m_tData.iMaxHp = 100;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 80;
	m_tData.iShield = m_tData.iMaxShield;
	m_tData.iAttack = 20;
	m_tData.iDeffnse = 1;
	m_tData.fMovefSpeed = 2.461f;
	m_tData.fAttackSpeed = 30.f;

	m_tData.iFireRange = 4;
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

	m_tFrame = { 0.f, 9.f };
}

int CDragoon::Update(void)
{
	CGroundUnit::Update();

	return 0;
}

int CDragoon::LateUpdate(void)
{
	CGroundUnit::LateUpdate();
	m_pCollider->LateUpdate();

	return 0;
}

void CDragoon::Render()
{
	m_pGraphics->Render(L"Dragoon", L"Move12", m_tFrame.fFrame);
	CGroundUnit::Render();
}

void CDragoon::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

CGameObject * CDragoon::Clone()
{
	CGameObject* pNewObj = new CDragoon(*this);
	return pNewObj;
}
