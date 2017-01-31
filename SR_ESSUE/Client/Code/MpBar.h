/*!
 * \file MpBar.h
 * \date 2017/01/16 4:35
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief �÷��̾��� ������ ������ UI
 *
 * TODO: long description
 *
 * \note �������� �÷��̾� ������ �޾ƴٰ� ����� ����
*/

#ifndef MpBar_h__
#define MpBar_h__

#include "UI.h"

namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
}

class CUIObserver;
class CMpBar
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
	HRESULT		Initialize(void);
	void		SetTransform(void);

public:
	void			Update(void);
	void			Render(void);
	void			Release(void);
	HRESULT			AddComponent(void);

public:
	static	CMpBar*		Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CMpBar(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CMpBar(void);
};

#endif // MpBar_h__