#include "StdAfx.h"
#include "SingleGameObject.h"

CSingleGameObject::CSingleGameObject( LPDIRECT3DDEVICE9 pDevice )
:CGameObject(pDevice)
{

}

CSingleGameObject::~CSingleGameObject( void )
{
	Release();
}
void CSingleGameObject::Release( void )
{

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

CSingleGameObject* CSingleGameObject::Create( LPDIRECT3DDEVICE9 pDevice, wstring wstrLoadKey )
{
	CSingleGameObject* pSingle = new CSingleGameObject(pDevice);

	if (FAILED(pSingle->Initialize()))
		Engine::Safe_Delete(pSingle);

	return pSingle;
}

