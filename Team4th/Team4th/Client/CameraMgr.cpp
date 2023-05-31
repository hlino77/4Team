#include "stdafx.h"
#include "CameraMgr.h"
#include "TimeMgr.h"


IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr() : m_fScrollSpeed(500.0f), m_fScrollX(0.0f), m_fScrollY(0.0f)
{
}


CCameraMgr::~CCameraMgr()
{
}

void CCameraMgr::Initialize(void)
{

}

void CCameraMgr::Update(void)
{
	MouseUpdate();

	ScrollUpdate();

	
}

void CCameraMgr::LateUpdate(void)
{

}

void CCameraMgr::Release(void)
{

}

void CCameraMgr::MouseUpdate(void)
{
	POINT	Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(g_hWnd, &Mouse);



	m_vMouse.x = Mouse.x;
	m_vMouse.y = Mouse.y;
	m_vMouse.z = 0.0f;
}

void CCameraMgr::ScrollUpdate(void)
{
	if (m_vMouse.x > (WINCX - 20))
		m_fScrollX -= m_fScrollSpeed * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_vMouse.x < 20.0f)
		m_fScrollX += m_fScrollSpeed * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_vMouse.y > (WINCY - 20))
		m_fScrollY -= m_fScrollSpeed * CTimeMgr::Get_Instance()->Get_TimeDelta();

	if (m_vMouse.y < 20.0f)
		m_fScrollY += m_fScrollSpeed * CTimeMgr::Get_Instance()->Get_TimeDelta();


	if (m_fScrollX > 0.0f)
		m_fScrollX = 0.0f;

	if (m_fScrollX < -(MAPCX - WINCX))
		m_fScrollX = -(MAPCX - WINCX);


	if (m_fScrollY > 0.0f)
		m_fScrollY = 0.0f;

	if (m_fScrollY < -(MAPCY - WINCY))
		m_fScrollY = -(MAPCY - WINCY);

}

const D3DXVECTOR3 & CCameraMgr::Get_RenderPos(const D3DXVECTOR3 & _vPos)
{
	// TODO: 여기에 반환 구문을 삽입합니다.
	D3DXVECTOR3 vMousePos;

	return vMousePos;

}


