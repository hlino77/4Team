// UnitTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTool.h"
#include "afxdialogex.h"


// CUnitTool ��ȭ �����Դϴ�.

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
END_MESSAGE_MAP()


// CUnitTool �޽��� ó�����Դϴ�.


BOOL CUnitTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	//TVINSERTSTRUCT	tvInsert;

	//tvInsert.hParent = NULL;
	//tvInsert.hInsertAfter = TVI_LAST;
	//tvInsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_TEXT;
	//tvInsert.item.state = 0;
	//tvInsert.item.stateMask = 0;
	//tvInsert.item.cchTextMax = 60;

	//tvInsert.item.cChildren = 0;

	//tvInsert.item.pszText = L"Units";
	//tvInsert.item.iImage = 0;
	//tvInsert.item.iSelectedImage = 1;

	//m_Units = m_UnitTree.InsertItem(&tvInsert);

	//

	m_Units = m_UnitTree.InsertItem(L"Units");
	m_Protoss = m_UnitTree.InsertItem(L"Protoss", m_Units);

	m_GroundUnits = m_UnitTree.InsertItem(L"Ground Unit", m_Protoss);
	m_AirUnits = m_UnitTree.InsertItem(L"Air Unit", m_Protoss);

	m_UnitTree.InsertItem(L"Zealot", m_GroundUnits);
	m_UnitTree.InsertItem(L"Probe", m_GroundUnits);
	m_UnitTree.InsertItem(L"Dragoon", m_GroundUnits);
	m_UnitTree.InsertItem(L"High Templer", m_GroundUnits);
	m_UnitTree.InsertItem(L"Dark Templer", m_GroundUnits);

	m_UnitTree.InsertItem(L"Scout", m_AirUnits);
	m_UnitTree.InsertItem(L"Corsair", m_AirUnits);

	m_UnitTree.Expand(m_Units, TVE_EXPAND);
	m_UnitTree.Expand(m_Protoss, TVE_EXPAND);
	m_UnitTree.Expand(m_GroundUnits, TVE_EXPAND);
	m_UnitTree.Expand(m_AirUnits, TVE_EXPAND);
	/*m_vecUnits.push_back(m_UnitTree.InsertItem(L"Zealot", m_Protoss));
	m_vecUnits.push_back(m_UnitTree.InsertItem(L"Probe", m_Protoss));
	m_vecUnits.push_back(m_UnitTree.InsertItem(L"Dragoon", m_Protoss));
	m_vecUnits.push_back(m_UnitTree.InsertItem(L"High Templer", m_Protoss));
	m_vecUnits.push_back(m_UnitTree.InsertItem(L"Dark Templer", m_Protoss));*/

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
