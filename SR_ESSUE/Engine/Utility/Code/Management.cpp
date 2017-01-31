#include "Management.h"
#include "Renderer.h"
#include "Scene.h"

int Engine::CManagement::m_iScene = 0;

IMPLEMENT_SINGLETON(Engine::CManagement)

Engine::CManagement::CManagement(void)
: m_pDevice(NULL)
, m_pRenderer(NULL)
, m_pScene(NULL)
{
	for(int i = 0; i < Engine::CManagement::SC_END; ++i)
		m_pSceneTemp[i] = NULL;
}

Engine::CManagement::~CManagement(void)
{
	Release();
}


void Engine::CManagement::Release( void )
{
	Engine::Safe_Delete(m_pRenderer);

	for(int i = 0; i < Engine::CManagement::SC_END; ++i)
	{
		if(m_pSceneTemp[i] != NULL)
			Engine::Safe_Delete(m_pSceneTemp[i]);
	}
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
	if (m_pRenderer != NULL && m_iScene != 3)
		m_pRenderer->Render(fTime);
}

const Engine::VTXTEX* Engine::CManagement::GetTerrainVertex(const WORD& LayerID, 
															const wstring& wstrObjKey)
{
	return m_pScene->GetTerrainVertex(LayerID, wstrObjKey);
}

Engine::CScene* Engine::CManagement::GetScene( int ID )
{
	return m_pSceneTemp[ID];
}
