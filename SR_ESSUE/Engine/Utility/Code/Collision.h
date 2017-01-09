/*!
 * \file Collision.h
 * \date 2017/01/08 18:15
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

#ifndef Collision_h__
#define Collision_h__

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CCollision
{
protected:
	WORD*			m_pwRefCnt;

protected:
	void	Release(void);

public:
	virtual CCollision*	Clone(void)PURE;

protected:
	CCollision(void);

public:
	virtual ~CCollision(void);

};

END
#endif // Collision_h__