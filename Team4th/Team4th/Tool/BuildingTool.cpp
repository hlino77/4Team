// BuildingTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "ObjectMgr.h"
#include "Nexus.h"

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

	m_Buildings = m_BuildingTree.InsertItem(L"Buildings");

	m_Protoss = m_BuildingTree.InsertItem(L"Protoss", m_Buildings);
	m_BuildingTree.InsertItem(L"Nexus", m_Protoss);
	m_BuildingTree.InsertItem(L"GateWay", m_Protoss);

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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

}
