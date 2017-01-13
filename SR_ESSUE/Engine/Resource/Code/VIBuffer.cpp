#include "VIBuffer.h"

Engine::CVIBuffer::CVIBuffer( LPDIRECT3DDEVICE9 pDevice )
: Engine::CResources(pDevice)
, m_pVB(NULL)
, m_pIB(NULL)
, m_pOriginVertex(NULL)
, m_pOriginIndex(NULL)
, m_dwVtxSize(0)
, m_dwVtxCnt(0)
, m_dwTriCnt(0)
, m_dwVtxFVF(0)
, m_dwIdxSize(0)
{

}

Engine::CVIBuffer::~CVIBuffer( void )
{
	Release();
}


HRESULT Engine::CVIBuffer::CreateBuffer( void )
{
	HRESULT	hr = NULL;

	hr = m_pDevice->CreateVertexBuffer(m_dwVtxSize * m_dwVtxCnt, 0, m_dwVtxFVF, 
		D3DPOOL_MANAGED, &m_pVB, NULL);
	//NULL_CHECK_RETURN_MSG(hr, E_FAIL, L"버텍스버퍼 생성실패");

	hr = m_pDevice->CreateIndexBuffer(m_dwIdxSize * m_dwTriCnt, 0, m_IdxFmt, D3DPOOL_MANAGED, &m_pIB, NULL);

	//NULL_CHECK_RETURN_MSG(hr, E_FAIL, L"인덱스버퍼 생성실패");

	return S_OK;
}

void Engine::CVIBuffer::Render( void )
{
	m_pDevice->SetStreamSource(0, m_pVB, 0, m_dwVtxSize);

	m_pDevice->SetFVF(m_dwVtxFVF);

	m_pDevice->SetIndices(m_pIB);

	m_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwVtxCnt, 0, m_dwTriCnt);
}

void Engine::CVIBuffer::Release( void )
{
	if((*m_pwRefCnt) == 0)
	{
		Engine::Safe_Release(m_pVB);
		Engine::Safe_Release(m_pIB);
		Engine::Safe_Delete_Array(m_pOriginVertex);
		Engine::Safe_Delete_Array(m_pOriginIndex);
		Engine::CResources::Release();
	}
	else
	{
		--(*m_pwRefCnt);
	}
}

Engine::CResources* Engine::CVIBuffer::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CVIBuffer(*this);
}

void Engine::CVIBuffer::SetVtxInfo(void* pVertex)
{
	void*		pOriVertex = NULL;

	m_pVB->Lock(0, 0, &pOriVertex, 0);

	memcpy(pOriVertex, pVertex, m_dwVtxSize * m_dwVtxCnt);

	m_pVB->Unlock();

}

void Engine::CVIBuffer::GetVtxInfo(void* pVertex)
{
	void*		pOriVertex = NULL;

	m_pVB->Lock(0, 0, &pOriVertex, 0);

	memcpy(pVertex, pOriVertex, m_dwVtxSize * m_dwVtxCnt);

	m_pVB->Unlock();
}	

void Engine::CVIBuffer::GetIdxInfo( void* pIndex )
{
	void*		pOriIndex = NULL;

	m_pIB->Lock(0, 0, &pOriIndex, 0);

	memcpy(pIndex, pOriIndex, m_dwIdxSize * m_dwTriCnt);

	m_pIB->Unlock();
}

void Engine::CVIBuffer::GetOriginVtxInfo( void* pVertex )
{
	memcpy(pVertex, m_pOriginVertex, m_dwVtxSize * m_dwVtxCnt);
}

void Engine::CVIBuffer::SetOriginVtxInfo( void* pVertex )
{
	memcpy(m_pOriginVertex, pVertex, m_dwVtxSize * m_dwVtxCnt);
}
