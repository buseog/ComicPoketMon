#include "CubeMotion.h"
#include "CubeObj.h"

Engine::CCubeMotion::CCubeMotion( LPDIRECT3DDEVICE9 pDevice )
: CResources(pDevice)
{

}

Engine::CCubeMotion::~CCubeMotion( void )
{
	Release();
}

void Engine::CCubeMotion::Update( const wstring& wstrStateKey, D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	m_wstrKey = wstrStateKey;

	MAPVECTOR::iterator iter = m_SpriteMap.find(m_wstrKey);

	if (iter == m_SpriteMap.end())
		return;

	for (size_t i = 0; i < m_SpriteMap[m_wstrKey].size(); ++i)
	{
		m_SpriteMap[m_wstrKey][i]->Update(matWorld, matView, matProj);
	}
}

void Engine::CCubeMotion::Render( const DWORD& Frame )
{
	MAPVECTOR::iterator iter = m_SpriteMap.find(m_wstrKey);

	if (iter == m_SpriteMap.end())
		return;

	m_SpriteMap[m_wstrKey][Frame]->Render();
}

void Engine::CCubeMotion::Render( void )
{
	
}

void Engine::CCubeMotion::Release( void )
{
	MAPVECTOR::iterator iter = m_SpriteMap.begin();
	MAPVECTOR::iterator iter_end = m_SpriteMap.end();

	for ( ; iter != iter_end; ++iter)
	{
		vector<Engine::CCubeObj*>::iterator veciter = iter->second.begin();
		vector<Engine::CCubeObj*>::iterator veciter_end = iter->second.end();

		for ( ; veciter != veciter_end; ++veciter)
		{
			Engine::Safe_Delete(*veciter);
		}
		iter->second.clear();
	}
	m_SpriteMap.clear();

	Engine::CResources::Release();
	
}

void Engine::CCubeMotion::AddSprite( const wstring& wstrName, Engine::CCubeObj* pComponent )
{
	MAPVECTOR::iterator iter = m_SpriteMap.find(wstrName);

	if (iter == m_SpriteMap.end())
	{
		m_SpriteMap[wstrName] = vector<Engine::CCubeObj*>();
	}

	m_SpriteMap[wstrName].push_back(pComponent);
}

void Engine::CCubeMotion::RemoveSprite( const wstring& wstrName )
{

}
Engine::CResources* Engine::CCubeMotion::CloneResource( void )
{
	++(*m_pwRefCnt);

	return new CCubeMotion(*this);
}

Engine::CCubeMotion* Engine::CCubeMotion::Create( LPDIRECT3DDEVICE9 pDevice )
{
	return new CCubeMotion(pDevice);
}

Engine::CCubeMotion::MAPVECTOR* Engine::CCubeMotion::GetSpriteMap( void )
{
	return &m_SpriteMap;
}

int Engine::CCubeMotion::GetSpriteCount( const wstring& wstrKey )
{
	MAPVECTOR::iterator iter = m_SpriteMap.find(wstrKey);

	if (iter == m_SpriteMap.end())
		return NULL;

	return iter->second.size();
}
