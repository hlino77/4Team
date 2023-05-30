#pragma once
#include "Include.h"
class CCameraMgr
{
DECLARE_SINGLETON(CCameraMgr)
private:
	CCameraMgr();
	~CCameraMgr();

public:

	void		Initialize(void);
	void		Update(void);
	void		LateUpdate(void);
	void		Release(void);
	void		MouseUpdate(void);
	void		ScrollUpdate(void);

	const D3DXVECTOR3&				Get_RenderPos(const D3DXVECTOR3& _vPos);

	const float&					Get_ScrollX(void) const { return m_fScrollX; }
	const float&					Get_ScrollY(void) const { return m_fScrollY; }

	const D3DXVECTOR3&				Get_MousePos(void);
	

private:
	float m_fScrollX;
	float m_fScrollY;
	float m_fScrollSpeed;

	D3DXVECTOR3	m_vMouse;
};

