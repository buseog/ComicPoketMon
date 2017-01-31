/*!
 * \file Status.h
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

#ifndef Status_h__
#define Status_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CStatus
	:public CComponent
{
public:
	wstring wstrObjKey;

	float	fHp;
	float	fFullHp;

	float	fMp;
	float	fFullMp;

	float	fSpeed;
	float	fAttack;

public:
	static CStatus* Create(void);
	static CStatus* Create(float _fHp, float _fMp, float _fSpeed, float _fAttack);

private:
	CStatus( float _fHp, float _fMp, float _fSpeed, float _fAttack );
	CStatus(void);

public:
	virtual ~CStatus(void);
};

END
#endif // Status_h__