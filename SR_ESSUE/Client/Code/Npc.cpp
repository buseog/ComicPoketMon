#include "StdAfx.h"
#include "Npc.h"

#include "Stage.h"
#include "TerrainCol.h"

CNpc::CNpc( LPDIRECT3DDEVICE9 pDevice )
: CMultiGameObject(pDevice)
, m_bState(true)
{

}

CNpc::~CNpc( void )
{
	Release();
}

HRESULT CNpc::Initialize( void )
{
	Load();

	FAILED_CHECK(AddComponent());

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_fPattenTime = 2.f;

	m_pStat->fSpeed = 10.f;

	m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(180.f);

	return S_OK;
}

void CNpc::Update( void )
{
	float fTime = m_pTimeMgr->GetTime();
	m_fPattenTime -= fTime;

	if(m_fPattenTime < 0)
	{
		if(m_bState)
		{
			m_bState = false;
			m_fPattenTime = 5.f;
		}
		else
		{
			m_bState = true;
			m_fPattenTime = 2.f;
			m_pInfo->fAngle[Engine::ANGLE_Y] += D3DXToRadian(180.f);
			if(m_pInfo->fAngle[Engine::ANGLE_Y] == 360.f)
				m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(0.f);

			
		}

	}

	if(m_bState)
		Patten();

	SetDirection();

	m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");
	m_pTerrainCol->SetColInfo(&m_pInfo->vPos, m_pTerrainVtx);

	Engine::CGameObject::Update();

	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	m_pResource->Update(L"Walk", &m_pInfo->matWorld, pMatView, pMatProj);

}

void CNpc::Render( void )
{
	m_pResource->Render((DWORD)m_pSprite->fSpriteCnt);
}

void CNpc::Release( void )
{
	Engine::Safe_Delete(m_pCameraObserver);

	if (m_pResource)
	{
		Engine::Safe_Delete(m_pResource);
	}
}

HRESULT CNpc::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// BoundBox
	pComponent = m_pBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &m_pInfo->vScale);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundBox", pComponent));

	// Collision Terrain
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_TERRAIN);
	m_pTerrainCol = dynamic_cast<CTerrainCol*>(pComponent);
	NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

	// Stat
	pComponent = m_pStat = Engine::CStatus::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Status", pComponent));

	// Sprite
	pComponent = m_pSprite = Engine::CSprite::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Sprite", pComponent));
	m_pSprite->fSpriteMax = 4.f;
	m_pSprite->fSpriteSpeed = 2.f;


	return S_OK;
}

void CNpc::SetDirection( void )
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}

CNpc* CNpc::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CNpc*		pPoketmon = new CNpc(pDevice);

	if(FAILED(pPoketmon->Initialize()))
		Engine::Safe_Delete(pPoketmon);

	return pPoketmon;
}

void CNpc::Load( void )
{
	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(L"../bin/Data/SWalk.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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

void CNpc::SetPos( const D3DXVECTOR3& vPos )
{
	m_pInfo->vPos = vPos;
}

void CNpc::Patten( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;

}
