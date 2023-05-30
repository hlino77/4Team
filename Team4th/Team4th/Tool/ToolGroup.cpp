// ToolGroup.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ToolGroup.h"
#include "Include.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "GameObject.h"
#include "ObjectMgr.h"


// CToolGroup

IMPLEMENT_DYNCREATE(CToolGroup, CFormView)

CToolGroup::CToolGroup()
	: CFormView(IDD_TOOLGROUP)
{

}

CToolGroup::~CToolGroup()
{
}

void CToolGroup::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CToolGroup, CFormView)
END_MESSAGE_MAP()


// CToolGroup �����Դϴ�.

#ifdef _DEBUG
void CToolGroup::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CToolGroup::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CToolGroup �޽��� ó�����Դϴ�.


void CToolGroup::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_vecTools.push_back(new CTerrainTool);
	m_vecTools.push_back(new CBuildingTool);
	m_vecTools.push_back(new CUnitTool);

	m_vecTools[(UINT)TOOLTYPE::TOOL_TERRAIN]->Create(IDD_TERRAINTOOL, this);
	m_vecTools[(UINT)TOOLTYPE::TOOL_BUILDING]->Create(IDD_BUILDINGTOOL, this);
	m_vecTools[(UINT)TOOLTYPE::TOOL_UNIT]->Create(IDD_UNITTOOL, this);

	m_pCurrentTool = m_vecTools[(UINT)TOOLTYPE::TOOL_TERRAIN];
	m_pCurrentTool->ShowWindow(SW_SHOW);
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}

void CToolGroup::ChangeTool(TOOLTYPE _eType)
{
	m_pCurrentTool->ShowWindow(SW_HIDE);

	m_pCurrentTool = m_vecTools[(UINT)_eType];
	m_pCurrentTool->ShowWindow(SW_SHOW);

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
	CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
	pToolView->m_eToolType = _eType;

	vector<CGameObject*>& vecCursorObj = CObjectMgr::Get_Instance()->GetObjList(OBJID::OBJ_ONCURSOR);
	if (vecCursorObj.size())
	{
		for (auto& iter : vecCursorObj)
			Safe_Delete(iter);
		vecCursorObj.clear();

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
		pToolView->Invalidate(FALSE);
	}
}
