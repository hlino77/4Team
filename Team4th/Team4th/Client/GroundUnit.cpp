#include "stdafx.h"
#include "GroundUnit.h"
#include "Transform.h"
#include "Collider.h"

CGroundUnit::CGroundUnit()
{
}


CGroundUnit::~CGroundUnit()
{
}

int CGroundUnit::Update()
{
	if (UNIT_STATE::IDLE == m_eState)
		m_vTargetPos = m_pTransform->Position();
	else if (UNIT_STATE::MOVE == m_eState)
		CGroundUnit::Move();

	return 0;
}

void CGroundUnit::OnCollisionEnter(TILE * _pTIle)
{
	D3DXVECTOR3 vOtherPos = _pTIle->vPos;
	D3DXVECTOR3 vOtherScale = _pTIle->vSize;

	D3DXVECTOR3 vThisPos = GetCollider()->GetPosition();
	D3DXVECTOR3 vThisScale = GetCollider()->GetScale();

	float fWidth = fabs(vOtherPos.x - vThisPos.x);
	float fHeight = fabs(vOtherPos.y - vThisPos.y);
	float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
	float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

	if (fRadiusX < fRadiusY)
	{
		if (vOtherPos.x < vThisPos.x)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusX, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusX, 0.f, 0.f));
	}
	else
	{
		if (vOtherPos.y < vThisPos.y)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusY, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusY, 0.f, 0.f));
	}
}

void CGroundUnit::OnCollisionStay(TILE * _pTIle)
{
	D3DXVECTOR3 vOtherPos = _pTIle->vPos;
	D3DXVECTOR3 vOtherScale = _pTIle->vSize;

	D3DXVECTOR3 vThisPos = GetCollider()->GetPosition();
	D3DXVECTOR3 vThisScale = GetCollider()->GetScale();

	float fWidth = fabs(vOtherPos.x - vThisPos.x);
	float fHeight = fabs(vOtherPos.y - vThisPos.y);
	float fRadiusX = (vOtherScale.x / 2.f + vThisScale.x / 2.f) - fWidth;
	float fRadiusY = (vOtherScale.y / 2.f + vThisScale.y / 2.f) - fHeight;

	if (fRadiusX < fRadiusY)
	{
		if (vOtherPos.x < vThisPos.x)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusX, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusX, 0.f, 0.f));
	}
	else
	{
		if (vOtherPos.y < vThisPos.y)
			m_pTransform->Translate(D3DXVECTOR3(fRadiusY, 0.f, 0.f));
		else
			m_pTransform->Translate(D3DXVECTOR3(-fRadiusY, 0.f, 0.f));
	}
}

void CGroundUnit::OnCollisionExit(TILE * _pTIle)
{
}

void CGroundUnit::Move()
{
	D3DXVECTOR3 vDistance = m_vTargetPos - m_pTransform->Position();
	float&	fSpeed = m_tData.fMovefSpeed;

	if (fabs(vDistance.x) > fSpeed && fabs(vDistance.y) > fSpeed)
	{
		D3DXVECTOR3 vDistNorm;
		D3DXVec3Normalize(&vDistNorm, &vDistance);
		m_pTransform->Translate(fSpeed * vDistNorm);
	}
	else
	{
		m_vTargetPos = m_pTransform->Position();
		m_eState = UNIT_STATE::IDLE;
	}
}
