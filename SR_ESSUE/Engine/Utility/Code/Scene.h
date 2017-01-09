#ifndef Scene_h__
#define Scene_h__

#include "Engine_Include.h"

BEGIN(Engine)

class CLayer;
class ENGINE_DLL CScene
{
protected:
	typedef	map<WORD, CLayer*>		MAPLAYER;
	MAPLAYER						m_mapLayer;
	LPDIRECT3DDEVICE9				m_pDevice;

protected:
	void	Release(void);

public:
	virtual HRESULT	InitScene(void);
	virtual	void	Update(void);
	virtual void	Render(void);

protected:
	explicit CScene(LPDIRECT3DDEVICE9 _pDeivce);
public:
	virtual ~CScene(void);

};

END
#endif // Scene_h__
