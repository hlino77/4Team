#include "stdafx.h"
#include "MyMouse.h"

#include "Transform.h"
#include "Collider.h"
#include "Graphics.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjectMgr.h"
#include "MainFrm.h"
#include "ToolView.h"

CMyMouse::CMyMouse()
{
}

CMyMouse::~CMyMouse()
{
	Release();
}

void CMyMouse::Initialize(void)
{
	m_eType = OBJID::OBJ_MOUSE;
	m_IsDead = false;

	m_dwTime = 0;

	m_pTransform = new CTransform;
	m_pCollider = new CCollider;
	//m_pGraphics = new CGraphics;

	m_pTransform->Initialize(this);
	m_pTransform->Scale(D3DXVECTOR3(0.f, 0.f, 0.f));
	m_pCollider->Initialize(this);
	//m_pGraphics->Initialize(this);

}

void CMyMouse::Release(void)
{
	Safe_Delete(m_pTransform);
	Safe_Delete(m_pCollider);
	//Safe_Delete(m_pGraphics);
}

void CMyMouse::OnCollisionEnter(CCollider * _pOther)
{
	vector<CGameObject*>& vecObj = CObjectMgr::Get_Instance()->GetObjList(_pOther->GetHost()->GetType());

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR).push_back(_pOther->GetHost()->Clone());

	for (auto iter = vecObj.begin(); iter != vecObj.end();)
	{
		if (*iter == _pOther->GetHost())
		{
			if ((*iter)->GetType() == OBJID::OBJ_BUILDING)
				pToolView->Get_Terrain()->Tile_Change((*iter)->GetTransform()->Position(), (*iter)->GetTransform()->LocalScale(), false);
			Safe_Delete(*iter);
			iter = vecObj.erase(iter);
		}
		else
			++iter;
	}
	
	
	

	m_pCollider->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pCollider->SetScale(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}

void CMyMouse::OnCollisionStay(CCollider * _pOther)
{
}

void CMyMouse::OnCollisionExit(CCollider * _pOther)
{

}

void CMyMouse::OnCollisionEnter(TILE * _pTIle)
{
	
}

void CMyMouse::OnCollisionStay(TILE * _pTIle)
{

}

void CMyMouse::OnCollisionExit(TILE * _pTIle)
{

}

CGameObject * CMyMouse::Clone()
{
	return nullptr;
}

int CMyMouse::Update(void)
{
	return 0;
}

int CMyMouse::LateUpdate(void)
{
	
	return 0;
}

void CMyMouse::Render()
{
}







