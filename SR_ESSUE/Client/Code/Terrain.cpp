#include "stdafx.h"
#include "Terrain.h"

CTerrain::CTerrain(LPDIRECT3DDEVICE9 pDevice)
: CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pQuadTree(NULL)
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

	if(Engine::CManagement::m_iScene == SC_STAGE)
	{
		m_dwVtxCnt			=	VTXCNTX * VTXCNTZ;
		m_pVertex			=	new Engine::VTXTEX[m_dwVtxCnt];
		m_pConvertVertex	=	new Engine::VTXTEX[m_dwVtxCnt];

		m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Terrain", m_pVertex);

		/*m_pQuadTree = new CZQuadTree(257, 257);
		BuildQuadTree();*/

		DataLoad();

	}

	else if(Engine::CManagement::m_iScene == SC_CENTER)
	{
		m_dwVtxCnt			=	33 * 33;
		m_pVertex			=	new Engine::VTXTEX[m_dwVtxCnt];
		m_pConvertVertex	=	new Engine::VTXTEX[m_dwVtxCnt];

		m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer TerrainCenter", m_pVertex);

		/*m_pQuadTree = new CZQuadTree(33, 33);
		BuildQuadTree();*/
	}
	


	return S_OK;
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
	Engine::CGameObject::Update();
	SetTransform();
}

void CTerrain::Render(void)
{
	if(Engine::CManagement::m_iScene == SC_STAGE)
		m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer Terrain", m_pConvertVertex);

	else if(Engine::CManagement::m_iScene == SC_CENTER)
		m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer TerrainCenter", m_pConvertVertex);
	
	m_pTexture->Render(Engine::CManagement::m_iScene);

	m_pBuffer->Render();

}

void CTerrain::Release(void)
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

HRESULT CTerrain::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Buffer
	if(Engine::CManagement::m_iScene == SC_STAGE)
	{
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer Terrain");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	}
	else if(Engine::CManagement::m_iScene == SC_CENTER)
	{
		pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer TerrainCenter");
		m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
		NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	}
	

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture Terrain");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

void CTerrain::DataLoad(void)
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


const Engine::VTXTEX* CTerrain::GetTerrainVertex(void)
{
	return m_pVertex;
}

void CTerrain::SetTransform( void )
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

HRESULT CTerrain::BuildQuadTree( void )
{
	m_pQuadTree->Build();
	return S_OK;
}

