#include "stdafx.h"
#include "Graphics.h"
#include "GameObject.h"
#include "Transform.h"

#include "MainFrm.h"
#include "ToolView.h"
#include "Device.h"
#include "TextureMgr.h"

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
	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	Set_MainView(dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1)));
}

void CGraphics::Render(const TCHAR * pObjKey, const TCHAR * pStateKey, const int & iCount)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	RECT	rc{};
	GetClientRect(m_pMainView->m_hWnd, &rc);
	// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_pHost->GetTransform()->Position().x - m_pMainView->GetScrollPos(0),
		m_pHost->GetTransform()->Position().y - m_pMainView->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;

	Set_Ratio(&matWorld, fX, fY);
	
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

void CGraphics::Set_Ratio(D3DXMATRIX * pOut, float fRatioX, float fRatioY)
{
	pOut->_11 *= fRatioX;
	pOut->_21 *= fRatioX;
	pOut->_31 *= fRatioX;
	pOut->_41 *= fRatioX;

	pOut->_12 *= fRatioY;
	pOut->_22 *= fRatioY;
	pOut->_32 *= fRatioY;
	pOut->_42 *= fRatioY;
}
