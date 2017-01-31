#include "StdAfx.h"
#include "Boss.h"
#include "EarthCamera.h"
#include "BasicCamera.h"
#include "Gather.h"
#include "Firework.h"
#include "Breath.h"
#include "BoundCol.h"
#include "Stage.h"
#include "Include.h"
#include "SceneSelector.h"

CBoss::CBoss(LPDIRECT3DDEVICE9 pDevice)
: CMultiGameObject(pDevice)
, m_pLayer(NULL)
, m_pVertex(NULL)
, m_pConvertVertex(NULL)
, m_pPlayer(NULL)
, m_pTargetInfo(NULL)
, m_pBoundCol(NULL)
, m_dwPatten(0)
, m_fPattenTime(0)
, m_fSkillTime(0)
, m_bEarthThrow(false)
, m_bColCheck(false)
, m_dwType(0)
{

}

CBoss::~CBoss(void)
{
	Release();
}

HRESULT CBoss::Initialize(Engine::CLayer* pLayer)
{
	Load();

	FAILED_CHECK(AddComponent());

	m_wstrObjKey = L"Mangna";
	m_pLayer = pLayer;

	m_pVertex			=	new Engine::VTXTEX[4];
	m_pConvertVertex	=	new Engine::VTXTEX[4];

	m_pResourceMgr->GetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pVertex);
	

	m_pInfo->vScale = D3DXVECTOR3(2.f, 2.f, 2.f);

	m_pBox->Initialize(&m_pInfo->vPos, &D3DXVECTOR3(3.f, 4.f, 3.f));

	m_pCameraObserver = CCameraObserver::Create();
	m_pInfoSubject->Subscribe(m_pCameraObserver);

	m_pPlayer = dynamic_cast<CPlayer*>(m_pLayer->GetComponentList(L"Player")->back());
	m_pTargetInfo = const_cast<Engine::CTransform*>(dynamic_cast<const Engine::CTransform*>(m_pPlayer->GetComponent(L"Transform")));

	m_pStat->fHp		= 50.f;
	m_pStat->fFullHp	= 50.f;
	m_pStat->fMp		= 0.f;
	m_pStat->fFullMp	= 0.f;
	m_pStat->fSpeed		= 20.f;
	m_pStat->fAttack	= 5.f;

	m_fPattenTime = float(rand() % 5);

	return S_OK;
}

void CBoss::Update(void)
{
	if (m_dwPatten != 4 && m_pInfo->vPos.y < 5.f)
		m_pInfo->vPos.y = 5.f;

	SetDirection();

	m_pTerrainVtx = m_pManagement->GetTerrainVertex(CStage::LAYER_GAMELOGIC, L"Terrain");

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
		SetSprite(L"Stand");
	}
	if (m_wstrStatekey == L"Death")
		return;

	Inspect();

	Engine::CGameObject::Update();
	SetTransform();

	switch (m_dwPatten)
	{
	case 0:
		Patrol();
		break;

	case 1:
		Hurricane();
		break;

	case 2:
		Dash();
		break;

	case 3:
		DestroyBeam();
		break;

	case 4:
		EarthThrow();
		break;
	}

	m_pBox->Update(&m_pInfo->vPos);
}

void CBoss::Render(void)
{
	if (m_bCulling == true)
		return;

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	m_pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pResource->Render((DWORD)m_pSprite->fSpriteCnt);

	if (m_dwPatten != 4)
	{
		m_pResourceMgr->SetVtxInfo(Engine::RESOURCE_STATIC, L"Buffer RcTex", m_pConvertVertex);
		m_pHpBarTexture->Render(0);
		m_pHpBarBuffer->Render();
	}

	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	m_pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

void CBoss::Release(void)
{

	/*if(m_pStat->fHp < 0)
	{
		m_pManagement->SceneChange(CSceneSelector(SC_ENDING), SC_ENDING);
	}
	*/
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

HRESULT CBoss::AddComponent(void)
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

	// Stat
	pComponent = m_pStat = Engine::CStatus::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Status", pComponent));

	// Sprite
	pComponent = m_pSprite = Engine::CSprite::Create();
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"Sprite", pComponent));
	SetSprite(L"Stand");

	// Collision Bound
	pComponent = m_pCollisionMgr->CloneColObject(CCollisionMgr::COL_BOUND);
	m_pBoundCol = dynamic_cast<CBoundCol*>(pComponent);
	NULL_CHECK_RETURN(m_pBoundCol, E_FAIL);
	m_mapComponent.insert(MAPCOMPONENT::value_type(L"BoundCol", pComponent));

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


	return S_OK;
}

void CBoss::SetTransform(void)
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
	matWorld._42 += 15.f;
	matWorld = matBill * matWorld * (*pMatView) * (*pMatProj);

	for(size_t i = 0; i < 4; ++i)
	{
		m_pConvertVertex[i] = m_pVertex[i];

		Engine::MyTransformCoord(&m_pConvertVertex[i].vPos, 
			&m_pConvertVertex[i].vPos, 
			&matWorld);
	}
}

void CBoss::SetDirection(void)
{
	D3DXVec3TransformNormal(&m_pInfo->vDir, &g_vLook, &m_pInfo->matWorld);
	D3DXVec3Normalize(&m_pInfo->vDir, &m_pInfo->vDir);
}


void CBoss::Load(void)
{
	DWORD	dwByte = 0;

	HANDLE	hFile  = CreateFile(L"../bin/Data/MSPrite.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

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

CBoss* CBoss::Create( LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer )
{
	CBoss* pBoss = new CBoss(pDevice);

	if (FAILED(pBoss->Initialize(pLayer)))
		Engine::Safe_Delete(pBoss);

	return pBoss;
}

void CBoss::Patrol( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;
	m_fSkillTime -= fTime;

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

	if (m_pStat->fHp == m_pStat->fFullHp)
	{
		m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;
	}
	else
	{
		D3DXVECTOR3 vTargetDir = m_pTargetInfo->vPos - m_pInfo->vPos;
		Engine::MyNormalize(&vTargetDir, &vTargetDir);

		float fSearchAngle = Engine::MyDot(&vTargetDir, &D3DXVECTOR3(0.f, 0.f, 1.f));
		D3DXVECTOR3 vRight = Engine::MyCross(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(0.f, 0.f, 1.f));

		if (Engine::MyDot(&vRight, &vTargetDir) >= 0)
		{
			m_pInfo->fAngle[Engine::ANGLE_Y] = acosf(fSearchAngle);
		}
		else if(Engine::MyDot(&vRight, &vTargetDir) < 0)
		{
			fSearchAngle = 2 * D3DX_PI - acosf(fSearchAngle);
			m_pInfo->fAngle[Engine::ANGLE_Y] = fSearchAngle;
		}

		m_pInfo->Update();
		
		float fTargetDistance = Engine::MyLength(&m_pTargetInfo->vPos, &m_pInfo->vPos);

		if (fTargetDistance < 8.f)
			return;

		m_pInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime;
	}
}

void CBoss::Hurricane( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;
	m_fSkillTime -= fTime;

	SetSprite(L"Attack");
}

void CBoss::Dash( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;
	m_fSkillTime -= fTime;

	SetSprite(L"Attack2");
	m_pSprite->fSpriteSpeed = 0.5f;

	if (m_bColCheck == false && m_pSprite->fSpriteMax > 6.f)
	{
		if (m_pBoundCol->ColBoundBox((Engine::CBoundBox*)m_pPlayer->GetComponent(L"BoundBox"), m_pBox))
		{
			m_pTargetInfo->vPos += m_pInfo->vDir * m_pStat->fSpeed * fTime * 10.f;
			m_bColCheck = true;
		}
	}

	if (m_fPattenTime < 0)
	{
		m_bColCheck = false;
		SetSprite(L"Stand");
		m_fSkillTime = 5.f;
		m_fPattenTime = 2.f;
		m_dwPatten = 0;
		return;
	}	
}

void CBoss::DestroyBeam( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;
	m_fSkillTime -= fTime;

	SetSprite(L"Skill");

	if (m_fPattenTime < 0.f)
	{
		CSoundMgr::GetInstance()->PlaySound(L"Mangna3.MP3");
		m_bColCheck = false;
		SetSprite(L"Stand");
		m_fSkillTime = 5.f;
		m_fPattenTime = 2.f;
		m_dwPatten = 0;
		return;
	}

	if (m_fPattenTime > 1.5f)
	{
		m_pLayer->AddObject(L"Gather", CGather::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Gather.png", m_pInfo->vPos, m_pInfo->vDir, 2));
	}
	else
	{
		D3DXVECTOR3 vTargetDir = m_pTargetInfo->vPos - m_pInfo->vPos;
		Engine::MyNormalize(&vTargetDir, &vTargetDir);
		Engine::MyNormalize(&m_pInfo->vDir, &m_pInfo->vDir);

		float fSearchAngle = Engine::MyDot(&vTargetDir, &D3DXVECTOR3(0.f, 0.f, 1.f));
		D3DXVECTOR3 vRight = Engine::MyCross(&D3DXVECTOR3(0.f, 1.f, 0.f), &D3DXVECTOR3(0.f, 0.f, 1.f));

		if (Engine::MyDot(&vRight, &vTargetDir) >= 0)
		{
			m_pInfo->fAngle[Engine::ANGLE_Y] = acosf(fSearchAngle);
		}
		else if(Engine::MyDot(&vRight, &vTargetDir) < 0)
		{
			fSearchAngle = 2 * D3DX_PI - acosf(fSearchAngle);
			m_pInfo->fAngle[Engine::ANGLE_Y] = fSearchAngle;
		}

		D3DXVECTOR3 vTemp = m_pInfo->vPos + m_pInfo->vDir * 4.f;
		vTemp.y += 15.f;
		m_pLayer->AddObject(L"Bomb", CFirework::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Gather.png", vTemp, 10));
		m_pLayer->AddObject(L"Beam", CBreath::Create(m_pDevice, L"../bin/Resources/Texture/Etc/Gather.png", m_pInfo, m_pTargetInfo, 100, m_pLayer));
	}
	
}

void CBoss::EarthThrow( void )
{
	float fTime = m_pTimeMgr->GetTime();

	m_fPattenTime -= fTime;
	m_fSkillTime -= fTime;

	((CPlayer*)m_pPlayer)->SetState(ST_STUN);

	if (m_fPattenTime < 0.f)
	{
		CSoundMgr::GetInstance()->PlaySound(L"Earth2.MP3");
		m_bColCheck = false;
		SetSprite(L"Stand");
		m_fSkillTime = 5.f;
		m_bEarthThrow = true;

		m_pInfo->fAngle[Engine::ANGLE_X] = D3DXToRadian(0.f);
		((Engine::CTransform*)m_pPlayer->GetComponent(L"Transform"))->fAngle[Engine::ANGLE_X] = D3DXToRadian(0.f);

		m_dwPatten = 0;
		m_fPattenTime = 3.f;
		((CPlayer*)m_pPlayer)->SetState(ST_NORMAL);
	}

	if (m_fPattenTime > 1.f)
	{
		m_pInfo->vPos.y += 40.f * fTime;
		m_pInfo->fAngle[Engine::ANGLE_Y] += D3DXToRadian(20.f);

		m_pPlayer->SetPos(m_pInfo->vPos + m_pInfo->vDir * 5.f);
		((Engine::CTransform*)m_pPlayer->GetComponent(L"Transform"))->Update();
	}
	else
	{
		if (m_pTerrainVtx)
		{	
			int	iIndex = (int(m_pInfo->vPos.z) / VTXITV) * VTXCNTX + (int(m_pInfo->vPos.x) / VTXITV);

			for (int i = -15; i < 15; ++i)
			{
				for (int j = -15; j < 15; ++j)
				{
					int iCount = (i * VTXCNTX) + j;
					Engine::VTXTEX* pTemp = const_cast<Engine::VTXTEX*>(m_pTerrainVtx);
					pTemp[iIndex + iCount].vPos.y -= 0.1f;
				}	
			}
		}
		

		m_pInfo->fAngle[Engine::ANGLE_X] = D3DXToRadian(180.f);
		((Engine::CTransform*)m_pPlayer->GetComponent(L"Transform"))->fAngle[Engine::ANGLE_X] = D3DXToRadian(180.f);

		m_pInfo->vPos.y -= 160.f * fTime;
		m_pPlayer->SetPos(m_pInfo->vPos + m_pInfo->vDir * 5.f);
		((Engine::CTransform*)m_pPlayer->GetComponent(L"Transform"))->Update();
	}
}

void CBoss::Inspect( void )
{
	if (m_fPattenTime > 0.f || m_fSkillTime > 0)
		return;

	float fTargetDistance = Engine::MyLength(&m_pTargetInfo->vPos, &m_pInfo->vPos);

	if (m_pStat->fHp == m_pStat->fFullHp)
	{
		m_dwPatten = 0;
		m_fPattenTime = 2.f;

	}
	else if (fTargetDistance > 40.f && m_fSkillTime < 0)
	{
		m_fPattenTime = 3.f;
		m_dwPatten = 3;
		return;
	}

	else if (m_bEarthThrow == false && (m_pStat->fHp / m_pStat->fFullHp) < 0.3f)
	{
		CSoundMgr::GetInstance()->PlaySound(L"Mangna2.MP3");
		m_pLayer->AddObject(L"EarthCam", CEarthCamera::Create(m_pDevice, m_pInfo));
		CBasicCamera::m_eCamType = CAM_EARTH;
		m_fPattenTime = 5.f;
		m_dwPatten = 4;
		return;
	}
	else
	{
		if (fTargetDistance > 20.f)
		{
			m_fPattenTime = 2.f;
			m_dwPatten = 1;
		}
		else
		{
			m_pInfo->vPos -= m_pInfo->vDir * m_pStat->fSpeed * m_pTimeMgr->GetTime() * 5.f;
			m_fPattenTime = 2.f;
			m_dwPatten = 2;
		}
	}
}


DWORD CBoss::GetType( void )
{
	return m_dwType;
}
