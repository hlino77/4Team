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
	// GetClientRect : ���� Ŭ���̾�Ʈ ������ rect ������ ����

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
		nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
		&D3DXVECTOR3(_fX, _fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
		nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����
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
