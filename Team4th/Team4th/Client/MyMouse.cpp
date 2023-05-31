#include "stdafx.h"
#include "MyMouse.h"

#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "GameMgr.h"
#include "Controller.h"

CMyMouse::CMyMouse()
{
}

CMyMouse::~CMyMouse()
{
	Release();
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

}

void CMyMouse::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CMyMouse::OnCollisionEnter(CCollider * _pOther)
{

}

void CMyMouse::OnCollisionStay(CCollider * _pOther)
{

}

void CMyMouse::OnCollisionExit(CCollider * _pOther)
{
	if (!m_bDragStart)
	{
		CGameMgr::Get_Instance()->Get_Controller()->GetControllObj().push_back(_pOther->GetHost());
	}

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
		m_vStart = CCameraMgr::Get_Instance()->Get_MousePos();
	}

	if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_vEnd = CCameraMgr::Get_Instance()->Get_MousePos();
	}
	else
	{

	}

	
}
