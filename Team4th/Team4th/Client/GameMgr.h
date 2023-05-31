#pragma once
#include "Include.h"
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


private:

};

