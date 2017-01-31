#include "stdafx.h"
#include "Wall.h"

#include "Export_Function.h"
#include "ResourceMgr.h"
#include "SceneSelector.h"

#include "Layer.h"
#include "Transform.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "CollisionMgr.h"
#include "CubeTex.h"
#include "CubeObj.h"
#include "BoundBox.h"
#include "Player.h"
#include "BasicCamera.h"

CWall::CWall( LPDIRECT3DDEVICE9 pDevice )
: CHousing(pDevice)
, m_pManagement(Engine::Get_Management())
{

}

CWall::~CWall( void )
{
	Release();
}

void CWall::Release( void )
{
	if(m_pVertex)
		Engine::Safe_Delete_Array(m_pVertex);
	
	if(m_pConvertVertex)
		Engine::Safe_Delete_Array(m_pConvertVertex);
	
	for(size_t i = 0; i < m_vecBuffer.size(); ++i)
		Engine::Safe_Delete(m_vecBuffer[i]);
	m_vecBuffer.clear();
	Engine::Safe_Delete(m_pCameraObserver);
}

HRESULT CWall::Initialize( SCENEID ID )
{
	FAILED_CHECK(AddComponent());

	m_eState = ID;

	Load(m_eState);

	m_dwVtxCnt			=	8;
	m_pVertex			=	new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXCUBE[m_dwVtxCnt]; 

	m_pInfo->vPos = D3DXVECTOR3(245.f, 1.f, 15.f);

	m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(-90.f);

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	PotalSetting();
	return S_OK;
}

void CWall::Update( void )
{
	ColPlayer();
	Engine::CGameObject::Update();
	SetTrensform();
}

void CWall::Render( void )
{
	CHousing::Render();
}

CWall* CWall::Create(LPDIRECT3DDEVICE9 pDevice, SCENEID ID)
{
	CWall*		pWall = new CWall(pDevice);

	if(FAILED(pWall->Initialize(ID)))
		Engine::Safe_Delete(pWall);

	return pWall;
}

HRESULT CWall::AddComponent( void )
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

	// PotalBox
	pComponent = m_pPotalBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &m_pInfo->vScale);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"PotalBox", pComponent));

	// Collision Bound
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_BOUND);
	m_pBoundCol = dynamic_cast<CBoundCol*>(pComponent);
	NULL_CHECK_RETURN(m_pBoundCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundCol", pComponent));

	return S_OK;
}

void CWall::Load( SCENEID ID )
{
	DWORD	dwByte = 0;
	HANDLE	hFile;
	switch(ID)
	{
	case SC_STAGE:
		hFile  = CreateFile(L"../bin/Data/Center.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		break;

	case SC_CENTER:
		hFile  = CreateFile(L"../bin/Data/test.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		break;
	}
	
	Engine::VTXCUBE*		pVtx = new Engine::VTXCUBE[8];
	wstring wstrStateKey = L"";

	while(true)
	{
		Engine::SAVEFILE* pSave = new Engine::SAVEFILE;
		ReadFile(hFile, pSave, sizeof(Engine::SAVEFILE), &dwByte, NULL);

		if(dwByte == 0)
		{
			Engine::Safe_Delete(pSave);
			break;
		}
		TCHAR szBuf[255] = L"";
		wsprintf(szBuf, L"%s%s", pSave->wstrName.c_str(), L".dds");

		Engine::CVIBuffer* pResource = Engine::CCubeTex::Create(m_pDevice, szBuf);

		for (int i = 0; i < 8; ++i)
			pVtx[i] = pSave->VtxInfo[i];

		pResource->SetOriginVtxInfo(pVtx);
		pResource->SetVtxInfo(pVtx);

		m_vecBuffer.push_back(pResource);
		Engine::Safe_Delete(pSave);

	}
	CloseHandle(hFile);
	Engine::Safe_Delete_Array(pVtx);
}

void CWall::SetTrensform(void)
{
	const D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	const D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	D3DXMATRIX matPrint = m_pInfo->matWorld * (*pMatView);

	for(size_t j = 0; j < m_vecBuffer.size(); ++j)
	{
		m_vecBuffer[j]->GetOriginVtxInfo(m_pVertex);

		for(size_t i = 0; i < m_dwVtxCnt; ++i)
		{
			m_pConvertVertex[i] = m_pVertex[i];

			Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, &m_pConvertVertex[i].vPos, &matPrint);

			if (m_pConvertVertex[i].vPos.z < 1.f)
				m_pConvertVertex[i].vPos.z = 1.f;

			Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
				&m_pConvertVertex[i].vPos,pMatProj);
		}


		m_vecBuffer[j]->SetVtxInfo(m_pConvertVertex);
	}
}

void CWall::PotalSetting( void )
{
	m_pPotalBox->Update(&m_pInfo->vPos);
	m_pPotalBox->vCenter.x -= 10.f;
	m_pPotalBox->vSize = D3DXVECTOR3(1.f, 1.f, 1.f);

	m_pBox->Initialize(&m_pInfo->vPos, &D3DXVECTOR3(2.5f, 2.f, 5.f));
	m_pBox->Update(&m_pInfo->vPos);
	
}

void CWall::SetLayer( Engine::CLayer* pLayer )
{
	m_pLayer = pLayer;
}

void CWall::ColPlayer( void )
{
	
	Engine::CGameObject* pPlayer = m_pLayer->GetComponentList(L"Player")->back();

	if(pPlayer == NULL)
		return;
	Engine::CBoundBox* pBox = (Engine::CBoundBox*)pPlayer->GetComponent(L"BoundBox");

	if(m_pBoundCol->ColBoundBox(m_pPotalBox, pBox))
	{
		CSoundMgr::GetInstance()->StopBGM(L"Bgm.mp3");
		CSoundMgr::GetInstance()->PlayBGM(L"prison.mp3");
		CSoundMgr::GetInstance()->PlaySound(L"Jiwoo1.MP3");
		((CPlayer*)pPlayer)->SetPos(D3DXVECTOR3(15.f, 0.f, 5.f));
		CBasicCamera::m_eCamType = CAM_INSIDE;
		m_pManagement->SceneChange(CSceneSelector(SC_CENTER), SC_CENTER);
		Engine::CManagement::m_iScene = SC_CENTER;
		((CPlayer*)pPlayer)->SetLayer(m_pManagement->GetScene(SC_CENTER)->GetLayer(1));

	}
}
