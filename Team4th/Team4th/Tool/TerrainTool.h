#pragma once
#include "afxwin.h"
#include "Enum.h"

// CTerrainTool ��ȭ �����Դϴ�.

class CTerrainTool : public CDialog
{
	DECLARE_DYNAMIC(CTerrainTool)

public:
	CTerrainTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CTerrainTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAINTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnOptionNormal();
	afx_msg void OnOptionSmall();
	afx_msg void OnOptionNone();
	afx_msg void OnSizeNormal();
	afx_msg void OnSizeSmall();
	afx_msg void OnColiderbutton();

	CButton		m_Option[3];
	CButton		m_Size[2];

	SETCOL_STATE m_ColState;
	virtual BOOL OnInitDialog();
	CButton		 m_ColButton;
};
