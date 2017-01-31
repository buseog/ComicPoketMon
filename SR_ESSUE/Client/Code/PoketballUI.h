#ifndef PoketballUI_h__
#define PoketballUI_h__

#include "UI.h"

namespace Engine
{
	class CResourceMgr;
	class CTexture;
	class CVIBuffer;
}

class CUIObserver;
class CPoketballUI
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

	void			SetPos(D3DXVECTOR3 vPos);

public:
	static	CPoketballUI*		Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CPoketballUI(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CPoketballUI(void);
};

#endif // PoketballUI_h__
