#include "StdAfx.h"
#include "MultiGameObject.h"
#include "Export_Function.h"
#include "CollisionMgr.h"
#include "enum.h"
#include "CameraObserver.h"
#include "Transform.h"
CMultiGameObject::CMultiGameObject( LPDIRECT3DDEVICE9 pDevice )
:CGameObject(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pManagement(Engine::Get_Management())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCollisionMgr(CCollisionMgr::GetInstance())
, m_pZFrustum(CZFrustum::GetInstance())
, m_pInfo(NULL)
, m_pStat(NULL)
, m_pSprite(NULL)
, m_pBox(NULL)
, m_pResource(NULL)
, m_pTerrainVtx(NULL)
, m_pCameraObserver(NULL)
, m_wstrStatekey(L"")
, m_pSound(CSoundMgr::GetInstance())
{

}

CMultiGameObject::~CMultiGameObject( void )
{
	Release();
}

void CMultiGameObject::Release( void )
{
	
}

HRESULT CMultiGameObject::Initialize( void )
{
	return S_OK;
}

void CMultiGameObject::Update( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
}

void CMultiGameObject::Render( void )
{
	
}

void CMultiGameObject::LoadFile( wstring wstrLoadKey )
{

}

void CMultiGameObject::SetPos( D3DXVECTOR3 vPos )
{
	m_pInfo->vPos = vPos;
}
void CMultiGameObject::SetHp( float Damage )
{
	m_pStat->fHp -= Damage;
}

void CMultiGameObject::SetSprite( wstring wstrStateKey )
{
	if (m_wstrStatekey == wstrStateKey)
		return;

	m_wstrStatekey = wstrStateKey;
	m_pSprite->fSpriteCnt = 0.f;
	m_pSprite->fSpriteMax = (float)m_pResource->GetSpriteCount(m_wstrStatekey);
	
	if (wstrStateKey == L"Attack" || wstrStateKey == L"Attack2" || wstrStateKey == L"Attack3" ||
		wstrStateKey == L"Attack4")
	{
		m_pSprite->fSpriteSpeed = 2.f;
	}
	else if (wstrStateKey == L"Skill" || wstrStateKey == L"Death")
	{
		m_pSprite->fSpriteSpeed = 0.5f;
	}
	else
		m_pSprite->fSpriteSpeed = 1.f;
}

std::wstring CMultiGameObject::GetObjKey( void )
{
	return m_wstrObjKey;
}

DWORD CMultiGameObject::GetType( void )
{
	return 0;
}

float CMultiGameObject::GetHp( void )
{
	return m_pStat->fHp;
}