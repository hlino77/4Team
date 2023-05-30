#pragma once
#include "afxcmn.h"


// CBuildingTool ��ȭ �����Դϴ�.

class CBuildingTool : public CDialog
{
	DECLARE_DYNAMIC(CBuildingTool)

public:
	CBuildingTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBuildingTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BUILDINGTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_BuildingTree;
	virtual BOOL OnInitDialog();

	HTREEITEM m_Buildings;
	HTREEITEM m_Protoss;
	afx_msg void OnNMClickBuildingtree(NMHDR *pNMHDR, LRESULT *pResult);
};
