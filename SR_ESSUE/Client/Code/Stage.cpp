#include "stdafx.h"
#include "Stage.h"

#include "Include.h"
#include "Export_Function.h"

#include "Player.h"
#include "Layer.h"
#include "Terrain.h"
#include "Pipeline.h"
#include "Component.h"
#include "StaticCamera.h"
#include "Transform.h"
#include "CollisionMgr.h"
#include "Inven.h"
#include "SkyBox.h"
#include "Item.h"

CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
{

}

CStage::~CStage(void)
{
	Release();
}

HRESULT CStage::InitScene(void)
{
	m_pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	HRESULT hr = NULL;


	// Collision

	hr = CCollisionMgr::GetInstance()->AddColObject(CCollisionMgr::COL_TERRAIN);
	FAILED_CHECK(hr);
	
	hr = CCollisionMgr::GetInstance()->AddColObject(CCollisionMgr::COL_MOUSE);
	FAILED_CHECK(hr);

	// Action

	//hr = CCollisionMgr::GetInstance()->AddColObject(CCollisionMgr::COL_TERRAIN);
	//FAILED_CHECK_MSG(Add_Environment_Layer(), L"Environment 레이어 초기화 실패");
	FAILED_CHECK_MSG(Add_GameLogic_Layer(), L"GameLogic 레이어 초기화 실패");
	FAILED_CHECK_MSG(Add_UI_Layer(), L"UI 레이어 초기화 실패");

	return S_OK;
}

void CStage::Update(void)
{
	Engine::CScene::Update();
}

void CStage::Render(void)
{
	Engine::CScene::Render();
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CStage*		pStage = new CStage(pDevice);

	if (FAILED(pStage->InitScene()))
		Engine::Safe_Delete(pStage);

	return pStage;
}

HRESULT CStage::Add_Environment_Layer( void )
{
	return S_OK;
}

HRESULT CStage::Add_GameLogic_Layer( void )
{
	Engine::CLayer*					pLayer = Engine::CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*			pGameObject = NULL;
	pGameObject = CPlayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Player", pGameObject);

	pGameObject = CTerrain::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Terrain", pGameObject);

	pGameObject = CInven::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Inven", pGameObject);


	pGameObject = CSkyBox::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"SkyBox", pGameObject);


	pGameObject = CItem::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Item", pGameObject);


	m_mapLayer.insert(MAPLAYER::value_type(LAYER_GAMELOGIC, pLayer));
	return S_OK;

}

HRESULT CStage::Add_UI_Layer( void )
{

	Engine::CLayer*					pLayer = Engine::CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	// PlayerInfo
	MAPLAYER::iterator	iter = m_mapLayer.find(LAYER_GAMELOGIC);

	if(iter == m_mapLayer.end())
		return E_FAIL;

	const Engine::CComponent*		pTransform = iter->second->GetComponent(L"Player", L"Transform");
	NULL_CHECK_RETURN(pTransform, E_FAIL);


	// StaticCamera
	Engine::CGameObject*			pGameObject = NULL;
	pGameObject = CStaticCamera::Create(m_pDevice, dynamic_cast<const Engine::CTransform*>(pTransform));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"StaticCamera", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_UI, pLayer));

	return S_OK;
}

void CStage::Release( void )
{
	CCollisionMgr::GetInstance()->DestroyInstance();
	Engine::CInfoSubject::GetInstance()->DestroyInstance();
}

