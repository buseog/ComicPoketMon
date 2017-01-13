#include "CubeObj.h"

Engine::CCubeObj::CCubeObj( LPDIRECT3DDEVICE9 pDevice )
: CResources(pDevice)
{
}

Engine::CCubeObj::~CCubeObj( void )
{
	Release();
}


void Engine::CCubeObj::Render( void )
{

}

void Engine::CCubeObj::Release( void )
{
	for (size_t i = 0 ; i < m_vecFrame.size() ; ++i)
	{
		Engine::Safe_Delete(m_vecFrame[i]);
	}
	m_vecFrame.clear();
}

void Engine::CCubeObj::Update( void )
{

}

Engine::CResources* Engine::CCubeObj::CloneResource( void )
{
	++(*m_pwRefCnt);

	return new CCubeObj(*this);
}

void Engine::CCubeObj::AddSprite(const wstring& wstrName, SAVEFRAME* pSave )
{
	for (size_t i = 0 ; i < m_vecFrame.size() ; ++i)
	{
		if (m_vecFrame[i]->wstrPartsKey == wstrName)
			return;
	}

	m_vecFrame.push_back(pSave);
}

void Engine::CCubeObj::RemoveSprite( const wstring& wstrName )
{
	for (size_t i = 0 ; i < m_vecFrame.size() ; ++i)
	{
		if (m_vecFrame[i]->wstrPartsKey == wstrName)
			return;
	}
}

Engine::CCubeObj* Engine::CCubeObj::Create( LPDIRECT3DDEVICE9 pDevice )
{
	return new CCubeObj(pDevice);
}

Engine::CCubeObj::VECTORFRAME* Engine::CCubeObj::GetVecPart( void )
{
	return &m_vecFrame;
}
