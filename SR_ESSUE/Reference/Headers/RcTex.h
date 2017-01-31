/*!
 * \file RcTex.h
 * \date 2017/01/07 2:22
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

#ifndef RcTex_h__
#define RcTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTex
	:public CVIBuffer
{
private:
	wstring			m_wstrTexKey;
	D3DXVECTOR3		m_vAddPos;
	int				m_iTexCount;

private:
	void			Release(void);
	
public:
	virtual HRESULT	CreateBuffer(void);
	virtual void	Render(void);
	wstring			GetKey(void);
	int				GetTexCount(void);

public:
	static CRcTex*	Create(LPDIRECT3DDEVICE9 pDevice);
	static CRcTex*	Create( LPDIRECT3DDEVICE9 pDevice, wstring _wstrTexKey, D3DXVECTOR3 vPos, int iTexCount );
private:
	explicit CRcTex(LPDIRECT3DDEVICE9 pDevice);
			CRcTex(LPDIRECT3DDEVICE9 pDevice, wstring _wstrTexKey, D3DXVECTOR3 vPos = D3DXVECTOR3(0.f, 0.f, 0.f), int iTexCount = 0);
public:
	virtual ~CRcTex(void);
};

END
#endif // RcTex_h__