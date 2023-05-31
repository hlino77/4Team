#pragma once
#include "GameObject.h"

class CController
{
public:
	CController();
	~CController();

	void	Initialize(void);
	void	Update(void);
	void	LateUpdate(void);
	void	Render(void);
	void	Release(void);

	vector<CGameObject*>&	GetControllObj() { return m_vecControllObj; }

private:
	vector<CGameObject*> m_vecControllObj;
};

