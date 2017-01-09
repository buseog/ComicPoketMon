#pragma once
#include "afxcmn.h"

#include "MapTab.h"
#include "ObjectTab.h"
#include "UnitTab.h"


// CMainForm �� ���Դϴ�.

class CMainForm : public CFormView
{
	DECLARE_DYNCREATE(CMainForm)
private:
	CMapTab		m_pMap;
	CObjectTab	m_pObject;
	CUnitTab	m_pUnit;

protected:
	CMainForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMainForm();

public:
	enum { IDD = IDD_MAINFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void ChangeTab(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CTabCtrl m_TabControl;
public:
	virtual void OnInitialUpdate();
};


