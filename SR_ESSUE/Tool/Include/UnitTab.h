#pragma once


// CUnitTab ��ȭ �����Դϴ�.

class CUnitTab : public CDialog
{
	DECLARE_DYNAMIC(CUnitTab)

public:
	CUnitTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CUnitTab();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_UNITTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
