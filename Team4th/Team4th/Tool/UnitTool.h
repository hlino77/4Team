#pragma once
#include "afxcmn.h"


// CUnitTool ��ȭ �����Դϴ�.

class CUnitTool : public CDialog
{
	DECLARE_DYNAMIC(CUnitTool)

public:
	CUnitTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_UNITTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_UnitTree;
	CImageList m_ImageListTree;


	HTREEITEM	m_Units;
	HTREEITEM	m_Protoss;
	HTREEITEM	m_Zerg;
	HTREEITEM	m_PGround;
	HTREEITEM	m_ZGround;
	HTREEITEM	m_AirUnits;

	//vector<HTREEITEM> m_vecUnits;

	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickTree1(NMHDR *pNMHDR, LRESULT *pResult);
};
