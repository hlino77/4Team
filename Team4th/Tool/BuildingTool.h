#pragma once


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
};
