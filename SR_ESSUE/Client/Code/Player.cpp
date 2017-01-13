#include "stdafx.h"
#include "Player.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "TimeMgr.h"
#include "Include.h"
#include "Texture.h"
#include "Transform.h"
#include "Pipeline.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "Stage.h"
#include "Pipeline.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: Engine::CGameObject(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pManagement(Engine::Get_Management())
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pCameraObserver(NULL)
, m_pTerrainVtx(NULL)
, m_pStat(NULL)
, m_fSpeed(0.f)
, m_bMove(false)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_dwVtxCnt			= 4;
	m_pVertex			= new Engine::VTXTEX[m_dwVtxCnt];
	m_pConvertVertex	= new Engine::VTXTEX[m_dwVtxCnt];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_DYNAMIC, L"Buffer Player", m_pVertex);


	m_fSpeed = 40.f;

	FAILED_CHECK(AddComponent());


	return S_OK;
}

void CPlayer::KeyInput(void)
{
	float fTime = m_pTimeMgr->GetTime();

	if(GetAsyncKeyState('W') & 0X8000)
	{
		m_pInfo->vPos += m_pInfo->vDir * m_fSpeed * fTime;
	}

	if(GetAsyncKeyState('S') & 0X8000)
	{
		m_pInfo->vPos -= m_pInfo->vDir * m_fSpeed * fTime;
	}

	if(GetAsyncKeyState('A') & 0X8000)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] += D3DXToRadian(90.f) * fTime;
	}

	if(GetAsyncKeyState('D') & 0X8000)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] -= D3DXToRadian(90.f) * fTime;
	}

	if(GetAsyncKeyState(VK_LBUTTON)  & 0x8000)
	{
		/*m_bMove = true;
		m_pMouseCol->PickTerrain(&m_vDestPos, m_pTerrainVtx);*/

		D3DXVECTOR3	vTemp;
		//m_pMouseCol->PickObject(&vTemp, m_pVertex, &m_pInfo->matWorld);
	}
		
}

void CPlayer::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pDevice)
{
	CPlayer*		pPlayer = new CPlayer(pDevice);

	if(FAILED(pPlayer->Initialize()))
		Engine::Safe_Delete(pPlayer);

	return pPlayer;
}

void CPlayer::Update(void)
{
	KeyInput();
	SetDirection();
	
	if(m_bMove)
		Move();

	m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");

	Engine::CGameObject::Update();

	SetTransform();
}

void CPlayer::Render(void)
{
	/*m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);*/

	//m_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_DYNAMIC, L"Buffer Player", m_pConvertVertex);

	m_pTexture->Render(0);
	m_pBuffer->Render();

	/*m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);*/
}

void CPlayer::Release(void)
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

HRESULT CPlayer::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	//// Collision Terrain
	//pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_TERRAIN);
	//m_pTerrainCol = dynamic_cast<CTerrainCol*>(pComponent);
	//NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	//m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

	//// Collision Mouse
	//pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_MOUSE);
	//m_pMouseCol = dynamic_cast<CMouseCol*>(pComponent);
	//NULL_CHECK_RETURN(m_pMouseCol, E_FAIL);
	//m_mapComponent.insert(MAPCOMPONENT::value_type(L"MouseCol", pComponent));

	// Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_DYNAMIC, L"Buffer Player");
	m_pBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Buffer", pComponent));

	//Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_DYNAMIC, L"Texture Player");
	m_pTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Texture", pComponent));

	return S_OK;
}

void CPlayer::SetTransform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);
	
	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	for(size_t i = 0; i < m_dwVtxCnt; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, 
								&m_pConvertVertex[i].vPos, 
								&m_pInfo->matWorld);

		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatView);

		if(m_pConvertVertex[i].vPos.z < 1.f)
			m_pConvertVertex[i].vPos.z = 1.f;

		Engine::CPipeline::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			pMatProj);
	}
}

void CPlayer::Move(void)
{
	D3DXVECTOR3		vDir;
	vDir = m_vDestPos - m_pInfo->vPos;

	float fDistance = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	m_pInfo->vPos += vDir * m_fSpeed * m_pTimeMgr->GetTime();

	if(fDistance < 1.f)
		m_bMove = false;
}

