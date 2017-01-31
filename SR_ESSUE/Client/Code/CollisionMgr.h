/*!
 * \file CollisionMgr.h
 * \date 2017/01/14 22:30
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

#ifndef CollisionMgr_h__
#define CollisionMgr_h__

#include "Engine_Include.h"

namespace Engine
{
	class CCollision;
}

class CCollisionMgr
{
	DECLARE_SINGLETON(CCollisionMgr)

public:
	enum COLLISIONID { COL_TERRAIN, COL_MOUSE, COL_BOUND};

private:
	typedef map<COLLISIONID, Engine::CCollision*>		MAPCOLLISION;
	MAPCOLLISION										m_mapCollision;

private:
	void	Release(void);

public:
	HRESULT		AddColObject(COLLISIONID eCollisionID);
	Engine::CCollision* CloneColObject(COLLISIONID eCollisionID);

private:
	CCollisionMgr(void);
	~CCollisionMgr(void);
};

#endif // CollisionMgr_h__