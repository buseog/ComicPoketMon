#include "StdAfx.h"
#include "SingleGameObject.h"

CSingleGameObject::CSingleGameObject( LPDIRECT3DDEVICE9 pDevice )
: CGameObject(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pTimeMgr(Engine::Get_TimeMgr())
, m_pManagement(Engine::Get_Management())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCollisionMgr(CCollisionMgr::GetInstance())
, m_pZFrustum(CZFrustum::GetInstance())
, m_pBuffer(NULL)
, m_pTexture(NULL)
, m_pCameraObserver(NULL)
, m_pBox(NULL)
{


}

CSingleGameObject::~CSingleGameObject( void )
{
	Release();
}

HRESULT CSingleGameObject::Initialize( void )
{
	return S_OK;
}

void CSingleGameObject::Update( void )
{

}

void CSingleGameObject::Render( void )
{

}

void CSingleGameObject::Release( void )
{

}
