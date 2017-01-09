#include "stdafx.h"
#include "CubeCol.h"
#include "Engine_Include.h"


CCubeCol::CCubeCol( LPDIRECT3DDEVICE9 pDevice )
:CVIBuffer(pDevice)
{

}

CCubeCol::~CCubeCol( void )
{
	Release();
}

HRESULT CCubeCol::CreateBuffer( D3DXVECTOR3 vScale, DWORD dwColor )
{
	m_dwVtxSize = sizeof(Engine::VTXCUBECOL);
	m_dwVtxCnt = 8;
	m_dwVtxFVF = Engine::VTXFVF_CUBECOL;
	m_dwTriCnt = 12;
	m_dwIdxSize = sizeof(Engine::INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	CVIBuffer::CreateBuffer();

	Engine::VTXCUBECOL* pVtxCubeCol = NULL;

	m_pVB->Lock(0,0,(void**)&pVtxCubeCol,0);

	pVtxCubeCol[0].vPos = D3DXVECTOR3(-1.f * vScale.x, 1.f * vScale.y,-1.f * vScale.z);
	pVtxCubeCol[0].dwColor = dwColor;

	pVtxCubeCol[1].vPos = D3DXVECTOR3(1.f * vScale.x, 1.f * vScale.y ,-1.f * vScale.z);
	pVtxCubeCol[1].dwColor = dwColor;

	pVtxCubeCol[2].vPos = D3DXVECTOR3(1.f * vScale.x, -1.f * vScale.y ,-1.f * vScale.z);
	pVtxCubeCol[2].dwColor = dwColor;

	pVtxCubeCol[3].vPos = D3DXVECTOR3(-1.f * vScale.x, -1.f * vScale.y ,-1.f * vScale.z);
	pVtxCubeCol[3].dwColor = dwColor;

	pVtxCubeCol[4].vPos = D3DXVECTOR3(-1.f * vScale.x, 1.f * vScale.y ,1.f * vScale.z);
	pVtxCubeCol[4].dwColor = dwColor;

	pVtxCubeCol[5].vPos = D3DXVECTOR3(1.f * vScale.x, 1.f * vScale.y ,1.f * vScale.z);
	pVtxCubeCol[5].dwColor = dwColor;

	pVtxCubeCol[6].vPos = D3DXVECTOR3(1.f * vScale.x, -1.f * vScale.y ,1.f * vScale.z);
	pVtxCubeCol[6].dwColor = dwColor;

	pVtxCubeCol[7].vPos = D3DXVECTOR3(-1.f * vScale.x, -1.f * vScale.y ,1.f * vScale.z);
	pVtxCubeCol[7].dwColor = dwColor;

	m_pVB->Unlock();

	Engine::INDEX32* pIndex = NULL;
	m_pIB->Lock(0,0,(void**)&pIndex,0);

	//x
	pIndex[0]._1 = 2;
	pIndex[0]._2 = 1;
	pIndex[0]._3 = 5;

	pIndex[1]._1 = 2;
	pIndex[1]._2 = 5;
	pIndex[1]._3 = 6;

	pIndex[2]._1 = 7;
	pIndex[2]._2 = 4;
	pIndex[2]._3 = 0;

	pIndex[3]._1 = 7;
	pIndex[3]._2 = 0;
	pIndex[3]._3 = 3;

	//y
	pIndex[4]._1 = 0;
	pIndex[4]._2 = 4;
	pIndex[4]._3 = 5;

	pIndex[5]._1 = 0;
	pIndex[5]._2 = 5;
	pIndex[5]._3 = 1;

	pIndex[6]._1 = 7;
	pIndex[6]._2 = 3;
	pIndex[6]._3 = 2;

	pIndex[7]._1 = 7;
	pIndex[7]._2 = 2;
	pIndex[7]._3 = 6;

	//z

	pIndex[8]._1 = 7;
	pIndex[8]._2 = 5;
	pIndex[8]._3 = 4;

	pIndex[9]._1 = 7;
	pIndex[9]._2 = 6;
	pIndex[9]._3 = 5;

	pIndex[10]._1 = 3;
	pIndex[10]._2 = 0;
	pIndex[10]._3 = 1;

	pIndex[11]._1 = 3;
	pIndex[11]._2 = 1;
	pIndex[11]._3 = 2;


	m_pIB->Unlock();


	return S_OK;
}

void CCubeCol::Release( void )
{

}

void CCubeCol::Render( void )
{
	CVIBuffer::Render();
}

CCubeCol* CCubeCol::Create( LPDIRECT3DDEVICE9 pDevice , D3DXVECTOR3 vScale, DWORD dwColor)
{
	CCubeCol* pCubeCol = new CCubeCol(pDevice);

	if (FAILED(pCubeCol->CreateBuffer(vScale, dwColor)))
		Engine::Safe_Delete(pCubeCol);

	return pCubeCol;
}