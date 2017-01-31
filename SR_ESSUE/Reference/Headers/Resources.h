/*!
 * \file Resources.h
 * \date 2017/01/07 1:42
 *
 * \author Administrator
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Resources_h__
#define Resources_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CResources
	:public CComponent
{
protected:
	LPDIRECT3DDEVICE9	m_pDevice;
	WORD*				m_pwRefCnt;

public:
	virtual void Render(void) PURE;
	virtual void Release(void);
	virtual CResources* CloneResource(void) PURE;

protected:
	explicit CResources(LPDIRECT3DDEVICE9 pDevice);
	
public:
	virtual ~CResources(void);

};

END
#endif // Resources_h__