#pragma once


// CBuildingTab 대화 상자입니다.

class CBuildingTab : public CDialogEx
{
	DECLARE_DYNAMIC(CBuildingTab)

public:
	CBuildingTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CBuildingTab();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TABBUILDING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
