#pragma once
#include "GroundUnit.h"

class CProbe :
	public CGroundUnit
{
public:
	CProbe();
	CProbe(const CProbe& rhs);
	virtual ~CProbe();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize(void)	override;
	virtual int	 Update(void)		override;
	virtual int	 LateUpdate(void)	override;
	virtual void Render()			override;
	virtual void Release(void)		override;

	virtual void OnCollisionEnter(CCollider * _pOther)	override;
	virtual void OnCollisionStay(CCollider * _pOther)	override;
	virtual void OnCollisionExit(CCollider * _pOther)	override;

	virtual CGameObject * Clone() override;
};

