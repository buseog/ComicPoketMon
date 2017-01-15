// UnitTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "UnitTab.h"
#include "Export_Function.h"
#include "ObjBack.h"
#include "MainFrm.h"
#include "CubeCol.h"
#include "CubeTex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CUnitTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CUnitTab, CDialog)

CUnitTab::CUnitTab(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTab::IDD, pParent)
	, m_bStart(true)
	, m_strKey(_T(""))
	, wstrTexKey(L"")
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
	, m_iCubetype(0)
	, m_fAngleX(0)
	, m_fAngleY(0)
	, m_fAngleZ(0)
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
	DDX_Text(pDX, IDC_EDIT9, m_fAngleX);
	DDX_Text(pDX, IDC_EDIT14, m_fAngleY);
	DDX_Text(pDX, IDC_EDIT15, m_fAngleZ);
	DDX_Radio(pDX, IDC_RADIO3, m_iActionRadio);
	DDX_Radio(pDX, IDC_RADIO1, m_iCubetype);
	DDX_Control(pDX, IDC_LIST1, m_TexListControl);
	DDX_Control(pDX, IDC_SLIDER2, m_XRotSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_YRotSlider);
	DDX_Control(pDX, IDC_SLIDER4, m_ZRotSlider);
}


BEGIN_MESSAGE_MAP(CUnitTab, CDialog)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO3, IDC_RADIO5, OnActionRadio)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO2, OnCubeTypeRadio)
	ON_BN_CLICKED(IDC_BUTTON2, &CUnitTab::OnColorControl)
	ON_BN_CLICKED(IDC_BUTTON3, &CUnitTab::OnSave)
	ON_BN_CLICKED(IDC_BUTTON4, &CUnitTab::OnLoad)
	ON_BN_CLICKED(IDC_BUTTON1, &CUnitTab::OnColTexApply)
	ON_BN_CLICKED(IDC_BUTTON6, &CUnitTab::OnSTApply)
	ON_LBN_SELCHANGE(IDC_LIST1, &CUnitTab::OnTextureListBox)
	ON_BN_CLICKED(IDC_BUTTON8, &CUnitTab::OnDelete)
	ON_BN_CLICKED(IDC_BUTTON9, &CUnitTab::OnClear)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &CUnitTab::OnRotXSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER3, &CUnitTab::OnRotYSlider)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER4, &CUnitTab::OnRotZSlider)
	ON_BN_CLICKED(IDC_BUTTON7, &CUnitTab::OnApplyCube)
	ON_EN_CHANGE(IDC_EDIT9, &CUnitTab::OnEidtRotX)
	ON_EN_CHANGE(IDC_EDIT14, &CUnitTab::OnEidtRotY)
	ON_EN_CHANGE(IDC_EDIT15, &CUnitTab::OnEidtRotZ)
	ON_EN_CHANGE(IDC_EDIT5, &CUnitTab::OnChangeName)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CUnitTab 메시지 처리기입니다.

void CUnitTab::Release(void)
{
	for_each(m_MapUnitData.begin(), m_MapUnitData.end(), Engine::CDeleteMap());
	m_MapUnitData.clear();
}

void CUnitTab::SetPos( D3DXVECTOR3 vPos, D3DXVECTOR3 vScale)
{
	UpdateData(TRUE);

	m_fPosX = vPos.x;
	m_fPosY = vPos.y;
	m_fPosZ = vPos.z;

	m_fScaleX = vScale.x;
	m_fScaleY = vScale.y;
	m_fScaleZ = vScale.z;

	UpdateData(FALSE);
}

void CUnitTab::SetDesign( D3DXVECTOR3 vScale, DWORD dwColor )
{

}

BOOL CUnitTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	UpdateData(TRUE);

	m_XRotSlider.SetRange(-180, 180);
	m_XRotSlider.SetRangeMin(-180);
	m_XRotSlider.SetRangeMax(180);
	m_XRotSlider.SetPos(0);
	m_XRotSlider.SetTicFreq(5);
	m_XRotSlider.SetPageSize(5);

	m_YRotSlider.SetRange(-180, 180);
	m_YRotSlider.SetRangeMin(-180);
	m_YRotSlider.SetRangeMax(180);
	m_YRotSlider.SetPos(0);
	m_YRotSlider.SetTicFreq(5);
	m_YRotSlider.SetPageSize(5);

	m_ZRotSlider.SetRange(-180, 180);
	m_ZRotSlider.SetRangeMin(-180);
	m_ZRotSlider.SetRangeMax(180);
	m_ZRotSlider.SetPos(0);
	m_ZRotSlider.SetTicFreq(5);
	m_ZRotSlider.SetPageSize(5);

	UpdateData(FALSE);

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
		
		m_iRed = GetRValue(color);
		m_iGreen = GetGValue(color);
		m_iBlue = GetBValue(color);

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
	map<wstring, Engine::CResources*>* mapChar = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_mapChar;
	
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

	for (map<wstring, Engine::CResources*>::iterator iter = mapChar->begin();
		iter != mapChar->end(); ++iter)
	{
		Engine::SAVEFILE tSave;
		tSave.wstrName = iter->first;
		((Engine::CVIBuffer*)iter->second)->GetOriginVtxInfo(&tSave.VtxInfo);

		WriteFile(hFile, &tSave, sizeof(Engine::SAVEFILE), &dwByte, NULL);
	}
	CloseHandle(hFile);
}

void CUnitTab::OnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	map<wstring, Engine::CResources*>* mapChar = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_mapChar;

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

	Engine::VTXCUBE*		pVtx = new Engine::VTXCUBE[8];

	while(true)
	{
		Engine::SAVEFILE* pSave = new Engine::SAVEFILE;
		ReadFile(hFile, pSave, sizeof(Engine::SAVEFILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			Engine::Safe_Delete(pSave);
			break;
		}

		Engine::CResources* pResource = Engine::CCubeTex::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice);

		for (int i = 0; i < 8; ++i)
			pVtx[i] = pSave->VtxInfo[i];

		((Engine::CVIBuffer*)pResource)->SetOriginVtxInfo(pVtx);
		((Engine::CVIBuffer*)pResource)->SetVtxInfo(pVtx);

		mapChar->insert(make_pair(pSave->wstrName, pResource));
		Engine::Safe_Delete(pSave);

	}

	CloseHandle(hFile);

	Engine::Safe_Delete_Array(pVtx);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	UpdateData(FALSE);
}

void CUnitTab::OnColTexApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	switch (m_iCubetype)
	{
	case 0:
		((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetColor(D3DCOLOR_ARGB(255, m_iRed, m_iGreen, m_iBlue));
		break;
	case 1:
		break;
	}
	UpdateData(FALSE);
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
}

void CUnitTab::OnSTApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetTransCube(D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ), D3DXVECTOR3(m_fScaleX, m_fScaleY, m_fScaleZ));
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);

	UpdateData(FALSE);
}

void CUnitTab::OnActionRadio(UINT msg)

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


void CUnitTab::OnCubeTypeRadio(UINT msg)

{
	UpdateData(TRUE);

	switch (m_iCubetype)
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



void CUnitTab::OnDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTab::OnClear()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTab::OnRotXSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if (GetAsyncKeyState(VK_LBUTTON))
		m_fAngleX = (float)m_XRotSlider.GetPos();

	UpdateData(FALSE);

	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetRotationCube(0, m_fAngleX, D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ));
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	*pResult = 0;
}

void CUnitTab::OnRotYSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if (GetAsyncKeyState(VK_LBUTTON))
		m_fAngleY = (float)m_YRotSlider.GetPos();

	UpdateData(FALSE);

	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetRotationCube(1, m_fAngleY, D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ));
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);

	*pResult = 0;
}

void CUnitTab::OnRotZSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	if (GetAsyncKeyState(VK_LBUTTON))
		m_fAngleZ = (float)m_ZRotSlider.GetPos();

	UpdateData(FALSE);

	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetRotationCube(2, m_fAngleZ, D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ));
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);

	*pResult = 0;
}

void CUnitTab::OnApplyCube()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetApplyCube();

}

void CUnitTab::OnEidtRotX()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	UpdateData(TRUE);

	m_XRotSlider.SetPos((int)m_fAngleX);

	UpdateData(FALSE);
	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTab::OnEidtRotY()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	UpdateData(TRUE);

	m_YRotSlider.SetPos((int)m_fAngleY);

	UpdateData(FALSE);

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTab::OnEidtRotZ()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	UpdateData(TRUE);

	m_ZRotSlider.SetPos((int)m_fAngleZ);

	UpdateData(FALSE);

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTab::OnChangeName()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.
	UpdateData(TRUE);
	UpdateData(FALSE);

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CUnitTab::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);
	CDialog::OnDropFiles(hDropInfo);

	int		iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 1인자 : 드롭된 파일 정보를 저장하는 구조체
	// 2인자 : 파일의 인덱스를 지정, -1(0xffffffff)을 지정하면 이 함수의 반환값으로 파일 개수를 반환
	// 3인자 : 취득한 파일명을 격납하는 버퍼에의 포인터를 지정
	// 4인자 : 지정한 버퍼 사이즈

	TCHAR	szFullPath[MAX_PATH] = L"";
 
	for(int i = 0; i < iFileNumber; ++i)
	{
		DragQueryFile(hDropInfo, i, (LPWSTR)szFullPath, MAX_PATH);

		wstring wstrRelativePath = m_FileInfo.ConvertRelativePath(szFullPath);

		CString		strImageName;		

		strImageName = PathFindFileName(wstrRelativePath.c_str());

		map<CString, CString>::iterator iter = m_mapPng.find(strImageName);

		if(iter == m_mapPng.end())
		{
			m_mapPng.insert(map<CString, CString>::value_type(strImageName, szFullPath));
			m_TexListControl.AddString(strImageName);
		}

	}

	UpdateData(FALSE);
}

void CUnitTab::OnTextureListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CString strTemp;

	m_TexListControl.GetText(m_TexListControl.GetCurSel(), strTemp);

	wstrTexKey = (LPWSTR)strTemp.operator LPCWSTR();

	UpdateData(FALSE);
}