// UnitTab.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTab.h"


// CUnitTab ��ȭ �����Դϴ�.

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


// CUnitTab �޽��� ó�����Դϴ�.
