// TerrainTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TerrainTab.h"
#include "afxdialogex.h"


// CTerrainTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CTerrainTab, CDialogEx)

CTerrainTab::CTerrainTab(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TABTERRAIN, pParent)
{

}

CTerrainTab::~CTerrainTab()
{
}

void CTerrainTab::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTerrainTab, CDialogEx)
END_MESSAGE_MAP()


// CTerrainTab �޽��� ó�����Դϴ�.