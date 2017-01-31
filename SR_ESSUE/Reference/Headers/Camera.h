/*!
 * \file Camera.h
 * \date 2017/01/08 18:21
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

#ifndef Camera_h__
#define Camera_h__

#include "GameObject.h"

BEGIN(Engine)

class ENGINE_DLL CCamera
	:public CGameObject
{
protected:
	D3DXMATRIX		m_matView, m_matProj;
	D3DXVECTOR3		m_vEye, m_vAt, m_vUp;

public:
	void	SetViewSpaceMatrix(const D3DXVECTOR3* pEye, const D3DXVECTOR3* pAt, const D3DXVECTOR3* pUp);
	void	SetProjectionMatrix(const float& fFovY, const float& fAspect, const float& fNear, const float& fFar);

public:
	D3DXMATRIX	GetView(void);
	D3DXMATRIX	GetProj(void);

protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pDevice);

public:
	virtual ~CCamera(void);

};

END
#endif // Camera_h__