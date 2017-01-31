/********************************************************************
	created:	2017/01/15
	created:	15:1:2017   3:24
	filename: 	c:\Users\Administrator\Desktop\새 폴더\trunk\Engine\Utility\Code\Action.h
	file path:	c:\Users\Administrator\Desktop\새 폴더\trunk\Engine\Utility\Code
	file base:	Action
	file ext:	h
	author:		
	
	purpose:	오브잭트의 행동(점프, 공격등) 또는 판정 관리
*********************************************************************/
#ifndef Action_h__
#define Action_h__

#include "Component.h"

namespace Engine
{
	class CGameObject;
	class CTransform;
	class CTimeMgr;
}

class CAction : public Engine::CComponent
{
private:
	Engine::CGameObject*			m_pGameObj;
	const Engine::CComponent*		m_pTransform;
	const Engine::CComponent*		m_pTerrainCol;

	Engine::CTimeMgr*				m_pTimeMgr;
	float							m_fTime;

private:
	float			m_fGravity;
	float			m_fAcceleration;
	float			m_fStartEnergy;

	bool			m_bFall;
	bool			m_bJump;
	bool			m_bJumpStart;

public:
	void	JumpMove(void);
	void	Attack(void);

public:
	virtual void Update(void);

public:
	static CAction*	Create(Engine::CGameObject* pGameObj);

private:
	explicit	CAction(Engine::CGameObject* pGameObj);
public:
	virtual	~CAction(void);
};

#endif // Action_h__