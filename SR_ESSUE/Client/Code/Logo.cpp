#include "stdafx.h"
#include "Logo.h"
#include "Layer.h"

#include "Include.h"
#include "SceneSelector.h"
#include "Export_Function.h"

#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

unsigned int __stdcall CLogo::ImgLoadThreadFunc(void* pArg)
{
	CLogo*		pLogo = (CLogo*)pArg;

	EnterCriticalSection(&pLogo->GetCrt());

	HRESULT hr = NULL;

	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Player");

	FAILED_CHECK_MSG(hr, L"Buffer Player Create Failed");

	// Player Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture Player", 
		L"../bin/Resources/Texture/Player%d.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Player Create Failed");


	// Terrain Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::TERRAIN_TEX, 
		L"Buffer Terrain", VTXCNTX, VTXCNTZ, VTXITV);
	FAILED_CHECK(hr);

	// Terrain Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture Terrain", 
		L"../bin/Resources/Texture/Terrain/Terrain_grass%d.png", 
		2);
	FAILED_CHECK_MSG(hr, L"Texture Terrain Create Failed");

	// SkyBox Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::CVIBuffer::TERRAIN_TEX, 
		L"Buffer SkyBox", 11, 11, VTXITV);
	FAILED_CHECK(hr);

	// SkyBox Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_NORMAL, 
		L"Texture SkyBox", 
		L"../bin/Resources/Texture/SkyBox/Sky_Side%d.png", 
		2);
	FAILED_CHECK_MSG(hr, L"Texture Terrain Create Failed");

	// Cube Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_STATIC, 
		Engine::TEX_CUBE, 
		L"Cube0.dds", 
		L"../bin/Resources/Texture/Cube%d.dds", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture CubeTex Create Failed");

	// Inven Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_DYNAMIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Inven");

	FAILED_CHECK_MSG(hr, L"Buffer Inven Create Failed");

	// Inven Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_DYNAMIC, 
		Engine::TEX_NORMAL, 
		L"Texture Inven", 
		L"../bin/Resources/Texture/Ui/Inven.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Inven Create Failed");

	// Item Buffer
	hr = Engine::Get_ResourceMgr()->AddBuffer(pLogo->GetDevice(), 
		Engine::RESOURCE_DYNAMIC, 
		Engine::CVIBuffer::BUFFER_RCTEX, 
		L"Buffer Item");

	FAILED_CHECK_MSG(hr, L"Buffer Item Create Failed");

	// Item Texture
	hr = Engine::Get_ResourceMgr()->AddTexture(pLogo->GetDevice(), 
		Engine::RESOURCE_DYNAMIC, 
		Engine::TEX_NORMAL, 
		L"Texture Item", 
		L"../bin/Resources/Texture/Ui/Item%d.png", 
		1);
	FAILED_CHECK_MSG(hr, L"Texture Item Create Failed");

	LeaveCriticalSection(&pLogo->GetCrt());
	_endthreadex(0);

	return 0;
}

CRITICAL_SECTION CLogo::GetCrt(void)
{
	return m_Crt;
}

CLogo::CLogo(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pManagement(Engine::Get_Management())
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_fCount(0)
, m_fMaxCount(0)

{

}

CLogo::~CLogo(void)
{
	Release();
}

HRESULT CLogo::InitScene(void)
{
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"../Bin/Video/Opening.wmv");

	HRESULT hr = NULL;

	InitializeCriticalSection(&m_Crt);

	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ImgLoadThreadFunc, this, 0, NULL);

	MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
	MCIWndPlay(m_hVideo);

	return S_OK;
}

void CLogo::Update(void)
{
	if(GetAsyncKeyState(VK_RETURN))
	{
		WaitForSingleObject(m_hThread, INFINITE);
		CloseHandle(m_hThread);

		DeleteCriticalSection(&m_Crt);

		m_pManagement->SceneChange(CSceneSelector(SC_STAGE), SC_STAGE);
		return;
	}
}

void CLogo::Render(void)
{

}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CLogo*	pLogo = new CLogo(pDevice);

	if (FAILED(pLogo->InitScene()))
		Engine::Safe_Delete(pLogo);

	return pLogo;
}

HRESULT CLogo::Add_Environment_Layer(void)
{
	return S_OK;
}

HRESULT CLogo::Add_GameLogic_Layer(void)
{

	return S_OK;
}

LPDIRECT3DDEVICE9 CLogo::GetDevice( void )
{
	return m_pDevice;
}

void CLogo::Release( void )
{
	MCIWndClose(m_hVideo);
}
