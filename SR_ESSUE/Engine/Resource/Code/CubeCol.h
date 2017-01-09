/*!
 * \file CubeCol.h
 * \date 2017/01/09 0:26
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef CubeCol_h__
#define CubeCol_h__

#include "VIBuffer.h"

class CCubeCol
	:public Engine::CVIBuffer
{
private:
	virtual HRESULT	CreateBuffer(D3DXVECTOR3 vScale, DWORD dwColor);

public:
	void			Release(void);
	void			Render(void);

public:
	static CCubeCol*	Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vScale, DWORD dwColor);

private:
	explicit CCubeCol(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCubeCol(void);
};

#endif // CubeCol_h__