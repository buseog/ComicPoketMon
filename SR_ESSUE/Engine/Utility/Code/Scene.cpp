#include "Scene.h"
#include "Layer.h"

Engine::CScene::CScene( LPDIRECT3DDEVICE9 _pDeivce )
: m_pDevice(_pDeivce)
{

}

Engine::CScene::~CScene( void )
{
	Release();
}

void Engine::CScene::Release( void )
{
	for_each(m_mapLayer.begin(), m_mapLayer.end(), CDeleteMap());
	m_mapLayer.clear();
}

HRESULT Engine::CScene::InitScene( void )
{
	return S_OK;
}

void Engine::CScene::Update( void )
{
	MAPLAYER::iterator		iter = m_mapLayer.begin();
	MAPLAYER::iterator		iter_end = m_mapLayer.end();

	for(; iter != iter_end; ++iter)
	{
		iter->second->Update();
	}
}

void Engine::CScene::Render( void )
{
	MAPLAYER::iterator		iter = m_mapLayer.begin();
	MAPLAYER::iterator		iter_end = m_mapLayer.end();

	for(; iter != iter_end; ++iter)
	{
		iter->second->Render();
	}
}

const Engine::VTXTEX* Engine::CScene::GetTerrainVertex(const WORD& LayerID, 
													   const wstring& wstrObjKey)
{
	MAPLAYER::iterator	iter = m_mapLayer.find(LayerID);

	if(iter == m_mapLayer.end())
		return NULL;

	return iter->second->GetTerrainVertex(wstrObjKey);
}

Engine::CLayer* Engine::CScene::GetLayer( int ikey )
{
	MAPLAYER::iterator	iter = m_mapLayer.find(ikey);

	return iter->second;
}

