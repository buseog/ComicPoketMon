#ifndef ItemParts_h__
#define ItemParts_h__

#include "SingleGameObject.h"
#include "TerrainCol.h"
#include "BoundCol.h"

namespace	Engine
{
	class CTransform;
	class CLayer;
}
class CItemParts 
	: public CSingleGameObject
{
private:
	Engine::VTXCUBE*	m_pVertex;
	Engine::VTXCUBE*	m_pConvertVertex;
	wstring				m_wstrTextureKey;
	Engine::CLayer*		m_pLayer;

	float				m_fDijilGerGatDa;
	
	// 플레이어와 충돌을 위해 만들어둔 변수
	Engine::CTransform*	m_pTargetInfo;
	CTerrainCol*		m_pTerrainCol;
	CBoundCol*			m_pBoundCol;

	bool				m_bCulling;

private:
	HRESULT				Initialize(Engine::CTransform* pInfo);
	HRESULT				Initialize(void);
	void				SetTransform(void);
	void				Load(void);

	void				ColPlayer(void);
public:
	HRESULT				AddComponent(void);
	void				Update(void);
	void				Render(void);
	void				Release(void);

public:
	static	CItemParts*		Create(LPDIRECT3DDEVICE9 pDevice);
	static	CItemParts*		Create(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, Engine::CTransform* pInfo, const wstring& wstrObjKey);

private:
	explicit	CItemParts(LPDIRECT3DDEVICE9 pDevice);
	explicit	CItemParts(LPDIRECT3DDEVICE9 pDevice, Engine::CLayer* pLayer, const wstring& wstrObjKey);

public:
	virtual ~CItemParts(void);

};
#endif // ItemParts_h__
