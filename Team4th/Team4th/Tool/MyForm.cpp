// MyForm.cpp : ���� �����Դϴ�.
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
#include "ObjectMgr.h"
#include "GameObject.h"
#include "Transform.h"
#include "ToolView.h"

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
	ON_BN_CLICKED(IDC_SAVEBUTTON, &CMyForm::OnSaveData)
	ON_BN_CLICKED(IDC_LOADBUTTON, &CMyForm::OnLoadData)
END_MESSAGE_MAP()

void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	m_Font.CreatePointFont(180, L"�ü�");

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


	// GetDlgItem : ���̾�α׿� ��ġ�� ���ҽ��� id���� ���� ������ �Լ�
}

#pragma region �Ⱥ�
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
#pragma endregion �Ⱥ�

void CMyForm::OnTabChange(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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


void CMyForm::OnSaveData()
{
	CFileDialog		Dlg(FALSE,	// TRUE(����), FALSE(�ٸ� �̸����� ����) ��� ����	
		L"dat", // defaule ���� Ȯ���ڸ�
		L"*.dat", // ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ����� ���� �� ���޼��� ����)
		L"Data Files(*.dat) | *.dat||",  // ��ȭ ���ڿ� ǥ�õ� ���� ���� '�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||'
		this); // �θ� ������ �ּ�

	TCHAR	szPath[MAX_PATH] = L"";

	// GetCurrentDirectory : ���� ������Ʈ ��θ� ������ �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);
	//szPath = 0x00d2e810 L"D:\\����ȯ\\137��\\Frame137\\Tool"

	//PathRemoveFileSpec : ��ü ��ο��� ���� �̸��� �߶󳻴� �Լ�, ���� �̸��� ���� ���, ���� ������ ��θ� �߶�
	PathRemoveFileSpec(szPath);
	//szPath = 0x00efe3f8 L"D:\\����ȯ\\137��\\Frame137"

	lstrcat(szPath, L"\\Data");

	// ��ȭ ���ڸ� ������ �� ���̴� �⺻ ��� ���� ���� �����ϴ� ����
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		HANDLE hFile = CreateFile(L"../Data/TempData.dat", GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		DWORD	dwStrByte = 0;


		for (int i = 0; i < (UINT)OBJID::OBJ_END; ++i)
		{
			/*if ((UINT)OBJID::OBJ_MOUSE == i)
				continue;
*/
			vector<CGameObject*>& vecObjList = CObjectMgr::Get_Instance()->GetObjList((OBJID)i);
			for (auto& iter : vecObjList)
			{
				/*if (OBJID::OBJ_MOUSE == iter->GetType())
					continue;*/

				dwStrByte = sizeof(TCHAR) * (iter->GetData().strName.GetLength() + 1);

				WriteFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);
				WriteFile(hFile, iter->GetData().strName, dwStrByte, &dwByte, nullptr);

				WriteFile(hFile, &(iter->GetTransform()->Position().x), sizeof(float), &dwByte, nullptr);
				WriteFile(hFile, &(iter->GetTransform()->Position().y), sizeof(float), &dwByte, nullptr);
			}
		}


		CloseHandle(hFile);
	}


	CFileDialog		DlgTile(FALSE,	// TRUE(����), FALSE(�ٸ� �̸����� ����) ��� ����	
		L"dat", // defaule ���� Ȯ���ڸ�
		L"*.dat", // ��ȭ ���ڿ� ǥ�õ� ���� ���ϸ�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(�б����� üũ�ڽ� ����), OFN_OVERWRITEPROMPT(�ߺ����� ���� �� ���޼��� ����)
		L"Data Files(*.dat) | *.dat||",  // ��ȭ ���ڿ� ǥ�õ� ���� ���� '�޺� �ڽ��� ��µ� ���ڿ� | ���� ����� ���͸� ���ڿ� ||'
		this); // �θ� ������ �ּ�

	TCHAR	szTilePath[MAX_PATH] = L"";

	// GetCurrentDirectory : ���� ������Ʈ ��θ� ������ �Լ�
	GetCurrentDirectory(MAX_PATH, szTilePath);
	//szPath = 0x00d2e810 L"D:\\����ȯ\\137��\\Frame137\\Tool"

	//PathRemoveFileSpec : ��ü ��ο��� ���� �̸��� �߶󳻴� �Լ�, ���� �̸��� ���� ���, ���� ������ ��θ� �߶�
	PathRemoveFileSpec(szTilePath);
	//szPath = 0x00efe3f8 L"D:\\����ȯ\\137��\\Frame137"

	lstrcat(szTilePath, L"\\Data");

	// ��ȭ ���ڸ� ������ �� ���̴� �⺻ ��� ���� ���� �����ϴ� ����
	DlgTile.m_ofn.lpstrInitialDir = szTilePath;

	if (IDOK == DlgTile.DoModal())
	{
		HANDLE hFile = CreateFile(L"../Data/TileData.dat", GENERIC_WRITE, 0, 0,
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		DWORD	dwStrByte = 0;

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTileList = pToolView->Get_Terrain()->Get_TileList();
		


		for (auto& iter : vecTileList)
		{
			WriteFile(hFile, &iter->bCollider, sizeof(bool), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}
}


void CMyForm::OnLoadData()
{
	CFileDialog		Dlg(TRUE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat) | *.dat||",
		this);

	TCHAR	szPath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szPath);

	PathRemoveFileSpec(szPath);

	lstrcat(szPath, L"\\Data");
	Dlg.m_ofn.lpstrInitialDir = szPath;

	if (IDOK == Dlg.DoModal())
	{
		
		CObjectMgr::Get_Instance()->Release();

		CString		strTemp = Dlg.GetPathName().GetString();
		const TCHAR* pGetPath = strTemp.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ,
			0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;
		DWORD	dwStrByte = 0;
		float fX, fY;

		while (true)
		{
			// key �� ����
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR*	pName = new TCHAR[dwStrByte];

			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);
		

			// value�� ����
			ReadFile(hFile, &fX, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &fY, sizeof(float), &dwByte, nullptr);
	

			if (0 == dwByte)
			{
				delete[]pName;
				pName = nullptr;
				break;
			}

			//if���߰�
			CObjectMgr::Get_Instance()->CreateObject(pName, D3DXVECTOR3(fX, fY, 0.f));

			CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
			dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1))->Invalidate(FALSE);

			delete[]pName;
			pName = nullptr;
		}

		CloseHandle(hFile);
	}



	CFileDialog		DlgTile(TRUE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat) | *.dat||",
		this);

	TCHAR	szTilePath[MAX_PATH] = L"";

	GetCurrentDirectory(MAX_PATH, szTilePath);

	PathRemoveFileSpec(szTilePath);

	lstrcat(szTilePath, L"\\Data");
	DlgTile.m_ofn.lpstrInitialDir = szTilePath;



	if (IDOK == DlgTile.DoModal())
	{

		CString		strTemp = DlgTile.GetPathName().GetString();
		const TCHAR* pGetPath = strTemp.GetString();

		HANDLE hFile = CreateFile(pGetPath, GENERIC_READ,
			0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;

		DWORD	dwByte = 0;

		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetMainWnd());
		CToolView*		pToolView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));
		vector<TILE*>& vecTileList = pToolView->Get_Terrain()->Get_TileList();

		for (auto& iter : vecTileList)
		{
			ReadFile(hFile, &iter->bCollider, sizeof(bool), &dwByte, nullptr);


			if (0 == dwByte)
			{
				break;
			}
		}

		CloseHandle(hFile);
	}
}
