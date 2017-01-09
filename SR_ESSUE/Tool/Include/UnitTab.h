#pragma once


// CUnitTab 대화 상자입니다.

class CUnitTab : public CDialog
{
	DECLARE_DYNAMIC(CUnitTab)

public:
	CUnitTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CUnitTab();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_UNITTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
