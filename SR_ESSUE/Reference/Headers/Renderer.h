#ifndef Renderer_h__
#define Renderer_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CScene;
class ENGINE_DLL CRenderer
{
private:
	LPDIRECT3DDEVICE9		m_pDevice;
	CScene*					m_pScene;

public:
	static	CRenderer*	Create(LPDIRECT3DDEVICE9 pDevice);
	HRESULT				InitRenderer(void);
	void				Render(void);

public:
	void				SetScene(CScene* _pScene);

private:
	explicit CRenderer(LPDIRECT3DDEVICE9 pDevice);
public:
	~CRenderer(void);

};

END


#endif // Renderer_h__
