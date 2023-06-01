#include "stdafx.h"
#include "Controller.h"
#include "GameObject.h"
#include "TextureMgr.h"
#include "CameraMgr.h"
#include "KeyMgr.h"
#include "Transform.h"
#include "GroundUnit.h"
#include "AirUnit.h"
#include "Device.h"

CController::CController()
{
}

CController::~CController()
{
}

void CController::Initialize(void)
{
	if (FAILED(CTextureMgr::Get_Instance()->Insert_Texture(L"../Texture/Stage/Texture/Single/Select/2.png", TEX_SINGLE, L"Select", L"Select", 1)))
	{
		ERR_MSG(L"Zealot Move12 Create Failed");
		return;
	}
}

void CController::Update(void)
{
	Key_Input();
}

void CController::LateUpdate(void)
{
}

void CController::Release(void)
{
}

void CController::Key_Input()
{
	if (CKeyMgr::Get_Instance()->Key_Down(VK_RBUTTON))
	{
		D3DXVECTOR3 vTargetPos = CCameraMgr::Get_Instance()->Get_MousePos();

		for (auto& iter : m_vecControllObj)
		{
			if (OBJID::OBJ_UNIT_GROUND == iter->GetType())
			{
				static_cast<CGroundUnit*>(iter)->SetTargetPos(vTargetPos);
				static_cast<CGroundUnit*>(iter)->InitPath();
				static_cast<CGroundUnit*>(iter)->SetState(UNIT_STATE::MOVE);
			}
			else if (OBJID::OBJ_UNIT_AIR == iter->GetType())
			{
				static_cast<CAirUnit*>(iter)->SetTargetPos(vTargetPos);
				static_cast<CUnit*>(iter)->SetState(UNIT_STATE::MOVE);
			}
		}
	}
}

void CController::Render(void)
{
	float m_fScrollX = CCameraMgr::Get_Instance()->Get_ScrollX();
	float m_fScrollY = CCameraMgr::Get_Instance()->Get_ScrollY();

	if (!m_vecControllObj.empty())
	{
		for (auto& iter : m_vecControllObj)
		{
			D3DXMATRIX	matWorld, matScale, matTrans;

			// GetClientRect : ���� Ŭ���̾�Ʈ ������ rect ������ ����

			//float fScale = iter->GetTransform()->LocalScale().x / 224.0f;
			float fScale = 1.0f;

			D3DXMatrixIdentity(&matWorld);
			D3DXMatrixScaling(&matScale, fScale, fScale, 1.f);
			D3DXMatrixTranslation(&matTrans,
				iter->GetTransform()->Position().x + m_fScrollX,
				iter->GetTransform()->Position().y + (iter->GetTransform()->LocalScale().y * 0.5f) + m_fScrollY,
				0.f);

			matWorld = matScale * matTrans;
			
			CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

			const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Select", L"Select", 1);

			float	_fX = pTexInfo->tImgInfo.Width / 2.f;
			float	_fY = pTexInfo->tImgInfo.Height / 2.f;

			CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
				nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
				&D3DXVECTOR3(_fX, _fY, 0.f),		// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
				nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
				D3DCOLOR_ARGB(255, 0, 0, 0)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����
		}
	}

}

