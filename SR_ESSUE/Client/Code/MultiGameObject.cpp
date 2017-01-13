#include "StdAfx.h"
#include "MultiGameObject.h"
#include "Resources.h"
	
CMultiGameObject::CMultiGameObject( LPDIRECT3DDEVICE9 pDevice )
:CGameObject(pDevice)
{

}

CMultiGameObject::~CMultiGameObject( void )
{
	Release();
}

void CMultiGameObject::Release( void )
{
	for_each(m_vecVertex.begin(), m_vecVertex.end(), Engine::CDeleteObj());
	m_vecVertex.clear();
}



HRESULT CMultiGameObject::Initialize( void )
{
	return S_OK;
}

void CMultiGameObject::Update( void )
{
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i]->Update();
	}
}

void CMultiGameObject::Render( void )
{
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		Engine::Safe_Delete(m_vecVertex[i]);
	}
}

CMultiGameObject* CMultiGameObject::Create( LPDIRECT3DDEVICE9 pDevice, wstring wstrLoadKey )
{
	CMultiGameObject* pMulti = new CMultiGameObject(pDevice);

	if (FAILED(pMulti->Initialize()))
		Engine::Safe_Delete(pMulti);

	pMulti->LoadFile(wstrLoadKey);

	return pMulti;
}

void CMultiGameObject::LoadFile( wstring wstrLoadKey )
{

}