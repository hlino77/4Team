// BuildingTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "BuildingTool.h"
#include "afxdialogex.h"


// CBuildingTool ��ȭ �����Դϴ�.

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


// CBuildingTool �޽��� ó�����Դϴ�.
