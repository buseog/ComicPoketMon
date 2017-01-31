#include "StdAfx.h"
#include "Poketmon.h"

#include "Stage.h"
#include "TerrainCol.h"
#include "Action.h"

#include "BoundCol.h"
#include "Player.h"

#include "ItemParts.h"
#include "PokemonParts.h"
#include "EffectMgr.h"


CPoketmon::CPoketmon( LPDIRECT3DDEVICE9 pDevice, const wstring& wstrObjKey, Engine::CLayer* pLayer )
: CMultiGameObject(pDevice)
, m_pLayer(pLayer)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_dwPatten(0)
, m_dwType(0)
, m_fSkillTime(Engine::GetRandomFloat(10.f, 20.f))
, m_fChannel(0.f)
, m_pAttackBox(NULL)
{
	m_wstrObjKey = wstrObjKey;
}

CPoketmon::~CPoketmon( void )
{
	Release();
}

HRESULT CPoketmon::Initialize( void )
{
	Load();

	FAILED_CHECK(AddComponent());

	m_pVertex			=	new Engine::VTXTEX[4];
	m_pConvertVertex	=	new Engine::VTXTEX[4];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pVertex);

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(rand() % 360);

	m_pTargetInfo = dynamic_cast<const Engine::CTransform*>(m_pLayer->GetComponent(L"Player", L"Transform"));

	m_fPattenTime = float(rand() % 5);

	if (m_wstrObjKey == L"Ggobugi")
	{
		m_pStat->fHp		= 10.f;
		m_pStat->fFullHp	= 10.f;
		m_pStat->fMp		= 0.f;
		m_pStat->fFullMp	= 0.f;
		m_pStat->fSpeed		= 10.f;
		m_pStat->fAttack	= 2.f;
	}
	else if (m_wstrObjKey == L"Pairi")
	{
		m_pStat->fHp		= 10.f;
		m_pStat->fFullHp	= 10.f;
		m_pStat->fMp		= 0.f;
		m_pStat->fFullMp	= 0.f;
		m_pStat->fSpeed		= 10.f;
		m_pStat->fAttack	= 2.f;
	}
	else if (m_wstrObjKey == L"Picachu")
	{
		m_pStat->fHp		= 10.f;
		m_pStat->fFullHp	= 10.f;
		m_pStat->fMp		= 0.f;
		m_pStat->fFullMp	= 0.f;
		m_pStat->fSpeed		= 10.f;
		m_pStat->fAttack	= 2.f;
	}
	
	m_fAttackTime = 2.f;
	m_fSoundTime = 5.f;

	return S_OK;
}

void CPoketmon::Update( void )
{
	if(m_dwType == 1)
		Sound();

	ColBulding();

	D3DXVECTOR3 vTemp = m_pInfo->vPos + m_pInfo->vDir * 3.f;
	m_pAttackBox->Update(&vTemp);

	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	m_pResource->Update(m_wstrStatekey, &m_pInfo->matWorld, pMatView, pMatProj);

	if (m_pSprite->PlaySprite())
	{
		if (m_wstrStatekey == L"Death")
		{
			m_bDestroy = true;
			return;
		}
		SetSprite(L"Walk");
	}
	if (m_wstrStatekey == L"Death")
		return;

	D3DXMATRIX matViewProj = (*pMatView) * (*pMatProj);
	m_pZFrustum->MakePlane(&matViewProj);

	if (m_pZFrustum->IsIn(&m_pInfo->vPos) == true)
		m_bCulling = false;

	else
		m_bCulling = true;

	if(m_dwType != 99 && Engine::CManagement::m_iScene == SC_STAGE )
	{
		m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");
		m_pTerrainCol->SetColInfo(&m_pInfo->vPos, m_pTerrainVtx);

		m_fSkillTime -= m_pTimeMgr->GetTime();

		if (m_fSkillTime < 0)
		{
			m_fChannel = 1.f;
			m_fSkillTime = Engine::GetRandomFloat(10.f, 20.f);
		}

		if (m_fChannel > 0)
		{
			m_fChannel -= m_pTimeMgr->GetTime();

			if(m_wstrObjKey == L"Ggobugi")
				CEffectMgr::GetInstance()->AddEffect(Engine::EFFECT_COLOR, Engine::EMID_WATER, m_pInfo, m_pInfo->vDir);

			if(m_wstrObjKey == L"Pairi")
				CEffectMgr::GetInstance()->AddEffect(Engine::EFFECT_COLOR, Engine::EMID_FLAME, m_pInfo, m_pInfo->vDir);
			
			return;
		}

		SetDirection();

		if(ColPoketmon())
			Follow();

		switch (m_dwPatten)
		{
		case 0:
			Patrol();
			break;

		case 1:
			FollowMove();
			break;

		case 2:
			ColPlayerAttack();
			break;
		}
	}

	Engine::CGameObject::Update();
	SetTransform();

	m_pBox->Update(&m_pInfo->vPos);
}

void CPoketmon::Render( void )
{
	if (m_bCulling == true)
		return;
		
	m_pResource->Render((DWORD)m_pSprite->fSpriteCnt);

	m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pConvertVertex);

	if(m_dwType == 0)
		m_pHpBarTexture->Render(0);

	else if(m_dwType == 1)
		m_pMpBarTexture->Render(0);


	m_pHpBarBuffer->Render();

	
}

void CPoketmon::Release( void )
{

	if(m_pStat->fHp < 0)
	{
		CGameObject* pParts = CPokemonParts::Create(m_pDevice, m_pLayer, m_pInfo, m_wstrObjKey);
		m_pLayer->AddObject(L"Partsa", pParts);
	}

	if (m_pResource)
	{
		Engine::Safe_Delete(m_pResource);
	}

	if (m_pVertex)
	{
		Engine::Safe_Delete_Array(m_pVertex);
	}

	if (m_pConvertVertex)
	{
		Engine::Safe_Delete_Array(m_pConvertVertex);
	}

	if (m_pInfoSubject != NULL)
		m_pInfoSubject->UnSubscribe(m_pCameraObserver);

	Engine::Safe_Delete(m_pCameraObserver);

}

HRESULT CPoketmon::AddComponent( void )
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// BoundBox
	pComponent = m_pBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &D3DXVECTOR3(1.f, 1.5f, 1.f));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundBox", pComponent));

	// AttackBoundBox
	pComponent = m_pAttackBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &m_pInfo->vScale);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Attack BoundBox", pComponent));

	// Collision Terrain`
	
	if(Engine::CManagement::m_iScene == SC_STAGE)
	{
		pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_TERRAIN);
		m_pTerrainCol = dynamic_cast<CTerrainCol*>(pComponent);
		NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

		pComponent = m_pAction = CAction::Create(this);
		NULL_CHECK_RETURN(pComponent, E_FAIL);
		m_mapComponent.insert(MAPCOMPONENT::value_type(L"Poketmon Action", pComponent));
	}

	// Stat
	pComponent = m_pStat = Engine::CStatus::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Status", pComponent));

	// Sprite
	pComponent = m_pSprite = Engine::CSprite::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Sprite", pComponent));
	SetSprite(L"Walk");

	// Hp Buffer
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Buffer RcTex");
	m_pHpBarBuffer = dynamic_cast<Engine::CVIBuffer*>(pComponent);
	NULL_CHECK_RETURN(m_pHpBarBuffer, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"HpBar Buffer", pComponent));

	// Hp Texture
	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture HpGauge");
	m_pHpBarTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pHpBarTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"HpBar Texture", pComponent));

	pComponent = m_pResourceMgr->CloneResource(Engine::RESOURCE_STATIC, L"Texture HpGauge1");
	m_pMpBarTexture = dynamic_cast<Engine::CTexture*>(pComponent);
	NULL_CHECK_RETURN(m_pMpBarTexture, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"HpBar Texture1", pComponent));



	return S_OK;
}

void CPoketmon::SetDirection( void )
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}


CPoketmon* CPoketmon::Create( LPDIRECT3DDEVICE9 pDevice, const wstring& wstrObjKey, Engine::CLayer* pLayer)
{
	CPoketmon*		pPoketmon = new CPoketmon(pDevice, wstrObjKey, pLayer);

	if(FAILED(pPoketmon->Initialize()))
		Engine::Safe_Delete(pPoketmon);

	return pPoketmon;
}

void CPoketmon::Load( void )
{
	DWORD	dwByte = 0;

	HANDLE	hFile;

	if (m_wstrObjKey == L"Ggobugi")
	{
		hFile  = CreateFile(L"../bin/Data/SSprite.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (m_wstrObjKey == L"Pairi")
	{
		hFile  = CreateFile(L"../bin/Data/CSprite.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}
	else if (m_wstrObjKey == L"Picachu")
	{
		hFile  = CreateFile(L"../bin/Data/PSprite.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	}

	Engine::VTXCUBE*		pVtx = new Engine::VTXCUBE[8];
	Engine::CCubeObj*		pCube = Engine::CCubeObj::Create(m_pDevice);
	m_pResource = Engine::CCubeMotion::Create(m_pDevice);
	wstring wstrStateKey = L"";

	int iFrame = 0;
	while(true)
	{
		Engine::SAVEFRAME* pSave = new Engine::SAVEFRAME;
		ReadFile(hFile, pSave, sizeof(Engine::SAVEFRAME), &dwByte, NULL);

		if(dwByte == 0)
		{
			m_pResource->AddSprite(wstrStateKey, pCube);

			Engine::Safe_Delete(pSave);
			break;
		}
		TCHAR szBuf[255] = L"";
		wsprintf(szBuf, L"%s%s", pSave->wstrPartsKey.c_str(), L".dds");

		Engine::CVIBuffer* pResource = Engine::CCubeTex::Create(m_pDevice, szBuf);

		for (int i = 0; i < 8; ++i)
			pVtx[i] = pSave->VtxInfo[i];

		pResource->SetOriginVtxInfo(pVtx);
		pResource->SetVtxInfo(pVtx);

		if (iFrame == pSave->FrameKey)
		{
			pCube->AddCube(pResource);
			wstrStateKey = pSave->wstrStateKey;
		}
		else
		{
			m_pResource->AddSprite(wstrStateKey, pCube);

			iFrame = pSave->FrameKey;
			pCube = Engine::CCubeObj::Create(m_pDevice);
			pCube->AddCube(pResource);
		}
		Engine::Safe_Delete(pSave);

	}
	CloseHandle(hFile);
	Engine::Safe_Delete_Array(pVtx);
}

void CPoketmon::Follow( void )
{
	float fTime = m_pTimeMgr->GetTime();

	D3DXVECTOR3 vTargetDir = m_pTargetInfo->vPos - m_pInfo->vPos;
	Engine::MyNormalize(&vTargetDir, &vTargetDir);

	float fTargetDistance = Engine::MyLength(&m_pTargetInfo->vPos, &m_pInfo->vPos);
	float fSearchAngle = Engine::MyDot(&vTargetDir, &D3DXVECTOR3(0.f, 0.f, 1.f));
	D3DXVECTOR3 vRight = Engine::MyCross(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(0.f, 0.f, 1.f));

	float fSeeAngle = Engine::MyDot(&vTargetDir, &vTargetDir);

	if (fTargetDistance < 20.f)
	{
		// 몬스터의 시야각도 내에 들어왔는지 확인
		if(fSeeAngle > 0.5f)
		{
			m_dwPatten = 1;

			// 몬스터 각도회전
			if (Engine::MyDot(&vRight, &vTargetDir) >= 0)
			{
				m_pInfo->fAngle[Engine::ANGLE_Y] = acosf(fSearchAngle);
			}
			else if(Engine::MyDot(&vRight, &vTargetDir) < 0)
			{
				fSearchAngle = 2 * D3DX_PI - acosf(fSearchAngle);
				m_pInfo->fAngle[Engine::ANGLE_Y] = fSearchAngle;
			}
		}
		else 
		{
			m_dwPatten = 0;
			return;
		}
	}
	if (fTargetDistance < 6.f)
		m_dwPatten = 2;
}

void CPoketmon::FollowMove( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;

	D3DXVECTOR3 vTemp = m_pInfo->vPos + (m_pInfo->vDir * m_pStat->fSpeed * fTime);
	int	iIndex = (int(vTemp.z) / VTXITV) * VTXCNTX + (int(vTemp.x) / VTXITV);

	if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(rand() % 360);
		return;
	}
	else if (vTemp.x < 0 || vTemp.x > VTXCNTX - 1 * VTXITV)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(rand() % 360);
		return;
	}
	else
		m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;
}

void CPoketmon::Patrol( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;

	D3DXVECTOR3 vTemp = m_pInfo->vPos + (m_pInfo->vDir * m_pStat->fSpeed * fTime);
	int	iIndex = (int(vTemp.z) / VTXITV) * VTXCNTX + (int(vTemp.x) / VTXITV);

	if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(rand() % 360);
		return;
	}
	else if (vTemp.x < 0 || vTemp.x > VTXCNTX - 1 * VTXITV)
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(rand() % 360);
		return;
	}
	else
		m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;

	if(m_fPattenTime < 0)
	{
		m_fPattenTime = 5.f;
		m_pInfo->fAngle[Engine::ANGLE_Y] = D3DXToRadian(rand() % 360);
	}
}

void CPoketmon::SetType( DWORD dwType )
{
	m_dwType = dwType;
}

void CPoketmon::Sound( void )
{
	float fTime = m_pTimeMgr->GetTime();
	m_fSoundTime -= fTime;
	if(m_fSoundTime < 0.f)
	{
		if(m_wstrObjKey == L"Ggobugi")
			m_pSound->PlaySound(L"ccobook.mp3");

		if(m_wstrObjKey == L"Pairi")
			m_pSound->PlaySound(L"Pairi1.MP3");

		if(m_wstrObjKey == L"Picachu")
			m_pSound->PlaySound(L"Picachu2.MP3");


		m_fSoundTime = 5.f;
	}
		
}

void CPoketmon::SetTransform( void )
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

	float fPercent = m_pStat->fHp / m_pStat->fFullHp;

	if (fPercent < 0.f)
		fPercent = 0.f;

	matWorld._11 = fPercent;
	matWorld._22 = 0.3f;
	matWorld._33 = fPercent;

	memcpy(&matWorld.m[3][0], m_pInfo->matWorld.m[3], sizeof(float) * 3);
	matWorld._42 += 6.f;
	matWorld = matBill * matWorld * (*pMatView) * (*pMatProj);

	for(size_t i = 0; i < 4; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matWorld);
	}
}

void CPoketmon::ColPlayerAttack( void )
{
	Engine::CGameObject* pPlayer = m_pLayer->GetComponentList(L"Player")->back();

	Engine::CBoundBox*	pBox = (Engine::CBoundBox*)pPlayer->GetComponent(L"BoundBox");

	if(m_pBoundCol->ColBoundBox(m_pAttackBox, pBox))
	{
		float fTime = m_pTimeMgr->GetTime();
		m_fAttackTime -= fTime;
		
		if (m_fSkillTime > 0)
		{
			m_fSkillTime -= fTime;

			if (m_wstrObjKey == L"Ggobugi")
				SetSprite(L"Attack2");

			else
				SetSprite(L"Attack");

			return;
		}

		if(m_fAttackTime < 0)
		{
			
			CSoundMgr::GetInstance()->PlaySound(L"Basic_Attack.mp3");
			if (m_wstrObjKey == L"Ggobugi")
			{
				CEffectMgr::GetInstance()->AddEffect(Engine::EFFECT_COLOR, Engine::EMID_WATER, m_pInfo, m_pInfo->vDir);
				SetSprite(L"Attack2");
			}
			else
			{
				if (m_wstrObjKey == L"Pairi")
					CEffectMgr::GetInstance()->AddEffect(Engine::EFFECT_COLOR, Engine::EMID_FLAME, m_pInfo, m_pInfo->vDir);

				SetSprite(L"Attack");
			}
			((CPlayer*)pPlayer)->SetHp(m_pStat->fAttack);
			m_fAttackTime  = 2.f;
			return;
		}
	}
}


bool CPoketmon::ColPoketmon( void )
{
	list<CGameObject*>*		pPoketmon = m_pLayer->GetComponentList(L"Poketmon");

	list<CGameObject*>::iterator		iter = pPoketmon->begin();
	list<CGameObject*>::iterator		iter_end = pPoketmon->end();

	for( ; iter != iter_end; ++iter)
	{
		if((*iter) == this)
			continue;

		Engine::CBoundBox* pBox = (Engine::CBoundBox*)(*iter)->GetComponent(L"BoundBox");

		if(m_pBoundCol->ColBoundBox(m_pBox, pBox))
		{
			float fTime = m_pTimeMgr->GetTime();

			

			m_pInfo->fAngle[Engine::ANGLE_Y] -= D3DXToRadian(5.f); 
			m_pInfo->Update();
			m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;

			return false;
			//m_pInfo->vPos -= m_pInfo->vDir * m_pStat->fSpeed * fTime;

		}
	}
	return true;
}

void CPoketmon::ColBulding( void )
{
	Engine::CGameObject* pBulding = m_pLayer->GetComponentList(L"Wall")->back();

	Engine::CBoundBox* pBox = (Engine::CBoundBox*)pBulding->GetComponent(L"BoundBox");

	if(m_pBoundCol->ColBoundBox(m_pBox, pBox))
	{
		float fTime = m_pTimeMgr->GetTime();
		m_pInfo->vPos -= m_pInfo->vDir * m_pStat->fSpeed * fTime;

	}
}

DWORD CPoketmon::GetType( void )
{
	return m_dwType;
}
