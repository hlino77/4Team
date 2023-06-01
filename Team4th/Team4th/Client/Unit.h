#pragma once
#include "GameObject.h"
class CUnit :
	public CGameObject
{
public:
	CUnit();
	virtual ~CUnit();

	virtual void Move() PURE;

	const D3DXVECTOR3&	GetTargetPos() { return m_vTargetPos; }
	const UNIT_STATE&		GetState() { return m_eState; }

	void	SetTargetPos(D3DXVECTOR3 _pTargetPos) { m_vTargetPos = _pTargetPos; }
	void	SetState(UNIT_STATE _eState) { m_eState = _eState; }

protected:
	CGameObject*	m_pTarget;
	D3DXVECTOR3		m_vTargetPos;
	UNIT_STATE		m_eState;
};

