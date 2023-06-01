#pragma once

class CGameObject;
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

	void	Key_Input();

	vector<CGameObject*>&	GetControllObj() { return m_vecControllObj; }

	void	ClearList(void) { m_vecControllObj.clear(); }
private:
	vector<CGameObject*> m_vecControllObj;
};

