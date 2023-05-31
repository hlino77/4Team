#include "stdafx.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Transform.h"

#include "Device.h"
#include "TextureMgr.h"
#include "CameraMgr.h"

CGraphics::CGraphics()
{
}

CGraphics::CGraphics(const CGraphics& rhs) : CGraphics()
{
}

CGraphics::~CGraphics()
{
}

void CGraphics::Initialize(CGameObject * _pHost)
{
	__super::Initialize(_pHost);
}

void CGraphics::Render(const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pHost->GetTransform()->Position().x + CCameraMgr::Get_Instance()->Get_ScrollX(),
		m_pHost->GetTransform()->Position().y + CCameraMgr::Get_Instance()->Get_ScrollY(),
		0.f);

	matWorld = matScale * matTrans;

	CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

	const TEXINFO*	pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(pObjKey, pStateKey, iCount);

	float	_fX = pTexInfo->tImgInfo.Width / 2.f;
	float	_fY = pTexInfo->tImgInfo.Height / 2.f;

	CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
		nullptr,							// 출력할 이미지 영역에 대한 Rect 주소, null인 경우 이미지의 0, 0 기준으로 출력
		&D3DXVECTOR3(_fX, _fY, 0.f),			// 출력할 이미지의 중심축에 대한 vector3 주소, null인 경우 이미지의 0, 0이 중심 좌표
		nullptr,							// 위치 좌표에 대한 vector3 주소, null인 경우 스크린 상의 0, 0좌표 출력
		D3DCOLOR_ARGB(255, 255, 255, 255)); // 출력할 이미지와 섞을 색상 값, 0xffffffff를 넘겨주면 원본 색상 유지
}