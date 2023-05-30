
// ToolView.cpp : CToolView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tool.h"
#endif

#include "ToolDoc.h"
#include "ToolView.h"
#include "Device.h"
#include "TextureMgr.h"
#include "ObjectMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "CollisionMgr.h"
#include "Collider.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

HWND		g_hWnd;
UINT		g_iNextID = 0;

// CToolView

IMPLEMENT_DYNCREATE(CToolView, CScrollView)

BEGIN_MESSAGE_MAP(CToolView, CScrollView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CToolView ����/�Ҹ�

CToolView::CToolView() : m_pTerrain(nullptr)
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
	g_hWnd = m_hWnd;

	CScrollView::OnInitialUpdate();

	// SetScrollSizes : ��ũ�� ���� ����� �����ϴ� �Լ�
	// MM_TEXT : �ȼ� ������ �����ϰڴٴ� �ɼ�
	// ��ũ�� ���� ������, ��ũ�� ���� ������

	SetScrollSizes(MM_TEXT, CSize(MAPCX, MAPCY));

	// AfxGetMainWnd : ������ ���� â�� �ּҸ� ��ȯ�ϴ� �Լ�
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : ���� â�� ��Ʈ ������ ������ �Լ�
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : �Ű� ������� ��Ʈ�� ������ �����ϴ� �Լ�
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	// GetClientRect : ���� viewâ�� RECT ������ ������ �Լ�
	GetClientRect(&rcMainView);

	float		fRowFrm = float(rcWnd.right - rcMainView.right);
	float		fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	//SetWindowPos : �Ű� ������� ���Ӱ� ������ ��ġ�� ũ�⸦ �����ϴ� �Լ�
	 // (��ġ�� �������� Z������ ���� ������, X��ǥ, Y��ǥ, ���� ũ��, ���� ũ��, ��ġ�� �������� ũ��� ��ġ ���� �ɼ�)
	pMainFrm->SetWindowPos(nullptr,  // ���� ������ ���ϱ� ������ NULL
							0, 
							0, 
							int(WINCX + fRowFrm),
							int(WINCY + fColFrm), 
							SWP_NOZORDER);	// ���� ������ �����ϰڴٴ� �ɼ�


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	if (FAILED(CDevice::Get_Instance()->Initialize()))
	{
		AfxMessageBox(L"Device Create Failed");
		return;
	}

	m_pTerrain = new CTerrain;

	if (FAILED(m_pTerrain->Initialize()))
	{
		AfxMessageBox(L"Terrain Init Failed");
		return;
	}

	m_eToolType = TOOLTYPE::TOOL_TERRAIN;
	
	CObjectMgr::Get_Instance()->Initialize();
	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_ONCURSOR, OBJID::OBJ_UNIT_GROUND);
	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_ONCURSOR, OBJID::OBJ_BUILDING);
	CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_ONCURSOR, OBJID::OBJ_TILE);
	//CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_UNIT_GROUND, OBJID::OBJ_UNIT_GROUND);
	//CCollisionMgr::Get_Instance()->CheckGroup(OBJID::OBJ_UNIT_GROUND, OBJID::OBJ_BUILDING);

	m_pTerrain->Set_MainView(this);
}

void CToolView::OnDraw(CDC* /*pDC*/)
{
	CToolDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CObjectMgr::Get_Instance()->Update();
	CObjectMgr::Get_Instance()->LateUpdate();
	CCollisionMgr::Get_Instance()->LateUpdate();

	CDevice::Get_Instance()->Render_Begin();

	m_pTerrain->Render();
	m_pTerrain->Collider_Render();

	CObjectMgr::Get_Instance()->Render();

	

	m_pTerrain->Grid_Render();


	CDevice::Get_Instance()->Render_End();
}
void CToolView::OnDestroy()
{
	CScrollView::OnDestroy();

	Safe_Delete(m_pTerrain);

	CTextureMgr::Get_Instance()->Destroy_Instance();
	CDevice::Get_Instance()->Destroy_Instance();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
#pragma region �Ⱥ�
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView �μ�

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CToolView ����

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView �޽��� ó����


// CToolView �׸���
#pragma endregion �Ⱥ�

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnLButtonDown(nFlags, point);

	// point : ���콺 ��ǥ�� ���� ����.

	switch (m_eToolType)
	{
	case TOOLTYPE::TOOL_TERRAIN:
		OnLButtonDown_Terrain(point);
		break;
	case TOOLTYPE::TOOL_BUILDING:
		OnLButtonDown_Building(point);
		break;
	case TOOLTYPE::TOOL_UNIT:
		OnLButtonDown_Unit(point);
		break;
	}
}

void CToolView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CScrollView::OnMouseMove(nFlags, point);
	
	switch (m_eToolType)
	{
	case TOOLTYPE::TOOL_TERRAIN:
		OnMouseMove_Terrain(point);
		break;
	case TOOLTYPE::TOOL_BUILDING:
		OnMouseMove_Building(point);
		break;
	case TOOLTYPE::TOOL_UNIT:
		OnMouseMove_Unit(point);
		break;
	}
}

void CToolView::OnLButtonDown_Terrain(CPoint point)
{
	if (GetAsyncKeyState(VK_LBUTTON))
	{
		m_pTerrain->Tile_Change({ float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f });

		Invalidate(FALSE);

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());
		CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));

		pMiniView->Invalidate(FALSE);
	}
}

void CToolView::OnLButtonDown_Building(CPoint point)
{
}

void CToolView::OnLButtonDown_Unit(CPoint point)
{
	vector<CGameObject*>& vecCursorObj = CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR);
	if (vecCursorObj.size() && !vecCursorObj.front()->GetCollider()->isCollided())
	{
		CGameObject* pClone = vecCursorObj.front()->Clone();
		pClone->GetTransform()->Translate(vecCursorObj.front()->GetTransform()->Position());
		CObjectMgr::Get_Instance()->GetObjList(vecCursorObj.front()->GetType()).push_back(pClone);
		Invalidate(FALSE);
	}
}

void CToolView::OnMouseMove_Terrain(CPoint point)
{

	if (GetAsyncKeyState(VK_LBUTTON))
	{
		RECT	rc{};
		GetClientRect(&rc);

		if (point.x < 30 || point.y < 30 || point.x > rc.right - 30 || point.y > rc.bottom - 30)
			return;

		m_pTerrain->Tile_Change({ float(point.x + GetScrollPos(0)), float(point.y + GetScrollPos(1)), 0.f });
		Invalidate(FALSE);

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CMiniView*		pMiniView = dynamic_cast<CMiniView*>(pMainFrm->m_SecondSplitter.GetPane(0, 0));
		pMiniView->Invalidate(FALSE);
	}
}

void CToolView::OnMouseMove_Building(CPoint point)
{
	point.x -= (point.x + GetScrollPos(0)) % TILECX;
	point.y -= (point.y + GetScrollPos(1)) % TILECY;

	vector<CGameObject*>& vecCursorObj = CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR);
	if (vecCursorObj.size())
	{
		const D3DXVECTOR3& vScale = vecCursorObj.front()->GetTransform()->LocalScale();

		point.x += ((int(vScale.x) / 30) % 2) * (TILECX * 0.5f);
		point.y += ((int(vScale.y) / 30) % 2) * (TILECY * 0.5f);

		const D3DXVECTOR3& vCursorObjPos = vecCursorObj.front()->GetTransform()->Position();

		D3DXVECTOR3 vToMousePos(point.x + GetScrollPos(0) - vCursorObjPos.x , point.y + GetScrollPos(1) - vCursorObjPos.y , 0.f);
		vecCursorObj.front()->GetTransform()->Translate(vToMousePos);

		if (GetAsyncKeyState(VK_LBUTTON) && !vecCursorObj.front()->GetCollider()->isCollided())
		{
			RECT	rc{};
			GetClientRect(&rc);

			if (point.x < 30 || point.y < 30 || point.x > rc.right - 30 || point.y > rc.bottom - 30)
				return;	// ���� ������ ���� ���� ���� �� ��ũ�� Ŭ�� �� �����ڸ��� ������ ������ ������ ���� ���� ó��.

			CGameObject* pClone = vecCursorObj.front()->Clone();
			pClone->GetTransform()->Translate(vCursorObjPos);
			CObjectMgr::Get_Instance()->GetObjList(vecCursorObj.front()->GetType()).push_back(pClone);

			m_pTerrain->Tile_Change(pClone->GetTransform()->Position(), pClone->GetTransform()->LocalScale());
		}

		Invalidate(FALSE);
	}
}

void CToolView::OnMouseMove_Unit(CPoint point)
{
	vector<CGameObject*>& vecCursorObj = CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR);
	if (vecCursorObj.size())
	{
		const D3DXVECTOR3& vCursorObjPos = vecCursorObj.front()->GetTransform()->Position();

		D3DXVECTOR3 vToMousePos(point.x - vCursorObjPos.x + GetScrollPos(0), point.y - vCursorObjPos.y + GetScrollPos(1), 0.f);
		vecCursorObj.front()->GetTransform()->Translate(vToMousePos);

		if (GetAsyncKeyState(VK_LBUTTON) && !vecCursorObj.front()->GetCollider()->isCollided())
		{
			RECT	rc{};
			GetClientRect(&rc);

			if (point.x < 30 || point.y < 30 || point.x > rc.right - 30 || point.y > rc.bottom - 30)
				return;	// ���� ������ ���� ���� ���� �� ��ũ�� Ŭ�� �� �����ڸ��� ������ ������ ������ ���� ���� ó��.

			CGameObject* pClone = vecCursorObj.front()->Clone();
			pClone->GetTransform()->Translate(vCursorObjPos);
			CObjectMgr::Get_Instance()->GetObjList(vecCursorObj.front()->GetType()).push_back(pClone);
		}

		Invalidate(FALSE);
	}
}


//BOOL CToolView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//	D3DXMATRIX matWorld, matScale, matTrans, matTransInv;
//	D3DXMatrixIdentity(&matWorld);
//	D3DXMatrixTranslation(&matTrans, -pt.x, -pt.y, 0.f);
//	D3DXMatrixInverse(&matTransInv, NULL, &matTrans);
//	if (zDelta < 0)
//	{
//		D3DXMatrixScaling(&matScale, 1.25f, 1.25f, 1.25f);
//	}
//	else
//	{
//		D3DXMatrixScaling(&matScale, 0.8f, 0.8f, 0.8f);
//	}
//	matWorld = matTrans * matScale * matTransInv;
//
//
//
//	return CScrollView::OnMouseWheel(nFlags, zDelta, pt);
//}
