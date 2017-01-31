#include "StdAfx.h"
#include "WaterEffect.h"

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

CWaterEffect::CWaterEffect(LPDIRECT3DDEVICE9 pDevice)
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

CWaterEffect::~CWaterEffect()
{
	Release();
}

HRESULT CWaterEffect::Initialize(const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir, int iCount)
{
	Addcomponent();

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer WaterEffect", m_pVertex);

	m_fTime = 0.f;
	m_fSpeed = 10.f;

	return S_OK;
}

void CWaterEffect::Update(void)
{
	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matViewProj = (*pMatView) * (*pMatProj);
	m_pZFrustum->MakePlane(&matViewProj);

	Engine::CGameObject::Update();


	Engine::SPRITE	m_Fire = {12, 0, 0, 3};

	Sprite();

	SetTransform();
}

void CWaterEffect::Render(void)
{
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer WaterEffect", m_pConvertVertex);
	m_pTexture->Render(0);
	m_pBuffer->Render();

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void CWaterEffect::Release(void)
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

HRESULT CWaterEffect::Addcomponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer WaterEffect");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture WaterEffect");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

CWaterEffect* CWaterEffect::Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey, D3DXVECTOR3 vOrigin, D3DXVECTOR3 vDir, int iCount)
{
	CWaterEffect*		pWaterEffect = new CWaterEffect(pDevice);

	if(FAILED(pWaterEffect->Initialize(wstrKey, vOrigin, vDir, iCount)))
		Engine::Safe_Delete(pWaterEffect);

	return pWaterEffect;
}

void CWaterEffect::SetTransform(void)
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

HRESULT CWaterEffect::Sprite(void)
{
	int iFullFrame = 16;
	int iCurIndex = 0;
	int iFrameCounter = 0;

	float X = iCurIndex / 16.f;
	float X2 = (iCurIndex + 1) / 16.f;

	m_pVertex[0].vTex = D3DXVECTOR2(X, 0.0f);
	m_pVertex[1].vTex = D3DXVECTOR2(X2, 0.0f);
	m_pVertex[2].vTex = D3DXVECTOR2(X2, 1.0f);
	m_pVertex[3].vTex = D3DXVECTOR2(X, 1.0f);

	iCurIndex += int(1 * m_pTimeMgr->GetTime()); 

	if(iCurIndex > iFullFrame)
	{
		iCurIndex = 0;
		return 1;
	}

	return S_OK;
}
