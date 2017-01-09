// MapTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"


// CMapTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTab, CDialog)

CMapTab::CMapTab(CWnd* pParent /*=NULL*/)
	: CDialog(CMapTab::IDD, pParent)
{

}

CMapTab::~CMapTab()
{
}

void CMapTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMapTab, CDialog)
END_MESSAGE_MAP()


// CMapTab 메시지 처리기입니다.
