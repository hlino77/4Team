#include "stdafx.h"
#include "Transform.h"


CTransform::CTransform()
{
	/*D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(32.f, 32.f, 0.f);
	m_tInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(0.f, 0.f, 0.f);*/
}

CTransform::CTransform(const CTransform & rhs)
{
	/*D3DXMatrixIdentity(&m_tInfo.matWorld);
	m_tInfo.vPos = rhs.m_tInfo.vPos;
	m_tInfo.vSize = rhs.m_tInfo.vSize;
	m_tInfo.vDir = rhs.m_tInfo.vDir;
	m_tInfo.vLook = rhs.m_tInfo.vLook;*/
}

CTransform::~CTransform()
{
}

void CTransform::Initialize(CGameObject * _pHost)
{
	__super::Initialize(_pHost);

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	/*D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotate, 0.f); // or 1.5f * D3DX_PI
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);

	m_tInfo.matWorld = matScale * matRotate * matTrans;*/

	//Temp m_tInfo;
	m_tInfo.vPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vSize = D3DXVECTOR3(1.f, 1.f, 0.f);
	m_tInfo.vDir = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_tInfo.vLook = D3DXVECTOR3(0.f, 0.f, 0.f);
}

void CTransform::Update()
{
	/*D3DXMATRIX	matScale, matRotate, matTrans;

	D3DXMatrixIdentity(&m_tInfo.matWorld);

	D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
	D3DXMatrixRotationZ(&matRotate, 0.f); // or 1.5f * D3DX_PI
	D3DXMatrixTranslation(&matTrans, 100.f, 100.f, 0.f);

	m_tInfo.matWorld = matScale * matRotate * matTrans;*/
}

void CTransform::Translate(D3DXVECTOR3& _vTrans)
{
	D3DXMATRIX	matTrans;
	D3DXMatrixTranslation(&matTrans, _vTrans.x, _vTrans.y, _vTrans.z);
	D3DXVec3TransformCoord(&m_tInfo.vPos, &m_tInfo.vPos, &matTrans);
}

void CTransform::Translate(const D3DXVECTOR3& _vTrans)
{
	Translate(const_cast<D3DXVECTOR3&>(_vTrans));
}

void CTransform::Rotate(float _fRotate)
{
	D3DXMATRIX	matRotate;
	D3DXMatrixRotationZ(&matRotate, _fRotate);
	D3DXVec3TransformCoord(&m_tInfo.vDir, &m_tInfo.vDir, &matRotate);
}

void CTransform::Scale(D3DXVECTOR3& _vScale)
{
	D3DXMATRIX	matScale;
	D3DXMatrixScaling(&matScale, _vScale.x, _vScale.y, _vScale.z);
	D3DXVec3TransformCoord(&m_tInfo.vSize, &m_tInfo.vSize, &matScale);
	// 나중에 정점에 다 곱해주든가 하자
}
