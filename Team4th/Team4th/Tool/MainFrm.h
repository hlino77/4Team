
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once

#include "MyForm.h"
#include "TerrainTool.h"
//#include "MyTool.h"
#include "MiniView.h"
#include "Include.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:
	void	SetView(CRuntimeClass* _pTool);

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // ��Ʈ�� ������ ���Ե� ����Դϴ�.
	CToolBar        m_wndToolBar;
	CStatusBar      m_wndStatusBar;


public:
	CSplitterWnd	m_MainSplitter;
	CSplitterWnd	m_SecondSplitter;

	CCreateContext* GetContext() { return m_pContext; }
private:
	CCreateContext*	m_pContext;


// ������ �޽��� �� �Լ�
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};




