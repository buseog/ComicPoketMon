#ifndef TriCol_h__
#define TriCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CTriCol
	:public CVIBuffer
{
private:
	void	Release(void);

public:
	virtual HRESULT CreateBuffer(void);
	virtual void	Render(void);

public:
	static	Engine::CTriCol* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CTriCol(LPDIRECT3DDEVICE9 pDevice);
public:
	virtual ~CTriCol(void);

};

END
#endif // TriCol_h__
