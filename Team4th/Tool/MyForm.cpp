// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"
//
#include "TerrainTool.h"
#include "UnitTool.h"
#include "BuildingTool.h"
#include "MainFrm.h"
#include "ToolGroup.h"

// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_TAB1, m_TerrainTab);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)

	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMyForm::OnTabChange)
END_MESSAGE_MAP()

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_Font.CreatePointFont(180, L"궁서");

	CRect rect;
	m_Tab.GetWindowRect(rect);

	m_Tab.InsertItem(0, L"Terrain");
	m_Tab.InsertItem(1, L"Building");
	m_Tab.InsertItem(2, L"Unit");

	m_Tab.SetCurSel(0);

	m_pTerrainTab = new CTerrainTab;
	m_pTerrainTab->Create(IDD_TABTERRAIN, &m_Tab);
	m_pTerrainTab->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pTerrainTab->ShowWindow(SW_SHOW);

	m_pBuildingTab = new CBuildingTab;
	m_pBuildingTab->Create(IDD_TABBUILDING, &m_Tab);
	m_pBuildingTab->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pBuildingTab->ShowWindow(SW_HIDE);

	m_pUnitTab = new CUnitTab;
	m_pUnitTab->Create(IDD_TABUNIT, &m_Tab);
	m_pUnitTab->MoveWindow(0, 20, rect.Width(), rect.Height());
	m_pUnitTab->ShowWindow(SW_HIDE);


	// GetDlgItem : 다이얼로그에 배치된 리소스를 id값에 따라 얻어오는 함수
}

#pragma region 안봐
#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG
#pragma endregion 안봐

void CMyForm::OnTabChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CFormView*		pToolGroup = dynamic_cast<CFormView*>(pMainFrm->m_SecondSplitter.GetPane(2, 0));

	int	iselect = m_Tab.GetCurSel();

	switch (iselect)
	{
	case 0:
		m_pTerrainTab->ShowWindow(SW_SHOW);
		m_pBuildingTab->ShowWindow(SW_HIDE);
		m_pUnitTab->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pBuildingTab->ShowWindow(SW_SHOW);
		m_pUnitTab->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pTerrainTab->ShowWindow(SW_HIDE);
		m_pBuildingTab->ShowWindow(SW_HIDE);
		m_pUnitTab->ShowWindow(SW_SHOW);
		break;
	}

	dynamic_cast<CToolGroup*>(pToolGroup)->ChangeTool((TOOLTYPE)iselect);
}
