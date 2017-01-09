// ObjectTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTab.h"


// CObjectTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CObjectTab, CDialog)

CObjectTab::CObjectTab(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectTab::IDD, pParent)
{

}

CObjectTab::~CObjectTab()
{
}

void CObjectTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CObjectTab, CDialog)
END_MESSAGE_MAP()


// CObjectTab 메시지 처리기입니다.
