/*!
 * \file CubeTex.h
 * \date 2017/01/07 2:26
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

#ifndef CubeTex_h__
#define CubeTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class CTexture;
class ENGINE_DLL CCubeTex
	: public CVIBuffer
{
private:
	Engine::CTexture*	m_pTexture;
	wstring m_wstrKey;

public:
	wstring		GetKey(void);

	HRESULT		CreateBuffer(void);
	HRESULT		CreateBuffer(const wstring& wstrKey);

	static CCubeTex*	Create(LPDIRECT3DDEVICE9 pDevice);
	static CCubeTex*	Create(LPDIRECT3DDEVICE9 pDevice, const wstring& wstrKey);

	void	SetTexutre(void);

private:
	void Release(void);

public:
	virtual void Render(void);
	virtual CResources* CloneResource(void);

private:
	explicit CCubeTex(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CCubeTex(void);
};

END
#endif // CubeTex_h__
