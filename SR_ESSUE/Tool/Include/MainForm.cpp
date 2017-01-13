// MainForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MainForm.h"
#include "MainFrm.h"
#include "ToolView.h"
#include "MapTab.h"
// CMainForm

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CMainForm, CFormView)

CMainForm::CMainForm()
	: CFormView(CMainForm::IDD)
	, m_iType(0)
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


// CMainForm 진단입니다.

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


// CMainForm 메시지 처리기입니다.

void CMainForm::ChangeTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	UpdateData(TRUE);

	int iIndex = m_TabControl.GetCurSel();

	switch(iIndex)
	{
	case 0:
		m_pMap.ShowWindow(SW_SHOW);
		m_pObject.ShowWindow(SW_HIDE);
		m_pUnit.ShowWindow(SW_HIDE);
		m_pAnimation.ShowWindow(SW_HIDE);
		m_iType = 0;
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetBack(((CMainFrame*)AfxGetMainWnd())->m_pMainView->BK_MAP);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		break;

	case 1:
		m_pMap.ShowWindow(SW_HIDE);
		m_pObject.ShowWindow(SW_SHOW);
		m_pUnit.ShowWindow(SW_HIDE);
		m_pAnimation.ShowWindow(SW_HIDE);
		m_iType = 1;
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetBack(((CMainFrame*)AfxGetMainWnd())->m_pMainView->BK_OBJ);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		break;

	case 2:
		m_pMap.ShowWindow(SW_HIDE);
		m_pObject.ShowWindow(SW_HIDE);
		m_pUnit.ShowWindow(SW_SHOW);
		m_pAnimation.ShowWindow(SW_HIDE);
		m_iType = 2;
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->SetBack(((CMainFrame*)AfxGetMainWnd())->m_pMainView->BK_UNIT);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
		break;

	case 3:
		m_pMap.ShowWindow(SW_HIDE);
		m_pObject.ShowWindow(SW_HIDE);
		m_pUnit.ShowWindow(SW_HIDE);
		m_pAnimation.ShowWindow(SW_SHOW);
		m_iType = 2;
		m_iType = 3;
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
	m_TabControl.InsertItem(3, L"Animation");

	CRect rc;
	m_TabControl.GetClientRect(&rc);

	m_pMap.Create(IDD_MAPTAB, &m_TabControl );
	m_pMap.SetWindowPos(NULL, 0, 25, rc.Width() - 5, rc.Height() - 5, SWP_SHOWWINDOW);
	m_pMap.ShowWindow(SW_SHOW);

	m_pObject.Create(IDD_OBJECTTAB, &m_TabControl );
	m_pObject.SetWindowPos(NULL, 0, 25, rc.Width() - 5, rc.Height() - 5, SWP_SHOWWINDOW);
	m_pObject.ShowWindow(SW_HIDE);

	m_pUnit.Create(IDD_UNITTAB, &m_TabControl );
	m_pUnit.SetWindowPos(NULL, 0, 25, rc.Width() - 5, rc.Height() - 5, SWP_SHOWWINDOW);
	m_pUnit.ShowWindow(SW_HIDE);

	m_pAnimation.Create(IDD_ANIMATION, &m_TabControl );
	m_pAnimation.SetWindowPos(NULL, 0, 25, rc.Width() - 5, rc.Height() - 5, SWP_SHOWWINDOW);
	m_pAnimation.ShowWindow(SW_HIDE);

	HRESULT hr = NULL;

	int VtxcntX = ((CMapTab*)AfxGetMainWnd())->m_iCountX;
	int VtxcntZ = ((CMapTab*)AfxGetMainWnd())->m_iCountZ;


	Invalidate(false);


	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
}