/*!
 * \file Infomation.h
 * \date 2017/01/10 4:50
 *
 * \author ESSUE
 * Contact: user@company.com
 *
 * \brief 
 *
 * TODO: long description
 *
 * \note
*/

#ifndef Infomation_h__
#define Infomation_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CInfomation
	:public CComponent
{
public:
	wstring wstrObjKey;
	float	fHp;
	float	fSpeed;
	float	fAttack;

public:
	static CInfomation* Create(const D3DXVECTOR3& vLook);

private:
	CInfomation(void);

public:
	virtual ~CInfomation(void);
};

END
#endif // Infomation_h__