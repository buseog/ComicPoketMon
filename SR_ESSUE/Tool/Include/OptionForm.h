#pragma once



// COptionForm �� ���Դϴ�.

class COptionForm : public CFormView
{
	DECLARE_DYNCREATE(COptionForm)

protected:
	COptionForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~COptionForm();

public:
	enum { IDD = IDD_OPTIONFORM };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};


