// UnitTab.cpp : ���� �����Դϴ�.
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


// CUnitTab ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CUnitTab, CDialog)

CUnitTab::CUnitTab(CWnd* pParent /*=NULL*/)
	: CDialog(CUnitTab::IDD, pParent)
	, m_bStart(true)
	, m_strKey(_T(""))
	, m_TexKey(L"")
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
	ON_BN_CLICKED(IDC_BUTTON13, &CUnitTab::OnTransApply)
END_MESSAGE_MAP()


// CUnitTab �޽��� ó�����Դϴ�.

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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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

	HRESULT hr = NULL;

	//����

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"THead.dds", 
		L"../bin/Resources/Texture/CubeTexture/THead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/TBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/TArm.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/TArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TLeg.dds", 
		L"../bin/Resources/Texture/CubeTexture/TLeg.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"TLeg1.dds", 
		L"../bin/Resources/Texture/CubeTexture/TLeg1.dds", 
		1);

	// ���α�
	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/SHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/SBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm.dds", 
		1);
	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm2.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"SArm3.dds", 
		L"../bin/Resources/Texture/CubeTexture/SArm3.dds", 
		1);

	// ��ī��
	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/PHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PEar.dds", 
		L"../bin/Resources/Texture/CubeTexture/PEar.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PEar1.dds", 
		L"../bin/Resources/Texture/CubeTexture/PEar1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/PBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm.dds", 
		1);
	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm2.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"PArm3.dds", 
		L"../bin/Resources/Texture/CubeTexture/PArm3.dds", 
		1);

	// ���̸�
	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/CHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/CBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm.dds", 
		1);
	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm1.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm2.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CArm3.dds", 
		L"../bin/Resources/Texture/CubeTexture/CArm3.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Charman.dds", 
		L"../bin/Resources/Texture/CubeTexture/Charman.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Fire.dds", 
		L"../bin/Resources/Texture/CubeTexture/Fire.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"CTail1.dds", 
		L"../bin/Resources/Texture/CubeTexture/CTail1.dds", 
		1);

		// �ǹ� �ؽ���

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Cenmark.dds", 
		L"../bin/Resources/Texture/Cube/Cenmark.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"RoofTex.dds", 
		L"../bin/Resources/Texture/Cube/RoofTex.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Danger.dds", 
		L"../bin/Resources/Texture/Cube/Danger.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"RedRoof.dds", 
		L"../bin/Resources/Texture/Cube/RedRoof.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Wall_Wh.dds", 
		L"../bin/Resources/Texture/Cube/Wall_Wh.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Wooden.dds", 
		L"../bin/Resources/Texture/Cube/Wooden.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Glass.dds", 
		L"../bin/Resources/Texture/Cube/Glass.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"pokeball.dds", 
		L"../bin/Resources/Texture/CubeTexture/pokeball.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"renga1.dds", 
		L"../bin/Resources/Texture/Cube/renga1.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"renga2.dds", 
		L"../bin/Resources/Texture/Cube/renga2.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MBody.dds", 
		L"../bin/Resources/Texture/CubeTexture/MBody.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MHead.dds", 
		L"../bin/Resources/Texture/CubeTexture/MHead.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MLArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/MLArm.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MRArm.dds", 
		L"../bin/Resources/Texture/CubeTexture/MRArm.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MLWing.dds", 
		L"../bin/Resources/Texture/CubeTexture/MLWing.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MRWing.dds", 
		L"../bin/Resources/Texture/CubeTexture/MRWing.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MLLeg.dds", 
		L"../bin/Resources/Texture/CubeTexture/MLLeg.dds", 
		1);

	hr = Engine::Get_ResourceMgr()->AddTexture(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice,
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"MRLeg.dds", 
		L"../bin/Resources/Texture/CubeTexture/MRLeg.dds", 
		1);


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void CUnitTab::OnColorControl()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	DWORD dwType = ((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_dwType;

	if (dwType == 0)
	{
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
	else if (dwType == 1)
	{
		vector<Engine::CResources*>* vecObject = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_vecObject;

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

		for (size_t i = 0; i < vecObject->size(); ++i)
		{
			Engine::SAVEFILE tSave;

			wstring wstrKey = ((Engine::CCubeTex*)(*vecObject)[i])->GetKey();
			CString strKey;
			strKey = wstrKey.c_str();
			PathRemoveExtension((LPWSTR)strKey.operator LPCWSTR());
			wstrKey = (LPWSTR)strKey.operator LPCWSTR();

			tSave.wstrName = wstrKey;
			((Engine::CVIBuffer*)(*vecObject)[i])->GetOriginVtxInfo(&tSave.VtxInfo);

			WriteFile(hFile, &tSave, sizeof(Engine::SAVEFILE), &dwByte, NULL);
		}
		CloseHandle(hFile);
	}
}

void CUnitTab::OnLoad()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	DWORD dwType = ((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_dwType;

	if (dwType == 0)
	{
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

			TCHAR szBuf[255] = L"";
			wsprintf(szBuf, L"%s%s", pSave->wstrName.c_str(), L".dds");

			Engine::CResources* pResource = Engine::CCubeTex::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice, szBuf);

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
	}
	else if (dwType == 1)
	{
		vector<Engine::CResources*>* vecObject = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_vecObject;

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
			
			TCHAR szBuf[255] = L"";
			wsprintf(szBuf, L"%s%s", pSave->wstrName.c_str(), L".dds");

			Engine::CResources* pResource = Engine::CCubeTex::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice, szBuf);

			for (int i = 0; i < 8; ++i)
				pVtx[i] = pSave->VtxInfo[i];

			((Engine::CVIBuffer*)pResource)->SetOriginVtxInfo(pVtx);
			((Engine::CVIBuffer*)pResource)->SetVtxInfo(pVtx);

			vecObject->push_back(pResource);
			Engine::Safe_Delete(pSave);

		}

		CloseHandle(hFile);
		Engine::Safe_Delete_Array(pVtx);
		((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	}

	
	UpdateData(FALSE);
}

void CUnitTab::OnColTexApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetScaleCube(D3DXVECTOR3(m_fScaleX, m_fScaleY, m_fScaleZ));
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	UpdateData(FALSE);
	
}

void CUnitTab::OnTransApply()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);
	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetTransCube(D3DXVECTOR3(m_fPosX, m_fPosY, m_fPosZ));
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CUnitTab::OnClear()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CUnitTab::OnRotXSlider(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->SetApplyCube();

}

void CUnitTab::OnEidtRotX()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	UpdateData(TRUE);

	m_XRotSlider.SetPos((int)m_fAngleX);

	UpdateData(FALSE);
	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CUnitTab::OnEidtRotY()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	UpdateData(TRUE);

	m_YRotSlider.SetPos((int)m_fAngleY);

	UpdateData(FALSE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CUnitTab::OnEidtRotZ()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	UpdateData(TRUE);

	m_ZRotSlider.SetPos((int)m_fAngleZ);

	UpdateData(FALSE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CUnitTab::OnChangeName()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialog::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.
	UpdateData(TRUE);
	UpdateData(FALSE);

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}

void CUnitTab::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UpdateData(TRUE);
	CDialog::OnDropFiles(hDropInfo);

	int		iFileNumber = DragQueryFile(hDropInfo, -1, NULL, 0);
	// 1���� : ��ӵ� ���� ������ �����ϴ� ����ü
	// 2���� : ������ �ε����� ����, -1(0xffffffff)�� �����ϸ� �� �Լ��� ��ȯ������ ���� ������ ��ȯ
	// 3���� : ����� ���ϸ��� �ݳ��ϴ� ���ۿ��� �����͸� ����
	// 4���� : ������ ���� ������

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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);

	m_TexListControl.GetText(m_TexListControl.GetCurSel(), m_TexKey);

	m_strKey = m_TexKey;
	m_wstrTexKey = (LPWSTR)m_TexKey.operator LPCWSTR();
	PathRemoveExtension((LPWSTR)m_strKey.operator LPCWSTR());

	

	UpdateData(FALSE);
}
