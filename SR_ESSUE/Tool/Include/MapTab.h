#pragma once


// CMapTab ��ȭ �����Դϴ�.

class CMapTab : public CDialog
{
	DECLARE_DYNAMIC(CMapTab)

public:
	CMapTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTab();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_MAPTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
