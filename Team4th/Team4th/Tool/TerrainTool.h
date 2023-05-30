#pragma once
#include "afxwin.h"
#include "Enum.h"

// CTerrainTool 대화 상자입니다.

class CTerrainTool : public CDialog
{
	DECLARE_DYNAMIC(CTerrainTool)

public:
	CTerrainTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CTerrainTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERRAINTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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
