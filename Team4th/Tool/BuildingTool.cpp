// BuildingTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"


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
