#include "stdafx.h"
#include "Terrain.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"
#include "Texture.h"
#include "Transform.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "Pipeline.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_fSpeed(0.f)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pCameraObserver(NULL)
{

}

CTerrain::~CTerrain(void)
{
	Release();
}	


HRESULT CTerrain::Initialize(void)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());

	m_fSpeed = 100.f;

	m_dwVtxCnt			=  VTXCNTX * VTXCNTZ;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Terrain", m_pVertex);
	DataLoad();


	return S_OK;
}

void CTerrain::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}

CTerrain* CTerrain::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CTerrain*		pTerrain = new CTerrain(pDevice);

	if(FAILED(pTerrain->Initialize()))
		Engine::Safe_Delete(pTerrain);

	return pTerrain;
}

void CTerrain::Update(void)
{
	SetDirection();

	Engine::CGameObject::Update();

	SetTransform();

}

void CTerrain::Render(void)
{

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Terrain", m_pConvertVertex);
	
	m_pTexture->Render(1);

	m_pBuffer->Render();
}

void CTerrain::Release(void)
{
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

HRESULT CTerrain::AddComponent(void)
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

void CTerrain::SetTransform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&m_pInfo->matWorld);

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatView);

		if(m_pConvertVertex[i].vPos.z < 1.f)
			m_pConvertVertex[i].vPos.z = 1.f;

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatProj);
	}
}

void CTerrain::DataLoad(void)
{

	DWORD	dwByte = 0;

	HANDLE	hFile  = NULL;

	hFile = CreateFile(L"../../Data/test.dat",GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

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

const Engine::VTXTEX* CTerrain::GetTerrainVertex(void)
{
	return m_pVertex;
}

