#include "stdafx.h"
#include "Blaze.h"
#include "Layer.h"
#include "MathMgr.h"

CBlaze::CBlaze(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer)
: CEmanation(pDevice)
{

}

CBlaze::~CBlaze()
{
	Release();
}

CBlaze* CBlaze::Create(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, Engine::CTransform* pTransform, D3DXVECTOR3 vDir)
{
	CBlaze*	pBlaze = new CBlaze(pDevice, pLayer);

	if(FAILED(pBlaze->Initialize(pTransform, vDir)))
		Engine::Safe_Delete(pBlaze);

	return pBlaze;
}

HRESULT CBlaze::Initialize(Engine::CTransform* pTransform, D3DXVECTOR3 vDir)
{
	//m_pTexture = NULL;
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	FAILED_CHECK(AddComponent());

	m_fGunDistance = 3.f;
	m_fShotRadian  = 5.f;
	m_fRange	   = 20.f;

	
	m_fCetTime = 0.f;

	m_dwColorARGB[COL_A] = 255;
	m_dwColorARGB[COL_R] = 255;
	m_dwColorARGB[COL_G] = 255;
	m_dwColorARGB[COL_B] = 0;

	m_dwVtxCnt = 8;
	m_pVertex			=	new Engine::VTXCOL[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXCOL[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeCol", m_pVertex);

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pVertex[i].dwColor = D3DCOLOR_ARGB(m_dwColorARGB[COL_A],
												m_dwColorARGB[COL_R],
												m_dwColorARGB[COL_G],
												m_dwColorARGB[COL_B]);
	}
	m_pInfo->vPos = pTransform->vPos + vDir * m_fGunDistance;
	m_pInfo->vPos.y += 3.f;
	//m_pInfo->vDir = vDir;
	//m_pInfo->vPos = pTransform->vPos;
	
	D3DXVECTOR3 vTemp = m_pInfo->vPos + vDir * 10.f;

	vTemp.x += Engine::GetRandomFloat(0.f, m_fShotRadian);
	vTemp.y += Engine::GetRandomFloat(0.f, m_fShotRadian);
	vTemp.z += Engine::GetRandomFloat(0.f, m_fShotRadian);

	m_pInfo->vDir = vTemp - m_pInfo->vPos;
	
	Engine::CMathMgr::MyNormalize(&m_pInfo->vDir, &m_pInfo->vDir);

	return S_OK;
}

void CBlaze::SetTransform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matInvers;

	//D3DXMatrixInverse(&matInvers, NULL, pMatView);

	//memcpy(&m_pInfo->matWorld.m[0][0], &matInvers.m[0][0], sizeof(float) * 3);
	//memcpy(&m_pInfo->matWorld.m[1][0], &matInvers.m[1][0], sizeof(float) * 3);
	////memcpy(&m_pInfo->matWorld.m[2][0], &matInvers.m[2][0], sizeof(float) * 3);

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

void CBlaze::Update(void)
{
	float fTime = m_pTimeMgr->GetTime();

	m_pInfo->vPos += (m_pInfo->vDir * m_fRange) * fTime;
	m_pInfo->vPos.y += fTime;
	m_fRange -=  m_fRange * fTime;

	if(m_fRange <= 0.f)
		m_fRange = 0.f;

	m_fCetTime += fTime;

	if( m_dwColorARGB[COL_G] != 0 && m_fCetTime >= 0.025f )
	{
		m_dwColorARGB[COL_G] -= 5;
		m_fCetTime = 0.f;
	}
	
	if(m_dwColorARGB[COL_G] == 0 && m_dwColorARGB[COL_R] != 0 && m_fCetTime >= 0.025f)
	{
		m_dwColorARGB[COL_R] -= 5;
	}

	if(m_dwColorARGB[COL_R] == 0)
		m_bContents = false;

	for(size_t i = 0; i< m_dwVtxCnt; ++i)
	{
		m_pVertex[i].dwColor = D3DCOLOR_ARGB(m_dwColorARGB[COL_A],
			m_dwColorARGB[COL_R],
			m_dwColorARGB[COL_G],
			m_dwColorARGB[COL_B]);
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
	CGameObject::Update();
	
}

void CBlaze::Render(void)
{
	if (m_bCulling == true)
		return;

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer CubeCol", m_pConvertVertex);
	m_pBuffer->Render();
}

void CBlaze::Release(void)
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

HRESULT CBlaze::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer CubeCol");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"SHead.dds");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

