#include "stdafx.h"
#include "Gateway.h"
#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

CGateway::CGateway()
{
}

CGateway::CGateway(const CGateway & rhs)
{
	Initialize();
}

CGateway::~CGateway()
{
	Release();
}

void CGateway::Initialize(void)
{
	m_eType = OBJID::OBJ_BUILDING;
	m_IsDead = false;

	m_dwTime = 0;

	m_tData.strName = L"Gateway";

	m_tData.iMaxHp = 100;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 60;
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

int CGateway::Update(void)
{
	return 0;
}

int CGateway::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	return 0;
}

void CGateway::Render()
{
	m_pGraphics->Render(L"Gateway", L"Gateway", 1);
}

void CGateway::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CGateway::OnCollisionEnter(CCollider * _pOther)
{
}

void CGateway::OnCollisionStay(CCollider * _pOther)
{
}

void CGateway::OnCollisionExit(CCollider * _pOther)
{
}

void CGateway::OnCollisionEnter(TILE * _pTIle)
{
}

void CGateway::OnCollisionStay(TILE * _pTIle)
{
}

void CGateway::OnCollisionExit(TILE * _pTIle)
{
}

CGameObject * CGateway::Clone()
{
	CGameObject* pNewObj = new CGateway(*this);
	return pNewObj;
}
