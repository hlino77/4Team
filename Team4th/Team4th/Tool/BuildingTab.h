#pragma once


// CBuildingTab ��ȭ �����Դϴ�.

class CBuildingTab : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildingTab)

public:
	CBuildingTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CBuildingTab();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABBUILDING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
