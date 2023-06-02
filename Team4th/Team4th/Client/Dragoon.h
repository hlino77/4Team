#pragma once
#include "GroundUnit.h"
class CDragoon :
	public CGroundUnit
{
public:
	CDragoon();
	CDragoon(const CDragoon& rhs);
	virtual ~CDragoon();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual int  LateUpdate(void)	override;
	virtual void Render()			override;
	virtual void Release(void)		override;

	virtual CGameObject * Clone() override;
};

