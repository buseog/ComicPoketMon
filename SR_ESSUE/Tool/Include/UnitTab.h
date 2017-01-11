#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "Include.h"

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

public:
	CString m_strKey;
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;

	float m_fPosX;
	float m_fPosY;
	float m_fPosZ;

	int m_iRed;
	int m_iGreen;
	int m_iBlue;
	int m_iActionRadio;
	CStatic m_ColorBox;

public:
	map<CString, UNITDATA*>		m_MapUnitData;
	bool						m_bStart;

public:
	void		Release(void);
	void		SetPos(D3DXVECTOR3 vPos);
	void		SetDesign(D3DXVECTOR3 vScale, DWORD dwColor);
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnColorControl();
	afx_msg void OnSave();
	afx_msg void OnLoad();
	afx_msg void OnScaleApply();
	afx_msg void OnTransApply();
	afx_msg void OnBnClickedRadio(UINT msg);
};
