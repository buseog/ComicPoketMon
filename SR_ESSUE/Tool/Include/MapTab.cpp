// MapTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"


// CMapTab ��ȭ �����Դϴ�.

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


// CMapTab �޽��� ó�����Դϴ�.
