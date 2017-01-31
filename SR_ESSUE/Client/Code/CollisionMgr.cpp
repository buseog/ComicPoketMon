#include "stdafx.h"
#include "CollisionMgr.h"
#include "Collision.h"
#include "Export_Function.h"
#include "TerrainCol.h"
#include "MouseCol.h"
#include "BoundCol.h"

IMPLEMENT_SINGLETON(CCollisionMgr)

CCollisionMgr::CCollisionMgr(void)
{

}

CCollisionMgr::~CCollisionMgr(void)
{
	Release();
}


HRESULT CCollisionMgr::AddColObject(COLLISIONID eCollisionID)
{
	MAPCOLLISION::iterator	iter = m_mapCollision.find(eCollisionID);

	if(iter != m_mapCollision.end())
	{
		TAGMSG_BOX(L"CollisinMgr", L"捞固 积己等 面倒");
		return E_FAIL;
	}

	Engine::CCollision*		pCollision = NULL;

	switch(eCollisionID)
	{
	case COL_TERRAIN:
		pCollision = CTerrainCol::Create();
		break;

	case COL_MOUSE:
		pCollision = CMouseCol::Create();
		break;

	case COL_BOUND:
		pCollision = CBoundCol::Create();
		break;
	}

	NULL_CHECK_RETURN(pCollision, E_FAIL);

	m_mapCollision.insert(MAPCOLLISION::value_type(eCollisionID, pCollision));

	return S_OK;
}

Engine::CCollision* CCollisionMgr::CloneColObject(COLLISIONID eCollisionID)
{
	MAPCOLLISION::iterator	iter = m_mapCollision.find(eCollisionID);

	if(iter == m_mapCollision.end())
		return NULL;

	return iter->second->Clone();
}

void CCollisionMgr::Release(void)
{
	for_each(m_mapCollision.begin(), m_mapCollision.end(), Engine::CDeleteMap());
	m_mapCollision.clear();
}
