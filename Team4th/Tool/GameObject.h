#pragma once
#include "Include.h"

class CTransform;
class CCollider;
class CGraphics;
class CGameObject
{
public:
	CGameObject();
	virtual ~CGameObject();

public:
	virtual void	Initialize(void)	PURE;
	virtual int		Update(void)		PURE;
	virtual int		LateUpdate(void)	PURE;
	virtual void	Render()			PURE;
	virtual void	Release(void)		PURE;

public:
	bool			IsDead() { return m_IsDead; }
	OBJID			GetType() { return m_eType; }

	int				GetMaxHp() { return m_tData.iMaxHp; }
	int				GetHp() { return m_tData.iHp; }

	void			SetHp(int _iHp) { m_tData.iHp = _iHp; }
	
	void			SetDead(bool _isDead) { m_IsDead = _isDead; }

	CTransform*		GetTransform() { return m_pTransform; }
	CCollider*		GetCollider() { return m_pCollider; }
	CGraphics*		GetGraphics() { return m_pGraphics; }

	virtual void	OnCollisionEnter(CCollider* _pOther)	PURE;
	virtual void	OnCollisionStay(CCollider* _pOther)		PURE;
	virtual void	OnCollisionExit(CCollider* _pOther)		PURE;

protected:
	OBJID			m_eType;
	bool			m_IsDead;

	DWORD			m_dwTime;

protected:
	CTransform*		m_pTransform;
	CCollider*		m_pCollider;
	CGraphics*		m_pGraphics;

	UNITDATA		m_tData;
};

