// MapTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"
#include "MainFrm.h"
#include "Background.h"


// CMapTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMapTab, CDialog)

CMapTab::CMapTab(CWnd* pParent /*=NULL*/)
	: CDialog(CMapTab::IDD, pParent)
	, m_iHeight(0)
	, m_iCountX(0)
	, m_iCountZ(0)
{

}

CMapTab::~CMapTab()
{
}

void CMapTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iCountX);
	DDX_Text(pDX, IDC_EDIT2, m_iCountZ);
	DDX_Text(pDX, IDC_EDIT3, m_iHeight);
	DDX_Control(pDX, IDC_COMBO1, m_TextureContrl);
	DDX_Control(pDX, IDC_SLIDER1, m_HeightSlider);
}


BEGIN_MESSAGE_MAP(CMapTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTab::OnCreateMap)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTab::OnHeightApply)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTab::OnTextureApply)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTab::OnSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTab::OnLoad)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMapTab::OnHeightSlider)
END_MESSAGE_MAP()


// CMapTab �޽��� ó�����Դϴ�.

void CMapTab::OnCreateMap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->AddTerrain(m_iCountX, m_iCountZ);
	((CMainFrame*)AfxGetMainWnd())->GetView()->Invalidate(TRUE);

	UpdateData(FALSE);
}

void CMapTab::OnHeightApply()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTab::OnTextureApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTab::OnSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTab::OnLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CMapTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_HeightSlider.SetRange(0, 20);
	m_HeightSlider.SetRangeMin(0);
	m_HeightSlider.SetRangeMax(20);
	m_HeightSlider.SetPos(0);
	m_HeightSlider.SetTicFreq(1);
	m_HeightSlider.SetPageSize(1);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMapTab::OnHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	m_iHeight = m_HeightSlider.GetPos();

	UpdateData(FALSE);
	*pResult = 0;
}
