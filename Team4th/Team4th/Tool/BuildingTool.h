#pragma once
#include "afxcmn.h"


// CBuildingTool 대화 상자입니다.

class CBuildingTool : public CDialog
{
	DECLARE_DYNAMIC(CBuildingTool)

public:
	CBuildingTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBuildingTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUILDINGTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl	m_BuildingTree;
	CImageList	m_ImageListTree;

	HTREEITEM	m_Buildings;
	HTREEITEM	m_Protoss;

	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickBuildingtree(NMHDR *pNMHDR, LRESULT *pResult);
};
