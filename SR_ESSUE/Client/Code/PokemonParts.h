/*!
 * \file PokemonParts.h
 * \date 2017/01/23 21:14
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \ 아이템 파츠입니다
*/
#ifndef PokemonParts_h__
#define PokemonParts_h__


#include "SingleGameObject.h"
#include "TerrainCol.h"
#include "BoundCol.h"


namespace Engine
{
	class CLayer;
}

class CPokemonParts :
	public CSingleGameObject
{
private:
	Engine::VTXCUBE*	m_pVertex;
	Engine::VTXCUBE*	m_pConvertVertex;
	DWORD				m_dwType;
	DWORD				m_dwState;
	float				m_fHeight;
	wstring				m_wstrObjkey;

	wstring				m_wstrTextureKey;
	float				m_fJukCoShipDa;

	int					m_iNanWaeSalcca;

	// 콜리전
	CTerrainCol*		m_pTerrainCol;
	CBoundCol*			m_pBoundCol;

	const Engine::VTXTEX*	m_pTerrainVtx;

	// 스테이지 씬
	Engine::CLayer*		m_pLayer;

private:
	HRESULT				Initialize(Engine::CTransform* pInfo);
	void				SetTransform(void);

	void				ColPlayer(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);
	void				SetLayer(Engine::CLayer* pLayer);
	wstring				GetObjkey(void);

public:
	static	CPokemonParts*	Create(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, Engine::CTransform* pInfo, const wstring& wstrObjKey);

private:
	explicit CPokemonParts(LPDIRECT3DDEVICE9 pDevice);
	explicit CPokemonParts(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, const wstring& wstrObjKey);

public:
	virtual ~CPokemonParts(void);
};



#endif // PokemonParts_h__