#include "Renderer.h"
#include "Scene.h"

Engine::CRenderer::CRenderer( LPDIRECT3DDEVICE9 pDevice )
: m_pDevice(pDevice)
, m_pScene(NULL)
, m_pD3DXFont(NULL)
, m_fTime(0.f)
, m_wFramCnt(0)
{

}

Engine::CRenderer::~CRenderer( void )
{

}

Engine::CRenderer* Engine::CRenderer::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CRenderer*	pRenderer = new CRenderer(pDevice);

	if (FAILED(pRenderer->InitRenderer()))
		Engine::Safe_Delete(pRenderer);

	return pRenderer;
}

HRESULT Engine::CRenderer::InitRenderer( void )
{
	D3DXFONT_DESC			hFont;
	ZeroMemory(&hFont, sizeof(D3DXFONT_DESC));

	hFont.Width = 20;
	hFont.Height = 20;
	hFont.Weight = FW_NORMAL;
	lstrcpy(hFont.FaceName, L"±¼¸²");
	hFont.CharSet = HANGUL_CHARSET;

	FAILED_CHECK(D3DXCreateFontIndirect(m_pDevice, &hFont, &m_pD3DXFont));

	return S_OK;
}

void Engine::CRenderer::Render( float fTime  )
{
	RECT	rc = {50, 50, 200, 300 };

	++m_wFramCnt;
	m_fTime += fTime;

	if(1.f < m_fTime)
	{
		wsprintf(m_szFPS, L"FPS : %d", m_wFramCnt);
		m_fTime = 0.f;
		m_wFramCnt = 0;
	}	

	m_pDevice->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	
	m_pDevice->BeginScene();

	m_pD3DXFont->DrawText(NULL, m_szFPS, lstrlen(m_szFPS), &rc, DT_NOCLIP, D3DCOLOR_ARGB(255, 0, 255, 0));

	if(m_pScene != NULL)
		m_pScene->Render();

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void Engine::CRenderer::SetScene( CScene* _pScene )
{
	m_pScene = _pScene;
}