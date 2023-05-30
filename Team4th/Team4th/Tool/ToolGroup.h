#pragma once
#include "TerrainTool.h"
#include "UnitTool.h"
#include "BuildingTool.h"
#include "Include.h"

// CToolGroup �� ���Դϴ�.

class CToolGroup : public CFormView
{
	DECLARE_DYNCREATE(CToolGroup)

protected:
	CToolGroup();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CToolGroup();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLGROUP };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	vector<CDialog*> m_vecTools;
	CDialog*		m_pCurrentTool;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	void	ChangeTool(TOOLTYPE _eType);
};


