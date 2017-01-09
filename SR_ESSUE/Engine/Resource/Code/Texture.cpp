#include "Texture.h"

Engine::CTexture::CTexture(LPDIRECT3DDEVICE9 pDevice)
: CResources(pDevice)
, m_dwContainerSize(0)
{

}

Engine::CTexture::~CTexture(void)
{
	Release();
}


HRESULT Engine::CTexture::LoadTexture(TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt)
{
	IDirect3DBaseTexture9*		pTexture = NULL;

	m_vecTexture.reserve(wCnt);

	TCHAR	szFullPath[MAX_PATH] = L"";

	for(size_t i = 0; i < wCnt; ++i)
	{
		wsprintf(szFullPath, wstrFilePath.c_str(), i);
		HRESULT	hr = NULL;

		switch(eTextureType)
		{
		case TEX_NORMAL:
			hr = D3DXCreateTextureFromFile(m_pDevice, szFullPath, (LPDIRECT3DTEXTURE9*)&pTexture);
			break;

		case TEX_CUBE:
			hr = D3DXCreateCubeTextureFromFile(m_pDevice, szFullPath, (LPDIRECT3DCUBETEXTURE9*)&pTexture);
			break;
		}

		FAILED_CHECK_MSG(hr, szFullPath);

		m_vecTexture.push_back(pTexture);
	}

	m_dwContainerSize = m_vecTexture.size();


	return S_OK;
}


void Engine::CTexture::Render(const DWORD& Index)
{
	if(Index >= m_dwContainerSize)
		return;

	m_pDevice->SetTexture(0, m_vecTexture[Index]);
}

void Engine::CTexture::Render(void)
{

}

void Engine::CTexture::Release(void)
{
	if((*m_pwRefCnt) == 0)
	{
		for(size_t i = 0; i < m_vecTexture.size(); ++i)
		{
			Engine::Safe_Release(m_vecTexture[i]);
		}
		m_vecTexture.clear();

		Engine::CResources::Release();
	}

	else
	{
		--(*m_pwRefCnt);
	}
}


Engine::CResources* Engine::CTexture::CloneResource(void)
{
	++(*m_pwRefCnt);

	return new CTexture(*this);
}

Engine::CTexture* Engine::CTexture::Create(LPDIRECT3DDEVICE9 pDevice, TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt)
{
	CTexture*	pTexture = new CTexture(pDevice);

	if(FAILED(pTexture->LoadTexture(eTextureType, wstrFilePath, wCnt)))
		Engine::Safe_Delete(pTexture);

	return pTexture;
}

