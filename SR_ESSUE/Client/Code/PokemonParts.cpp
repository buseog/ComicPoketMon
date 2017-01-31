#include "StdAfx.h"
#include "PokemonParts.h"

#include "Stage.h"
#include "Layer.h"

#include "BoundCol.h"

CPokemonParts::CPokemonParts(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, const wstring& wstrObjKey)
:CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pBoundCol(NULL)
, m_pTerrainCol(NULL)
, m_dwType(0)
, m_dwState(0)
, m_pLayer(pLayer)
, m_wstrTextureKey(wstrObjKey)
, m_fJukCoShipDa(0.f)
, m_iNanWaeSalcca(0)
, m_wstrObjkey(wstrObjKey)
{

}

CPokemonParts::~CPokemonParts(void)
{
	Release();
}

CPokemonParts* CPokemonParts::Create(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, Engine::CTransform* pInfo, const wstring& wstrObjKey)
{
	CPokemonParts*		pParts = new CPokemonParts(pDevice, pLayer, wstrObjKey);

	if(FAILED(pParts->Initialize(pInfo)))
		Engine::Safe_Delete(pParts);

	return pParts;
}

HRESULT CPokemonParts::Initialize(Engine::CTransform* pInfo)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());
	
	m_dwVtxCnt			=	8;
	m_pVertex			=	new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXCUBE[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pVertex);

	m_pInfo->vPos = pInfo->vPos;
	m_pInfo->vDir = pInfo->vDir;
	m_pInfo->vScale = pInfo->vScale;
	m_pInfo->fAngle[1] = pInfo->fAngle[1];

	m_pBox->Initialize(&m_pInfo->vPos, &m_pInfo->vScale);
	m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");


	return S_OK;
}



void CPokemonParts::Update(void)
{
	float fTime = m_pTimeMgr->GetTime();

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

	m_fJukCoShipDa += fTime;
	m_pInfo->vPos.y += sinf(m_fJukCoShipDa) * fTime;

	m_pInfo->fAngle[1] += m_fJukCoShipDa;
	m_pTerrainCol->SetColInfo(&m_pInfo->vPos, m_pTerrainVtx);
	Engine::CGameObject::Update();
	m_pBox->Update(&m_pInfo->vPos);
	//	ColMonster();

	if (m_pTerrainCol->GetColTerrainStat())
	{
		m_dwState = 2;
	}
}

void CPokemonParts::Render(void)
{
	if (m_bCulling == true)
		return;

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pConvertVertex);
	m_pTexture->Render(0);
	m_pBuffer->Render();
}

void CPokemonParts::Release(void)
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

HRESULT CPokemonParts::AddComponent(void)
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
	if(m_wstrObjkey == L"Ggobugi")
	{
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"SHead.dds");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	}
	else if(m_wstrObjkey == L"Pairi")
	{
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"CHead.dds");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	}
	else if(m_wstrObjkey == L"Picachu")
	{
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"PHead.dds");
		m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
		NULL_CHECK_RETURN(m_pTexture, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	}
	

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

void CPokemonParts::SetLayer(Engine::CLayer* pLayer)
{

}
void CPokemonParts::SetTransform(void)
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

void CPokemonParts::ColPlayer(void)
{

}

std::wstring CPokemonParts::GetObjkey( void )
{
	return m_wstrObjkey;
}
