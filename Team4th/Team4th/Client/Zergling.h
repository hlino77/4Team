#pragma once
#include "GroundUnit.h"
class CZergling :
	public CGroundUnit
{
public:
	CZergling();
	CZergling(const CZergling & rhs);
	virtual ~CZergling();

	// CGameObject��(��) ���� ��ӵ�
	virtual void Initialize(void)	override;
	virtual int  Update(void)		override;
	virtual int  LateUpdate(void)	override;
	virtual void Render()			override;
	virtual void Release(void)		override;

	virtual CGameObject * Clone()	override;
};

