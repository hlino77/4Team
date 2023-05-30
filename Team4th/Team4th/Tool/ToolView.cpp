
// ToolView.cpp : CToolView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CToolView 생성/소멸

CToolView::CToolView() : m_pTerrain(nullptr)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CToolView::~CToolView()
{
}

void CToolView::OnInitialUpdate()
{
	g_hWnd = m_hWnd;

	CScrollView::OnInitialUpdate();

	// SetScrollSizes : 스크롤 바의 사이즈를 지정하는 함수
	// MM_TEXT : 픽셀 단위로 조정하겠다는 옵션
	// 스크롤 가로 사이즈, 스크롤 세로 사이즈

	SetScrollSizes(MM_TEXT, CSize(MAPCX, MAPCY));

	// AfxGetMainWnd : 현재의 메인 창의 주소를 반환하는 함수
	CMainFrame*		pMainFrm = (CMainFrame*)AfxGetMainWnd();

	RECT	rcWnd{};

	// GetWindowRect : 현재 창의 렉트 정보를 얻어오는 함수
	pMainFrm->GetWindowRect(&rcWnd);

	// SetRect : 매개 변수대로 렉트의 정보를 지정하는 함수
	SetRect(&rcWnd, 0, 0, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top);

	RECT	rcMainView{};

	// GetClientRect : 현재 view창의 RECT 정보를 얻어오는 함수
	GetClientRect(&rcMainView);

	float		fRowFrm = float(rcWnd.right - rcMainView.right);
	float		fColFrm = float(rcWnd.bottom - rcMainView.bottom);

	//SetWindowPos : 매개 변수대로 새롭게 윈도우 위치와 크기를 조정하는 함수
	 // (배치할 윈도우의 Z순서에 대한 포인터, X좌표, Y좌표, 가로 크기, 세로 크기, 배치할 윈도우의 크기및 위치 지정 옵션)
	pMainFrm->SetWindowPos(nullptr,  // 순서 변경을 안하기 때문에 NULL
							0, 
							0, 
							int(WINCX + fRowFrm),
							int(WINCY + fColFrm), 
							SWP_NOZORDER);	// 현재 순서를 유지하겠다는 옵션


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
#pragma region 안봐
BOOL CToolView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CToolView 인쇄

BOOL CToolView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CToolView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CToolView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CToolView 진단

#ifdef _DEBUG
void CToolView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CToolView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CToolDoc* CToolView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CToolDoc)));
	return (CToolDoc*)m_pDocument;
}
#endif //_DEBUG


// CToolView 메시지 처리기


// CToolView 그리기
#pragma endregion 안봐

void CToolView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CScrollView::OnLButtonDown(nFlags, point);

	// point : 마우스 좌표를 갖고 있음.

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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
				return;	// 유닛 툴에서 유닛 선택 직후 및 스크롤 클릭 후 가장자리에 유닛이 찍히는 문제에 대한 예외 처리.

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
				return;	// 유닛 툴에서 유닛 선택 직후 및 스크롤 클릭 후 가장자리에 유닛이 찍히는 문제에 대한 예외 처리.

			CGameObject* pClone = vecCursorObj.front()->Clone();
			pClone->GetTransform()->Translate(vCursorObjPos);
			CObjectMgr::Get_Instance()->GetObjList(vecCursorObj.front()->GetType()).push_back(pClone);
		}

		Invalidate(FALSE);
	}
}


//BOOL CToolView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
