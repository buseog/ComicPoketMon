#include "StdAfx.h"
#include "FireEffect.h"

#include "Export_Function.h"
#include "TimeMgr.h"
#include "Include.h"
#include "Texture.h"
#include "Transform.h"
#include "Pipeline.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "TerrainCol.h"
#include "CollisionMgr.h"
#include "Stage.h"
#include "Engine_Include.h"

CFireEffect::CFireEffect(LPDIRECT3DDEVICE9 pDevice)
: CSingleGameObject(pDevice)
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_fSpeed(0.f)
, m_fCameraAngle(0.f)
, m_fDistance(0.f)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pCameraObserver(NULL)
{

}

CFireEffect::~CFireEffect()
{
	Release();
}

HRESULT CFireEffect::Initialize(void)
{
	Addcomponent();

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer FireEffect", m_pVertex);

	m_fTime = 0.f;
	m_fSpeed = 10.f;

	Sprite();

	return S_OK;
}

void CFireEffect::Update(void)
{
	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matViewProj = (*pMatView) * (*pMatProj);
	m_pZFrustum->MakePlane(&matViewProj);

	Engine::CGameObject::Update();


	Engine::SPRITE	m_Fire = {12, 0, 0, 3};

	SetTransform();
}

void CFireEffect::Render(void)
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer FireEffect", m_pConvertVertex);
	m_pTexture->Render(0);
	m_pBuffer->Render();
	
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CFireEffect::Release(void)
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

HRESULT CFireEffect::Addcomponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer FireEffect");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture FireEffect");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

HRESULT CFireEffect::Sprite(void)
{
	m_pVertex[0].vTex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVertex[1].vTex = D3DXVECTOR2((1.f/16.f), 0.0f);
	m_pVertex[2].vTex = D3DXVECTOR2((1.f/16.f), 1.0f);
	m_pVertex[3].vTex = D3DXVECTOR2(0.0f, 1.0f);

	int iCount = 0;
	iCount = int((1.f * int(m_pTimeMgr->GetTime())) / 16.f);

	/*m_pVertex[0].vTex = D3DXVECTOR2(0.0f, 0.0f);
	m_pVertex[1].vTex = D3DXVECTOR2(float(iCount), 0.0f);
	m_pVertex[2].vTex = D3DXVECTOR2(float(iCount), 1.0f);
	m_pVertex[3].vTex = D3DXVECTOR2(0.0f, 1.0f);*/

	if(iCount > 16)
		iCount = 0;

	return S_OK;
}

CFireEffect* CFireEffect::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CFireEffect*		pFireEffect = new CFireEffect(pDevice);

	if(FAILED(pFireEffect->Initialize()))
		Engine::Safe_Delete(pFireEffect);

	return pFireEffect;
}

void CFireEffect::SetTransform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matBill;
	Engine::MyIdentity(&matBill);

	matBill = *pMatView;
	ZeroMemory(&matBill.m[3][0], sizeof(D3DXVECTOR3));
	D3DXMatrixInverse(&matBill, NULL, &matBill);

	D3DXMATRIX matWorld;
	Engine::MyIdentity(&matWorld);

	matWorld = matBill * matWorld * (*pMatView) * (*pMatProj);

	for(size_t i = 0; i < 4; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matWorld);
	}
}
