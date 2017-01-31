#include "stdafx.h"
#include "Housing.h"
#include "Export_Function.h"
#include "CollisionMgr.h"
#include "ResourceMgr.h"
#include "Include.h"

#include "Transform.h"
#include "CameraObserver.h"
#include "InfoSubject.h"
#include "CollisionMgr.h"
#include "CubeTex.h"
#include "CubeObj.h"
#include "BoundBox.h"

CHousing::CHousing( LPDIRECT3DDEVICE9 pDevice )
:CGameObject(pDevice)
, m_pResourceMgr(Engine::Get_ResourceMgr())
, m_pInfoSubject(Engine::Get_InfoSubject())
, m_pCollisionMgr(CCollisionMgr::GetInstance())
, m_pZFrustum(CZFrustum::GetInstance())
, m_pInfo(NULL)
, m_pBox(NULL)
, m_pCameraObserver(NULL)
, m_wstrStatekey(L"")
{

}

CHousing::~CHousing( void )
{
	Release();
}

void CHousing::Release( void )
{

}

HRESULT CHousing::Initialize( void )
{

	return S_OK;
}

void CHousing::Update( void )
{

}

void CHousing::Render( void )
{
	for(size_t i = 0; i < m_vecBuffer.size(); ++i)
	{
		m_vecBuffer[i]->Render();
	}
}
