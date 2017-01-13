#include "CubeCol.h"

Engine::CCubeCol::CCubeCol( LPDIRECT3DDEVICE9 pDevice )
:CVIBuffer(pDevice)
{

}

Engine::CCubeCol::~CCubeCol( void )
{
	Release();
}

HRESULT Engine::CCubeCol::CreateBuffer( void )
{
	m_dwVtxSize = sizeof(Engine::VTXCOL);
	m_dwVtxCnt = 8;
	m_dwVtxFVF = Engine::VTXFVF_COL;
	m_dwTriCnt = 12;
	m_dwIdxSize = sizeof(Engine::INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	CVIBuffer::CreateBuffer();

	DWORD Red = D3DCOLOR_ARGB(255, 255, 0, 0);
	DWORD Green = D3DCOLOR_ARGB(255, 0, 255, 0);
	DWORD Blue = D3DCOLOR_ARGB(255, 0, 0, 255);

	Engine::VTXCOL* pVtxCubeCol = NULL;

	m_pVB->Lock(0,0,(void**)&pVtxCubeCol,0);

	pVtxCubeCol[0].vPos = D3DXVECTOR3(-1.f, 1.f, -1.f);
	pVtxCubeCol[0].dwColor = Red;

	pVtxCubeCol[1].vPos = D3DXVECTOR3(1.f, 1.f ,-1.f);
	pVtxCubeCol[1].dwColor = Red;

	pVtxCubeCol[2].vPos = D3DXVECTOR3(1.f, -1.f ,-1.f);
	pVtxCubeCol[2].dwColor = Green;

	pVtxCubeCol[3].vPos = D3DXVECTOR3(-1.f, -1.f ,-1.f);
	pVtxCubeCol[3].dwColor = Green;

	pVtxCubeCol[4].vPos = D3DXVECTOR3(-1.f, 1.f ,1.f);
	pVtxCubeCol[4].dwColor = Blue;

	pVtxCubeCol[5].vPos = D3DXVECTOR3(1.f, 1.f ,1.f);
	pVtxCubeCol[5].dwColor = Blue;

	pVtxCubeCol[6].vPos = D3DXVECTOR3(1.f, -1.f ,1.f);
	pVtxCubeCol[6].dwColor = Red;

	pVtxCubeCol[7].vPos = D3DXVECTOR3(-1.f, -1.f ,1.f);
	pVtxCubeCol[7].dwColor = Green;

	m_pOriginVertex = new VTXCOL[m_dwVtxCnt];
	memcpy(m_pOriginVertex, pVtxCubeCol, m_dwVtxSize * m_dwVtxCnt);

	m_pVB->Unlock();

	Engine::INDEX32* pIndex = NULL;
	m_pIB->Lock(0,0,(void**)&pIndex,0);

	//x
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 5;
	pIndex[0]._3 = 6;

	pIndex[1]._1 = 1;
	pIndex[1]._2 = 6;
	pIndex[1]._3 = 2;

	// x-
	pIndex[2]._1 = 4;
	pIndex[2]._2 = 0;
	pIndex[2]._3 = 3;

	pIndex[3]._1 = 4;
	pIndex[3]._2 = 3;
	pIndex[3]._3 = 7;

	// y+
	pIndex[4]._1 = 4;
	pIndex[4]._2 = 5;
	pIndex[4]._3 = 1;

	pIndex[5]._1 = 4;
	pIndex[5]._2 = 1;
	pIndex[5]._3 = 0;

	// y-
	pIndex[6]._1 = 3;
	pIndex[6]._2 = 2;
	pIndex[6]._3 = 6;

	pIndex[7]._1 = 3;
	pIndex[7]._2 = 6;
	pIndex[7]._3 = 7;

	// z+
	pIndex[8]._1 = 7;
	pIndex[8]._2 = 6;
	pIndex[8]._3 = 5;

	pIndex[9]._1 = 7;
	pIndex[9]._2 = 5;
	pIndex[9]._3 = 4;

	// z-
	pIndex[10]._1 = 0;
	pIndex[10]._2 = 1;
	pIndex[10]._3 = 2;

	pIndex[11]._1 = 0;
	pIndex[11]._2 = 2;
	pIndex[11]._3 = 3;

	m_pIB->Unlock();

	m_pOriginIndex = new INDEX32[m_dwTriCnt];
	memcpy(m_pOriginIndex, pIndex, m_dwIdxSize * m_dwTriCnt);


	return S_OK;
}

void Engine::CCubeCol::Release( void )
{
	
}

void Engine::CCubeCol::Render( void )
{
	CVIBuffer::Render();
}

Engine::CCubeCol* Engine::CCubeCol::Create( LPDIRECT3DDEVICE9 pDevice)
{
	CCubeCol* pCubeCol = new CCubeCol(pDevice);

	if (FAILED(pCubeCol->CreateBuffer()))
		Engine::Safe_Delete(pCubeCol);

	return pCubeCol;
}