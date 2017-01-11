// UnitTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTab.h"
#include "Export_Function.h"
#include "ObjBack.h"
#include "MainFrm.h"


// CUnitTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTab, CDialog)

CUnitTab::CUnitTab(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTab::IDD, pParent)
	, m_bStart(true)
	, m_strKey(_T(""))
	, m_fScaleX(1.0f)
	, m_fScaleY(1.0f)
	, m_fScaleZ(1.0f)
	, m_fPosX(0)
	, m_fPosY(0)
	, m_fPosZ(0)
	, m_iActionRadio(0)
	, m_iRed(0)
	, m_iGreen(0)
	, m_iBlue(0)
{

}

CUnitTab::~CUnitTab()
{
	Release();
}

void CUnitTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLORBOX, m_ColorBox);
	DDX_Text(pDX, IDC_EDIT5, m_strKey);
	DDX_Text(pDX, IDC_EDIT1, m_fScaleX);
	DDX_Text(pDX, IDC_EDIT2, m_fScaleY);
	DDX_Text(pDX, IDC_EDIT3, m_fScaleZ);
	DDX_Text(pDX, IDC_EDIT6, m_fPosX);
	DDX_Text(pDX, IDC_EDIT7, m_fPosY);
	DDX_Text(pDX, IDC_EDIT8, m_fPosZ);
	DDX_Text(pDX, IDC_EDIT10, m_iRed);
	DDX_Text(pDX, IDC_EDIT11, m_iGreen);
	DDX_Text(pDX, IDC_EDIT12, m_iBlue);
	DDX_Radio(pDX, IDC_RADIO3, m_iActionRadio);
}


BEGIN_MESSAGE_MAP(CUnitTab, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO3, IDC_RADIO5, OnBnClickedRadio)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTab::OnColorControl)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTab::OnSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTab::OnLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTab::OnScaleApply)
	ON_BN_CLICKED(IDC_BUTTON6, &CUnitTab::OnTransApply)
	ON_BN_CLICKED(IDC_RADIO3, &CUnitTab::OnTransApply)
END_MESSAGE_MAP()


// CUnitTab 메시지 처리기입니다.

void CUnitTab::Release(void)
{
	for_each(m_MapUnitData.begin(), m_MapUnitData.end(), Engine::CDeleteMap());
	m_MapUnitData.clear();
}

void CUnitTab::SetPos( D3DXVECTOR3 vPos )
{
	UpdateData(TRUE);

	m_fPosX = vPos.x;
	m_fPosY = vPos.y;
	m_fPosZ = vPos.z;

	UpdateData(FALSE);

	Invalidate(TRUE);

}

void CUnitTab::SetDesign( D3DXVECTOR3 vScale, DWORD dwColor )
{

}

BOOL CUnitTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CUnitTab::OnColorControl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CColorDialog colorDlg;

	UpdateData(TRUE);
   
	if (colorDlg.DoModal() == IDOK)
	{
		COLORREF color = colorDlg.GetColor();

		CString strTemp;
		strTemp.Format((L"R: %u, G: %u, B: %u"), GetRValue(color), GetGValue(color), GetBValue(color));

		m_iRed = GetRValue(color);
		m_iGreen = GetRValue(color);
		m_iBlue = GetBValue(color);

		//AfxMessageBox(strTemp);

		CDC*	Box = m_ColorBox.GetWindowDC();
		CBrush	Fill(color);
		CRect	Rect(0, 0, 50, 50);

		Box->FillRect(&Rect, &Fill);
		m_ColorBox.ReleaseDC(Box);
	}

	UpdateData(FALSE);
	//Invalidate(FALSE);
}

void CUnitTab::OnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dlg(FALSE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);

	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;	

	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(Dlg.GetPathName(), 
		GENERIC_WRITE, 
		0, 
		NULL, 
		CREATE_ALWAYS, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	for(map<CString, UNITDATA*>::iterator	iter = m_MapUnitData.begin();
		iter != m_MapUnitData.end(); ++iter)
	{
		WriteFile(hFile, iter->second, sizeof(UNITDATA), &dwByte, NULL);
	}
	CloseHandle(hFile);
}

void CUnitTab::OnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CFileDialog		Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

	if(Dlg.DoModal() == IDCANCEL)
		return;

	Release();


	TCHAR		szDirPath[MAX_PATH] = L"";

	GetCurrentDirectory(sizeof(szDirPath), szDirPath);
	SetCurrentDirectory(szDirPath);
	PathRemoveFileSpec(szDirPath);
	lstrcat(szDirPath, L"\\Data");

	Dlg.m_ofn.lpstrInitialDir = szDirPath;	

	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(Dlg.GetPathName(), 
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	while(true)
	{
		UNITDATA*			pUnitData = new UNITDATA;
		ReadFile(hFile, pUnitData, sizeof(UNITDATA), &dwByte, NULL);

		if(dwByte == 0)
		{
			Engine::Safe_Delete(pUnitData);
			break;
		}
		m_MapUnitData.insert(map<CString, UNITDATA*>
			::value_type(pUnitData->wstrName.c_str(), pUnitData));

	}

	CloseHandle(hFile);

	UpdateData(FALSE);
}

void CUnitTab::OnScaleApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	UpdateData(FALSE);
}

void CUnitTab::OnTransApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetTransCube(D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ));
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);

	UpdateData(FALSE);
}

void CUnitTab::OnBnClickedRadio(UINT msg)

{

	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_pBuffer = NULL;

	UpdateData(TRUE);

	switch (m_iActionRadio)
	{
	case 0:
		break;

	case 1:
		break;

	case 2:
		break;
	}

	UpdateData(FALSE);

}
