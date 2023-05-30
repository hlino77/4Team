// UnitTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTab.h"
#include "afxdialogex.h"


// CUnitTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTab, CDialogEx)

CUnitTab::CUnitTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABUNIT, pParent)
{

}

CUnitTab::~CUnitTab()
{
}

void CUnitTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUnitTab, CDialogEx)
END_MESSAGE_MAP()


// CUnitTab 메시지 처리기입니다.
