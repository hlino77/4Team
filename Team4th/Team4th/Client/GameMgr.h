#pragma once
#include "Include.h"

class CController;
class CGameMgr
{
DECLARE_SINGLETON(CGameMgr)

private:
	CGameMgr();
	~CGameMgr();

public:
	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Release(void);


	CController*	Get_Controller() { return m_pController; }

private:
	CController*	m_pController;
};

