#include "stdafx.h"
#include "Collider.h"
#include "Transform.h"
#include "GameObject.h"
#include "Device.h"
//

#include "Device.h"
#include "TextureMgr.h"
#include "CameraMgr.h"
//

//UINT CCollider::g_iNextID = 0;

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
	/*assert(0 <= m_iCol);*/
	/*if (m_iCol < 0)
		m_iCol = 0;*/

	m_vPosition = m_pHost->GetTransform()->Position();
	int a = 0;
	
}

void CCollider::Render(LPD3DXLINE _pLine)
{
	D3DXMATRIX	matWorld, matScale, matTrans;

	// GetClientRect : 현재 클라이언트 영역의 rect 정보를 얻어옴

	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixTranslation(&matTrans,
		m_vPosition.x + CCameraMgr::Get_Instance()->Get_ScrollX(),
		m_vPosition.y + CCameraMgr::Get_Instance()->Get_ScrollY(),
		0.f);

	matWorld = matScale * matTrans;

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

void CCollider::OnCollisionEnter(TILE * _pTile)
{
	++m_iCol;
	m_pHost->OnCollisionEnter(_pTile);
}

void CCollider::OnCollisionStay(TILE * _pTile)
{
	m_pHost->OnCollisionStay(_pTile);
}

void CCollider::OnCollisionExit(TILE * _pTile)
{
	--m_iCol;
	m_pHost->OnCollisionExit(_pTile);
}
