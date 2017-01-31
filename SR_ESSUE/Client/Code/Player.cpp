#include "stdafx.h"
#include "Player.h"

#include "StatSubject.h"
#include "Stage.h"

#include "TerrainCol.h"
#include "MouseCol.h"
#include "BoundCol.h"
#include "Action.h"

#include "ItemParts.h"
#include "MonsterBall.h"
#include "Poketmon.h"
#include "PoketballUI.h"
#include "PokemonParts.h"
#include "Hit.h"
#include "Lightning.h"
#include "Flame.h"
#include "HighlightCamera.h"


CPlayer::CPlayer(LPDIRECT3DDEVICE9 pDevice)
: CMultiGameObject(pDevice)
, m_pKeyMgr(Engine::Get_KeyMgr())
, m_pStatSubject(Engine::Get_StatSubject())
, m_pTerrainCol(NULL)
, m_pMouseCol(NULL)
, m_pBoundCol(NULL)
, m_bMove(false)
, m_pInven(NULL)
, m_eState(ST_NORMAL)
{
}

CPlayer::~CPlayer(void)
{
	Release();
}

HRESULT CPlayer::Initialize(void)
{
	Load();

	FAILED_CHECK(AddComponent());

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_pAttackBox->Initialize(&m_pInfo->vPos, &D3DXVECTOR3(2.f, 2.f, 2.f));

	m_pStat->fHp		= 50.f;
	m_pStat->fFullHp	= 50.f;
	m_pStat->fMp		= 50.f;
	m_pStat->fFullMp	= 50.f;
	m_pStat->fSpeed		= 30.f;
	m_pStat->fAttack	= 4.f;
	SetSprite(L"Stand");

	m_iPoketballEA = 5;

	m_pStatSubject->AddData(DT_STATUS, m_pStat);

	m_iItem = 99;

	CreatePoketball();

	return S_OK;
}

void CPlayer::Update(void)
{
	SetDirection();
	ColBulding();

	D3DXMATRIX*		pMatView = m_pCameraObserver->GetView();
	NULL_CHECK(pMatView);

	D3DXMATRIX*		pMatProj = m_pCameraObserver->GetProj();
	NULL_CHECK(pMatProj);

	m_pResource->Update(m_wstrStatekey, &m_pInfo->matWorld, pMatView, pMatProj);

	if (m_eState == ST_STUN)
		return;

	KeyInput();

	for(int i = 0; i < m_iPoketballEA; ++i)
		m_pPoketball[i]->Update();

	if (m_pSprite->PlaySprite())
	{
		SetSprite(L"Stand");
	}

	if(Engine::CManagement::m_iScene == SC_STAGE)
	{
		m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");
		m_pTerrainCol->SetColInfo(&m_pInfo->vPos, m_pTerrainVtx);
	}

	BoundBoxSetting();

	m_pStatSubject->Notify(DT_STATUS, &m_pStat);

	Engine::CGameObject::Update();
}

void CPlayer::Render(void)
{
	m_pResource->Render((DWORD)m_pSprite->fSpriteCnt);

	for(int i = 0; i < m_iPoketballEA; ++i)
		m_pPoketball[i]->Render();
}

void CPlayer::Release(void)
{
	Engine::Safe_Delete(m_pCameraObserver);

	if (m_pResource)
	{
		Engine::Safe_Delete(m_pResource);
	}

	for(int i = 0; i < 5; ++i)
		Engine::Safe_Delete(m_pPoketball[i]);
}


void CPlayer::KeyInput(void)
{
	if (m_wstrStatekey != L"Stand" && m_wstrStatekey != L"Walk")
		return;

	float fTime = m_pTimeMgr->GetTime();

	if(m_pKeyMgr->StayKeyDown('W'))
	{
		D3DXVECTOR3 vTemp = m_pInfo->vPos + (m_pInfo->vDir * m_pStat->fSpeed * fTime);
		int	iIndex = (int(vTemp.z) / VTXITV) * VTXCNTX + (int(vTemp.x) / VTXITV);

		if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
		{
			return;
		}
		else if (vTemp.x < 0 || vTemp.x > VTXCNTX - 1 * VTXITV)
		{
			return;
		}
		else
		{
			m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;
			SetSprite(L"Walk");
		}	
	}

	if(m_pKeyMgr->StayKeyDown('S'))
	{
		D3DXVECTOR3 vTemp = m_pInfo->vPos - (m_pInfo->vDir * m_pStat->fSpeed * fTime);
		int	iIndex = (int(vTemp.z) / VTXITV) * VTXCNTX + (int(vTemp.x) / VTXITV);

		if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
		{
			return;
		}
		else if (vTemp.x < 0 || vTemp.x > VTXCNTX - 1 * VTXITV)
		{
			return;
		}
		else
		{
			m_pInfo->vPos -= m_pInfo->vDir * m_pStat->fSpeed * fTime;
			SetSprite(L"Walk");
		}	
	}

	if(m_pKeyMgr->StayKeyDown('Q'))
	{
		D3DXVECTOR3 vTemp = m_pInfo->vPos + (m_pInfo->vDir * m_pStat->fSpeed * fTime);
		int	iIndex = (int(vTemp.z) / VTXITV) * VTXCNTX + (int(vTemp.x) / VTXITV);

		if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
		{
			return;
		}
		else if (vTemp.x < 0 || vTemp.x > VTXCNTX - 1 * VTXITV)
		{
			return;
		}
		else
		{
			D3DXVECTOR3 vRight;
			memcpy(&vRight, &m_pInfo->matWorld._11, sizeof(D3DXVECTOR3));
			m_pInfo->vPos -= vRight * m_pStat->fSpeed * fTime;
			SetSprite(L"Walk");
		}	
	}

	if(m_pKeyMgr->StayKeyDown('E'))
	{
		D3DXVECTOR3 vTemp = m_pInfo->vPos - (m_pInfo->vDir * m_pStat->fSpeed * fTime);
		int	iIndex = (int(vTemp.z) / VTXITV) * VTXCNTX + (int(vTemp.x) / VTXITV);

		if (iIndex < 0 || (iIndex + VTXCNTX) > VTXCNTX * VTXCNTZ)
		{
			return;
		}
		else if (vTemp.x < 0 || vTemp.x > VTXCNTX - 1 * VTXITV)
		{
			return;
		}
		else
		{
			D3DXVECTOR3 vRight;
			memcpy(&vRight, &m_pInfo->matWorld._11, sizeof(D3DXVECTOR3));
			m_pInfo->vPos += vRight * m_pStat->fSpeed * fTime;
			SetSprite(L"Walk");
		}	
	}

	if(m_pKeyMgr->StayKeyDown('A'))
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] -= D3DXToRadian(90.f) * fTime;
	}

	if(m_pKeyMgr->StayKeyDown('D'))
	{
		m_pInfo->fAngle[Engine::ANGLE_Y] += D3DXToRadian(90.f) * fTime;
	}

	if(m_pKeyMgr->StayKeyDown(VK_SPACE))
	{
		((CAction*)m_pAction)->JumpMove();
	}

	if(m_pKeyMgr->KeyDown('Z'))
	{
		
		if(m_iItem == 99)
			SetSprite(L"Attack2");

		else if(m_iItem == 0)
			SetSprite(L"Attack3");

		else if(m_iItem == 1)
		{
			D3DXVECTOR3 vTemp = m_pInfo->vPos + m_pInfo->vDir * m_pStat->fSpeed * m_pTimeMgr->GetTime() * 4.f;
			m_pLayer->AddObject(L"FlameEffect", CFlame::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Flame.png", vTemp));
			SetSprite(L"Attack4");
		}

		else if(m_iItem == 2)
		{
			D3DXVECTOR3 vTemp = m_pInfo->vPos + m_pInfo->vDir * m_pStat->fSpeed * m_pTimeMgr->GetTime() * 4.f;
			m_pLayer->AddObject(L"LightningEffect", CLightning::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Lightning.png", vTemp));
			SetSprite(L"Attack5");
		}
		ColPoketmon();
	}

	if(m_pKeyMgr->KeyDown('V'))
	{
		if(m_iPoketballEA < 5)
		{
			SetSprite(L"JubJub");
			ColMonsterball();
		}
	}

	if(m_pKeyMgr->KeyDown('B'))
	{
		SetSprite(L"JubJub");
		ColItem();
	}



	if (m_pKeyMgr->KeyDown('X'))
	{
		if(m_iPoketballEA > 0)
		{
			--m_iPoketballEA;
			SetSprite(L"Attack");

			D3DXVECTOR3 vRight = Engine::MyCross(&D3DXVECTOR3(0.f, 1.f, 0.f), &m_pInfo->vDir);
			Engine::MyNormalize(&vRight, &vRight);

			D3DXVECTOR3 vTemp = m_pInfo->vPos + (vRight * 2.f);
			vTemp.y += 4.f;
			CMonsterBall* pBall = CMonsterBall::Create(m_pDevice, vTemp, m_pInfo->vDir);
			pBall->SetLayer(m_pLayer);
			m_pLayer->AddObject(L"Missile", pBall);
		}
	}

	if (m_pKeyMgr->KeyDown('C'))
	{
		if(m_iPoketballEA > 0)
		{
			--m_iPoketballEA;
			SetSprite(L"Attack");

			D3DXVECTOR3 vRight = Engine::MyCross(&D3DXVECTOR3(0.f, 1.f, 0.f), &m_pInfo->vDir);
			Engine::MyNormalize(&vRight, &vRight);

			D3DXVECTOR3 vTemp = m_pInfo->vPos + (vRight * 2.f);
			vTemp.y += 4.f;
			CMonsterBall* pBall = CMonsterBall::Create(m_pDevice, vTemp, m_pInfo->vDir, 1);
			pBall->SetLayer(m_pLayer);
			m_pLayer->AddObject(L"Missile", pBall);
		}
	}
	if(m_pKeyMgr->KeyDown('1'))
	{
		m_pStat->fHp -= 5.f;
		SetSprite(L"Death");
	}

	if(m_pKeyMgr->KeyDown('2'))
	{
		m_pStat->fMp -= 5.f;
	}

	if(m_pKeyMgr->KeyDown('3'))
	{
		SetSprite(L"Skill");
		ColPoketmon();
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

HRESULT CPlayer::AddComponent(void)
{
	Engine::CComponent*		pComponent = NULL;

	// Transform
	pComponent = m_pInfo = Engine::CTransform::Create(g_vLook);
	m_pInfo->vScale = D3DXVECTOR3(1.f, 1.f, 1.f);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Transform", pComponent));

	// BoundBox
	pComponent = m_pBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &m_pInfo->vScale);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundBox", pComponent));

	// BoundBox
	pComponent = m_pAttackBox = Engine::CBoundBox::Create(&m_pInfo->vPos, &m_pInfo->vScale);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"AttackBoundBox", pComponent));


	// Collision Terrain
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_TERRAIN);
	m_pTerrainCol = dynamic_cast<CTerrainCol*>(pComponent);
	NULL_CHECK_RETURN(m_pTerrainCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"TerrainCol", pComponent));

	// Collision Bound
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_BOUND);
	m_pBoundCol = dynamic_cast<CBoundCol*>(pComponent);
	NULL_CHECK_RETURN(m_pBoundCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundCol", pComponent));

	// Action
	pComponent = m_pAction = CAction::Create(this);
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Player Action", pComponent));

	// Stat
	pComponent = m_pStat = Engine::CStatus::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Status", pComponent));

	// Sprite
	pComponent = m_pSprite = Engine::CSprite::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Sprite", pComponent));
	SetSprite(L"Stand");

	return S_OK;
}

void CPlayer::Move(void)
{
	D3DXVECTOR3		vDir;
	vDir = m_vDestPos - m_pInfo->vPos;

	float fDistance = D3DXVec3Length(&vDir);
	D3DXVec3Normalize(&vDir, &vDir);

	m_pInfo->vPos += vDir * m_pStat->fSpeed * m_pTimeMgr->GetTime();

	if(fDistance < 1.f)
		m_bMove = false;
}

void CPlayer::Load( void )
{
	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(L"../bin/Data/TSPrite.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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

void CPlayer::SetLayer( Engine::CLayer* pLayer )
{
	m_pLayer = pLayer;
}

void CPlayer::SetInven(Engine::CGameObject* Inven)
{
	m_pInven = Inven;
}

void CPlayer::ItemEquip(int Item)
{
	m_iItem = Item;
}

void CPlayer::ItemUnequip(void)
{
	m_iItem = 99;
}

void CPlayer::PoketEquip( int Type )
{
	Engine::CGameObject* pPoketMon = NULL;
	switch(Type)
	{
	case 0:
		pPoketMon = CPoketmon::Create(m_pDevice, L"Ggobugi", m_pLayer);
		break;
	case 1:
		pPoketMon = CPoketmon::Create(m_pDevice, L"Pairi", m_pLayer);
		break;
	case 2:
		pPoketMon = CPoketmon::Create(m_pDevice, L"Picachu", m_pLayer);
		break;
	}

	((CPoketmon*)pPoketMon)->SetPos(m_pInfo->vPos);
	((CPoketmon*)pPoketMon)->SetType(true);
	m_pManagement->GetScene(Engine::CManagement::m_iScene)->GetLayer(1)->AddObject(L"Poketmon", pPoketMon);

	if(Engine::CManagement::m_iScene == SC_CENTER)
		((CPoketmon*)pPoketMon)->SetType(99);
		
	++m_iPoketballEA;
	//m_pLayer->AddObject(L"Poketmon", pPoketMon);
	
}

void CPlayer::ColBulding( void )
{
	Engine::CGameObject* pBulding = m_pLayer->GetComponentList(L"Wall")->back();

	Engine::CBoundBox* pBox = (Engine::CBoundBox*)pBulding->GetComponent(L"BoundBox");

	if(m_pBoundCol->ColBoundBox(m_pBox, pBox))
	{
		float fTime = m_pTimeMgr->GetTime();
		m_pInfo->vPos -= m_pInfo->vDir * m_pStat->fSpeed * fTime;
		
	}
}

void CPlayer::SetStage( SCENEID ID )
{
	m_eStage = ID;
}


void CPlayer::BoundBoxSetting( void )
{
	m_pBox->Update(&m_pInfo->vPos);

	D3DXVECTOR3 vTemp = m_pInfo->vPos + m_pInfo->vDir * 2.f;
	m_pAttackBox->Update(&vTemp);
}

void CPlayer::ColBoss( void )
{

}

void CPlayer::ColPoketmon( void )
{
	list<CGameObject*>* pMonster = m_pLayer->GetComponentList(L"Poketmon");

	list<CGameObject*>::iterator iter = pMonster->begin();
	list<CGameObject*>::iterator iter_end = pMonster->end();

	for( ; iter != iter_end; ++iter)
	{
		Engine::CBoundBox* pBox = (Engine::CBoundBox*)(*iter)->GetComponent(L"BoundBox");

		if(m_pBoundCol->ColBoundBox(pBox, m_pAttackBox))
		{
			m_pLayer->AddObject(L"HitEffect", CHit::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Blood.png", m_pInfo->vPos, m_pInfo->vDir));
			CSoundMgr::GetInstance()->PlaySound(L"Basic_Attack.mp3");
			((CMultiGameObject*)(*iter))->SetHp(m_pStat->fAttack);
		
			if(((CMultiGameObject*)(*iter))->GetHp() < 0)
			{
				if (m_wstrStatekey == L"Skill")
				{ 
					m_pLayer->AddObject(L"HighlightCam", CHighlightCamera::Create(m_pDevice, m_pInfo));
					CBasicCamera::m_eCamType = CAM_HIRITE;
				}
				if(((CMultiGameObject*)(*iter))->GetObjKey() == L"Ggobugi")
					CSoundMgr::GetInstance()->PlaySound(L"ccobook_hit.MP3");

				if(((CMultiGameObject*)(*iter))->GetObjKey() == L"Pairi")
					CSoundMgr::GetInstance()->PlaySound(L"Pairi0.MP3");

				if(((CMultiGameObject*)(*iter))->GetObjKey() == L"Picachu")
					CSoundMgr::GetInstance()->PlaySound(L"Picachu1.MP3");

				((CMultiGameObject*)(*iter))->SetSprite(L"Death");
			}
			return;
			
		}
	}
}

void CPlayer::ColMonsterball( void )
{
	list<CGameObject*>* pMonsterball = m_pLayer->GetComponentList(L"Missile");

	list<CGameObject*>::iterator iter = pMonsterball->begin();
	list<CGameObject*>::iterator iter_end = pMonsterball->end();

	for( ; iter != iter_end; ++iter)
	{
		Engine::CBoundBox* pBox = (Engine::CBoundBox*)(*iter)->GetComponent(L"BoundBox");

		if(m_pBoundCol->ColBoundBox(pBox, m_pBox))
		{
			if(((CMonsterBall*)(*iter))->GetObjkey() == L"Monsterball")
			{
				++m_iPoketballEA;
				(*iter)->SetDestroy();
				return;
			}
			else
			{
				((CInven*)m_pInven)->AddPoketmon(((CMonsterBall*)(*iter))->GetObjkey());
				(*iter)->SetDestroy();
				return;
			}
			

		}
	}

}

void CPlayer::SetState( STATEID eState )
{
	m_eState = eState;
}

void CPlayer::CreatePoketball( void )
{
	for(int i = 0; i < 5; ++i)
	{
		m_pPoketball[i] = CPoketballUI::Create(m_pDevice);
		((CPoketballUI*)m_pPoketball[i])->SetPos(D3DXVECTOR3(220.f + i * 60, 560.f, 0.f));
	}
}

void CPlayer::ColItem( void )
{
	list<CGameObject*>* pItem = m_pLayer->GetComponentList(L"Partsa");

	list<CGameObject*>::iterator iter = pItem->begin();
	list<CGameObject*>::iterator iter_end = pItem->end();

	for( ; iter != iter_end; ++iter)
	{
		Engine::CBoundBox* pBox = (Engine::CBoundBox*)(*iter)->GetComponent(L"BoundBox");

		if(m_pBoundCol->ColBoundBox(pBox, m_pBox))
		{	
			((CInven*)m_pInven)->AddItem(((CPokemonParts*)(*iter))->GetObjkey());
			(*iter)->SetDestroy();
			return;
		}
	}
}
