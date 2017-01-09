// OptionForm.cpp : 구현 파일입니다.
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


// COptionForm 진단입니다.

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


// COptionForm 메시지 처리기입니다.
