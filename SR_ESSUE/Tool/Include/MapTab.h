#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Resource.h"


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
public:
	int m_iCountX;
	int m_iCountZ;
	int m_iHeight;
	CComboBox m_TextureContrl;
	CSliderCtrl m_HeightSlider;

	afx_msg void OnCreateMap();
	afx_msg void OnHeightApply();
	afx_msg void OnTextureApply();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	virtual BOOL OnInitDialog();
	afx_msg void OnHeightSlider(NMHDR *pNMHDR, LRESULT *pResult);
	
};
