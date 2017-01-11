#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "Resource.h"


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
