// TerrainTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "TerrainTool.h"
#include "afxdialogex.h"


// CTerrainTool 대화 상자입니다.

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


// CTerrainTool 메시지 처리기입니다.
