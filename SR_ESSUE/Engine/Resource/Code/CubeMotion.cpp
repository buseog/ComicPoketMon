#include "CubeMotion.h"

Engine::CCubeMotion::CCubeMotion( LPDIRECT3DDEVICE9 pDevice )
: CResources(pDevice)
{

}

Engine::CCubeMotion::~CCubeMotion( void )
{
	Release();
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
		vector<CResources*>::iterator veciter = iter->second.begin();
		vector<CResources*>::iterator veciter_end = iter->second.end();

		for ( ; veciter != veciter_end; ++veciter)
		{
			Engine::Safe_Delete(*veciter);
		}
		iter->second.clear();
	}
	m_SpriteMap.clear();
	
}

void Engine::CCubeMotion::Update( void )
{

}

void Engine::CCubeMotion::AddSprite( const wstring& wstrName, CResources* pComponent )
{
	MAPVECTOR::iterator iter = m_SpriteMap.find(wstrName);

	if (iter == m_SpriteMap.end())
	{
		m_SpriteMap[wstrName] = vector<CResources*>();
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
