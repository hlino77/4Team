// UnitTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTab.h"
#include "afxdialogex.h"


// CUnitTab ��ȭ �����Դϴ�.

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


// CUnitTab �޽��� ó�����Դϴ�.
