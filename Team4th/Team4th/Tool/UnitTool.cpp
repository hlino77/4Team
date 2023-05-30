// UnitTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"
#include "Include.h"

#include "ObjectMgr.h"
#include "Zealot.h"
#include "Probe.h"
#include "Dragoon.h"
#include "MainFrm.h"
#include "ToolView.h"
// CUnitTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTool, CDialog)

CUnitTool::CUnitTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_UNITTOOL, pParent)
{

}

CUnitTool::~CUnitTool()
{
}

void CUnitTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_UnitTree);
}


BEGIN_MESSAGE_MAP(CUnitTool, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_TREE1, &CUnitTool::OnNMClickTree1)
END_MESSAGE_MAP()


// CUnitTool 메시지 처리기입니다.


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

#pragma region ImageList
	m_ImageListTree.Create(IDB_BITMAP_PGROUND, 34, 5, D3DCOLOR_ARGB(255, 255, 255, 255));
	m_UnitTree.SetImageList(&m_ImageListTree, TVSIL_NORMAL);

	TVINSERTSTRUCT	tvInsert;

	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = TVI_LAST;
	tvInsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	tvInsert.item.state = 0;
	tvInsert.item.stateMask = 0;
	tvInsert.item.cchTextMax = 60;

	tvInsert.item.cChildren = 0;

	tvInsert.item.pszText = L"Units";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_Units = m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_Units;
	tvInsert.item.pszText = L"Protoss";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_Protoss = m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_Protoss;
	tvInsert.item.pszText = L"Ground Unit";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_GroundUnits = m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_Protoss;
	tvInsert.item.pszText = L"Air Unit";
	tvInsert.item.iImage = 3;
	tvInsert.item.iSelectedImage = 3;
	m_AirUnits = m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_GroundUnits;
	tvInsert.item.pszText = L"Zealot";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_GroundUnits;
	tvInsert.item.pszText = L"Probe";
	tvInsert.item.iImage = 1;
	tvInsert.item.iSelectedImage = 1;
	m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_GroundUnits;
	tvInsert.item.pszText = L"Dragoon";
	tvInsert.item.iImage = 2;
	tvInsert.item.iSelectedImage = 2;
	m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_GroundUnits;
	tvInsert.item.pszText = L"High Templer";
	tvInsert.item.iImage = 3;
	tvInsert.item.iSelectedImage = 3;
	m_UnitTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_GroundUnits;
	tvInsert.item.pszText = L"Dark Templer";
	tvInsert.item.iImage = 4;
	tvInsert.item.iSelectedImage = 4;
	m_UnitTree.InsertItem(&tvInsert);
#pragma endregion ImageList


	m_UnitTree.Expand(m_Units, TVE_EXPAND);
	m_UnitTree.Expand(m_Protoss, TVE_EXPAND);
	m_UnitTree.Expand(m_GroundUnits, TVE_EXPAND);
	m_UnitTree.Expand(m_AirUnits, TVE_EXPAND);

		// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CUnitTool::OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CPoint p;
	GetCursorPos(&p);
	UINT flag;
	m_UnitTree.ScreenToClient(&p);
	HTREEITEM hItem_dc = m_UnitTree.HitTest(p, &flag);

	vector<CGameObject*>& vecCursorObj = CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR);

	if (vecCursorObj.size() && (m_UnitTree.GetItemText(hItem_dc) == vecCursorObj.front()->GetData().strName))
		return;
	else if (vecCursorObj.size() && m_UnitTree.GetItemText(hItem_dc) != vecCursorObj.front()->GetData().strName)
	{
		for (auto& iter : vecCursorObj)
			Safe_Delete(iter);
		vecCursorObj.clear();
	}

	//CObjectMgr::Get_Instance()->CreateObject((TCHAR*)m_UnitTree.GetItemText(hItem_dc).GetString(), D3DXVECTOR3((float)p.x, (float)p.y, 0.f));

	if(L"Zealot" == m_UnitTree.GetItemText(hItem_dc))
	{
		CGameObject* pZealot = new CZealot;
		pZealot->Initialize();

		CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR).push_back(pZealot);
	}
	else if (L"Probe" == m_UnitTree.GetItemText(hItem_dc))
	{
		CGameObject* pProbe = new CProbe;
		pProbe->Initialize();
		CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR).push_back(pProbe);
	}
	else if (L"Dragoon" == m_UnitTree.GetItemText(hItem_dc))
	{
		CGameObject* pDragoon = new CDragoon;
		pDragoon->Initialize();
		CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR).push_back(pDragoon);
	}
	/*
	else if (L"High Templer" == m_UnitTree.GetItemText(hItem_dc))
	{

	}
	else if (L"Dark Templer" == m_UnitTree.GetItemText(hItem_dc))
	{


	}*/

	*pResult = 0;
}
