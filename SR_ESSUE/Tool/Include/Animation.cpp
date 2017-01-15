// Animation.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "Animation.h"

#include "ObjBack.h"
#include "MainFrm.h"
#include "CubeCol.h"
#include "CubeMotion.h"
#include "CubeObj.h"
#include "Resources.h"
#include "CubeTex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// CAnimation 대화 상자입니다.

IMPLEMENT_DYNAMIC(CAnimation, CDialog)

CAnimation::CAnimation(CWnd* pParent /*=NULL*/)
	: CDialog(CAnimation::IDD, pParent)
	, m_pCubeMotion(NULL)
	, m_pCUbeObj(NULL)
	, m_bPlay(false)
	, m_dwFrame(-1)
	, m_dwMaxFrame(-1)
{

}

CAnimation::~CAnimation()
{
	Engine::Safe_Delete(m_pCubeMotion);
}

void CAnimation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_StateListCtrl);
	DDX_Control(pDX, IDC_LIST2, m_FrameListCtrl);
	DDX_Control(pDX, IDC_COMBO1, m_StateComboCtrl);
}


BEGIN_MESSAGE_MAP(CAnimation, CDialog)
	ON_BN_CLICKED(IDC_BUTTON5, &CAnimation::OnUp)
	ON_BN_CLICKED(IDC_BUTTON10, &CAnimation::OnFrameAdd)
	ON_BN_CLICKED(IDC_BUTTON11, &CAnimation::OnFrameDelete)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CAnimation::OnStateComboCtrl)
	ON_BN_CLICKED(IDC_BUTTON3, &CAnimation::OnSave)
	ON_LBN_SELCHANGE(IDC_LIST1, &CAnimation::OnStateList)
	ON_BN_CLICKED(IDC_BUTTON1, &CAnimation::OnPlay)
	ON_BN_CLICKED(IDC_BUTTON6, &CAnimation::OnStop)
	ON_BN_CLICKED(IDC_BUTTON12, &CAnimation::OnDown)
	ON_BN_CLICKED(IDC_BUTTON4, &CAnimation::OnLoad)
	ON_LBN_SELCHANGE(IDC_LIST2, &CAnimation::OnFrameList)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAnimation 메시지 처리기입니다.


void CAnimation::OnFrameAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_StateComboCtrl.GetCurSel() < 0)
		return;

	UpdateData(TRUE);

	map<wstring, Engine::CResources*>* mapChar = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_mapChar;

	m_pCUbeObj = Engine::CCubeObj::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice);
	vector<Engine::SAVEFRAME*>*	pvecParts = m_pCUbeObj->GetVecPart();

	CString strTemp;
	m_StateComboCtrl.GetLBText(m_StateComboCtrl.GetCurSel(), strTemp);

	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();

	m_pCubeMotion->AddSprite(wstrState, m_pCUbeObj);
	map<wstring, vector<Engine::CCubeObj*>>* pSpriteMap = m_pCubeMotion->GetSpriteMap();
	map<wstring, vector<Engine::CCubeObj*>>::iterator Spriteiter = pSpriteMap->find(wstrState);

	for (map<wstring, Engine::CResources*>::iterator iter = mapChar->begin(); iter != mapChar->end(); ++iter)
	{
		Engine::SAVEFRAME* pSave = new Engine::SAVEFRAME;

		pSave->wstrStateKey = wstrState;
		pSave->FrameKey = Spriteiter->second.size() - 1;
		pSave->wstrPartsKey = iter->first;
		

		((Engine::CVIBuffer*)iter->second)->GetOriginVtxInfo(pSave->VtxInfo);

		for (size_t i = 0 ; i < pvecParts->size() ; ++i)
		{
			if ((*pvecParts)[i]->wstrPartsKey == pSave->wstrPartsKey)
				continue;
		}

		pvecParts->push_back(pSave);
	}

	// 스테이트키로 저장함
	for (int i = 0; i < m_StateListCtrl.GetCount(); ++i)
	{
		if (m_StateListCtrl.FindString(i, strTemp) >= 0)
		{		
			UpdateData(FALSE);
			return;
		}
	}

	m_StateListCtrl.AddString(strTemp);

	UpdateData(FALSE);
		
}

void CAnimation::OnFrameDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString strTemp;
	m_StateListCtrl.GetText(m_StateListCtrl.GetCurSel(), strTemp);

	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();;

	map<wstring, vector<Engine::CCubeObj*>>* pMapSprite = m_pCubeMotion->GetSpriteMap();
	map<wstring, vector<Engine::CCubeObj*>>::iterator iter = pMapSprite->find(wstrState);

	int iCount = m_FrameListCtrl.GetCurSel();
	int iStart = iCount;

	for (vector<Engine::CCubeObj*>::iterator veciter = iter->second.begin(); veciter != iter->second.end(); ++veciter)
	{
		if (iCount == 0)
		{
			Engine::Safe_Delete(*veciter);
			iter->second.erase(veciter);
			break;
		}
		--iCount;
	}

	for (size_t i = iStart; i < iter->second.size(); ++i)
	{
		vector<Engine::SAVEFRAME*>* pFrame = ((Engine::CCubeObj*)iter->second[i])->GetVecPart();

		for (size_t j = 0; j < pFrame->size(); ++j)
		{
			(*pFrame)[j]->FrameKey -= 1;
		}
	}

	m_FrameListCtrl.DeleteString(m_FrameListCtrl.GetCurSel());

	UpdateData(FALSE);
	Invalidate(FALSE);	
}

void CAnimation::OnStateComboCtrl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CAnimation::OnSave()
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

	map<wstring, vector<Engine::CCubeObj*>>* pMapSprite = m_pCubeMotion->GetSpriteMap();

	map<wstring, vector<Engine::CCubeObj*>>::iterator iter = pMapSprite->begin();
	map<wstring, vector<Engine::CCubeObj*>>::iterator iter_end = pMapSprite->end();

	int iCount = 0;

	for ( ; iter != iter_end; ++iter)
	{
		vector<Engine::CCubeObj*>::iterator veciter = iter->second.begin();
		vector<Engine::CCubeObj*>::iterator veciter_end = iter->second.end();
	
		for ( ; veciter != veciter_end; ++veciter)
		{
			vector<Engine::SAVEFRAME*>* pvecFrame = ((Engine::CCubeObj*)(*veciter))->GetVecPart();

			for (size_t i = 0 ; i < pvecFrame->size() ; ++i)
			{
				Engine::SAVEFRAME tSave;
				tSave.wstrStateKey = (*pvecFrame)[i]->wstrStateKey;
				tSave.FrameKey = (*pvecFrame)[i]->FrameKey;
				tSave.wstrPartsKey = (*pvecFrame)[i]->wstrPartsKey;

				memcpy(&(tSave.VtxInfo), &((*pvecFrame)[i]->VtxInfo), sizeof(Engine::VTXCUBE) * 8);
				WriteFile(hFile, &tSave, sizeof(Engine::SAVEFRAME), &dwByte, NULL);
			}
		}
	}
	CloseHandle(hFile);
}

BOOL CAnimation::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	m_pCubeMotion = Engine::CCubeMotion::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice);
	
	m_StateComboCtrl.AddString(L"Stand");
	m_StateComboCtrl.AddString(L"Walk");
	m_StateComboCtrl.AddString(L"Attack");
	m_StateComboCtrl.AddString(L"Skill");
	m_StateComboCtrl.AddString(L"Death");

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CAnimation::OnStateList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_StateListCtrl.GetCurSel() < 0)
		return;

	UpdateData(TRUE);

	m_FrameListCtrl.ResetContent();

	CString strTemp;
	m_StateListCtrl.GetText(m_StateListCtrl.GetCurSel(), strTemp);

	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();

	map<wstring, vector<Engine::CCubeObj*>>* pSpriteMap = m_pCubeMotion->GetSpriteMap();
	map<wstring, vector<Engine::CCubeObj*>>::iterator iter = pSpriteMap->find(wstrState);

	// 프레임 숫자 지정

	for (size_t i = 0; i < iter->second.size(); ++i)
	{
		TCHAR szFrame[MAX_PATH] = L"";

		wsprintf(szFrame, L"%d", ((Engine::CCubeObj*)iter->second[i])->GetVecPart()->front()->FrameKey);

		m_FrameListCtrl.AddString(szFrame);
	}

	

	UpdateData(FALSE);
}

void CAnimation::OnPlay()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_dwFrame = 0;

	m_dwMaxFrame = m_FrameListCtrl.GetCount();

	m_FrameListCtrl.SetCurSel(0);

	m_bPlay = true;

	SetTimer(1394, 150, NULL);

	UpdateData(FALSE);
}

void CAnimation::OnStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_StateListCtrl.GetCurSel() < 0)
		return;

	UpdateData(TRUE);

	m_bPlay = false;

	KillTimer(1394);

	UpdateData(FALSE);
}

void CAnimation::OnUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (m_FrameListCtrl.GetCurSel() <= 0)
		return;

	UpdateData(TRUE);

	CString strTemp;
	m_StateListCtrl.GetText(m_StateListCtrl.GetCurSel(), strTemp);

	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();

	map<wstring, vector<Engine::CCubeObj*>>* pMapSprite = m_pCubeMotion->GetSpriteMap();
	map<wstring, vector<Engine::CCubeObj*>>::iterator iter = pMapSprite->find(wstrState);
	
	for (vector<Engine::SAVEFRAME*>::iterator iter2 = ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel()])->GetVecPart()->begin();
		iter2 != ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel()])->GetVecPart()->end(); ++iter2)
	{
		(*iter2)->FrameKey -= 1; 
	}

	if (m_FrameListCtrl.GetCurSel() - 1 >= 0)
	{
		for (vector<Engine::SAVEFRAME*>::iterator iter2 = ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel() - 1])->GetVecPart()->begin();
			iter2 != ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel() - 1])->GetVecPart()->end(); ++iter2)
		{
			(*iter2)->FrameKey += 1; 
		}

		swap(iter->second[m_FrameListCtrl.GetCurSel() - 1], iter->second[m_FrameListCtrl.GetCurSel()]);
	}
	
	UpdateData(FALSE);
	Invalidate(FALSE);
}

void CAnimation::OnDown()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	CString strTemp;
	m_StateListCtrl.GetText(m_StateListCtrl.GetCurSel(), strTemp);

	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();

	map<wstring, vector<Engine::CCubeObj*>>* pMapSprite = m_pCubeMotion->GetSpriteMap();
	map<wstring, vector<Engine::CCubeObj*>>::iterator iter = pMapSprite->find(wstrState);

	
	for (vector<Engine::SAVEFRAME*>::iterator iter2 = ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel()])->GetVecPart()->begin();
		iter2 != ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel()])->GetVecPart()->end(); ++iter2)
	{
		(*iter2)->FrameKey += 1; 
	}
	if (m_FrameListCtrl.GetCurSel() + 1 < m_FrameListCtrl.GetCount())
	{
		for (vector<Engine::SAVEFRAME*>::iterator iter2 = ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel() + 1])->GetVecPart()->begin();
			iter2 != ((Engine::CCubeObj*)iter->second[m_FrameListCtrl.GetCurSel() + 1])->GetVecPart()->end(); ++iter2)
		{
			(*iter2)->FrameKey -= 1; 
		}

		swap(iter->second[m_FrameListCtrl.GetCurSel() + 1], iter->second[m_FrameListCtrl.GetCurSel()]);
	}

	UpdateData(FALSE);
	Invalidate(FALSE);
}

void CAnimation::OnLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_FrameListCtrl.ResetContent();
	m_StateListCtrl.ResetContent();
	
	m_pCubeMotion->Release();

	CFileDialog		Dlg(TRUE, L"dat", L"*.dat", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, L"*.dat", this);

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

	int iFlag = 0;
	m_pCUbeObj = Engine::CCubeObj::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice);

	while(true)
	{
		Engine::SAVEFRAME* pSave = new Engine::SAVEFRAME;

		ReadFile(hFile, pSave, sizeof(Engine::SAVEFRAME), &dwByte, NULL);

		if(dwByte == 0)
		{
			m_pCubeMotion->AddSprite(m_pCUbeObj->GetVecPart()->front()->wstrStateKey, m_pCUbeObj);
			Engine::Safe_Delete(pSave);
			break;
		}

		if (iFlag == pSave->FrameKey)
		{
			m_pCUbeObj->AddFrame(pSave);
		}
		else
		{
			m_pCubeMotion->AddSprite(m_pCUbeObj->GetVecPart()->front()->wstrStateKey, m_pCUbeObj);
			
			iFlag = pSave->FrameKey;
			m_pCUbeObj = Engine::CCubeObj::Create(((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pDevice);
			m_pCUbeObj->AddFrame(pSave);
		}
	}

	CloseHandle(hFile);


	map<wstring, vector<Engine::CCubeObj*>>* pSpriteMap = m_pCubeMotion->GetSpriteMap();

	map<wstring, vector<Engine::CCubeObj*>>::iterator iter = pSpriteMap->begin();
	map<wstring, vector<Engine::CCubeObj*>>::iterator iter_end = pSpriteMap->end();

	for ( ; iter != iter_end; ++iter)
	{
		for (int i = 0; i < m_StateListCtrl.GetCount(); ++i)
		{
			if (m_StateListCtrl.FindString(i, iter->first.c_str()) != -1)
			{		
				UpdateData(FALSE);
				break;;
			}
		}
		m_StateListCtrl.AddString(iter->first.c_str());
	}

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	UpdateData(FALSE);
}

void CAnimation::OnFrameList()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.


	if (m_StateListCtrl.GetCurSel() < 0)
		return;

	UpdateData(TRUE);

	map<wstring, Engine::CResources*>* mapChar = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_mapChar;
	map<wstring, vector<Engine::CCubeObj*>>* pSpriteMap = m_pCubeMotion->GetSpriteMap();

	CString strTemp;
	m_StateListCtrl.GetText(m_StateListCtrl.GetCurSel(), strTemp);
	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();

	map<wstring, vector<Engine::CCubeObj*>>::iterator Spriteiter = pSpriteMap->find(wstrState);
	Engine::CResources* pCubeObj = Spriteiter->second[m_FrameListCtrl.GetCurSel()];

	vector<Engine::SAVEFRAME*>* pVecParts = ((Engine::CCubeObj*)pCubeObj)->GetVecPart();

	for (size_t i = 0; i < pVecParts->size(); ++i)
	{
		map<wstring, Engine::CResources*>::iterator iter = mapChar->find((*pVecParts)[i]->wstrPartsKey);
		((Engine::CVIBuffer*)iter->second)->SetVtxInfo(&(*pVecParts)[i]->VtxInfo);
		((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(&(*pVecParts)[i]->VtxInfo);
	}
	
	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	UpdateData(FALSE);
}

void CAnimation::OnTimer(UINT nIDEvent)
{
	switch(nIDEvent)
	{
	case 1394:
		if (m_bPlay)
		{
			++m_dwFrame;

			if (m_dwFrame >= m_dwMaxFrame)
			{
				m_dwFrame = 0;
				m_FrameListCtrl.SetCurSel(0);
			}
			m_FrameListCtrl.SetCurSel(m_dwFrame);
			PlayAnimation();
		}

		break;
	}
}

void CAnimation::PlayAnimation( void )
{
	UpdateData(TRUE);

	map<wstring, Engine::CResources*>* mapChar = &((CObjBack*)((CMainFrame*)AfxGetMainWnd())->m_pMainView->m_pBackground[2])->m_mapChar;
	map<wstring, vector<Engine::CCubeObj*>>* pSpriteMap = m_pCubeMotion->GetSpriteMap();

	CString strTemp;
	m_StateListCtrl.GetText(m_StateListCtrl.GetCurSel(), strTemp);
	wstring wstrState = (LPWSTR)strTemp.operator LPCWSTR();

	map<wstring, vector<Engine::CCubeObj*>>::iterator Spriteiter = pSpriteMap->find(wstrState);
	Engine::CResources* pCubeObj = Spriteiter->second[m_FrameListCtrl.GetCurSel()];

	vector<Engine::SAVEFRAME*>* pVecParts = ((Engine::CCubeObj*)pCubeObj)->GetVecPart();

	for (size_t i = 0; i < pVecParts->size(); ++i)
	{
		map<wstring, Engine::CResources*>::iterator iter = mapChar->find((*pVecParts)[i]->wstrPartsKey);
		((Engine::CVIBuffer*)iter->second)->SetVtxInfo(&(*pVecParts)[i]->VtxInfo);
		((Engine::CVIBuffer*)iter->second)->SetOriginVtxInfo(&(*pVecParts)[i]->VtxInfo);
	}

	((CMainFrame*)AfxGetMainWnd())->m_pMainView->Invalidate(FALSE);
	UpdateData(FALSE);
}
