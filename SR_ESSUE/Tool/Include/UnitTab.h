#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "Include.h"
#include "afxcmn.h"
#include "FileInfo.h"
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

public:
	CFileInfo					m_FileInfo;
	map<CString, CString>		m_mapPng;

	wstring m_wstrTexKey;
	CString m_strKey;
	CString m_TexKey;
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;

	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;

	float m_fAngleX;
	float m_fAngleY;
	float m_fAngleZ;

	int m_iActionRadio;
	int m_iCubetype;

	int m_iRed;
	int m_iGreen;
	int m_iBlue;

	CStatic m_ColorBox;
	CListBox m_TexListControl;

	CSliderCtrl m_XRotSlider;
	CSliderCtrl m_YRotSlider;
	CSliderCtrl m_ZRotSlider;

public:
	map<CString, UNITDATA*>		m_MapUnitData;
	bool						m_bStart;

public:
	void		Release(void);
	void		SetPos(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale);
	void		SetDesign(D3DXVECTOR3 vScale, DWORD dwColor);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnColorControl();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnColTexApply();
	afx_msg void OnSTApply();
	afx_msg void OnActionRadio(UINT msg);
	afx_msg void OnCubeTypeRadio(UINT msg);
	afx_msg void OnTextureListBox();
	
	afx_msg void OnDelete();
	afx_msg void OnClear();
	
	afx_msg void OnRotXSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotYSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnRotZSlider(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnApplyCube();
	afx_msg void OnEidtRotX();
	afx_msg void OnEidtRotY();
	afx_msg void OnEidtRotZ();
	afx_msg void OnChangeName();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnTransApply();
};
