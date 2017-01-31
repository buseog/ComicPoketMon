#include "StdAfx.h"
#include "Objects.h"



CObjects::CObjects(LPDIRECT3DDEVICE9 pDevice)
:CSingleGameObject(pDevice)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)

{

}

CObjects::~CObjects(void)
{
	Release();
}

CObjects* CObjects::Create(LPDIRECT3DDEVICE9 pDevice, Engine::OBJINFO tObjInfo)
{	
	CObjects* pObjects = new CObjects(pDevice);
	
	if(FAILED(pObjects->Initialize(tObjInfo)))
		Engine::Safe_Delete(pObjects);

	return pObjects;
}

HRESULT CObjects::Initialize(Engine::OBJINFO tObjInfo)
{
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_wstrTexKey = tObjInfo.wstrTexKey;
	m_iTexCount = tObjInfo.iTexCount;

	FAILED_CHECK(AddComponent());
	
	m_pInfo->vScale = D3DXVECTOR3(20.f, 10.f, 0.f);
	
	m_dwVtxCnt			=	4;
	m_pVertex			=	new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXTEX[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pVertex);

	m_pInfo->vPos = tObjInfo.vPos;

	return S_OK;
}

void CObjects::SetTransform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX	matViewInverse;

	D3DXMatrixInverse(&matViewInverse, NULL, pMatView);

	memcpy(&m_pInfo->matWorld.m[0][0], &matViewInverse.m[0][0], sizeof(float)*3);

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

void CObjects::Update(void)
{
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
	Engine::CGameObject::Update();
}

void CObjects::Render(void)
{
	if (m_bCulling == true)
		return;

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pConvertVertex);
	m_pTexture->Render(m_iTexCount);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CObjects::Release(void)
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

HRESULT CObjects::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer RcTex");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, m_wstrTexKey);
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

