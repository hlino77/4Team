#pragma once
#include "Component.h"
#include "Include.h"

class CTransform :
	public CComponent
{
public:
	CTransform();
	virtual ~CTransform();

	virtual void Initialize(CGameObject* _pHost) override;
	void	Update();

	void	Translate(D3DXVECTOR3& _vTrans);
	void	Rotate(float _fRotate);
	void	Scale(D3DXVECTOR3& _vScale);

	const D3DXVECTOR3&	Position() const	{ return m_tInfo.vPos; }
	const D3DXVECTOR3&	Rotation() const	{ return m_tInfo.vDir; }
	const D3DXVECTOR3&	LocalScale() const	{ return m_tInfo.vSize; }

private:
	INFO	m_tInfo;
};

