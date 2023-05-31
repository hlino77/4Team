#pragma once
#include "GameObject.h"
class CMyMouse : public CGameObject
{
public:
	CMyMouse();
	virtual ~CMyMouse();

	// CGameObject을(를) 통해 상속됨
	virtual void Initialize(void) override;
	virtual int Update(void) override;
	virtual int LateUpdate(void) override;
	virtual void Render() override;
	virtual void Release(void) override;
	virtual void OnCollisionEnter(CCollider * _pOther) override;
	virtual void OnCollisionStay(CCollider * _pOther) override;
	virtual void OnCollisionExit(CCollider * _pOther) override;
	virtual void OnCollisionEnter(TILE * _pTIle) override;
	virtual void OnCollisionStay(TILE * _pTIle) override;
	virtual void OnCollisionExit(TILE * _pTIle) override;
	virtual CGameObject * Clone() override;


	void		Key_Input(void);
private:


	D3DXVECTOR3 m_vStart;
	D3DXVECTOR3 m_vEnd;

	bool		m_bDragEnd;
};

