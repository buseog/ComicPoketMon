#include "RcTerrain.h"


Engine::CRcTerrain::CRcTerrain(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{

}

Engine::CRcTerrain::~CRcTerrain(void)
{
	Release();
}


HRESULT Engine::CRcTerrain::CreateBuffer(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv)
{
	m_dwVtxSize = sizeof(VTXCOL);
	m_dwVtxCnt = wCntX * wCntZ;
	m_dwVtxFVF = VTXFVF_COL;
	m_dwTriCnt = (wCntX - 1) * (wCntZ - 1) * 2;
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	VTXCOL*		pVtxCol = NULL;

	m_pVB->Lock(0, 0 , (void**)&pVtxCol, 0);

	int	iIndex = 0;

	for(int z = 0; z < wCntZ; ++z)
	{
		for(int x = 0; x < wCntX; ++x)
		{
			iIndex = z * wCntX + x;

			pVtxCol[iIndex].vPos    = D3DXVECTOR3(float(x) * wItv, 0.f, float(z) * wItv);
			pVtxCol[iIndex].dwColor = D3DCOLOR_ARGB(255, 255, 255, 255);
		}
	}

	m_pOriginVertex = new VTXCOL[m_dwVtxCnt];
	memcpy(&m_pOriginVertex, pVtxCol, sizeof(pVtxCol));

	m_pVB->Unlock();

	INDEX32*		pIndex = NULL;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int iTriCnt = 0;

	for(int z = 0; z < wCntZ - 1; ++z)
	{
		for(int x = 0; x < wCntX - 1; ++x)
		{
			iIndex = z * wCntX + x;

			pIndex[iTriCnt]._1 = iIndex + wCntX;
			pIndex[iTriCnt]._2 = iIndex + wCntX + 1;
			pIndex[iTriCnt]._3 = iIndex + 1;

			iTriCnt++;

			pIndex[iTriCnt]._1 = iIndex + wCntX;
			pIndex[iTriCnt]._2 = iIndex + 1;
			pIndex[iTriCnt]._3 = iIndex;

			iTriCnt++;
		}
	}


	m_pIB->Unlock();

	return S_OK;
}

void Engine::CRcTerrain::Release(void)
{

}

Engine::CRcTerrain* Engine::CRcTerrain::Create(LPDIRECT3DDEVICE9 pDevice, const WORD& wCntX, const WORD& wCntZ, const WORD& wItv)
{
	CRcTerrain* pTerrain = new CRcTerrain(pDevice);

	if (FAILED(pTerrain->CreateBuffer(wCntX, wCntZ, wItv)))
		Engine::Safe_Delete(pTerrain);

	return pTerrain;
}

void Engine::CRcTerrain::Render( void )
{
	CVIBuffer::Render();
}
