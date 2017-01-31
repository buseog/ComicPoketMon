#include "stdafx.h"
#include "ItemParts.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"
#include "Texture.h"
#include "CameraObserver.h"
#include "Transform.h"
#include "InfoSubject.h"

CItemParts::CItemParts(LPDIRECT3DDEVICE9 pDevice)
: CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pBoundCol(NULL)
{
}
CItemParts::CItemParts(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, const wstring& wstrObjKey)
: CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pLayer(pLayer)
, m_wstrTextureKey(wstrObjKey)
, m_fDijilGerGatDa(0.f)
, m_pBoundCol(NULL)
{
}
CItemParts::~CItemParts(void)
{
	Release();
}

HRESULT CItemParts::Initialize(void)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_dwVtxCnt			= 8;
	m_pVertex			= new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXCUBE[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pVertex);

	FAILED_CHECK(AddComponent());

	return S_OK;
}

HRESULT CItemParts::Initialize(Engine::CTransform* pInfo)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());

	m_dwVtxCnt			= 8;
	m_pVertex			= new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXCUBE[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pVertex);

	m_pInfo->vPos = D3DXVECTOR3(10.f, 0.f, 10.f);//pInfo->vPos;
	//m_pInfo->vDir = pInfo->vDir;
	m_pInfo->fAngle[1] = pInfo->fAngle[1];
	m_pInfo->vScale = pInfo->vScale;
	
	m_pBox->Initialize(&m_pInfo->vPos, &m_pInfo->vScale);

	return S_OK;
}

void CItemParts::Update(void)
{
	//float fTime = m_pTimeMgr->GetTime();
	//m_fDijilGerGatDa += fTime;
	//m_pInfo->vPos.y += sinf(m_fDijilGerGatDa) * fTime;

	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matViewProj = (*pMatView) * (*pMatProj);
	m_pZFrustum->MakePlane(&matViewProj);

	/*if (m_pZFrustum->IsIn(&m_pInfo->vPos) == true)
	{
		m_bCulling = false;
	}
	else
	{
		m_bCulling = true;
		return;
	}*/

	SetTransform();
	Engine::CGameObject::Update();
	m_pBox->Update(&m_pInfo->vPos);
}

void CItemParts::Render(void)
{
	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeTex", m_pConvertVertex);
	m_pTexture->Render(0);
	m_pBuffer->Render();
}

void CItemParts::Release(void)
{
	if(m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if(m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}

	m_pInfoSubject->UnSubscribe(m_pCameraObserver);
	Engine::Safe_Delete(m_pCameraObserver);
}


CItemParts* CItemParts::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CItemParts*		pItemParts = new CItemParts(pDevice);

	if(FAILED(pItemParts->Initialize()))
		Engine::Safe_Delete(pItemParts);

	return pItemParts;
}

CItemParts* CItemParts::Create(LPDIRECT3DDEVICE9 pDevice, 
							   Engine::CLayer* pLayer, 
							   Engine::CTransform* pInfo, 
							   const wstring& wstrObjKey )
{
	CItemParts*		pItemParts = new CItemParts(pDevice, pLayer, wstrObjKey);

	if(FAILED(pItemParts->Initialize(pInfo)))
		Engine::Safe_Delete(pItemParts);

	return pItemParts;
}

void CItemParts::Load( void )
{
	
}

HRESULT CItemParts::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer CubeTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"SHead.dds");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	// BoundBox
	pComponent = m_pBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &m_pInfo->vScale);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundBox", pComponent));

	return S_OK;
}


void CItemParts::SetTransform( void )
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
		
		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatProj);
	}
}

void CItemParts::ColPlayer(void)
{

}