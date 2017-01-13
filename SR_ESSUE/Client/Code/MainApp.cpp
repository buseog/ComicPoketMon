#include "stdafx.h"
#include "MainApp.h"
#include "GraphicDev.h"
#include "Export_Function.h"
#include "SceneSelector.h"

CMainApp::CMainApp()
: m_pGraphicDev(Engine::Get_GraphicDev())
, m_pManagement(Engine::Get_Management())
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pDevice(NULL)
{

}

CMainApp::~CMainApp()
{
	Release();
}

HRESULT CMainApp::Initialize( void )
{
	HRESULT hr = NULL;

	hr = Engine::CGraphicDev::GetInstance()->InitGraphicDev
		(Engine::CGraphicDev::MODE_WIN, g_hWnd, WINCX, WINCY);

	FAILED_CHECK_MSG(hr, L"그래픽 디바이스 초기화 실패");

	m_pDevice = m_pGraphicDev->GetDevice();
	FAILED_CHECK_RETURN(m_pDevice, E_FAIL);

	hr = m_pManagement->InitManagement(m_pDevice);
	FAILED_CHECK_MSG(hr, L"managment Init Failed");

	hr = m_pManagement->SceneChange(CSceneSelector(SC_LOGO));
	FAILED_CHECK_MSG(hr, L"CSceneSelector Failed");

	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	return S_OK;
}

void CMainApp::Release( void )
{
	Engine::Safe_Single_Destory(m_pTimeMgr);
	Engine::Safe_Single_Destory(m_pManagement);
	Engine::CResourceMgr::GetInstance()->DestroyInstance();
	Engine::Safe_Single_Destory(m_pGraphicDev);
}


void CMainApp::Update( void )
{
	m_pManagement->Update();
}

void CMainApp::Render( void )
{
	m_pManagement->Render();
}

CMainApp* CMainApp::Create( void )
{
	CMainApp*	pMainApp = new CMainApp;

	if (FAILED(pMainApp->Initialize()))
	{
		delete pMainApp;
		pMainApp = NULL;
	}

	return pMainApp;
}
