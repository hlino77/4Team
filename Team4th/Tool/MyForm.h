#pragma once
#include "afxcmn.h"

#include "TerrainTab.h"
#include "BuildingTab.h"
#include "UnitTab.h"

// CMyForm �� ���Դϴ�.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:

private:
	CFont		m_Font;


public:
	virtual void OnInitialUpdate();
	afx_msg void OnTabChange(NMHDR *pNMHDR, LRESULT *pResult);
//	CTabCtrl m_TerrainTab;
	CTabCtrl m_Tab;

	CTerrainTab*	m_pTerrainTab;
	CBuildingTab*	m_pBuildingTab;
	CUnitTab*		m_pUnitTab;
};


