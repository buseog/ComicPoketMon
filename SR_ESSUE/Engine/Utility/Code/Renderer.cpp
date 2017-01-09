#include "Renderer.h"
#include "Scene.h"

Engine::CRenderer::CRenderer( LPDIRECT3DDEVICE9 pDevice )
:m_pDevice(pDevice)
,m_pScene(NULL)
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
	return S_OK;
}

void Engine::CRenderer::Render( void )
{
	m_pDevice->Clear(0, NULL, 
		D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		D3DCOLOR_ARGB(255, 0, 0, 255), 1.f, 0);
	m_pDevice->BeginScene();

	if(m_pScene != NULL)
		m_pScene->Render();

	m_pDevice->EndScene();
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

void Engine::CRenderer::SetScene( CScene* _pScene )
{
	m_pScene = _pScene;
}