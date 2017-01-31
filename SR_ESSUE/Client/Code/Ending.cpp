#include "StdAfx.h"
#include "Ending.h"

#include "Include.h"
#include <Vfw.h>
#pragma comment(lib, "Vfw32.lib")

CEnding::CEnding( LPDIRECT3DDEVICE9 pDevice )
: Engine::CScene(pDevice)
{

}

CEnding::~CEnding( void )
{
	Release();
}

HRESULT CEnding::InitScene( void )
{
	m_hVideo = MCIWndCreate(g_hWnd, NULL, MCIWNDF_NOPLAYBAR | WS_VISIBLE | WS_CHILD,
		L"../Bin/Video/Ending.wmv");

		MoveWindow(m_hVideo, 0, 0, WINCX, WINCY, NULL);
		MCIWndPlay(m_hVideo);

	return S_OK;
}

CEnding* CEnding::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CEnding* pEnding = new CEnding(pDevice);

	if (FAILED(pEnding->InitScene()))
		Engine::Safe_Delete(pEnding);

	return pEnding;
}

void CEnding::Release( void )
{
	MCIWndClose(m_hVideo);

}

void CEnding::Update( void )
{
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		DestroyWindow(g_hWnd);
	}
}

