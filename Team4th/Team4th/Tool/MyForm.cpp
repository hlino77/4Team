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


void CMyForm::OnSaveData()
{
	CFileDialog		Dlg(FALSE,	// TRUE(열기), FALSE(다른 이름으로 저장) 모드 지정	
		L"dat", // defaule 파일 확장자명
		L"*.dat", // 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복파일 저장 시 경고메세지 띄우기)
		L"Data Files(*.dat) | *.dat||",  // 대화 상자에 표시될 파일 형식 '콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||'
		this); // 부모 윈도우 주소

	TCHAR	szPath[MAX_PATH] = L"";

	// GetCurrentDirectory : 현재 프로젝트 경로를 얻어오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);
	//szPath = 0x00d2e810 L"D:\\유준환\\137기\\Frame137\\Tool"

	//PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라내는 함수, 파일 이름이 없을 경우, 가장 마지막 경로명만 잘라냄
	PathRemoveFileSpec(szPath);
	//szPath = 0x00efe3f8 L"D:\\유준환\\137기\\Frame137"

	lstrcat(szPath, L"\\Data");

	// 대화 상자를 열었을 때 보이는 기본 경로 설정 값을 저장하는 변수
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


	CFileDialog		DlgTile(FALSE,	// TRUE(열기), FALSE(다른 이름으로 저장) 모드 지정	
		L"dat", // defaule 파일 확장자명
		L"*.dat", // 대화 상자에 표시될 최초 파일명
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, // OFN_HIDEREADONLY(읽기전용 체크박스 숨김), OFN_OVERWRITEPROMPT(중복파일 저장 시 경고메세지 띄우기)
		L"Data Files(*.dat) | *.dat||",  // 대화 상자에 표시될 파일 형식 '콤보 박스에 출력될 문자열 | 실제 사용할 필터링 문자열 ||'
		this); // 부모 윈도우 주소

	TCHAR	szTilePath[MAX_PATH] = L"";

	// GetCurrentDirectory : 현재 프로젝트 경로를 얻어오는 함수
	GetCurrentDirectory(MAX_PATH, szTilePath);
	//szPath = 0x00d2e810 L"D:\\유준환\\137기\\Frame137\\Tool"

	//PathRemoveFileSpec : 전체 경로에서 파일 이름만 잘라내는 함수, 파일 이름이 없을 경우, 가장 마지막 경로명만 잘라냄
	PathRemoveFileSpec(szTilePath);
	//szPath = 0x00efe3f8 L"D:\\유준환\\137기\\Frame137"

	lstrcat(szTilePath, L"\\Data");

	// 대화 상자를 열었을 때 보이는 기본 경로 설정 값을 저장하는 변수
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
			// key 값 저장
			ReadFile(hFile, &dwStrByte, sizeof(DWORD), &dwByte, nullptr);

			TCHAR*	pName = new TCHAR[dwStrByte];

			ReadFile(hFile, pName, dwStrByte, &dwByte, nullptr);
		

			// value값 저장
			ReadFile(hFile, &fX, sizeof(float), &dwByte, nullptr);
			ReadFile(hFile, &fY, sizeof(float), &dwByte, nullptr);
	

			if (0 == dwByte)
			{
				delete[]pName;
				pName = nullptr;
				break;
			}

			//if문추가
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
