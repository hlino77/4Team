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
	void	Release(void);


	void	Add_Obj(vector<CGameObject*>* _pvecObj) { m_vecControllObj.swap(*_pvecObj); }
private:
	vector<CGameObject*> m_vecControllObj;
};

