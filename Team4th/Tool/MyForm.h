#pragma once
#include "afxcmn.h"

#include "TerrainTab.h"
#include "BuildingTab.h"
#include "UnitTab.h"

// CMyForm 폼 뷰입니다.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


