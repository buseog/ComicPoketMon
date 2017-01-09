#include "RcCol.h"

Engine::CRcCol::CRcCol( LPDIRECT3DDEVICE9 pDevice )
: CVIBuffer(pDevice)
{

}

Engine::CRcCol::~CRcCol( void )
{
	Release();
}

void Engine::CRcCol::Release( void )
{

}

HRESULT Engine::CRcCol::CreateBuffer( void )
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = 6;
	m_dwVtxFVF = VTXFVF_COL;
	m_dwTriCnt = 2;
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL*		pVtxCol = NULL;

	m_pVB->Lock(0, 0, (void**)&pVtxCol, 0);

	pVtxCol[0].vPos = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxCol[0].dwColor = D3DCOLOR_ARGB(255, 255, 0, 0);

	pVtxCol[1].vPos = D3DXVECTOR3(1.f, 1.f, 0.f);
	pVtxCol[1].dwColor = D3DCOLOR_ARGB(255, 0, 255, 0);

	pVtxCol[2].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxCol[2].dwColor = D3DCOLOR_ARGB(255, 0, 0, 255);



	pVtxCol[3].vPos = D3DXVECTOR3(-1.f, 1.f, 0.f);
	pVtxCol[3].dwColor = D3DCOLOR_ARGB(255, 125, 0, 0);

	pVtxCol[4].vPos = D3DXVECTOR3(1.f, -1.f, 0.f);
	pVtxCol[4].dwColor = D3DCOLOR_ARGB(255, 125, 255, 0);

	pVtxCol[5].vPos = D3DXVECTOR3(-1.f, -1.f, 0.f);
	pVtxCol[5].dwColor = D3DCOLOR_ARGB(255, 0, 125, 255);

	m_pOriginVertex = new VTXCOL[m_dwVtxCnt];
	memcpy(&m_pOriginVertex, pVtxCol, sizeof(pVtxCol));
	m_pVB->Unlock();

	return S_OK;
}

void Engine::CRcCol::Render( void )
{
	CVIBuffer::Render();
}

Engine::CRcCol* Engine::CRcCol::Create( LPDIRECT3DDEVICE9 pDevice )
{
	CRcCol*		pRcCol = new CRcCol(pDevice);

	if (FAILED(pRcCol->CreateBuffer()))
		Engine::Safe_Delete(pRcCol);

	return pRcCol;
}

