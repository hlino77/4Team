// BuildingTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"


// CBuildingTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CBuildingTool, CDialog)

CBuildingTool::CBuildingTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_BUILDINGTOOL, pParent)
{

}

CBuildingTool::~CBuildingTool()
{
}

void CBuildingTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBuildingTool, CDialog)
END_MESSAGE_MAP()


// CBuildingTool 메시지 처리기입니다.
