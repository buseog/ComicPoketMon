// OptionForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "OptionForm.h"


// COptionForm

IMPLEMENT_DYNCREATE(COptionForm, CFormView)

COptionForm::COptionForm()
	: CFormView(COptionForm::IDD)
{

}

COptionForm::~COptionForm()
{
}

void COptionForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COptionForm, CFormView)
END_MESSAGE_MAP()


// COptionForm �����Դϴ�.

#ifdef _DEBUG
void COptionForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COptionForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COptionForm �޽��� ó�����Դϴ�.
