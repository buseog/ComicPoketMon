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
	virtual HRESULT	CreateBuffer(void);

public:
	static CRcTex*	Create(LPDIRECT3DDEVICE9 pDevice);
	void			Release(void);
	void			Render(void);

private:
	explicit CRcTex(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CRcTex(void);
};

END
#endif // RcTex_h__