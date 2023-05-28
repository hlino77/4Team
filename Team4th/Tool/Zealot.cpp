#include "stdafx.h"
#include "Zealot.h"
#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"

//
#include "MainFrm.h"
#include "ToolView.h"
#include "Device.h"
#include "TextureMgr.h"

CZealot::CZealot()
{
}


CZealot::~CZealot()
{
}

void CZealot::Initialize(void)
{
	m_eType = OBJID::OBJ_UNIT_GROUND;
	m_IsDead = false;

	m_dwTime = 0;

#pragma region Data

	m_tData.strName = L"Zealot";
	
	m_tData.iMaxHp = 100;
	m_tData.iHp = m_tData.iMaxHp;
	m_tData.iMaxShield = 60;
	m_tData.iShield = m_tData.iMaxShield;
	m_tData.iAttack = 8;
	m_tData.iDeffnse = 1;
	m_tData.fMovefSpeed = 1.875f;
	m_tData.fAttackSpeed = 22.f;

	m_tData.iFireRange = 0;
	m_tData.iSightRange = 7;
	
	m_tData.iMaxEnergy = 0;
	m_tData.iEnergy = m_tData.iMaxEnergy;

#pragma endregion Data

	m_pTransform = new CTransform;
	m_pCollider = new CCollider;
	m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pCollider->Initialize(this);
	m_pGraphics->Initialize(this);

	// Temp
}

int CZealot::Update(void)
{
	m_pTransform->Update();

	return 0;
}

int CZealot::LateUpdate(void)
{
	m_pCollider->LateUpdate();
	return 0;
}

void CZealot::Render()
{
	//D3DXMATRIX	matWorld, matScale, matTrans;

	//CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	//CToolView*		pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	//
	//RECT	rc{};
	//GetClientRect(pMainView->m_hWnd, &rc);
	//// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴

	//float	fX = WINCX / float(rc.right - rc.left);
	//float	fY = WINCY / float(rc.bottom - rc.top);

	//D3DXMatrixIdentity(&matWorld);
	//D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	//D3DXMatrixTranslation(&matTrans,
	//	m_pTransform->Position().x - pMainView->GetScrollPos(0),
	//	m_pTransform->Position().y - pMainView->GetScrollPos(1),
	//	0.f);

	//matWorld = matScale * matTrans;

	////Set_Ratio(&matWorld, fX, fY);
	//matWorld._11 *= fX;
	//matWorld._21 *= fX;
	//matWorld._31 *= fX;
	//matWorld._41 *= fX;

	//matWorld._12 *= fY;
	//matWorld._22 *= fY;
	//matWorld._32 *= fY;
	//matWorld._42 *= fY;
	////
	//CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	//const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Zealot", L"Move12", 0);

	//float	_fX = pTexInfo->tImgInfo.Width / 2.f;
	//float	_fY = pTexInfo->tImgInfo.Height / 2.f;

	//CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
	//	nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
	//	&D3DXVECTOR3(_fX, _fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
	//	nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
	//	D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지

	m_pGraphics->Render(L"Zealot", L"Move12", 0);
}

void CZealot::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	Safe_Delete(m_pGraphics);
}

void CZealot::OnCollisionEnter(CCollider * _pOther)
{
}

void CZealot::OnCollisionStay(CCollider * _pOther)
{
}

void CZealot::OnCollisionExit(CCollider * _pOther)
{
}
