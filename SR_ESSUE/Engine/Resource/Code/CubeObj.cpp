#include "CubeObj.h"
#include "VIBuffer.h"
#include "Export_Function.h"

Engine::CCubeObj::CCubeObj( LPDIRECT3DDEVICE9 pDevice )
: CResources(pDevice)
, m_pVertex(NULL)
{
	m_pVertex	= new Engine::VTXCUBE[8];
}

Engine::CCubeObj::~CCubeObj( void )
{
	Release();
}


void Engine::CCubeObj::Update( D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj )
{
	D3DXMATRIX matPrint = (*matWorld) * (*matView);

	for (size_t i = 0; i < m_vecCube.size(); ++i)
	{
		((Engine::CVIBuffer*)m_vecCube[i])->GetOriginVtxInfo(m_pVertex);

		for (int j = 0; j < 8; ++j)
		{
			Engine::MyTransformCoord(&m_pVertex[j].vPos, &m_pVertex[j].vPos, &matPrint);

			if(m_pVertex[j].vPos.z < 1.f)
				m_pVertex[j].vPos.z = 1.f;

			Engine::MyTransformCoord(&m_pVertex[j].vPos, &m_pVertex[j].vPos, matProj);
		}

		((Engine::CVIBuffer*)m_vecCube[i])->SetVtxInfo(m_pVertex);
	}
}

void Engine::CCubeObj::Render( void )
{
	for (size_t i = 0; i < m_vecCube.size(); ++i)
	{
		m_vecCube[i]->Render();
	}
}

void Engine::CCubeObj::Release( void )
{
	for (size_t i = 0 ; i < m_vecFrame.size() ; ++i)
	{
		Engine::Safe_Delete(m_vecFrame[i]);
	}
	m_vecFrame.clear();

	for (size_t i = 0 ; i < m_vecCube.size() ; ++i)
	{
		Engine::Safe_Delete(m_vecCube[i]);
	}
	m_vecCube.clear();

	if (m_pVertex)
		Engine::Safe_Delete_Array(m_pVertex);

	Engine::CResources::Release();
}

Engine::CResources* Engine::CCubeObj::CloneResource( void )
{
	return NULL;
}

void Engine::CCubeObj::AddFrame(SAVEFRAME* pSave )
{
	for (size_t i = 0 ; i < m_vecFrame.size() ; ++i)
	{
		if (m_vecFrame[i]->wstrPartsKey == pSave->wstrPartsKey)
			return;
	}

	m_vecFrame.push_back(pSave);
}

void Engine::CCubeObj::RemoveFrame( const wstring& wstrName )
{
	for (size_t i = 0 ; i < m_vecFrame.size() ; ++i)
	{
		if (m_vecFrame[i]->wstrPartsKey == wstrName)
			return;
	}
}

Engine::CCubeObj* Engine::CCubeObj::Create( LPDIRECT3DDEVICE9 pDevice )
{
	return new CCubeObj(pDevice);
}

Engine::CCubeObj::VECTORFRAME* Engine::CCubeObj::GetVecPart( void )
{
	return &m_vecFrame;
}

void Engine::CCubeObj::AddCube( Engine::CVIBuffer* pCube )
{
	m_vecCube.push_back(pCube);
}

void Engine::CCubeObj::RemoveCube( Engine::CVIBuffer* pCube )
{
	for (size_t i = 0; i < m_vecCube.size(); ++i)
	{
		
	}
}
