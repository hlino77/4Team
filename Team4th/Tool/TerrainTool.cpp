// TerrainTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TerrainTool.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CTerrainTool, CDialog)
END_MESSAGE_MAP()


// CTerrainTool �޽��� ó�����Դϴ�.
