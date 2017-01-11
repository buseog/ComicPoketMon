#pragma once
#include "Resource.h"
#include "afxwin.h"


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
public:
	float m_fScaleX;
	float m_fScaleY;
	float m_fScaleZ;
	CComboBox m_ComboControl;
	afx_msg void OnScaleApply();
	virtual BOOL OnInitDialog();
	CComboBox m_ComboBox;
	afx_msg void OnSaveData();
	float m_fSizeX;
	int m_fSizeY;
};
