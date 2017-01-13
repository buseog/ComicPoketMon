// ObjectTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CObjectTab 대화 상자입니다.

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BOOL CObjectTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CObjectTab::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
