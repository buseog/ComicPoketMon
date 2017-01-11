#include "CubeObj.h"
#include "Transform.h"


Engine::CCubeObj::~CCubeObj( void )
{

}

Engine::CCubeObj::CCubeObj( LPDIRECT3DDEVICE9 pDevice )
: CResources(pDevice)
{
	m_pInfo = Engine::CTransform::Create(D3DXVECTOR3(0.f, 0.f, 1.f ));
}


void Engine::CCubeObj::Render( void )
{

}

void Engine::CCubeObj::Release( void )
{
	delete m_pInfo;
}

void Engine::CCubeObj::Update( void )
{

}

Engine::CResources* Engine::CCubeObj::CloneResource( void )
{
	return NULL;
}

void Engine::CCubeObj::AddParts(const wstring& wstrName, CComponent* pComponent )
{
	MAPCOMPONENT::iterator iter = m_MapComponent.find(wstrName);

	if (iter != m_MapComponent.end())
		return;

	m_MapComponent.insert(MAPCOMPONENT::value_type(wstrName, pComponent));
}

void Engine::CCubeObj::RemoveParts( const wstring& wstrName )
{
	MAPCOMPONENT::iterator iter = m_MapComponent.find(wstrName);

	if (iter == m_MapComponent.end())
		return

	Engine::Safe_Delete(iter->second);
	m_MapComponent.erase(iter);
}

void Engine::CCubeObj::PikingPlane( void )
{
	//POINT	pt;
}

