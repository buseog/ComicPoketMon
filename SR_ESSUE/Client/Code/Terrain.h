#ifndef Terrain_h__
#define Terrain_h__

#include "SingleGameObject.h"
#include "ZQuadTree.h"

class CTerrain 
	: public CSingleGameObject
{
	// 컬링용
private:
	int		m_IBCX;	// 인덱스 버퍼 가로
	int		m_ICBY;	// 인덱스 버퍼 높이
	int		m_IBCZ;	// 인덱스 버퍼 세로

	D3DXVECTOR3	m_vScale; // 스케일
	LPDIRECT3DVERTEXBUFFER9	m_pVB;	// 버텍스버퍼
	LPDIRECT3DINDEXBUFFER9	m_pIB;	// 인덱스버퍼

	int				m_iTriangles;	// 출력할 삼각형수
	CZQuadTree*		m_pQuadTree;	// 쿼드트리
	
public:
	HRESULT		BuildQuadTree(void);


private:
	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;

private:
	HRESULT				Initialize(void);
	void				DataLoad(void);
	void				SetTransform(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);

	virtual const Engine::VTXTEX* GetTerrainVertex(void);

public:
	static	CTerrain*	Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit	CTerrain(LPDIRECT3DDEVICE9 pDevice);
public:
	~CTerrain(void);

};
#endif // Terrain_h__
