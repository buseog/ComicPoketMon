// MainForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MainForm.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "MapTab.h"
// CMainForm

IMPLEMENT_DYNCREATE(CMainForm, CFormView)

#include "Export_Function.h"


CMainForm::CMainForm()
	: CFormView(CMainForm::IDD)
	, m_iType(0)
	, m_pResourceMgr(Engine::Get_ResourceMgr())
{

}

CMainForm::~CMainForm()
{
}

void CMainForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_TabControl);
}

BEGIN_MESSAGE_MAP(CMainForm, CFormView)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CMainForm::ChangeTab)
END_MESSAGE_MAP()


// CMainForm �����Դϴ�.

#ifdef _DEBUG
void CMainForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMainForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainForm �޽��� ó�����Դϴ�.

void CMainForm::ChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	UpdateData(TRUE);

	int iIndex = m_TabControl.GetCurSel();

	switch(iIndex)
	{
	case 0:
		m_pMap.ShowWindow(SW_SHOW);
		m_pObject.ShowWindow(SW_HIDE);
		m_pUnit.ShowWindow(SW_HIDE);
		m_iType = 0;
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetBack(((CMainFrame*)AfxGetMainWnd())->m_pMainView->BK_MAP);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		break;

	case 1:
		m_pMap.ShowWindow(SW_HIDE);
		m_pObject.ShowWindow(SW_SHOW);
		m_pUnit.ShowWindow(SW_HIDE);
		m_iType = 1;
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetBack(((CMainFrame*)AfxGetMainWnd())->m_pMainView->BK_OBJ);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		break;

	case 2:
		m_pMap.ShowWindow(SW_HIDE);
		m_pObject.ShowWindow(SW_HIDE);
		m_pUnit.ShowWindow(SW_SHOW);
		m_iType = 2;
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetBack(((CMainFrame*)AfxGetMainWnd())->m_pMainView->BK_UNIT);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		break;

	}

	UpdateData(FALSE);
}

void CMainForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	m_TabControl.DeleteAllItems();
	m_TabControl.InsertItem(0, L"Map");
	m_TabControl.InsertItem(1, L"Object");
	m_TabControl.InsertItem(2, L"Unit");

	CRect rect;
	m_TabControl.GetClientRect(&rect);

	m_pMap.Create(IDD_MAPTAB, &m_TabControl );
	m_pMap.GetWindowRect(&rect);
	m_pMap.MoveWindow(0,25, 250, 400);
	m_pMap.ShowWindow(SW_SHOW);

	m_pObject.Create(IDD_OBJECTTAB, &m_TabControl );
	m_pObject.GetWindowRect(&rect);
	m_pObject.MoveWindow(0,25, 250, 400);
	m_pObject.ShowWindow(SW_HIDE);

	m_pUnit.Create(IDD_UNITTAB, &m_TabControl );
	m_pUnit.GetWindowRect(&rect);
	m_pUnit.MoveWindow(0,25, 250, 400);
	m_pUnit.ShowWindow(SW_HIDE);

	HRESULT hr = NULL;

	int VtxcntX = ((CMapTab*)AfxGetMainWnd())->m_iCountX;
	int VtxcntZ = ((CMapTab*)AfxGetMainWnd())->m_iCountZ;

	

	hr = m_pResourceMgr->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice, 
		Engine::RESOURCE_DYNAMIC, 
		Engine::TEX_NORMAL, 
		L"Texture Terrain", 
		L"../bin/Resources/Texture/Terrain/Terrain%d.png", 
		1);
	//FAILED_CHECK_MSG(hr, L"Texture Terrain Create Failed");

	Invalidate(false);


	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
}