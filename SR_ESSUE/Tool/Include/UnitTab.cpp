// UnitTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTab.h"


// CUnitTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTab, CDialog)

CUnitTab::CUnitTab(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTab::IDD, pParent)
{

}

CUnitTab::~CUnitTab()
{
}

void CUnitTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CUnitTab, CDialog)
END_MESSAGE_MAP()


// CUnitTab 메시지 처리기입니다.
