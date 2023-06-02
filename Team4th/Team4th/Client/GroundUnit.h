#pragma once
#include "Unit.h"

class CCollider;
class CGroundUnit :
	public CUnit
{
public:
	CGroundUnit();
	virtual ~CGroundUnit();

public:
	virtual int	 Update()		override;
	virtual	int  LateUpdate()	override;
	virtual void Render()		override;

	void		 InitPath() { m_vecPath.clear(); m_iPathIndex = 0; }

	virtual void OnCollisionEnter(CCollider* _pOther)	override;
	virtual void OnCollisionStay(CCollider* _pOther)	override;
	virtual void OnCollisionExit(CCollider* _pOther)	override;

	virtual void OnCollisionEnter(TILE* _pTIle)			override;
	virtual void OnCollisionStay(TILE* _pTIle)			override;
	virtual void OnCollisionExit(TILE* _pTIle)			override;

public:
	virtual void Move() override;

private:
	bool		Movable(Pos pos);
	void		AStar();

	vector<Pos>	m_vecPath;
	UINT		m_iPathIndex;
};

