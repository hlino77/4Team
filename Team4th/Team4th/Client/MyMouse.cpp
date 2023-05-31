#include "stdafx.h"
#include "MyMouse.h"

#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "Device.h"

CMyMouse::CMyMouse()
{
}


CMyMouse::~CMyMouse()
{
}

void CMyMouse::Initialize(void)
{
	m_eType = OBJID::OBJ_MOUSE;
	m_IsDead = false;

	m_dwTime = 0;


	m_pTransform = new CTransform;
	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pTransform->Scale(D3DXVECTOR3(0.f, 0.f, 0.f));
	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);
	m_bDragStart = false;
}

int CMyMouse::Update(void)
{
	Key_Input();


	return 0;
}

int CMyMouse::LateUpdate(void)
{


	return 0;
}

void CMyMouse::Render()
{
	float m_fScrollX = CCameraMgr::Get_Instance()->Get_ScrollX();
	float m_fScrollY = CCameraMgr::Get_Instance()->Get_ScrollY();

	if (m_bDragStart)
	{
		CDevice::Get_Instance()->Get_Sprite()->End();

		CDevice::Get_Instance()->Get_Line()->Begin();

		m_vDragPoint[0] = { m_vStart.x + m_fScrollX, m_vStart.y + m_fScrollY };
		m_vDragPoint[1] = { m_vEnd.x + m_fScrollX, m_vStart.y + m_fScrollY };
		m_vDragPoint[2] = {m_vEnd.x + m_fScrollX, m_vEnd.y + m_fScrollY };
		m_vDragPoint[3] = { m_vStart.x + m_fScrollX, m_vEnd.y + m_fScrollY };
		m_vDragPoint[4] = { m_vStart.x + m_fScrollX, m_vStart.y + m_fScrollY };

		CDevice::Get_Instance()->Get_Line()->Draw(m_vDragPoint, 5 ,D3DCOLOR_XRGB(0, 255, 0));



		CDevice::Get_Instance()->Get_Line()->End();

		CDevice::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);
	}
}

void CMyMouse::Release(void)
{
}

void CMyMouse::OnCollisionEnter(CCollider * _pOther)
{
}

void CMyMouse::OnCollisionStay(CCollider * _pOther)
{

}

void CMyMouse::OnCollisionExit(CCollider * _pOther)
{

}

void CMyMouse::OnCollisionEnter(TILE * _pTIle)
{
}

void CMyMouse::OnCollisionStay(TILE * _pTIle)
{

}

void CMyMouse::OnCollisionExit(TILE * _pTIle)
{
}

CGameObject * CMyMouse::Clone()
{
	return nullptr;
}

void CMyMouse::Key_Input(void)
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_LBUTTON))
	{
		m_bDragStart = true;
		m_vStart = CCameraMgr::Get_Instance()->Get_MousePos();
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_vEnd = CCameraMgr::Get_Instance()->Get_MousePos();
	}
	else
	{
		D3DXVECTOR3 vPos = (m_vStart + m_vEnd) * 0.5f;

		m_pCollider->SetPosition(vPos);
		m_pCollider->SetScale(D3DXVECTOR3(fabs(m_vStart.x - m_vEnd.x), fabs(m_vStart.y - m_vEnd.y), 0.0f));
		m_bDragStart = false;
	}

	
}
