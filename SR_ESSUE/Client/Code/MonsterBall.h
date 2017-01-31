/*!
 * \file MonsterBall.h
 * \date 2017/01/16 22:48
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \ 투사체를 상속받는 몬스터볼 객체입니다.
*/

#include "SingleGameObject.h"
#include "TerrainCol.h"
#include "BoundCol.h"

namespace Engine
{
	class CLayer;
}

class CMonsterBall 
	: public CSingleGameObject
{
private:
	Engine::VTXCUBE*	m_pVertex;
	Engine::VTXCUBE*	m_pConvertVertex;
	DWORD				m_dwType;
	DWORD				m_dwState;
	float				m_fHeight;
	wstring				m_wstrObjkey;

	// 콜리전
	CTerrainCol*		m_pTerrainCol;
	CBoundCol*			m_pBoundCol;

	const Engine::VTXTEX*	m_pTerrainVtx;

	// 스테이지 씬
	Engine::CLayer*		m_pLayer;

private:
	HRESULT				Initialize(D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, DWORD iType = 0);
	void				SetTransform(void);
	void				SetDirection(void);
	void				Move(void);
	void				HitMove(void);
	void				ColMonster(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);
	void				SetLayer(Engine::CLayer* pLayer);
	wstring				GetObjkey(void);

public:
	static	CMonsterBall*	Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, D3DXVECTOR3 vDir, DWORD iType = 0);

private:
	explicit CMonsterBall(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CMonsterBall(void);
};
