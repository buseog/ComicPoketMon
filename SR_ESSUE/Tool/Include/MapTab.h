#pragma once


// CMapTab 대화 상자입니다.

class CMapTab : public CDialog
{
	DECLARE_DYNAMIC(CMapTab)

public:
	CMapTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTab();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_MAPTAB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
