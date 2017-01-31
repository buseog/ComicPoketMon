/*!
 * \file TerrainCol.h
 * \date 2017/01/14 22:35
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

#ifndef TerrainCol_h__
#define TerrainCol_h__

#include "Collision.h"

class CTerrainCol
	:public Engine::CCollision
{
private:
	D3DXVECTOR3*				m_pPos;
	const Engine::VTXTEX*		m_pTerrainVtx;
	bool						m_bStepOnTerrain;

private:
	void Release(void);

public:
	void SetColInfo(D3DXVECTOR3* pPos, const Engine::VTXTEX* pTerrainTex);

public:
	virtual void Update(void);
	virtual Engine::CCollision* Clone(void);

public:
	static CTerrainCol* Create(void);
	bool	GetColTerrainStat(void);

private:
	CTerrainCol(void);

public:
	virtual ~CTerrainCol(void);
};

#endif // TerrainCol_h__