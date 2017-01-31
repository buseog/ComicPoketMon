#include "stdafx.h"
#include "Center.h"

#include "Include.h"
#include "SceneSelector.h"
#include "Export_Function.h"

#include "Player.h"
#include "Layer.h"
#include "Terrain.h"
#include "Pipeline.h"
#include "Component.h"
#include "StaticCamera.h"
#include "InsideCamera.h"
#include "Transform.h"
#include "CollisionMgr.h"
#include "Inven.h"
#include "SkyBox.h"
#include "Item.h"
#include "HpBar.h"
#include "MpBar.h"
#include "Gauge.h"
#include "Poketmon.h"
#include "CubeMotion.h"
#include "CubeObj.h"
#include "CubeTex.h"
#include "Npc.h"
#include "Snow.h"
#include "Centerdesk.h"
#include "BasicCamera.h"

CCenter::CCenter(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pSound(CSoundMgr::GetInstance())
, m_pManagement(Engine::Get_Management())
, m_pPlayer(NULL)
{

}

CCenter::~CCenter(void)
{
	Release();
}

HRESULT CCenter::InitScene(void)
{
	// Action
	FAILED_CHECK_MSG(Add_GameLogic_Layer(), L"GameLogic 레이어 초기화 실패");
	FAILED_CHECK_MSG(Add_UI_Layer(), L"UI 레이어 초기화 실패");

	return S_OK;
}

void CCenter::Update(void)
{
	Engine::CScene::Update();
	m_pPlayer->Update();
	m_pInven->Update();

	if(GetAsyncKeyState('4')  & 0x8000)
	{
		CBasicCamera::m_eCamType = CAM_STATIC;

		((CPlayer*)m_pPlayer)->SetPos(D3DXVECTOR3(230.f, 1.f, 15.f));
		m_pManagement->SceneChange(CSceneSelector(SC_STAGE), SC_STAGE);

		return;
	}
}

void CCenter::Render(void)
{
	Engine::CScene::Render();
	m_pPlayer->Render();
	m_pInven->Render();
}

CCenter* CCenter::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CCenter*		pCenter = new CCenter(pDevice);

	if (FAILED(pCenter->InitScene()))
		Engine::Safe_Delete(pCenter);

	return pCenter;
}

HRESULT CCenter::Add_Environment_Layer( void )
{
	return S_OK;
}

HRESULT CCenter::Add_GameLogic_Layer( void )
{
	Engine::CLayer*					pLayer = Engine::CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject* pPlayer = m_pManagement->GetScene(SC_STAGE)->GetLayer(1)->GetComponentList(L"Player")->back();
	Engine::CGameObject* pInven = m_pManagement->GetScene(SC_STAGE)->GetLayer(1)->GetComponentList(L"Inven")->back();

	Engine::CGameObject*			pGameObject = NULL;
	Engine::CGameObject*			pTemp = NULL;

	// 인벤 추가
	m_pInven = pInven;

	// 플레이어 추가
	m_pPlayer = pPlayer;
	((CPlayer*)m_pPlayer)->SetPos(D3DXVECTOR3(15.f, 0.f, 5.f));
	((CPlayer*)m_pPlayer)->SetLayer(pLayer);
	((CPlayer*)m_pPlayer)->SetStage(SC_CENTER);
	((CPlayer*)m_pPlayer)->SetInven(m_pInven);

	((CInven*)m_pInven)->SetPlayer(m_pPlayer);

	// 지형 추가
	pGameObject = CTerrain::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Terrain", pGameObject);

	// 스카이박스 추가
	pGameObject = CSkyBox::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"SkyBox", pGameObject);

	//갑옥 추가
	pGameObject = CCenterdesk::Create(m_pDevice, 0);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Desk", pGameObject);
	((CCenterdesk*)pGameObject)->SetPlayer(m_pPlayer);
	((CCenterdesk*)pGameObject)->SetLayer(pLayer);

	//문 추가
	pGameObject = CCenterdesk::Create(m_pDevice, 1);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Door", pGameObject);
	((CCenterdesk*)pGameObject)->SetPlayer(m_pPlayer);
	//((CCenterdesk*)pGameObject)->SetLayer(pLayer);


	
	m_mapLayer.insert(MAPLAYER::value_type(LAYER_GAMELOGIC, pLayer));
	return S_OK;

}

HRESULT CCenter::Add_UI_Layer( void )
{
	Engine::CLayer*					pLayer = Engine::CLayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	// PlayerInfo
	MAPLAYER::iterator	iter = m_mapLayer.find(LAYER_GAMELOGIC);

	if(iter == m_mapLayer.end())
		return E_FAIL;

	const Engine::CComponent*		pTransform = m_pPlayer->GetComponent(L"Transform");
	NULL_CHECK_RETURN(pTransform, E_FAIL);


	// Inside Camera
	Engine::CGameObject*			pGameObject = NULL;
	pGameObject = CInsideCamera::Create(m_pDevice, dynamic_cast<const Engine::CTransform*>(pTransform));
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"InsideCamera", pGameObject);

	m_mapLayer.insert(MAPLAYER::value_type(LAYER_UI, pLayer));

	return S_OK;
}

void CCenter::Release( void )
{

}

