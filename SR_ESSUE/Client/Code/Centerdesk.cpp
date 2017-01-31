#include "stdafx.h"
#include "Centerdesk.h"

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
#include "Poketmon.h"
CCenterdesk::CCenterdesk( LPDIRECT3DDEVICE9 pDevice )
: CHousing(pDevice)
, m_pManagement(Engine::Get_Management())
, m_iState(0)
{

}

CCenterdesk::~CCenterdesk( void )
{
	Release();
}

void CCenterdesk::Release( void )
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

HRESULT CCenterdesk::Initialize(int iState )
{
	m_iState = iState;
	FAILED_CHECK(AddComponent());

	Load();

	m_dwVtxCnt			=	8;
	m_pVertex			=	new Engine::VTXCUBE[m_dwVtxCnt];
	m_pConvertVertex	=	new Engine::VTXCUBE[m_dwVtxCnt]; 


	if(m_iState == 0)
	{
		m_pInfo->vPos = D3DXVECTOR3(0.f, 1.f, 21.f);
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(90.f);
	}

	if(m_iState == 1)
	{
		m_pInfo->vPos = D3DXVECTOR3(15.f, 1.f, 1.f);
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(90.f);
	}
	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	PotalSetting();
	return S_OK;
}

void CCenterdesk::Update( void )
{
	if(m_iState == 1)
		ColPlayer();
	else if(m_iState == 0)
		ColMonster();

	Engine::CGameObject::Update();
	SetTrensform();
}

void CCenterdesk::Render( void )
{
	CHousing::Render();
}

CCenterdesk* CCenterdesk::Create(LPDIRECT3DDEVICE9 pDevice,int iState)
{
	CCenterdesk*		pDesk = new CCenterdesk(pDevice);

	if(FAILED(pDesk->Initialize(iState)))
		Engine::Safe_Delete(pDesk);

	return pDesk;
}

HRESULT CCenterdesk::AddComponent( void )
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

void CCenterdesk::Load( void )
{
	DWORD	dwByte = 0;

	HANDLE	hFile;
	if(m_iState == 0)
	{
		hFile = CreateFile(L"../bin/Data/Prison1.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if(m_iState == 1)
	{
		hFile = CreateFile(L"../bin/Data/Door.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
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

void CCenterdesk::SetTrensform(void)
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

void CCenterdesk::PotalSetting( void )
{
	if(m_iState == 1)
	{
		m_pPotalBox->Update(&m_pInfo->vPos);
		m_pPotalBox->vCenter.x -= 10.f;
		m_pPotalBox->vSize = D3DXVECTOR3(1.f, 1.f, 1.f);
	}
	else if(m_iState == 0)
	{
		m_pPotalBox->Initialize(&m_pInfo->vPos, &D3DXVECTOR3(5.f, 1.f, 3.f));
		m_pPotalBox->Update(&m_pInfo->vPos);
	}

	m_pBox->Initialize(&m_pInfo->vPos, &D3DXVECTOR3(1.f, 1.f, 1.f));
	m_pBox->Update(&m_pInfo->vPos);

}

void CCenterdesk::ColPlayer( void )
{

	Engine::CBoundBox* pBox = (Engine::CBoundBox*)m_pPlayer->GetComponent(L"BoundBox");

	if(m_pBoundCol->ColBoundBox(pBox, m_pBox))
	{
		
		CSoundMgr::GetInstance()->StopBGM(L"prison.mp3");
		CSoundMgr::GetInstance()->PlayBGM(L"Bgm.mp3");
		((CPlayer*)m_pPlayer)->SetPos(D3DXVECTOR3(230.f, 1.f, 15.f));
		m_pManagement->SceneChange(CSceneSelector(SC_STAGE), SC_STAGE);
		CBasicCamera::m_eCamType = CAM_STATIC;
		m_pManagement->SceneChange(CSceneSelector(SC_STAGE), SC_STAGE);
		Engine::CManagement::m_iScene = SC_STAGE;
		((CPlayer*)m_pPlayer)->SetLayer(m_pManagement->GetScene(SC_STAGE)->GetLayer(1));
		return;
	}
}

void CCenterdesk::ColMonster(void)
{
	list<CGameObject*>* pPokeymon = m_pLayer->GetComponentList(L"Poketmon");

	if(pPokeymon == NULL)
		return;

	list<CGameObject*>::iterator iter = pPokeymon->begin();
	list<CGameObject*>::iterator iter_end = pPokeymon->end();

	for( ; iter != iter_end; ++iter)
	{
		Engine::CBoundBox* pBox = (Engine::CBoundBox*)(*iter)->GetComponent(L"BoundBox");
		if(m_pBoundCol->ColBoundBox(pBox, m_pPotalBox))
		{

			int a = 0;
		}
		else
		{
			((CPoketmon*)(*iter))->SetPos(D3DXVECTOR3(15.f, 0.f, 25.f));
		}

	}
}

void CCenterdesk::SetLayer(Engine::CLayer* pLayer)
{
	m_pLayer = pLayer;
}

void CCenterdesk::SetPlayer( Engine::CGameObject* pPlayer )
{
	m_pPlayer = pPlayer;
}
