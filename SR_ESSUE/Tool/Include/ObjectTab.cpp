// ObjectTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "ObjectTab.h"


// CObjectTab ��ȭ �����Դϴ�.

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


// CObjectTab �޽��� ó�����Դϴ�.
