// BuildingTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"


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
