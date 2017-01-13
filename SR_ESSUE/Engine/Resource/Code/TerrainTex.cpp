#include "TerrainTex.h"


Engine::CTerrainTex::CTerrainTex(LPDIRECT3DDEVICE9 pDevice)
: CVIBuffer(pDevice)
{

}

Engine::CTerrainTex::~CTerrainTex(void)
{
	Release();
}

HRESULT Engine::CTerrainTex::CreateBuffer(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv)
{

	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = wCntX * wCntZ;
	m_dwVtxFVF = VTXFVF_TEX;
	m_dwTriCnt = (wCntX - 1) * (wCntZ - 1) * 2;
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK(CVIBuffer::CreateBuffer());

	//DWORD*		pdwPixel = LoadImage();

	VTXTEX*		pVtxTex = NULL;

	m_pVB->Lock(0, 0 , (void**)&pVtxTex, 0);

	int	iIndex = 0;

	for(int z = 0; z < wCntZ; ++z)
	{
		for(int x = 0; x < wCntX; ++x)
		{
			iIndex = z * wCntX + x;

			pVtxTex[iIndex].vPos    = D3DXVECTOR3(float(x) * wItv, 
				0.f,
				float(z) * wItv);
			pVtxTex[iIndex].vTex    = D3DXVECTOR2(x / (wCntX - 1.f), z / (wCntZ - 1.f));
		}
	}

	m_pOriginVertex = new VTXTEX[m_dwVtxCnt];
	memcpy(m_pOriginVertex, pVtxTex, sizeof(pVtxTex));

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

	m_pOriginIndex = new INDEX32[m_dwTriCnt];
	memcpy(m_pOriginIndex, pIndex, m_dwIdxSize * m_dwTriCnt);

	//Engine::Safe_Delete_Array(pdwPixel);

	return S_OK;

}

DWORD* Engine::CTerrainTex::LoadImage(void)
{
	HANDLE		hFile = NULL;
	DWORD		dwByte = 0;

	hFile = CreateFile(L"../bin/Resources/Texture/Terrain/Height.bmp", GENERIC_READ, 
		0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	BITMAPFILEHEADER		fh;
	BITMAPINFOHEADER		ih;

	ReadFile(hFile, &fh, sizeof(fh), &dwByte, NULL);
	ReadFile(hFile, &ih, sizeof(ih), &dwByte, NULL);

	DWORD*	pdwPixel = new DWORD[ih.biHeight * ih.biWidth];

	ReadFile(hFile, pdwPixel, sizeof(DWORD) * ih.biHeight * ih.biWidth, &dwByte, NULL);
	CloseHandle(hFile);

	return pdwPixel;
}

Engine::CTerrainTex* Engine::CTerrainTex::Create(LPDIRECT3DDEVICE9 pDevice, const WORD& wCntX, const WORD& wCntZ, const WORD& wItv)
{
	CTerrainTex*		pTerrainTex = new CTerrainTex(pDevice);

	if(FAILED(pTerrainTex->CreateBuffer(wCntX, wCntZ, wItv)))
		Engine::Safe_Delete(pTerrainTex);

	return pTerrainTex;
}

void Engine::CTerrainTex::Release(void)
{
	
}

void Engine::CTerrainTex::Render( void )
{
	CVIBuffer::Render();
}
