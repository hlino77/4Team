// TerrainTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TerrainTool.h"
#include "afxdialogex.h"
#include "MainFrm.h"
#include "ToolView.h"

// CTerrainTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTerrainTool, CDialog)

CTerrainTool::CTerrainTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TERRAINTOOL, pParent)
{

}

CTerrainTool::~CTerrainTool()
{
}

void CTerrainTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_Option1, m_Option[0]);
	DDX_Control(pDX, IDC_Option3, m_Option[2]);

	DDX_Control(pDX, IDC_ColiderButton, m_ColButton);
}


BEGIN_MESSAGE_MAP(CTerrainTool, CDialog)
	ON_BN_CLICKED(IDC_Option1, &CTerrainTool::OnOptionNormal)
	ON_BN_CLICKED(IDC_Option3, &CTerrainTool::OnOptionNone)
	ON_BN_CLICKED(IDC_ColiderButton, &CTerrainTool::OnColiderbutton)
END_MESSAGE_MAP()


// CTerrainTool �޽��� ó�����Դϴ�.


void CTerrainTool::OnOptionNormal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	pToolView->Get_Terrain()->Set_GridState(GRID_STATE::NORMAL);
	pToolView->Invalidate(FALSE);
}


void CTerrainTool::OnOptionSmall()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	pToolView->Get_Terrain()->Set_GridState(GRID_STATE::SMALL);
	pToolView->Invalidate(FALSE);
}


void CTerrainTool::OnOptionNone()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	pToolView->Get_Terrain()->Set_GridState(GRID_STATE::NONE);
	pToolView->Invalidate(FALSE);
}


void CTerrainTool::OnSizeNormal()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CTerrainTool::OnSizeSmall()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}




void CTerrainTool::OnColiderbutton()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.


	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));



	switch (m_ColState)
	{
	case SETCOL_STATE::NONE:
		m_ColState = SETCOL_STATE::COLLIDER;
		pToolView->Get_Terrain()->Set_ColState(m_ColState);
		m_ColButton.SetWindowTextW(L"COLLIDER");
		break;
	case SETCOL_STATE::COLLIDER:
		m_ColState = SETCOL_STATE::DELETECOL;
		pToolView->Get_Terrain()->Set_ColState(m_ColState);
		m_ColButton.SetWindowTextW(L"DELETE");
		break;
	case SETCOL_STATE::DELETECOL:
		m_ColState = SETCOL_STATE::NONE;
		pToolView->Get_Terrain()->Set_ColState(m_ColState);
		m_ColButton.SetWindowTextW(L"NONE");
		break;
	}
}


BOOL CTerrainTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_Option[2].SetCheck(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.

	m_ColState = SETCOL_STATE::NONE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
