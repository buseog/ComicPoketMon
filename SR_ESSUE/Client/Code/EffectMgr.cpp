#include "stdafx.h"
#include "EffectMgr.h"
#include "Emanation.h"
#include "Blaze.h"
#include "WaterCannon.h"
#include "Layer.h"
#include "Transform.h"

CEffectMgr*	CEffectMgr::m_pInstance = NULL;

CEffectMgr*	CEffectMgr::GetInstance( void )
{												
	return m_pInstance;								
}	

void CEffectMgr::DestroyInstance( void )
{		
	if(NULL != m_pInstance)	
	{						
		delete m_pInstance;
		m_pInstance = NULL;	
	}
}

void CEffectMgr::CreateEffectMgr(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer)
{
	m_pInstance = new CEffectMgr(pDevice, pLayer);
}

CEffectMgr::CEffectMgr(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer)
: m_pDevice(pDevice)
, m_pLayer(pLayer)
{

}

CEffectMgr::~CEffectMgr(void)
{
	Release();
}

void CEffectMgr::AddEffect(Engine::EFFECTTYPE eEffectType, Engine::EMANATIONID eEmanationID, Engine::CTransform* pTransform, D3DXVECTOR3 vDir)
{
	MAPEMANATIONLST::iterator iter = m_mapEffectList.find(eEffectType);

	if(iter == m_mapEffectList.end())
		m_mapEffectList[eEffectType] = EMANATIONLIST();

	switch(eEmanationID)
	{
	case Engine::EMID_FLAME:
		m_mapEffectList[eEffectType].push_back(CBlaze::Create( m_pDevice, m_pLayer, pTransform, vDir));
		break;

	case Engine::EMID_WATER:
		m_mapEffectList[eEffectType].push_back(CWaterCannon::Create(m_pDevice, m_pLayer, pTransform, vDir));
		break;
	}
}

std::list<CEmanation*> CEffectMgr::GetEffectList(Engine::EFFECTTYPE eEffectType)
{
	MAPEMANATIONLST::iterator iter = m_mapEffectList.find(eEffectType);

	return iter->second;
}

void CEffectMgr::Update(void)
{
	MAPEMANATIONLST::iterator iter = m_mapEffectList.begin();
	MAPEMANATIONLST::iterator iter_End = m_mapEffectList.end();

	for(iter; iter != iter_End; ++iter)
	{
		EMANATIONLIST::iterator Insideiter = iter->second.begin();
		EMANATIONLIST::iterator Insideiter_End = iter->second.end();

		for(Insideiter; Insideiter != Insideiter_End; )
		{
			(*Insideiter)->Update();

			if(!((*Insideiter)->m_bContents))
			{
				Engine::Safe_Delete(*Insideiter);
				Insideiter = iter->second.erase(Insideiter);
			}
			else
			 ++Insideiter;

		}
	}
}

void CEffectMgr::Render(void)
{
	MAPEMANATIONLST::iterator iter = m_mapEffectList.begin();
	MAPEMANATIONLST::iterator iter_End = m_mapEffectList.end();

	for(iter; iter != iter_End; ++iter)
	{
		EMANATIONLIST::iterator Insideiter = iter->second.begin();
		EMANATIONLIST::iterator Insideiter_End = iter->second.end();

		for(Insideiter; Insideiter != Insideiter_End; ++Insideiter)
		{
			(*Insideiter)->Render();
		}
	}
}

void CEffectMgr::Release(void)
{
	MAPEMANATIONLST::iterator iter = m_mapEffectList.begin();
	MAPEMANATIONLST::iterator iter_End = m_mapEffectList.end();

	for(iter; iter != iter_End; ++iter)
	{
		EMANATIONLIST::iterator Insideiter = iter->second.begin();
		EMANATIONLIST::iterator Insideiter_End = iter->second.end();

		for(Insideiter; Insideiter != Insideiter_End; ++Insideiter)
		{
			Engine::Safe_Delete(*Insideiter);
		}
		
		//iter->second.clear();
	}
}