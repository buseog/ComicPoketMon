#include "GameObject.h"
#include "Component.h"

Engine::CGameObject::CGameObject(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
{

}

Engine::CGameObject::~CGameObject(void)
{
	Release();
}

HRESULT Engine::CGameObject::Initialize(void)
{
	return S_OK;
}

void Engine::CGameObject::Update(void)
{
	MAPCOMPONENT::iterator		iter = m_mapComponent.begin();
	MAPCOMPONENT::iterator		iter_end = m_mapComponent.end();

	for(; iter != iter_end; ++iter)
	{
		iter->second->Update();
	}
}

void Engine::CGameObject::Render(void)
{

}

void Engine::CGameObject::Release(void)
{
	for_each(m_mapComponent.begin(), m_mapComponent.end(), CDeleteMap());
	m_mapComponent.clear();
}

const Engine::CComponent* Engine::CGameObject::GetComponent(const wstring& wstrComponentKey)
{
	MAPCOMPONENT::iterator		iter = m_mapComponent.find(wstrComponentKey);

	if(iter == m_mapComponent.end())
		return NULL;

	return iter->second;
}

