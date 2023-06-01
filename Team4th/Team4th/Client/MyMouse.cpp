#include "stdafx.h"
#include "MyMouse.h"

#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"
#include "KeyMgr.h"
#include "CameraMgr.h"
#include "GameMgr.h"
#include "Controller.h"
#include "Device.h"
#include "TextureMgr.h"

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
	//m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pTransform->Scale(D3DXVECTOR3(0.f, 0.f, 0.f));
	m_pCollider->Initialize(this);
	//m_pGraphics->Initialize(this);
	m_bDragStart = false;

	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Texture/Single/Mouse/0.png", TEX_SINGLE, L"Mouse", L"Mouse", 1)))
	{
		ERR_MSG(L"Mouse Create Failed");
		return;
	}

	m_MouseState = MOUSE_STATE::IDLE;

	m_iCurr = 0;

	m_iDir = 0;
}

int CMyMouse::Update(void)
{
	Key_Input();
	return 0;
}

int CMyMouse::LateUpdate(void)
{
	Update_ScrollDir();

	return 0;
}

void CMyMouse::Render()
{
	float m_fScrollX = CCameraMgr::Get_Instance()->Get_ScrollX();
	float m_fScrollY = CCameraMgr::Get_Instance()->Get_ScrollY();

	switch (m_MouseState)
	{
	case MOUSE_STATE::IDLE:
		if (m_iCurr > 2)
			m_iCurr = 0;

		Mouse_Render(m_iCurr, 0);

		++m_iCurr;
		break;
	case MOUSE_STATE::DRAG:
		if (m_bDragStart)
		{
			CDevice::Get_Instance()->Get_Sprite()->End();

			CDevice::Get_Instance()->Get_Line()->Begin();

			m_vDragPoint[0] = { m_vStart.x + m_fScrollX, m_vStart.y + m_fScrollY };
			m_vDragPoint[1] = { m_vEnd.x + m_fScrollX, m_vStart.y + m_fScrollY };
			m_vDragPoint[2] = { m_vEnd.x + m_fScrollX, m_vEnd.y + m_fScrollY };
			m_vDragPoint[3] = { m_vStart.x + m_fScrollX, m_vEnd.y + m_fScrollY };
			m_vDragPoint[4] = { m_vStart.x + m_fScrollX, m_vStart.y + m_fScrollY };

			CDevice::Get_Instance()->Get_Line()->Draw(m_vDragPoint, 5, D3DCOLOR_XRGB(0, 255, 0));

			CDevice::Get_Instance()->Get_Line()->End();

			CDevice::Get_Instance()->Get_Sprite()->Begin(D3DXSPRITE_ALPHABLEND);

			Mouse_Render(5, 0);
		}
		break;
	case MOUSE_STATE::SCROLL:
	{
		int iX;
		int iY;

		if (m_iDir & 0b10000000)
		{
			iX = 8;
			iY = 1;
		}
		else if (m_iDir & 0b01000000)
		{
			iX = 6;
			iY = 1;
		}
		else if (m_iDir & 0b00100000)
		{
			iX = 4;
			iY = 1;
		}
		else if (m_iDir & 0b00010000)
		{
			iX = 2;
			iY = 1;
		}
		else if (m_iDir & 0b00001000)
		{
			iX = 0;
			iY = 1;
		}
		else if (m_iDir & 0b00000100)
		{
			iX = 14;
			iY = 1;
		}
		else if (m_iDir & 0b00000010)
		{
			iX = 12;
			iY = 1;
		}
		else if (m_iDir & 0b00000001)
		{
			iX = 10;
			iY = 1;
		}

		Mouse_Render(iX, iY);
	}
		break;
	}
}

void CMyMouse::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	//Safe_Delete(m_pGraphics);
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
		vector<CGameObject*>& vecControllObj = CGameMgr::Get_Instance()->Get_Controller()->GetControllObj();
		//vecControllObj.clear(); // 이전 리스트 다 날리고 새로 받도록. 여기서 호출해버리면 하나 넣을 때마다 앞에꺼 날려버리게 됨. 대안을 찾자...

		vecControllObj.push_back(_pOther->GetHost());
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
		m_bDragStart = true;
		m_vStart = CCameraMgr::Get_Instance()->Get_MousePos();

		m_MouseState = MOUSE_STATE::DRAG;
	}
	else if (CKeyMgr::Get_Instance()->Key_Pressing(VK_LBUTTON))
	{
		m_vEnd = CCameraMgr::Get_Instance()->Get_MousePos();

		D3DXVECTOR3 vPos = (m_vStart + m_vEnd) * 0.5f;

		m_pCollider->SetPosition(vPos);
		m_pCollider->SetScale(D3DXVECTOR3(fabs(m_vStart.x - m_vEnd.x), fabs(m_vStart.y - m_vEnd.y), 0.0f));
	}
	else
	{
		if (MOUSE_STATE::DRAG == m_MouseState)
		{
			m_pCollider->SetPosition(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_pCollider->SetScale(D3DXVECTOR3(0.0f,0.0f,0.0f));
			m_bDragStart = false;

			m_MouseState = MOUSE_STATE::IDLE;
		}
	}
}

void CMyMouse::Mouse_Render(int iX, int iY)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	RECT rc = {50 * iX, 60 * iY,(50 * iX) + 50, (50 * iY) + 50};

	// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴
	D3DXVECTOR3 vMouse = CCameraMgr::Get_Instance()->Get_Mouse();

	if (m_MouseState == MOUSE_STATE::SCROLL)
	{
		if (vMouse.x > (WINCX - 20))
			vMouse.x = WINCX - 15;

		if (vMouse.x < 20.0f)
			vMouse.x = 15.0f;

		if (vMouse.y > (WINCY - 20))
			vMouse.y = WINCY;

		if (vMouse.y < 20.0f)
			vMouse.y = 30.0f;
	}

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		vMouse.x,
		vMouse.y,
		0.f);

	matWorld = matScale * matTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Mouse", L"Mouse", 1);

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		&rc,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
		&D3DXVECTOR3(25.f, 30.f, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
		nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
}

void CMyMouse::Update_ScrollDir(void)
{
	D3DXVECTOR3 vMouse = CCameraMgr::Get_Instance()->Get_Mouse();

	if (vMouse.x <= (WINCX - 20) && vMouse.x >= 20.0f && vMouse.y <= (WINCY - 20) && vMouse.y >= 20.0f)
	{
		if(m_MouseState != MOUSE_STATE::DRAG)
			m_MouseState = MOUSE_STATE::IDLE;
	}
	else
	{
		m_iDir = 0;

		m_MouseState = MOUSE_STATE::SCROLL;

		if (vMouse.x > (WINCX - 20))
			m_iDir |= 0b00001000;

		if (vMouse.x < 20.0f)
			m_iDir |= 0b10000000;

		if (vMouse.y >(WINCY - 20))
			m_iDir |= 0b00000010;

		if (vMouse.y < 20.0f)
			m_iDir |= 0b00100000;


		if (vMouse.x >(WINCX - 20) && vMouse.y < 20.0f)
		{
			m_iDir = 0;
			m_iDir |= 0b00010000;
		}

		if (vMouse.x >(WINCX - 20) && vMouse.y >(WINCY - 20))
		{
			m_iDir = 0;
			m_iDir |= 0b00000100;
		}

		if (vMouse.x < 20.0f && vMouse.y >(WINCY - 20))
		{
			m_iDir = 0;
			m_iDir |= 0b00000001;
		}

		if (vMouse.x < 20.0f && vMouse.y < 20.0f)
		{
			m_iDir = 0;
			m_iDir |= 0b01000000;
		}
	}


	

}
