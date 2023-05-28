#pragma once
#include "Component.h"

class CCollider :
	public CComponent
{
public:
	CCollider();
	CCollider(const CCollider& rhs);
	CCollider& operator= (CCollider& _origin) = delete;
	virtual ~CCollider();

	virtual void	Initialize(CGameObject* _pHost) override;

	void			LateUpdate();
	void			Render(LPD3DXLINE _pLine);

public:
	D3DXVECTOR3 GetPosition() { return m_vPosition; }
	D3DXVECTOR3 GetScale() { return m_vScale; }
	UINT		GetID() { return m_iID; }

	void SetPosition(D3DXVECTOR3 _vPosition) { m_vPosition = _vPosition; }
	void SetScale(D3DXVECTOR3 _vScale) { m_vScale = _vScale; }

public:
	virtual void	OnCollisionEnter(CCollider* _pOther);
	virtual void	OnCollisionStay(CCollider* _pOther);
	virtual void	OnCollisionExit(CCollider* _pOther);

private:

	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3		m_vScale;

	UINT			m_iID;
	static UINT		g_iNextID;

	int				m_iCol;

	D3DXVECTOR3		m_vOriginPoints[5];
	D3DXVECTOR3		m_vVertices[5];
};

