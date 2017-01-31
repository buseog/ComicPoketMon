/*!
 * \file HpBar.h
 * \date 2017/01/16 4:50
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �÷��̾�&����?�� ü���� ������ UI
 *
 * TODO: long description
 *
 * \note UI�������� ��ü���� ü�°� ���°��� ������ ���̴�.
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