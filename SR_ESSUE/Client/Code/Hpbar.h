/*!
 * \file HpBar.h
 * \date 2017/01/16 4:50
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 플레이어&몬스터?의 체력을 보여줄 UI
 *
 * TODO: long description
 *
 * \note UI옵저버로 객체들의 체력과 마력값을 가져올 것이다.
*/

#ifndef HpBar_h__
#define HpBar_h__

#include "UI.h"

namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
}

class CUIObserver;
class CHpBar
	:public Engine::CUI
{
private:
	Engine::CResourceMgr*		m_pResourceMgr;
	Engine::CVIBuffer*			m_pBuffer;
	Engine::CTexture*			m_pTexture;

	Engine::VTXTEX*				m_pVertex;
	Engine::VTXTEX*				m_pConvertVertex;
	DWORD						m_dwVtxCnt;

private:
	HRESULT			Initialize(void);
	void			SetTransform(void);

public:
	void			Update(void);
	void			Render(void);
	void			Release(void);
	HRESULT			AddComponent(void);

public:
	static	CHpBar*		Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CHpBar(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CHpBar(void);
};

#endif // HpBar_h__