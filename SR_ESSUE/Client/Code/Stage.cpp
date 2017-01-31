#include "stdafx.h"
#include "Stage.h"

#include "Include.h"
#include "SceneSelector.h"
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
#include "HpBar.h"
#include "MpBar.h"
#include "Gauge.h"
#include "Poketmon.h"
#include "CubeMotion.h"
#include "CubeObj.h"
#include "CubeTex.h"
#include "Npc.h"
#include "Snow.h"
#include "Wall.h"
#include "BoundBox.h"
#include "Boss.h"
#include "PoketballUI.h"
#include "FireEffect.h"
#include "EffectMgr.h"
#include "Objects.h"
#include "WaterEffect.h"
#include "ElectricEffect.h"

CStage::CStage(LPDIRECT3DDEVICE9 pDevice)
: Engine::CScene(pDevice)
, m_pSound(CSoundMgr::GetInstance())
, m_pManagement(Engine::Get_Management())
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

	hr = CCollisionMgr::GetInstance()->AddColObject(CCollisionMgr::COL_BOUND);
	FAILED_CHECK(hr);

	m_pSound->Initialize();
	m_pSound->PlayBGM(L"Bgm.mp3");
	

	// Resourece 추가

	// Action
	//hr = CCollisionMgr::GetInstance()->AddColObject(CCollisionMgr::COL_TERRAIN);
	//FAILED_CHECK_MSG(Add_Environment_Layer(), L"Environment 레이어 초기화 실패");
	FAILED_CHECK_MSG(Add_GameLogic_Layer(), L"GameLogic 레이어 초기화 실패");
	FAILED_CHECK_MSG(Add_UI_Layer(), L"UI 레이어 초기화 실패");

	D3DXVECTOR3 vPos = D3DXVECTOR3(128.f, 50.f, 128.f);
	Engine::CBoundBox* pBox = Engine::CBoundBox::Create(&vPos, &D3DXVECTOR3(1.f, 1.f, 1.f));
	pBox->vSize = D3DXVECTOR3(150.f, 80.f, 150.f);
	pBox->Initialize(&vPos, &D3DXVECTOR3(1.f, 1.f, 1.f));
	
	
	m_pSnow = CSnow::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Snow2.png", pBox, 500);

	return S_OK;
}

void CStage::Update(void)
{
	Engine::CScene::Update();

	if(GetAsyncKeyState('5') & 0x8000)
	{
		Engine::CManagement::m_iScene = SC_CENTER;
		m_pManagement->SceneChange(CSceneSelector(SC_CENTER), SC_CENTER);

		return;
	}

	CEffectMgr::GetInstance()->Update();

	m_pSnow->Update();
}

void CStage::Render(void)
{
	Engine::CScene::Render();

	CEffectMgr::GetInstance()->Render();

	m_pSnow->Render();
}

void CStage::DataLoad(Engine::CLayer* pLayer)
{
	DWORD	dwByte = 0;

	HANDLE	hFile  = NULL;

	hFile = CreateFile(L"../bin/Data/Objects.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	vector<Engine::OBJINFO>	vecObj;

	Engine::OBJINFO tObj;
	//Engine::VTXTEX*		pVTXCOL = new Engine::VTXTEX[257 * 257];

	while(true)
	{
		ReadFile(hFile, &tObj, sizeof(Engine::OBJINFO), &dwByte, NULL);

		vecObj.push_back(tObj);

		if(dwByte == 0)
		{	
			break;
		}
	}

	vector<Engine::OBJINFO>::iterator iter = vecObj.begin();
	vector<Engine::OBJINFO>::iterator iter_end = vecObj.end();

	for(iter; iter != iter_end; ++iter)
	{
		pLayer->AddObject(L"Objects", CObjects::Create(m_pDevice, (*iter)));
	}

	CloseHandle(hFile);
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

	CEffectMgr::CreateEffectMgr(m_pDevice, pLayer);
	
	Engine::CGameObject*			pGameObject = NULL;
	Engine::CGameObject*			pTemp = NULL;

	// 인벤 추가
	pGameObject = pTemp = CInven::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Inven", pGameObject);

	// 플레이어 추가
	pGameObject = CPlayer::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Player", pGameObject);
	((CPlayer*)pGameObject)->SetLayer(pLayer);
	((CPlayer*)pGameObject)->SetStage(SC_STAGE);

	//플레이어에 인벤추가
	((CPlayer*)pGameObject)->SetInven(pLayer->GetComponentList(L"Inven")->back());

	// 포켓몬 추가
	for(int i = 0; i < 5; ++i)
	{
		pGameObject = CPoketmon::Create(m_pDevice, L"Ggobugi", pLayer);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);

		((CPoketmon*)pGameObject)->SetPos(D3DXVECTOR3(rand() % 157 + 100.f, 0.f, rand() % 205 + 50.f));

		pLayer->AddObject(L"Poketmon", pGameObject);
	}

	// 포켓몬 추가
	for(int i = 0; i < 5; ++i)
	{
		pGameObject = CPoketmon::Create(m_pDevice, L"Pairi", pLayer);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);

		((CPoketmon*)pGameObject)->SetPos(D3DXVECTOR3(rand() % 157 + 100.f, 0.f, rand() % 205 + 50.f));

		pLayer->AddObject(L"Poketmon", pGameObject);
	}

	// 포켓몬 추가
	for(int i = 0; i < 5; ++i)
	{
		pGameObject = CPoketmon::Create(m_pDevice, L"Picachu", pLayer);
		NULL_CHECK_RETURN(pGameObject, E_FAIL);

		((CPoketmon*)pGameObject)->SetPos(D3DXVECTOR3(rand() % 157 + 100.f, 0.f, rand() % 205 + 50.f));

		pLayer->AddObject(L"Poketmon", pGameObject);
	}

	// 보스 추가
	pGameObject = CBoss::Create(m_pDevice, pLayer);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	float fX = float(rand() % (VTXCNTX));
	float fZ = float(rand() % (VTXCNTZ));
	((CMultiGameObject*)pGameObject)->SetPos(D3DXVECTOR3(fX, 0.f, fZ));
	pLayer->AddObject(L"Poketmon", pGameObject);
	
	// 지형 추가
	pGameObject = CTerrain::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Terrain", pGameObject);

	// HpBar 추가
	pGameObject = CHpBar::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"HpBar", pGameObject);

	// MpBar 추가
	pGameObject = CMpBar::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"MpBar", pGameObject);

	// Hp Gauge 추가
	pGameObject = CGauge::Create(m_pDevice, L"HP Gauge");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"HpGauge", pGameObject);

	// Mp Gauge 추가
	pGameObject = CGauge::Create(m_pDevice, L"MP Gauge");
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"MpGauge", pGameObject);

	// 스카이박스 추가
	pGameObject = CSkyBox::Create(m_pDevice);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"SkyBox", pGameObject);

	// 벽 추가
	pGameObject = CWall::Create(m_pDevice, SC_STAGE);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	pLayer->AddObject(L"Wall", pGameObject);
	((CWall*)pGameObject)->SetLayer(pLayer);

	////인벤에 플레이어 추가
	((CInven*)pTemp)->SetPlayer(pLayer->GetComponentList(L"Player")->back());

	// 오브젝트 생성 부분
	DataLoad(pLayer);


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
	CEffectMgr::GetInstance()->DestroyInstance();
	Engine::Safe_Delete(m_pSnow);
}

