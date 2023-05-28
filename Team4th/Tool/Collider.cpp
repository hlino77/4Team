#include "stdafx.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"
#include "SelectGDI.h"
#include "Device.h"
//
#include "MainFrm.h"
#include "ToolView.h"
#include "Device.h"
#include "TextureMgr.h"
//

UINT CCollider::g_iNextID = 0;

CCollider::CCollider() : CComponent(), m_iCol(0), m_vPosition(), m_vScale()
{
	m_iID = g_iNextID++;
}

CCollider::CCollider(const CCollider & rhs)
{
	m_pHost = nullptr;
	m_vScale = rhs.m_vScale;
	m_iID = g_iNextID++;
}


CCollider::~CCollider()
{
}

void CCollider::Initialize(CGameObject * _pHost)
{
	__super::Initialize(_pHost);

	m_vPosition = m_pHost->GetTransform()->Position();
	m_vScale = D3DXVECTOR3(m_pHost->GetTransform()->LocalScale().x, m_pHost->GetTransform()->LocalScale().y, 0.f);
	
	m_vVertices[0] = D3DXVECTOR3(-m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f);
	m_vVertices[1] = D3DXVECTOR3(m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f);
	m_vVertices[2] = D3DXVECTOR3(m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f);
	m_vVertices[3] = D3DXVECTOR3(-m_vScale.x / 2.f, m_vScale.y / 2.f, 0.f);
	m_vVertices[4] = D3DXVECTOR3(-m_vScale.x / 2.f, -m_vScale.y / 2.f, 0.f);
	
	//for (int i = 0; i < 5; ++i)
	//	m_vOriginPoints[i] = m_vVertices[i];
}

void CCollider::LateUpdate()
{
	assert(0 <= m_iCol);
	/*if (m_iCol < 0)
		m_iCol = 0;*/

	m_vPosition = m_pHost->GetTransform()->Position();
	int a = 0;
	
}

void CCollider::Render(LPD3DXLINE _pLine)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	RECT	rc{};

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pMainView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	GetClientRect(pMainView->m_hWnd, &rc);
	// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_vPosition.x - pMainView->GetScrollPos(0),
		m_vPosition.y - pMainView->GetScrollPos(1),
		0.f);

	matWorld = matScale * matTrans;

	//Set_Ratio(&matWorld, fX, fY);
	matWorld._11 *= fX;
	matWorld._21 *= fX;
	matWorld._31 *= fX;
	matWorld._41 *= fX;

	matWorld._12 *= fY;
	matWorld._22 *= fY;
	matWorld._32 *= fY;
	matWorld._42 *= fY;

	D3DXVECTOR2	vVertices[5];
	for (int i = 0; i < 5; ++i)
	{
		vVertices[i].x = m_vVertices[i].x;
		vVertices[i].y = m_vVertices[i].y;
		D3DXVec2TransformCoord(&vVertices[i], &vVertices[i], &matWorld);
	}

	if (m_iCol)
		_pLine->Draw(vVertices, 5, D3DCOLOR_XRGB(255, 0, 0));
	else
		_pLine->Draw(vVertices, 5, D3DCOLOR_XRGB(0, 255, 0));
}

void CCollider::OnCollisionEnter(CCollider * _pOther)
{
	++m_iCol;
	m_pHost->OnCollisionEnter(_pOther);
}

void CCollider::OnCollisionStay(CCollider * _pOther)
{
	m_pHost->OnCollisionStay(_pOther);
}

void CCollider::OnCollisionExit(CCollider * _pOther)
{
	--m_iCol;
	m_pHost->OnCollisionExit(_pOther);
}
