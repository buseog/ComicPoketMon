// ObjectTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CObjectTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CObjectTab, CDialog)

CObjectTab::CObjectTab(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectTab::IDD, pParent)
	, m_fScaleX(0)
	, m_fScaleY(0)
	, m_fScaleZ(0)
	, m_fSizeX(0)
	, m_fSizeY(0)
{

}

CObjectTab::~CObjectTab()
{
}

void CObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_COMBO1, m_ComboControl);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
	DDX_Text(pDX, IDC_EDIT1, m_fSizeX);
	DDX_Text(pDX, IDC_EDIT2, m_fSizeY);
}


BEGIN_MESSAGE_MAP(CObjectTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON4, &CObjectTab::OnScaleApply)
	ON_BN_CLICKED(IDC_BUTTON1, &CObjectTab::OnSaveData)
END_MESSAGE_MAP()

void CObjectTab::OnScaleApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

BOOL CObjectTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CObjectTab::OnSaveData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}
