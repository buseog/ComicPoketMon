#pragma once
#include "afxcmn.h"

#include "MapTab.h"
#include "ObjectTab.h"
#include "UnitTab.h"


// CMainForm 폼 뷰입니다.
namespace Engine
{
	class CResourceMgr;
}
class CToolView;
class CMainForm : public CFormView
{
	DECLARE_DYNCREATE(CMainForm)
public:
	CMapTab		m_pMap;
	CObjectTab	m_pObject;
	CUnitTab	m_pUnit;
	int			m_iType;

	Engine::CResourceMgr*	m_pResourceMgr;
	LPDIRECT3DDEVICE9*		m_pDevice;

protected:
	CMainForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void ChangeTab(NMHDR *pNMHDR, LRESULT *pResult);

private:
	CTabCtrl m_TabControl;
public:
	virtual void OnInitialUpdate();
};


