/*!
 * \file Effect.h
 * \date 2017/01/25 5:17
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 이펙트 스프라이트 돌릴 클래스
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Effect_h__
#define Effect_h__

#include "SingleGameObject.h"
#include "Sprite.h"

class CEffect
	:public CSingleGameObject
{
private:
	Engine::VTXCUBE*	m_pVertex;
	Engine::VTXCUBE*	m_pConvertVertex;

	Engine::CSprite*	m_pSprite;
	wstring				m_wstrObjkey;

private:
	HRESULT				Initialize(D3DXVECTOR3 vPos, const wstring& wstrObjKey);
	void				SetTransform(void);

public:
	void				Update(void);
	void				Render(void);
	void				Release(void);
	HRESULT				AddComponent(void);

public:
	static	CEffect*	Create(LPDIRECT3DDEVICE9 pDevice, D3DXVECTOR3 vPos, const wstring& wstrObjKey);

private:
	explicit CEffect(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CEffect(void);
};

#endif // Effect_h__