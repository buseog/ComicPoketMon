/*!
 * \file RcTerrain.h
 * \date 2017/01/07 2:15
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

#ifndef RcTerrain_h__
#define RcTerrain_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcTerrain
	:public CVIBuffer
{
private:
	void Release(void);

public:
	virtual HRESULT	CreateBuffer(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
	virtual void Render( void );
	
public:
	static CRcTerrain* Create(LPDIRECT3DDEVICE9 pDevice, const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);

private:
	explicit CRcTerrain(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CRcTerrain(void);

	

};

END
#endif // RcTerrain_h__