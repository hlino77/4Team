#include "stdafx.h"
#include "Nexus.h"

#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

CNexus::CNexus()
{
}

CNexus::CNexus(const CNexus & rhs)
{
	Initialize();
}

CNexus::~CNexus()
{
}

void CNexus::Initialize(void)
{
	m_eType = OBJID::OBJ_BUILDING;
	m_IsDead = false;

	m_dwTime = 0;

	m_tData.strName = L"Nexus";

	m_tData.iMaxHp = 750;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 750;
	m_tData.iShield = m_tData.iMaxShield;
	m_tData.iAttack = 0;
	m_tData.iDeffnse = 1;
	m_tData.fMovefSpeed = 0.0f;
	m_tData.fAttackSpeed = 0.0f;

	m_tData.iFireRange = 0;
	m_tData.iSightRange = 0;

	m_tData.iMaxEnergy = 0;
	m_tData.iEnergy = m_tData.iMaxEnergy;


	m_pTransform = new CTransform;
	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pTransform->Scale(D3DXVECTOR3(127.f, 95.f, 0.f));
	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);
}

int CNexus::Update(void)
{
	m_pTransform->Update();
	
	return 0;
}

int CNexus::LateUpdate(void)
{
	m_pCollider->LateUpdate();

	return 0;
}

void CNexus::Render()
{
	m_pGraphics->Render(L"Nexus", L"Nexus", 1);
}

void CNexus::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CNexus::OnCollisionEnter(CCollider * _pOther)
{
}

void CNexus::OnCollisionStay(CCollider * _pOther)
{
}

void CNexus::OnCollisionExit(CCollider * _pOther)
{
}

void CNexus::OnCollisionEnter(TILE * _pTIle)
{
}

void CNexus::OnCollisionStay(TILE * _pTIle)
{
}

void CNexus::OnCollisionExit(TILE * _pTIle)
{
}

CGameObject * CNexus::Clone()
{
	CGameObject* pNewObj = new CNexus(*this);
	return pNewObj;
}