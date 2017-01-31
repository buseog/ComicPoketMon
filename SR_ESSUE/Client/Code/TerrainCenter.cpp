#include "stdafx.h"
#include "TerrainCenter.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"
#include "Texture.h"
#include "CameraObserver.h"
#include "Transform.h"
#include "InfoSubject.h"
#include "ZFrustum.h"

CTerrainCenter::CTerrainCenter(LPDIRECT3DDEVICE9 pDevice)
: CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pQuadTree(NULL)
{

}

CTerrainCenter::~CTerrainCenter(void)
{
	Release();
}	


HRESULT CTerrainCenter::Initialize(void)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			=	VTXCNTX * VTXCNTZ;
	m_pVertex			=	new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXTEX[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Terrain", m_pVertex);

	m_pQuadTree = new CZQuadTree(VTXCNTX, VTXCNTZ);
	BuildQuadTree();
	//DataLoad();


	return S_OK;
}

CTerrainCenter* CTerrainCenter::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTerrainCenter*		pTerrain = new CTerrainCenter(pDevice);

	if(FAILED(pTerrain->Initialize()))
		Engine::Safe_Delete(pTerrain);

	return pTerrain;
}

void CTerrainCenter::Update(void)
{
	Engine::CGameObject::Update();
	SetTransform();
}

void CTerrainCenter::Render(void)
{
	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Terrain", m_pConvertVertex);

	m_pTexture->Render(2);

	m_pBuffer->Render();
}

void CTerrainCenter::Release(void)
{
	Engine::Safe_Delete(m_pQuadTree);

	if(m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if(m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}

	Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CTerrainCenter::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Terrain");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture Terrain");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

void CTerrainCenter::DataLoad(void)
{

	DWORD	dwByte = 0;

	HANDLE	hFile  = NULL;

	hFile = CreateFile(L"../bin/Data/Stage.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	Engine::VTXTEX*		pVTXCOL = new Engine::VTXTEX[257 * 257];
	int i = 0;
	while(true)
	{

		ReadFile(hFile, &pVTXCOL[i], sizeof(Engine::VTXTEX), &dwByte, NULL);

		if(dwByte == 0)
		{	
			break;
		}
		++i;
	}

	m_pBuffer->SetVtxInfo(pVTXCOL);
	m_pBuffer->SetOriginVtxInfo(pVTXCOL);

	memcpy(m_pVertex, pVTXCOL, sizeof(Engine::VTXTEX) * (257*257));

	Engine::Safe_Delete_Array(pVTXCOL);

	CloseHandle(hFile);
}


const Engine::VTXTEX* CTerrainCenter::GetTerrainVertex(void)
{
	return m_pVertex;
}

void CTerrainCenter::SetTransform( void )
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matPrint = m_pInfo->matWorld * (*pMatView);

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, &matPrint);

		if (m_pConvertVertex[i].vPos.z < 1.f)
			m_pConvertVertex[i].vPos.z = 1.f;

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatProj);
	}
}

HRESULT CTerrainCenter::BuildQuadTree( void )
{
	m_pQuadTree->Build();
	return S_OK;
}

