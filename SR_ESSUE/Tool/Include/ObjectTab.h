#pragma once


// CObjectTab ��ȭ �����Դϴ�.

class CObjectTab : public CDialog
{
	DECLARE_DYNAMIC(CObjectTab)

public:
	CObjectTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CObjectTab();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_OBJECTTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
