#pragma once
#include "Unit.h"
class CGroundUnit :
	public CUnit
{
public:
	CGroundUnit();
	virtual ~CGroundUnit();

public:
	virtual int	 Update() override;

	void	InitPath() { m_vecPath.clear(); m_iPathIndex = 0; }

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

