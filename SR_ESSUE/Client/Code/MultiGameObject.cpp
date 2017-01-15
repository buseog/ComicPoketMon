#include "StdAfx.h"
#include "MultiGameObject.h"
#include "Resources.h"
#include "VIBuffer.h"
#include "Export_Function.h"
#include "Texture.h"
#include "Pipeline.h"
	
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

void CMultiGameObject::Update( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	Engine::VTXCUBE* pVertex			= new Engine::VTXCUBE[8];

	/*m_pDevice->SetTransform(D3DTS_VIEW, matView);
	m_pDevice->SetTransform(D3DTS_PROJECTION, matProj);*/

	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		((Engine::CVIBuffer*)m_vecVertex[i])->GetOriginVtxInfo(pVertex);

		for (int j = 0; j < 8; ++j)
		{
			Engine::MyTransformCoord(&pVertex[j].vPos, &pVertex[j].vPos,	matWorld);
			Engine::MyTransformCoord(&pVertex[j].vPos, &pVertex[j].vPos,	matView);

			if(pVertex[j].vPos.z < 1.f)
				pVertex[j].vPos.z = 1.f;

			Engine::MyTransformCoord(&pVertex[j].vPos, &pVertex[j].vPos,	matProj);
		}

		((Engine::CVIBuffer*)m_vecVertex[i])->SetVtxInfo(pVertex);
	}

	Engine::Safe_Delete_Array(pVertex);
}

void CMultiGameObject::Render( void )
{
	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		m_vecVertex[i]->Render();
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