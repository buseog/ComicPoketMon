#include "stdafx.h"
#include "Player.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"

#include "Transform.h"
#include "Pipeline.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "Stage.h"
#include "TerrainCol.h"
#include "MouseCol.h"
#include "CollisionMgr.h"
#include "CubeTex.h"
#include "Action.h"
#include "CubeMotion.h"
#include "CubeObj.h"
#include "Status.h"
#include "Sprite.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: CMultiGameObject(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pManagement(Engine::Get_Management())
, m_pCollisionMgr(CCollisionMgr::GetInstance())
, m_pCameraObserver(NULL)
, m_pTerrainVtx(NULL)
, m_pStat(NULL)
, m_pSprite(NULL)
, m_pResource(NULL)
, m_pTerrainCol(NULL)
, m_pMouseCol(NULL)
, m_fSpeed(0.f)
, m_bMove(false)


{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	//m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Player", m_pVertex);

	m_fSpeed = 40.f;

	Load();

	FAILED_CHECK(AddComponent());

	return S_OK;
}

void CPlayer::KeyInput(void)
{
	float fTime = m_pTimeMgr->GetTime();

	if(GetAsyncKeyState('W') & 0X8000)
	{
		m_pInfo->vPos += m_pInfo->vDir * m_fSpeed * fTime;
	}

	if(GetAsyncKeyState('S') & 0X8000)
	{
		m_pInfo->vPos -= m_pInfo->vDir * m_fSpeed * fTime;
	}

	if(GetAsyncKeyState('A') & 0X8000)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] -= D3DXToRadian(90.f) * fTime;
	}

	if(GetAsyncKeyState('D') & 0X8000)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] += D3DXToRadian(90.f) * fTime;
	}

	if(GetAsyncKeyState(VK_LBUTTON)  & 0x8000)
	{
		/*m_bMove = true;
		m_pMouseCol->PickTerrain(&m_vDestPos, m_pTerrainVtx);*/

		D3DXVECTOR3	vTemp;
		//m_pMouseCol->PickObject(&vTemp, m_pVertex, &m_pInfo->matWorld);
	}
		
}

void CPlayer::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayer*		pPlayer = new CPlayer(pDevice);

	if(FAILED(pPlayer->Initialize()))
		Engine::Safe_Delete(pPlayer);

	return pPlayer;
}

void CPlayer::Update(void)
{
	KeyInput();
	SetDirection();
	
	if(m_bMove)
		Move();

	m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");
	m_pTerrainCol->SetColInfo(&m_pInfo->vPos, m_pTerrainVtx);

	Engine::CGameObject::Update();

	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	m_pResource->Update(L"Stand", &m_pInfo->matWorld, pMatView, pMatProj);
}

void CPlayer::Render(void)
{
	m_pResource->Render(0);
}

void CPlayer::Release(void)
{
	Engine::Safe_Delete(m_pCameraObserver);

	if (m_pResource)
		Engine::Safe_Delete(m_pResource);
}

HRESULT CPlayer::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Collision Terrain
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_TERRAIN);
	m_pTerrainCol = dynamic_cast<CTerrainCol*>(pComponent);
	NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

	// Action
	pComponent = CAction::Create(this);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Player Action", pComponent));

	// Stat
	pComponent = m_pStat = Engine::CStatus::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Status", pComponent));
	
	// Sprite
	pComponent = m_pSprite = Engine::CSprite::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Sprite", pComponent));



	//// Collision Mouse
	//pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_MOUSE);
	//m_pMouseCol = dynamic_cast<CMouseCol*>(pComponent);
	//NULL_CHECK_RETURN(m_pMouseCol, E_FAIL);
	//m_mapComponent.insert(MAPCOMPONENT::value_type(L"MouseCol", pComponent));

	return S_OK;
}

void CPlayer::Move(void)
{
	D3DXVECTOR3		vDir;
	vDir = m_vDestPos - m_pInfo->vPos;

	float fDistance = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	m_pInfo->vPos += vDir * m_fSpeed * m_pTimeMgr->GetTime();

	if(fDistance < 1.f)
		m_bMove = false;
}

void CPlayer::Load( void )
{
	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(L"../../Data/b.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	Engine::VTXCUBE*		pVtx = new Engine::VTXCUBE[8];
	Engine::CCubeMotion*	pMotion = Engine::CCubeMotion::Create(m_pDevice);
	Engine::CCubeObj*		pCube = Engine::CCubeObj::Create(m_pDevice);
	wstring wstrStateKey = L"";

	int iFrame = 0;
	while(true)
	{
		Engine::SAVEFRAME* pSave = new Engine::SAVEFRAME;
		ReadFile(hFile, pSave, sizeof(Engine::SAVEFRAME), &dwByte, NULL);

		if(dwByte == 0)
		{
			pMotion->AddSprite(wstrStateKey, pCube);

			Engine::Safe_Delete(pSave);
			break;
		}
		wstrStateKey = pSave->wstrStateKey;

		TCHAR szBuf[255] = L"";
		wsprintf(szBuf, L"%s%s", pSave->wstrPartsKey.c_str(), L".dds");

		Engine::CVIBuffer* pResource = Engine::CCubeTex::Create(m_pDevice, szBuf);

		for (int i = 0; i < 8; ++i)
			pVtx[i] = pSave->VtxInfo[i];

		pResource->SetOriginVtxInfo(pVtx);
		pResource->SetVtxInfo(pVtx);

		if (iFrame == pSave->FrameKey)
		{
			pCube->AddCube(pResource);
		}
		else
		{
			pMotion->AddSprite(wstrStateKey, pCube);

			iFrame = pSave->FrameKey;
			pCube = Engine::CCubeObj::Create(m_pDevice);
			pCube->AddCube(pResource);
		}
		Engine::Safe_Delete(pSave);

	}
	
	m_pResource = pMotion;
	CloseHandle(hFile);
	Engine::Safe_Delete_Array(pVtx);
}

