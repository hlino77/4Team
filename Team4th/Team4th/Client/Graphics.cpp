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
		nullptr,							// ����� �̹��� ������ ���� Rect �ּ�, null�� ��� �̹����� 0, 0 �������� ���
		&D3DXVECTOR3(_fX, _fY, 0.f),			// ����� �̹����� �߽��࿡ ���� vector3 �ּ�, null�� ��� �̹����� 0, 0�� �߽� ��ǥ
		nullptr,							// ��ġ ��ǥ�� ���� vector3 �ּ�, null�� ��� ��ũ�� ���� 0, 0��ǥ ���
		D3DCOLOR_ARGB(255, 255, 255, 255)); // ����� �̹����� ���� ���� ��, 0xffffffff�� �Ѱ��ָ� ���� ���� ����
}