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

			// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴

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
				nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
				&D3DXVECTOR3(_fX, _fY, 0.f),		// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
				nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
				D3DCOLOR_ARGB(255, 0, 0, 0)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
		}
	}

}

