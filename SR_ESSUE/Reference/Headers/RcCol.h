#ifndef RcCol_h__
#define RcCol_h__

#include "VIBuffer.h"

BEGIN(Engine)

class ENGINE_DLL CRcCol
	:public CVIBuffer
{
private:
	void	Release(void);

public:
	virtual HRESULT CreateBuffer(void);
	virtual	void	Render(void);

public:
	static Engine::CRcCol* Create(LPDIRECT3DDEVICE9 pDevice);

private:
	explicit CRcCol(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CRcCol(void);

};

END
#endif // RcCol_h__
