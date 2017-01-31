#include "StdAfx.h"
#include "MonsterBall.h"

#include "Stage.h"
#include "Layer.h"

#include "BoundCol.h"

CMonsterBall::CMonsterBall( LPDIRECT3DDEVICE9 pDevice )
:CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pLayer(NULL)
, m_pBoundCol(NULL)
, m_pTerrainCol(NULL)
, m_dwType(0)
, m_dwState(0)
{

}

CMonsterBall::~CMonsterBall( void )
{
	Release();
}

HRESULT CMonsterBall::Initialize( D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, DWORD dwType)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			=	8;
	m_pVertex			=	new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXCUBE[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pVertex);
	m_dwType = dwType;
	m_pInfo->vPos = vPos;
	m_pInfo->vDir = vDir;
	m_pInfo->vScale /= 2.f;
	m_fHeight = 0.f;

	m_wstrObjkey = L"Monsterball";

	m_pBox->Initialize(&m_pInfo->vPos, &m_pInfo->vScale);
	m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");

	return S_OK;
}

void CMonsterBall::Update( void )
{
	switch (m_dwState)
	{
	case 0:
		Move();
		break;

	case 1:
		HitMove();
		break;
	}

	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matViewProj = (*pMatView) * (*pMatProj);
	m_pZFrustum->MakePlane(&matViewProj);

	if (m_pZFrustum->IsIn(&m_pInfo->vPos) == true)
	{
		m_bCulling = false;
	}
	else
	{
		m_bCulling = true;
		return;
	}

	SetTransform();
	//SetDirection();

	m_pTerrainCol->SetColInfo(&m_pInfo->vPos, m_pTerrainVtx);
	Engine::CGameObject::Update();
	m_pBox->Update(&m_pInfo->vPos);
	if (m_dwState == 0)
		ColMonster();

	if (m_pTerrainCol->GetColTerrainStat())
	{
		m_dwState = 2;
	}
}

void CMonsterBall::Render( void )
{
	if (m_bCulling == true)
		return;

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pConvertVertex);
	m_pTexture->Render(0);
	m_pBuffer->Render();
}

void CMonsterBall::Release( void )
{
	if(m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if(m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}

	if (m_pInfoSubject != NULL)
		m_pInfoSubject->UnSubscribe(m_pCameraObserver);

	Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CMonsterBall::AddComponent( void )
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

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer CubeTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture MonsterBall");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	// Collision Terrain
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_TERRAIN);
	m_pTerrainCol = dynamic_cast<CTerrainCol*>(pComponent);
	NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

	// Collision Bound
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_BOUND);
	m_pBoundCol = dynamic_cast<CBoundCol*>(pComponent);
	NULL_CHECK_RETURN(m_pBoundCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundCol", pComponent));

	return S_OK;
}


void CMonsterBall::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}

void CMonsterBall::Move( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_pInfo->vDir.y -= 0.2f * fTime;


	m_pInfo->fAngle[Engine::ANGLE_Z] -= D3DXToRadian(rand() % 600 + 600) * fTime;
	m_pInfo->fAngle[Engine::ANGLE_X] -= D3DXToRadian(720.f) * fTime;
	m_pInfo->fAngle[Engine::ANGLE_Y] -= D3DXToRadian(2600.f) * fTime;

	m_pInfo->vPos += m_pInfo->vDir * 60.f * fTime;
}

void CMonsterBall::HitMove(void)
{
	float fTime = m_pTimeMgr->GetTime();

	m_pInfo->vDir.y -= 0.6f * fTime;
	m_pInfo->vPos += m_pInfo->vDir * 30.f * fTime;
}

CMonsterBall* CMonsterBall::Create( LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, DWORD dwType)
{
	CMonsterBall* pMonsterball = new CMonsterBall(pDevice);

	if (FAILED(pMonsterball->Initialize(vPos, vDir, dwType)))
		Engine::Safe_Delete(pMonsterball);

	return pMonsterball;
}

void CMonsterBall::SetTransform( void )
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matPrint = m_pInfo->matWorld * (*pMatView) ;

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matPrint);

		if (m_pConvertVertex[i].vPos.z < 1.f)
		{
			m_bCulling = true;
			return;
		}

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatProj);
	}
}

void CMonsterBall::SetLayer( Engine::CLayer* pLayer )
{
	m_pLayer = pLayer;
}

void CMonsterBall::ColMonster( void )
{
	list<Engine::CGameObject*>* plist = m_pLayer->GetComponentList(L"Poketmon");

	if (plist == NULL)
		return;

	list<Engine::CGameObject*>::iterator iter = plist->begin();
	list<Engine::CGameObject*>::iterator iter_end = plist->end();

	for ( ; iter != iter_end; ++iter)
	{
		Engine::CBoundBox* pBox = (Engine::CBoundBox*)(*iter)->GetComponent(L"BoundBox");

		if (m_pBoundCol->ColBoundBox(m_pBox, pBox))
		{
			CSoundMgr::GetInstance()->PlaySound(L"Basic_Attack2.mp3");
			Engine::CStatus* pStat = (Engine::CStatus*)(*iter)->GetComponent(L"Status");
			
			switch (m_dwType)
			{
			case 0:

				if (pStat->fHp / pStat->fFullHp < 0.3f || ((CMultiGameObject*)(*iter))->GetType() != 0)
				{
					m_wstrObjkey = ((CMultiGameObject*)(*iter))->GetObjKey();
					if(((CMultiGameObject*)(*iter))->GetObjKey() == L"Pairi" && ((CMultiGameObject*)(*iter))->GetType() == 1)
						CSoundMgr::GetInstance()->PlaySound(L"Jiwoo0.MP3");
					else
						CSoundMgr::GetInstance()->PlaySound(L"Jiwoo2.mp3");
					(*iter)->SetDestroy();
				}
				break;

			case 1:
				pStat->fHp -= 1.f;

				if (pStat->fHp < 0)
				{

				}
				break;

			}
			
			m_pInfo->vDir.x *= -1.f;
			m_pInfo->vDir.z *= -1.f;
			m_dwState = 1;
			return;
		}
	}
}

std::wstring CMonsterBall::GetObjkey( void )
{
	return m_wstrObjkey;
}

