#include "TriCol.h"

Engine::CTriCol::CTriCol( LPDIRECT3DDEVICE9 pDevice )
: CVIBuffer(pDevice)
{

}

Engine::CTriCol::~CTriCol( void )
{
	Release();
}


void Engine::CTriCol::Release( void )
{
	CVIBuffer::Release();
}

HRESULT Engine::CTriCol::CreateBuffer( void )
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 3;
	m_dwVtxFVF = VTXFVF_COL;
	m_dwTriCnt = 1;
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL*		pVtxCol = NULL;

 	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPos = D3DXVECTOR3(0.f, 1.f, 0.f);
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[2].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);

	m_pOriginVertex = new VTXCOL[m_dwVtxCnt];
	memcpy(m_pOriginVertex, pVtxCol, sizeof(pVtxCol));

	m_pVB->Unlock();

	return S_OK;
}

void Engine::CTriCol::Render( void )
{
	CVIBuffer::Render();
}

Engine::CTriCol* Engine::CTriCol::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CTriCol*	pTriCol = new CTriCol(pDevice);

	if (FAILED(pTriCol->CreateBuffer()))
		Engine::Safe_Delete(pTriCol);

	return pTriCol;
}