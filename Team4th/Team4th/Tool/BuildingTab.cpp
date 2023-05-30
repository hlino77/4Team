// BuildingTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTab.h"
#include "afxdialogex.h"


// CBuildingTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBuildingTab, CDialogEx)

CBuildingTab::CBuildingTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABBUILDING, pParent)
{

}

CBuildingTab::~CBuildingTab()
{
}

void CBuildingTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBuildingTab, CDialogEx)
END_MESSAGE_MAP()


// CBuildingTab 메시지 처리기입니다.
