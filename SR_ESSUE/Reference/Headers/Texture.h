/*!
 * \file Texture.h
 * \date 2017/01/07 2:04
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Texture_h__
#define Texture_h__

#include "Resources.h"

BEGIN(Engine)

class ENGINE_DLL CTexture
	:public CResources
{
private:
	typedef vector<IDirect3DBaseTexture9*>		VECTEXTURE;
	VECTEXTURE									m_vecTexture;

	DWORD										m_dwContainerSize;

private:
	HRESULT		LoadTexture(TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt);

public:
	void	Render(const DWORD&	Index);
	void	Render(void);
	void	Release(void);

public:
	virtual CResources* CloneResource(void);

public:
	static CTexture* Create(LPDIRECT3DDEVICE9 pDevice, TEXTURETYPE eTextureType, const wstring& wstrFilePath, const WORD& wCnt);


private:
	explicit CTexture(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CTexture(void);

};

END
#endif // Texture_h__
