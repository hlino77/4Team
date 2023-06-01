#pragma once
#include "Unit.h"
class CGroundUnit :
	public CUnit
{
public:
	CGroundUnit();
	virtual ~CGroundUnit();

public:
	virtual int	Update() override;

	virtual void OnCollisionEnter(TILE* _pTIle)			override;
	virtual void OnCollisionStay(TILE* _pTIle)			override;
	virtual void OnCollisionExit(TILE* _pTIle)			override;

public:
	virtual void Move() override;
};

