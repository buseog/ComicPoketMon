/*!
 * \file Transform.h
 * \date 2017/01/08 16:32
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

#ifndef Transform_h__
#define Transform_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform
	:public CComponent
{
public:
	float		fAngle[ANGLE_END];
	D3DXVECTOR3	vPos;
	D3DXVECTOR3	vDir;
	D3DXMATRIX	matWorld;

public:
	virtual void Update(void);

public:
	static CTransform* Create(const D3DXVECTOR3& vLook);

private:
	explicit CTransform(const D3DXVECTOR3& vLook);
public:
	virtual ~CTransform(void);
};

END
#endif // Transform_h__