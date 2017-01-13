// MapTab.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTab.h"
#include "MainFrm.h"
#include "Background.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CMapTab 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTab, CDialog)

#include "Export_Function.h"
#include "Engine_Include.h"

CMapTab::CMapTab(CWnd* pParent /*=NULL*/)
	: CDialog(CMapTab::IDD, pParent)
	, m_iHeight(0)
	, m_iCountX(0)
	, m_iCountZ(0)
{

}

CMapTab::~CMapTab()
{
}

void CMapTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iCountX);
	DDX_Text(pDX, IDC_EDIT2, m_iCountZ);
	DDX_Text(pDX, IDC_EDIT3, m_iHeight);
	DDX_Control(pDX, IDC_COMBO1, m_TextureContrl);
	DDX_Control(pDX, IDC_SLIDER1, m_HeightSlider);
}


BEGIN_MESSAGE_MAP(CMapTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTab::OnCreateMap)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTab::OnHeightApply)
	ON_BN_CLICKED(IDC_BUTTON3, &CMapTab::OnTextureApply)
	ON_BN_CLICKED(IDC_BUTTON4, &CMapTab::OnSave)
	ON_BN_CLICKED(IDC_BUTTON5, &CMapTab::OnLoad)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CMapTab::OnHeightSlider)
END_MESSAGE_MAP()


// CMapTab 메시지 처리기입니다.

void CMapTab::OnCreateMap()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->AddTerrain(m_iCountX, m_iCountZ);
	((CMainFrame*)AfxGetMainWnd())->GetView()->Invalidate(TRUE);

	UpdateData(FALSE);
}

void CMapTab::OnHeightApply()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CMapTab::OnTextureApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->SetIndex(m_TextureContrl.GetCurSel());
	((CMainFrame*)AfxGetMainWnd())->GetView()->Invalidate(TRUE);
}

void CMapTab::OnSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dlg(FALSE,	// false - save, true - load
		L"dat", // 파일의 확장자명
		L"*.dat", // 최초에 띄워줄 파일 이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
		this);

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



	Engine::VTXTEX*		pVTXCOL = ((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->GetVtxcol();

	if(pVTXCOL == NULL)
		return;

	for(int z = 0; z < m_iCountZ; ++z)
	{
		for(int x = 0; x < m_iCountX; ++x)
		{
			int iIndex = z * m_iCountX + x; 
			WriteFile(hFile, &pVTXCOL[iIndex], sizeof(Engine::VTXTEX), &dwByte, NULL);
		}
	}
	CloseHandle(hFile);
}

void CMapTab::OnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->AddTerrain(257, 257);

	CFileDialog		Dlg(TRUE,	// false - save, true - load
		L"dat", // 파일의 확장자명
		L"*.dat", // 최초에 띄워줄 파일 이름
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // 저장 시 밑에 띄워주는 파일 형식
		this);

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
		GENERIC_READ, 
		0, 
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL, 
		NULL);

	Engine::VTXTEX*		pVTXCOL = new Engine::VTXTEX[257*257];
	int i = 0;
	while(true)
	{
		Engine::VTXTEX*		pVTXCOL2 = new Engine::VTXTEX;
		ReadFile(hFile, pVTXCOL2, sizeof(Engine::VTXTEX), &dwByte, NULL);

		if(dwByte == 0)
		{
			((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->SetVtxcol(pVTXCOL);
			//Engine::Safe_Delete(*pVTXCOL2);
			break;
		}
		pVTXCOL[i] = *pVTXCOL2;
		++i;

	}

	CloseHandle(hFile);
	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->m_pBuffer->SetVtxInfo(pVTXCOL);

	((CMainFrame*)AfxGetMainWnd())->GetView()->Invalidate(TRUE);
}

BOOL CMapTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_HeightSlider.SetRange(0, 20);
	m_HeightSlider.SetRangeMin(0);
	m_HeightSlider.SetRangeMax(20);
	m_HeightSlider.SetPos(0);
	m_HeightSlider.SetTicFreq(1);
	m_HeightSlider.SetPageSize(1);

	m_TextureContrl.AddString(L"지형");
	m_TextureContrl.AddString(L"지형1");
	m_TextureContrl.AddString(L"지형2");
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CMapTab::OnHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_iHeight = m_HeightSlider.GetPos();

	UpdateData(FALSE);
	*pResult = 0;
}
