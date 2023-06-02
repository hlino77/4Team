// BuildingTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "ObjectMgr.h"
#include "Nexus.h"
#include "Gateway.h"

// CBuildingTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CBuildingTool, CDialog)

CBuildingTool::CBuildingTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BUILDINGTOOL, pParent)
{

}

CBuildingTool::~CBuildingTool()
{
}

void CBuildingTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BuildingTree, m_BuildingTree);
}


BEGIN_MESSAGE_MAP(CBuildingTool, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_BuildingTree, &CBuildingTool::OnNMClickBuildingtree)
END_MESSAGE_MAP()


// CBuildingTool �޽��� ó�����Դϴ�.


BOOL CBuildingTool::OnInitDialog()
{
	CDialog::OnInitDialog();

#pragma region ImageList
	m_ImageListTree.Create(IDB_BITMAP_BUILDING, 34, 2, D3DCOLOR_ARGB(255, 255, 255, 255));
	m_BuildingTree.SetImageList(&m_ImageListTree, TVSIL_NORMAL);

	TVINSERTSTRUCT	tvInsert;

	tvInsert.hParent = NULL;
	tvInsert.hInsertAfter = TVI_LAST;
	tvInsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	tvInsert.item.state = 0;
	tvInsert.item.stateMask = 0;
	tvInsert.item.cchTextMax = 60;

	tvInsert.item.cChildren = 0;

	tvInsert.item.pszText = L"Buildings";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_Buildings = m_BuildingTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_Buildings;
	tvInsert.item.pszText = L"Protoss";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_Protoss = m_BuildingTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_Protoss;
	tvInsert.item.pszText = L"Nexus";
	tvInsert.item.iImage = 0;
	tvInsert.item.iSelectedImage = 0;
	m_BuildingTree.InsertItem(&tvInsert);

	tvInsert.hParent = m_Protoss;
	tvInsert.item.pszText = L"Gateway";
	tvInsert.item.iImage = 1;
	tvInsert.item.iSelectedImage = 1;
	m_BuildingTree.InsertItem(&tvInsert);
#pragma endregion ImageList


	m_BuildingTree.Expand(m_Buildings, TVE_EXPAND);
	m_BuildingTree.Expand(m_Protoss, TVE_EXPAND);


	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CBuildingTool::OnNMClickBuildingtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	CPoint p;
	GetCursorPos(&p);
	UINT flag;
	m_BuildingTree.ScreenToClient(&p);
	HTREEITEM hItem_dc = m_BuildingTree.HitTest(p, &flag);

	vector<CGameObject*>& vecCursorObj = CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR);

	if (vecCursorObj.size() && (m_BuildingTree.GetItemText(hItem_dc) == vecCursorObj.front()->GetData().strName))
		return;
	else if (vecCursorObj.size() && m_BuildingTree.GetItemText(hItem_dc) != vecCursorObj.front()->GetData().strName)
	{
		for (auto& iter : vecCursorObj)
			Safe_Delete(iter);
		vecCursorObj.clear();
	}

	if (L"Nexus" == m_BuildingTree.GetItemText(hItem_dc))
	{
		CGameObject* pNexus = new CNexus;
		pNexus->Initialize();
		CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR).push_back(pNexus);
	}
	else if (L"Gateway" == m_BuildingTree.GetItemText(hItem_dc))
	{
		CGameObject* pGateway = new CGateway;
		pGateway->Initialize();
		CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR).push_back(pGateway);
	}

}
