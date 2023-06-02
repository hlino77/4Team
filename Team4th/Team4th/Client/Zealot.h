#pragma once
#include "GroundUnit.h"

class CZealot :
	public CGroundUnit
{
public:
	CZealot();
	CZealot(const CZealot& rhs);
	virtual ~CZealot();

	// CGroundUnit을(를) 통해 상속됨
	virtual void Initialize(void)	override;
	virtual int	 Update(void)		override;
	virtual int	 LateUpdate(void)	override;
	virtual void Render()			override;
	virtual void Release(void)		override;

	virtual CGameObject*	Clone()	override;

//protected:
//	OBJID			m_eType;
//	bool			m_IsDead;
//
//	DWORD			m_dwTime;
//
//protected:
//	CTransform*		m_pTransform;
//	CCollider*		m_pCollider;
//	//CGraphics*	m_pGraphics;
//
//	UNITDATA		m_tData;
};

