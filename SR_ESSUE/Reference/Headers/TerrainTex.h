/*!
 * \file TerrainTex.h
 * \date 2017/01/07 2:24
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

#ifndef TerrainTex_h__
#define TerrainTex_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTerrainTex
	: public CVIBuffer
{
private:
	void	Release(void);
	DWORD*	LoadImage(void);

public:
	virtual HRESULT	CreateBuffer(const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
	virtual	void	Render(void);

public:
	static Engine::CTerrainTex*	 Create(LPDIRECT3DDEVICE9 pDevice, const WORD& wCntX, const WORD& wCntZ, const WORD& wItv);
	

private:
	explicit CTerrainTex(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CTerrainTex(void);

};

END
#endif // TerrainTex_h__
