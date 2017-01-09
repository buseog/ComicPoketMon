#include "Layer.h"
#include "GameObject.h"
#include "Component.h"

Engine::CLayer::CLayer(LPDIRECT3DDEVICE9 pDevice)
: m_pDevice(pDevice)
{

}

Engine::CLayer::~CLayer()
{
	Release();
}

void Engine::CLayer::Update(void)
{
	MAPOBJLIST::iterator		mapiter		= m_mapObjList.begin();
	MAPOBJLIST::iterator		mapiter_end = m_mapObjList.end();

	for( ; mapiter != mapiter_end; ++mapiter)
	{
		OBJLIST::iterator		iterList	 = mapiter->second.begin();
		OBJLIST::iterator		iterList_end = mapiter->second.end();

		for(; iterList != iterList_end; ++iterList)
		{
			(*iterList)->Update();
		}
	}
}

void Engine::CLayer::Render(void)
{
	MAPOBJLIST::iterator		mapiter		= m_mapObjList.begin();
	MAPOBJLIST::iterator		mapiter_end = m_mapObjList.end();

	for( ; mapiter != mapiter_end; ++mapiter)
	{
		OBJLIST::iterator		iterList	 = mapiter->second.begin();
		OBJLIST::iterator		iterList_end = mapiter->second.end();

		for(; iterList != iterList_end; ++iterList)
		{
			(*iterList)->Render();
		}
	}
}

void Engine::CLayer::Release(void)
{
	MAPOBJLIST::iterator		mapiter		= m_mapObjList.begin();
	MAPOBJLIST::iterator		mapiter_end = m_mapObjList.end();

	for( ; mapiter != mapiter_end; ++mapiter)
	{
		OBJLIST::iterator		iterList	 = mapiter->second.begin();
		OBJLIST::iterator		iterList_end = mapiter->second.end();

		for(; iterList != iterList_end; ++iterList)
		{
			Engine::Safe_Delete(*iterList);
		}
		mapiter->second.clear();
	}
	m_mapObjList.clear();
}

Engine::CLayer* Engine::CLayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	return new CLayer(pDevice);
}

HRESULT Engine::CLayer::AddObject(const wstring& wstrObjKey, CGameObject* pGameObject)
{
	if(pGameObject)
	{
		MAPOBJLIST::iterator	iter = m_mapObjList.find(wstrObjKey);

		if(iter == m_mapObjList.end())
		{
			m_mapObjList[wstrObjKey] = OBJLIST();
		}

		m_mapObjList[wstrObjKey].push_back(pGameObject);
	}

	return S_OK;
}

const Engine::CComponent* Engine::CLayer::GetComponent(const wstring& wstrObjKey, 
													   const wstring& wstrComponentKey)
{
	MAPOBJLIST::iterator	mapiter = m_mapObjList.find(wstrObjKey);

	if(mapiter == m_mapObjList.end())
		return NULL;

	OBJLIST::iterator		Listiter = mapiter->second.begin();
	OBJLIST::iterator		Listiter_end = mapiter->second.end();

	for(; Listiter != Listiter_end; ++Listiter)
	{
		const CComponent*	pComponent = (*Listiter)->GetComponent(wstrComponentKey);

		if(pComponent != NULL)
			return pComponent;
	}

	return NULL;
}
