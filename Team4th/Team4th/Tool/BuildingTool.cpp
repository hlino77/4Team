// BuildingTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"
#include "GameObject.h"
#include "ObjectMgr.h"
#include "Nexus.h"

// CBuildingTool 대화 상자입니다.

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


// CBuildingTool 메시지 처리기입니다.


BOOL CBuildingTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_Buildings = m_BuildingTree.InsertItem(L"Buildings");

	m_Protoss = m_BuildingTree.InsertItem(L"Protoss", m_Buildings);
	m_BuildingTree.InsertItem(L"Nexus", m_Protoss);
	m_BuildingTree.InsertItem(L"GateWay", m_Protoss);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CBuildingTool::OnNMClickBuildingtree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
