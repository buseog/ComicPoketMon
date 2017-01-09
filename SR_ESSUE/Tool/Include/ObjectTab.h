#pragma once


// CObjectTab 대화 상자입니다.

class CObjectTab : public CDialog
{
	DECLARE_DYNAMIC(CObjectTab)

public:
	CObjectTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CObjectTab();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_OBJECTTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
