#include "Management.h"
#include "Renderer.h"
#include "Scene.h"

IMPLEMENT_SINGLETON(Engine::CManagement)

Engine::CManagement::CManagement(void)
: m_pDevice(NULL)
, m_pRenderer(NULL)
, m_pScene(NULL)
, m_iScene(0)
{

}

Engine::CManagement::~CManagement(void)
{
	Release();
}

void Engine::CManagement::Release( void )
{
	Engine::Safe_Delete(m_pRenderer);
	Engine::Safe_Delete(m_pScene);
}

HRESULT Engine::CManagement::InitManagement( LPDIRECT3DDEVICE9 pDevice )
{
	m_pDevice = pDevice;

	m_pRenderer = CRenderer::Create(pDevice);
	NULL_CHECK_RETURN_MSG(m_pRenderer, E_FAIL, L"Renderer Create Failed");

	return S_OK;
}

void Engine::CManagement::Update( void )
{
	if (m_pScene != NULL)
		m_pScene->Update();
}

void Engine::CManagement::Render( float fTime )
{
	if (m_pRenderer != NULL && m_iScene != 0)
		m_pRenderer->Render(fTime);
}

const Engine::VTXTEX* Engine::CManagement::GetTerrainVertex(const WORD& LayerID, 
															const wstring& wstrObjKey)
{
	return m_pScene->GetTerrainVertex(LayerID, wstrObjKey);
}

  