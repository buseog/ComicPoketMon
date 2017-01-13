// MapTab.cpp : ���� �����Դϴ�.
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


// CMapTab ��ȭ �����Դϴ�.

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


// CMapTab �޽��� ó�����Դϴ�.

void CMapTab::OnCreateMap()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->AddTerrain(m_iCountX, m_iCountZ);
	((CMainFrame*)AfxGetMainWnd())->GetView()->Invalidate(TRUE);

	UpdateData(FALSE);
}

void CMapTab::OnHeightApply()
{
	UpdateData(TRUE);

	UpdateData(FALSE);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CMapTab::OnTextureApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->SetIndex(m_TextureContrl.GetCurSel());
	((CMainFrame*)AfxGetMainWnd())->GetView()->Invalidate(TRUE);
}

void CMapTab::OnSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dlg(FALSE,	// false - save, true - load
		L"dat", // ������ Ȯ���ڸ�
		L"*.dat", // ���ʿ� ����� ���� �̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CBackground*)((CMainFrame*)AfxGetMainWnd())->GetView()->m_pBackground[0])->AddTerrain(257, 257);

	CFileDialog		Dlg(TRUE,	// false - save, true - load
		L"dat", // ������ Ȯ���ڸ�
		L"*.dat", // ���ʿ� ����� ���� �̸�
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, 
		L"*.dat", // ���� �� �ؿ� ����ִ� ���� ����
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

	m_HeightSlider.SetRange(0, 20);
	m_HeightSlider.SetRangeMin(0);
	m_HeightSlider.SetRangeMax(20);
	m_HeightSlider.SetPos(0);
	m_HeightSlider.SetTicFreq(1);
	m_HeightSlider.SetPageSize(1);

	m_TextureContrl.AddString(L"����");
	m_TextureContrl.AddString(L"����1");
	m_TextureContrl.AddString(L"����2");
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CMapTab::OnHeightSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData(TRUE);

	m_iHeight = m_HeightSlider.GetPos();

	UpdateData(FALSE);
	*pResult = 0;
}
